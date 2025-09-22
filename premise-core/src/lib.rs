pub mod diagnostics;
pub mod cst;
pub mod ast;
pub mod symbols;
pub mod imports;
pub mod validation;
pub mod ir;
pub mod planning;
pub mod api;

use tree_sitter::{Language, Parser as TsParser};
use std::path::Path;
use std::fs;

extern "C" { fn tree_sitter_premise() -> Language; }

pub struct Parser {
    internal: TsParser,
}

impl Parser {
    pub fn new() -> Self {
        let mut parser = TsParser::new();
        unsafe { parser.set_language(&tree_sitter_premise()).expect("failed to set Premise language"); }
        Self { internal: parser }
    }

    pub fn parse_str(&mut self, input: &str) -> (cst::Cst, Vec<diagnostics::Diagnostic>, Option<ast::AstNode>) {
        let tree = self.internal.parse(input, None);
        match tree {
            Some(tree) => {
                let root = tree.root_node();
                let sexp = root.to_sexp();
                let range = ast::Range::from_node(&root);
                let mut diags = Vec::new();
                let ast = ast::AstNode::build(&root, None, &mut diags);
                (cst::Cst { root_sexpr: sexp, range }, diags, Some(ast))
            }
            None => {
                (cst::Cst { root_sexpr: String::new(), range: ast::Range::default() }, vec![diagnostics::Diagnostic::error("Parse failed")], None)
            }
        }
    }

    pub fn analyze_symbols(&mut self, input: &str) -> crate::symbols::Analysis {
        let tree = self.internal.parse(input, None);
        match tree {
            Some(tree) => {
                let root = tree.root_node();
                crate::symbols::analyze_tree(&root, input)
            }
            None => crate::symbols::Analysis { symbols: crate::symbols::SymbolTable::default(), diagnostics: vec![diagnostics::Diagnostic::error("Parse failed")], },
        }
    }

    pub fn analyze_imports(&mut self, input: &str) -> crate::imports::ImportAnalysis {
        let tree = self.internal.parse(input, None);
        match tree {
            Some(tree) => {
                let root = tree.root_node();
                crate::imports::analyze_imports(&root, input)
            }
            None => crate::imports::ImportAnalysis { imports: crate::imports::ImportList::default(), diagnostics: vec![diagnostics::Diagnostic::error("Parse failed")] },
        }
    }

    pub fn resolve_imports_with_base<P: AsRef<Path>>(&mut self, input: &str, base_dir: P) -> crate::imports::ImportResolution {
        let analysis = self.analyze_imports(input);
        crate::imports::resolve_imports_relative(base_dir.as_ref(), &analysis.imports)
    }

    pub fn resolve_imports_from_path<P: AsRef<Path>>(&mut self, path: P) -> crate::imports::ImportResolution {
        let content = match fs::read_to_string(&path) {
            Ok(c) => c,
            Err(err) => {
                return crate::imports::ImportResolution { resolved: Vec::new(), diagnostics: vec![diagnostics::Diagnostic::error(format!("Failed to read file: {}", err))] };
            }
        };
        let base_dir = path.as_ref().parent().unwrap_or_else(|| Path::new("."));
        self.resolve_imports_with_base(&content, base_dir)
    }

    pub fn parse_path<P: AsRef<Path>>(&mut self, path: P) -> (cst::Cst, Vec<diagnostics::Diagnostic>, Option<ast::AstNode>) {
        let content = match fs::read_to_string(&path) {
            Ok(c) => c,
            Err(err) => {
                return (
                    cst::Cst { root_sexpr: String::new(), range: ast::Range::default() },
                    vec![diagnostics::Diagnostic::error(format!("Failed to read file: {}", err))],
                    None,
                );
            }
        };
        self.parse_str(&content)
    }

    pub fn validate(&mut self, input: &str) -> crate::validation::ValidationReport {
        let tree = self.internal.parse(input, None);
        match tree {
            Some(tree) => crate::validation::validate(&tree.root_node(), input),
            None => crate::validation::ValidationReport { issues: vec![crate::validation::Issue { code: crate::validation::IssueCode::UnknownEntityReference, message: "Parse failed".into(), range: ast::Range::default(), related_text: None }] },
        }
    }

    pub fn analyze_ir(&mut self, input: &str) -> crate::ir::IrAnalysis {
        let tree = self.internal.parse(input, None);
        match tree {
            Some(tree) => crate::ir::build_ir(&tree.root_node(), input),
            None => crate::ir::IrAnalysis::default(),
        }
    }

    pub fn plan_adapters(&mut self, input: &str) -> crate::planning::PlanAnalysis {
        let ir = self.analyze_ir(input);
        crate::planning::plan_from_ir(&ir.ir)
    }
}


