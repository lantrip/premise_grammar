// Domain model abstraction
//
// Provides domain-agnostic interfaces for working with Premise IR across different use cases

use crate::ir::{Act, Cel, Scene};
use serde::{Deserialize, Serialize};
use schemars::JsonSchema;

/// Domain-agnostic entity representation
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct DomainEntity {
    /// Entity name
    pub name: String,

    /// Entity type in this domain (e.g., "character", "participant", "component")
    pub entity_type: String,

    /// Original Premise entity type (e.g., "character")
    pub source_type: String,

    /// Description or definition
    #[serde(skip_serializing_if = "Option::is_none")]
    pub description: Option<String>,

    /// Additional domain-specific properties
    #[serde(default)]
    pub properties: std::collections::HashMap<String, serde_json::Value>,
}

/// Domain-agnostic section representation
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct DomainSection {
    /// Section ID (stable across runs)
    pub id: String,

    /// Section title
    pub title: String,

    /// Section level (1=act, 2=scene, 3=cel)
    pub level: u8,

    /// Section type in this domain (e.g., "act", "call-segment", "module")
    pub section_type: String,

    /// Original Premise section type ("act", "scene", "cel")
    pub source_type: String,

    /// Parent section ID (if any)
    #[serde(skip_serializing_if = "Option::is_none")]
    pub parent_id: Option<String>,

    /// Range in source file
    #[serde(skip_serializing_if = "Option::is_none")]
    pub range: Option<crate::ast::Range>,
}

/// Domain model mapper for transforming IR to domain-specific representations
pub trait DomainMapper {
    /// Map an entity type from Premise to domain-specific type
    fn map_entity_type(&self, premise_type: &str) -> String;

    /// Map a section type from Premise to domain-specific type
    fn map_section_type(&self, premise_type: &str, level: u8) -> String;

    /// Get the domain identifier
    fn domain_id(&self) -> &str;
}

/// Default narrative domain mapper (1:1 mapping)
pub struct NarrativeDomainMapper;

impl DomainMapper for NarrativeDomainMapper {
    fn map_entity_type(&self, premise_type: &str) -> String {
        premise_type.to_string()
    }

    fn map_section_type(&self, premise_type: &str, _level: u8) -> String {
        premise_type.to_string()
    }

    fn domain_id(&self) -> &str {
        "narrative"
    }
}

/// Sales call domain mapper
pub struct SalesDomainMapper;

impl DomainMapper for SalesDomainMapper {
    fn map_entity_type(&self, premise_type: &str) -> String {
        match premise_type {
            "character" => "participant".to_string(),
            "location" => "company".to_string(),
            _ => premise_type.to_string(),
        }
    }

    fn map_section_type(&self, premise_type: &str, _level: u8) -> String {
        match premise_type {
            "act" => "call".to_string(),
            "scene" => "segment".to_string(),
            "cel" => "moment".to_string(),
            _ => premise_type.to_string(),
        }
    }

    fn domain_id(&self) -> &str {
        "sales"
    }
}

/// Architecture/code domain mapper
pub struct ArchitectureDomainMapper;

impl DomainMapper for ArchitectureDomainMapper {
    fn map_entity_type(&self, premise_type: &str) -> String {
        match premise_type {
            "character" => "component".to_string(),
            "location" => "service".to_string(),
            _ => premise_type.to_string(),
        }
    }

    fn map_section_type(&self, premise_type: &str, _level: u8) -> String {
        match premise_type {
            "act" => "module".to_string(),
            "scene" => "feature".to_string(),
            "cel" => "function".to_string(),
            _ => premise_type.to_string(),
        }
    }

    fn domain_id(&self) -> &str {
        "architecture"
    }
}

/// Convert Act to DomainSection
pub fn act_to_domain_section(act: &Act, mapper: &dyn DomainMapper, id: String) -> DomainSection {
    DomainSection {
        id,
        title: act.title.clone(),
        level: 1,
        section_type: mapper.map_section_type("act", 1),
        source_type: "act".to_string(),
        parent_id: None,
        range: Some(act.range),
    }
}

/// Convert Scene to DomainSection
pub fn scene_to_domain_section(
    scene: &Scene,
    mapper: &dyn DomainMapper,
    id: String,
    parent_id: Option<String>,
) -> DomainSection {
    DomainSection {
        id,
        title: scene.title.clone(),
        level: 2,
        section_type: mapper.map_section_type("scene", 2),
        source_type: "scene".to_string(),
        parent_id,
        range: Some(scene.range),
    }
}

/// Convert Cel to DomainSection
pub fn cel_to_domain_section(
    cel: &Cel,
    mapper: &dyn DomainMapper,
    id: String,
    parent_id: Option<String>,
) -> DomainSection {
    DomainSection {
        id,
        title: cel.title.clone(),
        level: 3,
        section_type: mapper.map_section_type("cel", 3),
        source_type: "cel".to_string(),
        parent_id,
        range: Some(cel.range),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_narrative_mapper() {
        let mapper = NarrativeDomainMapper;
        assert_eq!(mapper.map_entity_type("character"), "character");
        assert_eq!(mapper.map_section_type("act", 1), "act");
        assert_eq!(mapper.domain_id(), "narrative");
    }

    #[test]
    fn test_sales_mapper() {
        let mapper = SalesDomainMapper;
        assert_eq!(mapper.map_entity_type("character"), "participant");
        assert_eq!(mapper.map_section_type("act", 1), "call");
        assert_eq!(mapper.domain_id(), "sales");
    }

    #[test]
    fn test_architecture_mapper() {
        let mapper = ArchitectureDomainMapper;
        assert_eq!(mapper.map_entity_type("character"), "component");
        assert_eq!(mapper.map_section_type("act", 1), "module");
        assert_eq!(mapper.domain_id(), "architecture");
    }
}
