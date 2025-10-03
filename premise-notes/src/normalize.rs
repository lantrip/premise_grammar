use regex::Regex;
use std::collections::{HashMap, HashSet};

use crate::schema::{Beat, Fact};

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
            normalized.push_str(&text[last_idx..m.start()]);
            let inner = cap.get(1).map(|m| m.as_str().trim()).unwrap_or("");
            let (is_uncertain, name_raw) = if inner.starts_with('?') { (true, inner.trim_start_matches('?').trim()) } else { (false, inner) };
            let mapped = if let Some(canon) = reverse_alias.get(name_raw) { canon.as_str() } else { name_raw };
            let final_token = if canonical.contains(mapped) {
                if is_uncertain { format!("{{?{}}}", mapped) } else { format!("{{{}}}", mapped) }
            } else {
                let tok = if mapped.is_empty() { name_raw } else { mapped };
                format!("{{?{}}}", tok)
            };
            normalized.push_str(&final_token);
            last_idx = m.end();
        }
    }
    normalized.push_str(&text[last_idx..]);

    let mut entities: Vec<String> = Vec::new();
    for cap in re.captures_iter(&normalized) {
        if let Some(inner) = cap.get(1) {
            let token = inner.as_str().trim();
            if token.starts_with('?') { continue; }
            if !token.is_empty() { entities.push(token.to_string()); }
        }
    }
    entities.sort();
    entities.dedup();
    (normalized, entities)
}

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
            if let Some(ref mut prov) = b.provenance {
                // Append step indicator for idempotence tracking
                if prov.normalization_steps.is_none() { prov.normalization_steps = Some(Vec::new()); }
                if let Some(ref mut steps) = prov.normalization_steps { steps.push("normalize_beat_text".to_string()); }
            } else {
                b.provenance = Some(crate::schema::Provenance {
                    source_file: None,
                    source_line: None,
                    normalized_with_aliases: None,
                    aliases_applied: None,
                    normalization_steps: Some(vec!["normalize_beat_text".to_string()]),
                });
            }
            b
        })
        .collect()
}

pub fn normalize_facts(
    facts: Vec<Fact>,
    reverse_alias: &HashMap<String, String>,
) -> Vec<Fact> {
    facts
        .into_iter()
        .map(|mut f| {
            if let Some(ref e) = f.entity {
                if let Some(canon) = reverse_alias.get(e) { f.entity = Some(canon.clone()); }
            }
            if let Some(ref mut es) = f.entities {
                for item in es.iter_mut() {
                    if let Some(canon) = reverse_alias.get(item) { *item = canon.clone(); }
                }
                es.sort();
                es.dedup();
            }
            if let Some(ref mut prov) = f.provenance {
                if prov.normalization_steps.is_none() { prov.normalization_steps = Some(Vec::new()); }
                if let Some(ref mut steps) = prov.normalization_steps { steps.push("normalize_facts".to_string()); }
            } else {
                f.provenance = Some(crate::schema::Provenance {
                    source_file: None,
                    source_line: None,
                    normalized_with_aliases: None,
                    aliases_applied: None,
                    normalization_steps: Some(vec!["normalize_facts".to_string()]),
                });
            }
            f
        })
        .collect()
}

pub fn collect_uncertain_entities_from_text(text: &str) -> Vec<String> {
    let re = Regex::new(r"\{\?([^}]+)\}").unwrap();
    let mut out: Vec<String> = Vec::new();
    for cap in re.captures_iter(text) {
        if let Some(m) = cap.get(1) {
            let name = m.as_str().trim();
            if !name.is_empty() { out.push(name.to_string()); }
        }
    }
    out.sort();
    out.dedup();
    out
}

/// High-level normalization for both beats and facts; returns normalized records and unknowns
pub fn normalize_all(
    beats: Vec<Beat>,
    facts: Vec<Fact>,
    alias_map: &std::collections::HashMap<String, Vec<String>>,
) -> (Vec<Beat>, Vec<Fact>, Vec<String>) {
    use crate::io::build_reverse_alias_map;
    let canonical: HashSet<String> = alias_map.keys().cloned().collect();
    let reverse = build_reverse_alias_map(alias_map);
    let beats_norm = normalize_beats(beats, &canonical, &reverse);
    let facts_norm = normalize_facts(facts, &reverse);
    let unknowns = collect_unknown_fact_entities(&facts_norm, &canonical);
    (beats_norm, facts_norm, unknowns)
}

pub fn collect_unknown_fact_entities(
    facts: &[Fact],
    canonical: &HashSet<String>,
) -> Vec<String> {
    let mut set: HashSet<String> = HashSet::new();
    for f in facts {
        if let Some(ref e) = f.entity { if !canonical.contains(e) { set.insert(e.clone()); } }
        if let Some(ref es) = f.entities {
            for e in es { if !canonical.contains(e) { set.insert(e.clone()); } }
        }
    }
    let mut out: Vec<String> = set.into_iter().collect();
    out.sort();
    out
}

