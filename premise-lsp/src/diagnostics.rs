use tower_lsp::lsp_types as lsp;

pub fn to_lsp_range(range: premise_core::ast::Range) -> lsp::Range {
    lsp::Range {
        start: lsp::Position { line: range.start.row as u32, character: range.start.column as u32 },
        end: lsp::Position { line: range.end.row as u32, character: range.end.column as u32 },
    }
}

pub fn to_lsp_diagnostics(report: &premise_core::validation::ValidationReport) -> Vec<lsp::Diagnostic> {
    report
        .issues
        .iter()
        .map(|issue| lsp::Diagnostic {
            range: to_lsp_range(issue.range),
            severity: Some(lsp::DiagnosticSeverity::ERROR),
            code: None,
            code_description: None,
            source: Some("premise".to_string()),
            message: issue.message.clone(),
            related_information: None,
            tags: None,
            data: None,
        })
        .collect()
}


