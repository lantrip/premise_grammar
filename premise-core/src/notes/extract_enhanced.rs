use premise_notes::{generate_id, Beat, BeatSource, Fact, FactSource, FactType, Section};
use regex::Regex;
use std::collections::HashSet;
use tree_sitter::Node;

/// Enhanced extraction that works directly with tree-sitter nodes and source text
pub fn extract_beats_from_tree(root: &Node, source: &str, file_path: &str) -> Vec<Beat> {
    let mut beats = Vec::new();
    let mut current_section = None;
    walk_for_beats(root, source, file_path, &mut beats, &mut current_section);
    beats
}

fn walk_for_beats(
    node: &Node,
    source: &str,
    file_path: &str,
    beats: &mut Vec<Beat>,
    current_section: &mut Option<Section>,
) {
    match node.kind() {
        "act_header" => {
            let title = extract_title_from_header(node, source);
            *current_section = Some(Section {
                act: Some(title),
                scene: None,
                cel: None,
            });
        }
        "scene_header" => {
            let title = extract_title_from_header(node, source);
            if let Some(section) = current_section {
                section.scene = Some(title);
                section.cel = None;
            }
        }
        "cel_header" => {
            let title = extract_title_from_header(node, source);
            if let Some(section) = current_section {
                section.cel = Some(title);
            }
        }
        "beat_content" => {
            // Extract beat text (after ###)
            let text = slice_text(node, source).trim().to_string();
            if !text.is_empty() {
                let entities = extract_entity_references(&text);
                let beat = Beat {
                    id: generate_id("beat_"),
                    text,
                    file: file_path.to_string(),
                    line: Some(node.start_position().row + 1),
                    section: current_section.clone(),
                    entities,
                    added: chrono::Utc::now().to_rfc3339(),
                    source: BeatSource::Imported,
                    metadata: None,
                    provenance: None,
                    importance: None,
                    importance_assessments: None,
                };
                beats.push(beat);
            }
        }
        _ => {}
    }

    // Recurse
    let mut cursor = node.walk();
    for child in node.children(&mut cursor) {
        walk_for_beats(&child, source, file_path, beats, current_section);
    }
}

fn extract_title_from_header(node: &Node, source: &str) -> String {
    if let Some(title_node) = node.child_by_field_name("title") {
        slice_text(&title_node, source).trim().to_string()
    } else {
        // Fallback: extract text after markers
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

fn slice_text(node: &Node, source: &str) -> String {
    source
        .get(node.start_byte()..node.end_byte())
        .unwrap_or("")
        .to_string()
}

fn extract_entity_references(text: &str) -> Vec<String> {
    let re = Regex::new(r"\{([^}]+)\}").unwrap();
    re.captures_iter(text)
        .filter_map(|cap| cap.get(1).map(|m| m.as_str().to_string()))
        .collect()
}

/// Extract entities with their definitions from the tree
pub fn extract_entity_definitions(root: &Node, source: &str, file_path: &str) -> Vec<Fact> {
    let mut facts = Vec::new();
    walk_for_entities(root, source, file_path, &mut facts);
    facts
}

fn walk_for_entities(node: &Node, source: &str, file_path: &str, facts: &mut Vec<Fact>) {
    match node.kind() {
        "entity_construct" => {
            // @character Hero: Description text
            // Parse manually since grammar doesn't expose fields
            let text = slice_text(node, source);
            let re = Regex::new(r"@\w+\s+([A-Za-z0-9\s]+):\s*(.+)").unwrap();
            if let Some(captures) = re.captures(&text) {
                if let (Some(name), Some(desc)) = (captures.get(1), captures.get(2)) {
                    let entity_name = name.as_str().trim().to_string();
                    let description = desc.as_str().trim().to_string();
                    if !entity_name.is_empty() && !description.is_empty() {
                        let fact = Fact {
                            fact_type: FactType::Trait,
                            id: generate_id("fact_"),
                            entity: Some(entity_name.clone()),
                            entities: None,
                            category: Some("description".to_string()),
                            fact: description,
                            evidence: vec![format!(
                                "{}:{}",
                                file_path,
                                node.start_position().row + 1
                            )],
                            confidence: Some(1.0),
                            added: chrono::Utc::now().to_rfc3339(),
                            status: None,
                            timeline: None,
                            source: FactSource::Imported,
                            metadata: None,
                            provenance: None,
                            importance: None,
                            importance_assessments: None,
                        };
                        facts.push(fact);
                    }
                }
            }
        }
        "entity_line" => {
            // Entity line within a block: - Name: Description
            if let Some(name_node) = node.child_by_field_name("entity_name") {
                let entity_name = slice_text(&name_node, source).trim().to_string();

                if let Some(desc_node) = node.child_by_field_name("entity_desc") {
                    let description = slice_text(&desc_node, source).trim().to_string();
                    if !description.is_empty() {
                        let fact = Fact {
                            fact_type: FactType::Trait,
                            id: generate_id("fact_"),
                            entity: Some(entity_name.clone()),
                            entities: None,
                            category: Some("description".to_string()),
                            fact: description,
                            evidence: vec![format!(
                                "{}:{}",
                                file_path,
                                node.start_position().row + 1
                            )],
                            confidence: Some(1.0),
                            added: chrono::Utc::now().to_rfc3339(),
                            status: None,
                            timeline: None,
                            source: FactSource::Imported,
                            metadata: None,
                            provenance: None,
                            importance: None,
                            importance_assessments: None,
                        };
                        facts.push(fact);
                    }
                }
            }
        }
        _ => {}
    }

    // Recurse
    let mut cursor = node.walk();
    for child in node.children(&mut cursor) {
        walk_for_entities(&child, source, file_path, facts);
    }
}

/// Extract entity co-occurrence relationships from dialogue and prose
pub fn extract_entity_cooccurrence(root: &Node, source: &str, file_path: &str) -> Vec<Fact> {
    let mut facts = Vec::new();
    let mut section_context = SectionContext::default();

    walk_for_cooccurrence(root, source, file_path, &mut facts, &mut section_context);

    // Flush final section
    generate_cooccurrence_facts(
        &section_context,
        file_path,
        root.end_position().row,
        &mut facts,
    );

    facts
}

#[derive(Default)]
struct SectionContext {
    act: Option<String>,
    scene: Option<String>,
    cel: Option<String>,
    entities_in_section: HashSet<String>,
}

fn walk_for_cooccurrence(
    node: &Node,
    source: &str,
    file_path: &str,
    facts: &mut Vec<Fact>,
    context: &mut SectionContext,
) {
    match node.kind() {
        "act_header" => {
            // Flush previous section
            generate_cooccurrence_facts(context, file_path, node.start_position().row, facts);

            let title = extract_title_from_header(node, source);
            context.act = Some(title);
            context.scene = None;
            context.cel = None;
            context.entities_in_section.clear();
        }
        "scene_header" => {
            // Flush previous section
            generate_cooccurrence_facts(context, file_path, node.start_position().row, facts);

            let title = extract_title_from_header(node, source);
            context.scene = Some(title);
            context.cel = None;
            context.entities_in_section.clear();
        }
        "cel_header" => {
            // Flush previous section
            generate_cooccurrence_facts(context, file_path, node.start_position().row, facts);

            let title = extract_title_from_header(node, source);
            context.cel = Some(title);
            context.entities_in_section.clear();
        }
        "dialogue_speaker" => {
            // Extract speaker from {Hero} style references
            let speaker_text = slice_text(node, source);
            // Use regex to extract entity name
            for entity in extract_entity_references(&speaker_text) {
                context.entities_in_section.insert(entity);
            }
        }
        "prose_line" | "narrative_content" | "treatment_content" | "beat_content" => {
            // Extract entities from complete line text (not fragments)
            let text = slice_text(node, source);
            for entity in extract_entity_references(&text) {
                context.entities_in_section.insert(entity);
            }
        }
        _ => {}
    }

    // Recurse
    let mut cursor = node.walk();
    for child in node.children(&mut cursor) {
        walk_for_cooccurrence(&child, source, file_path, facts, context);
    }
}

fn generate_cooccurrence_facts(
    context: &SectionContext,
    file_path: &str,
    line: usize,
    facts: &mut Vec<Fact>,
) {
    if context.entities_in_section.len() < 2 {
        return;
    }

    let mut entities: Vec<_> = context.entities_in_section.iter().cloned().collect();
    entities.sort(); // Sort for deterministic ordering

    // Generate relationship facts for each pair
    for i in 0..entities.len() {
        for j in (i + 1)..entities.len() {
            let section_desc = if let Some(cel) = &context.cel {
                format!("cel '{}'", cel)
            } else if let Some(scene) = &context.scene {
                format!("scene '{}'", scene)
            } else if let Some(act) = &context.act {
                format!("act '{}'", act)
            } else {
                "same section".to_string()
            };

            let fact = Fact {
                fact_type: FactType::Relationship,
                id: generate_id("fact_"),
                entity: None,
                entities: Some(vec![entities[i].clone(), entities[j].clone()]),
                category: Some("co-occurrence".to_string()),
                fact: format!(
                    "{} and {} appear together in {}",
                    entities[i], entities[j], section_desc
                ),
                evidence: vec![format!("{}:{}", file_path, line + 1)],
                confidence: Some(0.7),
                added: chrono::Utc::now().to_rfc3339(),
                status: Some("developing".to_string()),
                timeline: None,
                source: FactSource::Imported,
                metadata: None,
                provenance: None,
                importance: None,
                importance_assessments: None,
            };
            facts.push(fact);
        }
    }
}

/// Extract all facts from a parse tree
pub fn extract_all_facts_from_tree(root: &Node, source: &str, file_path: &str) -> Vec<Fact> {
    let mut all_facts = Vec::new();

    // Extract entity definitions (traits)
    let entity_facts = extract_entity_definitions(root, source, file_path);
    all_facts.extend(entity_facts);

    // Extract co-occurrence relationships
    let cooccurrence_facts = extract_entity_cooccurrence(root, source, file_path);
    all_facts.extend(cooccurrence_facts);

    all_facts
}
