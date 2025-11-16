use regex::Regex;
//

use crate::generate_id;
use crate::schema::{
    Beat, BeatSource, Fact, FactSource, FactType, Provenance, Section, TimelineEvent, TimelineOrder,
};

#[derive(Default, Debug, Clone)]
pub struct TextExtractionOptions {
    pub file_label: Option<String>,
    pub section_headers: bool,
}

pub fn extract_beats_from_text(text: &str, opts: &TextExtractionOptions) -> Vec<Beat> {
    if opts.section_headers {
        return extract_beats_from_markdown(text, opts);
    }
    let file = opts
        .file_label
        .clone()
        .unwrap_or_else(|| "stdin".to_string());
    let mut beats: Vec<Beat> = Vec::new();
    for (i, line) in text.lines().enumerate() {
        let line_trim = line.trim();
        if line_trim.is_empty() {
            continue;
        }
        let entities = extract_entity_refs(line_trim);
        let beat = Beat {
            id: generate_id("beat_"),
            text: line_trim.to_string(),
            file: file.clone(),
            line: Some(i + 1),
            section: None,
            entities,
            added: chrono::Utc::now().to_rfc3339(),
            source: BeatSource::Imported,
            metadata: None,
            provenance: Some(Provenance {
                source_file: Some(file.clone()),
                source_line: Some(i + 1),
                normalized_with_aliases: None,
                aliases_applied: None,
                normalization_steps: None,
            }),
            importance: None,
            importance_assessments: None,
        };
        beats.push(beat);
    }
    beats
}

/// Extract beats from Markdown: paragraphs become beats; #, ##, ### map to Section.act/scene/cel
pub fn extract_beats_from_markdown(text: &str, opts: &TextExtractionOptions) -> Vec<Beat> {
    let file = opts
        .file_label
        .clone()
        .unwrap_or_else(|| "stdin".to_string());
    let mut beats: Vec<Beat> = Vec::new();
    let mut current_section: Section = Section {
        act: None,
        scene: None,
        cel: None,
    };
    let mut paragraph_lines: Vec<(usize, String)> = Vec::new();

    let flush_paragraph =
        |para: &mut Vec<(usize, String)>, beats: &mut Vec<Beat>, section: &Section| {
            if para.is_empty() {
                return;
            }
            let start_line = para.first().map(|(ln, _)| *ln).unwrap_or(1);
            let text = para
                .iter()
                .map(|(_, s)| s.as_str())
                .collect::<Vec<_>>()
                .join(" ")
                .trim()
                .to_string();
            if text.is_empty() {
                para.clear();
                return;
            }
            let entities = extract_entity_refs(&text);
            let beat = Beat {
                id: generate_id("beat_"),
                text,
                file: file.clone(),
                line: Some(start_line),
                section: Some(section.clone()),
                entities,
                added: chrono::Utc::now().to_rfc3339(),
                source: BeatSource::Imported,
                metadata: None,
                provenance: Some(Provenance {
                    source_file: Some(file.clone()),
                    source_line: Some(start_line),
                    normalized_with_aliases: None,
                    aliases_applied: None,
                    normalization_steps: None,
                }),
                importance: None,
                importance_assessments: None,
            };
            beats.push(beat);
            para.clear();
        };

    for (i, raw) in text.lines().enumerate() {
        let line_num = i + 1;
        let line = raw.trim_end();
        if line.trim().is_empty() {
            flush_paragraph(&mut paragraph_lines, &mut beats, &current_section);
            continue;
        }
        if let Some((level, title)) = parse_markdown_heading(line) {
            flush_paragraph(&mut paragraph_lines, &mut beats, &current_section);
            match level {
                1 => {
                    current_section.act = Some(title.to_string());
                    current_section.scene = None;
                    current_section.cel = None;
                }
                2 => {
                    current_section.scene = Some(title.to_string());
                    current_section.cel = None;
                }
                3 => {
                    current_section.cel = Some(title.to_string());
                }
                _ => {}
            }
            continue;
        }
        paragraph_lines.push((line_num, line.trim().to_string()));
    }
    // Flush final paragraph
    flush_paragraph(&mut paragraph_lines, &mut beats, &current_section);
    beats
}

fn parse_markdown_heading(line: &str) -> Option<(usize, &str)> {
    let trimmed = line.trim_start();
    let mut hashes = 0usize;
    for ch in trimmed.chars() {
        if ch == '#' {
            hashes += 1;
        } else {
            break;
        }
    }
    if hashes > 0 && hashes <= 6 {
        let title = trimmed[hashes..].trim();
        return Some((hashes, title));
    }
    None
}

pub fn extract_facts_from_text(text: &str, file_label: &str) -> Vec<Fact> {
    let mut facts: Vec<Fact> = Vec::new();
    for (i, line) in text.lines().enumerate() {
        let lt = line.trim();
        if lt.is_empty() {
            continue;
        }
        // Simple heuristic: sentences with "is/are" become traits
        if lt.contains(" is ") || lt.contains(" are ") {
            let fact = Fact {
                fact_type: FactType::Trait,
                id: generate_id("fact_"),
                entity: None,
                entities: None,
                category: Some("text".to_string()),
                fact: lt.to_string(),
                evidence: vec![format!("{}:{}", file_label, i + 1)],
                confidence: Some(0.6),
                added: chrono::Utc::now().to_rfc3339(),
                status: None,
                timeline: None,
                source: FactSource::Imported,
                metadata: None,
                provenance: Some(Provenance {
                    source_file: Some(file_label.to_string()),
                    source_line: Some(i + 1),
                    normalized_with_aliases: None,
                    aliases_applied: None,
                    normalization_steps: None,
                }),
                importance: None,
                importance_assessments: None,
            };
            facts.push(fact);
        }
    }
    facts
}

pub fn extract_timeline_from_text(text: &str, file_label: &str) -> Vec<TimelineEvent> {
    let mut events: Vec<TimelineEvent> = Vec::new();
    let mut order = 0i64;
    for (i, line) in text.lines().enumerate() {
        let lt = line.trim();
        if lt.is_empty() {
            continue;
        }
        let ev = TimelineEvent {
            id: generate_id("timeline_"),
            event: lt.to_string(),
            order: TimelineOrder::Numeric(order),
            relative_to: None,
            entities: Vec::new(),
            source: vec![format!("{}:{}", file_label, i + 1)],
            added: chrono::Utc::now().to_rfc3339(),
            provenance: Some(Provenance {
                source_file: Some(file_label.to_string()),
                source_line: Some(i + 1),
                normalized_with_aliases: None,
                aliases_applied: None,
                normalization_steps: None,
            }),
        };
        events.push(ev);
        order += 1;
    }
    events
}

pub fn extract_entity_refs(text: &str) -> Vec<String> {
    let re = Regex::new(r"\{([^}]+)\}").unwrap();
    re.captures_iter(text)
        .filter_map(|cap| cap.get(1).map(|m| m.as_str().trim().to_string()))
        .collect()
}

/// Minimal SRT/VTT transcript parsing: yields beats per caption/dialogue line
pub fn extract_beats_from_transcript(text: &str, opts: &TextExtractionOptions) -> Vec<Beat> {
    let file = opts
        .file_label
        .clone()
        .unwrap_or_else(|| "stdin".to_string());
    let mut beats: Vec<Beat> = Vec::new();
    let mut buffer: Vec<String> = Vec::new();
    let timecode_re =
        Regex::new(r"^\d{2}:\d{2}:\d{2}[\.,]\d{3}\s+-->\s+\d{2}:\d{2}:\d{2}[\.,]\d{3}").unwrap();

    for (i, line) in text.lines().enumerate() {
        let lt = line.trim();
        if lt.is_empty() {
            if !buffer.is_empty() {
                let content = buffer.join(" ").trim().to_string();
                if !content.is_empty() {
                    let entities = extract_entity_refs(&content);
                    beats.push(Beat {
                        id: generate_id("beat_"),
                        text: content,
                        file: file.clone(),
                        line: Some(i + 1),
                        section: None,
                        entities,
                        added: chrono::Utc::now().to_rfc3339(),
                        source: BeatSource::Imported,
                        metadata: None,
                        provenance: Some(Provenance {
                            source_file: Some(file.clone()),
                            source_line: Some(i + 1),
                            normalized_with_aliases: None,
                            aliases_applied: None,
                            normalization_steps: None,
                        }),
                        importance: None,
                        importance_assessments: None,
                    });
                }
                buffer.clear();
            }
            continue;
        }
        if lt.chars().all(|c| c.is_ascii_digit()) {
            continue;
        }
        if timecode_re.is_match(lt) {
            continue;
        }
        buffer.push(lt.to_string());
    }
    if !buffer.is_empty() {
        let content = buffer.join(" ").trim().to_string();
        if !content.is_empty() {
            let entities = extract_entity_refs(&content);
            beats.push(Beat {
                id: generate_id("beat_"),
                text: content,
                file: file.clone(),
                line: None,
                section: None,
                entities,
                added: chrono::Utc::now().to_rfc3339(),
                source: BeatSource::Imported,
                metadata: None,
                provenance: Some(Provenance {
                    source_file: Some(file.clone()),
                    source_line: None,
                    normalized_with_aliases: None,
                    aliases_applied: None,
                    normalization_steps: None,
                }),
                importance: None,
                importance_assessments: None,
            });
        }
    }
    beats
}
