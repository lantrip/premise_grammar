use std::collections::{HashMap, HashSet};

use crate::extract_text::{
    extract_beats_from_text, extract_facts_from_text, TextExtractionOptions,
};
use crate::schema::{Beat, Fact};
use crate::{normalize_beats, normalize_facts};

pub struct ExtractPipeline;

pub struct BeatParams<'a> {
    pub content: &'a str,
    pub file_label: &'a str,
    pub markdown_sections: bool,
    pub aliases: Option<&'a HashMap<String, Vec<String>>>,
    pub min_importance: Option<f64>,
    pub stable_ids: bool,
}

pub struct FactParams<'a> {
    pub content: &'a str,
    pub file_label: &'a str,
    pub aliases: Option<&'a HashMap<String, Vec<String>>>,
    pub min_importance: Option<f64>,
    pub min_confidence: Option<f64>,
    pub stable_ids: bool,
}

impl ExtractPipeline {
    pub fn beats_from_text(params: BeatParams) -> Vec<Beat> {
        let opts = TextExtractionOptions {
            file_label: Some(params.file_label.to_string()),
            section_headers: params.markdown_sections,
        };
        let mut beats = extract_beats_from_text(params.content, &opts);

        // Aliases and normalization
        let (canonical, reverse) = Self::canon_and_reverse(params.aliases);
        beats = normalize_beats(beats, &canonical, &reverse);

        // Importance heuristic (if missing) and filter
        for b in &mut beats {
            if b.importance.is_none() {
                let score = (b.entities.len() as f64).min(3.0) / 3.0
                    + ((b.text.len() as f64).min(300.0) / 600.0);
                if score >= 0.5 {
                    b.importance = Some(crate::schema::Importance {
                        score,
                        assessed_by: crate::schema::ImportanceSource::Heuristic,
                        method: Some("entities_count+length".to_string()),
                        updated: chrono::Utc::now().to_rfc3339(),
                    });
                    if let Some(list) = &mut b.importance_assessments {
                        list.push(b.importance.clone().unwrap());
                    } else {
                        b.importance_assessments = Some(vec![b.importance.clone().unwrap()]);
                    }
                }
            }
        }
        if let Some(threshold) = params.min_importance {
            beats.retain(|b| {
                b.importance
                    .as_ref()
                    .map(|i| i.score >= threshold)
                    .unwrap_or(false)
            });
        }

        if params.stable_ids {
            for b in &mut beats {
                let line_str = b.line.map(|n| n.to_string()).unwrap_or_default();
                let id = crate::io::stable_id("beat_", &[&b.file, &line_str, &b.text]);
                b.id = id;
            }
        }

        beats
    }

    pub fn facts_from_text(params: FactParams) -> Vec<Fact> {
        let mut facts = extract_facts_from_text(params.content, params.file_label);

        // Aliases and normalization
        let (_canonical, reverse) = Self::canon_and_reverse(params.aliases);
        facts = normalize_facts(facts, &reverse);

        // Importance heuristic (if missing)
        for f in &mut facts {
            if f.importance.is_none() {
                let base = if matches!(
                    f.fact_type,
                    crate::schema::FactType::Event | crate::schema::FactType::Relationship
                ) {
                    0.8
                } else {
                    0.4
                };
                let conf = f.confidence.unwrap_or(0.6);
                let score = (base + conf) / 2.0;
                if score >= 0.5 {
                    f.importance = Some(crate::schema::Importance {
                        score,
                        assessed_by: crate::schema::ImportanceSource::Heuristic,
                        method: Some("type_weight+confidence".to_string()),
                        updated: chrono::Utc::now().to_rfc3339(),
                    });
                    if let Some(list) = &mut f.importance_assessments {
                        list.push(f.importance.clone().unwrap());
                    } else {
                        f.importance_assessments = Some(vec![f.importance.clone().unwrap()]);
                    }
                }
            }
        }

        if let Some(threshold) = params.min_confidence {
            facts.retain(|f| f.confidence.unwrap_or(0.0) >= threshold);
        }
        if let Some(threshold) = params.min_importance {
            facts.retain(|f| {
                f.importance
                    .as_ref()
                    .map(|i| i.score >= threshold)
                    .unwrap_or(false)
            });
        }

        if params.stable_ids {
            for f in &mut facts {
                let ev = f.evidence.first().cloned().unwrap_or_default();
                let id = crate::io::stable_id("fact_", &[&ev, &f.fact]);
                f.id = id;
            }
        }

        facts
    }

    fn canon_and_reverse(
        aliases: Option<&HashMap<String, Vec<String>>>,
    ) -> (HashSet<String>, HashMap<String, String>) {
        if let Some(map) = aliases {
            let canonical: HashSet<String> = map.keys().cloned().collect();
            (canonical.clone(), crate::build_reverse_alias_map(map))
        } else {
            (HashSet::new(), HashMap::new())
        }
    }
}
