//! Text normalization shared by the tokenizer and the dictionary.
//!
//! Two concerns live here because both sides must agree on them exactly:
//!
//! 1. **Apostrophe folding.** Prose pasted from a word processor is full of
//!    typographic apostrophes, and a spellchecker that treats `don't` and
//!    `don’t` as different words flags half a manuscript. Hunspell solves this
//!    with an `ICONV ’ '` line in the affix file (shipped in the LibreOffice /
//!    Mozilla `en_US` dictionaries) and Chromium folds the same way before
//!    lookup. Nobody keeps two dictionary entries; neither do we.
//!
//! 2. **UTF-16 lengths.** Misspelling offsets leave this crate and land in a
//!    JavaScript document position. JS string indices count UTF-16 code units,
//!    not bytes, so anything measured for the wire must be measured in those.

use std::borrow::Cow;

/// Characters that act as an apostrophe. All fold to `'` for dictionary lookup.
///
/// - `U+2019` RIGHT SINGLE QUOTATION MARK — the typographic apostrophe every
///   word processor and every smart-quote substitution produces.
/// - `U+2018` LEFT SINGLE QUOTATION MARK — an *opening quote*, not an
///   apostrophe. It is in this class so `‘hello’` tokenizes as a single token
///   and the tokenizer's edge trim peels it off, and so that `‘twas` reaches
///   the elision list the same way `'twas` does.
/// - `U+02BC` MODIFIER LETTER APOSTROPHE — the Unicode-correct apostrophe;
///   turns up in transliterated names and text from linguistics tooling.
/// - `U+FF07` FULLWIDTH APOSTROPHE — CJK IME paste.
///
/// Deliberately excluded: `U+2032` PRIME (a measurement mark, `6′ tall`) and
/// the ASCII backtick (folding it would swallow inline code).
pub fn is_apostrophe(ch: char) -> bool {
    matches!(ch, '\'' | '\u{2019}' | '\u{2018}' | '\u{02BC}' | '\u{FF07}')
}

/// Fold every apostrophe variant to `'`.
///
/// Borrows when there is nothing to change, which is the overwhelmingly common
/// case — this runs once per word over a whole document.
pub fn fold_apostrophes(s: &str) -> Cow<'_, str> {
    if !s.chars().any(|c| is_apostrophe(c) && c != '\'') {
        return Cow::Borrowed(s);
    }
    Cow::Owned(
        s.chars()
            .map(|c| if is_apostrophe(c) { '\'' } else { c })
            .collect(),
    )
}

/// The canonical key for any dictionary membership test: folded, then lowered.
///
/// Every insert and every lookup goes through this, so a word stored with a
/// curly apostrophe and a word checked with a straight one cannot disagree.
pub fn lookup_key(s: &str) -> String {
    fold_apostrophes(s).to_lowercase()
}

/// Length in UTF-16 code units — the unit JavaScript document positions count.
///
/// `’` is 3 bytes but 1 code unit; an emoji is 4 bytes but 2. Measuring the
/// wire offsets in bytes desyncs every squiggle after the first such character.
pub fn u16_len(s: &str) -> u32 {
    s.encode_utf16().count() as u32
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn folds_every_apostrophe_variant() {
        assert_eq!(fold_apostrophes("don\u{2019}t"), "don't");
        assert_eq!(fold_apostrophes("\u{2018}hello\u{2019}"), "'hello'");
        assert_eq!(fold_apostrophes("don\u{02BC}t"), "don't");
        assert_eq!(fold_apostrophes("don\u{FF07}t"), "don't");
    }

    #[test]
    fn borrows_when_nothing_changes() {
        assert!(matches!(fold_apostrophes("don't"), Cow::Borrowed(_)));
        assert!(matches!(fold_apostrophes("plain"), Cow::Borrowed(_)));
    }

    #[test]
    fn prime_and_backtick_are_not_apostrophes() {
        assert!(!is_apostrophe('\u{2032}'));
        assert!(!is_apostrophe('`'));
        assert_eq!(fold_apostrophes("6\u{2032}"), "6\u{2032}");
    }

    #[test]
    fn lookup_key_folds_and_lowers() {
        assert_eq!(lookup_key("Cedar\u{2019}s"), "cedar's");
    }

    #[test]
    fn u16_len_counts_code_units() {
        assert_eq!(u16_len("it's"), 4);
        assert_eq!(u16_len("it\u{2019}s"), 4); // 5 bytes, 4 code units
        assert_eq!(u16_len("\u{1F332}"), 2); // 🌲 — 4 bytes, 2 code units
    }
}
