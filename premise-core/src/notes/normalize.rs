use regex::Regex;
use std::collections::{HashMap, HashSet};

use super::schema::{Beat, Fact};

/// Normalize a beat's text and entities by:
/// - Mapping aliases to canonical names inside {Entity} references
/// - Converting unknown {Entity} to {?Entity} (uncertain)
/// Returns (normalized_text, canonical_entities)
pub fn normalize_beat_text(
    text: &str,
    canonical: &HashSet<String>,
    reverse_alias: &HashMap<String, String>,
) -> (String, Vec<String>) {
    let re = Regex::new(r"\{([^}]+)\}").unwrap();
    let mut normalized = String::new();
    let mut last_idx = 0usize;
    for cap in re.captures_iter(text) {
        if let Some(m) = cap.get(0) {
            // Append preceding plain text
            normalized.push_str(&text[last_idx..m.start()]);
            let inner = cap.get(1).map(|m| m.as_str().trim()).unwrap_or("");
            let (is_uncertain, name_raw) = if inner.starts_with('?') {
                (true, inner.trim_start_matches('?').trim())
            } else {
                (false, inner)
            };

            // Alias normalization (even for uncertain) if uniquely resolvable
            let mapped = if let Some(canon) = reverse_alias.get(name_raw) {
                canon.as_str()
            } else {
                name_raw
            };

            let final_token = if canonical.contains(mapped) {
                if is_uncertain {
                    format!("{{?{}}}", mapped)
                } else {
                    format!("{{{}}}", mapped)
                }
            } else {
                // Unknown -> mark uncertain, keep original or mapped token
                let tok = if mapped.is_empty() { name_raw } else { mapped };
                format!("{{?{}}}", tok)
            };

            normalized.push_str(&final_token);
            last_idx = m.end();
        }
    }
    // Append trailing text
    normalized.push_str(&text[last_idx..]);

    // Extract canonical entity list from normalized text (exclude uncertain)
    let mut entities: Vec<String> = Vec::new();
    for cap in re.captures_iter(&normalized) {
        if let Some(inner) = cap.get(1) {
            let token = inner.as_str().trim();
            if token.starts_with('?') {
                continue;
            }
            if !token.is_empty() {
                entities.push(token.to_string());
            }
        }
    }
    entities.sort();
    entities.dedup();
    (normalized, entities)
}

/// Normalize a set of beats in-place and return a new Vec
pub fn normalize_beats(
    beats: Vec<Beat>,
    canonical: &HashSet<String>,
    reverse_alias: &HashMap<String, String>,
) -> Vec<Beat> {
    beats
        .into_iter()
        .map(|mut b| {
            let (text, ents) = normalize_beat_text(&b.text, canonical, reverse_alias);
            b.text = text;
            b.entities = ents;
            b
        })
        .collect()
}

/// Normalize Fact entity names using alias map to canonical.
/// Unknowns are left unchanged; normalization is best-effort.
pub fn normalize_facts(
    facts: Vec<Fact>,
    reverse_alias: &HashMap<String, String>,
) -> Vec<Fact> {
    facts
        .into_iter()
        .map(|mut f| {
            if let Some(ref e) = f.entity {
                if let Some(canon) = reverse_alias.get(e) {
                    f.entity = Some(canon.clone());
                }
            }
            if let Some(ref mut es) = f.entities {
                for item in es.iter_mut() {
                    if let Some(canon) = reverse_alias.get(item) {
                        *item = canon.clone();
                    }
                }
                es.sort();
                es.dedup();
            }
            f
        })
        .collect()
}

/// Collect uncertain entity tokens (e.g., {?Name}) present in a beat text
pub fn collect_uncertain_entities_from_text(text: &str) -> Vec<String> {
    let re = Regex::new(r"\{\?([^}]+)\}").unwrap();
    let mut out: Vec<String> = Vec::new();
    for cap in re.captures_iter(text) {
        if let Some(m) = cap.get(1) {
            let name = m.as_str().trim();
            if !name.is_empty() {
                out.push(name.to_string());
            }
        }
    }
    out.sort();
    out.dedup();
    out
}

/// Collect unknown entity names referenced by facts' entity fields
pub fn collect_unknown_fact_entities(
    facts: &[Fact],
    canonical: &HashSet<String>,
) -> Vec<String> {
    let mut set: HashSet<String> = HashSet::new();
    for f in facts {
        if let Some(ref e) = f.entity {
            if !canonical.contains(e) {
                set.insert(e.clone());
            }
        }
        if let Some(ref es) = f.entities {
            for e in es {
                if !canonical.contains(e) {
                    set.insert(e.clone());
                }
            }
        }
    }
    let mut out: Vec<String> = set.into_iter().collect();
    out.sort();
    out
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::notes::{BeatSource, FactSource, FactType};
    use crate::notes::schema;

    #[test]
    fn test_normalize_beat_text_alias_and_unknown() {
        let mut canonical = HashSet::new();
        canonical.insert("Maya Chen".to_string());
        let mut reverse = std::collections::HashMap::new();
        reverse.insert("Maya".to_string(), "Maya Chen".to_string());

        let (text, entities) = normalize_beat_text("{Maya} meets {Kai}", &canonical, &reverse);
        assert_eq!(text, "{Maya Chen} meets {?Kai}");
        assert_eq!(entities, vec!["Maya Chen".to_string()]);
    }

    #[test]
    fn test_collect_uncertain_entities_from_text() {
        let u = collect_uncertain_entities_from_text("{?Maya} argues with {?Kai} while {Chen} watches");
        assert_eq!(u, vec!["Kai".to_string(), "Maya".to_string()]);
    }

    #[test]
    fn test_normalize_facts_aliases() {
        let mut reverse = std::collections::HashMap::new();
        reverse.insert("Maya".to_string(), "Maya Chen".to_string());
        let facts = vec![
            schema::Fact {
                fact_type: FactType::Trait,
                id: "f1".to_string(),
                entity: Some("Maya".to_string()),
                entities: Some(vec!["Maya".to_string(), "Kai".to_string()]),
                category: None,
                fact: "is brave".to_string(),
                evidence: vec![],
                confidence: None,
                added: "2020-01-01T00:00:00Z".to_string(),
                status: None,
                timeline: None,
                source: FactSource::Manual,
                metadata: None,
            }
        ];
        let out = normalize_facts(facts, &reverse);
        let f = &out[0];
        assert_eq!(f.entity.as_deref(), Some("Maya Chen"));
        assert!(f.entities.as_ref().unwrap().contains(&"Maya Chen".to_string()));
    }

    #[test]
    fn test_normalize_beats_alias_and_uncertain() {
        use std::collections::{HashMap, HashSet};

        let mut canonical: HashSet<String> = HashSet::new();
        canonical.insert("Maya Chen".to_string());

        let mut reverse: HashMap<String, String> = HashMap::new();
        reverse.insert("Maya".to_string(), "Maya Chen".to_string());

        let beats = vec![
            schema::Beat {
                id: "b1".to_string(),
                text: "{Maya} meets {?Kai}".to_string(),
                file: "story/scene1.prem".to_string(),
                line: Some(10),
                section: None,
                entities: vec![],
                added: "2020-01-01T00:00:00Z".to_string(),
                source: BeatSource::Manual,
                metadata: None,
            },
            schema::Beat {
                id: "b2".to_string(),
                text: "Walks with {Maya} and {?Sam}".to_string(),
                file: "story/scene2.prem".to_string(),
                line: Some(5),
                section: None,
                entities: vec![],
                added: "2020-01-01T00:00:00Z".to_string(),
                source: BeatSource::Manual,
                metadata: None,
            },
        ];

        let out = super::normalize_beats(beats, &canonical, &reverse);
        assert_eq!(out[0].text, "{Maya Chen} meets {?Kai}");
        assert_eq!(out[0].entities, vec!["Maya Chen".to_string()]);
        assert_eq!(out[1].text, "Walks with {Maya Chen} and {?Sam}");
        assert_eq!(out[1].entities, vec!["Maya Chen".to_string()]);
    }

    #[test]
    fn test_collect_unknown_fact_entities() {
        use std::collections::HashSet;

        let mut canonical: HashSet<String> = HashSet::new();
        canonical.insert("Maya Chen".to_string());

        let facts = vec![
            schema::Fact {
                fact_type: FactType::Trait,
                id: "f1".to_string(),
                entity: Some("Kai".to_string()),
                entities: None,
                category: None,
                fact: "is calm".to_string(),
                evidence: vec![],
                confidence: None,
                added: "2020-01-01T00:00:00Z".to_string(),
                status: None,
                timeline: None,
                source: FactSource::Manual,
                metadata: None,
            },
            schema::Fact {
                fact_type: FactType::Relationship,
                id: "f2".to_string(),
                entity: None,
                entities: Some(vec!["Maya Chen".to_string(), "Sam".to_string()]),
                category: None,
                fact: "works with".to_string(),
                evidence: vec![],
                confidence: None,
                added: "2020-01-01T00:00:00Z".to_string(),
                status: None,
                timeline: None,
                source: FactSource::Manual,
                metadata: None,
            },
        ];

        let unknowns = super::collect_unknown_fact_entities(&facts, &canonical);
        assert_eq!(unknowns, vec!["Kai".to_string(), "Sam".to_string()]);
    }
}


