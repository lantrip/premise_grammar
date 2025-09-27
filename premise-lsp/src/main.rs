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
            let list = symbols::to_document_symbols(&analysis);
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
                if name.starts_with("local.@") {
                    match scope::resolve_local_at_definition(&self.state, current_uri, &name).await {
                        Ok(Some(loc)) => return Ok(Some(lsp::GotoDefinitionResponse::Scalar(loc))),
                        Ok(None) => {},
                        Err(err) => {
                            tracing::warn!("local.@ definition resolution error: {}", err);
                        }
                    }
                } else {
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
                if name.starts_with("local.@") {
                    match scope::resolve_local_at_references(&self.state, current_uri, &name).await {
                        Ok(out) if !out.is_empty() => return Ok(Some(out)),
                        Ok(_) => {},
                        Err(err) => {
                            tracing::warn!("local.@ references resolution error: {}", err);
                        }
                    }
                } else {
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
                if name.starts_with("local.@") {
                    if let Ok(Some(loc)) = scope::resolve_local_at_definition(&self.state, uri, &name).await {
                        contents.push_str(&format!("\nDefined in: {}", loc.uri));
                    }
                } else if let Ok(Some(loc)) = scope::resolve_global_definition(&self.state, uri, &name).await {
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

    // workspace/symbol not implemented for this tower-lsp version
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
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .with_writer(std::io::stderr)
        .init();

    let (stdin, stdout) = (tokio::io::stdin(), tokio::io::stdout());
    let state = Arc::new(RwLock::new(WorldState::default()));
    let (service, socket) = LspService::build(|client| PremiseServer { client, state: state.clone() }).finish();
    Server::new(stdin, stdout, socket).serve(service).await;
    Ok(())
}


