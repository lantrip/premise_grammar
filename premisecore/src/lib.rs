use pyo3::prelude::*;
use pyo3::types::PyModule;
use pyo3::Bound;

#[pyclass]
struct Parser {
    inner: premise_core::Parser,
}

#[pymethods]
impl Parser {
    #[new]
    fn new() -> Self { Self { inner: premise_core::Parser::new() } }

    /// Parse a source string and return JSON with cst/diagnostics; optional ast/symbols/imports
    fn parse_json(&mut self, source: &str, include_ast: bool, include_symbols: bool, include_imports: bool) -> PyResult<String> {
        let (cst, diagnostics, ast_value) = self.inner.parse_str(source);
        let mut out = premise_core::api::ParseOutput {
            cst: premise_core::cst::Cst { root_sexpr: cst.root_sexpr, range: cst.range },
            diagnostics,
            ast: if include_ast { ast_value } else { None },
            symbols: None,
            imports: None,
            resolved_imports: None,
        };
        if include_symbols { out.symbols = Some(self.inner.analyze_symbols(source)); }
        if include_imports { out.imports = Some(self.inner.analyze_imports(source)); }
        Ok(serde_json::to_string(&out).unwrap())
    }

    /// Validate source and return JSON report
    fn validate_json(&mut self, source: &str) -> PyResult<String> {
        let report = self.inner.validate(source);
        let out = premise_core::api::ValidateOutput { report };
        Ok(serde_json::to_string(&out).unwrap())
    }

    /// Analyze IR and return JSON
    fn analyze_json(&mut self, source: &str) -> PyResult<String> {
        let ir = self.inner.analyze_ir(source);
        let out = premise_core::api::AnalyzeOutput { ir };
        Ok(serde_json::to_string(&out).unwrap())
    }

    /// Plan adapters and return JSON
    fn plan_json(&mut self, source: &str) -> PyResult<String> {
        let plan = self.inner.plan_adapters(source);
        let out = premise_core::api::PlanOutput { plan };
        Ok(serde_json::to_string(&out).unwrap())
    }
}

/// Return a JSON Schema for a given type name: "parse", "validate", "analyze", "plan", or "all" for map
#[pyfunction]
#[pyo3(signature = (which=None))]
fn schema(which: Option<&str>) -> PyResult<String> {
    let which = which.unwrap_or("all");
    let value = match which {
        "parse" => serde_json::to_value(&schemars::schema_for!(premise_core::api::ParseOutput)).unwrap(),
        "validate" => serde_json::to_value(&schemars::schema_for!(premise_core::api::ValidateOutput)).unwrap(),
        "analyze" => serde_json::to_value(&schemars::schema_for!(premise_core::api::AnalyzeOutput)).unwrap(),
        "plan" => serde_json::to_value(&schemars::schema_for!(premise_core::api::PlanOutput)).unwrap(),
        _ => {
            let mut map = std::collections::BTreeMap::new();
            map.insert("ParseOutput", schemars::schema_for!(premise_core::api::ParseOutput));
            map.insert("ValidateOutput", schemars::schema_for!(premise_core::api::ValidateOutput));
            map.insert("AnalyzeOutput", schemars::schema_for!(premise_core::api::AnalyzeOutput));
            map.insert("PlanOutput", schemars::schema_for!(premise_core::api::PlanOutput));
            serde_json::to_value(&map).unwrap()
        }
    };
    Ok(serde_json::to_string_pretty(&value).unwrap())
}

#[pymodule]
fn premisecore(py: Python<'_>, m: &Bound<PyModule>) -> PyResult<()> {
    m.add_class::<Parser>()?;
    m.add_function(wrap_pyfunction!(schema, py)?)?;
    Ok(())
}


