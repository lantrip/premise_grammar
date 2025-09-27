use premise_core::ast::{AstNode, Range};
use serde::Serialize;

pub fn contains_position(range: &Range, line: u32, character: u32) -> bool {
    let (sl, sc) = (range.start.row as u32, range.start.column as u32);
    let (el, ec) = (range.end.row as u32, range.end.column as u32);
    if line < sl || line > el { return false; }
    if line == sl && character < sc { return false; }
    // Use exclusive end boundary for the column on the end line
    if line == el && character >= ec { return false; }
    true
}

pub fn walk<'a, F: FnMut(&'a AstNode)>(node: &'a AstNode, f: &mut F) {
    f(node);
    for child in &node.children {
        walk(child, f);
    }
}

pub fn find_deepest_at<'a>(node: &'a AstNode, line: u32, character: u32) -> Option<&'a AstNode> {
    if !contains_position(&node.range, line, character) {
        return None;
    }
    for child in &node.children {
        if let Some(found) = find_deepest_at(child, line, character) {
            return Some(found);
        }
    }
    Some(node)
}

pub fn slice_text(text: &str, range: &Range) -> String {
    let (s, e) = (range.start_byte, range.end_byte);
    text.get(s..e).unwrap_or("").to_string()
}

pub fn normalize_name(s: &str) -> String {
    s.trim().replace("\n", " ").split_whitespace().collect::<Vec<_>>().join(" ")
}

pub fn extract_child_field<'a>(node: &'a AstNode, field: &str) -> Option<&'a AstNode> {
    node.children.iter().find(|c| matches!(c.field.as_deref(), Some(f) if f == field))
}

pub fn reference_name_at(ast: &AstNode, line: u32, character: u32, text: &str) -> Option<String> {
    let target = find_deepest_at(ast, line, character)?;
    // climb up if we're inside the entity field
    let ref_node = if target.kind == "entity_reference" || target.kind == "dialogue_speaker" {
        target
    } else {
        // find nearest ancestor of those kinds by simple upward scan using a stack we build along the way
        // Since AstNode lacks parent pointers, re-find path from root
        find_ancestor_kind(ast, line, character, &["entity_reference", "dialogue_speaker"])?
    };

    // Prefer explicit child field if grammar provides it; else trim braces from the node text
    let raw = if let Some(entity_child) = extract_child_field(ref_node, if ref_node.kind == "dialogue_speaker" { "speaker" } else { "entity" }) {
        slice_text(text, &entity_child.range)
    } else {
        let s = slice_text(text, &ref_node.range);
        let t = s.trim();
        let t = t.strip_prefix('{').unwrap_or(t);
        let t = t.strip_suffix('}').unwrap_or(t);
        t.trim().to_string()
    };
    Some(normalize_name(&raw))
}

pub fn definition_name_at(ast: &AstNode, line: u32, character: u32, text: &str) -> Option<String> {
    let target = find_deepest_at(ast, line, character)?;
    if target.kind == "entity_construct" || target.kind == "entity_line" {
        // ok
    } else {
        let kinds = ["entity_construct", "entity_line"];
        if let Some(node) = find_ancestor_kind(ast, line, character, &kinds) {
            return extract_definition_name(node, text);
        } else {
            return None;
        }
    }
    extract_definition_name(target, text)
}

fn extract_definition_name(node: &AstNode, text: &str) -> Option<String> {
    if node.kind == "entity_construct" {
        if let Some(name_node) = extract_child_field(node, "name") {
            return Some(normalize_name(&slice_text(text, &name_node.range)));
        }
    }
    if node.kind == "entity_line" {
        if let Some(name_node) = extract_child_field(node, "entity_name") {
            return Some(normalize_name(&slice_text(text, &name_node.range)));
        }
    }
    None
}

pub fn name_at(ast: &AstNode, line: u32, character: u32, text: &str) -> Option<String> {
    reference_name_at(ast, line, character, text)
        .or_else(|| definition_name_at(ast, line, character, text))
}

fn find_ancestor_kind<'a>(node: &'a AstNode, line: u32, character: u32, kinds: &[&str]) -> Option<&'a AstNode> {
    fn helper<'a>(node: &'a AstNode, line: u32, character: u32, kinds: &[&str], stack: &mut Vec<&'a AstNode>, out: &mut Option<&'a AstNode>) {
        if !contains_position(&node.range, line, character) { return; }
        stack.push(node);
        for child in &node.children {
            helper(child, line, character, kinds, stack, out);
        }
        if out.is_none() && kinds.contains(&node.kind.as_str()) {
            *out = Some(node);
        }
        stack.pop();
    }
    let mut stack = Vec::new();
    let mut out = None;
    helper(node, line, character, kinds, &mut stack, &mut out);
    out
}

pub fn collect_entity_definitions(ast: &AstNode, text: &str) -> Vec<(String, Range)> {
    let mut defs = Vec::new();
    walk(ast, &mut |n| {
        if n.kind == "entity_construct" {
            if let Some(name_node) = extract_child_field(n, "name") {
                let name = normalize_name(&slice_text(text, &name_node.range));
                defs.push((name, name_node.range));
            }
        }
        if n.kind == "entity_line" {
            if let Some(name_node) = extract_child_field(n, "entity_name") {
                let name = normalize_name(&slice_text(text, &name_node.range));
                defs.push((name, name_node.range));
            }
        }
    });
    defs
}

pub fn collect_entity_references(ast: &AstNode, text: &str) -> Vec<(String, Range)> {
    let mut refs = Vec::new();
    walk(ast, &mut |n| {
        if n.kind == "entity_reference" {
            if let Some(ent_node) = extract_child_field(n, "entity") {
                let name = normalize_name(&slice_text(text, &ent_node.range));
                refs.push((name, ent_node.range));
            } else {
                // Fallback: trim braces from the node text
                let s = slice_text(text, &n.range);
                if let Some(stripped) = s.strip_prefix('{').and_then(|t| t.strip_suffix('}')) {
                    let name = normalize_name(stripped);
                    if !name.is_empty() { refs.push((name, n.range)); }
                } else {
                    let name = normalize_name(&s);
                    if !name.is_empty() { refs.push((name, n.range)); }
                }
            }
        }
        if n.kind == "dialogue_speaker" {
            if let Some(speaker_node) = extract_child_field(n, "speaker") {
                let name = normalize_name(&slice_text(text, &speaker_node.range));
                refs.push((name, speaker_node.range));
            } else {
                // Fallback: speaker content is within braces at the start of the node
                let s = slice_text(text, &n.range);
                let t = s.trim();
                let t = t.strip_prefix('{').unwrap_or(t);
                let t = t.strip_suffix('}').unwrap_or(t);
                let name = normalize_name(t);
                if !name.is_empty() { refs.push((name, n.range)); }
            }
        }
    });
    refs
}

#[derive(Default, Clone, Debug, Serialize)]
pub struct StoryContext {
    pub act: Option<String>,
    pub scene: Option<String>,
    pub cel: Option<String>,
    pub beat: Option<String>,
}

pub fn story_context_at(ast: &AstNode, line: u32, _character: u32, text: &str) -> StoryContext {
    // Walk nodes in document order, tracking the latest section headers before the given line.
    let mut ctx = StoryContext::default();
    walk(ast, &mut |n| {
        if (n.range.start.row as u32) > line { return; }
        match n.kind.as_str() {
            "act_header" => {
                if let Some(t) = extract_child_field(n, "title") {
                    ctx.act = Some(normalize_name(&slice_text(text, &t.range)));
                }
            }
            "scene_header" => {
                if let Some(t) = extract_child_field(n, "title") {
                    ctx.scene = Some(normalize_name(&slice_text(text, &t.range)));
                }
            }
            "cel_header" => {
                if let Some(t) = extract_child_field(n, "title") {
                    ctx.cel = Some(normalize_name(&slice_text(text, &t.range)));
                }
            }
            "content_type_beat" => {
                // Use the raw line content after the leading '///'
                let raw = slice_text(text, &n.range);
                let beat = raw.trim_start_matches('/').trim().to_string();
                if !beat.is_empty() {
                    ctx.beat = Some(beat);
                }
            }
            _ => {}
        }
    });
    ctx
}


