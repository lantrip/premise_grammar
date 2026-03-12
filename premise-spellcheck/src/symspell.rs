use std::collections::HashMap;

/// Symmetric Delete spelling correction algorithm.
///
/// Pre-computes all deletion variants within `max_edit_distance` at load time,
/// enabling O(1) lookups and fast suggestion generation.
pub struct SymSpell {
    max_edit_distance: usize,
    /// Maps delete variants → list of (original_word, frequency) pairs
    deletes: HashMap<String, Vec<(String, u64)>>,
    /// Maps exact words → frequency
    words: HashMap<String, u64>,
}

impl SymSpell {
    pub fn new(max_edit_distance: usize) -> Self {
        Self {
            max_edit_distance,
            deletes: HashMap::new(),
            words: HashMap::new(),
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
            let freq: u64 = parts
                .next()
                .and_then(|f| f.parse().ok())
                .unwrap_or(1);
            self.add_word_with_freq(&word, freq);
        }
    }

    /// Add a single word with a given frequency.
    pub fn add_word_with_freq(&mut self, word: &str, freq: u64) {
        let lower = word.to_lowercase();
        *self.words.entry(lower.clone()).or_insert(0) += freq;

        let deletes = self.edits(&lower, self.max_edit_distance);
        for delete in deletes {
            self.deletes
                .entry(delete)
                .or_default()
                .push((lower.clone(), freq));
        }
        // Also store the word itself as a "delete" of distance 0
        self.deletes
            .entry(lower.clone())
            .or_default()
            .push((lower, freq));
    }

    /// Add a word with default frequency (high, so it's always considered correct).
    pub fn add_word(&mut self, word: &str) {
        self.add_word_with_freq(word, 100_000);
    }

    /// Remove a word from the dictionary.
    pub fn remove_word(&mut self, word: &str) {
        let lower = word.to_lowercase();
        self.words.remove(&lower);
        // Note: we don't clean up deletes map for simplicity.
        // The word will still appear as a candidate but won't be in self.words,
        // so it won't be returned as a suggestion.
    }

    /// Check if a word is in the dictionary (case-insensitive).
    pub fn is_known(&self, word: &str) -> bool {
        self.words.contains_key(&word.to_lowercase())
    }

    /// Get spelling suggestions for a word, ranked by edit distance then frequency.
    pub fn lookup(&self, input: &str, max_results: usize) -> Vec<Suggestion> {
        let input_lower = input.to_lowercase();

        // Exact match — word is correct
        if self.words.contains_key(&input_lower) {
            return vec![];
        }

        let mut candidates: HashMap<String, Suggestion> = HashMap::new();

        // Generate deletes of the input and look them up
        let input_deletes = self.edits(&input_lower, self.max_edit_distance);
        let mut all_variants = input_deletes;
        all_variants.push(input_lower.clone());

        for variant in &all_variants {
            if let Some(entries) = self.deletes.get(variant) {
                for (dict_word, freq) in entries {
                    if !self.words.contains_key(dict_word) {
                        continue;
                    }
                    let dist = edit_distance(&input_lower, dict_word);
                    if dist <= self.max_edit_distance {
                        let entry = candidates.entry(dict_word.clone()).or_insert(Suggestion {
                            word: dict_word.clone(),
                            distance: dist,
                            frequency: *freq,
                        });
                        // Keep best frequency
                        if *freq > entry.frequency {
                            entry.frequency = *freq;
                        }
                        if dist < entry.distance {
                            entry.distance = dist;
                        }
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
}
