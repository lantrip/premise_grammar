use super::schema::*;
use std::collections::{BTreeMap, HashSet};
use std::fs;
use std::io::{BufRead, BufReader, Write};
use std::path::{Path, PathBuf};

const NOTES_DIR: &str = ".premise-notes";
const SCHEMA_VERSION: &str = "1.0";

/// Get the notes directory for a given story root
pub fn get_notes_dir<P: AsRef<Path>>(story_root: P) -> PathBuf {
    story_root.as_ref().join(NOTES_DIR)
}

/// Ensure the notes directory exists
pub fn ensure_notes_dir<P: AsRef<Path>>(story_root: P) -> std::io::Result<PathBuf> {
    let notes_dir = get_notes_dir(story_root);
    fs::create_dir_all(&notes_dir)?;
    Ok(notes_dir)
}

/// Read all records from a JSONL file
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

/// Append a single record to a JSONL file
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

/// Append multiple records to a JSONL file
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

/// Write records to a JSONL file (overwrites existing)
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

/// Read the notes index (JSON)
pub fn read_index<P: AsRef<Path>>(story_root: P) -> std::io::Result<Option<NotesIndex>> {
    let index_path = get_notes_dir(story_root).join("index.json");
    if !index_path.exists() {
        return Ok(None);
    }
    let content = fs::read_to_string(index_path)?;
    let index = serde_json::from_str(&content)?;
    Ok(Some(index))
}

/// Write the notes index (JSON)
pub fn write_index<P: AsRef<Path>>(story_root: P, index: &NotesIndex) -> std::io::Result<()> {
    let notes_dir = ensure_notes_dir(&story_root)?;
    let index_path = notes_dir.join("index.json");
    let content = serde_json::to_string_pretty(index)?;
    fs::write(index_path, content)?;
    Ok(())
}

/// Read notes metadata (JSON)
pub fn read_metadata<P: AsRef<Path>>(story_root: P) -> std::io::Result<Option<NotesMetadata>> {
    let metadata_path = get_notes_dir(story_root).join("metadata.json");
    if !metadata_path.exists() {
        return Ok(None);
    }
    let content = fs::read_to_string(metadata_path)?;
    let metadata = serde_json::from_str(&content)?;
    Ok(Some(metadata))
}

/// Write notes metadata (JSON)
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

/// Initialize notes directory with default metadata
pub fn initialize_notes<P: AsRef<Path>>(story_root: P, title: Option<String>) -> std::io::Result<()> {
    let notes_dir = ensure_notes_dir(&story_root)?;

    // Create default metadata if it doesn't exist
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

    // Create empty JSONL files if they don't exist
    let files = ["beats.jsonl", "facts.jsonl", "timeline.jsonl", "consistency.jsonl"];
    for file in &files {
        let file_path = notes_dir.join(file);
        if !file_path.exists() {
            fs::File::create(file_path)?;
        }
    }

    Ok(())
}

/// Read all beats from the notes directory
pub fn read_beats<P: AsRef<Path>>(story_root: P) -> std::io::Result<Vec<Beat>> {
    let beats_path = get_notes_dir(story_root).join("beats.jsonl");
    read_jsonl(&beats_path)
}

/// Append beats to the notes directory
pub fn append_beats<P: AsRef<Path>>(story_root: P, beats: &[Beat]) -> std::io::Result<()> {
    ensure_notes_dir(&story_root)?;
    let beats_path = get_notes_dir(story_root).join("beats.jsonl");
    append_many_jsonl(&beats_path, beats)
}

/// Read all facts from the notes directory
pub fn read_facts<P: AsRef<Path>>(story_root: P) -> std::io::Result<Vec<Fact>> {
    let facts_path = get_notes_dir(story_root).join("facts.jsonl");
    read_jsonl(&facts_path)
}

/// Append facts to the notes directory
pub fn append_facts<P: AsRef<Path>>(story_root: P, facts: &[Fact]) -> std::io::Result<()> {
    ensure_notes_dir(&story_root)?;
    let facts_path = get_notes_dir(story_root).join("facts.jsonl");
    append_many_jsonl(&facts_path, facts)
}

/// Read timeline events
pub fn read_timeline<P: AsRef<Path>>(story_root: P) -> std::io::Result<Vec<TimelineEvent>> {
    let timeline_path = get_notes_dir(story_root).join("timeline.jsonl");
    read_jsonl(&timeline_path)
}

/// Read consistency entries
pub fn read_consistency<P: AsRef<Path>>(story_root: P) -> std::io::Result<Vec<ConsistencyEntry>> {
    let consistency_path = get_notes_dir(story_root).join("consistency.jsonl");
    read_jsonl(&consistency_path)
}

/// Generate a unique ID for a record
pub fn generate_id(prefix: &str) -> String {
    use std::time::{SystemTime, UNIX_EPOCH};
    let timestamp = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_millis();
    let random = rand::random::<u32>();
    format!("{}{:x}{:x}", prefix, timestamp, random)
}

/// Rebuild the index from all JSONL files
pub fn rebuild_index<P: AsRef<Path>>(story_root: P) -> std::io::Result<NotesIndex> {
    let story_root_ref = story_root.as_ref();
    let beats = read_beats(story_root_ref)?;
    let facts = read_facts(story_root_ref)?;
    let timeline = read_timeline(story_root_ref)?;
    let consistency = read_consistency(story_root_ref)?;

    let mut entity_index: BTreeMap<String, Vec<String>> = BTreeMap::new();
    let mut file_index: BTreeMap<String, Vec<String>> = BTreeMap::new();
    let mut entities_tracked = HashSet::new();

    // Index beats
    for beat in &beats {
        if !beat.file.is_empty() {
            file_index
                .entry(beat.file.clone())
                .or_insert_with(Vec::new)
                .push(beat.id.clone());
        }
        for entity in &beat.entities {
            entity_index
                .entry(entity.clone())
                .or_insert_with(Vec::new)
                .push(beat.id.clone());
            entities_tracked.insert(entity.clone());
        }
    }

    // Index facts
    for fact in &facts {
        if let Some(entity) = &fact.entity {
            entity_index
                .entry(entity.clone())
                .or_insert_with(Vec::new)
                .push(fact.id.clone());
            entities_tracked.insert(entity.clone());
        }
        if let Some(entities) = &fact.entities {
            for entity in entities {
                entity_index
                    .entry(entity.clone())
                    .or_insert_with(Vec::new)
                    .push(fact.id.clone());
                entities_tracked.insert(entity.clone());
            }
        }
        for evidence in &fact.evidence {
            if let Some(file) = evidence.split(':').next() {
                file_index
                    .entry(file.to_string())
                    .or_insert_with(Vec::new)
                    .push(fact.id.clone());
            }
        }
    }

    let index = NotesIndex {
        schema_version: SCHEMA_VERSION.to_string(),
        story_root: story_root_ref
            .to_str()
            .unwrap_or_default()
            .to_string(),
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

/// Get notes directory status
pub fn get_notes_status<P: AsRef<Path>>(
    story_root: P,
) -> std::io::Result<(bool, bool, Option<NotesStats>)> {
    let notes_dir = get_notes_dir(&story_root);
    let exists = notes_dir.exists();
    if !exists {
        return Ok((false, false, None));
    }

    let metadata = read_metadata(&story_root)?;
    let initialized = metadata.is_some();

    if initialized {
        let index = read_index(&story_root)?;
        let stats = index.map(|i| i.stats);
        return Ok((true, true, stats));
    }

    Ok((true, false, None))
}
