use serde::{Deserialize, Serialize};
use schemars::JsonSchema;
use tree_sitter::Node;

#[derive(Debug, Clone, Copy, Default, Serialize, Deserialize, JsonSchema)]
pub struct Position {
    pub row: usize,
    pub column: usize,
}

#[derive(Debug, Clone, Copy, Default, Serialize, Deserialize, JsonSchema)]
pub struct Range {
    pub start: Position,
    pub end: Position,
    pub start_byte: usize,
    pub end_byte: usize,
}

impl Range {
    pub fn from_node(node: &Node) -> Self {
        let sp = node.start_position();
        let ep = node.end_position();
        Self {
            start: Position { row: sp.row, column: sp.column },
            end: Position { row: ep.row, column: ep.column },
            start_byte: node.start_byte(),
            end_byte: node.end_byte(),
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct AstNode {
    pub kind: String,
    pub field: Option<String>,
    pub range: Range,
    pub children: Vec<AstNode>,
}

impl AstNode {
    pub fn build(node: &Node, field: Option<String>, diagnostics: &mut Vec<crate::diagnostics::Diagnostic>) -> Self {
        if node.is_error() {
            diagnostics.push(crate::diagnostics::Diagnostic::error("ERROR node encountered"));
        }
        if node.is_missing() {
            diagnostics.push(crate::diagnostics::Diagnostic::error("Missing node encountered"));
        }

        let mut children: Vec<AstNode> = Vec::new();
        let child_count = node.child_count();
        for i in 0..child_count {
            if let Some(child) = node.child(i) {
                let field_name = node.field_name_for_child(i as u32).map(|s| s.to_string());
                children.push(AstNode::build(&child, field_name, diagnostics));
            }
        }
        AstNode {
            kind: node.kind().to_string(),
            field,
            range: Range::from_node(node),
            children,
        }
    }
}


