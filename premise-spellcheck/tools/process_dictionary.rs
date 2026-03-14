//! CLI tool to convert dictionary source data into optimized postcard binaries.
//!
//! Usage:
//!   process-dictionary --source webster1913 --input /path/to/dictionary.json --output dict-webster1913.bin
//!   process-dictionary --source wordnet --input /path/to/english-wordnet.xml --output dict-wordnet.bin

use premise_spellcheck::definitions::{DictionaryEntry, DictionarySource, SourcedDefinition};
use std::collections::HashMap;
use std::fs;
use std::path::PathBuf;

fn main() {
    let args: Vec<String> = std::env::args().collect();

    let mut source = String::new();
    let mut input = String::new();
    let mut output = String::new();

    let mut i = 1;
    while i < args.len() {
        match args[i].as_str() {
            "--source" => {
                i += 1;
                source = args[i].clone();
            }
            "--input" => {
                i += 1;
                input = args[i].clone();
            }
            "--output" => {
                i += 1;
                output = args[i].clone();
            }
            _ => {
                eprintln!("Unknown argument: {}", args[i]);
                std::process::exit(1);
            }
        }
        i += 1;
    }

    if source.is_empty() || input.is_empty() || output.is_empty() {
        eprintln!(
            "Usage: process-dictionary --source webster1913|wordnet --input <path> --output <path>"
        );
        std::process::exit(1);
    }

    match source.as_str() {
        "webster1913" => process_webster(&input, &output),
        "wordnet" => process_wordnet(&input, &output),
        _ => {
            eprintln!(
                "Unknown source: {}. Expected 'webster1913' or 'wordnet'",
                source
            );
            std::process::exit(1);
        }
    }
}

/// Process Webster's 1913 dictionary from ssvivian/WebstersDictionary.
///
/// Input: single dictionary.json file with array of { word, pos, definitions }.
/// Duplicate headwords (same word with different POS) are merged into one entry.
fn process_webster(input_path: &str, output_path: &str) {
    eprintln!("Processing Webster's 1913 from: {}", input_path);
    let mut entries: HashMap<String, DictionaryEntry> = HashMap::new();

    let content = fs::read_to_string(input_path)
        .unwrap_or_else(|e| panic!("Failed to read {}: {}", input_path, e));

    let raw_entries: Vec<serde_json::Value> = serde_json::from_str(&content)
        .unwrap_or_else(|e| panic!("Failed to parse JSON: {}", e));

    eprintln!("Parsed {} raw entries", raw_entries.len());

    for raw in raw_entries {
        let word = match raw.get("word").and_then(|v| v.as_str()) {
            Some(w) => w.to_string(),
            None => continue,
        };

        let key = word.to_lowercase();

        // POS from Webster's: "n.", "v.", "a.", "adv.", etc.
        let pos = raw
            .get("pos")
            .and_then(|v| v.as_str())
            .filter(|s| !s.is_empty())
            .map(|s| normalize_webster_pos(s));

        let definitions: Vec<SourcedDefinition> = raw
            .get("definitions")
            .and_then(|v| v.as_array())
            .map(|arr| {
                arr.iter()
                    .filter_map(|d| d.as_str())
                    .map(|text| {
                        let text = clean_definition(text);
                        SourcedDefinition {
                            text,
                            source: DictionarySource::Webster1913,
                            pos: pos.clone(),
                        }
                    })
                    .collect()
            })
            .unwrap_or_default();

        if definitions.is_empty() {
            continue;
        }

        let etymology = raw
            .get("etymology")
            .and_then(|v| v.as_str())
            .filter(|s| !s.is_empty())
            .map(|s| truncate_str(s, 2000).to_string());

        let pronunciation = raw
            .get("pronunciation")
            .and_then(|v| v.as_str())
            .filter(|s| !s.is_empty())
            .map(|s| s.to_string());

        match entries.get_mut(&key) {
            Some(existing) => {
                existing.definitions.extend(definitions);
                if existing.etymology.is_none() {
                    existing.etymology = etymology;
                }
                if existing.pronunciation.is_none() {
                    existing.pronunciation = pronunciation;
                }
            }
            None => {
                entries.insert(
                    key,
                    DictionaryEntry {
                        word,
                        definitions,
                        etymology,
                        pronunciation,
                    },
                );
            }
        }
    }

    write_output(entries, output_path, "Webster's 1913");
}

fn normalize_webster_pos(pos: &str) -> String {
    match pos.trim().trim_end_matches('.') {
        "n" => "noun".to_string(),
        "v" => "verb".to_string(),
        "a" => "adj".to_string(),
        "adv" => "adv".to_string(),
        "prep" => "prep".to_string(),
        "conj" => "conj".to_string(),
        "interj" => "interj".to_string(),
        "pron" => "pron".to_string(),
        "p" => "participle".to_string(),
        other => other.to_string(),
    }
}

/// Process English WordNet XML (WN-LMF format from en-word.net).
///
/// Two-pass approach:
/// 1. Collect synset definitions: synset_id -> (definition, pos)
/// 2. Map lemmas to their synsets via LexicalEntry/Sense elements
fn process_wordnet(input_path: &str, output_path: &str) {
    use quick_xml::events::Event;
    use quick_xml::reader::Reader;

    eprintln!("Processing English WordNet from: {}", input_path);
    let content = fs::read_to_string(input_path)
        .unwrap_or_else(|e| panic!("Failed to read {}: {}", input_path, e));

    // Pass 1: Collect synset definitions
    eprintln!("Pass 1: Collecting synset definitions...");
    let mut synset_defs: HashMap<String, (String, String)> = HashMap::new(); // id -> (definition, pos)

    {
        let mut reader = Reader::from_str(&content);
        let mut buf = Vec::new();
        let mut current_synset_id = String::new();
        let mut current_synset_pos = String::new();
        let mut in_definition = false;
        let mut definition_text = String::new();

        loop {
            match reader.read_event_into(&mut buf) {
                Ok(Event::Start(e)) | Ok(Event::Empty(e)) => {
                    match e.name().as_ref() {
                        b"Synset" => {
                            current_synset_id.clear();
                            current_synset_pos.clear();
                            for attr in e.attributes().flatten() {
                                match attr.key.as_ref() {
                                    b"id" => {
                                        current_synset_id =
                                            String::from_utf8_lossy(&attr.value).to_string();
                                    }
                                    b"partOfSpeech" => {
                                        current_synset_pos =
                                            normalize_wordnet_pos(&String::from_utf8_lossy(&attr.value));
                                    }
                                    _ => {}
                                }
                            }
                        }
                        b"Definition" => {
                            in_definition = true;
                            definition_text.clear();
                        }
                        _ => {}
                    }
                }
                Ok(Event::Text(e)) => {
                    if in_definition {
                        definition_text.push_str(&e.unescape().unwrap_or_default());
                    }
                }
                Ok(Event::End(e)) => {
                    if e.name().as_ref() == b"Definition" {
                        in_definition = false;
                        if !current_synset_id.is_empty() && !definition_text.is_empty() {
                            let def = clean_definition(&definition_text);
                            if !def.is_empty() {
                                synset_defs.insert(
                                    current_synset_id.clone(),
                                    (def, current_synset_pos.clone()),
                                );
                            }
                        }
                    }
                }
                Ok(Event::Eof) => break,
                Err(e) => {
                    eprintln!("XML parse error: {}", e);
                    break;
                }
                _ => {}
            }
            buf.clear();
        }
    }
    eprintln!("  Found {} synset definitions", synset_defs.len());

    // Pass 2: Map lemmas to synsets
    eprintln!("Pass 2: Mapping lemmas to definitions...");
    let mut entries: HashMap<String, DictionaryEntry> = HashMap::new();

    {
        let mut reader = Reader::from_str(&content);
        let mut buf = Vec::new();
        let mut current_lemma = String::new();
        let mut current_pos = String::new();

        loop {
            match reader.read_event_into(&mut buf) {
                Ok(Event::Start(e)) | Ok(Event::Empty(e)) => {
                    match e.name().as_ref() {
                        b"LexicalEntry" => {
                            current_lemma.clear();
                            current_pos.clear();
                        }
                        b"Lemma" => {
                            for attr in e.attributes().flatten() {
                                match attr.key.as_ref() {
                                    b"writtenForm" => {
                                        current_lemma =
                                            String::from_utf8_lossy(&attr.value).to_string();
                                    }
                                    b"partOfSpeech" => {
                                        current_pos = normalize_wordnet_pos(
                                            &String::from_utf8_lossy(&attr.value),
                                        );
                                    }
                                    _ => {}
                                }
                            }
                        }
                        b"Sense" => {
                            if !current_lemma.is_empty() {
                                let mut synset_id = String::new();
                                for attr in e.attributes().flatten() {
                                    if attr.key.as_ref() == b"synset" {
                                        synset_id =
                                            String::from_utf8_lossy(&attr.value).to_string();
                                    }
                                }
                                if let Some((def_text, _)) = synset_defs.get(&synset_id) {
                                    let key = current_lemma.to_lowercase();
                                    let def = SourcedDefinition {
                                        text: def_text.clone(),
                                        source: DictionarySource::WordNet,
                                        pos: if current_pos.is_empty() {
                                            None
                                        } else {
                                            Some(current_pos.clone())
                                        },
                                    };

                                    match entries.get_mut(&key) {
                                        Some(existing) => {
                                            existing.definitions.push(def);
                                        }
                                        None => {
                                            entries.insert(
                                                key,
                                                DictionaryEntry {
                                                    word: current_lemma.clone(),
                                                    definitions: vec![def],
                                                    etymology: None,
                                                    pronunciation: None,
                                                },
                                            );
                                        }
                                    }
                                }
                            }
                        }
                        _ => {}
                    }
                }
                Ok(Event::Eof) => break,
                Err(e) => {
                    eprintln!("XML parse error: {}", e);
                    break;
                }
                _ => {}
            }
            buf.clear();
        }
    }

    write_output(entries, output_path, "English WordNet");
}

fn normalize_wordnet_pos(pos: &str) -> String {
    match pos.trim() {
        "n" => "noun".to_string(),
        "v" => "verb".to_string(),
        "a" | "s" => "adj".to_string(),
        "r" => "adv".to_string(),
        other => other.to_string(),
    }
}

fn clean_definition(text: &str) -> String {
    let text = text
        .chars()
        .filter(|c| !c.is_control() || *c == '\n')
        .collect::<String>();
    let text = text.split_whitespace().collect::<Vec<&str>>().join(" ");
    truncate_str(&text, 2000).to_string()
}

fn truncate_str(s: &str, max_len: usize) -> &str {
    if s.len() <= max_len {
        return s;
    }
    let mut end = max_len;
    while !s.is_char_boundary(end) && end > 0 {
        end -= 1;
    }
    &s[..end]
}

fn write_output(entries: HashMap<String, DictionaryEntry>, output_path: &str, source_name: &str) {
    let mut sorted: Vec<(String, DictionaryEntry)> = entries.into_iter().collect();
    sorted.sort_by(|a, b| a.0.cmp(&b.0));

    let total_defs: usize = sorted.iter().map(|(_, e)| e.definitions.len()).sum();
    eprintln!(
        "{}: {} entries, {} total definitions",
        source_name,
        sorted.len(),
        total_defs
    );

    let data =
        postcard::to_allocvec(&sorted).unwrap_or_else(|e| panic!("Failed to serialize: {}", e));

    eprintln!(
        "Binary size: {} bytes ({:.1} MB)",
        data.len(),
        data.len() as f64 / 1_048_576.0
    );

    if let Some(parent) = PathBuf::from(output_path).parent() {
        fs::create_dir_all(parent).ok();
    }

    fs::write(output_path, &data)
        .unwrap_or_else(|e| panic!("Failed to write {}: {}", output_path, e));

    eprintln!("Wrote: {}", output_path);
}
