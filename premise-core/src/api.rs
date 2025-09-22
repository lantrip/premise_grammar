use serde::{Deserialize, Serialize};
use schemars::JsonSchema;

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(rename_all = "snake_case")]
pub enum OutputFormat {
    Json,
    Pretty,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct ParseOutput {
    pub cst: crate::cst::Cst,
    pub diagnostics: Vec<crate::diagnostics::Diagnostic>,
    pub ast: Option<crate::ast::AstNode>,
    pub symbols: Option<crate::symbols::Analysis>,
    pub imports: Option<crate::imports::ImportAnalysis>,
    pub resolved_imports: Option<crate::imports::ImportResolution>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct ValidateOutput {
    pub report: crate::validation::ValidationReport,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct AnalyzeOutput {
    pub ir: crate::ir::IrAnalysis,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct PlanOutput {
    pub plan: crate::planning::PlanAnalysis,
}


