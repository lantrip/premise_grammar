use schemars::JsonSchema;
use serde::{Deserialize, Serialize};
use tree_sitter::Node;

use crate::ast::Range;

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Act {
    pub title: String,
    pub proportion: Option<String>,
    pub range: Range,
    /// True when this header is `~`-marked or sits inside an open
    /// `~`-graveyard region. See `crate::graveyard` for scope rules.
    #[serde(default, skip_serializing_if = "std::ops::Not::not")]
    pub graveyard: bool,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Scene {
    pub title: String,
    pub proportion: Option<String>,
    pub range: Range,
    #[serde(default, skip_serializing_if = "std::ops::Not::not")]
    pub graveyard: bool,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Cel {
    pub title: String,
    pub location_type: Option<String>,
    pub time: Option<String>,
    pub proportion: Option<String>,
    pub range: Range,
    #[serde(default, skip_serializing_if = "std::ops::Not::not")]
    pub graveyard: bool,
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

    // Cursor mirroring the frontend's `openLevel` (see premHierarchy.ts):
    // a `~`-header at level L opens a region that closes at the next header
    // with level <= L. Nested levels: act=0, scene=1, cel=2.
    let mut open_level: Option<u8> = None;

    walk(root, &mut |node| {
        let kind = node.kind();
        let level: Option<u8> = match kind {
            "act_header" => Some(0),
            "scene_header" => Some(1),
            "cel_header" => Some(2),
            _ => None,
        };

        if let Some(lvl) = level {
            // Sibling-or-higher closes the open region before classifying.
            if let Some(open) = open_level {
                if lvl <= open {
                    open_level = None;
                }
            }
        }

        let has_marker = node.child_by_field_name("graveyard").is_some();
        let is_graveyard = level.is_some() && (has_marker || open_level.is_some());

        if let (Some(lvl), true) = (level, has_marker) {
            // Lower (broader) graveyard headers extend the open region.
            open_level = match open_level {
                None => Some(lvl),
                Some(existing) if lvl < existing => Some(lvl),
                Some(existing) => Some(existing),
            };
        }

        match kind {
            "act_header" => {
                let title = node
                    .child_by_field_name("title")
                    .map(|n| slice_text(&n, source).trim().to_string())
                    .unwrap_or_default();
                let proportion = node
                    .child_by_field_name("proportion")
                    .map(|n| slice_text(&n, source).trim().to_string());
                story.acts.push(Act {
                    title,
                    proportion,
                    range: Range::from_node(node),
                    graveyard: is_graveyard,
                });
            }
            "scene_header" => {
                let title = node
                    .child_by_field_name("title")
                    .map(|n| slice_text(&n, source).trim().to_string())
                    .unwrap_or_default();
                let proportion = node
                    .child_by_field_name("proportion")
                    .map(|n| slice_text(&n, source).trim().to_string());
                story.scenes.push(Scene {
                    title,
                    proportion,
                    range: Range::from_node(node),
                    graveyard: is_graveyard,
                });
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
                story.cels.push(Cel {
                    title,
                    location_type,
                    time,
                    proportion,
                    range: Range::from_node(node),
                    graveyard: is_graveyard,
                });
            }
            "adapter_statement" => {
                let id_node = node
                    .child_by_field_name("adapter_path")
                    .or_else(|| node.child_by_field_name("adapter_name"));
                if let Some(id_node) = id_node {
                    let name_or_path = slice_text(&id_node, source).trim().to_string();
                    adapters.push(AdapterRef {
                        name_or_path,
                        range: Range::from_node(&id_node),
                    });
                }
            }
            _ => {}
        }
    });

    IrAnalysis {
        ir: Ir { story, adapters },
        diagnostics,
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
