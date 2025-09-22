use serde::{Deserialize, Serialize};
use schemars::JsonSchema;

use crate::{diagnostics::Diagnostic, ir};

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct AdapterGraphNode {
    pub id: String,
    pub index: usize,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct AdapterGraphEdge {
    pub from: usize,
    pub to: usize,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct AdapterGraph {
    pub nodes: Vec<AdapterGraphNode>,
    pub edges: Vec<AdapterGraphEdge>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct PlanStep {
    pub adapter: String,
    pub index: usize,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct AdapterPlan {
    pub steps: Vec<PlanStep>,
}

#[derive(Debug, Default, Clone, Serialize, Deserialize, JsonSchema)]
pub struct PlanAnalysis {
    pub plan: AdapterPlan,
    pub graph: AdapterGraph,
    pub diagnostics: Vec<Diagnostic>,
}

pub fn plan_from_ir(ir: &ir::Ir) -> PlanAnalysis {
    // Deterministic order: document order, dedup by first occurrence
    let mut seen = std::collections::HashSet::<String>::new();
    let mut steps: Vec<PlanStep> = Vec::new();
    let mut nodes: Vec<AdapterGraphNode> = Vec::new();
    for (i, a) in ir.adapters.iter().enumerate() {
        if seen.insert(a.name_or_path.clone()) {
            steps.push(PlanStep { adapter: a.name_or_path.clone(), index: i });
            nodes.push(AdapterGraphNode { id: a.name_or_path.clone(), index: i });
        }
    }
    // For now, linear edges in the chosen order
    let mut edges: Vec<AdapterGraphEdge> = Vec::new();
    for w in 1..nodes.len() {
        edges.push(AdapterGraphEdge { from: nodes[w - 1].index, to: nodes[w].index });
    }
    PlanAnalysis { plan: AdapterPlan { steps }, graph: AdapterGraph { nodes, edges }, diagnostics: Vec::new() }
}



