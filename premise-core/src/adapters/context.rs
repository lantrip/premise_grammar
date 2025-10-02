// Notes context API for adapters
//
// Provides adapters with read access to the notes system for context-aware generation

use crate::notes::{Beat, Fact, FactType};
use std::path::Path;
use std::io;

/// Notes context interface for adapters
pub struct NotesContext {
    story_root: std::path::PathBuf,
}

impl NotesContext {
    /// Create a new notes context for a story root
    pub fn new<P: AsRef<Path>>(story_root: P) -> Self {
        Self {
            story_root: story_root.as_ref().to_path_buf(),
        }
    }

    /// Get all facts for a specific entity
    pub fn get_entity_facts(&self, entity: &str) -> io::Result<Vec<Fact>> {
        let all_facts = crate::notes::read_facts(&self.story_root)?;
        Ok(all_facts
            .into_iter()
            .filter(|f| {
                f.entity.as_deref() == Some(entity)
                    || f.entities.as_ref().map_or(false, |entities| {
                        entities.iter().any(|e| e == entity)
                    })
            })
            .collect())
    }

    /// Get facts filtered by type
    pub fn get_facts_by_type(&self, fact_type: FactType) -> io::Result<Vec<Fact>> {
        let all_facts = crate::notes::read_facts(&self.story_root)?;
        Ok(all_facts
            .into_iter()
            .filter(|f| f.fact_type == fact_type)
            .collect())
    }

    /// Get facts with minimum confidence threshold
    pub fn get_facts_with_confidence(&self, min_confidence: f64) -> io::Result<Vec<Fact>> {
        let all_facts = crate::notes::read_facts(&self.story_root)?;
        Ok(all_facts
            .into_iter()
            .filter(|f| f.confidence.unwrap_or(0.0) >= min_confidence)
            .collect())
    }

    /// Get relationship facts between two entities
    pub fn get_relationship(&self, entity1: &str, entity2: &str) -> io::Result<Vec<Fact>> {
        let all_facts = crate::notes::read_facts(&self.story_root)?;
        Ok(all_facts
            .into_iter()
            .filter(|f| {
                f.fact_type == FactType::Relationship
                    && f.entities.as_ref().map_or(false, |entities| {
                        entities.contains(&entity1.to_string())
                            && entities.contains(&entity2.to_string())
                    })
            })
            .collect())
    }

    /// Get all beats for a specific entity
    pub fn get_entity_beats(&self, entity: &str) -> io::Result<Vec<Beat>> {
        let all_beats = crate::notes::read_beats(&self.story_root)?;
        Ok(all_beats
            .into_iter()
            .filter(|b| b.entities.contains(&entity.to_string()))
            .collect())
    }

    /// Get beats for a specific section
    pub fn get_section_beats(&self, section_id: &str) -> io::Result<Vec<Beat>> {
        let all_beats = crate::notes::read_beats(&self.story_root)?;
        Ok(all_beats
            .into_iter()
            .filter(|b| {
                b.section.as_ref().map_or(false, |s| {
                    // Match by act, scene, or cel title
                    s.act.as_deref().map_or(false, |a| a == section_id)
                        || s.scene.as_deref().map_or(false, |sc| sc == section_id)
                        || s.cel.as_deref().map_or(false, |c| c == section_id)
                })
            })
            .collect())
    }

    /// Get all entity names mentioned in notes
    pub fn get_all_entities(&self) -> io::Result<Vec<String>> {
        let all_facts = crate::notes::read_facts(&self.story_root)?;
        let mut entities = std::collections::HashSet::new();

        for fact in all_facts {
            if let Some(entity) = &fact.entity {
                entities.insert(entity.clone());
            }
            if let Some(fact_entities) = &fact.entities {
                for entity in fact_entities {
                    entities.insert(entity.clone());
                }
            }
        }

        let mut result: Vec<String> = entities.into_iter().collect();
        result.sort();
        Ok(result)
    }

    /// Check if notes exist for this story
    pub fn has_notes(&self) -> bool {
        let notes_dir = self.story_root.join(".premise-notes");
        notes_dir.exists() && notes_dir.is_dir()
    }

    /// Get story root path
    pub fn story_root(&self) -> &Path {
        &self.story_root
    }
}

/// Builder for querying facts with multiple criteria
pub struct FactQuery {
    entity: Option<String>,
    fact_type: Option<FactType>,
    min_confidence: Option<f64>,
    category: Option<String>,
}

impl FactQuery {
    pub fn new() -> Self {
        Self {
            entity: None,
            fact_type: None,
            min_confidence: None,
            category: None,
        }
    }

    pub fn entity(mut self, entity: impl Into<String>) -> Self {
        self.entity = Some(entity.into());
        self
    }

    pub fn fact_type(mut self, fact_type: FactType) -> Self {
        self.fact_type = Some(fact_type);
        self
    }

    pub fn min_confidence(mut self, confidence: f64) -> Self {
        self.min_confidence = Some(confidence);
        self
    }

    pub fn category(mut self, category: impl Into<String>) -> Self {
        self.category = Some(category.into());
        self
    }

    pub fn execute(&self, context: &NotesContext) -> io::Result<Vec<Fact>> {
        let all_facts = crate::notes::read_facts(context.story_root())?;

        Ok(all_facts
            .into_iter()
            .filter(|f| {
                // Filter by entity
                if let Some(ref entity) = self.entity {
                    let matches_entity = f.entity.as_deref() == Some(entity.as_str())
                        || f.entities.as_ref().map_or(false, |entities| {
                            entities.iter().any(|e| e == entity)
                        });
                    if !matches_entity {
                        return false;
                    }
                }

                // Filter by type
                if let Some(ref fact_type) = self.fact_type {
                    if &f.fact_type != fact_type {
                        return false;
                    }
                }

                // Filter by confidence
                if let Some(min_conf) = self.min_confidence {
                    if f.confidence.unwrap_or(0.0) < min_conf {
                        return false;
                    }
                }

                // Filter by category
                if let Some(ref category) = self.category {
                    if f.category.as_deref() != Some(category.as_str()) {
                        return false;
                    }
                }

                true
            })
            .collect())
    }
}

impl Default for FactQuery {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_notes_context_creation() {
        let context = NotesContext::new("/tmp/test-story");
        assert_eq!(context.story_root(), Path::new("/tmp/test-story"));
    }

    #[test]
    fn test_fact_query_builder() {
        let query = FactQuery::new()
            .entity("Hero")
            .fact_type(FactType::Trait)
            .min_confidence(0.8);

        assert_eq!(query.entity, Some("Hero".to_string()));
        assert_eq!(query.fact_type, Some(FactType::Trait));
        assert_eq!(query.min_confidence, Some(0.8));
    }
}
