use serde::{Deserialize, Serialize};
use schemars::JsonSchema;
use std::collections::{HashMap, HashSet};
use tree_sitter::Node;

use crate::ast::Range;

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(rename_all = "snake_case")]
pub enum IssueCode {
    DuplicateEntity,
    UnknownEntityReference,
    ImportCycle,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Issue {
    pub code: IssueCode,
    pub message: String,
    pub range: Range,
    pub related_text: Option<String>,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct ValidationReport {
    pub issues: Vec<Issue>,
}

pub fn validate(root: &Node, source: &str) -> ValidationReport {
    let mut issues: Vec<Issue> = Vec::new();

    let entity_names = collect_entity_names(root, source);
    add_duplicate_entity_issues(&entity_names, &mut issues);

    collect_unknown_reference_issues(root, source, &entity_names, &mut issues);

    // Basic import cycle detection using adjacency list
    detect_import_cycles(root, source, &mut issues);

    ValidationReport { issues }
}

fn collect_entity_names(root: &Node, source: &str) -> Vec<(String, Range)> {
    let mut results: Vec<(String, Range)> = Vec::new();
    walk(root, &mut |node| {
        if node.kind() == "entity_construct" {
            if let Some(name_node) = node.child_by_field_name("entity_name") {
                let name = slice_text(&name_node, source).trim().to_string();
                results.push((name, Range::from_node(&name_node)));
            }
        }
    });
    results
}

fn add_duplicate_entity_issues(names: &[(String, Range)], issues: &mut Vec<Issue>) {
    let mut first_seen: HashMap<&str, &Range> = HashMap::new();
    let mut seen: HashSet<&str> = HashSet::new();
    for (name, range) in names {
        let k: &str = name.as_str();
        if !seen.insert(k) {
            // duplicate
            let message = format!("Duplicate entity name: {}", name);
            issues.push(Issue { code: IssueCode::DuplicateEntity, message, range: *range, related_text: Some(name.clone()) });
        } else {
            first_seen.entry(k).or_insert(range);
        }
    }
}

fn collect_unknown_reference_issues(root: &Node, source: &str, names: &[(String, Range)], issues: &mut Vec<Issue>) {
    let mut name_set: HashSet<&str> = HashSet::new();
    for (n, _) in names.iter() { name_set.insert(n.as_str()); }

    walk(root, &mut |node| {
        if node.kind() == "entity_reference" {
            if let Some(entity_tok) = node.child_by_field_name("entity") {
                let ref_name = slice_text(&entity_tok, source).trim().to_string();
                if !ref_name.is_empty() && !name_set.contains(ref_name.as_str()) {
                    let message = format!("Unknown entity reference: {}", ref_name);
                    issues.push(Issue { code: IssueCode::UnknownEntityReference, message, range: Range::from_node(&entity_tok), related_text: Some(ref_name) });
                }
            }
        }
    });
}

fn detect_import_cycles(root: &Node, source: &str, issues: &mut Vec<Issue>) {
    // Build adjacency from simple "import path" statements; treat each file as a node by string
    // Here, since we only have a single source string and no loader context, we conservatively
    // detect immediate self-imports and repeated import chains in the same file like `a -> a`.
    // A full resolver-backed graph would live in an upper layer.
    let mut imports: Vec<(String, Range)> = Vec::new();
    walk(root, &mut |node| {
        if node.kind() == "import_statement" {
            if let Some(path_node) = node.child_by_field_name("path") {
                let p = slice_text(&path_node, source).trim().to_string();
                imports.push((p, Range::from_node(&path_node)));
            }
        }
    });

    // Detect trivial cycles: same path imported multiple times with an explicit self reference marker
    // Example heuristic: if the same path string appears with a trailing `#self` or it's exactly the current file indicator `.`
    for (p, r) in imports.iter() {
        let cleaned = p.trim_matches(['"', '\'']);
        if cleaned == "." || cleaned.ends_with("#self") {
            let message = format!("Import cycle detected involving {}", cleaned);
            issues.push(Issue { code: IssueCode::ImportCycle, message, range: *r, related_text: Some(cleaned.to_string()) });
        }
    }
}

fn walk<F: FnMut(&Node)>(root: &Node, f: &mut F) {
    f(root);
    let mut cursor = root.walk();
    for child in root.children(&mut cursor) {
        walk(&child, f);
    }
}

fn slice_text(node: &Node, source: &str) -> String {
    let start = node.start_byte();
    let end = node.end_byte();
    source.get(start..end).unwrap_or("").to_string()
}


