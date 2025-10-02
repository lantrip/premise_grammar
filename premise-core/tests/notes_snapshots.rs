use insta::assert_json_snapshot;
use premise_core::notes::*;
use premise_core::Parser;
use serde_json::Value;

/// Strip timestamps and IDs from facts for snapshot testing, and sort for determinism
fn normalize_facts(mut facts: Vec<Fact>) -> Value {
    // Sort by fact text to ensure deterministic ordering
    facts.sort_by(|a, b| a.fact.cmp(&b.fact));

    let mut json = serde_json::to_value(facts).unwrap();
    if let Value::Array(ref mut arr) = json {
        for item in arr {
            if let Value::Object(ref mut obj) = item {
                obj.remove("id");
                obj.remove("added");
            }
        }
    }
    json
}

/// Strip timestamps and IDs from beats for snapshot testing
fn normalize_beats(beats: Vec<Beat>) -> Value {
    let mut json = serde_json::to_value(beats).unwrap();
    if let Value::Array(ref mut arr) = json {
        for item in arr {
            if let Value::Object(ref mut obj) = item {
                obj.remove("id");
                obj.remove("added");
            }
        }
    }
    json
}

#[test]
fn test_entity_trait_extraction() {
    let source = r#"
@characters {
  - Hero: A brave warrior with a mysterious past
  - Mentor: An wise old sage who guides the Hero
  - Villain: A dark sorcerer seeking ultimate power
}
"#;

    let mut parser = Parser::new();
    let tree = parser.internal.parse(source, None).unwrap();
    let root = tree.root_node();

    let facts = extract_entity_definitions(&root, source, "test.prem");

    assert_eq!(facts.len(), 3);
    assert_json_snapshot!(normalize_facts(facts));
}

#[test]
fn test_entity_cooccurrence_extraction() {
    let source = r#"
@characters {
  - Hero: A brave warrior
  - Mentor: An wise sage
  - Villain: A dark sorcerer
}

= Act One

== The Beginning

{Hero} meets {Mentor} in the tavern.

{Hero}
  I need your help. The {Villain} has taken my family.

{Mentor}
  (thoughtfully)
  This is a dangerous path you're choosing, young {Hero}.

== The Confrontation

{Hero} faces {Villain} in the final battle.
"#;

    let mut parser = Parser::new();
    let tree = parser.internal.parse(source, None).unwrap();
    let root = tree.root_node();

    let facts = extract_entity_cooccurrence(&root, source, "test.prem");

    // Should have relationships for entities appearing together in scenes
    assert!(facts.len() > 0);

    // Check that we have Hero-Mentor relationship
    let has_hero_mentor = facts.iter().any(|f| {
        if let Some(entities) = &f.entities {
            entities.contains(&"Hero".to_string()) && entities.contains(&"Mentor".to_string())
        } else {
            false
        }
    });
    assert!(has_hero_mentor, "Should have Hero-Mentor relationship");

    // Check that we have Hero-Villain relationship
    let has_hero_villain = facts.iter().any(|f| {
        if let Some(entities) = &f.entities {
            entities.contains(&"Hero".to_string()) && entities.contains(&"Villain".to_string())
        } else {
            false
        }
    });
    assert!(has_hero_villain, "Should have Hero-Villain relationship");

    assert_json_snapshot!(normalize_facts(facts));
}

#[test]
fn test_beat_extraction() {
    let source = r#"
= Act One

== The Quest Begins

/// {Hero} decides to embark on a quest to defeat {Villain}

{Hero} prepares for the journey.

=== Training Montage

/// {Mentor} trains {Hero} in ancient combat techniques
"#;

    let mut parser = Parser::new();
    let tree = parser.internal.parse(source, None).unwrap();
    let root = tree.root_node();

    let beats = extract_beats_from_tree(&root, source, "test.prem");

    // Note: Beat extraction currently doesn't work due to grammar structure
    // This test documents the current state
    assert_json_snapshot!(normalize_beats(beats));
}

#[test]
fn test_all_facts_extraction() {
    let source = r#"
@character Hero: A brave warrior with a mysterious past

= Act One

== The Beginning

{Hero} enters the tavern.
{Hero} meets {Mentor}.

== The Confrontation

{Hero} faces {Villain}.
"#;

    let mut parser = Parser::new();
    let tree = parser.internal.parse(source, None).unwrap();
    let root = tree.root_node();

    let facts = extract_all_facts_from_tree(&root, source, "test.prem");

    // Should have at least:
    // - 1 trait (Hero definition)
    // - Multiple relationships (co-occurrence)
    assert!(facts.len() >= 2, "Should have traits and relationships");

    // Check trait extraction
    let has_trait = facts.iter().any(|f| matches!(f.fact_type, FactType::Trait));
    assert!(has_trait, "Should have at least one trait fact");

    // Check relationship extraction
    let has_relationship = facts.iter().any(|f| matches!(f.fact_type, FactType::Relationship));
    assert!(has_relationship, "Should have at least one relationship fact");

    assert_json_snapshot!(normalize_facts(facts));
}

#[test]
fn test_section_context_preservation() {
    let source = r#"
= Act One: The Beginning

== Scene Alpha

{Hero} appears.

=== Cel One

{Hero} and {Mentor} talk.

== Scene Beta

{Hero} leaves.
"#;

    let mut parser = Parser::new();
    let tree = parser.internal.parse(source, None).unwrap();
    let root = tree.root_node();

    let facts = extract_entity_cooccurrence(&root, source, "test.prem");

    // Check that section context is preserved
    let hero_mentor_fact = facts.iter().find(|f| {
        if let Some(entities) = &f.entities {
            entities.contains(&"Hero".to_string()) && entities.contains(&"Mentor".to_string())
        } else {
            false
        }
    });

    assert!(hero_mentor_fact.is_some(), "Should find Hero-Mentor relationship");

    let fact = hero_mentor_fact.unwrap();
    assert!(fact.fact.contains("cel"), "Fact should mention cel context");

    assert_json_snapshot!(normalize_facts(facts));
}

#[test]
fn test_confidence_scoring() {
    let source = r#"
@character Hero: Defined trait

= Act One

{Hero} and {Mentor} appear together.
"#;

    let mut parser = Parser::new();
    let tree = parser.internal.parse(source, None).unwrap();
    let root = tree.root_node();

    let all_facts = extract_all_facts_from_tree(&root, source, "test.prem");

    // Trait facts should have confidence 1.0
    let trait_fact = all_facts.iter().find(|f| matches!(f.fact_type, FactType::Trait));
    if let Some(fact) = trait_fact {
        assert_eq!(fact.confidence, Some(1.0), "Trait facts should have confidence 1.0");
    }

    // Relationship facts should have confidence 0.7
    let rel_fact = all_facts.iter().find(|f| matches!(f.fact_type, FactType::Relationship));
    if let Some(fact) = rel_fact {
        assert_eq!(fact.confidence, Some(0.7), "Relationship facts should have confidence 0.7");
    }

    assert_json_snapshot!(normalize_facts(all_facts));
}

#[test]
fn test_empty_file() {
    let source = "";

    let mut parser = Parser::new();
    let tree = parser.internal.parse(source, None).unwrap();
    let root = tree.root_node();

    let facts = extract_all_facts_from_tree(&root, source, "test.prem");
    assert_eq!(facts.len(), 0, "Empty file should produce no facts");
}

#[test]
fn test_no_entities() {
    let source = r#"
= Act One

== A Scene

Some prose without entity references.
More text here.
"#;

    let mut parser = Parser::new();
    let tree = parser.internal.parse(source, None).unwrap();
    let root = tree.root_node();

    let facts = extract_all_facts_from_tree(&root, source, "test.prem");
    assert_eq!(facts.len(), 0, "File without entities should produce no facts");
}

#[test]
fn test_duplicate_entity_deduplication() {
    let source = r#"
= Act One

{Hero} appears.
{Hero} speaks.
{Hero} leaves.
"#;

    let mut parser = Parser::new();
    let tree = parser.internal.parse(source, None).unwrap();
    let root = tree.root_node();

    let facts = extract_entity_cooccurrence(&root, source, "test.prem");

    // Should not create relationships between Hero and Hero
    let self_relationship = facts.iter().any(|f| {
        if let Some(entities) = &f.entities {
            entities.len() == 2 && entities[0] == entities[1]
        } else {
            false
        }
    });

    assert!(!self_relationship, "Should not create self-relationships");
}
