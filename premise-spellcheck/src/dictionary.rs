use std::collections::HashSet;

use crate::symspell::SymSpell;

/// Dictionary that combines SymSpell for standard words with separate membership
/// sets for user-added words and entity names.
///
/// **Memory note:** custom and entity words are deliberately kept OUT of the SymSpell
/// index. SymSpell precomputes all edit-distance-2 deletion variants per word, so
/// injecting thousands of project entities there exploded the `deletes` map — and since
/// the engine runs in WASM (linear memory never shrinks), that bloat became a permanent
/// multi-GB high-water mark on the `.prem` editing path. Membership-only `HashSet`s are
/// O(set size) and are all `is_correct` actually needs; suggestions come from the fixed
/// base dictionary only.
pub struct Dictionary {
    symspell: SymSpell,
    /// User dictionary + project dictionary words (additive across the session).
    custom_words: HashSet<String>,
    /// Entity names (and their split parts). Replaced wholesale by `set_entities`.
    entity_words: HashSet<String>,
}

impl Dictionary {
    pub fn new() -> Self {
        Self {
            symspell: SymSpell::new(2),
            custom_words: HashSet::new(),
            entity_words: HashSet::new(),
        }
    }

    /// Load a frequency-ranked word list (newline-separated "word frequency" pairs).
    pub fn load_wordlist(&mut self, data: &str) {
        self.symspell.load_dictionary(data);
    }

    /// Add a custom word (user dictionary / project dictionary word).
    /// Custom words are always considered correct and won't generate suggestions.
    /// Membership-only — not added to the SymSpell deletes index (see struct docs).
    pub fn add_word(&mut self, word: &str) {
        self.custom_words.insert(word.to_lowercase());
    }

    /// Remove a custom word.
    pub fn remove_word(&mut self, word: &str) {
        self.custom_words.remove(&word.to_lowercase());
    }

    /// Add multiple custom words at once (user/project dictionary).
    pub fn add_words(&mut self, words: &[String]) {
        for word in words {
            self.add_word(word);
        }
    }

    /// Replace the entity-name set, splitting multi-word names into individual words.
    /// E.g., "Maya Chen" registers "maya chen", "maya", and "chen".
    ///
    /// Idempotent: re-calling with the same set leaves memory unchanged (the previous
    /// entity set is cleared first). Entity words are membership-only.
    pub fn set_entity_names(&mut self, entities: &[String]) {
        self.entity_words.clear();
        for entity in entities {
            // The full name (lets multi-word references match as a unit)
            self.entity_words.insert(entity.to_lowercase());
            // Individual words so each token is treated as correctly spelled
            for part in entity.split_whitespace() {
                let clean = part.trim_matches(|c: char| !c.is_alphanumeric());
                if clean.len() >= 2 {
                    self.entity_words.insert(clean.to_lowercase());
                }
            }
        }
    }

    /// Check if a word is known (custom words, entity names, or base dictionary).
    pub fn is_correct(&self, word: &str) -> bool {
        let lower = word.to_lowercase();
        if self.custom_words.contains(&lower) || self.entity_words.contains(&lower) {
            return true;
        }
        self.symspell.is_known(&lower)
    }

    /// Get the frequency of a word from the underlying dictionary.
    /// Returns 0 for unknown words.
    pub fn word_frequency(&self, word: &str) -> u64 {
        self.symspell.get_frequency(word)
    }

    /// Get spelling suggestions for a misspelled word.
    pub fn suggest(&self, word: &str, max: usize) -> Vec<String> {
        self.symspell
            .lookup(word, max)
            .into_iter()
            .map(|s| s.word)
            .collect()
    }
}

impl Default for Dictionary {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_custom_words() {
        let mut dict = Dictionary::new();
        dict.add_word("Kael");
        assert!(dict.is_correct("Kael"));
        assert!(dict.is_correct("kael"));
    }

    #[test]
    fn test_entity_names() {
        let mut dict = Dictionary::new();
        dict.set_entity_names(&["Maya Chen".to_string(), "Dr. Vex".to_string()]);
        assert!(dict.is_correct("Maya"));
        assert!(dict.is_correct("Chen"));
        assert!(dict.is_correct("Vex"));
    }

    #[test]
    fn test_set_entity_names_replaces() {
        let mut dict = Dictionary::new();
        dict.set_entity_names(&["Kael".to_string()]);
        assert!(dict.is_correct("Kael"));

        // Re-setting with a different roster drops the old entity and adds the new one.
        dict.set_entity_names(&["Maya".to_string()]);
        assert!(dict.is_correct("Maya"));
        assert!(!dict.is_correct("Kael"));
    }

    #[test]
    fn test_set_entity_names_idempotent_does_not_touch_base_index() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("hello 1000\nworld 800\n");
        let base_words = dict.symspell.word_count();
        let base_deletes = dict.symspell.delete_key_count();

        // Entity injection must never grow the SymSpell index, no matter how many times
        // it runs — this is the property that keeps WASM memory bounded.
        let entities: Vec<String> =
            (0..500).map(|i| format!("Entity{i} Surname{i}")).collect();
        for _ in 0..10 {
            dict.set_entity_names(&entities);
        }

        assert_eq!(dict.symspell.word_count(), base_words);
        assert_eq!(dict.symspell.delete_key_count(), base_deletes);
        assert!(dict.is_correct("Entity0"));
        assert!(dict.is_correct("Surname499"));
        // Base dictionary suggestions still work for genuine misspellings.
        assert!(dict.suggest("helo", 5).iter().any(|w| w == "hello"));
    }

    #[test]
    fn test_remove_word() {
        let mut dict = Dictionary::new();
        dict.add_word("foo");
        assert!(dict.is_correct("foo"));
        dict.remove_word("foo");
        assert!(!dict.is_correct("foo"));
    }
}
