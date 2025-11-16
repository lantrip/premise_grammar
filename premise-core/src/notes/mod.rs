// Re-export shared notes crate
pub use premise_notes as notes_core;
pub use premise_notes::*;

// Premise-specific modules remain here
pub mod entity_discovery;
pub mod extract;
pub mod extract_enhanced;
pub use extract::*;
pub use extract_enhanced::*;
// Intentionally do not glob re-export entity_discovery to avoid ambiguous names with premise_notes
