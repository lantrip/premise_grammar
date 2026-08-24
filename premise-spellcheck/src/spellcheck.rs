use serde::{Deserialize, Serialize};

use crate::dictionary::Dictionary;
use crate::normalize::{self, u16_len};

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
    // Two cursors: byte offsets slice `text`, UTF-16 offsets are what leaves the
    // engine. `span.from` is a JavaScript document position, and JS string
    // indices count UTF-16 code units — `’` is 3 bytes but 1 unit, so reporting
    // byte offsets shifts every squiggle after the first non-ASCII character.
    let mut word_start: Option<(usize, u32)> = None;
    let mut u16_pos = 0u32;

    for (i, ch) in text.char_indices() {
        if is_word_char(ch) {
            if word_start.is_none() {
                word_start = Some((i, u16_pos));
            }
        } else if let Some(start) = word_start.take() {
            check_word(dict, text, start, i, span.from, results);
        }
        u16_pos += ch.len_utf16() as u32;
    }

    // Check the last word if the span ends mid-word
    if let Some(start) = word_start {
        check_word(dict, text, start, text.len(), span.from, results);
    }
}

/// Check a single token extracted from text.
///
/// `start` is the token's `(byte offset, UTF-16 offset)` within `text`; `end` is
/// its byte offset. Edge punctuation is trimmed off the token before anything
/// else, and the trimmed characters are excluded from both the reported word and
/// the squiggle range.
fn check_word(
    dict: &Dictionary,
    text: &str,
    start: (usize, u32),
    end: usize,
    span_offset: u32,
    results: &mut Vec<Misspelling>,
) {
    let tok = &text[start.0..end];
    let tok_u16_start = span_offset + start.1;

    // A leading apostrophe is an opening quote — unless the whole token is a
    // known elision ('twas, 'bout), where it is part of the spelling.
    let lead = if is_elision(tok) {
        0
    } else {
        edge_len(tok.chars())
    };
    if lead == tok.len() {
        return; // all punctuation
    }
    // Trailing apostrophes and hyphens are always punctuation. A plural
    // possessive (`squirrels'`) loses its apostrophe here and is then found by
    // the possessive-aware lookup on the base — and if the base is *also*
    // misspelled, the base alone is exactly the range we want to squiggle.
    let trail = edge_len(tok[lead..].chars().rev());

    check_core(
        dict,
        tok,
        tok_u16_start,
        lead,
        tok.len() - trail - lead,
        results,
    );
}

/// Byte length of the leading run of edge punctuation in `chars`.
fn edge_len(chars: impl Iterator<Item = char>) -> usize {
    chars
        .take_while(|&c| normalize::is_apostrophe(c) || c == '-')
        .map(char::len_utf8)
        .sum()
}

/// Check a trimmed word core sitting at `rel..rel + len` within `tok`.
///
/// Recurses exactly one level, on the parts of a hyphenated compound, so the
/// short-word / all-caps / all-digit skips apply per part: `x-ray` passes on the
/// 1-char skip and `NASA-approved` on the all-caps skip.
fn check_core(
    dict: &Dictionary,
    tok: &str,
    tok_u16_start: u32,
    rel: usize,
    len: usize,
    results: &mut Vec<Misspelling>,
) {
    let core = &tok[rel..rel + len];

    // Skip very short words (1-2 chars), numbers, and all-caps abbreviations.
    // Counted in chars, not bytes — `añ` is 3 bytes and would escape a byte test.
    let char_count = core.chars().count();
    if char_count <= 2 {
        return;
    }
    if core.chars().all(|c| c.is_ascii_digit()) {
        return;
    }
    if char_count <= 4 && core.chars().all(|c| c.is_uppercase()) {
        return;
    }

    if core.contains('-') {
        // Whole-unit match first: a hyphenated entity name or custom-dictionary
        // word. The base word list holds zero hyphenated entries, so this only
        // ever hits the entity / custom sets.
        if dict.is_known_allowing_possessive(core) {
            return;
        }
        // Otherwise the parts stand on their own. An empty part means `--` (an
        // em dash typed as two hyphens), which is just a word boundary.
        let mut part_rel = rel;
        for part in core.split('-') {
            if !part.is_empty() {
                check_core(dict, tok, tok_u16_start, part_rel, part.len(), results);
            }
            part_rel += part.len() + 1; // + the '-' separator
        }
        return;
    }

    if dict.is_known_allowing_possessive(core) {
        return;
    }

    // Flagged. When the miss is a possessive, squiggle only the base: the
    // suggestions that come back carry no possessive, so replacing `treee` with
    // `tree` inside `treee's` yields `tree's`. The invariant is that the flagged
    // range is exactly the substring a suggestion may replace verbatim.
    let flagged_len = possessive_base_len(core).unwrap_or(len);
    if flagged_len == 0 {
        return;
    }

    // Suggestions are intentionally NOT computed here. The bulk check runs over the
    // whole document, and generating edit-distance suggestions for every flagged word
    // (a narrative `.prem` flags many proper/fantasy nouns) created a large transient
    // allocation that set a permanent WASM-memory high-water mark. The popover fetches
    // suggestions lazily for the single clicked word via the `suggest` message.
    let from = tok_u16_start + u16_len(&tok[..rel]);
    results.push(Misspelling {
        word: tok[rel..rel + flagged_len].to_string(),
        from,
        to: from + u16_len(&tok[rel..rel + flagged_len]),
        suggestions: Vec::new(),
    });
}

/// Byte length of the base when `core` ends in a singular possessive (`tree's`).
fn possessive_base_len(core: &str) -> Option<usize> {
    let mut rev = core.chars().rev();
    let last = rev.next()?;
    if last != 's' && last != 'S' {
        return None;
    }
    let apos = rev.next()?;
    if !normalize::is_apostrophe(apos) {
        return None;
    }
    let base = core.len() - last.len_utf8() - apos.len_utf8();
    (base > 0).then_some(base)
}

/// The form to look up when fetching suggestions for a word.
///
/// The bulk checker already reports a trimmed base (see `check_core`), so this
/// is a no-op there; it exists for the right-click path, which hands over
/// whatever the caret scan scraped — edge quotes, curly apostrophes and all.
pub fn suggestion_key(word: &str) -> String {
    if is_elision(word) {
        return normalize::lookup_key(word);
    }
    let folded = normalize::fold_apostrophes(word);
    let trimmed = folded.trim_matches(|c: char| c == '\'' || c == '-');
    let base = possessive_base_len(trimmed).map_or(trimmed, |n| &trimmed[..n]);
    base.to_lowercase()
}

/// Determine if a character is part of a word.
///
/// Letters, every apostrophe variant (contractions, possessives, elisions), and
/// `-`, so a hyphenated compound arrives as one token and `check_core` can try
/// it against the entity / custom sets before decomposing it. Digits are
/// excluded, so a bare number never forms a token at all.
fn is_word_char(ch: char) -> bool {
    ch.is_alphabetic() || normalize::is_apostrophe(ch) || ch == '-'
}

/// Check if a word starting with apostrophe is a known elision form.
fn is_elision(word: &str) -> bool {
    let lower = normalize::lookup_key(word);
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

    /// Convenience: check one span starting at document offset 0.
    fn check(dict: &Dictionary, text: &str) -> Vec<Misspelling> {
        check_spans(
            dict,
            &[CheckableSpan {
                text: text.to_string(),
                from: 0,
                to: text.encode_utf16().count() as u32,
            }],
        )
    }

    fn words(results: &[Misspelling]) -> Vec<&str> {
        results.iter().map(|m| m.word.as_str()).collect()
    }

    // ---- possessives -------------------------------------------------------

    #[test]
    fn test_singular_possessive_not_flagged() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("tree 100\nthe 500\nbark 50\n");
        assert!(check(&dict, "the tree's bark").is_empty());
    }

    #[test]
    fn test_entity_possessive_not_flagged() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("roots 100\n");
        dict.set_entity_names(&["Cedar".to_string()]);
        assert_eq!(words(&check(&dict, "Cedar's roots")), Vec::<&str>::new());
    }

    #[test]
    fn test_curly_singular_possessive_not_flagged() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("tree 100\nbark 50\n");
        assert!(check(&dict, "tree\u{2019}s bark").is_empty());
    }

    #[test]
    fn test_wordlist_contraction_beats_possessive() {
        let mut dict = Dictionary::new();
        // "it" itself is absent; only the contraction is in the list.
        dict.load_wordlist("it's 5000\ncold 100\n");
        assert!(check(&dict, "it's cold").is_empty());
    }

    #[test]
    fn test_misspelled_possessive_flags_base_only() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("tree 100\nthe 500\nbark 50\n");
        let results = check(&dict, "the treee's bark");
        assert_eq!(words(&results), vec!["treee"]);
        assert_eq!(results[0].from, 4);
        assert_eq!(results[0].to, 9, "the 's must stay outside the squiggle");
    }

    // ---- typographic apostrophes -------------------------------------------

    #[test]
    fn test_curly_apostrophe_contraction() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("isn't 3000\n");
        // Previously tokenized as "isn" + "t" and flagged "isn".
        assert_eq!(words(&check(&dict, "isn\u{2019}t")), Vec::<&str>::new());
    }

    #[test]
    fn test_curly_quotes_around_word() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("hello 1000\n");
        assert!(check(&dict, "\u{2018}hello\u{2019}").is_empty());
    }

    #[test]
    fn test_modifier_letter_apostrophe() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("don't 5000\n");
        assert!(check(&dict, "don\u{02BC}t").is_empty());
    }

    #[test]
    fn test_curly_elision() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("'twas 500\ncold 100\n");
        assert!(check(&dict, "\u{2019}twas cold").is_empty());
    }

    // ---- offsets -----------------------------------------------------------

    #[test]
    fn test_curly_apostrophe_offsets_are_utf16() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("it's 5000\n");
        // "it’s teh" — `teh` starts at UTF-16 index 5 but byte index 7, because
        // the curly apostrophe is 3 bytes and 1 code unit.
        let results = check(&dict, "it\u{2019}s teh");
        assert_eq!(words(&results), vec!["teh"]);
        assert_eq!(results[0].from, 5);
        assert_eq!(results[0].to, 8);
    }

    #[test]
    fn test_astral_char_offset() {
        let dict = Dictionary::new();
        // 🌲 is 4 bytes but 2 UTF-16 code units.
        let results = check(&dict, "\u{1F332} teh");
        assert_eq!(words(&results), vec!["teh"]);
        assert_eq!(results[0].from, 3);
    }

    #[test]
    fn test_short_word_skip_counts_chars_not_bytes() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("hello 1000\n");
        // "añ" is 2 chars but 3 bytes — a byte-length skip test would miss it.
        assert!(check(&dict, "a\u{00F1} hello").is_empty());
    }

    #[test]
    fn test_trailing_quote_excluded_from_range() {
        let dict = Dictionary::new();
        let results = check(&dict, "badword'");
        assert_eq!(words(&results), vec!["badword"]);
        assert_eq!(
            results[0].to, 7,
            "the closing quote is not part of the word"
        );
    }

    // ---- hyphenated compounds ----------------------------------------------

    #[test]
    fn test_hyphenated_all_parts_known() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("well 1000\nknown 900\n");
        assert!(check(&dict, "well-known").is_empty());
    }

    #[test]
    fn test_hyphenated_entity_matches_as_unit() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("burned 100\n");
        dict.set_entity_names(&["Cedar-Ridge".to_string()]);
        assert_eq!(
            words(&check(&dict, "Cedar-Ridge burned")),
            Vec::<&str>::new()
        );
    }

    #[test]
    fn test_hyphenated_custom_word_as_unit() {
        let mut dict = Dictionary::new();
        dict.add_word("mother-in-law");
        assert!(check(&dict, "mother-in-law").is_empty());
    }

    #[test]
    fn test_hyphenated_possessive() {
        let mut dict = Dictionary::new();
        dict.add_word("mother-in-law");
        dict.load_wordlist("house 100\n");
        assert!(check(&dict, "mother-in-law's house").is_empty());
    }

    #[test]
    fn test_hyphenated_unknown_part_flagged() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("cedar 100\n");
        let results = check(&dict, "Cedar-Ridgge");
        assert_eq!(words(&results), vec!["Ridgge"]);
        assert_eq!(results[0].from, 6);
        assert_eq!(results[0].to, 12);
    }

    #[test]
    fn test_hyphenated_both_parts_unknown() {
        let dict = Dictionary::new();
        let results = check(&dict, "Cedarr-Ridgge");
        assert_eq!(words(&results), vec!["Cedarr", "Ridgge"]);
        assert_eq!((results[0].from, results[0].to), (0, 6));
        assert_eq!((results[1].from, results[1].to), (7, 13));
    }

    #[test]
    fn test_double_hyphen_is_two_words() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("dead 100\nsilence 100\n");
        assert!(check(&dict, "dead--silence").is_empty());

        let results = check(&dict, "dead--silencee");
        assert_eq!(words(&results), vec!["silencee"]);
        assert_eq!(results[0].from, 6);
    }

    #[test]
    fn test_leading_trailing_hyphen_trimmed() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("word 100\n");
        assert!(check(&dict, "-word-").is_empty());

        let results = check(&dict, "-wordd-");
        assert_eq!(words(&results), vec!["wordd"]);
        assert_eq!((results[0].from, results[0].to), (1, 6));
    }

    #[test]
    fn test_hyphen_part_skip_rules() {
        let mut dict = Dictionary::new();
        dict.load_wordlist("ray 100\napproved 100\n");
        // "x" is skipped as too short; "NASA" as a short all-caps abbreviation.
        assert!(check(&dict, "x-ray").is_empty());
        assert!(check(&dict, "NASA-approved").is_empty());
    }

    // ---- suggestion key ----------------------------------------------------

    #[test]
    fn test_suggestion_key_normalizes() {
        assert_eq!(suggestion_key("Cedar\u{2019}s"), "cedar");
        assert_eq!(suggestion_key("'lighthouse'"), "lighthouse");
        assert_eq!(suggestion_key("squirrels'"), "squirrels");
        assert_eq!(suggestion_key("don\u{2019}t"), "don't");
        assert_eq!(suggestion_key("\u{2019}twas"), "'twas");
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
