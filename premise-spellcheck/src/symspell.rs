use std::collections::HashMap;

/// Default prefix length for delete generation. Classic SymSpell uses 7: deletes
/// are computed only over the first `prefix_length` characters of each term, which
/// bounds the deletes table to a near-constant per word instead of growing with
/// word length. Over the ~314K-word English dictionary this is the difference
/// between a ~2.1GB and a few-hundred-MB index. Must be ≥ max_edit_distance + 1.
const DEFAULT_PREFIX_LENGTH: usize = 7;

/// Symmetric Delete spelling correction algorithm.
///
/// Pre-computes deletion variants within `max_edit_distance` (over each term's
/// `prefix_length`-char prefix) at load time, enabling O(1) lookups and fast
/// suggestion generation.
///
/// Memory: words are interned once into `words` and referenced everywhere else by
/// `u32` index — the `deletes` buckets hold indices, NOT cloned word strings, so a
/// word that lands in N delete buckets costs N×4 bytes, not N×(string + freq).
pub struct SymSpell {
    max_edit_distance: usize,
    prefix_length: usize,
    /// Maps a delete variant → indices into `words` of terms that produce it.
    deletes: HashMap<String, Vec<u32>>,
    /// Interned terms: index → (word, frequency). The single owner of word strings.
    words: Vec<(String, u64)>,
    /// Exact word → index, for is_known / get_frequency and add-time dedup.
    word_index: HashMap<String, u32>,
}

impl SymSpell {
    pub fn new(max_edit_distance: usize) -> Self {
        Self {
            max_edit_distance,
            prefix_length: DEFAULT_PREFIX_LENGTH.max(max_edit_distance + 1),
            deletes: HashMap::new(),
            words: Vec::new(),
            word_index: HashMap::new(),
        }
    }

    /// The prefix over which deletes are generated: the whole word when short
    /// enough, else its first `prefix_length` characters (char-aware).
    fn prefix_key(&self, word: &str) -> String {
        if word.chars().count() <= self.prefix_length {
            word.to_string()
        } else {
            word.chars().take(self.prefix_length).collect()
        }
    }

    /// Load words from a newline-separated list of "word frequency" pairs.
    /// Lines without a frequency default to 1.
    pub fn load_dictionary(&mut self, data: &str) {
        for line in data.lines() {
            let line = line.trim();
            if line.is_empty() {
                continue;
            }
            let mut parts = line.split_whitespace();
            let word = match parts.next() {
                Some(w) => w.to_lowercase(),
                None => continue,
            };
            let freq: u64 = parts.next().and_then(|f| f.parse().ok()).unwrap_or(1);
            self.add_word_with_freq(&word, freq);
        }
    }

    /// Add a single word with a given frequency.
    pub fn add_word_with_freq(&mut self, word: &str, freq: u64) {
        let lower = word.to_lowercase();

        // Intern the word once. A repeat just accumulates frequency — its delete
        // variants are already in the table, so don't re-add them (that would
        // duplicate index entries and re-bloat the buckets).
        if let Some(&i) = self.word_index.get(&lower) {
            self.words[i as usize].1 += freq;
            return;
        }
        let idx = self.words.len() as u32;
        self.words.push((lower.clone(), freq));
        self.word_index.insert(lower.clone(), idx);

        // Generate deletes over the prefix only (the prefix_length cap), and store
        // the term's index — never a cloned string — in each bucket.
        let key = self.prefix_key(&lower);
        for delete in self.edits(&key, self.max_edit_distance) {
            self.deletes.entry(delete).or_default().push(idx);
        }
        // The prefix key itself is the distance-0 delete.
        self.deletes.entry(key).or_default().push(idx);
    }

    /// Check if a word is in the dictionary (case-insensitive).
    pub fn is_known(&self, word: &str) -> bool {
        self.word_index.contains_key(&word.to_lowercase())
    }

    /// Get the frequency of a word (case-insensitive). Returns 0 if unknown.
    pub fn get_frequency(&self, word: &str) -> u64 {
        self.word_index
            .get(&word.to_lowercase())
            .map(|&i| self.words[i as usize].1)
            .unwrap_or(0)
    }

    /// Number of distinct words in the index. Exposed for memory-regression tests.
    #[cfg(test)]
    pub fn word_count(&self) -> usize {
        self.words.len()
    }

    /// Number of distinct delete-variant keys in the index. Exposed for
    /// memory-regression tests — this is the structure that bloated WASM memory.
    #[cfg(test)]
    pub fn delete_key_count(&self) -> usize {
        self.deletes.len()
    }

    /// Get spelling suggestions for a word, ranked by edit distance then frequency.
    pub fn lookup(&self, input: &str, max_results: usize) -> Vec<Suggestion> {
        let input_lower = input.to_lowercase();

        // Exact match — word is correct
        if self.word_index.contains_key(&input_lower) {
            return vec![];
        }

        // Candidates keyed by word index; the full-string edit distance is
        // deterministic for a given (input, candidate) pair, so first-write wins.
        let mut candidates: HashMap<u32, Suggestion> = HashMap::new();

        // Generate deletes of the input's prefix (mirrors the index side) and look
        // them up. Candidates are then verified against the FULL word, so the
        // prefix cap only narrows which terms are *found*, not the distance.
        let key = self.prefix_key(&input_lower);
        let mut all_variants = self.edits(&key, self.max_edit_distance);
        all_variants.push(key);

        for variant in &all_variants {
            if let Some(indices) = self.deletes.get(variant) {
                for &wi in indices {
                    if candidates.contains_key(&wi) {
                        continue;
                    }
                    let (dict_word, freq) = &self.words[wi as usize];
                    let dist = edit_distance(&input_lower, dict_word);
                    if dist <= self.max_edit_distance {
                        candidates.insert(
                            wi,
                            Suggestion {
                                word: dict_word.clone(),
                                distance: dist,
                                frequency: *freq,
                            },
                        );
                    }
                }
            }
        }

        let mut results: Vec<Suggestion> = candidates.into_values().collect();
        // Sort by distance (ascending), then frequency (descending)
        results.sort_by(|a, b| {
            a.distance
                .cmp(&b.distance)
                .then_with(|| b.frequency.cmp(&a.frequency))
        });
        results.truncate(max_results);
        results
    }

    /// Generate all delete variants within the given distance.
    fn edits(&self, word: &str, distance: usize) -> Vec<String> {
        if distance == 0 || word.is_empty() {
            return vec![];
        }

        let mut result = Vec::new();
        let chars: Vec<char> = word.chars().collect();

        for i in 0..chars.len() {
            let mut deleted: String = String::with_capacity(word.len() - 1);
            for (j, &c) in chars.iter().enumerate() {
                if j != i {
                    deleted.push(c);
                }
            }
            result.push(deleted.clone());

            if distance > 1 {
                let sub_edits = self.edits(&deleted, distance - 1);
                result.extend(sub_edits);
            }
        }

        result.sort();
        result.dedup();
        result
    }
}

#[derive(Debug, Clone)]
pub struct Suggestion {
    pub word: String,
    pub distance: usize,
    pub frequency: u64,
}

/// Compute the Damerau-Levenshtein edit distance between two strings.
fn edit_distance(a: &str, b: &str) -> usize {
    let a_chars: Vec<char> = a.chars().collect();
    let b_chars: Vec<char> = b.chars().collect();
    let m = a_chars.len();
    let n = b_chars.len();

    if m == 0 {
        return n;
    }
    if n == 0 {
        return m;
    }

    let mut matrix = vec![vec![0usize; n + 1]; m + 1];

    for i in 0..=m {
        matrix[i][0] = i;
    }
    for j in 0..=n {
        matrix[0][j] = j;
    }

    for i in 1..=m {
        for j in 1..=n {
            let cost = if a_chars[i - 1] == b_chars[j - 1] {
                0
            } else {
                1
            };

            matrix[i][j] = (matrix[i - 1][j] + 1) // deletion
                .min(matrix[i][j - 1] + 1) // insertion
                .min(matrix[i - 1][j - 1] + cost); // substitution

            // Transposition
            if i > 1
                && j > 1
                && a_chars[i - 1] == b_chars[j - 2]
                && a_chars[i - 2] == b_chars[j - 1]
            {
                matrix[i][j] = matrix[i][j].min(matrix[i - 2][j - 2] + cost);
            }
        }
    }

    matrix[m][n]
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_known_word() {
        let mut ss = SymSpell::new(2);
        ss.add_word_with_freq("hello", 1000);
        assert!(ss.is_known("hello"));
        assert!(ss.is_known("Hello"));
        assert!(!ss.is_known("helo"));
    }

    #[test]
    fn test_suggestions() {
        let mut ss = SymSpell::new(2);
        ss.add_word_with_freq("hello", 1000);
        ss.add_word_with_freq("help", 500);
        ss.add_word_with_freq("world", 800);

        let suggestions = ss.lookup("helo", 5);
        assert!(!suggestions.is_empty());
        assert_eq!(suggestions[0].word, "hello");
    }

    #[test]
    fn test_exact_match_returns_empty() {
        let mut ss = SymSpell::new(2);
        ss.add_word_with_freq("hello", 1000);
        let suggestions = ss.lookup("hello", 5);
        assert!(suggestions.is_empty());
    }

    #[test]
    fn test_edit_distance() {
        assert_eq!(edit_distance("kitten", "sitting"), 3);
        assert_eq!(edit_distance("", "abc"), 3);
        assert_eq!(edit_distance("abc", "abc"), 0);
        assert_eq!(edit_distance("ab", "ba"), 1); // transposition
    }

    /// The prefix_length cap is what took the real dictionary index from ~2.1GB to
    /// a few-hundred MB: a long word generates deletes only over its first
    /// `prefix_length` chars, so it costs no more delete keys than that bare prefix.
    #[test]
    fn test_prefix_length_caps_deletes() {
        let mut long = SymSpell::new(2);
        long.add_word_with_freq("antidisestablishmentarianism", 1); // 28 chars
        let long_keys = long.delete_key_count();

        let mut prefix = SymSpell::new(2);
        prefix.add_word_with_freq("antidis", 1); // the 7-char prefix only
        let prefix_keys = prefix.delete_key_count();

        assert_eq!(
            long_keys, prefix_keys,
            "deletes for a long word must be bounded by its prefix"
        );
        // The full word is still an exact match and still suggestable via its prefix.
        assert!(long.is_known("antidisestablishmentarianism"));
    }

    /// Corrections within the prefix region still resolve after the cap.
    #[test]
    fn test_long_word_still_suggests_within_prefix() {
        let mut ss = SymSpell::new(2);
        ss.add_word_with_freq("beautiful", 1000);
        let s = ss.lookup("beuatiful", 5); // transposition in first 7 chars
        assert!(s.iter().any(|x| x.word == "beautiful"));
    }

    /// Interning: a repeated word accumulates frequency without adding a new term
    /// or new delete keys (the old impl re-pushed cloned strings into every bucket).
    #[test]
    fn test_interning_dedups_repeats() {
        let mut ss = SymSpell::new(2);
        ss.add_word_with_freq("hello", 10);
        let words = ss.word_count();
        let keys = ss.delete_key_count();
        ss.add_word_with_freq("hello", 5);
        assert_eq!(ss.word_count(), words, "repeat must not add a term");
        assert_eq!(
            ss.delete_key_count(),
            keys,
            "repeat must not add delete keys"
        );
        assert_eq!(ss.get_frequency("hello"), 15, "frequency must accumulate");
    }
}
