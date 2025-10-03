pub mod schema;
pub mod io;
pub mod normalize;
pub mod sink;
pub mod extract_text;
pub mod schemas;
pub mod discovery;
pub mod orchestrate;

pub use schema::*;
pub use io::*;
pub use normalize::*;
pub use sink::*;
pub use extract_text::*;
pub use schemas::*;
pub use discovery::*;
pub use orchestrate::*;

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
