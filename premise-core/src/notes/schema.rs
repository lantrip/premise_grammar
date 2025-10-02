use schemars::JsonSchema;
use serde::{Deserialize, Serialize};
use std::collections::BTreeMap;

/// A story beat - a major story milestone or turning point
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(tag = "type", rename = "beat")]
pub struct Beat {
    /// Unique identifier for this beat
    pub id: String,
    /// The beat text, potentially containing {Entity} references
    pub text: String,
    /// Source file path relative to story root
    pub file: String,
    /// Line number in source file where beat was anchored
    #[serde(skip_serializing_if = "Option::is_none")]
    pub line: Option<usize>,
    /// Section context where beat appears
    #[serde(skip_serializing_if = "Option::is_none")]
    pub section: Option<Section>,
    /// Entity names referenced in this beat
    pub entities: Vec<String>,
    /// Timestamp when beat was added (ISO 8601)
    pub added: String,
    /// Source of beat: "llm-generated" | "manual" | "imported"
    pub source: BeatSource,
    /// Optional generation metadata
    #[serde(skip_serializing_if = "Option::is_none")]
    pub metadata: Option<BeatMetadata>,
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

/// A story fact - extractable knowledge about entities, events, or world state
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Fact {
    /// Fact type discriminator
    #[serde(rename = "type")]
    pub fact_type: FactType,
    /// Unique identifier for this fact
    pub id: String,
    /// Entity or entities this fact concerns
    #[serde(skip_serializing_if = "Option::is_none")]
    pub entity: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub entities: Option<Vec<String>>,
    /// The fact category for organization
    #[serde(skip_serializing_if = "Option::is_none")]
    pub category: Option<String>,
    /// The actual fact statement
    pub fact: String,
    /// Evidence supporting this fact (file:line references)
    pub evidence: Vec<String>,
    /// Confidence score 0.0-1.0
    #[serde(skip_serializing_if = "Option::is_none")]
    pub confidence: Option<f64>,
    /// Timestamp when fact was extracted (ISO 8601)
    pub added: String,
    /// Status for relationships: "established" | "developing" | "uncertain" | "broken"
    #[serde(skip_serializing_if = "Option::is_none")]
    pub status: Option<String>,
    /// Optional temporal context
    #[serde(skip_serializing_if = "Option::is_none")]
    pub timeline: Option<Timeline>,
    /// Source of fact extraction
    pub source: FactSource,
    /// Optional generation metadata
    #[serde(skip_serializing_if = "Option::is_none")]
    pub metadata: Option<FactMetadata>,
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

/// Timeline event - temporal ordering of story events
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(tag = "type", rename = "timeline")]
pub struct TimelineEvent {
    /// Unique identifier for this event
    pub id: String,
    /// Description of the event
    pub event: String,
    /// Temporal order indicator
    pub order: TimelineOrder,
    /// Optional reference point for relative ordering
    #[serde(skip_serializing_if = "Option::is_none")]
    pub relative_to: Option<String>,
    /// Entities involved in this event
    pub entities: Vec<String>,
    /// Source file references
    pub source: Vec<String>,
    /// Timestamp when event was added (ISO 8601)
    pub added: String,
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

/// Consistency tracking entry - state that should remain consistent
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(tag = "type", rename = "consistency")]
pub struct ConsistencyEntry {
    /// Unique identifier for this entry
    pub id: String,
    /// Category: "possession" | "location" | "state" | "knowledge"
    pub category: String,
    /// Entity or entities this concerns
    #[serde(skip_serializing_if = "Option::is_none")]
    pub entity: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub entities: Option<Vec<String>>,
    /// The state being tracked
    pub state: String,
    /// Current value of this state
    pub value: String,
    /// When this state was established (file:line references)
    pub established: Vec<String>,
    /// When this state was last confirmed (ISO 8601)
    pub last_confirmed: String,
    /// Optional notes about expected consistency
    #[serde(skip_serializing_if = "Option::is_none")]
    pub notes: Option<String>,
}

/// Index manifest - quick lookup structure (JSON, not JSONL)
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct NotesIndex {
    /// Schema version for future compatibility
    pub schema_version: String,
    /// Story root path
    pub story_root: String,
    /// Last updated timestamp (ISO 8601)
    pub last_updated: String,
    /// Statistics
    pub stats: NotesStats,
    /// Entity -> record IDs mapping for quick lookup
    pub entity_index: BTreeMap<String, Vec<String>>,
    /// File -> record IDs mapping
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

/// Notes metadata - configuration for notes system (JSON, not JSONL)
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct NotesMetadata {
    /// Schema version
    pub schema_version: String,
    /// Story title
    #[serde(skip_serializing_if = "Option::is_none")]
    pub title: Option<String>,
    /// When notes tracking began (ISO 8601)
    pub created: String,
    /// Last modified timestamp (ISO 8601)
    pub modified: String,
    /// Configuration
    pub config: NotesConfig,
}

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct NotesConfig {
    /// Auto-export notes after generation
    pub auto_export: bool,
    /// Fact categories to track
    pub fact_categories: Vec<String>,
    /// Enable LSP integration
    pub lsp_integration: bool,
}

/// Union type for all JSONL record types
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
#[serde(untagged)]
pub enum NotesRecord {
    Beat(Beat),
    Fact(Fact),
    TimelineEvent(TimelineEvent),
    ConsistencyEntry(ConsistencyEntry),
}
