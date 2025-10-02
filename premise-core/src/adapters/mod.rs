// Adapter framework for domain-agnostic content transformation
//
// This module provides the foundation for adapters that can:
// - Transform Premise IR into domain-specific artifacts
// - Query the notes system for context
// - Track provenance of generated content
// - Support multiple domains (narrative, sales, architecture, etc.)

pub mod manifest;
pub mod registry;
pub mod context;
pub mod domain;

pub use manifest::*;
pub use registry::*;
pub use context::*;
pub use domain::*;
