use std::collections::HashMap;

#[cfg(feature = "thesaurus")]
use crate::stemming::stem_simple;

#[cfg(feature = "thesaurus")]
const THESAURUS_DATA: &str = include_str!("../data/moby_thesaurus.txt");

/// Embedded thesaurus for synonym lookup.
///
/// When compiled with the `thesaurus` feature (default), embeds the Moby Thesaurus
/// (~30K root words) and provides synonym lookup with simple suffix stripping.
/// Without the feature, this is a zero-cost stub that returns empty results.
#[cfg(feature = "thesaurus")]
pub struct Thesaurus {
    entries: HashMap<String, Vec<String>>,
}

// Delegates to `new`, which parses the embedded thesaurus — not a cheap
// default, but callers reaching for `Thesaurus::default()` want the loaded
// dictionary, not an empty one.
#[cfg(feature = "thesaurus")]
impl Default for Thesaurus {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(feature = "thesaurus")]
impl Thesaurus {
    pub fn new() -> Self {
        let mut entries = HashMap::with_capacity(32_000);

        for line in THESAURUS_DATA.lines() {
            if line.is_empty() {
                continue;
            }
            let mut parts = line.splitn(2, ',');
            let root = match parts.next() {
                Some(w) if !w.is_empty() => w.to_string(),
                _ => continue,
            };
            let synonyms: Vec<String> = match parts.next() {
                Some(rest) => rest.split(',').map(|s| s.to_string()).collect(),
                None => continue,
            };
            if !synonyms.is_empty() {
                entries.insert(root, synonyms);
            }
        }

        Self { entries }
    }

    pub fn is_available(&self) -> bool {
        true
    }

    /// Look up synonyms for a word, returning at most `max` results.
    ///
    /// Tries direct lookup first, then attempts simple suffix stripping
    /// to find the root form (e.g., "running" -> "run").
    /// Returns synonyms in their original (alphabetical) order.
    pub fn lookup(&self, word: &str, max: usize) -> Vec<String> {
        let lower = word.to_lowercase();

        // Direct lookup
        if let Some(syns) = self.entries.get(&lower) {
            return syns.iter().take(max).cloned().collect();
        }

        // Try suffix stripping
        for stem in stem_simple(&lower) {
            if let Some(syns) = self.entries.get(&stem) {
                return syns.iter().take(max).cloned().collect();
            }
        }

        Vec::new()
    }

    /// Look up synonyms ranked by word frequency so common, recognizable
    /// words appear first. Uses `freq_fn` to score each synonym.
    ///
    /// Synonyms with frequency 0 (not in the frequency dictionary) are
    /// kept at the end in their original order, so multi-word phrases
    /// and archaic terms still appear when `max` is generous enough.
    pub fn lookup_ranked(
        &self,
        word: &str,
        max: usize,
        freq_fn: impl Fn(&str) -> u64,
    ) -> Vec<String> {
        let lower = word.to_lowercase();

        let syns = self.find_synonyms(&lower);
        let syns = match syns {
            Some(s) => s,
            None => return Vec::new(),
        };

        // Score each synonym, preserving original index as tiebreaker
        let mut scored: Vec<(usize, &String, u64)> = syns
            .iter()
            .enumerate()
            .map(|(i, s)| (i, s, freq_fn(s)))
            .collect();

        // Highest frequency first; ties preserve original order
        scored.sort_by(|a, b| b.2.cmp(&a.2).then_with(|| a.0.cmp(&b.0)));

        scored
            .into_iter()
            .take(max)
            .map(|(_, s, _)| s.clone())
            .collect()
    }

    /// Find the synonym list for a word (direct or via stemming).
    fn find_synonyms(&self, lower: &str) -> Option<&Vec<String>> {
        if let Some(syns) = self.entries.get(lower) {
            return Some(syns);
        }
        for stem in stem_simple(lower) {
            if let Some(syns) = self.entries.get(&stem) {
                return Some(syns);
            }
        }
        None
    }
}

// --- Stub implementation when thesaurus feature is disabled ---

#[cfg(not(feature = "thesaurus"))]
pub struct Thesaurus;

#[cfg(not(feature = "thesaurus"))]
impl Thesaurus {
    pub fn new() -> Self {
        Thesaurus
    }

    pub fn is_available(&self) -> bool {
        false
    }

    pub fn lookup(&self, _word: &str, _max: usize) -> Vec<String> {
        Vec::new()
    }

    pub fn lookup_ranked(
        &self,
        _word: &str,
        _max: usize,
        _freq_fn: impl Fn(&str) -> u64,
    ) -> Vec<String> {
        Vec::new()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    #[cfg(feature = "thesaurus")]
    fn test_lookup_known_word() {
        let t = Thesaurus::new();
        let results = t.lookup("happy", 10);
        assert!(!results.is_empty(), "expected synonyms for 'happy'");
    }

    #[test]
    fn test_lookup_unknown_word() {
        let t = Thesaurus::new();
        let results = t.lookup("xyzzyplugh", 10);
        assert!(results.is_empty(), "expected no synonyms for gibberish");
    }

    #[test]
    #[cfg(feature = "thesaurus")]
    fn test_stem_and_lookup() {
        let t = Thesaurus::new();
        // "running" should find synonyms via stem "run"
        let results = t.lookup("running", 10);
        // Even if "running" itself is a root word, we should get results
        assert!(
            !results.is_empty(),
            "expected synonyms for 'running' (via stemming or direct)"
        );
    }

    #[test]
    #[cfg(feature = "thesaurus")]
    fn test_max_limit() {
        let t = Thesaurus::new();
        let results = t.lookup("happy", 3);
        assert!(
            results.len() <= 3,
            "expected at most 3 results, got {}",
            results.len()
        );
    }

    #[test]
    #[cfg(feature = "thesaurus")]
    fn test_case_insensitive() {
        let t = Thesaurus::new();
        let lower = t.lookup("happy", 5);
        let upper = t.lookup("Happy", 5);
        assert_eq!(lower, upper, "lookup should be case-insensitive");
    }

    #[test]
    fn test_is_available() {
        let t = Thesaurus::new();
        #[cfg(feature = "thesaurus")]
        assert!(t.is_available());
        #[cfg(not(feature = "thesaurus"))]
        assert!(!t.is_available());
    }

    #[test]
    #[cfg(feature = "thesaurus")]
    fn test_ranked_prefers_common_words() {
        let t = Thesaurus::new();
        // Simulate a frequency function where common English words score high
        let common_words: std::collections::HashMap<&str, u64> = [
            ("content", 5000),
            ("glad", 4000),
            ("cheerful", 3000),
            ("bright", 6000),
            ("well", 9000),
            ("good", 8000),
            ("right", 7000),
            ("fair", 5500),
            ("nice", 4500),
            ("pleasant", 3500),
        ]
        .into_iter()
        .collect();

        let results = t.lookup_ranked("happy", 10, |w| common_words.get(w).copied().unwrap_or(0));
        assert!(!results.is_empty(), "expected ranked synonyms for 'happy'");
        // The first result should be one of the high-frequency words
        let top3: Vec<&str> = results.iter().take(3).map(|s| s.as_str()).collect();
        assert!(
            top3.contains(&"well") || top3.contains(&"good") || top3.contains(&"right"),
            "expected common words in top 3, got: {:?}",
            top3
        );
    }

    #[test]
    #[cfg(feature = "thesaurus")]
    fn test_ranked_max_limit() {
        let t = Thesaurus::new();
        let results = t.lookup_ranked("happy", 5, |_| 1);
        assert!(
            results.len() <= 5,
            "expected at most 5 results, got {}",
            results.len()
        );
    }

    #[test]
    #[cfg(feature = "thesaurus")]
    fn test_ranked_zero_freq_preserves_order() {
        let t = Thesaurus::new();
        // When all frequencies are 0, original order is preserved
        let results = t.lookup_ranked("happy", 200, |_| 0);
        let unranked = t.lookup("happy", 200);
        assert_eq!(
            results, unranked,
            "with all-zero frequencies, ranked should match original order"
        );
    }
}
