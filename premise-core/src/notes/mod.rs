// Re-export shared notes crate
pub use premise_notes as notes_core;
pub use premise_notes::*;

// Premise-specific modules remain here
pub mod extract;
pub mod extract_enhanced;
pub mod entity_discovery;
pub use extract::*;
pub use extract_enhanced::*;
pub use entity_discovery::*;
