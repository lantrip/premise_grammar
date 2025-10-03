use crate::schema::*;
use serde::{Deserialize, Serialize};
use std::collections::{BTreeMap, HashMap, HashSet};
use std::fs;
use std::io::{BufRead, BufReader, Write};
use std::path::{Path, PathBuf};

const NOTES_DIR: &str = ".premise-notes";
const SCHEMA_VERSION: &str = "1.0";

pub fn get_notes_dir<P: AsRef<Path>>(story_root: P) -> PathBuf {
    story_root.as_ref().join(NOTES_DIR)
}

pub fn ensure_notes_dir<P: AsRef<Path>>(story_root: P) -> std::io::Result<PathBuf> {
    let notes_dir = get_notes_dir(story_root);
    fs::create_dir_all(&notes_dir)?;
    Ok(notes_dir)
}

pub fn read_jsonl<T>(file_path: &Path) -> std::io::Result<Vec<T>>
where
    T: serde::de::DeserializeOwned,
{
    if !file_path.exists() {
        return Ok(Vec::new());
    }
    let file = fs::File::open(file_path)?;
    let reader = BufReader::new(file);
    let mut records = Vec::new();
    for line in reader.lines() {
        let line = line?;
        let line = line.trim();
        if line.is_empty() {
            continue;
        }
        match serde_json::from_str::<T>(line) {
            Ok(record) => records.push(record),
            Err(e) => eprintln!("Warning: failed to parse JSONL line: {}", e),
        }
    }
    Ok(records)
}

pub fn append_jsonl<T>(file_path: &Path, record: &T) -> std::io::Result<()>
where
    T: serde::Serialize,
{
    let mut file = fs::OpenOptions::new()
        .create(true)
        .append(true)
        .open(file_path)?;
    let line = serde_json::to_string(record)?;
    writeln!(file, "{}", line)?;
    Ok(())
}

pub fn append_many_jsonl<T>(file_path: &Path, records: &[T]) -> std::io::Result<()>
where
    T: serde::Serialize,
{
    let mut file = fs::OpenOptions::new()
        .create(true)
        .append(true)
        .open(file_path)?;
    for record in records {
        let line = serde_json::to_string(record)?;
        writeln!(file, "{}", line)?;
    }
    Ok(())
}

pub fn write_jsonl<T>(file_path: &Path, records: &[T]) -> std::io::Result<()>
where
    T: serde::Serialize,
{
    let mut file = fs::File::create(file_path)?;
    for record in records {
        let line = serde_json::to_string(record)?;
        writeln!(file, "{}", line)?;
    }
    Ok(())
}

/// Generate a stable ID from content inputs (e.g., file, line, and text)
pub fn stable_id(prefix: &str, parts: &[&str]) -> String {
    use sha2::{Digest, Sha256};
    let mut hasher = Sha256::new();
    for p in parts { hasher.update(p.as_bytes()); hasher.update(b"\x1f"); }
    let hash = hasher.finalize();
    let short = base16ct::lower::encode_string(&hash[..12]);
    format!("{}{}", prefix, short)
}

pub fn read_index<P: AsRef<Path>>(story_root: P) -> std::io::Result<Option<NotesIndex>> {
    let index_path = get_notes_dir(story_root).join("index.json");
    if !index_path.exists() {
        return Ok(None);
    }
    let content = fs::read_to_string(index_path)?;
    let index = serde_json::from_str(&content)?;
    Ok(Some(index))
}

pub fn write_index<P: AsRef<Path>>(story_root: P, index: &NotesIndex) -> std::io::Result<()> {
    let notes_dir = ensure_notes_dir(&story_root)?;
    let index_path = notes_dir.join("index.json");
    let content = serde_json::to_string_pretty(index)?;
    fs::write(index_path, content)?;
    Ok(())
}

pub fn read_metadata<P: AsRef<Path>>(story_root: P) -> std::io::Result<Option<NotesMetadata>> {
    let metadata_path = get_notes_dir(story_root).join("metadata.json");
    if !metadata_path.exists() {
        return Ok(None);
    }
    let content = fs::read_to_string(metadata_path)?;
    let metadata = serde_json::from_str(&content)?;
    Ok(Some(metadata))
}

pub fn write_metadata<P: AsRef<Path>>(
    story_root: P,
    metadata: &NotesMetadata,
) -> std::io::Result<()> {
    let notes_dir = ensure_notes_dir(&story_root)?;
    let metadata_path = notes_dir.join("metadata.json");
    let content = serde_json::to_string_pretty(metadata)?;
    fs::write(metadata_path, content)?;
    Ok(())
}

pub fn initialize_notes<P: AsRef<Path>>(story_root: P, title: Option<String>) -> std::io::Result<()> {
    let notes_dir = ensure_notes_dir(&story_root)?;
    if read_metadata(&story_root)?.is_none() {
        let metadata = NotesMetadata {
            schema_version: SCHEMA_VERSION.to_string(),
            title: title.or_else(|| {
                story_root
                    .as_ref()
                    .file_name()
                    .and_then(|n| n.to_str())
                    .map(|s| s.to_string())
            }),
            created: chrono::Utc::now().to_rfc3339(),
            modified: chrono::Utc::now().to_rfc3339(),
            config: NotesConfig {
                auto_export: false,
                fact_categories: vec![
                    "trait".to_string(),
                    "relationship".to_string(),
                    "knowledge".to_string(),
                    "event".to_string(),
                    "state".to_string(),
                ],
                lsp_integration: false,
            },
        };
        write_metadata(&story_root, &metadata)?;
    }

    let files = ["beats.jsonl", "facts.jsonl", "timeline.jsonl", "consistency.jsonl"];
    for file in &files {
        let file_path = notes_dir.join(file);
        if !file_path.exists() {
            fs::File::create(file_path)?;
        }
    }
    Ok(())
}

pub fn read_beats<P: AsRef<Path>>(story_root: P) -> std::io::Result<Vec<Beat>> {
    let beats_path = get_notes_dir(story_root).join("beats.jsonl");
    read_jsonl(&beats_path)
}

pub fn append_beats<P: AsRef<Path>>(story_root: P, beats: &[Beat]) -> std::io::Result<()> {
    ensure_notes_dir(&story_root)?;
    let beats_path = get_notes_dir(story_root).join("beats.jsonl");
    append_many_jsonl(&beats_path, beats)
}

pub fn read_facts<P: AsRef<Path>>(story_root: P) -> std::io::Result<Vec<Fact>> {
    let facts_path = get_notes_dir(story_root).join("facts.jsonl");
    read_jsonl(&facts_path)
}

pub fn append_facts<P: AsRef<Path>>(story_root: P, facts: &[Fact]) -> std::io::Result<()> {
    ensure_notes_dir(&story_root)?;
    let facts_path = get_notes_dir(story_root).join("facts.jsonl");
    append_many_jsonl(&facts_path, facts)
}

pub fn read_timeline<P: AsRef<Path>>(story_root: P) -> std::io::Result<Vec<TimelineEvent>> {
    let timeline_path = get_notes_dir(story_root).join("timeline.jsonl");
    read_jsonl(&timeline_path)
}

pub fn read_consistency<P: AsRef<Path>>(story_root: P) -> std::io::Result<Vec<ConsistencyEntry>> {
    let consistency_path = get_notes_dir(story_root).join("consistency.jsonl");
    read_jsonl(&consistency_path)
}

pub fn generate_id(prefix: &str) -> String {
    use std::time::{SystemTime, UNIX_EPOCH};
    let timestamp = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_millis();
    let random = rand::random::<u32>();
    format!("{}{:x}{:x}", prefix, timestamp, random)
}

pub fn rebuild_index<P: AsRef<Path>>(story_root: P) -> std::io::Result<NotesIndex> {
    let story_root_ref = story_root.as_ref();
    let beats = read_beats(story_root_ref)?;
    let facts = read_facts(story_root_ref)?;
    let timeline = read_timeline(story_root_ref)?;
    let consistency = read_consistency(story_root_ref)?;

    let mut entity_index: BTreeMap<String, Vec<String>> = BTreeMap::new();
    let mut file_index: BTreeMap<String, Vec<String>> = BTreeMap::new();
    let mut entities_tracked = HashSet::new();

    for beat in &beats {
        if !beat.file.is_empty() {
            file_index.entry(beat.file.clone()).or_insert_with(Vec::new).push(beat.id.clone());
        }
        for entity in &beat.entities {
            entity_index.entry(entity.clone()).or_insert_with(Vec::new).push(beat.id.clone());
            entities_tracked.insert(entity.clone());
        }
    }

    for fact in &facts {
        if let Some(entity) = &fact.entity {
            entity_index.entry(entity.clone()).or_insert_with(Vec::new).push(fact.id.clone());
            entities_tracked.insert(entity.clone());
        }
        if let Some(entities) = &fact.entities {
            for entity in entities {
                entity_index.entry(entity.clone()).or_insert_with(Vec::new).push(fact.id.clone());
                entities_tracked.insert(entity.clone());
            }
        }
        for evidence in &fact.evidence {
            if let Some(file) = evidence.split(':').next() {
                file_index.entry(file.to_string()).or_insert_with(Vec::new).push(fact.id.clone());
            }
        }
    }

    let index = NotesIndex {
        schema_version: SCHEMA_VERSION.to_string(),
        story_root: story_root_ref.to_str().unwrap_or_default().to_string(),
        last_updated: chrono::Utc::now().to_rfc3339(),
        stats: NotesStats {
            beats: beats.len(),
            facts: facts.len(),
            timeline_events: timeline.len(),
            consistency_entries: consistency.len(),
            entities_tracked: entities_tracked.len(),
        },
        entity_index,
        file_index,
    };

    write_index(story_root_ref, &index)?;
    Ok(index)
}

pub fn get_notes_status<P: AsRef<Path>>(story_root: P) -> std::io::Result<(bool, bool, Option<NotesStats>)> {
    let notes_dir = get_notes_dir(&story_root);
    let exists = notes_dir.exists();
    if !exists { return Ok((false, false, None)); }

    let metadata = read_metadata(&story_root)?;
    let initialized = metadata.is_some();
    if initialized {
        let index = read_index(&story_root)?;
        let stats = index.map(|i| i.stats);
        return Ok((true, true, stats));
    }
    Ok((true, false, None))
}

/// Build reverse alias map (alias -> canonical). Conflicts are ignored (first wins) for determinism.
pub fn build_reverse_alias_map(
    alias_map: &HashMap<String, Vec<String>>,
) -> HashMap<String, String> {
    let mut reverse: HashMap<String, String> = HashMap::new();
    // Deterministic iteration by sorting canonicals
    let mut canonicals: Vec<_> = alias_map.keys().cloned().collect();
    canonicals.sort();
    for canon in canonicals {
        if let Some(aliases) = alias_map.get(&canon) {
            for alias in aliases {
                if reverse.contains_key(alias) {
                    // Conflict: alias already mapped to a different canonical; keep first mapping
                    continue;
                }
                reverse.insert(alias.clone(), canon.clone());
            }
        }
    }
    reverse
}

/// Path to the aliases JSON file under the notes directory
pub fn get_aliases_file<P: AsRef<Path>>(story_root: P) -> PathBuf {
    get_notes_dir(story_root).join("aliases.json")
}

/// Read the aliases map stored in notes (canonical -> [aliases])
pub fn read_alias_map<P: AsRef<Path>>(
    story_root: P,
) -> std::io::Result<HashMap<String, Vec<String>>> {
    let path = get_aliases_file(&story_root);
    if !path.exists() {
        return Ok(HashMap::new());
    }
    let content = std::fs::read_to_string(&path)?;
    let map = serde_json::from_str(&content).unwrap_or_default();
    Ok(map)
}

/// Load aliases by merging notes aliases.json with an optional list of external files.
/// Returns merged map and a conflict report using the same shape as merge_alias_maps.
pub fn load_aliases_with<P: AsRef<Path>>(
    story_root: P,
    extra_files: &[std::path::PathBuf],
) -> std::io::Result<(HashMap<String, Vec<String>>, AliasMergeReport)> {
    let mut base = read_alias_map(&story_root)?;
    let mut total_report = AliasMergeReport { added: 0, conflicts: Vec::new() };
    for file in extra_files {
        if !file.exists() { continue; }
        let content = std::fs::read_to_string(file)?;
        let incoming: HashMap<String, Vec<String>> = serde_json::from_str(&content).unwrap_or_default();
        let report = merge_alias_maps(&mut base, &incoming);
        total_report.added += report.added;
        total_report.conflicts.extend(report.conflicts);
    }
    Ok((base, total_report))
}

/// Apply alias delta (canonical -> aliases to add) and return report
pub fn apply_alias_delta(
    base: &mut HashMap<String, Vec<String>>,
    delta: &HashMap<String, Vec<String>>,
) -> AliasMergeReport {
    merge_alias_maps(base, delta)
}

/// Atomically write the aliases map to notes directory
pub fn write_alias_map<P: AsRef<Path>>(
    story_root: P,
    alias_map: &HashMap<String, Vec<String>>,
) -> std::io::Result<()> {
    let dir = ensure_notes_dir(&story_root)?;
    let path = dir.join("aliases.json");
    let tmp = dir.join("aliases.json.tmp");
    let content = serde_json::to_string_pretty(alias_map)?;
    std::fs::write(&tmp, content)?;
    std::fs::rename(tmp, path)?;
    Ok(())
}

/// Merge incoming aliases into an existing alias map with conflict detection.
/// Returns a report of changes and conflicts.
pub fn merge_alias_maps(
    base: &mut HashMap<String, Vec<String>>,
    incoming: &HashMap<String, Vec<String>>,
) -> AliasMergeReport {
    let mut added: usize = 0;
    let mut conflicts: Vec<AliasConflict> = Vec::new();

    // Build initial reverse to detect alias conflicts across canonicals
    let mut reverse = build_reverse_alias_map(base);

    let mut canonicals: Vec<_> = incoming.keys().cloned().collect();
    canonicals.sort();
    for canon in canonicals {
        let aliases = incoming.get(&canon).cloned().unwrap_or_default();
        let entry = base.entry(canon.clone()).or_insert_with(Vec::new);
        for alias in aliases {
            if let Some(existing_canon) = reverse.get(&alias) {
                if existing_canon != &canon {
                    conflicts.push(AliasConflict {
                        alias: alias.clone(),
                        existing_canonical: existing_canon.clone(),
                        proposed_canonical: canon.clone(),
                    });
                    continue;
                }
            }
            if !entry.contains(&alias) {
                entry.push(alias.clone());
                added += 1;
                reverse.insert(alias, canon.clone());
            }
        }
        entry.sort();
        entry.dedup();
    }

    AliasMergeReport { added, conflicts }
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AliasConflict {
    pub alias: String,
    pub existing_canonical: String,
    pub proposed_canonical: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AliasMergeReport {
    pub added: usize,
    pub conflicts: Vec<AliasConflict>,
}

