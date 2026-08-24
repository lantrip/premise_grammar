use std::collections::HashSet;

use crate::normalize;
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
        self.custom_words.insert(normalize::lookup_key(word));
    }

    /// Remove a custom word.
    pub fn remove_word(&mut self, word: &str) {
        self.custom_words.remove(&normalize::lookup_key(word));
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
    /// Hyphenated parts register both as a unit and per sub-part, so
    /// "Maya Chen-Ortiz" registers "maya chen-ortiz", "maya", "chen-ortiz",
    /// "chen" and "ortiz" — prose that says only "Chen" is accepted, while the
    /// tokenizer's whole-compound lookup can still match "Chen-Ortiz" as a unit
    /// (the base word list contains no hyphenated entries at all).
    ///
    /// Idempotent: re-calling with the same set leaves memory unchanged (the previous
    /// entity set is cleared first). Entity words are membership-only.
    pub fn set_entity_names(&mut self, entities: &[String]) {
        self.entity_words.clear();
        for entity in entities {
            // The full name (lets multi-word references match as a unit)
            self.entity_words.insert(normalize::lookup_key(entity));
            // Individual words so each token is treated as correctly spelled
            for part in entity.split_whitespace() {
                let clean = part.trim_matches(|c: char| !c.is_alphanumeric());
                if clean.chars().count() >= 2 {
                    self.entity_words.insert(normalize::lookup_key(clean));
                }
                // `trim_matches` keeps internal hyphens, so also register the
                // sides of a hyphenated surname individually.
                if clean.contains('-') {
                    for sub in clean.split('-') {
                        if sub.chars().count() >= 2 {
                            self.entity_words.insert(normalize::lookup_key(sub));
                        }
                    }
                }
            }
        }
    }

    /// Check if a word is known (custom words, entity names, or base dictionary).
    pub fn is_correct(&self, word: &str) -> bool {
        self.is_correct_key(&normalize::lookup_key(word))
    }

    /// Membership test against an already-normalized key (see `normalize::lookup_key`).
    fn is_correct_key(&self, key: &str) -> bool {
        if self.custom_words.contains(key) || self.entity_words.contains(key) {
            return true;
        }
        self.symspell.is_known(key)
    }

    /// True if `word` is known, allowing for an English possessive suffix.
    ///
    /// `tree's` → `tree`, `Cedar’s` → `cedar`, `squirrels'` → `squirrels`. The
    /// full form is tried FIRST so that word-list contractions (`it's`, `he's`,
    /// `let's` — all 89 apostrophe entries in the base list are of this kind)
    /// win over the possessive reading.
    ///
    /// Possessives are derived here rather than stored: minting a `cedar's` for
    /// every entity would double a large project's roster for no lookup benefit.
    pub fn is_known_allowing_possessive(&self, word: &str) -> bool {
        let key = normalize::lookup_key(word);
        if self.is_correct_key(&key) {
            return true;
        }
        match strip_possessive(&key) {
            Some(base) if !base.is_empty() => self.is_correct_key(base),
            _ => false,
        }
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

/// Strip an English possessive suffix from an already-normalized lookup key.
/// `tree's` → `tree` (singular), `squirrels'` → `squirrels` (plural).
fn strip_possessive(key: &str) -> Option<&str> {
    if let Some(base) = key.strip_suffix("'s") {
        return Some(base);
    }
    key.strip_suffix('\'')
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
        let entities: Vec<String> = (0..500).map(|i| format!("Entity{i} Surname{i}")).collect();
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
    fn test_lookup_folds_curly_apostrophe() {
        let mut dict = Dictionary::new();
        dict.add_word("Kael\u{2019}s");
        // Stored folded, so either spelling of the apostrophe matches.
        assert!(dict.is_correct("Kael's"));
        assert!(dict.is_correct("kael\u{2019}s"));
    }

    #[test]
    fn test_entity_hyphen_subparts() {
        let mut dict = Dictionary::new();
        dict.set_entity_names(&["Maya Chen-Ortiz".to_string()]);
        assert!(dict.is_correct("Maya"));
        assert!(
            dict.is_correct("Chen-Ortiz"),
            "compound should match as a unit"
        );
        assert!(dict.is_correct("Chen"));
        assert!(dict.is_correct("Ortiz"));
    }

    #[test]
    fn test_is_known_allowing_possessive() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("tree 100\nsquirrels 50\n");
        dict.set_entity_names(&["Cedar".to_string()]);

        assert!(dict.is_known_allowing_possessive("tree's"));
        assert!(dict.is_known_allowing_possessive("tree\u{2019}s"));
        assert!(dict.is_known_allowing_possessive("Cedar's"));
        assert!(dict.is_known_allowing_possessive("squirrels'"));
        assert!(!dict.is_known_allowing_possessive("treee's"));
    }

    #[test]
    fn test_wordlist_contraction_wins_over_possessive_reading() {
        let mut dict = Dictionary::new();
        // Note: "it" itself is NOT in the list, only the contraction.
        dict.load_wordlist("it's 5000\n");
        assert!(dict.is_known_allowing_possessive("it's"));
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
