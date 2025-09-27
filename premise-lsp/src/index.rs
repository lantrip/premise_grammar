use std::collections::{BTreeMap, HashMap};
use std::path::{Path, PathBuf};
use std::time::UNIX_EPOCH;

use tower_lsp::lsp_types as lsp;
use walkdir::WalkDir;

use crate::{ast_utils, diagnostics::to_lsp_range};

#[derive(Clone, Debug)]
struct IndexedFile {
    #[allow(dead_code)]
    path: PathBuf,
    #[allow(dead_code)]
    uri: lsp::Url,
    story_root: PathBuf,
    #[allow(dead_code)]
    modified_millis: Option<u128>,
    defs: Vec<(String, lsp::Location)>,
    refs: Vec<(String, lsp::Location)>,
}

#[derive(Default, Debug)]
pub struct EntityIndex {
    files: HashMap<PathBuf, IndexedFile>,
    defs_by_root: HashMap<PathBuf, BTreeMap<String, Vec<lsp::Location>>>,
    refs_by_root: HashMap<PathBuf, BTreeMap<String, Vec<lsp::Location>>>,
    roots: Vec<PathBuf>,
}

impl EntityIndex {
    #[allow(dead_code)]
    pub fn new() -> Self { Self::default() }

    pub fn set_roots(&mut self, roots: Vec<PathBuf>) { self.roots = roots; }

    pub fn list_roots(&self) -> Vec<PathBuf> { self.roots.clone() }

    pub fn index_text(&mut self, path: PathBuf, uri: lsp::Url, text: &str) {
        let story_root = self.story_root_for_path(&path);
        let (defs, refs) = parse_defs_refs(&uri, text);
        let file = IndexedFile {
            path: path.clone(),
            uri,
            story_root: story_root.clone(),
            modified_millis: None,
            defs,
            refs,
        };
        self.files.insert(path, file);
        self.rebuild_root(&story_root);
    }

    pub fn index_path_from_disk(&mut self, path: &Path) {
        if !path.is_file() { return; }
        if path.extension().and_then(|e| e.to_str()) != Some("prem") { return; }
        let Ok(text) = std::fs::read_to_string(path) else { return; };
        let uri = match lsp::Url::from_file_path(path) { Ok(u) => u, Err(_) => return };
        let modified_millis = file_mtime_millis(path);
        let story_root = self.story_root_for_path(path);
        let (defs, refs) = parse_defs_refs(&uri, &text);
        let file = IndexedFile {
            path: path.to_path_buf(),
            uri,
            story_root: story_root.clone(),
            modified_millis,
            defs,
            refs,
        };
        self.files.insert(path.to_path_buf(), file);
        self.rebuild_root(&story_root);
    }

    pub fn remove_file(&mut self, path: &Path) {
        if let Some(file) = self.files.remove(path) {
            self.rebuild_root(&file.story_root);
        }
    }

    pub fn scan_root_from_disk(&mut self, root: &Path) {
        for entry in WalkDir::new(root).into_iter().filter_map(|e| e.ok()) {
            let p = entry.path();
            if p.is_file() && p.extension().and_then(|e| e.to_str()) == Some("prem") {
                self.index_path_from_disk(p);
            }
        }
    }

    pub fn list_entity_names_in_root(&self, story_root: &Path) -> Vec<String> {
        if let Some(map) = self.defs_by_root.get(story_root) {
            return map.keys().cloned().collect();
        }
        Vec::new()
    }

    pub fn get_defs_in_root(&self, story_root: &Path, name: &str) -> Vec<lsp::Location> {
        self.defs_by_root
            .get(story_root)
            .and_then(|m| m.get(name))
            .cloned()
            .unwrap_or_default()
    }

    pub fn get_refs_in_root(&self, story_root: &Path, name: &str) -> Vec<lsp::Location> {
        // Only return references if there is at least one definition in this root
        let has_defs = self
            .defs_by_root
            .get(story_root)
            .and_then(|m| m.get(name))
            .map(|v| !v.is_empty())
            .unwrap_or(false);
        if !has_defs { return Vec::new(); }
        self.refs_by_root
            .get(story_root)
            .and_then(|m| m.get(name))
            .cloned()
            .unwrap_or_default()
    }

    fn rebuild_root(&mut self, story_root: &Path) {
        let mut defs: BTreeMap<String, Vec<lsp::Location>> = BTreeMap::new();
        let mut refs: BTreeMap<String, Vec<lsp::Location>> = BTreeMap::new();
        for file in self.files.values() {
            if file.story_root == story_root {
                for (n, loc) in &file.defs {
                    defs.entry(n.clone()).or_default().push(loc.clone());
                }
                for (n, loc) in &file.refs {
                    refs.entry(n.clone()).or_default().push(loc.clone());
                }
            }
        }
        self.defs_by_root.insert(story_root.to_path_buf(), defs);
        self.refs_by_root.insert(story_root.to_path_buf(), refs);
    }

    fn story_root_for_path(&self, path: &Path) -> PathBuf {
        let start_dir = path.parent().unwrap_or(Path::new("."));
        crate::scope::find_story_root(start_dir).unwrap_or_else(|| start_dir.to_path_buf())
    }
}

fn parse_defs_refs(uri: &lsp::Url, text: &str) -> (Vec<(String, lsp::Location)>, Vec<(String, lsp::Location)>) {
    let mut parser = premise_core::Parser::new();
    let (_, _, ast_opt) = parser.parse_str(text);
    if let Some(ast) = ast_opt {
        let mut defs_out: Vec<(String, lsp::Location)> = Vec::new();
        for (name, range) in ast_utils::collect_entity_definitions(&ast, text) {
            defs_out.push((name, lsp::Location { uri: uri.clone(), range: to_lsp_range(range) }));
        }
        let mut refs_out: Vec<(String, lsp::Location)> = Vec::new();
        for (name, range) in ast_utils::collect_entity_references(&ast, text) {
            refs_out.push((name, lsp::Location { uri: uri.clone(), range: to_lsp_range(range) }));
        }
        (defs_out, refs_out)
    } else {
        (Vec::new(), Vec::new())
    }
}

fn file_mtime_millis(path: &Path) -> Option<u128> {
    std::fs::metadata(path)
        .and_then(|m| m.modified())
        .ok()
        .and_then(|st| st.duration_since(UNIX_EPOCH).ok())
        .map(|d| d.as_millis())
}


