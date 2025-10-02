# Premise Notes System

The Premise Notes System provides a structured, reusable way to track story knowledge outside of your `.prem` files. This enables better story consistency, external tool integration, and richer AI context.

## Overview

**Location**: `.premise-notes/` directory at your story root
**Format**: JSONL (JSON Lines) for data, JSON for indexes
**Purpose**: Track beats, facts, timeline, and consistency state

## Quick Start

### 1. Initialize Notes

**Via CLI** (recommended):
```bash
cd your-story-root
premise notes init . --title "My Story"
```

**Via VSCode**:
- Run **Premise: Extract Facts to Notes…**
- The extension will prompt to initialize if needed

This creates:
```
your-story-root/
├── .premise-notes/
│   ├── beats.jsonl          # Story beats
│   ├── facts.jsonl          # Extracted facts
│   ├── timeline.jsonl       # Temporal events
│   ├── consistency.jsonl    # State tracking
│   ├── index.json           # Fast lookup index
│   └── metadata.json        # Configuration
```

### 2. Extract Structural Data

**Via CLI** (intelligent extraction with tree-sitter):
```bash
# Extract facts from story structure (traits + co-occurrence relationships)
premise notes extract-facts story/chapter1.prem

# Example output:
# Extracted 10 facts from story/chapter1.prem
#   - 3 entity trait facts (from @character definitions)
#   - 7 co-occurrence relationships (from scenes/dialogue)

# Extract timeline from acts/scenes/cels
premise notes extract-timeline story/chapter1.prem

# Export beats from /// markers
premise notes export-beats story/chapter1.prem

# One-pass extraction during analysis
premise analyze story/chapter1.prem --extract-notes
```

**What gets extracted automatically:**
- **Entity traits** (confidence: 1.0): Extracted from `@character Name: Description` definitions
- **Co-occurrence relationships** (confidence: 0.7): Discovered by analyzing which entities appear together in scenes/cels
- **Section context**: Every fact includes act/scene/cel metadata for navigation

**Via VSCode** (AI-enhanced extraction):
1. Open a `.prem` file
2. Run **Premise: Extract Facts to Notes…**
3. Choose scope (file, story root, uncommitted changes)
4. Facts are appended to `.premise-notes/facts.jsonl`

### 3. Query and Manage Notes

**Query by entity**:
```bash
# View all notes for an entity (JSON output)
premise notes query --entity Hero .

# Example output shows:
# [
#   {
#     "type": "trait",
#     "entity": "Hero",
#     "fact": "A brave warrior with a mysterious past",
#     "evidence": ["story/scene1.prem:5"],
#     "confidence": 1.0
#   },
#   {
#     "type": "relationship",
#     "entities": ["Hero", "Villain"],
#     "fact": "Hero and Villain appear together in scene 'The Beginning'",
#     "evidence": ["story/scene1.prem:25"],
#     "confidence": 0.7
#   }
# ]

# Use standard CLI tools for advanced queries
grep '"Hero"' .premise-notes/facts.jsonl | jq 'select(.type=="trait")'
jq 'select(.confidence >= 0.9)' .premise-notes/facts.jsonl
```

**Manage index**:
```bash
# Rebuild index after manual edits
premise notes rebuild-index .

# Example output:
# Index rebuilt successfully
#   Beats: 47
#   Facts: 123
#   Timeline events: 8
#   Entities tracked: 15

# Check notes status
premise notes status .
```

## File Formats

### JSONL Files (Append-Only)

JSONL (JSON Lines) files contain one JSON object per line. This format is:
- **Append-friendly**: Add new records without rewriting the file
- **Merge-friendly**: Git conflicts are line-based, easier to resolve
- **Stream-friendly**: Process large files incrementally
- **Tool-friendly**: Easy to grep, filter, or parse with any language

#### `beats.jsonl`

Each line is a beat record:

```jsonl
{"type":"beat","id":"b001","text":"{Maya Chen} discovers forbidden knowledge","file":"story/scene1.prem","line":14,"section":{"act":"Act One","scene":"First Signs"},"entities":["Maya Chen"],"added":"2025-10-01T10:30:00Z","source":"llm-generated","metadata":{"model":"openrouter","mode":"add-new"}}
{"type":"beat","id":"b002","text":"Ancient power awakens","file":"story/scene1.prem","line":18,"section":{"act":"Act One","scene":"First Signs"},"entities":[],"added":"2025-10-01T10:31:00Z","source":"manual"}
```

**Fields**:
- `type`: Always "beat"
- `id`: Unique identifier (e.g., "b001kz5p3a")
- `text`: Beat text (may contain `{Entity}` references)
- `file`: Relative path from story root
- `line`: Line number in source file (optional)
- `section`: Act/Scene/Cel context
- `entities`: Array of referenced entity names
- `added`: ISO 8601 timestamp
- `source`: "llm-generated" | "manual" | "imported"
- `metadata`: Optional generation details

#### `facts.jsonl`

Each line is a fact record:

```jsonl
{"type":"trait","id":"f001","entity":"Hero","category":"description","fact":"A brave warrior with a mysterious past","evidence":["story/scene1.prem:2"],"confidence":1.0,"added":"2025-10-01T16:38:38Z","source":"imported"}
{"type":"relationship","id":"f002","entities":["Hero","Villain"],"category":"co-occurrence","fact":"Hero and Villain appear together in scene 'The Beginning'","evidence":["story/scene1.prem:25"],"confidence":0.7,"added":"2025-10-01T16:38:38Z","status":"developing","source":"imported"}
{"type":"trait","id":"f003","entity":"Maya Chen","category":"personality","fact":"determined to uncover secrets","evidence":["story/scene1.prem:15"],"confidence":0.9,"added":"2025-10-01T10:32:00Z","source":"llm-generated"}
{"type":"knowledge","id":"f004","entity":"Maya Chen","fact":"knows spirit rune magic","evidence":["story/scene1.prem:22"],"confidence":1.0,"added":"2025-10-01T10:32:00Z","source":"llm-generated"}
```

**Fact Types**:
- `trait`: Character personality, appearance, abilities (auto-extracted from `@character` definitions)
- `relationship`: How entities relate to each other (auto-discovered via co-occurrence + AI inference)
- `knowledge`: What entities know or have learned
- `event`: Significant events (past, present, future)
- `state`: Current state of locations, objects, world

**Extraction Sources**:
- `imported`: Structural extraction from parse tree (high confidence)
- `llm-generated`: AI-extracted facts (variable confidence)
- `manual`: Manually added by user

**Fields**:
- `type`: Fact type (trait/relationship/knowledge/event/state)
- `id`: Unique identifier
- `entity`: Single entity (for traits, knowledge, state)
- `entities`: Multiple entities (for relationships, events)
- `category`: Sub-category (e.g., "personality", "appearance")
- `fact`: Concise fact statement
- `evidence`: Array of file:line references
- `confidence`: 0.0-1.0 (1.0 = explicit, 0.5-0.9 = implied)
- `status`: For relationships ("established", "developing", "uncertain", "broken")
- `timeline`: For events ("past", "present", "future")
- `added`: ISO 8601 timestamp
- `source`: Origin of fact

#### `timeline.jsonl`

Temporal ordering of events:

```jsonl
{"type":"timeline","id":"e001","event":"The Great Burning","order":"past","relative_to":"story_present","entities":["Burned District"],"source":["story/scene1.prem:19"],"added":"2025-10-01T10:33:00Z"}
{"type":"timeline","id":"e002","event":"Maya approaches library","order":"present","relative_to":"story_present","entities":["Maya Chen","Last Library"],"source":["story/scene1.prem:15"],"added":"2025-10-01T10:33:00Z"}
```

#### `consistency.jsonl`

State tracking for consistency validation:

```jsonl
{"type":"consistency","id":"c001","category":"possession","entity":"Maya Chen","state":"has spirit rune page","value":"true","established":["story/scene1.prem:22"],"last_confirmed":"2025-10-01T10:35:00Z","notes":"Maya grips the rune page"}
{"type":"consistency","id":"c002","category":"location","entities":["Last Library","Burned District"],"state":"library is in burned district","value":"true","established":["story/scene1.prem:13"],"last_confirmed":"2025-10-01T10:35:00Z"}
```

### JSON Files (Structured Data)

#### `index.json`

Fast lookup index (regenerated from JSONL files):

```json
{
  "schema_version": "1.0",
  "story_root": "/path/to/your/story",
  "last_updated": "2025-10-01T10:40:00Z",
  "stats": {
    "beats": 47,
    "facts": 123,
    "timeline_events": 8,
    "consistency_entries": 15,
    "entities_tracked": 8
  },
  "entity_index": {
    "Maya Chen": ["b001", "b002", "f001", "f003"],
    "Keeper Aldrich": ["b002", "f002"]
  },
  "file_index": {
    "story/scene1.prem": ["b001", "b002", "f001", "f002"],
    "story/scene2.prem": ["b003", "b004"]
  }
}
```

Rebuild with: (future CLI command)
```bash
premise notes rebuild-index
```

#### `metadata.json`

Notes system configuration:

```json
{
  "schema_version": "1.0",
  "title": "My Story",
  "created": "2025-10-01T09:00:00Z",
  "modified": "2025-10-01T10:40:00Z",
  "config": {
    "auto_export": false,
    "fact_categories": ["trait", "relationship", "knowledge", "event", "state"],
    "lsp_integration": false
  }
}
```

## VSCode Extension Settings

Configure in **Settings** → **Premise: Notes**:

### `premise.notes.enableTracking`
**Type**: boolean
**Default**: `false`
**Description**: Automatically export beats to `.premise-notes/` after AI generation

### `premise.notes.factCategories`
**Type**: array of strings
**Default**: `["trait", "relationship", "knowledge", "event"]`
**Description**: Which fact types to extract. Options:
- `trait`: Character traits, appearance, abilities
- `relationship`: Entity relationships
- `knowledge`: What entities know
- `event`: Significant events
- `state`: World/location/object state

### `premise.notes.storageLocation`
**Type**: string
**Default**: `".premise-notes"`
**Description**: Directory name for notes (relative to story root)

### `premise.notes.lspIntegration`
**Type**: boolean
**Default**: `false`
**Description**: Enable LSP features (experimental):
- Diagnostics for fact contradictions
- Hover hints showing related facts
- Code lenses for beat/fact navigation

## Commands

### Premise: Extract Facts to Notes…

Extract structured facts from story content using AI.

1. Open a `.prem` file
2. **Command Palette** → **Premise: Extract Facts to Notes…**
3. Choose scope:
   - **Current section**: Extract from section at cursor
   - **Current file**: Extract from active file
   - **Uncommitted: current file**: Only changed regions
   - **Story root**: All `.prem` files
   - **Uncommitted: story root**: All changed files
4. Facts are appended to `facts.jsonl` and index is rebuilt

**What gets extracted**:
- Character traits and descriptions
- Relationships between entities
- Character knowledge and abilities
- Significant events
- Location and world state

**Evidence tracking**: Every fact includes file:line references for verification.

### Premise: Export Beats to Notes

Export existing `///` beats from current document to notes.

1. Open a `.prem` file with beats
2. **Command Palette** → **Premise: Export Beats to Notes**
3. Beats are extracted and appended to `beats.jsonl`

Useful for:
- Migrating existing beats to notes system
- Creating a centralized beat database
- Preparing beats for external analysis tools

## Using Notes with External Tools

Because notes use standard JSONL/JSON formats, any tool can read and process them.

### Grep/Filter Beats

```bash
# Find all beats mentioning Maya Chen
grep '"Maya Chen"' .premise-notes/beats.jsonl

# Find high-confidence facts
jq 'select(.confidence >= 0.9)' .premise-notes/facts.jsonl

# Count beats per file
jq -r '.file' .premise-notes/beats.jsonl | sort | uniq -c
```

### Python Processing

```python
import json

# Read all facts
with open('.premise-notes/facts.jsonl', 'r') as f:
    facts = [json.loads(line) for line in f]

# Group by entity
from collections import defaultdict
by_entity = defaultdict(list)
for fact in facts:
    if 'entity' in fact:
        by_entity[fact['entity']].append(fact)

# Print Maya Chen's facts
for fact in by_entity['Maya Chen']:
    print(f"- {fact['fact']} (confidence: {fact['confidence']})")
```

### JavaScript/Node

```javascript
const fs = require('fs');
const readline = require('readline');

async function readBeats() {
  const beats = [];
  const stream = fs.createReadStream('.premise-notes/beats.jsonl');
  const rl = readline.createInterface({ input: stream });

  for await (const line of rl) {
    beats.push(JSON.parse(line));
  }
  return beats;
}

// Find beats in Act One
const beats = await readBeats();
const actOneBeats = beats.filter(b => b.section?.act === 'Act One');
```

## Workflow Examples

### Workflow 1: Consistency Checking

1. **Extract facts** from your story
2. Review `facts.jsonl` for contradictions
3. Search for entity across files: `grep '"EntityName"' .premise-notes/*.jsonl`
4. Verify timeline order in `timeline.jsonl`

### Workflow 2: Story Planning

1. **Export beats** from existing scenes
2. Review `beats.jsonl` to see story structure
3. Use index.json to find gaps (scenes with few beats)
4. **Generate beats** for underdeveloped sections

### Workflow 3: Character Analysis

```bash
# Extract all facts about a character
grep '"entity":"Maya Chen"' .premise-notes/facts.jsonl | jq .

# See all relationships involving Maya
grep '"Maya Chen"' .premise-notes/facts.jsonl | jq 'select(.type=="relationship")'

# Timeline of events involving Maya
grep '"Maya Chen"' .premise-notes/timeline.jsonl | jq -r '.event'
```

### Workflow 4: External LLM Context

Feed notes into external LLM prompts:

```bash
# Get recent facts as context
tail -20 .premise-notes/facts.jsonl | jq -r '.fact' > context.txt

# Then use context.txt in your LLM prompt
```

## Future Features

### CLI Reference

**Available commands** (all production-ready):

```bash
# Initialize notes directory
premise notes init <PATH> [--title <TITLE>]

# Extract facts (traits + co-occurrence relationships)
premise notes extract-facts <FILE>

# Export beats from /// markers
premise notes export-beats <FILE>

# Extract timeline events
premise notes extract-timeline <FILE>

# Query facts by entity
premise notes query --entity <ENTITY> <PATH>

# Rebuild index
premise notes rebuild-index <PATH>

# Check status
premise notes status <PATH>
```

**Path arguments**:
- `<PATH>`: Story root directory (where `.premise-notes/` is or will be created)
- `<FILE>`: Path to a `.prem` file to extract from

**Examples**:
```bash
# Complete workflow
cd my-story
premise notes init . --title "My Epic Tale"
premise notes extract-facts chapters/chapter1.prem
premise notes rebuild-index .
premise notes query --entity "Hero" .

# Use with JSON formatting (--format json)
premise --format json notes query --entity "Hero" . | jq '.[] | select(.confidence >= 0.8)'
```

### LSP Integration (Planned)

When `premise.notes.lspIntegration` is enabled:

- **Diagnostics**: Warning when story content contradicts tracked facts
- **Hover**: Show related facts when hovering over `{Entity}` references
- **Code Lenses**: "View beats for this section" above headers
- **Quick Fixes**: "Add to consistency tracking" for important state changes

### Advanced CLI Features (Planned)

```bash
# Type filtering
premise notes query --entity "Maya Chen" --type trait

# Consistency validation
premise notes validate --file story/scene2.prem

# Format export
premise notes export --format csv --output story-beats.csv

# Branch merging
premise notes merge --from feature-branch
```

### Consistency Validation (Planned)

Automatic checks for:
- Entity knowledge contradictions
- Timeline inconsistencies
- Possession tracking (who has what)
- Location continuity

## Tips

1. **Commit notes with your story**: `.premise-notes/` should be version-controlled alongside your `.prem` files
2. **Review extracted facts**: AI isn't perfect—check `facts.jsonl` for accuracy
3. **Use evidence links**: Click `file:line` references to verify facts in context
4. **Rebuild index after manual edits**: If you hand-edit JSONL files, rebuild `index.json`
5. **Start small**: Extract facts from one file first to understand the format

## Schema Version

Current schema version: **1.0**

The schema version is stored in `metadata.json` and `index.json`. Future versions will maintain backward compatibility or provide migration tools.

## Troubleshooting

**Q: Notes initialization failed**
A: Ensure you have write permissions in the story root directory.

**Q: Facts extracted but seem wrong**
A: Review evidence links (`file:line`). Adjust `premise.notes.factCategories` to focus extraction. Lower-confidence facts (< 0.7) may be speculative.

**Q: Index.json out of date**
A: Run any notes command (extract/export) to automatically rebuild the index.

**Q: Want to start over**
A: Delete `.premise-notes/` directory. It will be recreated on next use.

**Q: Can I edit JSONL files manually?**
A: Yes! Just ensure each line is valid JSON. Rebuild index afterward by running any notes command.

## See Also

- [AI_ROADMAP.md](./AI_ROADMAP.md) - Overall AI features roadmap
- [premise-core/src/notes/](./premise-core/src/notes/) - Rust implementation
  - [schema.rs](./premise-core/src/notes/schema.rs) - Canonical schema definitions
  - [extract_enhanced.rs](./premise-core/src/notes/extract_enhanced.rs) - Intelligent extraction logic
  - [io.rs](./premise-core/src/notes/io.rs) - JSONL I/O operations
- [premise-core/tests/notes_snapshots.rs](./premise-core/tests/notes_snapshots.rs) - Test examples and validation
