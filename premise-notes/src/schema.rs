use schemars::JsonSchema;
use serde::{Deserialize, Serialize};
use std::collections::BTreeMap;

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(tag = "type", rename = "beat")]
pub struct Beat {
    pub id: String,
    pub text: String,
    pub file: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub line: Option<usize>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub section: Option<Section>,
    pub entities: Vec<String>,
    pub added: String,
    pub source: BeatSource,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub metadata: Option<BeatMetadata>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub provenance: Option<Provenance>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Section {
    #[serde(skip_serializing_if = "Option::is_none")]
    pub act: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub scene: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub cel: Option<String>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(rename_all = "kebab-case")]
pub enum BeatSource {
    LlmGenerated,
    Manual,
    Imported,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct BeatMetadata {
    #[serde(skip_serializing_if = "Option::is_none")]
    pub model: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub mode: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub prompt_version: Option<String>,
}

/// Per-record provenance details for transparency and repeatability
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Provenance {
    #[serde(skip_serializing_if = "Option::is_none")]
    pub source_file: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub source_line: Option<usize>,
    /// Aliases considered during normalization (canonical names)
    #[serde(skip_serializing_if = "Option::is_none")]
    pub normalized_with_aliases: Option<Vec<String>>,
    /// Mapping of alias -> canonical applied during normalization
    #[serde(skip_serializing_if = "Option::is_none")]
    pub aliases_applied: Option<BTreeMap<String, String>>,
    /// Freeform step names for normalization pipeline
    #[serde(skip_serializing_if = "Option::is_none")]
    pub normalization_steps: Option<Vec<String>>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Fact {
    #[serde(rename = "type")]
    pub fact_type: FactType,
    pub id: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub entity: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub entities: Option<Vec<String>>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub category: Option<String>,
    pub fact: String,
    pub evidence: Vec<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub confidence: Option<f64>,
    pub added: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub status: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub timeline: Option<Timeline>,
    pub source: FactSource,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub metadata: Option<FactMetadata>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub provenance: Option<Provenance>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(rename_all = "lowercase")]
#[derive(PartialEq, Eq)]
pub enum FactType {
    Trait,
    Relationship,
    Knowledge,
    Event,
    State,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(rename_all = "lowercase")]
pub enum Timeline {
    Past,
    Present,
    Future,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(rename_all = "kebab-case")]
pub enum FactSource {
    LlmGenerated,
    Manual,
    Imported,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct FactMetadata {
    #[serde(skip_serializing_if = "Option::is_none")]
    pub model: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub prompt_version: Option<String>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(tag = "type", rename = "timeline")]
pub struct TimelineEvent {
    pub id: String,
    pub event: String,
    pub order: TimelineOrder,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub relative_to: Option<String>,
    pub entities: Vec<String>,
    pub source: Vec<String>,
    pub added: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub provenance: Option<Provenance>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(untagged)]
pub enum TimelineOrder {
    Named(TimelineOrderName),
    Numeric(i64),
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(rename_all = "lowercase")]
pub enum TimelineOrderName {
    Past,
    Present,
    Future,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(tag = "type", rename = "consistency")]
pub struct ConsistencyEntry {
    pub id: String,
    pub category: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub entity: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub entities: Option<Vec<String>>,
    pub state: String,
    pub value: String,
    pub established: Vec<String>,
    pub last_confirmed: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub notes: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub provenance: Option<Provenance>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct NotesIndex {
    pub schema_version: String,
    pub story_root: String,
    pub last_updated: String,
    pub stats: NotesStats,
    pub entity_index: BTreeMap<String, Vec<String>>,
    pub file_index: BTreeMap<String, Vec<String>>,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct NotesStats {
    pub beats: usize,
    pub facts: usize,
    pub timeline_events: usize,
    pub consistency_entries: usize,
    pub entities_tracked: usize,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct NotesMetadata {
    pub schema_version: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub title: Option<String>,
    pub created: String,
    pub modified: String,
    pub config: NotesConfig,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct NotesConfig {
    pub auto_export: bool,
    pub fact_categories: Vec<String>,
    pub lsp_integration: bool,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(untagged)]
pub enum NotesRecord {
    Beat(Beat),
    Fact(Fact),
    TimelineEvent(TimelineEvent),
    ConsistencyEntry(ConsistencyEntry),
}

