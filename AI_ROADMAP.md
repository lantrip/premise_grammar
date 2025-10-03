# Premise AI Features

> NOTE: This document is the sole source of truth for our AI roadmap. All prior planning docs have been consolidated here.

## Current Features

### Beat Generation

- **Command**: `Premise: Generate Beats…`
- **Provider**: OpenRouter (configurable model)
- **Scopes**: Current file, story root, uncommitted changes
- **Modes**: Add new, update/fix, recreate all
- **Anchoring**: Section-based (Cel/Scene/Act)
- **Settings**: `premise.ai.*` (model, apiKey, endpoint, beatInsertPosition, beatQualityLevel)

### Entity Description Updates

- **Command**: `Premise: Update Entity Descriptions…`
- **Scopes**: Same as beat generation
- **Updates**: Coalesced per entity, optional changed-ranges-only
- **Settings**: `premise.ai.entityUpdateScope` (descriptions-only, relationships, comprehensive)

### Story Notes System

- **Architecture**: CLI-first (Rust core), VSCode calls `premise notes` commands
- **Commands**:
  - VSCode: `premise.extractFacts` (AI-enhanced), `premise.exportBeats` (via CLI)
  - CLI: `init`, `extract-facts`, `export-beats`, `extract-timeline`, `query`, `rebuild-index`, `status`
- **Format**: JSONL (JSON Lines) for beats, facts, timeline, consistency
- **Location**: `.premise-notes/` at story root
- **Extraction Intelligence**:
  - **Entity traits**: Auto-extracted from `@character Name: Description` definitions (confidence: 1.0)
  - **Co-occurrence relationships**: Discovers entity interactions by analyzing scenes/cels (confidence: 0.7)
  - **Section context**: Tracks act/scene/cel location for all extracted facts
- **Record Types**:
  - `Beat` - Story milestones with entity refs and section context
  - `Fact` - Traits, relationships, knowledge, events, state (with evidence and confidence)
  - `TimelineEvent` - Temporal ordering with entity involvement
  - `ConsistencyEntry` - State tracking
- **Settings**: `premise.notes.*` (enableTracking, factCategories, lspIntegration)
- This roadmap also serves as the notes system reference.

## LSP Helpers

Server-side commands for grounding AI operations:

- `premise.getStoryRoot(uri)` - Resolve story root path
- `premise.listEntityNames(uri)` - Get canonical entity names
- `premise.collectStructure(uris)` - Get Acts/Scenes/Cels with ranges and entity mentions

## Configuration

### AI Settings (`premise.ai.*`)

- `provider` - AI provider (default: "openrouter")
- `model` - Model identifier (e.g., "openai/gpt-4o-mini")
- `apiKey` - API key (or use OPENROUTER_API_KEY env var)
- `endpoint` - API endpoint
- `chunkingMode` - "section" or "file"
- `beatInsertPosition` - "append" or "prepend"
- `beatQualityLevel` - "concise", "detailed", or "comprehensive"
- `beatGenerationMode` - "add-new", "update-fix", or "recreate-all"
- `entityUpdateScope` - "descriptions-only", "relationships", or "comprehensive"
- `rateLimitPerMinute` - Rate limiting for batch operations

### Notes Settings (`premise.notes.*`)

- `enableTracking` - Auto-export beats after generation (default: false)
- `factCategories` - Which fact types to extract (default: ["trait", "relationship", "knowledge", "event"])
- `storageLocation` - Notes directory name (default: ".premise-notes")
- `lspIntegration` - Enable LSP features (experimental, default: false)

## Implementation Status

✅ **Complete**:

- Beat generation with section anchoring
- Entity description updates with evidence
- **Notes System (CLI-First Architecture)**:
  - ✅ Rust core module: `premise-core/src/notes/` (schema, I/O, extraction)
  - ✅ CLI commands: `init`, `extract-facts`, `export-beats`, `extract-timeline`, `query`, `rebuild-index`, `status`
  - ✅ VSCode integration via CLI execution (TypeScript → Rust CLI)
  - ✅ **Intelligent Extraction**:
    - Entity trait extraction from `@character Name: Description` (1.0 confidence)
    - Co-occurrence relationship discovery from dialogue/prose (0.7 confidence)
    - Section context preservation (act/scene/cel metadata)
  - ✅ **Testing**: 9 snapshot tests with deterministic output
  - ✅ **Error Handling**: Comprehensive error messages with actionable guidance
  - ✅ **Production Ready**: Validated with real story files
- **LSP Helpers**:
  - ✅ `premise.getStoryRoot` - Resolve story root path
  - ✅ `premise.listEntityNames` - Get canonical entity names
  - ✅ `premise.collectStructure` - Get Acts/Scenes/Cels with:
    - **Hierarchical stable IDs** (e.g., `act-one/the-beginning/training-montage`)
    - Parent context (scenes include act, cels include scene + act)
    - Entity mentions per section
    - Range information for precise anchoring
- Uncommitted scope support (git diff integration)
- Sequential processing with progress
- Rate limiting
- Deduplication and validation
- Preview mode for beat changes

🚧 **In Progress**:

- Performance optimization for large story files
- LSP integration for notes (diagnostics, hovers, code lenses)

✅ **Phase C - Adapter Framework (Foundation Complete)**:

- ✅ **Domain-Agnostic Architecture**:l
  - Adapter manifest schema with domain metadata
  - Registry system with auto-discovery
  - CLI commands: `premise adapters list/show`
  - Support for multiple search paths
- ✅ **Domain Abstraction Layer**:
  - `DomainMapper` trait for cross-domain transformation
  - Built-in mappers: Narrative, Sales, Architecture
  - Domain-agnostic entity and section representations
- ✅ **Notes Context API**:
  - Read-only adapter access to notes
  - Query by entity, type, confidence, category
  - Relationship discovery
  - Beat and section queries
- ✅ **Example Adapters** (3 domains):
  - `premise-screenplay-pdf` - Narrative domain (PDF, FDX output)
  - `premise-sales-report` - Sales domain (call analysis)
  - `premise-architecture-diagram` - Software domain (C4, UML, Mermaid)

📋 **Planned (Phase C - Next Steps)**:

- Adapter execution engine
- Provenance tracking for adapter-generated content
- Adapter contribution to notes (facts, beats)
- Advanced relationship inference (sentiment, intensity)
- Consistency validation using notes
- Provider abstraction for local models
- Packaging and binary distribution

## Holistic Entity / Beat / Fact Extraction

This section is the canonical plan for entity discovery, beat generation, and fact extraction across CLI and editor integrations.

### Overview

- **Goal**: Bootstrap and evolve stories from raw narrative text by discovering entities, managing aliases, and generating beats and facts with strong grounding.
- **Approach**: Two-pass pipeline with optional hybrid mode, modular output sinks, and a consistent CLI-first surface that the VSCode/Zed extensions call.

### Architecture at a glance

1. **Entity Discovery (Pass 1)**

   - Rust: `premise-core/src/notes/entity_discovery.rs` (heuristics for names, aliases, evidence, type inference)
   - CLI: `premise notes discover-entities <file>` → emits JSON (or pretty) with `known_entities` and `discovered` candidates
   - Output fields: `canonical_name`, `type` (character/location/object/concept), `aliases`, `description`, `evidence`, `confidence`

2. **Beat/Fact Extraction (Pass 2)**

   - Beats: keep mandatory `{Entity}` syntax; allow `{?Entity}` for uncertain entities when canon is incomplete
   - Facts: extract traits/relationships/knowledge/events/state with evidence and confidence; tolerate uncertain refs when discovery is pending
   - Editor flow: if uncertain entities are present, prompt to run discovery → review → re-run generation with updated canon

3. **Alias Management**
   - Store and use alias mappings to normalize output to canonical names
   - Initial approach: inline `+aliases:` metadata under entity definitions; future: centralized story-wide map

### Storage and Output (Modular Sinks)

All extraction commands support pluggable sinks so workflows are not tied to a fixed folder layout.

- `notes` (default): Use managed `.premise-notes/` JSONL files and rebuild index
- `stdout`: Print to console (pretty or JSON via `--format`)
- `jsonl-dir`: Append `beats.jsonl`, `facts.jsonl`, `timeline.jsonl` to any directory
- `dir`: Write one JSON file per record under `beats/`, `facts/`, `timeline/`

CLI usage examples:

```bash
# Export beats to stdout as JSON (no filesystem writes)
premise notes export-beats story/scene1.prem --sink stdout --format json

# Extract facts to a custom JSONL directory
premise notes extract-facts story/scene1.prem --sink jsonl-dir --out-dir ./notes_out

# Extract timeline into individual JSON files
premise notes extract-timeline story/scene1.prem --sink dir --out-dir ./timeline_out
```

### Editor Integration (VSCode/Zed)

- Add commands: discover entities, review candidates, generate entity definitions
- Beat prompt: allow `{?Entity}` for unknowns, normalize aliases post-gen
- Validation: flag uncertain tokens instead of rejecting; guide user into discovery → review loop

### Current state

- ✅ Hybrid entity discovery implemented in Rust with CLI (`discover-entities`, `list-entities`)
- ✅ Inline alias metadata (`+aliases:`) extraction supported
- ✅ Notes system with JSONL index; CLI for `export-beats`, `extract-facts`, `extract-timeline`
- ✅ New modular sinks (`--sink` and `--out-dir`) implemented in CLI for free-form output
- ✅ Rust-side alias normalization and uncertainty surfacing in CLI (`notes export-beats`, `notes extract-facts`)
  - ✅ Added `notes normalize` to re-normalize existing notes across a story root
  - ✅ `extract-timeline` surfaces uncertainty summary when timeline events contain `{?Entity}` in text
- 🚧 VSCode UI for discovery review and auto-inserting `@entity` lines
- 🚧 Alias management UI and story-wide alias map

### Testing and Quality

- Unit tests for discovery heuristics and alias parsing (Rust)
- Integration tests for bootstrap flow: discover → review → insert entities → generate beats
- Success metrics: higher beat acceptance rate, strong precision/recall for discovery, fast iteration (<3s typical files)

### AI Prompt Specs and Validation Policies

#### Beats Generation

- System prompt (core rules):

```text
You are a story analyst creating beats for a Premise story.

ENTITY RULES:
1. Use {Entity} syntax for ALL character/location references.
2. Use canonical entity names from the provided list; do not use aliases.
3. If you introduce a new, uncertain entity, use {?Entity} with a meaningful placeholder name.
4. Keep each beat concise and actionable.

FORMAT:
- Output JSON array of strings, each string is one beat. No markdown.
```

- Inputs:

  - `canonicalEntities`: array of canonical names
  - `aliasMap` (optional): map of canonical → aliases (for normalization hints)
  - `sectionContext`: act/scene/cel titles and brief synopsis
  - `style`: concise|detailed|comprehensive

- Validator (client-side policy):

  - Extract tokens matching `/\{(\??[^}]+)\}/`.
  - Partition: `uncertain = startsWith('?')`, `known = rest`.
  - If `known.every(name ∈ canonicalEntities)` and `uncertain.length == 0` → status: valid.
  - If `uncertain.length > 0` → status: needs-review, capture `uncertain` list and beats.
  - Else → status: invalid (unknown or alias usage); surface suggestions via alias normalization.

- Implementation notes (done):

  - CLI normalizes aliases → canonical and converts unknown `{Entity}` → `{?Entity}` before saving.
  - CLI prints a summary of beat(s) containing uncertain entities to prompt discovery.

- Alias normalization policy:
  - Given `aliasMap`, map any `{Alias}` to `{Canonical}` if unique.
  - Do not normalize `{?Entity}`; keep for review.
  - After normalization, re-run validator; if now valid, accept.

#### Facts Extraction (AI-Enhanced mode)

- System prompt (core rules):

```text
Extract concise facts about entities from the provided text.

RULES:
1. Use canonical entity names when available.
2. If an entity is not in the canonical list but clearly present, use {?Entity}.
3. Provide evidence as file:line references when possible.
4. Assign confidence 0.0–1.0 (explicit=1.0, strong implication≈0.8, weak implication≈0.6).

OUTPUT FORMAT:
JSON array of objects with fields: type, entity|entities, fact, evidence[], confidence, source="llm-generated".
```

- Validation:

  - Normalize aliases to canonical using `aliasMap`.
  - Unknowns become `{?Entity}` in `fact` text but entity fields should use canonical when resolvable, otherwise omit `entity` and include unresolved mention in `fact` with `{?Entity}`.
  - Flag any facts with unresolved `{?Entity}` for review.

- Implementation notes (done):
  - CLI normalizes aliases in `entity`/`entities` fields, dedupes, and surfaces unknown canonical misses for review.

#### Entity Discovery

- System prompt (core rules):

```text
Identify potential entities (character, location, object, concept), aliases, brief descriptions, and evidence lines.

RULES:
1. Propose canonical names; list aliases (nicknames, titles).
2. Classify type using context heuristics.
3. Provide evidence as file:line references.
4. Confidence: 1.0 explicit, 0.8 strong contextual, 0.5 ambiguous.

OUTPUT FORMAT:
JSON object: { known_entities: Record<name, string[]>, discovered: EntityCandidate[] }
```

- Post-processing:
  - Merge with existing canonical set; prompt user to accept/edit/merge/reject.
  - Update `+aliases:` inline metadata or centralized map.

### Normalization Order of Operations

1. Run generation (beats or facts) with `{?Entity}` allowed.
2. Normalize aliases → canonical using `aliasMap`.
3. Re-validate against canonical list.
4. If unresolved `{?Entity}` remain, surface for review or trigger discovery pass.
5. Only after resolution, persist to notes (beats/facts) or chosen sink.

### Immediate next steps

- Add unit tests for `normalize_beat_text`, `normalize_beats`, `normalize_facts`, and uncertainty collectors.
- Expose sink selection and discovery prompts in the editor UI (later), reusing the CLI behavior.

### Notes System Essentials

- Location: `.premise-notes/` in story root (default; configurable)
- Formats: JSONL for data (`beats.jsonl`, `facts.jsonl`, `timeline.jsonl`, `consistency.jsonl`), JSON for `index.json` and `metadata.json`
- CLI quick-start:

```bash
# Initialize notes
premise notes init . --title "My Story"

# Extract structural data
premise notes extract-facts story/scene1.prem
premise notes export-beats story/scene1.prem
premise notes extract-timeline story/scene1.prem

# Query by entity
premise notes query --entity "Maya Chen" .

# Rebuild index
premise notes rebuild-index .
```

Notes schema types are defined in `premise-notes/src/schema.rs` (shared crate).

### Using Notes Outside Premise Grammar (Plain/Markdown)

- All `premise notes` commands support non-Premise input:
  - `--input prem|plain|markdown` (default: `prem`)
  - `--stdin` to read from standard input
  - `--aliases path.json` to seed canonical→aliases mapping for normalization

Examples:

```bash
# Export beats from a plain text transcript
premise notes export-beats transcript.txt --input plain --sink jsonl-dir --out-dir ./out

# Extract facts from Markdown piped via stdin with alias map
cat notes.md | premise notes extract-facts dummy --input markdown --stdin --aliases alias_map.json

# Extract timeline from Premise or plain text
premise notes extract-timeline story/scene1.prem --input prem
premise notes extract-timeline transcript.txt --input plain --sink stdout --format json
```

Alias map file format (JSON):

```json
{
  "Maya Chen": ["Maya", "Chen"],
  "Kai Tanaka": ["Kai"]
}
```

### Notes File Formats (summary)

- `beats.jsonl`: one beat per line with fields: `id`, `text`, `file`, optional `line`, optional `section`, `entities`, `added`, `source`, optional `metadata`.
- `facts.jsonl`: facts with `type`, `id`, `entity` or `entities`, `category`, `fact`, `evidence[]`, `confidence`, optional `status`/`timeline`, `added`, `source`.
- `timeline.jsonl`: `id`, `event`, `order`/`relative_to`, `entities[]`, `source[]`, `added`.
- `consistency.jsonl`: entries for state tracking (e.g., possession, location) for planned validation.

### Notes Refinements Roadmap

High priority:

- Enhanced entity detection from prose (beyond `@character` definitions)
- Relationship type classification (mentorship, antagonistic, romantic, collaborative) with sentiment/strength
- State tracking and basic consistency validation (possession/location)
- Performance and incremental extraction for large projects

Medium priority:

- Knowledge extraction/inference from actions and dialogue
- Timeline sequencing and causal links (before/after/during)
- Advanced query commands (summary, relationships, coverage, quality)

Low priority:

- Hybrid structural + AI extraction with calibrated confidence
- LSP integration (hovers, diagnostics, code lenses)
- Provenance/versioning for facts and rollback tools

## Future Enhancements

- Local model support (Ollama, etc.)
- Entity alias mapping
- Project-wide consistency checks
- Inline quick-fixes for AI suggestions
- Era/location metadata integration
