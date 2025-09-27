use std::path::{Path, PathBuf};
use std::sync::Arc;

use anyhow::Result;
use tokio::sync::RwLock;
use tower_lsp::lsp_types as lsp;
use walkdir::WalkDir;

use crate::{ast_utils, diagnostics::to_lsp_range, WorldState};

fn url_to_path(url: &lsp::Url) -> Option<PathBuf> {
    url.to_file_path().ok()
}

pub fn find_story_root(start: &Path) -> Option<PathBuf> {
    let mut dir = start.to_path_buf();
    let ws_root = dir.ancestors().last().map(|p| p.to_path_buf());
    while dir.parent().is_some() {
        let candidate = dir.join("story");
        if candidate.is_dir() { return Some(dir); }
        dir.pop();
    }
    ws_root
}

#[allow(dead_code)]
pub fn find_story_root_for_uri(uri: &lsp::Url) -> Option<PathBuf> {
    url_to_path(uri).and_then(|p| p.parent().map(|d| d.to_path_buf())).and_then(|d| find_story_root(&d))
}

pub async fn resolve_local_at_definition(state: &Arc<RwLock<WorldState>>, current_uri: &lsp::Url, name: &str) -> Result<Option<lsp::Location>> {
    let name = name.trim_start_matches("local.@").trim();
    let path = match url_to_path(current_uri) { Some(p) => p, None => return Ok(None) };
    let start_dir = path.parent().unwrap_or(Path::new("."));
    let story_root = find_story_root(start_dir).unwrap_or_else(|| start_dir.to_path_buf());

    // Try index first
    {
        let st = state.read().await;
        let defs = st.index.get_defs_in_root(&story_root, name);
        if let Some(loc) = defs.into_iter().next() { return Ok(Some(loc)); }
    }

    // Fallback: walkdir scan
    for entry in WalkDir::new(&story_root).into_iter().filter_map(|e| e.ok()) {
        let p = entry.path();
        if p.is_file() && p.extension().and_then(|e| e.to_str()) == Some("prem") {
            // Acquire text: prefer open docs, else read from disk
            let (text, uri) = {
                let st = state.read().await;
                let uri = lsp::Url::from_file_path(p).ok();
                if let Some(uri) = uri.clone() {
                    if let Some(doc) = st.docs.get(&uri) {
                        (Some(doc.text.clone()), Some(uri))
                    } else {
                        (None, Some(uri))
                    }
                } else { (None, None) }
            };
            let (content, uri) = if let Some(t) = text { (t, uri.unwrap()) } else {
                let t = match std::fs::read_to_string(p) { Ok(s) => s, Err(_) => continue };
                (t, lsp::Url::from_file_path(p).unwrap())
            };
            let mut parser = premise_core::Parser::new();
            let (_, _, ast) = parser.parse_str(&content);
            if let Some(ast) = ast {
                for (def_name, range) in ast_utils::collect_entity_definitions(&ast, &content) {
                    if def_name == name {
                        return Ok(Some(lsp::Location { uri, range: to_lsp_range(range) }));
                    }
                }
            }
        }
    }
    Ok(None)
}

pub async fn resolve_local_at_references(state: &Arc<RwLock<WorldState>>, current_uri: &lsp::Url, name: &str) -> Result<Vec<lsp::Location>> {
    let name = name.trim_start_matches("local.@").trim();
    let path = match url_to_path(current_uri) { Some(p) => p, None => return Ok(Vec::new()) };
    let start_dir = path.parent().unwrap_or(Path::new("."));
    let story_root = find_story_root(start_dir).unwrap_or_else(|| start_dir.to_path_buf());

    {
        let st = state.read().await;
        let refs = st.index.get_refs_in_root(&story_root, name);
        if !refs.is_empty() { return Ok(refs); }
    }

    let mut out = Vec::new();
    for entry in WalkDir::new(&story_root).into_iter().filter_map(|e| e.ok()) {
        let p = entry.path();
        if p.is_file() && p.extension().and_then(|e| e.to_str()) == Some("prem") {
            // Acquire text
            let (text, uri) = {
                let st = state.read().await;
                let uri = lsp::Url::from_file_path(p).ok();
                if let Some(uri) = uri.clone() {
                    if let Some(doc) = st.docs.get(&uri) {
                        (Some(doc.text.clone()), Some(uri))
                    } else {
                        (None, Some(uri))
                    }
                } else { (None, None) }
            };
            let (content, uri) = if let Some(t) = text { (t, uri.unwrap()) } else {
                let t = match std::fs::read_to_string(p) { Ok(s) => s, Err(_) => continue };
                (t, lsp::Url::from_file_path(p).unwrap())
            };
            let mut parser = premise_core::Parser::new();
            let (_, _, ast) = parser.parse_str(&content);
            if let Some(ast) = ast {
                let defs = ast_utils::collect_entity_definitions(&ast, &content);
                if defs.iter().any(|(n, _)| n == name) {
                    for (_n, r) in ast_utils::collect_entity_references(&ast, &content).into_iter().filter(|(n, _)| n == name) {
                        out.push(lsp::Location { uri: uri.clone(), range: to_lsp_range(r) });
                    }
                }
            }
        }
    }
    Ok(out)
}

pub async fn resolve_global_definition(state: &Arc<RwLock<WorldState>>, current_uri: &lsp::Url, name: &str) -> Result<Option<lsp::Location>> {
    let path = match url_to_path(current_uri) { Some(p) => p, None => return Ok(None) };
    let start_dir = path.parent().unwrap_or(Path::new("."));
    let story_root = find_story_root(start_dir).unwrap_or_else(|| start_dir.to_path_buf());
    let target = name.trim();
    // Try index first
    {
        let st = state.read().await;
        let defs = st.index.get_defs_in_root(&story_root, target);
        if let Some(loc) = defs.into_iter().next() { return Ok(Some(loc)); }
    }
    for entry in WalkDir::new(&story_root).into_iter().filter_map(|e| e.ok()) {
        let p = entry.path();
        if p.is_file() && p.extension().and_then(|e| e.to_str()) == Some("prem") {
            let (text, uri) = {
                let st = state.read().await;
                let uri = lsp::Url::from_file_path(p).ok();
                if let Some(uri) = uri.clone() {
                    if let Some(doc) = st.docs.get(&uri) { (Some(doc.text.clone()), Some(uri)) } else { (None, Some(uri)) }
                } else { (None, None) }
            };
            let (content, uri) = if let Some(t) = text { (t, uri.unwrap()) } else {
                let t = match std::fs::read_to_string(p) { Ok(s) => s, Err(_) => continue };
                (t, lsp::Url::from_file_path(p).unwrap())
            };
            let mut parser = premise_core::Parser::new();
            let (_, _, ast) = parser.parse_str(&content);
            if let Some(ast) = ast {
                for (def_name, range) in ast_utils::collect_entity_definitions(&ast, &content) {
                    if def_name == target {
                        return Ok(Some(lsp::Location { uri, range: to_lsp_range(range) }));
                    }
                }
            }
        }
    }
    Ok(None)
}

pub async fn resolve_global_references(state: &Arc<RwLock<WorldState>>, current_uri: &lsp::Url, name: &str) -> Result<Vec<lsp::Location>> {
    let path = match url_to_path(current_uri) { Some(p) => p, None => return Ok(Vec::new()) };
    let start_dir = path.parent().unwrap_or(Path::new("."));
    let story_root = find_story_root(start_dir).unwrap_or_else(|| start_dir.to_path_buf());
    let target = name.trim();
    // Try index first
    {
        let st = state.read().await;
        let refs = st.index.get_refs_in_root(&story_root, target);
        if !refs.is_empty() { return Ok(refs); }
    }
    let mut out = Vec::new();
    for entry in WalkDir::new(&story_root).into_iter().filter_map(|e| e.ok()) {
        let p = entry.path();
        if p.is_file() && p.extension().and_then(|e| e.to_str()) == Some("prem") {
            let (text, uri) = {
                let st = state.read().await;
                let uri = lsp::Url::from_file_path(p).ok();
                if let Some(uri) = uri.clone() {
                    if let Some(doc) = st.docs.get(&uri) { (Some(doc.text.clone()), Some(uri)) } else { (None, Some(uri)) }
                } else { (None, None) }
            };
            let (content, uri) = if let Some(t) = text { (t, uri.unwrap()) } else {
                let t = match std::fs::read_to_string(p) { Ok(s) => s, Err(_) => continue };
                (t, lsp::Url::from_file_path(p).unwrap())
            };
            let mut parser = premise_core::Parser::new();
            let (_, _, ast) = parser.parse_str(&content);
            if let Some(ast) = ast {
                let defs = ast_utils::collect_entity_definitions(&ast, &content);
                if defs.iter().any(|(n, _)| n == target) {
                    for (_n, r) in ast_utils::collect_entity_references(&ast, &content).into_iter().filter(|(n, _)| n == target) {
                        out.push(lsp::Location { uri: uri.clone(), range: to_lsp_range(r) });
                    }
                }
            }
        }
    }
    Ok(out)
}

pub async fn list_entity_names_in_story_root(state: &Arc<RwLock<WorldState>>, current_uri: &lsp::Url) -> Result<Vec<String>> {
    let path = match url_to_path(current_uri) { Some(p) => p, None => return Ok(Vec::new()) };
    let start_dir = path.parent().unwrap_or(Path::new("."));
    let story_root = find_story_root(start_dir).unwrap_or_else(|| start_dir.to_path_buf());
    {
        let st = state.read().await;
        let names = st.index.list_entity_names_in_root(&story_root);
        if !names.is_empty() { return Ok(names); }
    }
    let mut set: std::collections::BTreeSet<String> = std::collections::BTreeSet::new();
    for entry in WalkDir::new(&story_root).into_iter().filter_map(|e| e.ok()) {
        let p = entry.path();
        if p.is_file() && p.extension().and_then(|e| e.to_str()) == Some("prem") {
            let (text, _uri) = {
                let st = state.read().await;
                let uri = lsp::Url::from_file_path(p).ok();
                if let Some(uri) = uri.clone() {
                    if let Some(doc) = st.docs.get(&uri) { (Some(doc.text.clone()), Some(uri)) } else { (None, Some(uri)) }
                } else { (None, None) }
            };
            let content = if let Some(t) = text { t } else {
                match std::fs::read_to_string(p) { Ok(s) => s, Err(_) => continue }
            };
            let mut parser = premise_core::Parser::new();
            let (_, _, ast) = parser.parse_str(&content);
            if let Some(ast) = ast {
                for (n, _r) in ast_utils::collect_entity_definitions(&ast, &content) {
                    set.insert(n);
                }
            }
        }
    }
    Ok(set.into_iter().collect())
}


