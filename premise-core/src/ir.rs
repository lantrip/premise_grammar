use serde::{Deserialize, Serialize};
use schemars::JsonSchema;
use tree_sitter::Node;

use crate::ast::Range;

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Act {
    pub title: String,
    pub proportion: Option<String>,
    pub range: Range,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Scene {
    pub title: String,
    pub proportion: Option<String>,
    pub range: Range,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Cel {
    pub title: String,
    pub location_type: Option<String>,
    pub time: Option<String>,
    pub proportion: Option<String>,
    pub range: Range,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct StoryGraph {
    pub acts: Vec<Act>,
    pub scenes: Vec<Scene>,
    pub cels: Vec<Cel>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct AdapterRef {
    pub name_or_path: String,
    pub range: Range,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Ir {
    pub story: StoryGraph,
    pub adapters: Vec<AdapterRef>,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct IrAnalysis {
    pub ir: Ir,
    pub diagnostics: Vec<crate::diagnostics::Diagnostic>,
}

pub fn build_ir(root: &Node, source: &str) -> IrAnalysis {
    let mut story = StoryGraph::default();
    let mut adapters: Vec<AdapterRef> = Vec::new();
    let diagnostics = Vec::new();

    walk(root, &mut |node| {
        match node.kind() {
            "act_header" => {
                let title = node
                    .child_by_field_name("title")
                    .map(|n| slice_text(&n, source).trim().to_string())
                    .unwrap_or_default();
                let proportion = node
                    .child_by_field_name("proportion")
                    .map(|n| slice_text(&n, source).trim().to_string());
                story.acts.push(Act { title, proportion, range: Range::from_node(node) });
            }
            "scene_header" => {
                let title = node
                    .child_by_field_name("title")
                    .map(|n| slice_text(&n, source).trim().to_string())
                    .unwrap_or_default();
                let proportion = node
                    .child_by_field_name("proportion")
                    .map(|n| slice_text(&n, source).trim().to_string());
                story.scenes.push(Scene { title, proportion, range: Range::from_node(node) });
            }
            "cel_header" => {
                let title = node
                    .child_by_field_name("title")
                    .map(|n| slice_text(&n, source).trim().to_string())
                    .unwrap_or_default();
                let location_type = node
                    .child_by_field_name("location_type")
                    .map(|n| slice_text(&n, source).trim().to_string());
                let time = node
                    .child_by_field_name("time")
                    .map(|n| slice_text(&n, source).trim().to_string());
                let proportion = node
                    .child_by_field_name("proportion")
                    .map(|n| slice_text(&n, source).trim().to_string());
                story.cels.push(Cel { title, location_type, time, proportion, range: Range::from_node(node) });
            }
            "adapter_statement" => {
                let id_node = node
                    .child_by_field_name("adapter_path")
                    .or_else(|| node.child_by_field_name("adapter_name"));
                if let Some(id_node) = id_node {
                    let name_or_path = slice_text(&id_node, source).trim().to_string();
                    adapters.push(AdapterRef { name_or_path, range: Range::from_node(&id_node) });
                }
            }
            _ => {}
        }
    });

    IrAnalysis { ir: Ir { story, adapters }, diagnostics }
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


