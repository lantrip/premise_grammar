//! Graveyard region detection for `.prem` content.
//!
//! Mirrors the frontend scope rules in
//! `frontend/src/lib/premHierarchy.ts` so the studio outline and the
//! server-side lens / KB extraction agree on what is "dead but retained"
//! material.
//!
//! Two markers:
//! - A leading `~` on any header line marks that header and its subtree
//!   (until the next sibling-or-higher header) as graveyard.
//! - A line of the form `^~ <prose>` is a single-line graveyard, no scope.
//!
//! `~` is recognized only at column 0; mid-line tildes (e.g. `~5 minutes
//! later` in the middle of a paragraph) remain ordinary prose.
//!
//! Implementation is line-based (independent of the tree-sitter parser)
//! so it works on raw `.prem` source even when the file would otherwise
//! produce parse errors.

use std::ops::RangeInclusive;

#[derive(Debug, Clone, Copy)]
enum Header {
    /// Structural depth: act=0, scene=1, cel=2, beat=3, treatment=4, narrative=5.
    Level(u8),
}

/// Classify a single line. Returns `Some(Header::Level)` for `~`-prefixed
/// headers, or `None` for everything else (including non-graveyarded headers
/// and non-header lines).
fn graveyard_header_level(line: &str) -> Option<Header> {
    // Header keywords always start at column 0 (no indentation in .prem
    // hierarchy headers). Trim only trailing whitespace for safety.
    let bytes = line.as_bytes();
    if bytes.first() != Some(&b'~') {
        return None;
    }
    // Match `~` + run of `=` or `#` + whitespace.
    let mut i = 1;
    let mut eq = 0;
    while bytes.get(i) == Some(&b'=') {
        eq += 1;
        i += 1;
    }
    if eq > 0 {
        // `~=`, `~==`, `~===`. Must be followed by whitespace + content.
        if !matches!(bytes.get(i), Some(b' ') | Some(b'\t')) {
            return None;
        }
        return match eq {
            1 => Some(Header::Level(0)),
            2 => Some(Header::Level(1)),
            3 => Some(Header::Level(2)),
            _ => None,
        };
    }
    let mut hash = 0;
    while bytes.get(i) == Some(&b'#') {
        hash += 1;
        i += 1;
    }
    if hash > 0 {
        // `~#`, `~##`, `~###`. Trailing whitespace + content is optional
        // (matches the frontend's `\s*` for content layers).
        return match hash {
            1 => Some(Header::Level(3)),
            2 => Some(Header::Level(4)),
            3 => Some(Header::Level(5)),
            _ => None,
        };
    }
    None
}

/// Header level for any header line (with or without `~` prefix). Used to
/// detect when an open graveyard region closes.
fn header_level(line: &str) -> Option<u8> {
    let bytes = line.as_bytes();
    let mut i = 0;
    if bytes.first() == Some(&b'~') {
        i = 1;
    }
    let start = i;
    let mut eq = 0;
    while bytes.get(i) == Some(&b'=') {
        eq += 1;
        i += 1;
    }
    if eq > 0 {
        if !matches!(bytes.get(i), Some(b' ') | Some(b'\t')) {
            return None;
        }
        return match eq {
            1 => Some(0),
            2 => Some(1),
            3 => Some(2),
            _ => None,
        };
    }
    let mut hash = 0;
    i = start;
    while bytes.get(i) == Some(&b'#') {
        hash += 1;
        i += 1;
    }
    if hash > 0 {
        return match hash {
            1 => Some(3),
            2 => Some(4),
            3 => Some(5),
            _ => None,
        };
    }
    None
}

/// True when the line is a single-line graveyard prose marker (`^~ ...`).
fn is_graveyard_prose(line: &str) -> bool {
    let bytes = line.as_bytes();
    bytes.first() == Some(&b'~') && matches!(bytes.get(1), Some(b' '))
}

/// Returns inclusive 0-indexed line ranges covering every graveyarded line
/// in `source` (header subtrees + single-line `~ prose`).
pub fn graveyard_line_ranges(source: &str) -> Vec<RangeInclusive<usize>> {
    let lines: Vec<&str> = source.split('\n').collect();
    let mut ranges: Vec<RangeInclusive<usize>> = Vec::new();
    let mut open: Option<(u8, usize)> = None; // (level, start_line)

    for (idx, line) in lines.iter().enumerate() {
        // Single-line graveyard prose: emit a 1-line range and move on.
        // Don't let it open or close a region, but also don't treat it as
        // a header.
        if is_graveyard_prose(line) {
            ranges.push(idx..=idx);
            continue;
        }

        if let Some(level) = header_level(line) {
            // Sibling-or-higher header closes any open region (the closing
            // header is *not* part of the graveyard).
            if let Some((open_level, start)) = open {
                if level <= open_level {
                    ranges.push(start..=idx.saturating_sub(1));
                    open = None;
                }
            }

            // A `~`-header opens (or extends to a shallower level) a region.
            if let Some(Header::Level(lvl)) = graveyard_header_level(line) {
                let new_open = match open {
                    Some((open_level, start)) if lvl < open_level => {
                        ranges.push(start..=idx.saturating_sub(1));
                        Some((lvl, idx))
                    }
                    None => Some((lvl, idx)),
                    Some(existing) => Some(existing),
                };
                open = new_open;
            }
        }
    }

    if let Some((_, start)) = open {
        ranges.push(start..=lines.len().saturating_sub(1));
    }

    ranges
}

/// Strip all graveyard regions from `source`, returning the live remainder.
///
/// Line numbering is preserved: graveyarded lines are replaced with empty
/// lines so byte-offset diagnostics from downstream tools still map back to
/// the original file positions.
pub fn strip_graveyard(source: &str) -> String {
    let ranges = graveyard_line_ranges(source);
    if ranges.is_empty() {
        return source.to_string();
    }

    let mut killed = vec![false; source.split('\n').count()];
    for range in &ranges {
        for i in *range.start()..=*range.end() {
            if let Some(slot) = killed.get_mut(i) {
                *slot = true;
            }
        }
    }

    source
        .split('\n')
        .enumerate()
        .map(|(i, line)| if killed[i] { "" } else { line })
        .collect::<Vec<_>>()
        .join("\n")
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn no_graveyard_returns_source_unchanged() {
        let src = "= Act 1\n# beat\nlive prose\n";
        assert_eq!(strip_graveyard(src), src);
        assert!(graveyard_line_ranges(src).is_empty());
    }

    #[test]
    fn single_line_prose_marker() {
        let src = "live\n~ killed\nstill live\n";
        let ranges = graveyard_line_ranges(src);
        assert_eq!(ranges, vec![1..=1]);
        let stripped = strip_graveyard(src);
        assert_eq!(stripped, "live\n\nstill live\n");
    }

    #[test]
    fn beat_subtree_closes_at_sibling_beat() {
        let src = "\
= Act\n\
~# old\n\
dead body\n\
# live\n\
live body\n";
        let ranges = graveyard_line_ranges(src);
        assert_eq!(ranges, vec![1..=2]);
        let stripped = strip_graveyard(src);
        assert!(!stripped.contains("dead body"));
        assert!(stripped.contains("live body"));
        // Closing header itself stays alive.
        assert!(stripped.contains("# live"));
    }

    #[test]
    fn act_subtree_closes_at_next_act() {
        let src = "\
~= Old Act\n\
== old scene\n\
old body\n\
= Live Act\n\
live body\n";
        let ranges = graveyard_line_ranges(src);
        assert_eq!(ranges, vec![0..=2]);
        let stripped = strip_graveyard(src);
        assert!(!stripped.contains("old body"));
        assert!(stripped.contains("live body"));
        assert!(stripped.contains("= Live Act"));
    }

    #[test]
    fn scene_inside_live_act_only_kills_scene() {
        let src = "\
= Act\n\
~== Old Scene\n\
old\n\
== Live Scene\n\
live\n";
        let ranges = graveyard_line_ranges(src);
        assert_eq!(ranges, vec![1..=2]);
        let stripped = strip_graveyard(src);
        assert!(stripped.contains("== Live Scene"));
        assert!(!stripped.contains("\nold\n"));
    }

    #[test]
    fn graveyard_extends_to_eof_when_no_closing_header() {
        let src = "\
= Act\n\
~# trailing graveyard\n\
dead\n\
more dead";
        let ranges = graveyard_line_ranges(src);
        assert_eq!(ranges, vec![1..=3]);
    }

    #[test]
    fn nested_shallower_graveyard_lowers_open_level() {
        // ~# opens at level 3; ~== inside lowers to level 1 and broadens scope
        // to act-level. The first range closes at the new ~ header.
        let src = "\
= Act\n\
~# beat-level\n\
dead beat\n\
~== scene-level\n\
dead scene\n\
= Live Act\n\
live\n";
        let ranges = graveyard_line_ranges(src);
        // Beat range closes when ~== opens; scene range closes at next `= Live Act`.
        assert_eq!(ranges, vec![1..=2, 3..=4]);
    }

    #[test]
    fn mid_line_tilde_is_not_graveyard() {
        let src = "She said ~5 minutes later it began.\n";
        assert!(graveyard_line_ranges(src).is_empty());
        assert_eq!(strip_graveyard(src), src);
    }

    #[test]
    fn tilde_without_space_is_not_prose_graveyard() {
        // ~5 at column 0 lacks the required space, so it stays prose.
        let src = "~5 minutes later\n";
        assert!(graveyard_line_ranges(src).is_empty());
    }

    #[test]
    fn line_numbering_preserved_after_strip() {
        // `# live` closes the graveyard region opened by `~#` so line4
        // survives stripping at the same line index.
        let src = "line0\n~# dead\ndead body\n# live\nline4\n";
        let stripped = strip_graveyard(src);
        let lines: Vec<&str> = stripped.split('\n').collect();
        assert_eq!(lines[0], "line0");
        assert_eq!(lines[1], "");
        assert_eq!(lines[2], "");
        assert_eq!(lines[3], "# live");
        assert_eq!(lines[4], "line4");
    }
}
