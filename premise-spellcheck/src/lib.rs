pub mod definitions;
pub mod dictionary;
pub mod fuzzy;
pub mod spellcheck;
pub mod stemming;
mod symspell;
pub mod thesaurus;

#[cfg(feature = "wasm")]
use definitions::DefinitionDictionary;
#[cfg(feature = "wasm")]
use dictionary::Dictionary;
#[cfg(feature = "wasm")]
use fuzzy::FuzzyMatcher;
#[cfg(feature = "wasm")]
use spellcheck::CheckableSpan;
#[cfg(feature = "wasm")]
use thesaurus::Thesaurus;
#[cfg(feature = "wasm")]
use wasm_bindgen::prelude::*;

/// Embedded English word frequency list.
/// Format: "word frequency\n" — loaded at init time.
#[cfg(feature = "wasm")]
const DICTIONARY_DATA: &str = include_str!("../data/en_frequency.txt");

/// The main spellcheck engine exposed to JavaScript via WASM.
///
/// Combines dictionary-based spellchecking with fuzzy entity completion,
/// thesaurus synonym lookup, and definition dictionary lookup.
#[cfg(feature = "wasm")]
#[wasm_bindgen]
pub struct SpellEngine {
    dictionary: Dictionary,
    fuzzy: FuzzyMatcher,
    thesaurus: Thesaurus,
    definitions: DefinitionDictionary,
}

#[cfg(feature = "wasm")]
#[wasm_bindgen]
impl SpellEngine {
    /// Create a new SpellEngine with the embedded English dictionary.
    #[wasm_bindgen(constructor)]
    pub fn new() -> Self {
        let mut dictionary = Dictionary::new();
        dictionary.load_wordlist(DICTIONARY_DATA);

        Self {
            dictionary,
            fuzzy: FuzzyMatcher::new(),
            thesaurus: Thesaurus::new(),
            definitions: DefinitionDictionary::new(),
        }
    }

    /// Load an additional dictionary (newline-separated "word frequency" pairs).
    #[wasm_bindgen(js_name = "loadDictionary")]
    pub fn load_dictionary(&mut self, wordlist: &str) {
        self.dictionary.load_wordlist(wordlist);
    }

    /// Add custom words (entity names, user dictionary).
    /// Accepts a JS string array.
    #[wasm_bindgen(js_name = "addCustomWords")]
    pub fn add_custom_words(&mut self, words: JsValue) -> Result<(), JsValue> {
        let words: Vec<String> = serde_wasm_bindgen::from_value(words)
            .map_err(|e| JsValue::from_str(&format!("Invalid words array: {}", e)))?;
        self.dictionary.add_words(&words);
        Ok(())
    }

    /// Remove a custom word.
    #[wasm_bindgen(js_name = "removeCustomWord")]
    pub fn remove_custom_word(&mut self, word: &str) {
        self.dictionary.remove_word(word);
    }

    /// Set entity names for both spellcheck (as valid words) and fuzzy completion.
    /// Replaces any previously set entities.
    #[wasm_bindgen(js_name = "setEntities")]
    pub fn set_entities(&mut self, entities: JsValue) -> Result<(), JsValue> {
        let entities: Vec<String> = serde_wasm_bindgen::from_value(entities)
            .map_err(|e| JsValue::from_str(&format!("Invalid entities array: {}", e)))?;
        self.dictionary.add_entity_names(&entities);
        self.fuzzy.set_entities(&entities);
        Ok(())
    }

    /// Check text spans for misspellings.
    /// Input: CheckableSpan[] (JSON), Output: Misspelling[] (JSON).
    #[wasm_bindgen(js_name = "checkSpans")]
    pub fn check_spans(&self, spans: JsValue) -> Result<JsValue, JsValue> {
        let spans: Vec<CheckableSpan> = serde_wasm_bindgen::from_value(spans)
            .map_err(|e| JsValue::from_str(&format!("Invalid spans: {}", e)))?;
        let results = spellcheck::check_spans(&self.dictionary, &spans);
        serde_wasm_bindgen::to_value(&results)
            .map_err(|e| JsValue::from_str(&format!("Serialization error: {}", e)))
    }

    /// Get spelling suggestions for a single word.
    #[wasm_bindgen(js_name = "suggest")]
    pub fn suggest(&self, word: &str, max: u32) -> Result<JsValue, JsValue> {
        let suggestions = self.dictionary.suggest(word, max as usize);
        serde_wasm_bindgen::to_value(&suggestions)
            .map_err(|e| JsValue::from_str(&format!("Serialization error: {}", e)))
    }

    /// Complete a prefix against entity names.
    #[wasm_bindgen(js_name = "completePrefix")]
    pub fn complete_prefix(&self, prefix: &str, max: u32) -> Result<JsValue, JsValue> {
        let completions = self.fuzzy.complete_prefix(prefix, max as usize);
        serde_wasm_bindgen::to_value(&completions)
            .map_err(|e| JsValue::from_str(&format!("Serialization error: {}", e)))
    }

    /// Fuzzy match against entity names.
    #[wasm_bindgen(js_name = "fuzzyMatch")]
    pub fn fuzzy_match(&self, query: &str, max: u32) -> Result<JsValue, JsValue> {
        let completions = self.fuzzy.fuzzy_match(query, max as usize);
        serde_wasm_bindgen::to_value(&completions)
            .map_err(|e| JsValue::from_str(&format!("Serialization error: {}", e)))
    }

    /// Check if the thesaurus is available (compiled with `thesaurus` feature).
    #[wasm_bindgen(js_name = "thesaurusAvailable")]
    pub fn thesaurus_available(&self) -> bool {
        self.thesaurus.is_available()
    }

    /// Look up synonyms for a word, ranked by word frequency.
    #[wasm_bindgen(js_name = "synonyms")]
    pub fn synonyms(&self, word: &str, max: u32) -> Result<JsValue, JsValue> {
        let results = self
            .thesaurus
            .lookup_ranked(word, max as usize, |w| self.dictionary.word_frequency(w));
        serde_wasm_bindgen::to_value(&results)
            .map_err(|e| JsValue::from_str(&format!("Serialization error: {}", e)))
    }

    /// Check if the definition dictionary has any sources loaded.
    #[wasm_bindgen(js_name = "dictionaryAvailable")]
    pub fn dictionary_available(&self) -> bool {
        self.definitions.is_loaded()
    }

    /// Load a dictionary source binary (postcard-serialized).
    /// Returns { source, entryCount, totalEntries }.
    #[wasm_bindgen(js_name = "loadDictionarySource")]
    pub fn load_dictionary_source(
        &mut self,
        data: &[u8],
        source_id: &str,
    ) -> Result<JsValue, JsValue> {
        #[cfg(feature = "definitions")]
        {
            let source = match source_id {
                "webster1913" => definitions::DictionarySource::Webster1913,
                "wordnet" => definitions::DictionarySource::WordNet,
                _ => return Err(JsValue::from_str(&format!("Unknown source: {}", source_id))),
            };
            let count = self
                .definitions
                .load_source(data, source)
                .map_err(|e| JsValue::from_str(&e))?;
            serde_wasm_bindgen::to_value(&serde_json::json!({
                "source": source_id,
                "entryCount": count,
                "totalEntries": self.definitions.entry_count(),
            }))
            .map_err(|e| JsValue::from_str(&format!("Serialization error: {}", e)))
        }
        #[cfg(not(feature = "definitions"))]
        {
            let _ = (data, source_id);
            Err(JsValue::from_str("Definitions feature not compiled"))
        }
    }

    /// Look up a word definition across all loaded dictionary sources.
    /// Returns DictionaryEntry or null.
    #[wasm_bindgen(js_name = "define")]
    pub fn define(&self, word: &str) -> Result<JsValue, JsValue> {
        #[cfg(feature = "definitions")]
        {
            let entry = self.definitions.lookup(word);
            serde_wasm_bindgen::to_value(&entry)
                .map_err(|e| JsValue::from_str(&format!("Serialization error: {}", e)))
        }
        #[cfg(not(feature = "definitions"))]
        {
            let _ = word;
            Ok(JsValue::NULL)
        }
    }
}

#[cfg(feature = "wasm")]
impl Default for SpellEngine {
    fn default() -> Self {
        Self::new()
    }
}
