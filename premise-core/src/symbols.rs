use serde::{Deserialize, Serialize};
use schemars::JsonSchema;
use tree_sitter::Node;

use crate::ast::Range;

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub enum SymbolKind {
    EntityConstruct,
    EntityBlock,
    Import,
    AdapterPath,
    AdapterName,
    Metadata,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Symbol {
    pub kind: SymbolKind,
    pub name: Option<String>,
    pub range: Range,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct SymbolTable {
    pub entities: Vec<Symbol>,
    pub adapters: Vec<Symbol>,
    pub imports: Vec<Symbol>,
    pub metadata: Vec<Symbol>,
}

impl SymbolTable {
    pub fn collect_from_root(root: &Node, source: &str) -> (Self, Vec<crate::diagnostics::Diagnostic>) {
        let mut table = SymbolTable::default();
        let mut diagnostics = Vec::new();
        Self::walk(root, source, &mut table, &mut diagnostics);
        (table, diagnostics)
    }

    fn walk(node: &Node, source: &str, table: &mut SymbolTable, diagnostics: &mut Vec<crate::diagnostics::Diagnostic>) {
        let kind = node.kind();
        match kind {
            "entity_construct" => {
                let range = Range::from_node(node);
                let name = node
                    .child_by_field_name("entity_name")
                    .map(|n| Self::slice_text(&n, source));
                table.entities.push(Symbol { kind: SymbolKind::EntityConstruct, name, range });
            }
            "entity_block" => {
                table.entities.push(Symbol { kind: SymbolKind::EntityBlock, name: None, range: Range::from_node(node) });
            }
            "import_statement" => {
                let range = Range::from_node(node);
                let path_text = node
                    .child_by_field_name("path")
                    .map(|n| Self::slice_text(&n, source));
                table.imports.push(Symbol { kind: SymbolKind::Import, name: path_text, range });
            }
            "adapter_statement" => {
                let range = Range::from_node(node);
                let name = node
                    .child_by_field_name("adapter_path")
                    .or_else(|| node.child_by_field_name("adapter_name"))
                    .map(|n| Self::slice_text(&n, source));
                table.adapters.push(Symbol { kind: SymbolKind::AdapterPath, name, range });
            }
            "metadata_line" => {
                let range = Range::from_node(node);
                table.metadata.push(Symbol { kind: SymbolKind::Metadata, name: None, range });
            }
            _ => {}
        }

        let mut cursor = node.walk();
        for child in node.children(&mut cursor) {
            Self::walk(&child, source, table, diagnostics);
        }
    }

    fn slice_text(node: &Node, source: &str) -> String {
        let start = node.start_byte();
        let end = node.end_byte();
        source.get(start..end).unwrap_or("").to_string()
    }
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Analysis {
    pub symbols: SymbolTable,
    pub diagnostics: Vec<crate::diagnostics::Diagnostic>,
}

pub fn analyze_tree(root: &Node, source: &str) -> Analysis {
    let (symbols, diagnostics) = SymbolTable::collect_from_root(root, source);
    Analysis { symbols, diagnostics }
}


