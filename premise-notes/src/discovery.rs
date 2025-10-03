use regex::Regex;
use std::collections::{HashMap, HashSet};

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub enum EntityType {
    Character,
    Location,
    Object,
    Concept,
}

impl EntityType {
    pub fn as_str(&self) -> &str {
        match self {
            EntityType::Character => "character",
            EntityType::Location => "location",
            EntityType::Object => "object",
            EntityType::Concept => "concept",
        }
    }
}

#[derive(Debug, Clone)]
pub struct EntityCandidate {
    pub canonical_name: String,
    pub entity_type: EntityType,
    pub aliases: Vec<String>,
    pub description: String,
    pub evidence: Vec<String>,
    pub confidence: f64,
}

/// Discover entity candidates from plain text using regex heuristics
pub fn discover_entities_from_text(
    text: &str,
    known_entities: &HashSet<String>,
) -> Vec<EntityCandidate> {
    let mut candidates: HashMap<String, EntityCandidate> = HashMap::new();

    // Multi-word proper nouns
    let proper_noun_re = Regex::new(r"\b([A-Z][a-z]+(?:\s+[A-Z][a-z]+)+)\b").unwrap();
    for cap in proper_noun_re.captures_iter(text) {
        if let Some(m) = cap.get(1) {
            let name = m.as_str().to_string();
            if known_entities.contains(&name) { continue; }
            let entity_type = infer_entity_type(&name, text);
            let confidence = calculate_confidence(&name, text, &entity_type);
            add_or_update(&mut candidates, name, entity_type, "stdin", 0, confidence);
        }
    }

    // Single capitalized words (lower confidence)
    let single_name_re = Regex::new(r"\b([A-Z][a-z]{2,})\b").unwrap();
    for cap in single_name_re.captures_iter(text) {
        if let Some(m) = cap.get(1) {
            let name = m.as_str().to_string();
            if known_entities.contains(&name) || is_common_word(&name) { continue; }
            let entity_type = infer_entity_type(&name, text);
            let mut confidence = calculate_confidence(&name, text, &entity_type);
            confidence *= 0.7;
            if confidence >= 0.4 {
                add_or_update(&mut candidates, name, entity_type, "stdin", 0, confidence);
            }
        }
    }

    candidates.into_values().collect()
}

fn add_or_update(
    candidates: &mut HashMap<String, EntityCandidate>,
    name: String,
    entity_type: EntityType,
    file: &str,
    line: usize,
    confidence: f64,
) {
    let evidence = if line > 0 { format!("{}:{}", file, line) } else { file.to_string() };
    candidates
        .entry(name.clone())
        .and_modify(|c| {
            c.evidence.push(evidence.clone());
            c.confidence = c.confidence.max(confidence);
        })
        .or_insert(EntityCandidate {
            canonical_name: name,
            entity_type,
            aliases: Vec::new(),
            description: String::new(),
            evidence: vec![evidence],
            confidence,
        });
}

fn infer_entity_type(name: &str, context: &str) -> EntityType {
    let context_lower = context.to_lowercase();

    // Character indicators
    let character_patterns = [
        r"\b(said|asked|replied|whispered|shouted|called)\b",
        r"\b(he|she|they|him|her|them)\b",
        r"\b(walked|ran|stood|sat|spoke|thought)\b",
    ];

    // Location indicators
    let location_patterns = [
        r"\b(in|at|to|from|through|into|inside|outside)\s+(?i)",
        r"\b(entered|approached|left|reached|arrived)\b",
    ];

    // Object indicators
    let object_patterns = [
        r"\b(held|gripped|carried|wielded|grabbed|clutched)\b",
        r"\b(the\s+\w+)\s+(glowed|shimmered|hummed)\b",
    ];

    let mut scores: HashMap<EntityType, f64> = HashMap::new();
    scores.insert(EntityType::Character, 0.0);
    scores.insert(EntityType::Location, 0.0);
    scores.insert(EntityType::Object, 0.0);

    for pattern in &character_patterns {
        if Regex::new(pattern).unwrap().is_match(&context_lower) {
            *scores.get_mut(&EntityType::Character).unwrap() += 0.3;
        }
    }
    for pattern in &location_patterns {
        if Regex::new(pattern).unwrap().is_match(&context_lower) {
            *scores.get_mut(&EntityType::Location).unwrap() += 0.3;
        }
    }
    for pattern in &object_patterns {
        if Regex::new(pattern).unwrap().is_match(&context_lower) {
            *scores.get_mut(&EntityType::Object).unwrap() += 0.3;
        }
    }

    if name.contains("Library") || name.contains("District") || name.contains("Tower") {
        *scores.get_mut(&EntityType::Location).unwrap() += 0.4;
    }
    if name.split_whitespace().count() >= 2 {
        *scores.get_mut(&EntityType::Character).unwrap() += 0.2;
    }

    scores
        .into_iter()
        .max_by(|a, b| a.1.partial_cmp(&b.1).unwrap())
        .map(|(t, _)| t)
        .unwrap_or(EntityType::Character)
}

fn calculate_confidence(_name: &str, context: &str, entity_type: &EntityType) -> f64 {
    let context_lower = context.to_lowercase();
    let mut confidence: f64 = 0.5;
    match entity_type {
        EntityType::Character => {
            if Regex::new(r"\b(said|asked|whispered)\b").unwrap().is_match(&context_lower) {
                confidence += 0.3;
            }
        }
        EntityType::Location => {
            if Regex::new(r"\b(in|at|through)\s+").unwrap().is_match(&context_lower) {
                confidence += 0.3;
            }
        }
        EntityType::Object => {
            if Regex::new(r"\b(glowed|hummed|shimmered)\b").unwrap().is_match(&context_lower) {
                confidence += 0.3;
            }
        }
        EntityType::Concept => confidence += 0.1,
    }
    confidence.min(0.95_f64)
}

fn is_common_word(word: &str) -> bool {
    let common = [
        "The", "This", "That", "These", "Those", "Here", "There", "When", "Where", "What",
        "Which", "Who", "Why", "How", "Today", "Tomorrow", "Yesterday", "Never", "Always",
        "Once", "Suddenly", "Finally", "First", "Last", "Next", "Before", "After",
    ];
    common.contains(&word)
}

#[derive(Debug, Clone)]
pub struct AliasDelta {
    pub additions: HashMap<String, Vec<String>>, // canonical -> aliases to add
}

/// Propose alias additions based on candidates compared to current alias map
pub fn propose_alias_updates(
    candidates: &[EntityCandidate],
    alias_map: &HashMap<String, Vec<String>>,
) -> AliasDelta {
    let mut additions: HashMap<String, Vec<String>> = HashMap::new();
    for c in candidates {
        let existing = alias_map.get(&c.canonical_name).cloned().unwrap_or_default();
        let mut to_add: Vec<String> = c
            .aliases
            .iter()
            .filter(|a| !existing.contains(a))
            .cloned()
            .collect();
        to_add.sort();
        to_add.dedup();
        if !to_add.is_empty() {
            additions.insert(c.canonical_name.clone(), to_add);
        }
    }
    AliasDelta { additions }
}

