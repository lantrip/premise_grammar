use crate::ast::AstNode;
use crate::ir::IrAnalysis;
use premise_notes::{
    generate_id, Beat, BeatSource, Fact, FactSource, FactType, Section, TimelineEvent,
    TimelineOrder,
};
use regex::Regex;

/// Extract beats from AST (structural only, no AI)
pub fn extract_beats_from_ast(ast: &AstNode, file_path: &str) -> Vec<Beat> {
    let mut beats = Vec::new();
    extract_beats_recursive(ast, file_path, &mut beats, &mut None);
    beats
}

fn extract_beats_recursive(
    node: &AstNode,
    file_path: &str,
    beats: &mut Vec<Beat>,
    current_section: &mut Option<Section>,
) {
    match node.kind.as_str() {
        "act_header" => {
            let act_name = extract_header_text(node);
            *current_section = Some(Section {
                act: Some(act_name),
                scene: None,
                cel: None,
            });
        }
        "scene_header" => {
            let scene_name = extract_header_text(node);
            if let Some(section) = current_section {
                section.scene = Some(scene_name);
                section.cel = None;
            }
        }
        "cel_header" => {
            let cel_name = extract_header_text(node);
            if let Some(section) = current_section {
                section.cel = Some(cel_name);
            }
        }
        "beat_content" => {
            let text = extract_text_content(node);
            let entities = extract_entity_references(&text);
            let beat = Beat {
                id: generate_id("beat_"),
                text,
                file: file_path.to_string(),
                line: Some(node.range.start.row + 1),
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
        _ => {}
    }

    // Recurse into children
    for child in &node.children {
        extract_beats_recursive(child, file_path, beats, current_section);
    }
}

fn extract_header_text(node: &AstNode) -> String {
    // Extract text from header, stripping markers and whitespace
    for child in &node.children {
        if child.kind == "header_text" || child.field.as_deref() == Some("title") {
            return extract_text_content(child);
        }
    }
    String::new()
}

fn extract_text_content(node: &AstNode) -> String {
    // For leaf nodes, we would need the source text
    // For now, we'll recursively collect from children
    if node.children.is_empty() {
        // Leaf node - would need source text here
        // This is a limitation of working with AST alone
        return node.kind.clone();
    }

    node.children
        .iter()
        .map(extract_text_content)
        .filter(|s| !s.is_empty())
        .collect::<Vec<_>>()
        .join(" ")
        .trim()
        .to_string()
}

fn extract_entity_references(text: &str) -> Vec<String> {
    let re = Regex::new(r"\{([^}]+)\}").unwrap();
    re.captures_iter(text)
        .filter_map(|cap| cap.get(1).map(|m| m.as_str().to_string()))
        .collect()
}

/// Extract structural facts from IR (no AI)
/// Note: This is a simplified version that extracts from the StoryGraph
pub fn extract_facts_from_ir(ir: &IrAnalysis, file_path: &str) -> Vec<Fact> {
    let mut facts = Vec::new();

    // Extract timeline-based facts from story structure
    for act in &ir.ir.story.acts {
        let fact = Fact {
            fact_type: FactType::Event,
            id: generate_id("fact_"),
            entity: None,
            entities: None,
            category: Some("act".to_string()),
            fact: format!("Act: {}", act.title),
            evidence: vec![format!("{}:{}", file_path, act.range.start.row + 1)],
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

    for scene in &ir.ir.story.scenes {
        let fact = Fact {
            fact_type: FactType::Event,
            id: generate_id("fact_"),
            entity: None,
            entities: None,
            category: Some("scene".to_string()),
            fact: format!("Scene: {}", scene.title),
            evidence: vec![format!("{}:{}", file_path, scene.range.start.row + 1)],
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

    facts
}

/// Extract timeline events from IR structure
pub fn extract_timeline_from_ir(ir: &IrAnalysis, file_path: &str) -> Vec<TimelineEvent> {
    let mut events = Vec::new();
    let mut order = 0i64;

    for act in &ir.ir.story.acts {
        let event = TimelineEvent {
            id: generate_id("timeline_"),
            event: act.title.clone(),
            order: TimelineOrder::Numeric(order),
            relative_to: None,
            entities: vec![],
            source: vec![format!("{}:{}", file_path, act.range.start.row + 1)],
            added: chrono::Utc::now().to_rfc3339(),
            provenance: None,
        };
        events.push(event);
        order += 1;
    }

    for scene in &ir.ir.story.scenes {
        let event = TimelineEvent {
            id: generate_id("timeline_"),
            event: scene.title.clone(),
            order: TimelineOrder::Numeric(order),
            relative_to: None,
            entities: vec![],
            source: vec![format!("{}:{}", file_path, scene.range.start.row + 1)],
            added: chrono::Utc::now().to_rfc3339(),
            provenance: None,
        };
        events.push(event);
        order += 1;
    }

    events
}
