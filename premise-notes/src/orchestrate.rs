use std::collections::{HashMap, HashSet};

use crate::discovery::{discover_entities_from_text, EntityCandidate, propose_alias_updates, AliasDelta};
use crate::normalize::{collect_uncertain_entities_from_text, collect_unknown_fact_entities, normalize_all};
use crate::schema::{Beat, Fact};
use crate::{read_beats, read_facts};

/// One-shot helper: discover entity candidates from text
pub fn discover_entities_from_text_api(text: &str, known: &HashSet<String>) -> Vec<EntityCandidate> {
    discover_entities_from_text(text, known)
}

/// One-shot helper: propose alias additions
pub fn propose_alias_updates_api(candidates: &[EntityCandidate], alias_map: &HashMap<String, Vec<String>>) -> AliasDelta {
    propose_alias_updates(candidates, alias_map)
}

/// One-shot helper: normalize all and collect unknowns
pub fn normalize_all_api(
    beats: Vec<Beat>,
    facts: Vec<Fact>,
    alias_map: &HashMap<String, Vec<String>>,
) -> (Vec<Beat>, Vec<Fact>, Vec<String>) {
    normalize_all(beats, facts, alias_map)
}

/// Summarize unresolved entity references and unknowns across a notes root
pub fn summarize_uncertainties<P: AsRef<std::path::Path>>(
    notes_root: P,
) -> std::io::Result<(Vec<String>, Vec<String>)> {
    let beats = read_beats(&notes_root)?;
    let facts = read_facts(&notes_root)?;

    // Collect uncertain entity refs from beats
    let mut uncertain: HashSet<String> = HashSet::new();
    for b in &beats {
        for name in collect_uncertain_entities_from_text(&b.text) {
            uncertain.insert(name);
        }
    }

    // Unknowns from facts using entities seen in beats as canonical fallback
    let canonical: HashSet<String> = beats
        .iter()
        .flat_map(|b| b.entities.clone())
        .collect();
    let mut unknowns_set: HashSet<String> = collect_unknown_fact_entities(&facts, &canonical)
        .into_iter()
        .collect();

    // Union
    unknowns_set.extend(uncertain.into_iter());

    // Referenced files from beats and fact evidence
    let mut files_set: HashSet<String> = HashSet::new();
    for b in &beats { if !b.file.is_empty() { files_set.insert(b.file.clone()); } }
    for f in &facts {
        for ev in &f.evidence {
            if let Some(fp) = ev.split(':').next() { if !fp.is_empty() { files_set.insert(fp.to_string()); } }
        }
    }

    let mut unknown_entities: Vec<String> = unknowns_set.into_iter().collect();
    unknown_entities.sort();
    let mut files: Vec<String> = files_set.into_iter().collect();
    files.sort();
    Ok((unknown_entities, files))
}

