use std::sync::Arc;

use anyhow::Result;
use tokio::sync::RwLock;
use tower_lsp::jsonrpc::Result as LspResult;
use tower_lsp::lsp_types as lsp;
use tower_lsp::{Client, LanguageServer, LspService, Server};

mod diagnostics;
mod symbols;
mod ast_utils;
mod scope;
mod index;

#[derive(Default)]
struct DocumentState {
    text: String,
    version: i32,
}

#[derive(Default)]
struct WorldState {
    // Track open documents by URI
    docs: std::collections::HashMap<lsp::Url, DocumentState>,
    workspace_folders: Vec<lsp::WorkspaceFolder>,
    index: index::EntityIndex,
}

struct PremiseServer {
    client: Client,
    state: Arc<RwLock<WorldState>>,
}

#[tower_lsp::async_trait]
impl LanguageServer for PremiseServer {
    async fn initialize(&self, params: lsp::InitializeParams) -> LspResult<lsp::InitializeResult> {
        {
            let mut st = self.state.write().await;
            st.workspace_folders = params.workspace_folders.unwrap_or_default();
            // Seed index roots from workspace folders (file scheme only)
            let roots: Vec<std::path::PathBuf> = st
                .workspace_folders
                .iter()
                .filter_map(|wf| wf.uri.to_file_path().ok())
                .collect();
            st.index.set_roots(roots);
        }
        let capabilities = lsp::ServerCapabilities {
            text_document_sync: Some(lsp::TextDocumentSyncCapability::Kind(
                lsp::TextDocumentSyncKind::INCREMENTAL,
            )),
            document_symbol_provider: Some(lsp::OneOf::Left(true)),
            definition_provider: Some(lsp::OneOf::Left(true)),
            references_provider: Some(lsp::OneOf::Left(true)),
            hover_provider: Some(lsp::HoverProviderCapability::Simple(true)),
            completion_provider: Some(lsp::CompletionOptions::default()),
            execute_command_provider: Some(lsp::ExecuteCommandOptions { commands: vec!["premise.entityBeats".into(), "premise.scanWorkspace".into()], work_done_progress_options: Default::default() }),
            ..Default::default()
        };
        Ok(lsp::InitializeResult { capabilities, server_info: None })
    }
    async fn document_symbol(
        &self,
        params: lsp::DocumentSymbolParams,
    ) -> LspResult<Option<lsp::DocumentSymbolResponse>> {
        let text = {
            let st = self.state.read().await;
            st.docs.get(&params.text_document.uri).map(|d| d.text.clone())
        };
        if let Some(text) = text {
            let mut parser = premise_core::Parser::new();
            let analysis = parser.analyze_symbols(&text);
            let mut list = symbols::to_document_symbols(&analysis);
            let ir = parser.analyze_ir(&text);
            // Compute global ordinals by alphanumeric order across the story root.
            let offsets = {
                // Find story root for this file
                let uri = &params.text_document.uri;
                let st = self.state.read().await;
                let ord = if let Some(path) = uri.to_file_path().ok() {
                    let parent = path.parent().unwrap_or(std::path::Path::new("."));
                    let story_root = crate::scope::find_story_root(parent).unwrap_or_else(|| parent.to_path_buf());
                    // Walk all files under story root, sort, accumulate counts until current file
                    let mut files: Vec<std::path::PathBuf> = Vec::new();
                    for entry in walkdir::WalkDir::new(&story_root).into_iter().filter_map(|e| e.ok()) {
                        let p = entry.path();
                        if p.is_file() && p.extension().and_then(|e| e.to_str()) == Some("prem") {
                            files.push(p.to_path_buf());
                        }
                    }
                    files.sort();
                    let mut counts = symbols::OrdinalOffsets::default();
                    for p in files {
                        // Accumulate from text if open, else from disk
                        let (t, is_current) = if let Ok(u) = lsp::Url::from_file_path(&p) {
                            if let Some(doc) = st.docs.get(&u) { (Some(doc.text.clone()), u == *uri) } else {
                                let txt = std::fs::read_to_string(&p).ok();
                                (txt, u == *uri)
                            }
                        } else { (None, false) };
                        if let Some(t) = t {
                            let mut pparser = premise_core::Parser::new();
                            let irx = pparser.analyze_ir(&t);
                            if is_current { break; }
                            counts.acts += irx.ir.story.acts.len();
                            counts.scenes += irx.ir.story.scenes.len();
                            counts.cels += irx.ir.story.cels.len();
                        }
                    }
                    counts
                } else { symbols::OrdinalOffsets::default() };
                ord
            };
            let mut story_list = symbols::story_to_document_symbols(&ir, &params.text_document.uri, offsets);
            list.append(&mut story_list);
            return Ok(Some(lsp::DocumentSymbolResponse::Nested(list)));
        }
        Ok(None)
    }

    async fn initialized(&self, _: lsp::InitializedParams) {
        let _ = self
            .client
            .log_message(lsp::MessageType::INFO, "Premise LSP initialized");
        // Background scan of roots to warm the index
        let state = self.state.clone();
        tokio::spawn(async move {
            let mut st = state.write().await;
            for root in st.index.list_roots() {
                st.index.scan_root_from_disk(&root);
            }
        });
    }

    async fn shutdown(&self) -> LspResult<()> { Ok(()) }

    async fn did_open(&self, params: lsp::DidOpenTextDocumentParams) {
        let mut st = self.state.write().await;
        let doc = params.text_document;
        let text_for_index = doc.text.clone();
        st.docs.insert(
            doc.uri.clone(),
            DocumentState { text: doc.text, version: doc.version },
        );
        if let Some(path) = doc.uri.to_file_path().ok() {
            st.index.index_text(path, doc.uri.clone(), &text_for_index);
            // Seed roots with the file's story root and run an initial scan
            let story_root = {
                let p = doc.uri.to_file_path().ok();
                let parent = p.as_ref().and_then(|pp| pp.parent()).unwrap_or(std::path::Path::new("."));
                scope::find_story_root(parent).unwrap_or_else(|| parent.to_path_buf())
            };
            let mut roots = st.index.list_roots();
            if !roots.iter().any(|r| r == &story_root) {
                roots.push(story_root.clone());
                st.index.set_roots(roots);
                st.index.scan_root_from_disk(&story_root);
            }
        }
        drop(st);
        self.validate_and_publish(&doc.uri).await;
    }

    async fn did_change(&self, params: lsp::DidChangeTextDocumentParams) {
        let mut st = self.state.write().await;
        let uri = params.text_document.uri.clone();
        let mut text_for_index: Option<String> = None;
        if let Some(entry) = st.docs.get_mut(&uri) {
            entry.version = params.text_document.version;
            for change in params.content_changes {
                if let Some(_range) = change.range {
                    // For simplicity, replace full text on any change. Optimize later.
                    entry.text = change.text;
                } else {
                    entry.text = change.text;
                }
            }
            text_for_index = Some(entry.text.clone());
        }
        if let (Some(text), Some(path)) = (text_for_index, uri.to_file_path().ok()) {
            st.index.index_text(path, uri.clone(), &text);
        }
        drop(st);
        self.validate_and_publish(&uri).await;
    }

    async fn did_close(&self, params: lsp::DidCloseTextDocumentParams) {
        let mut st = self.state.write().await;
        let uri = &params.text_document.uri;
        if let Some(path) = uri.to_file_path().ok() {
            st.index.remove_file(&path);
        }
        st.docs.remove(uri);
    }


    async fn goto_definition(&self, params: lsp::GotoDefinitionParams) -> LspResult<Option<lsp::GotoDefinitionResponse>> {
        tracing::info!("goto_definition request received");
        let text_and_ast = {
            let st = self.state.read().await;
            let tdp = &params.text_document_position_params;
            if let Some(doc) = st.docs.get(&tdp.text_document.uri) {
                let mut parser = premise_core::Parser::new();
                let (_, _, ast) = parser.parse_str(&doc.text);
                (Some(doc.text.clone()), ast)
            } else {
                (None, None)
            }
        };
        if let (Some(text), Some(ast)) = text_and_ast {
            let pos = params.text_document_position_params.position;
            if let Some(name) = ast_utils::name_at(&ast, pos.line, pos.character, &text) {
                tracing::info!(name = %name, "name under cursor for definition");
                let current_uri = &params.text_document_position_params.text_document.uri;
                // Prefer index-backed global search
                if let Ok(Some(loc)) = scope::resolve_global_definition(&self.state, current_uri, &name).await {
                    return Ok(Some(lsp::GotoDefinitionResponse::Scalar(loc)));
                }
                let defs = ast_utils::collect_entity_definitions(&ast, &text);
                for (def_name, range) in defs {
                    if def_name == name {
                        let loc = lsp::Location { uri: current_uri.clone(), range: diagnostics::to_lsp_range(range) };
                        return Ok(Some(lsp::GotoDefinitionResponse::Scalar(loc)));
                    }
                }
            }
        }
        Ok(None)
    }

    async fn references(&self, params: lsp::ReferenceParams) -> LspResult<Option<Vec<lsp::Location>>> {
        tracing::info!("references request received");
        let text_and_ast = {
            let st = self.state.read().await;
            if let Some(doc) = st.docs.get(&params.text_document_position.text_document.uri) {
                let mut parser = premise_core::Parser::new();
                let (_, _, ast) = parser.parse_str(&doc.text);
                (Some(doc.text.clone()), ast)
            } else {
                (None, None)
            }
        };
        if let (Some(text), Some(ast)) = text_and_ast {
            let pos = params.text_document_position.position;
            if let Some(name) = ast_utils::name_at(&ast, pos.line, pos.character, &text) {
                tracing::info!(name = %name, "name under cursor for references");
                let current_uri = &params.text_document_position.text_document.uri;
                if let Ok(out) = scope::resolve_global_references(&self.state, current_uri, &name).await {
                    if !out.is_empty() { return Ok(Some(out)); }
                }
                let defs = ast_utils::collect_entity_definitions(&ast, &text);
                let refs = ast_utils::collect_entity_references(&ast, &text);
                if defs.iter().any(|(n, _)| n == &name) {
                    let mut out = Vec::new();
                    for (_n, r) in refs.into_iter().filter(|(n, _)| n == &name) {
                        out.push(lsp::Location { uri: current_uri.clone(), range: diagnostics::to_lsp_range(r) });
                    }
                    return Ok(Some(out));
                }
            }
        }
        Ok(None)
    }

    async fn hover(&self, params: lsp::HoverParams) -> LspResult<Option<lsp::Hover>> {
        tracing::info!("hover request received");
        let text_and_ast = {
            let st = self.state.read().await;
            if let Some(doc) = st.docs.get(&params.text_document_position_params.text_document.uri) {
                let mut parser = premise_core::Parser::new();
                let (_, _, ast) = parser.parse_str(&doc.text);
                (Some(doc.text.clone()), ast)
            } else {
                (None, None)
            }
        };
        if let (Some(text), Some(ast)) = text_and_ast {
            let pos = params.text_document_position_params.position;
            if let Some(name) = ast_utils::name_at(&ast, pos.line, pos.character, &text) {
                tracing::info!(name = %name, "name under cursor for hover");
                let mut contents = format!("Entity: {}", name);
                // Try to include file path if resolved globally
                let uri = &params.text_document_position_params.text_document.uri;
                if let Ok(Some(loc)) = scope::resolve_global_definition(&self.state, uri, &name).await {
                    contents.push_str(&format!("\nDefined in: {}", loc.uri));
                }
                let hover = lsp::Hover { contents: lsp::HoverContents::Scalar(lsp::MarkedString::String(contents)), range: None };
                return Ok(Some(hover));
            }
        }
        Ok(None)
    }

    async fn completion(&self, params: lsp::CompletionParams) -> LspResult<Option<lsp::CompletionResponse>> {
        let text_and_ast = {
            let st = self.state.read().await;
            if let Some(doc) = st.docs.get(&params.text_document_position.text_document.uri) {
                let mut parser = premise_core::Parser::new();
                let (_, _, ast) = parser.parse_str(&doc.text);
                (Some(doc.text.clone()), ast)
            } else { (None, None) }
        };
        if let (Some(text), Some(ast)) = text_and_ast {
            let pos = params.text_document_position.position;
            let uri = &params.text_document_position.text_document.uri;
            if let Some(prefix) = ast_utils::reference_name_at(&ast, pos.line, pos.character, &text) {
                let mut items: Vec<lsp::CompletionItem> = Vec::new();
                if prefix.starts_with("local.@") {
                    if let Ok(names) = scope::list_entity_names_in_story_root(&self.state, uri).await {
                        for n in names.into_iter().filter(|n| format!("local.@{}", n).starts_with(&prefix)) {
                            items.push(lsp::CompletionItem { label: format!("local.@{}", n), kind: Some(lsp::CompletionItemKind::REFERENCE), ..Default::default() });
                        }
                    }
                } else {
                    if let Ok(names) = scope::list_entity_names_in_story_root(&self.state, uri).await {
                        for n in names.into_iter().filter(|n| n.starts_with(&prefix)) {
                            items.push(lsp::CompletionItem { label: n, kind: Some(lsp::CompletionItemKind::REFERENCE), ..Default::default() });
                        }
                    }
                }
                return Ok(Some(lsp::CompletionResponse::Array(items)));
            }
        }
        Ok(None)
    }

    async fn execute_command(&self, params: lsp::ExecuteCommandParams) -> LspResult<Option<serde_json::Value>> {
        if params.command == "premise.scanWorkspace" {
            // Force a full rescan of all known roots
            let mut st = self.state.write().await;
            let roots = st.index.list_roots();
            for root in roots { st.index.scan_root_from_disk(&root); }
            return Ok(Some(serde_json::json!({ "ok": true })));
        }
        if params.command != "premise.entityBeats" { return Ok(None); }
        // Expect args: [uri: string, entityName: string]
        let args = params.arguments;
        if args.len() < 2 {
            return Ok(Some(serde_json::json!({ "error": "Expected [uri, entityName]" })));
        }
        let uri_str = args[0].as_str().unwrap_or("");
        let name_str = args[1].as_str().unwrap_or("");
        if uri_str.is_empty() || name_str.is_empty() {
            return Ok(Some(serde_json::json!({ "error": "Expected non-empty [uri, entityName]" })));
        }
        let (uri, name) = (lsp::Url::parse(uri_str).unwrap_or_else(|_| lsp::Url::parse("file:///" ).unwrap()), name_str.to_string());

        // Gather refs via existing global logic
        let mut hits = match scope::resolve_global_references(&self.state, &uri, &name).await { Ok(v) => v, Err(_) => Vec::new() };
        // Deterministic ordering: by uri path (alphanumeric), then start line/character
        hits.sort_by(|a, b| {
            let ap = a.uri.to_string();
            let bp = b.uri.to_string();
            ap.cmp(&bp).then_with(|| a.range.start.line.cmp(&b.range.start.line)).then_with(|| a.range.start.character.cmp(&b.range.start.character))
        });

        let mut out: Vec<serde_json::Value> = Vec::new();
        for loc in hits {
            // Acquire text and ast for the file of this reference
            let (text, ast) = {
                let st = self.state.read().await;
                if let Some(doc) = st.docs.get(&loc.uri) {
                    let mut p = premise_core::Parser::new();
                    let (_, _, ast) = p.parse_str(&doc.text);
                    (Some(doc.text.clone()), ast)
                } else if let Ok(path) = loc.uri.to_file_path() {
                    match std::fs::read_to_string(&path) {
                        Ok(t) => {
                            let mut p = premise_core::Parser::new();
                            let (_, _, ast) = p.parse_str(&t);
                            (Some(t), ast)
                        }
                        Err(_) => (None, None)
                    }
                } else { (None, None) }
            };
            if let (Some(text), Some(ast)) = (text, ast) {
                let line = loc.range.start.line;
                let ctx = crate::ast_utils::story_context_at(&ast, line, 0, &text);
                out.push(serde_json::json!({
                    "uri": loc.uri,
                    "range": loc.range,
                    "act": ctx.act,
                    "scene": ctx.scene,
                    "cel": ctx.cel,
                    "beat": ctx.beat,
                }));
            }
        }
        Ok(Some(serde_json::Value::Array(out)))
    }
}

impl PremiseServer {
    async fn validate_and_publish(&self, uri: &lsp::Url) {
        let text = {
            let st = self.state.read().await;
            st.docs.get(uri).map(|d| d.text.clone())
        };
        if let Some(text) = text {
            let mut parser = premise_core::Parser::new();
            let report = parser.validate(&text);
            let diags = diagnostics::to_lsp_diagnostics(&report);
            let _ = self.client.publish_diagnostics(uri.clone(), diags, None).await;
        }
    }
}

#[tokio::main]
async fn main() -> Result<()> {
    // Plain logs without ANSI to avoid noisy control codes in clients
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .with_ansi(false)
        .with_writer(std::io::stderr)
        .init();

    let (stdin, stdout) = (tokio::io::stdin(), tokio::io::stdout());
    let state = Arc::new(RwLock::new(WorldState::default()));
    let (service, socket) = LspService::build(|client| PremiseServer { client, state: state.clone() }).finish();
    Server::new(stdin, stdout, socket).serve(service).await;
    Ok(())
}


