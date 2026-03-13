use std::collections::HashMap;

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
}

/// Simple suffix stripping for common English inflections.
/// Returns candidate stems in priority order (most specific suffix first).
#[cfg(feature = "thesaurus")]
fn stem_simple(word: &str) -> Vec<String> {
    let mut stems = Vec::new();
    let len = word.len();

    // Minimum word length for stripping
    if len < 4 {
        return stems;
    }

    // Order: longer suffixes first for specificity
    let suffixes: &[(&str, Option<&str>)] = &[
        ("ation", Some("ate")),  // creation -> create
        ("tion", None),          // attraction -> attract (approx)
        ("ness", None),          // happiness -> happi (won't match, but happy will via -iness)
        ("ment", None),          // movement -> move (approx)
        ("able", None),          // readable -> read
        ("ible", None),          // visible -> vis (approx)
        ("ious", Some("y")),     // envious -> envy
        ("eous", None),          // gorgeous -> gorgeous (no strip needed usually)
        ("ous", None),           // famous -> fam (approx)
        ("ive", None),           // creative -> creat (approx)
        ("ful", None),           // beautiful -> beauti (approx)
        ("less", None),          // careless -> care
        ("ally", Some("al")),    // finally -> final
        ("ily", Some("y")),      // happily -> happy
        ("ing", None),           // running -> runn -> run (handled below)
        ("ing", Some("e")),      // making -> make
        ("ied", Some("y")),      // carried -> carry
        ("ed", None),            // walked -> walk
        ("ed", Some("e")),       // loved -> love
        ("er", None),            // faster -> fast
        ("est", None),           // fastest -> fast
        ("ly", None),            // quickly -> quick
        ("es", None),            // watches -> watch
        ("s", None),             // dogs -> dog
    ];

    for (suffix, replacement) in suffixes {
        if word.ends_with(suffix) && len > suffix.len() + 2 {
            let base = &word[..len - suffix.len()];
            // Add base form
            stems.push(base.to_string());
            // Add with replacement suffix
            if let Some(repl) = replacement {
                stems.push(format!("{}{}", base, repl));
            }
            // Special case for -ing: handle doubled consonant (running -> run)
            if *suffix == "ing" && base.len() >= 2 {
                let bytes = base.as_bytes();
                let last = bytes[bytes.len() - 1];
                let second_last = bytes[bytes.len() - 2];
                if last == second_last && last.is_ascii_alphabetic() {
                    stems.push(base[..base.len() - 1].to_string());
                }
            }
            // Special case for -ed: handle doubled consonant (stopped -> stop)
            if *suffix == "ed" && base.len() >= 2 {
                let bytes = base.as_bytes();
                let last = bytes[bytes.len() - 1];
                let second_last = bytes[bytes.len() - 2];
                if last == second_last && last.is_ascii_alphabetic() {
                    stems.push(base[..base.len() - 1].to_string());
                }
            }
        }
    }

    stems
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
        assert!(!results.is_empty(), "expected synonyms for 'running' (via stemming or direct)");
    }

    #[test]
    #[cfg(feature = "thesaurus")]
    fn test_max_limit() {
        let t = Thesaurus::new();
        let results = t.lookup("happy", 3);
        assert!(results.len() <= 3, "expected at most 3 results, got {}", results.len());
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
}
