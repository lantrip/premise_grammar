use std::collections::HashMap;

#[cfg(feature = "definitions")]
use serde::{Deserialize, Serialize};

#[cfg(feature = "definitions")]
use crate::stemming::stem_simple;

/// Identifies which dictionary a definition came from.
/// Serialized as lowercase strings to match TypeScript DictionarySourceId.
#[cfg(feature = "definitions")]
#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Eq)]
pub enum DictionarySource {
    #[serde(rename = "webster1913")]
    Webster1913,
    #[serde(rename = "wordnet")]
    WordNet,
}

/// A single definition with its source and optional part of speech.
#[cfg(feature = "definitions")]
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SourcedDefinition {
    pub text: String,
    pub source: DictionarySource,
    pub pos: Option<String>,
}

/// A multi-source dictionary entry for a single word.
#[cfg(feature = "definitions")]
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct DictionaryEntry {
    pub word: String,
    pub definitions: Vec<SourcedDefinition>,
    pub etymology: Option<String>,
    pub pronunciation: Option<String>,
}

/// Runtime-loaded definition dictionary supporting multiple sources.
///
/// Dictionary data is loaded at runtime from pre-processed binary files,
/// not embedded in the WASM binary. Each source can be loaded independently
/// and entries are merged by headword.
#[cfg(feature = "definitions")]
pub struct DefinitionDictionary {
    entries: HashMap<String, DictionaryEntry>,
    loaded_sources: Vec<DictionarySource>,
}

#[cfg(feature = "definitions")]
impl DefinitionDictionary {
    pub fn new() -> Self {
        Self {
            entries: HashMap::new(),
            loaded_sources: vec![],
        }
    }

    pub fn is_loaded(&self) -> bool {
        !self.loaded_sources.is_empty()
    }

    pub fn loaded_sources(&self) -> &[DictionarySource] {
        &self.loaded_sources
    }

    pub fn entry_count(&self) -> usize {
        self.entries.len()
    }

    /// Load a dictionary source binary. Merges into existing entries.
    pub fn load_source(&mut self, data: &[u8], source: DictionarySource) -> Result<usize, String> {
        let new_entries: Vec<(String, DictionaryEntry)> =
            postcard::from_bytes(data).map_err(|e| format!("Failed to deserialize: {}", e))?;
        let count = new_entries.len();

        for (key, entry) in new_entries {
            match self.entries.get_mut(&key) {
                Some(existing) => {
                    // Merge: append definitions from new source
                    existing.definitions.extend(entry.definitions);
                    // Fill in missing metadata (Webster's provides these, WordNet doesn't)
                    if existing.etymology.is_none() {
                        existing.etymology = entry.etymology;
                    }
                    if existing.pronunciation.is_none() {
                        existing.pronunciation = entry.pronunciation;
                    }
                }
                None => {
                    self.entries.insert(key, entry);
                }
            }
        }

        self.loaded_sources.push(source);
        Ok(count)
    }

    /// Lookup with fallback: lowercase -> suffix-stripped.
    pub fn lookup(&self, word: &str) -> Option<&DictionaryEntry> {
        let lower = word.to_lowercase();
        if let Some(entry) = self.entries.get(&lower) {
            return Some(entry);
        }
        // Suffix stripping fallback
        for stripped in stem_simple(&lower) {
            if let Some(entry) = self.entries.get(&stripped) {
                return Some(entry);
            }
        }
        None
    }
}

// --- Stub implementation when definitions feature is disabled ---

#[cfg(not(feature = "definitions"))]
pub struct DefinitionDictionary;

#[cfg(not(feature = "definitions"))]
impl DefinitionDictionary {
    pub fn new() -> Self {
        DefinitionDictionary
    }

    pub fn is_loaded(&self) -> bool {
        false
    }

    pub fn entry_count(&self) -> usize {
        0
    }

    pub fn load_source(&mut self, _data: &[u8], _source_id: &str) -> Result<usize, String> {
        Err("Definitions feature not compiled".to_string())
    }

    pub fn define(&self, _word: &str) -> Option<()> {
        None
    }
}

#[cfg(test)]
#[cfg(feature = "definitions")]
mod tests {
    use super::*;

    fn make_entry(word: &str, defs: Vec<(&str, DictionarySource)>) -> DictionaryEntry {
        DictionaryEntry {
            word: word.to_string(),
            definitions: defs
                .into_iter()
                .map(|(text, source)| SourcedDefinition {
                    text: text.to_string(),
                    source,
                    pos: None,
                })
                .collect(),
            etymology: None,
            pronunciation: None,
        }
    }

    fn make_binary(entries: Vec<(&str, DictionaryEntry)>) -> Vec<u8> {
        let data: Vec<(String, DictionaryEntry)> = entries
            .into_iter()
            .map(|(k, v)| (k.to_string(), v))
            .collect();
        postcard::to_allocvec(&data).unwrap()
    }

    #[test]
    fn test_load_and_lookup() {
        let mut dict = DefinitionDictionary::new();
        assert!(!dict.is_loaded());

        let entries = vec![(
            "ephemeral",
            make_entry(
                "Ephemeral",
                vec![(
                    "Short-lived; existing for a short time only.",
                    DictionarySource::Webster1913,
                )],
            ),
        )];
        let data = make_binary(entries);
        let count = dict
            .load_source(&data, DictionarySource::Webster1913)
            .unwrap();

        assert_eq!(count, 1);
        assert!(dict.is_loaded());
        assert_eq!(dict.entry_count(), 1);

        let entry = dict.lookup("ephemeral").unwrap();
        assert_eq!(entry.word, "Ephemeral");
        assert_eq!(entry.definitions.len(), 1);
        assert_eq!(entry.definitions[0].source, DictionarySource::Webster1913);
    }

    #[test]
    fn test_case_insensitive_lookup() {
        let mut dict = DefinitionDictionary::new();
        let entries = vec![(
            "hello",
            make_entry(
                "Hello",
                vec![("A greeting.", DictionarySource::Webster1913)],
            ),
        )];
        let data = make_binary(entries);
        dict.load_source(&data, DictionarySource::Webster1913)
            .unwrap();

        assert!(dict.lookup("Hello").is_some());
        assert!(dict.lookup("HELLO").is_some());
        assert!(dict.lookup("hello").is_some());
    }

    #[test]
    fn test_suffix_fallback() {
        let mut dict = DefinitionDictionary::new();
        let entries = vec![(
            "run",
            make_entry(
                "Run",
                vec![("To move swiftly on foot.", DictionarySource::Webster1913)],
            ),
        )];
        let data = make_binary(entries);
        dict.load_source(&data, DictionarySource::Webster1913)
            .unwrap();

        // "running" should fall back to "run" via stem_simple
        let entry = dict.lookup("running").unwrap();
        assert_eq!(entry.word, "Run");
    }

    #[test]
    fn test_merge_sources() {
        let mut dict = DefinitionDictionary::new();

        // Load Webster's first
        let webster = vec![(
            "ephemeral",
            DictionaryEntry {
                word: "Ephemeral".to_string(),
                definitions: vec![SourcedDefinition {
                    text: "Short-lived.".to_string(),
                    source: DictionarySource::Webster1913,
                    pos: None,
                }],
                etymology: Some("Gr. ephemeros".to_string()),
                pronunciation: Some("/ɛˈfɛm.ər.əl/".to_string()),
            },
        )];
        let data = make_binary(webster);
        dict.load_source(&data, DictionarySource::Webster1913)
            .unwrap();

        // Load WordNet second
        let wordnet = vec![(
            "ephemeral",
            DictionaryEntry {
                word: "ephemeral".to_string(),
                definitions: vec![SourcedDefinition {
                    text: "Lasting a very short time.".to_string(),
                    source: DictionarySource::WordNet,
                    pos: Some("adj".to_string()),
                }],
                etymology: None,
                pronunciation: None,
            },
        )];
        let data = make_binary(wordnet);
        dict.load_source(&data, DictionarySource::WordNet).unwrap();

        // Should have merged entry with both definitions
        let entry = dict.lookup("ephemeral").unwrap();
        assert_eq!(entry.definitions.len(), 2);
        assert_eq!(entry.definitions[0].source, DictionarySource::Webster1913);
        assert_eq!(entry.definitions[1].source, DictionarySource::WordNet);

        // Etymology preserved from Webster's (not overwritten by WordNet's None)
        assert_eq!(entry.etymology, Some("Gr. ephemeros".to_string()));
        assert_eq!(entry.pronunciation, Some("/ɛˈfɛm.ər.əl/".to_string()));
    }

    #[test]
    fn test_unknown_word() {
        let mut dict = DefinitionDictionary::new();
        let entries = vec![(
            "hello",
            make_entry(
                "Hello",
                vec![("A greeting.", DictionarySource::Webster1913)],
            ),
        )];
        let data = make_binary(entries);
        dict.load_source(&data, DictionarySource::Webster1913)
            .unwrap();

        assert!(dict.lookup("xyzzyplugh").is_none());
    }

    #[test]
    fn test_not_loaded() {
        let dict = DefinitionDictionary::new();
        assert!(!dict.is_loaded());
        assert_eq!(dict.entry_count(), 0);
        assert!(dict.lookup("anything").is_none());
    }
}
