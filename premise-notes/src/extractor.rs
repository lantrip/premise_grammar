use crate::extract_text::{
    extract_beats_from_text, extract_facts_from_text, TextExtractionOptions,
};
use crate::provider::{AiConfig, LlmProvider, NoopProvider};
use crate::schema::{
    Beat, BeatMetadata, BeatSource, Fact, FactMetadata, FactSource, FactType, Timeline,
};
use chrono::Utc;
use serde::Deserialize;
use std::sync::Arc;

pub trait Extractor {
    fn extract_beats(&self, text: &str, opts: &TextExtractionOptions) -> Vec<Beat>;
    fn extract_facts(&self, text: &str, file_label: &str) -> Vec<Fact>;
}

#[derive(Default, Debug, Clone)]
pub struct HeuristicExtractor;

impl HeuristicExtractor {
    pub fn new() -> Self {
        Self
    }
}

impl Extractor for HeuristicExtractor {
    fn extract_beats(&self, text: &str, opts: &TextExtractionOptions) -> Vec<Beat> {
        extract_beats_from_text(text, opts)
    }
    fn extract_facts(&self, text: &str, file_label: &str) -> Vec<Fact> {
        extract_facts_from_text(text, file_label)
    }
}

#[derive(Clone)]
pub struct LlmExtractor {
    provider: Arc<dyn LlmProvider>,
}

impl LlmExtractor {
    pub fn new_with(provider: Arc<dyn LlmProvider>) -> Self {
        Self { provider }
    }
    pub fn new_noop(cfg: AiConfig) -> Self {
        Self {
            provider: Arc::new(NoopProvider::new(cfg)),
        }
    }
    pub fn filter_by_min_confidence(&self, facts: &mut Vec<Fact>, threshold: Option<f64>) {
        if let Some(t) = threshold {
            facts.retain(|f| f.confidence.unwrap_or(0.0) >= t);
        }
    }

    fn provider_model(&self) -> Option<String> {
        self.provider.config().model.clone()
    }

    fn build_messages_for_beats(
        text: &str,
        markdown_sections: bool,
    ) -> Vec<crate::provider::ChatMessage> {
        let system = crate::provider::ChatMessage { role: "system".into(), content: "You extract structured narrative beats from story text. Return ONLY JSON array of objects with keys: text (string), entities (array of strings, optional). No prose.".into() };
        let user_prompt = if markdown_sections {
            format!(
                "Extract beats from the following Markdown text between <TEXT> tags. Return JSON only.\n<TEXT>\n{}\n</TEXT>",
                text
            )
        } else {
            format!(
                "Extract beats from the following plain text between <TEXT> tags. Return JSON only.\n<TEXT>\n{}\n</TEXT>",
                text
            )
        };
        let user = crate::provider::ChatMessage {
            role: "user".into(),
            content: user_prompt,
        };
        vec![system, user]
    }

    fn build_messages_for_facts(text: &str) -> Vec<crate::provider::ChatMessage> {
        let system = crate::provider::ChatMessage { role: "system".into(), content: "You extract atomic facts about entities from story text. Return ONLY JSON array of objects with keys: fact (string), entities (array of strings, optional) or entity (string), type (trait|relationship|knowledge|event|state), confidence (0..1), evidence (array of strings, optional). No prose.".into() };
        let user = crate::provider::ChatMessage {
            role: "user".into(),
            content: format!(
                "Extract facts from the following text. Return JSON only.\n<TEXT>\n{}\n</TEXT>",
                text
            ),
        };
        vec![system, user]
    }
}

impl Extractor for LlmExtractor {
    fn extract_beats(&self, text: &str, opts: &TextExtractionOptions) -> Vec<Beat> {
        let messages = Self::build_messages_for_beats(text, opts.section_headers);
        let now = Utc::now().to_rfc3339();
        let model = self.provider_model();
        #[derive(Deserialize)]
        struct LlmBeatOut {
            text: String,
            entities: Option<Vec<String>>,
        }
        if let Ok(raw) = self.provider.complete_chat(&messages) {
            let parsed: Result<Vec<LlmBeatOut>, _> = serde_json::from_str(raw.trim());
            if let Ok(list) = parsed {
                let file_label = opts.file_label.clone().unwrap_or_else(|| "unknown".into());
                return list
                    .into_iter()
                    .map(|b| Beat {
                        id: String::new(),
                        text: b.text,
                        file: file_label.clone(),
                        line: None,
                        section: None,
                        entities: b.entities.unwrap_or_default(),
                        added: now.clone(),
                        source: BeatSource::LlmGenerated,
                        metadata: Some(BeatMetadata {
                            model: model.clone(),
                            mode: Some(if opts.section_headers { "markdown".into() } else { "plain".into() }),
                            prompt_version: Some("v1".into()),
                        }),
                        provenance: None,
                        importance: None,
                        importance_assessments: None,
                    })
                    .collect();
            }
        }
        // Fallback to heuristics on error
        extract_beats_from_text(text, opts)
    }
    fn extract_facts(&self, text: &str, file_label: &str) -> Vec<Fact> {
        let messages = Self::build_messages_for_facts(text);
        let now = Utc::now().to_rfc3339();
        let model = self.provider_model();
        #[derive(Deserialize)]
        struct LlmFactOut {
            fact: String,
            #[serde(default)]
            entity: Option<String>,
            #[serde(default)]
            entities: Option<Vec<String>>,
            #[serde(rename = "type", default)]
            kind: Option<String>,
            #[serde(default)]
            confidence: Option<f64>,
            #[serde(default)]
            evidence: Option<Vec<String>>,
            #[serde(default)]
            category: Option<String>,
            #[serde(default)]
            timeline: Option<String>,
        }
        fn map_kind(s: &str) -> FactType {
            match s.to_lowercase().as_str() {
                "trait" => FactType::Trait,
                "relationship" => FactType::Relationship,
                "event" => FactType::Event,
                "state" => FactType::State,
                _ => FactType::Knowledge,
            }
        }
        fn map_timeline(s: &str) -> Option<Timeline> {
            match s.to_lowercase().as_str() {
                "past" => Some(Timeline::Past),
                "present" => Some(Timeline::Present),
                "future" => Some(Timeline::Future),
                _ => None,
            }
        }
        if let Ok(raw) = self.provider.complete_chat(&messages) {
            let parsed: Result<Vec<LlmFactOut>, _> = serde_json::from_str(raw.trim());
            if let Ok(list) = parsed {
                return list
                    .into_iter()
                    .map(|f| Fact {
                        fact_type: f
                            .kind
                            .as_deref()
                            .map(map_kind)
                            .unwrap_or(FactType::Knowledge),
                        id: String::new(),
                        entity: f.entity,
                        entities: f.entities,
                        category: f.category,
                        fact: f.fact,
                        evidence: f.evidence.unwrap_or_else(|| vec![file_label.to_string()]),
                        confidence: f.confidence,
                        added: now.clone(),
                        status: None,
                        timeline: f.timeline.and_then(|t| map_timeline(&t)),
                        source: FactSource::LlmGenerated,
                        metadata: Some(FactMetadata { model: model.clone(), prompt_version: Some("v1".into()) }),
                        provenance: None,
                        importance: None,
                        importance_assessments: None,
                    })
                    .collect();
            }
        }
        // Fallback to heuristics on error
        extract_facts_from_text(text, file_label)
    }
}
