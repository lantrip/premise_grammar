## premise-notes

Reusable notes primitives for Premise and non-Premise text.

What this crate provides:

- Schemas (serde + schemars) for notes records:
  - `Beat`, `Fact`, `TimelineEvent`, `ConsistencyEntry`, `NotesIndex`, `NotesMetadata`
- JSONL I/O helpers for durable storage (`beats.jsonl`, `facts.jsonl`, `timeline.jsonl`, `consistency.jsonl`)
- Normalization utilities for `{Entity}` references and alias mapping
- Pluggable sinks: stdout, JSONL directory, structured directory
- Plain-text extractors for quick ingestion (no Premise grammar required)
- Discovery and orchestration helpers for entities/aliases/unknowns

### Install (workspace dependency)

In a Cargo workspace, add:

```toml
[dependencies]
premise-notes = { path = "../premise-notes" }
```

### Schemas

Schemas live in `src/schema.rs` and are exported with `schemars`:

```rust
use premise_notes as notes;
let schema = schemars::schema_for!(notes::Beat);
println!("{}", serde_json::to_string_pretty(&schema).unwrap());

// Export all
for (name, root) in notes::export_all() {
    println!("{} => {}", name, serde_json::to_string_pretty(&root).unwrap());
}
```

Key types:

- `Beat { id, text, file, line?, section?, entities[], added, source, metadata?, provenance? }`
- `Fact { type, id, entity?, entities?, category?, fact, evidence[], confidence?, added, status?, timeline?, source, metadata?, provenance? }`
- `TimelineEvent { id, event, order, relative_to?, entities[], source[], added, provenance? }`
- `NotesIndex { schema_version, story_root, last_updated, stats, entity_index, file_index }`
- `NotesMetadata { schema_version, title?, created, modified, config }`
- `Provenance { source_file?, source_line?, normalized_with_aliases?, aliases_applied?, normalization_steps? }`

### Normalization

Utilities to normalize `{Entity}` tokens against canonical/alias maps, convert unknowns to `{?Name}`, and collect unresolved references:

```rust
use premise_notes::{normalize_beat_text, normalize_facts, normalize_all};
use std::collections::{HashMap, HashSet};

let canonical: HashSet<String> = ["Maya Chen".to_string()].into_iter().collect();
let reverse: HashMap<String, String> = [("Maya".to_string(), "Maya Chen".to_string())].into_iter().collect();
let (text, entities) = normalize_beat_text("{Maya} meets {Kai}", &canonical, &reverse);
assert_eq!(text, "{Maya Chen} meets {?Kai}");

let beats = vec![]; let facts = vec![];
let alias_map = std::collections::HashMap::from([(
    "Maya Chen".to_string(), vec!["Maya".to_string()]
)]);
let (_nb, _nf, unknowns) = normalize_all(beats, facts, &alias_map);
```

### Plain-text Extraction

Use simple helpers for non-Premise input (logs, transcripts, notes):

```rust
use premise_notes::extract_text::{
  extract_beats_from_text, extract_facts_from_text, TextExtractionOptions,
  extract_beats_from_markdown, extract_beats_from_transcript
};

let text = "{Maya} meets {Kai}\n{Maya} is brave";
let opts = TextExtractionOptions { file_label: Some("transcript.txt".into()), section_headers: false };
let beats = extract_beats_from_text(text, &opts);
let facts = extract_facts_from_text(text, "transcript.txt");

let md = "# Act 1\n## Scene A\nParagraph one with {Maya}.\n\nAnother paragraph.";
let md_opts = TextExtractionOptions { file_label: Some("notes.md".into()), section_headers: true };
let md_beats = extract_beats_from_markdown(md, &md_opts);

let srt = "1\n00:00:01,000 --> 00:00:03,000\n{Maya}: Hello\n\n2\n00:00:03,500 --> 00:00:05,000\n{Kai}: Hi";
let tr_beats = extract_beats_from_transcript(srt, &opts);
```

### Aliases

Read/write aliases stored under the notes directory and perform conflict-aware merges.
Keep it simple: a map from canonical names to a small set of nicknames. Avoid reusing the same alias for different canonicals.

```rust
use std::collections::HashMap;
use premise_notes::io::{read_alias_map, write_alias_map, merge_alias_maps, build_reverse_alias_map};

let root = ".";
let mut base = read_alias_map(root).unwrap();
let incoming = HashMap::from([
  ("Maya Chen".to_string(), vec!["Maya".to_string(), "Chen".to_string()])
]);
let report = merge_alias_maps(&mut base, &incoming);
write_alias_map(root, &base).unwrap();
let reverse = build_reverse_alias_map(&base);
```

Light examples:

```json
// aliases.json (canonical -> aliases)
{
  "Maya Chen": ["Maya", "Chen"],
  "Last Library": ["Library"]
}
```

```json
// alias-delta.json (additions only)
{
  "Maya Chen": ["M"],
  "Kai Ito": ["Kai"]
}
```

```bash
# Apply delta without writing
premise notes apply-alias-delta --delta alias-delta.json --path . --dry-run
# Merge aliases directly (dry-run)
premise notes merge-aliases --aliases alias-delta.json --path . --dry-run
```

### Orchestration

One-shot helpers to drive the loop end-to-end:

```rust
use std::collections::{HashMap, HashSet};
use premise_notes::{discover_entities_from_text_api, propose_alias_updates_api, normalize_all_api, summarize_uncertainties};

let text = "{?Maya} met Kai in the Last Library.";
let known: HashSet<String> = HashSet::new();
let candidates = discover_entities_from_text_api(text, &known);

let alias_map: HashMap<String, Vec<String>> = HashMap::new();
let delta = propose_alias_updates_api(&candidates, &alias_map);

let (_beats, _facts, unknowns) = normalize_all_api(vec![], vec![], &alias_map);
```

### Sinks & I/O

```rust
use premise_notes::{JsonlDirSink, NotesSink};
let mut sink = JsonlDirSink::new("./out").unwrap();
// sink.emit_beats(&beats)?;
```

### CLI Integration (via premise binary)

- Export beats/facts/timeline from Premise or plain/markdown files
- Normalize existing notes
- Summarize unknowns and merge aliases

```bash
# Summarize unknown/uncertain entities across notes
premise notes summarize-uncertain --path .

# Merge alias updates (dry-run)
premise notes merge-aliases --aliases aliases_update.json --path . --dry-run
```

### Packaging & JSON Schemas

- Schemas are generated into `schemas/` using the included generator:

```bash
# From the crate directory
SCHEMAS_OUT_DIR=./schemas cargo run --bin generate_schemas
```

- These JSON Schemas are intended to be published with the crate for downstream validation and tooling. Names follow `notes.<Type>.schema.json`.

### SemVer Policy for Schemas

- Patch releases (x.y.z): backward-compatible changes only (e.g., adding optional fields with `skip_serializing_if`, documentation updates).
- Minor releases (x.y): additive, backward-compatible schema extensions (new enum variants, new optional fields, new record types that don't break existing JSON).
- Major releases (x): breaking changes (renames, required field changes, semantic meaning changes). Coordinate changes across dependent tools and update `schema_version` in notes metadata and index.

Change process:

- Document schema changes in the changelog and bump crate version accordingly.
- Regenerate and commit schemas under `schemas/`.
- Update `NotesMetadata.schema_version` and handling logic if breaking.

### Compatibility

- This crate has no dependency on the Premise grammar or tree-sitter.
- `premise-core` depends on this crate and adds Premise-specific extractors.

### License

MIT OR Apache-2.0
