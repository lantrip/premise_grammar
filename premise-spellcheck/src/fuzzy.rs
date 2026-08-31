use std::collections::HashMap;

use serde::Serialize;

/// Fuzzy matcher for predictive text completion.
/// Uses a prefix trie for fast prefix lookups and edit distance for fuzzy matching.
#[derive(Default)]
pub struct FuzzyMatcher {
    /// Full entity names (multi-word)
    entity_names: Vec<String>,
    /// Trie for prefix lookups
    trie: PrefixTrie,
}

#[derive(Debug, Clone, Serialize)]
pub struct Completion {
    pub text: String,
    pub score: f32,
    pub source: CompletionSource,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "lowercase")]
pub enum CompletionSource {
    Entity,
    Dictionary,
}

impl FuzzyMatcher {
    pub fn new() -> Self {
        Self::default()
    }

    /// Set entity names for completion. Replaces any previous entities.
    pub fn set_entities(&mut self, entities: &[String]) {
        self.entity_names = entities.to_vec();
        self.trie = PrefixTrie::new();
        for (i, entity) in entities.iter().enumerate() {
            self.trie.insert(&entity.to_lowercase(), i);
            // Also insert individual words for partial matching
            for word in entity.split_whitespace() {
                let clean = word.trim_matches(|c: char| !c.is_alphanumeric());
                if clean.len() >= 2 {
                    self.trie.insert(&clean.to_lowercase(), i);
                }
            }
        }
    }

    /// Complete a prefix, returning matching entity names ranked by relevance.
    pub fn complete_prefix(&self, prefix: &str, max: usize) -> Vec<Completion> {
        if prefix.len() < 2 {
            return vec![];
        }

        let prefix_lower = prefix.to_lowercase();
        let indices = self.trie.find_prefix(&prefix_lower, max * 2);

        let mut seen = std::collections::HashSet::new();
        let mut results = Vec::new();

        for idx in indices {
            if idx < self.entity_names.len() && seen.insert(idx) {
                let name = &self.entity_names[idx];
                // Score: exact prefix match scores higher, shorter names score higher
                let name_lower = name.to_lowercase();
                let starts_with = name_lower.starts_with(&prefix_lower) as u8 as f32;
                let length_penalty = 1.0 / (name.len() as f32).sqrt();
                let score = starts_with * 0.5 + length_penalty * 0.5;

                results.push(Completion {
                    text: name.clone(),
                    score,
                    source: CompletionSource::Entity,
                });
            }
        }

        results.sort_by(|a, b| {
            b.score
                .partial_cmp(&a.score)
                .unwrap_or(std::cmp::Ordering::Equal)
        });
        results.truncate(max);
        results
    }

    /// Fuzzy match against entity names using edit distance.
    pub fn fuzzy_match(&self, query: &str, max: usize) -> Vec<Completion> {
        if query.len() < 2 {
            return vec![];
        }

        let query_lower = query.to_lowercase();
        let mut results = Vec::new();

        for name in &self.entity_names {
            let name_lower = name.to_lowercase();

            // Check each word in the entity name
            let best_dist = name_lower
                .split_whitespace()
                .map(|word| edit_distance_bounded(&query_lower, word, 3))
                .min()
                .unwrap_or(usize::MAX);

            // Also check if query is a substring
            let contains = name_lower.contains(&query_lower);

            if best_dist <= 2 || contains {
                let score = if contains {
                    0.9
                } else {
                    1.0 - (best_dist as f32 / 3.0)
                };

                results.push(Completion {
                    text: name.clone(),
                    score,
                    source: CompletionSource::Entity,
                });
            }
        }

        results.sort_by(|a, b| {
            b.score
                .partial_cmp(&a.score)
                .unwrap_or(std::cmp::Ordering::Equal)
        });
        results.truncate(max);
        results
    }
}

/// Simple prefix trie for fast lookups.
#[derive(Default)]
struct PrefixTrie {
    root: TrieNode,
}

#[derive(Default)]
struct TrieNode {
    children: HashMap<char, TrieNode>,
    /// Indices into the entity list for entries that pass through this node
    indices: Vec<usize>,
}

impl PrefixTrie {
    fn new() -> Self {
        Self::default()
    }

    fn insert(&mut self, word: &str, index: usize) {
        let mut node = &mut self.root;
        for ch in word.chars() {
            node = node.children.entry(ch).or_default();
            node.indices.push(index);
        }
    }

    /// Find all entity indices matching a prefix, up to `max` results.
    fn find_prefix(&self, prefix: &str, max: usize) -> Vec<usize> {
        let mut node = &self.root;
        for ch in prefix.chars() {
            match node.children.get(&ch) {
                Some(child) => node = child,
                None => return vec![],
            }
        }
        // Return indices at this node (all entries with this prefix)
        node.indices.iter().copied().take(max).collect()
    }
}

/// Bounded edit distance — returns early if distance exceeds max.
fn edit_distance_bounded(a: &str, b: &str, max: usize) -> usize {
    let a_chars: Vec<char> = a.chars().collect();
    let b_chars: Vec<char> = b.chars().collect();
    let m = a_chars.len();
    let n = b_chars.len();

    if m.abs_diff(n) > max {
        return max + 1;
    }

    let mut prev = vec![0usize; n + 1];
    let mut curr = vec![0usize; n + 1];

    for (j, slot) in prev.iter_mut().enumerate() {
        *slot = j;
    }

    for i in 1..=m {
        curr[0] = i;
        let mut min_in_row = curr[0];

        for j in 1..=n {
            let cost = if a_chars[i - 1] == b_chars[j - 1] {
                0
            } else {
                1
            };

            curr[j] = (prev[j] + 1).min(curr[j - 1] + 1).min(prev[j - 1] + cost);

            min_in_row = min_in_row.min(curr[j]);
        }

        if min_in_row > max {
            return max + 1;
        }

        std::mem::swap(&mut prev, &mut curr);
    }

    prev[n]
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_prefix_completion() {
        let mut fm = FuzzyMatcher::new();
        fm.set_entities(&[
            "Maya Chen".to_string(),
            "Marcus Webb".to_string(),
            "Nebula Station".to_string(),
        ]);

        let results = fm.complete_prefix("ma", 5);
        assert!(!results.is_empty());
        // Both "Maya Chen" and "Marcus Webb" should match "ma"
        let names: Vec<&str> = results.iter().map(|c| c.text.as_str()).collect();
        assert!(names.contains(&"Maya Chen"));
        assert!(names.contains(&"Marcus Webb"));
    }

    #[test]
    fn test_fuzzy_match() {
        let mut fm = FuzzyMatcher::new();
        fm.set_entities(&["Adaptipatable".to_string(), "Adventure".to_string()]);

        let results = fm.fuzzy_match("Ada", 5);
        assert!(!results.is_empty());
        let names: Vec<&str> = results.iter().map(|c| c.text.as_str()).collect();
        assert!(names.contains(&"Adaptipatable"));
    }

    #[test]
    fn test_short_query_returns_empty() {
        let mut fm = FuzzyMatcher::new();
        fm.set_entities(&["Maya Chen".to_string()]);

        let results = fm.complete_prefix("m", 5);
        assert!(results.is_empty());
    }
}
