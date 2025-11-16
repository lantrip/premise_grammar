// Adapter registry for discovery and management
//
// Provides functionality to discover, load, and manage adapters

use super::manifest::AdapterManifest;
use std::io;
use std::path::{Path, PathBuf};

/// Adapter registry that manages available adapters
#[derive(Debug, Clone)]
pub struct AdapterRegistry {
    adapters: Vec<AdapterManifest>,
    search_paths: Vec<PathBuf>,
}

impl AdapterRegistry {
    /// Create a new empty registry
    pub fn new() -> Self {
        Self {
            adapters: Vec::new(),
            search_paths: Vec::new(),
        }
    }

    /// Add a search path for adapter discovery
    pub fn add_search_path<P: AsRef<Path>>(&mut self, path: P) {
        self.search_paths.push(path.as_ref().to_path_buf());
    }

    /// Discover adapters in search paths
    pub fn discover(&mut self) -> io::Result<usize> {
        self.adapters.clear();
        let mut count = 0;

        for search_path in &self.search_paths {
            if !search_path.exists() {
                continue;
            }

            // Look for adapter manifest files (adapter.json or premise-adapter.json)
            if let Ok(entries) = std::fs::read_dir(search_path) {
                for entry in entries.flatten() {
                    let path = entry.path();

                    // Check if this is an adapter directory
                    let manifest_path = path.join("adapter.json");
                    let alt_manifest_path = path.join("premise-adapter.json");

                    let manifest_file = if manifest_path.exists() {
                        Some(manifest_path)
                    } else if alt_manifest_path.exists() {
                        Some(alt_manifest_path)
                    } else {
                        None
                    };

                    if let Some(manifest_file) = manifest_file {
                        if let Ok(manifest) = Self::load_manifest(&manifest_file) {
                            self.adapters.push(manifest);
                            count += 1;
                        }
                    }
                }
            }
        }

        Ok(count)
    }

    /// Load a manifest from a JSON file
    fn load_manifest(path: &Path) -> io::Result<AdapterManifest> {
        let content = std::fs::read_to_string(path)?;
        serde_json::from_str(&content).map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))
    }

    /// Get all registered adapters
    pub fn list_all(&self) -> &[AdapterManifest] {
        &self.adapters
    }

    /// Find adapter by ID
    pub fn find_by_id(&self, id: &str) -> Option<&AdapterManifest> {
        self.adapters.iter().find(|a| a.id == id)
    }

    /// Find adapters by domain
    pub fn find_by_domain(&self, domain: &str) -> Vec<&AdapterManifest> {
        self.adapters
            .iter()
            .filter(|a| a.supports_domain(domain))
            .collect()
    }

    /// Find adapters by capability
    pub fn find_by_capability(
        &self,
        predicate: impl Fn(&AdapterManifest) -> bool,
    ) -> Vec<&AdapterManifest> {
        self.adapters.iter().filter(|a| predicate(a)).collect()
    }

    /// Register an adapter manually
    pub fn register(&mut self, manifest: AdapterManifest) {
        // Remove existing adapter with same ID
        self.adapters.retain(|a| a.id != manifest.id);
        self.adapters.push(manifest);
    }
}

impl Default for AdapterRegistry {
    fn default() -> Self {
        Self::new()
    }
}

/// Get default adapter search paths
pub fn default_search_paths() -> Vec<PathBuf> {
    let mut paths = Vec::new();

    // 1. Current directory ./adapters
    paths.push(PathBuf::from("./adapters"));

    // 2. User home directory ~/.premise/adapters
    if let Some(home) = dirs::home_dir() {
        paths.push(home.join(".premise").join("adapters"));
    }

    // 3. System-wide /usr/local/share/premise/adapters (Unix)
    #[cfg(unix)]
    paths.push(PathBuf::from("/usr/local/share/premise/adapters"));

    // 4. Environment variable PREMISE_ADAPTERS_PATH
    if let Ok(env_path) = std::env::var("PREMISE_ADAPTERS_PATH") {
        for path in env_path.split(':') {
            paths.push(PathBuf::from(path));
        }
    }

    paths
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::adapters::manifest::{AdapterCapabilities, AdapterManifest};

    #[test]
    fn test_registry_operations() {
        let mut registry = AdapterRegistry::new();

        let manifest = AdapterManifest {
            id: "test-adapter".to_string(),
            name: "Test".to_string(),
            version: "1.0.0".to_string(),
            description: "Test adapter".to_string(),
            domains: vec!["narrative".to_string()],
            capabilities: AdapterCapabilities {
                generates_artifacts: true,
                uses_notes_context: false,
                contributes_facts: false,
                output_formats: vec!["pdf".to_string()],
                entity_types: vec!["character".to_string()],
            },
            entry_point: "./test.js".to_string(),
            author: None,
            repository: None,
        };

        registry.register(manifest.clone());
        assert_eq!(registry.list_all().len(), 1);
        assert!(registry.find_by_id("test-adapter").is_some());

        let narrative_adapters = registry.find_by_domain("narrative");
        assert_eq!(narrative_adapters.len(), 1);
    }
}
