use serde::{Deserialize, Serialize};

use crate::dictionary::Dictionary;

/// A span of text to check, with document positions.
#[derive(Debug, Clone, Deserialize)]
pub struct CheckableSpan {
    pub text: String,
    pub from: u32,
    pub to: u32,
}

/// A misspelled word with its document position and suggestions.
#[derive(Debug, Clone, Serialize)]
pub struct Misspelling {
    pub word: String,
    pub from: u32,
    pub to: u32,
    pub suggestions: Vec<String>,
}

/// Check a list of text spans for misspellings.
pub fn check_spans(dict: &Dictionary, spans: &[CheckableSpan]) -> Vec<Misspelling> {
    let mut results = Vec::new();

    for span in spans {
        check_span(dict, span, &mut results);
    }

    results
}

/// Check a single text span, extracting words and checking each.
fn check_span(dict: &Dictionary, span: &CheckableSpan, results: &mut Vec<Misspelling>) {
    let text = &span.text;
    let mut word_start: Option<usize> = None;

    for (i, ch) in text.char_indices() {
        if is_word_char(ch) {
            if word_start.is_none() {
                word_start = Some(i);
            }
        } else if let Some(start) = word_start {
            check_word(dict, text, start, i, span.from, results);
            word_start = None;
        }
    }

    // Check the last word if the span ends mid-word
    if let Some(start) = word_start {
        check_word(dict, text, start, text.len(), span.from, results);
    }
}

/// Check a single word extracted from text.
fn check_word(
    dict: &Dictionary,
    text: &str,
    start: usize,
    end: usize,
    span_offset: u32,
    results: &mut Vec<Misspelling>,
) {
    let raw = &text[start..end];

    // Strip trailing apostrophes for possessives (squirrels' → squirrels)
    let word = raw.trim_end_matches('\'');

    // Strip leading apostrophes unless it's a known elision ('twas, 'bout, etc.)
    let (word, leading_stripped) = if word.starts_with('\'') && !is_elision(word) {
        let trimmed = word.trim_start_matches('\'');
        (trimmed, word.len() - trimmed.len())
    } else {
        (word, 0)
    };

    // Adjust start offset to exclude stripped leading apostrophes from decoration
    let start = start + leading_stripped;

    // Skip very short words (1-2 chars), numbers, and all-caps abbreviations
    if word.len() <= 2 {
        return;
    }
    if word.chars().all(|c| c.is_ascii_digit()) {
        return;
    }
    if word.len() <= 4 && word.chars().all(|c| c.is_uppercase()) {
        return;
    }

    if !dict.is_correct(word) {
        // Suggestions are intentionally NOT computed here. The bulk check runs over the
        // whole document, and generating edit-distance suggestions for every flagged word
        // (a narrative `.prem` flags many proper/fantasy nouns) created a large transient
        // allocation that set a permanent WASM-memory high-water mark. The popover fetches
        // suggestions lazily for the single clicked word via the `suggest` message.
        results.push(Misspelling {
            word: word.to_string(),
            from: span_offset + start as u32,
            to: span_offset + end as u32,
            suggestions: Vec::new(),
        });
    }
}

/// Determine if a character is part of a word.
/// Includes letters and apostrophes (for contractions like "don't").
fn is_word_char(ch: char) -> bool {
    ch.is_alphabetic() || ch == '\''
}

/// Check if a word starting with apostrophe is a known elision form.
fn is_elision(word: &str) -> bool {
    let lower = word.to_lowercase();
    matches!(
        lower.as_str(),
        "'twas"
            | "'tis"
            | "'til"
            | "'bout"
            | "'cause"
            | "'em"
            | "'neath"
            | "'gainst"
            | "'round"
            | "'mongst"
            | "'fore"
    )
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_check_spans() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("hello 1000\nworld 800\nthe 5000\n");

        let spans = vec![CheckableSpan {
            text: "hello wrold the".to_string(),
            from: 10,
            to: 25,
        }];

        let results = check_spans(&dict, &spans);
        assert_eq!(results.len(), 1);
        assert_eq!(results[0].word, "wrold");
        assert_eq!(results[0].from, 16); // 10 + 6 (offset of "wrold")
    }

    #[test]
    fn test_skip_short_words() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("hello 1000\n");

        let spans = vec![CheckableSpan {
            text: "a I hello".to_string(),
            from: 0,
            to: 9,
        }];

        let results = check_spans(&dict, &spans);
        // "a" and "I" are <= 2 chars, should be skipped
        assert!(results.is_empty());
    }

    #[test]
    fn test_skip_numbers() {
        let dict = Dictionary::new();

        let spans = vec![CheckableSpan {
            text: "chapter 42 begins".to_string(),
            from: 0,
            to: 17,
        }];

        let results = check_spans(&dict, &spans);
        // "42" should be skipped
        assert!(results.iter().all(|m| m.word != "42"));
    }

    #[test]
    fn test_contractions_in_dictionary() {
        let mut dict = Dictionary::new();
        dict.load_wordlist(
            "you're 4000\ndon't 5000\nwon't 3500\nit's 5000\nthey'll 2500\nwe've 2500\n",
        );

        let spans = vec![CheckableSpan {
            text: "you're don't won't it's they'll we've".to_string(),
            from: 0,
            to: 36,
        }];

        let results = check_spans(&dict, &spans);
        assert!(
            results.is_empty(),
            "Unexpected misspellings: {:?}",
            results.iter().map(|m| &m.word).collect::<Vec<_>>()
        );
    }

    #[test]
    fn test_misspelled_contraction_flagged() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("can't 4500\ndon't 5000\n");

        let spans = vec![CheckableSpan {
            text: "cna't dontt".to_string(),
            from: 0,
            to: 11,
        }];

        let results = check_spans(&dict, &spans);
        // Both misspelled contractions should be flagged
        assert!(
            results.iter().any(|m| m.word == "cna't"),
            "cna't should be flagged"
        );
        assert!(
            results.iter().any(|m| m.word == "dontt"),
            "dontt should be flagged"
        );
    }

    #[test]
    fn test_trailing_apostrophe_stripped() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("squirrels 1\n");

        let spans = vec![CheckableSpan {
            text: "squirrels' nest".to_string(),
            from: 0,
            to: 15,
        }];

        let results = check_spans(&dict, &spans);
        assert!(
            results.iter().all(|m| m.word != "squirrels"),
            "squirrels should not be flagged"
        );
    }

    #[test]
    fn test_leading_apostrophe_stripped_for_quotes() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("hello 1000\nunprotectable 1\n");

        let spans = vec![CheckableSpan {
            text: "'hello' world 'unprotectable'".to_string(),
            from: 0,
            to: 29,
        }];

        let results = check_spans(&dict, &spans);
        // Words in single quotes should not be flagged
        assert!(
            results
                .iter()
                .all(|m| m.word != "hello" && m.word != "'hello"),
            "hello in quotes should not be flagged, got: {:?}",
            results.iter().map(|m| &m.word).collect::<Vec<_>>()
        );
        assert!(
            results
                .iter()
                .all(|m| m.word != "unprotectable" && m.word != "'unprotectable"),
            "unprotectable in quotes should not be flagged, got: {:?}",
            results.iter().map(|m| &m.word).collect::<Vec<_>>()
        );
    }

    #[test]
    fn test_leading_apostrophe_offset_correct() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("hello 1000\n");

        // "xyz 'badword' end" — 'badword' should be flagged as "badword" with correct offset
        let spans = vec![CheckableSpan {
            text: "xyz 'badword' end".to_string(),
            from: 10,
            to: 27,
        }];

        let results = check_spans(&dict, &spans);
        let m = results.iter().find(|m| m.word == "badword");
        assert!(m.is_some(), "badword should be flagged");
        let m = m.unwrap();
        // "xyz 'badword'" — badword starts at byte 5 (after "xyz '"), span_offset is 10
        assert_eq!(m.from, 15, "from should skip the leading apostrophe");
    }

    #[test]
    fn test_special_apostrophe_forms() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("o'clock 2500\n'twas 500\n");

        let spans = vec![CheckableSpan {
            text: "at three o'clock 'twas cold".to_string(),
            from: 0,
            to: 27,
        }];

        let results = check_spans(&dict, &spans);
        assert!(
            results.iter().all(|m| m.word != "o'clock"),
            "o'clock should not be flagged"
        );
        assert!(
            results
                .iter()
                .all(|m| m.word != "'twas" && m.word != "twas"),
            "'twas should not be flagged"
        );
    }
}
