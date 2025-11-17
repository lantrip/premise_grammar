pub mod discovery;
pub mod extract_pipeline;
pub mod extract_text;
pub mod extractor;
pub mod importance;
pub mod io;
pub mod normalize;
pub mod orchestrate;
pub mod schema;
pub mod schemas;
pub mod sink;

pub use discovery::*;
pub use extract_pipeline::*;
pub use extract_text::*;
pub use extractor::*;
pub use importance::*;
pub use io::*;
pub use normalize::*;
pub use orchestrate::*;
pub use schema::*;
pub use schemas::*;
pub use sink::*;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn schema_export_has_core_types() {
        let all = export_all();
        let names: std::collections::HashSet<String> = all.into_iter().map(|(n, _)| n).collect();
        assert!(names.contains("Beat"));
        assert!(names.contains("Fact"));
    }
}
