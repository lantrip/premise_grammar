use crate::schema::*;
use schemars::schema::RootSchema;

/// Export JSON Schemas for all public notes types
pub fn export_all() -> Vec<(String, RootSchema)> {
    vec![
        ("Beat".into(), schemars::schema_for!(Beat)),
        ("Fact".into(), schemars::schema_for!(Fact)),
        ("TimelineEvent".into(), schemars::schema_for!(TimelineEvent)),
        (
            "ConsistencyEntry".into(),
            schemars::schema_for!(ConsistencyEntry),
        ),
        ("NotesIndex".into(), schemars::schema_for!(NotesIndex)),
        ("NotesMetadata".into(), schemars::schema_for!(NotesMetadata)),
        ("NotesRecord".into(), schemars::schema_for!(NotesRecord)),
        ("Provenance".into(), schemars::schema_for!(Provenance)),
    ]
}

/// Export schema for a single type by name; returns None if not found
pub fn export_one(name: &str) -> Option<RootSchema> {
    match name {
        "Beat" => Some(schemars::schema_for!(Beat)),
        "Fact" => Some(schemars::schema_for!(Fact)),
        "TimelineEvent" => Some(schemars::schema_for!(TimelineEvent)),
        "ConsistencyEntry" => Some(schemars::schema_for!(ConsistencyEntry)),
        "NotesIndex" => Some(schemars::schema_for!(NotesIndex)),
        "NotesMetadata" => Some(schemars::schema_for!(NotesMetadata)),
        "NotesRecord" => Some(schemars::schema_for!(NotesRecord)),
        "Provenance" => Some(schemars::schema_for!(Provenance)),
        _ => None,
    }
}
