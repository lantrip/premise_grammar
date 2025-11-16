use regex::Regex;
use std::collections::{HashMap, HashSet};
use tree_sitter::Node;

/// Entity candidate discovered from text analysis
#[derive(Debug, Clone)]
pub struct EntityCandidate {
    pub canonical_name: String,
    pub entity_type: EntityType,
    pub aliases: Vec<String>,
    pub description: String,
    pub evidence: Vec<String>,
    pub confidence: f64,
}

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

/// Extract entity definitions with their aliases from metadata
pub fn extract_entities_with_aliases(
    root: &Node,
    source: &str,
    _file_path: &str,
) -> HashMap<String, Vec<String>> {
    let mut entity_aliases: HashMap<String, Vec<String>> = HashMap::new();

    // Walk through top-level nodes sequentially to track entity->metadata association
    let mut cursor = root.walk();
    let mut last_entity: Option<String> = None;

    for node in root.children(&mut cursor) {
        if node.kind() == "line" {
            // Check if this line contains an entity_construct or metadata_line
            let mut child_cursor = node.walk();
            for child in node.children(&mut child_cursor) {
                match child.kind() {
                    "entity_construct" => {
                        let text = slice_text(&child, source);
                        if let Some(entity_name) = extract_entity_name_from_construct(&text) {
                            last_entity = Some(entity_name.clone());
                            entity_aliases.entry(entity_name).or_default();
                        }
                    }
                    "entity_block" => {
                        // Process entity block
                        extract_aliases_from_block(&child, source, &mut entity_aliases);
                        last_entity = None; // Reset after block
                    }
                    "metadata_line" => {
                        // Metadata line follows an entity - associate it
                        if let Some(entity) = &last_entity {
                            // Parse metadata manually since fields aren't accessible
                            let text = slice_text(&child, source);
                            if let Some((key, value)) = parse_metadata_line(&text) {
                                if key == "aliases" {
                                    let aliases: Vec<String> = value
                                        .split(',')
                                        .map(|s| s.trim().to_string())
                                        .filter(|s| !s.is_empty())
                                        .collect();

                                    entity_aliases
                                        .entry(entity.clone())
                                        .or_default()
                                        .extend(aliases);
                                }
                            }
                        }
                    }
                    "act_header" | "scene_header" | "cel_header" => {
                        last_entity = None; // Reset on structural break
                    }
                    _ => {}
                }
            }
        }
    }

    entity_aliases
}

fn extract_aliases_from_block(
    block_node: &Node,
    source: &str,
    aliases_map: &mut HashMap<String, Vec<String>>,
) {
    let mut cursor = block_node.walk();
    let mut last_entity: Option<String> = None;

    for child in block_node.children(&mut cursor) {
        match child.kind() {
            "entity_line" => {
                if let Some(name_node) = child.child_by_field_name("entity_name") {
                    let entity_name = slice_text(&name_node, source).trim().to_string();
                    last_entity = Some(entity_name.clone());
                    aliases_map.entry(entity_name).or_default();
                }
            }
            "metadata_line" => {
                if let Some(entity) = &last_entity {
                    let text = slice_text(&child, source);
                    if let Some((key, value)) = parse_metadata_line(&text) {
                        if key == "aliases" {
                            let aliases: Vec<String> = value
                                .split(',')
                                .map(|s| s.trim().to_string())
                                .filter(|s| !s.is_empty())
                                .collect();

                            aliases_map
                                .entry(entity.clone())
                                .or_default()
                                .extend(aliases);
                        }
                    }
                }
            }
            _ => {}
        }
    }
}

fn extract_entity_name_from_construct(text: &str) -> Option<String> {
    let re = Regex::new(r"@\w+\s+([A-Za-z0-9\s]+):").unwrap();
    re.captures(text)
        .and_then(|cap| cap.get(1))
        .map(|m| m.as_str().trim().to_string())
}

fn parse_metadata_line(text: &str) -> Option<(String, String)> {
    // +key: value
    let re = Regex::new(r"^\+(\w+):\s*(.*)$").unwrap();
    re.captures(text).and_then(|cap| {
        let key = cap.get(1)?.as_str().to_string();
        let value = cap.get(2)?.as_str().trim().to_string();
        Some((key, value))
    })
}

/// Discover entities from narrative text (not from explicit @entity definitions)
/// This is for HYBRID mode - finding entities mentioned but not yet defined
pub fn discover_entities_from_narrative(
    root: &Node,
    source: &str,
    file_path: &str,
    known_entities: &HashSet<String>,
) -> Vec<EntityCandidate> {
    let mut candidates: HashMap<String, EntityCandidate> = HashMap::new();
    let mut section_context = SectionContext::default();

    walk_for_narrative_entities(
        root,
        source,
        file_path,
        known_entities,
        &mut candidates,
        &mut section_context,
    );

    candidates.into_values().collect()
}

#[derive(Default)]
struct SectionContext {
    act: Option<String>,
    scene: Option<String>,
    cel: Option<String>,
    current_line: usize,
}

fn walk_for_narrative_entities(
    node: &Node,
    source: &str,
    file_path: &str,
    known_entities: &HashSet<String>,
    candidates: &mut HashMap<String, EntityCandidate>,
    context: &mut SectionContext,
) {
    context.current_line = node.start_position().row + 1;

    match node.kind() {
        "act_header" => {
            context.act = Some(extract_header_title(node, source));
            context.scene = None;
            context.cel = None;
        }
        "scene_header" => {
            context.scene = Some(extract_header_title(node, source));
            context.cel = None;
        }
        "cel_header" => {
            context.cel = Some(extract_header_title(node, source));
        }
        "entity_reference" => {
            // Existing {Entity} references
            if let Some(name_node) = node.child_by_field_name("ref_name") {
                let entity_name = slice_text(&name_node, source).trim().to_string();

                // Check if this is an uncertain reference {?Entity}
                if entity_name.starts_with('?') {
                    let actual_name = entity_name.trim_start_matches('?').to_string();
                    if !known_entities.contains(&actual_name) && !actual_name.is_empty() {
                        add_or_update_candidate(
                            candidates,
                            actual_name,
                            EntityType::Character, // Default assumption
                            file_path,
                            context.current_line,
                            0.6, // Uncertain reference
                        );
                    }
                } else if !known_entities.contains(&entity_name) {
                    // Known reference but not in canonical list - add as candidate
                    add_or_update_candidate(
                        candidates,
                        entity_name,
                        EntityType::Character,
                        file_path,
                        context.current_line,
                        0.7,
                    );
                }
            }
        }
        "dialogue_speaker" => {
            // {Speaker} in dialogue - high confidence character
            if let Some(speaker_node) = node.child_by_field_name("speaker_name") {
                let speaker_name = slice_text(&speaker_node, source).trim().to_string();
                if !known_entities.contains(&speaker_name) && !speaker_name.is_empty() {
                    add_or_update_candidate(
                        candidates,
                        speaker_name,
                        EntityType::Character,
                        file_path,
                        context.current_line,
                        0.9, // Dialogue speakers are very likely characters
                    );
                }
            }
        }
        "dialogue_content" | "prose_text" | "narrative" | "content" => {
            // Analyze text for potential entities using NER-like heuristics
            let text = slice_text(node, source);
            discover_from_text(
                &text,
                file_path,
                context.current_line,
                known_entities,
                candidates,
            );
        }
        _ => {}
    }

    // Recurse
    let mut cursor = node.walk();
    for child in node.children(&mut cursor) {
        walk_for_narrative_entities(
            &child,
            source,
            file_path,
            known_entities,
            candidates,
            context,
        );
    }
}

fn extract_header_title(node: &Node, source: &str) -> String {
    if let Some(title_node) = node.child_by_field_name("title") {
        slice_text(&title_node, source).trim().to_string()
    } else {
        let text = slice_text(node, source);
        text.trim_start_matches('=')
            .trim_start_matches('@')
            .split('[')
            .next()
            .unwrap_or("")
            .trim()
            .to_string()
    }
}

/// Discover entities from plain text using NER-like heuristics
fn discover_from_text(
    text: &str,
    file_path: &str,
    line: usize,
    known_entities: &HashSet<String>,
    candidates: &mut HashMap<String, EntityCandidate>,
) {
    // Pattern: Capitalized multi-word names (e.g., "Maya Chen", "Last Library")
    let proper_noun_re = Regex::new(r"\b([A-Z][a-z]+(?:\s+[A-Z][a-z]+)+)\b").unwrap();

    for cap in proper_noun_re.captures_iter(text) {
        if let Some(matched) = cap.get(1) {
            let name = matched.as_str().to_string();
            if !known_entities.contains(&name) {
                let entity_type = infer_entity_type(&name, text);
                let confidence = calculate_confidence(&name, text, &entity_type);

                add_or_update_candidate(candidates, name, entity_type, file_path, line, confidence);
            }
        }
    }

    // Pattern: Single capitalized words (less confident)
    let single_name_re = Regex::new(r"\b([A-Z][a-z]{2,})\b").unwrap();
    for cap in single_name_re.captures_iter(text) {
        if let Some(matched) = cap.get(1) {
            let name = matched.as_str().to_string();
            // Skip common words
            if is_common_word(&name) || known_entities.contains(&name) {
                continue;
            }

            let entity_type = infer_entity_type(&name, text);
            let confidence = calculate_confidence(&name, text, &entity_type) * 0.7; // Lower confidence for single words

            if confidence >= 0.4 {
                // Only add if meets minimum threshold
                add_or_update_candidate(candidates, name, entity_type, file_path, line, confidence);
            }
        }
    }
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

    // Check character patterns
    for pattern in &character_patterns {
        if Regex::new(pattern).unwrap().is_match(&context_lower) {
            *scores.get_mut(&EntityType::Character).unwrap() += 0.3;
        }
    }

    // Check location patterns
    for pattern in &location_patterns {
        if Regex::new(pattern).unwrap().is_match(&context_lower) {
            *scores.get_mut(&EntityType::Location).unwrap() += 0.3;
        }
    }

    // Check object patterns
    for pattern in &object_patterns {
        if Regex::new(pattern).unwrap().is_match(&context_lower) {
            *scores.get_mut(&EntityType::Object).unwrap() += 0.3;
        }
    }

    // Name-based heuristics
    if name.contains("Library") || name.contains("District") || name.contains("Tower") {
        *scores.get_mut(&EntityType::Location).unwrap() += 0.4;
    }

    if name.split_whitespace().count() >= 2 {
        // Multi-word names are more likely characters (e.g., "Maya Chen")
        *scores.get_mut(&EntityType::Character).unwrap() += 0.2;
    }

    // Return type with highest score
    scores
        .into_iter()
        .max_by(|a, b| a.1.partial_cmp(&b.1).unwrap())
        .map(|(t, _)| t)
        .unwrap_or(EntityType::Character) // Default to character
}

fn calculate_confidence(name: &str, context: &str, entity_type: &EntityType) -> f64 {
    let mut confidence: f64 = 0.5; // Base confidence

    // Multi-word names are more confident
    if name.split_whitespace().count() >= 2 {
        confidence += 0.2;
    }

    // Check for supporting evidence in context
    let context_lower = context.to_lowercase();
    let name_lower = name.to_lowercase();

    match entity_type {
        EntityType::Character => {
            if Regex::new(&format!(r"\b{}\b.*(said|asked|whispered)", name_lower))
                .unwrap()
                .is_match(&context_lower)
            {
                confidence += 0.3;
            }
        }
        EntityType::Location => {
            if Regex::new(&format!(r"\b(in|at|through)\s+{}", name_lower))
                .unwrap()
                .is_match(&context_lower)
            {
                confidence += 0.3;
            }
        }
        EntityType::Object => {
            if Regex::new(&format!(r"\b{}\b.*(glowed|hummed|shimmered)", name_lower))
                .unwrap()
                .is_match(&context_lower)
            {
                confidence += 0.3;
            }
        }
        EntityType::Concept => {
            confidence += 0.1;
        }
    }

    confidence.min(0.95_f64) // Cap at 0.95 (only explicit definitions get 1.0)
}

fn is_common_word(word: &str) -> bool {
    let common = [
        "The",
        "This",
        "That",
        "These",
        "Those",
        "Here",
        "There",
        "When",
        "Where",
        "What",
        "Which",
        "Who",
        "Why",
        "How",
        "Today",
        "Tomorrow",
        "Yesterday",
        "Never",
        "Always",
        "Once",
        "Suddenly",
        "Finally",
        "First",
        "Last",
        "Next",
        "Before",
        "After",
    ];
    common.contains(&word)
}

fn add_or_update_candidate(
    candidates: &mut HashMap<String, EntityCandidate>,
    name: String,
    entity_type: EntityType,
    file_path: &str,
    line: usize,
    confidence: f64,
) {
    let evidence = format!("{}:{}", file_path, line);

    candidates
        .entry(name.clone())
        .and_modify(|c| {
            c.evidence.push(evidence.clone());
            // Update confidence to max
            c.confidence = c.confidence.max(confidence);
        })
        .or_insert_with(|| EntityCandidate {
            canonical_name: name.clone(),
            entity_type,
            aliases: Vec::new(),
            description: String::new(), // Will be filled by LLM or user
            evidence: vec![evidence],
            confidence,
        });
}

fn slice_text(node: &Node, source: &str) -> String {
    source
        .get(node.start_byte()..node.end_byte())
        .unwrap_or("")
        .to_string()
}

/// Merge alias map with discovered candidates
pub fn merge_aliases_with_candidates(
    candidates: &mut [EntityCandidate],
    alias_map: &HashMap<String, Vec<String>>,
) {
    for candidate in candidates.iter_mut() {
        if let Some(aliases) = alias_map.get(&candidate.canonical_name) {
            candidate.aliases.extend_from_slice(aliases);
        }
    }
}

/// Build reverse alias map (alias -> canonical name)
pub use premise_notes::normalize::collect_uncertain_entities_from_text;
pub use premise_notes::normalize::collect_unknown_fact_entities;
pub use premise_notes::normalize::normalize_beat_text;
pub use premise_notes::normalize::normalize_beats;
pub use premise_notes::normalize::normalize_facts;

pub use premise_notes::io::build_reverse_alias_map;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_infer_character_from_dialogue() {
        let text = "Maya Chen said, 'Hello there.'";
        let entity_type = infer_entity_type("Maya Chen", text);
        assert_eq!(entity_type, EntityType::Character);
    }

    #[test]
    fn test_infer_location_from_preposition() {
        let text = "They entered the Last Library through the eastern gate.";
        let entity_type = infer_entity_type("Last Library", text);
        assert_eq!(entity_type, EntityType::Location);
    }

    #[test]
    fn test_confidence_calculation() {
        let text = "Maya Chen said, 'This is important.'";
        let confidence = calculate_confidence("Maya Chen", text, &EntityType::Character);
        assert!(confidence > 0.7, "Expected high confidence for dialogue");
    }

    #[test]
    fn test_common_word_filtering() {
        assert!(is_common_word("The"));
        assert!(is_common_word("Suddenly"));
        assert!(!is_common_word("Maya"));
    }

    #[test]
    fn test_reverse_alias_map() {
        let mut aliases = HashMap::new();
        aliases.insert(
            "Maya Chen".to_string(),
            vec!["Chen".to_string(), "Maya".to_string()],
        );

        let reverse = build_reverse_alias_map(&aliases);
        assert_eq!(reverse.get("Chen"), Some(&"Maya Chen".to_string()));
        assert_eq!(reverse.get("Maya"), Some(&"Maya Chen".to_string()));
    }
}
