use std::collections::HashSet;

use crate::symspell::SymSpell;

/// Dictionary that combines SymSpell for standard words with a custom word set
/// for entity names and user-added words.
pub struct Dictionary {
    symspell: SymSpell,
    custom_words: HashSet<String>,
}

impl Dictionary {
    pub fn new() -> Self {
        Self {
            symspell: SymSpell::new(2),
            custom_words: HashSet::new(),
        }
    }

    /// Load a frequency-ranked word list (newline-separated "word frequency" pairs).
    pub fn load_wordlist(&mut self, data: &str) {
        self.symspell.load_dictionary(data);
    }

    /// Add a custom word (entity name, user dictionary word).
    /// Custom words are always considered correct and won't generate suggestions.
    pub fn add_word(&mut self, word: &str) {
        let lower = word.to_lowercase();
        self.custom_words.insert(lower.clone());
        self.symspell.add_word(&lower);
    }

    /// Remove a custom word.
    pub fn remove_word(&mut self, word: &str) {
        let lower = word.to_lowercase();
        self.custom_words.remove(&lower);
        self.symspell.remove_word(&lower);
    }

    /// Add multiple custom words at once (e.g., entity names).
    pub fn add_words(&mut self, words: &[String]) {
        for word in words {
            self.add_word(word);
        }
    }

    /// Add entity names, splitting multi-word names into individual words.
    /// E.g., "Maya Chen" adds both "maya" and "chen".
    pub fn add_entity_names(&mut self, entities: &[String]) {
        for entity in entities {
            // Add the full name for fuzzy matching
            self.add_word(entity);
            // Add individual words for spellcheck
            for part in entity.split_whitespace() {
                // Strip common punctuation
                let clean = part.trim_matches(|c: char| !c.is_alphanumeric());
                if clean.len() >= 2 {
                    self.add_word(clean);
                }
            }
        }
    }

    /// Check if a word is known (in standard dictionary or custom words).
    pub fn is_correct(&self, word: &str) -> bool {
        let lower = word.to_lowercase();
        if self.custom_words.contains(&lower) {
            return true;
        }
        self.symspell.is_known(&lower)
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
        dict.add_entity_names(&["Maya Chen".to_string(), "Dr. Vex".to_string()]);
        assert!(dict.is_correct("Maya"));
        assert!(dict.is_correct("Chen"));
        assert!(dict.is_correct("Vex"));
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
