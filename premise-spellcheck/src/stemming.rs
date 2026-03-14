/// Simple suffix stripping for common English inflections.
/// Returns candidate stems in priority order (most specific suffix first).
///
/// Shared by both the thesaurus (synonym lookup) and definitions (dictionary lookup)
/// modules for fallback word matching.
pub fn stem_simple(word: &str) -> Vec<String> {
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_stem_running() {
        let stems = stem_simple("running");
        assert!(stems.contains(&"run".to_string()), "expected 'run' in stems: {:?}", stems);
    }

    #[test]
    fn test_stem_creation() {
        let stems = stem_simple("creation");
        assert!(stems.contains(&"create".to_string()), "expected 'create' in stems: {:?}", stems);
    }

    #[test]
    fn test_stem_happily() {
        let stems = stem_simple("happily");
        assert!(stems.contains(&"happy".to_string()), "expected 'happy' in stems: {:?}", stems);
    }

    #[test]
    fn test_stem_short_word() {
        let stems = stem_simple("cat");
        assert!(stems.is_empty(), "expected no stems for short word");
    }

    #[test]
    fn test_stem_carried() {
        let stems = stem_simple("carried");
        assert!(stems.contains(&"carry".to_string()), "expected 'carry' in stems: {:?}", stems);
    }

    #[test]
    fn test_stem_stopped() {
        let stems = stem_simple("stopped");
        assert!(stems.contains(&"stop".to_string()), "expected 'stop' in stems: {:?}", stems);
    }
}
