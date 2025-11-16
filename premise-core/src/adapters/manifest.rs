// Adapter manifest schema
//
// Defines the metadata and capabilities of a Premise adapter

use schemars::JsonSchema;
use serde::{Deserialize, Serialize};

/// Adapter manifest containing metadata and capabilities
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct AdapterManifest {
    /// Unique adapter identifier (e.g., "premise-screenplay-pdf")
    pub id: String,

    /// Human-readable name
    pub name: String,

    /// Adapter version (semver)
    pub version: String,

    /// Brief description
    pub description: String,

    /// Target domain(s) this adapter supports
    pub domains: Vec<String>,

    /// Adapter capabilities
    pub capabilities: AdapterCapabilities,

    /// Entry point (executable path or module)
    pub entry_point: String,

    /// Author information
    #[serde(skip_serializing_if = "Option::is_none")]
    pub author: Option<String>,

    /// Repository URL
    #[serde(skip_serializing_if = "Option::is_none")]
    pub repository: Option<String>,
}

/// Capabilities an adapter can provide
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct AdapterCapabilities {
    /// Can generate artifacts (PDF, HTML, etc.)
    pub generates_artifacts: bool,

    /// Can query notes for context
    pub uses_notes_context: bool,

    /// Can contribute new facts to notes
    pub contributes_facts: bool,

    /// Output formats supported
    pub output_formats: Vec<String>,

    /// Entity types this adapter understands
    pub entity_types: Vec<String>,
}

/// Domain-specific configuration for adapters
#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct DomainConfig {
    /// Domain identifier (e.g., "narrative", "sales", "architecture")
    pub domain: String,

    /// Entity type mappings (e.g., "character" -> "participant")
    #[serde(default)]
    pub entity_mappings: std::collections::HashMap<String, String>,

    /// Section type mappings (e.g., "act" -> "module")
    #[serde(default)]
    pub section_mappings: std::collections::HashMap<String, String>,

    /// Custom domain-specific settings
    #[serde(default)]
    pub custom_settings: std::collections::HashMap<String, serde_json::Value>,
}

impl AdapterManifest {
    /// Check if adapter supports a specific domain
    pub fn supports_domain(&self, domain: &str) -> bool {
        self.domains.iter().any(|d| d == domain || d == "*")
    }

    /// Check if adapter can generate a specific output format
    pub fn supports_format(&self, format: &str) -> bool {
        self.capabilities
            .output_formats
            .iter()
            .any(|f| f.eq_ignore_ascii_case(format))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_manifest_creation() {
        let manifest = AdapterManifest {
            id: "test-adapter".to_string(),
            name: "Test Adapter".to_string(),
            version: "1.0.0".to_string(),
            description: "A test adapter".to_string(),
            domains: vec!["narrative".to_string()],
            capabilities: AdapterCapabilities {
                generates_artifacts: true,
                uses_notes_context: true,
                contributes_facts: false,
                output_formats: vec!["pdf".to_string()],
                entity_types: vec!["character".to_string()],
            },
            entry_point: "./adapters/test.js".to_string(),
            author: None,
            repository: None,
        };

        assert!(manifest.supports_domain("narrative"));
        assert!(!manifest.supports_domain("sales"));
        assert!(manifest.supports_format("pdf"));
        assert!(manifest.supports_format("PDF"));
    }
}
