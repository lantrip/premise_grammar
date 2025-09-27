use tower_lsp::lsp_types as lsp;

#[allow(deprecated)]
pub fn to_document_symbols(analysis: &premise_core::symbols::Analysis) -> Vec<lsp::DocumentSymbol> {
    let mut out: Vec<lsp::DocumentSymbol> = Vec::new();

    for sym in &analysis.symbols.entities {
        let name = sym.name.clone().unwrap_or_else(|| "entity".into());
        out.push(lsp::DocumentSymbol {
            name,
            detail: None,
            kind: lsp::SymbolKind::CLASS,
            tags: None,
            deprecated: None,
            range: super::diagnostics::to_lsp_range(sym.range),
            selection_range: super::diagnostics::to_lsp_range(sym.range),
            children: None,
        });
    }
    for imp in &analysis.symbols.imports {
        out.push(lsp::DocumentSymbol {
            name: imp.name.clone().unwrap_or_else(|| "import".into()),
            detail: None,
            kind: lsp::SymbolKind::NAMESPACE,
            tags: None,
            deprecated: None,
            range: super::diagnostics::to_lsp_range(imp.range),
            selection_range: super::diagnostics::to_lsp_range(imp.range),
            children: None,
        });
    }
    for m in &analysis.symbols.metadata {
        out.push(lsp::DocumentSymbol {
            name: "metadata".into(),
            detail: None,
            kind: lsp::SymbolKind::PROPERTY,
            tags: None,
            deprecated: None,
            range: super::diagnostics::to_lsp_range(m.range),
            selection_range: super::diagnostics::to_lsp_range(m.range),
            children: None,
        });
    }

    out
}


