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


#[allow(deprecated)]
#[derive(Clone, Copy, Debug, Default)]
pub struct OrdinalOffsets {
    pub acts: usize,
    pub scenes: usize,
    pub cels: usize,
}

#[allow(deprecated)]
pub fn story_to_document_symbols(ir: &premise_core::ir::IrAnalysis, uri: &lsp::Url, offsets: OrdinalOffsets) -> Vec<lsp::DocumentSymbol> {
    let mut out: Vec<lsp::DocumentSymbol> = Vec::new();

    fn name_or<'a>(s: &'a str, fallback: &'a str) -> String {
        let t = s.trim();
        if t.is_empty() { fallback.to_string() } else { t.to_string() }
    }

    // Best-effort file name for fallback context
    let file_name: String = uri
        .to_file_path()
        .ok()
        .and_then(|p| p.file_name().map(|os| os.to_string_lossy().to_string()))
        .unwrap_or_else(|| uri.to_string());

    for (i, a) in ir.ir.story.acts.iter().enumerate() {
        let has_title = !a.title.trim().is_empty();
        let title = if has_title { a.title.clone() } else { format!("Act {} — {}", offsets.acts + i + 1, file_name) };
        out.push(lsp::DocumentSymbol {
            name: name_or(&title, "Act"),
            detail: a.proportion.clone(),
            kind: lsp::SymbolKind::NAMESPACE,
            tags: None,
            deprecated: None,
            range: super::diagnostics::to_lsp_range(a.range),
            selection_range: super::diagnostics::to_lsp_range(a.range),
            children: None,
        });
    }
    for (i, s) in ir.ir.story.scenes.iter().enumerate() {
        let has_title = !s.title.trim().is_empty();
        let title = if has_title { s.title.clone() } else { format!("Scene {} — {}", offsets.scenes + i + 1, file_name) };
        out.push(lsp::DocumentSymbol {
            name: name_or(&title, "Scene"),
            detail: s.proportion.clone(),
            kind: lsp::SymbolKind::NAMESPACE,
            tags: None,
            deprecated: None,
            range: super::diagnostics::to_lsp_range(s.range),
            selection_range: super::diagnostics::to_lsp_range(s.range),
            children: None,
        });
    }
    for (i, c) in ir.ir.story.cels.iter().enumerate() {
        let has_title = !c.title.trim().is_empty();
        let title = if has_title { c.title.clone() } else { format!("Cel {} — {}", offsets.cels + i + 1, file_name) };
        out.push(lsp::DocumentSymbol {
            name: name_or(&title, "Cel"),
            detail: c.time.clone().or(c.location_type.clone()).or(c.proportion.clone()),
            kind: lsp::SymbolKind::STRING,
            tags: None,
            deprecated: None,
            range: super::diagnostics::to_lsp_range(c.range),
            selection_range: super::diagnostics::to_lsp_range(c.range),
            children: None,
        });
    }

    out
}

