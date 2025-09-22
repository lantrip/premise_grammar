use serde::{Deserialize, Serialize};
use schemars::JsonSchema;
use tree_sitter::Node;
use std::path::{Path, PathBuf};
use std::fs;

use crate::ast::Range;

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Import {
    pub path: String,
    pub alias: Option<String>,
    pub selector: Option<String>,
    pub range: Range,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct ImportList {
    pub imports: Vec<Import>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct ImportAnalysis {
    pub imports: ImportList,
    pub diagnostics: Vec<crate::diagnostics::Diagnostic>,
}

pub fn analyze_imports(root: &Node, source: &str) -> ImportAnalysis {
    let mut imports = Vec::new();
    let mut diagnostics = Vec::new();

    walk(root, source, &mut imports, &mut diagnostics);

    ImportAnalysis { imports: ImportList { imports }, diagnostics }
}

fn walk(node: &Node, source: &str, imports: &mut Vec<Import>, diagnostics: &mut Vec<crate::diagnostics::Diagnostic>) {
    if node.kind() == "import_statement" {
        let range = Range::from_node(node);
        let path_text = node
            .child_by_field_name("path")
            .map(|n| slice_text(&n, source));
        let alias_text = node
            .child_by_field_name("alias")
            .map(|n| slice_text(&n, source));
        let selector_text = node
            .child_by_field_name("selector")
            .map(|n| slice_text(&n, source));

        if let Some(path) = path_text {
            imports.push(Import { path, alias: alias_text, selector: selector_text, range });
        } else {
            diagnostics.push(crate::diagnostics::Diagnostic::error("Import missing path"));
        }
    }

    let mut cursor = node.walk();
    for child in node.children(&mut cursor) {
        walk(&child, source, imports, diagnostics);
    }
}

fn slice_text(node: &Node, source: &str) -> String {
    let start = node.start_byte();
    let end = node.end_byte();
    source.get(start..end).unwrap_or("").to_string()
}


// --- Import Resolution (Phase 2) ---

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct ResolvedImport {
    pub import: Import,
    pub resolved_path: Option<String>,
    pub exists: bool,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct ImportResolution {
    pub resolved: Vec<ResolvedImport>,
    pub diagnostics: Vec<crate::diagnostics::Diagnostic>,
}

pub trait FileLoader {
    fn read_to_string(&self, path: &Path) -> Result<String, std::io::Error>;
    fn exists(&self, path: &Path) -> bool;
}

pub struct FsLoader;

impl FileLoader for FsLoader {
    fn read_to_string(&self, path: &Path) -> Result<String, std::io::Error> {
        fs::read_to_string(path)
    }
    fn exists(&self, path: &Path) -> bool {
        path.exists()
    }
}

fn clean_import_path(text: &str) -> String {
    text.trim().trim_matches(['"', '\'']).to_string()
}

pub fn resolve_imports_relative(base_dir: &Path, imports: &ImportList) -> ImportResolution {
    let mut resolved: Vec<ResolvedImport> = Vec::new();
    let mut diagnostics: Vec<crate::diagnostics::Diagnostic> = Vec::new();

    for imp in &imports.imports {
        let cleaned = clean_import_path(&imp.path);
        let candidate = PathBuf::from(&cleaned);
        let full = if candidate.is_absolute() { candidate } else { base_dir.join(&cleaned) };
        let exists = full.exists();
        let resolved_path = full.to_str().map(|s| s.to_string());
        if !exists {
            diagnostics.push(crate::diagnostics::Diagnostic::error(format!("Import not found: {}", cleaned)));
        }
        resolved.push(ResolvedImport {
            import: imp.clone(),
            resolved_path,
            exists,
        });
    }

    ImportResolution { resolved, diagnostics }
}


