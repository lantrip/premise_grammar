use crate::extract_text::{
    extract_beats_from_text, extract_facts_from_text, TextExtractionOptions,
};
use crate::schema::{Beat, Fact};

pub trait Extractor {
    fn extract_beats(&self, text: &str, opts: &TextExtractionOptions) -> Vec<Beat>;
    fn extract_facts(&self, text: &str, file_label: &str) -> Vec<Fact>;
}

#[derive(Default, Debug, Clone)]
pub struct HeuristicExtractor;

impl HeuristicExtractor {
    pub fn new() -> Self {
        Self
    }
}

impl Extractor for HeuristicExtractor {
    fn extract_beats(&self, text: &str, opts: &TextExtractionOptions) -> Vec<Beat> {
        extract_beats_from_text(text, opts)
    }
    fn extract_facts(&self, text: &str, file_label: &str) -> Vec<Fact> {
        extract_facts_from_text(text, file_label)
    }
}
