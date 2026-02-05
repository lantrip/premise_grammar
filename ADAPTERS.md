# Premise Adapter Framework

## Overview

The Premise Adapter Framework enables **domain-agnostic content transformation** - the same `.prem` file can be interpreted as a story, sales call, architecture document, or any hierarchical content structure.

**Core Principle**: Premise provides a universal language for entities, hierarchy, and relationships. Adapters transform this into domain-specific outputs.

## Architecture

### Universal Content Pattern

```
Domain          Entity Type          Section Mapping              Output
──────────────────────────────────────────────────────────────────────────
Narrative       @character Hero      act/scene/cel                Screenplay PDF
Sales           @participant John    call/segment/moment          Call Report
Architecture    @component Auth      module/feature/function      Diagram
Legal           @party Alice         case/motion/argument         Brief
Meeting         @attendee Sarah      meeting/topic/decision       Notes
```

All domains share:

- **Entities**: Definitions with references `{Entity}`
- **Hierarchy**: Act/Scene/Cel (or mapped equivalents)
- **Content Types**: Beats (`#`), treatment (`##`), narrative (`###`)
- **Notes System**: Facts, relationships, timeline, consistency

## Adapter Manifest

Every adapter provides an `adapter.json` manifest:

```json
{
  "id": "premise-screenplay-pdf",
  "name": "Screenplay PDF Generator",
  "version": "1.0.0",
  "description": "Generates professional screenplay PDFs",
  "domains": ["narrative", "screenplay"],
  "capabilities": {
    "generates_artifacts": true,
    "uses_notes_context": true,
    "contributes_facts": false,
    "output_formats": ["pdf", "fdx"],
    "entity_types": ["character", "location"]
  },
  "entry_point": "./screenplay-generator.js"
}
```

### Manifest Fields

- **`id`**: Unique adapter identifier (kebab-case)
- **`name`**: Human-readable name
- **`version`**: Semantic version
- **`description`**: Brief description
- **`domains`**: Target domains (use `"*"` for universal)
- **`capabilities`**: What the adapter can do
- **`entry_point`**: Executable path (relative to adapter directory)
- **`author`** (optional): Author name
- **`repository`** (optional): Source repository URL

### Capabilities

- **`generates_artifacts`**: Creates output files (PDF, HTML, etc.)
- **`uses_notes_context`**: Queries notes for context
- **`contributes_facts`**: Writes facts back to notes
- **`output_formats`**: List of supported formats
- **`entity_types`**: Entity types this adapter understands

## CLI Usage

### Discover Adapters

```bash
# List all available adapters
premise adapters list

# Filter by domain
premise adapters list --domain narrative
premise adapters list --domain sales

# Show detailed information
premise adapters show premise-screenplay-pdf
```

**Output Example**:

```
Available adapters:

  Screenplay PDF Generator (premise-screenplay-pdf)
    Version: 1.0.0
    Domains: narrative, screenplay
    Description: Generates professional screenplay PDFs in industry-standard format
    Author: Premise Contributors
```

### Adapter Search Paths

Adapters are discovered from:

1. `./adapters` - Current directory
2. `~/.premise/adapters` - User home directory
3. `/usr/local/share/premise/adapters` - System-wide (Unix)
4. `$PREMISE_ADAPTERS_PATH` - Environment variable (colon-separated)

## Domain Mapping

Adapters use **Domain Mappers** to translate Premise concepts into domain-specific terminology.

### Built-in Mappers

#### Narrative Domain (1:1 mapping)

```
@character Hero     → character
@location Tavern    → location
act                 → act
scene               → scene
cel                 → cel
```

#### Sales Domain

```
@character John     → participant
@location Acme      → company
act                 → call
scene               → segment
cel                 → moment
```

#### Architecture Domain

```
@character Auth     → component
@location Backend   → service
act                 → module
scene               → feature
cel                 → function
```

### Custom Domain Mapper

Create your own mapper by implementing `DomainMapper`:

```rust
use premise_core::adapters::DomainMapper;

pub struct CustomMapper;

impl DomainMapper for CustomMapper {
    fn map_entity_type(&self, premise_type: &str) -> String {
        match premise_type {
            "character" => "custom_entity".to_string(),
            _ => premise_type.to_string(),
        }
    }

    fn map_section_type(&self, premise_type: &str, _level: u8) -> String {
        match premise_type {
            "act" => "custom_section".to_string(),
            _ => premise_type.to_string(),
        }
    }

    fn domain_id(&self) -> &str {
        "custom"
    }
}
```

## Notes Context API

Adapters can query the notes system for context-aware generation.

### Basic Queries

```rust
use premise_core::adapters::NotesContext;

let context = NotesContext::new("/path/to/story");

// Get all facts about an entity
let hero_facts = context.get_entity_facts("Hero")?;

// Get facts by type
let traits = context.get_facts_by_type(FactType::Trait)?;

// Get high-confidence facts only
let reliable = context.get_facts_with_confidence(0.9)?;

// Get relationship between entities
let relationship = context.get_relationship("Hero", "Villain")?;

// Get beats for an entity
let hero_beats = context.get_entity_beats("Hero")?;

// Get beats for a section
let scene_beats = context.get_section_beats("The Beginning")?;

// Get all entity names
let entities = context.get_all_entities()?;
```

### Advanced Queries

Use `FactQuery` builder for complex queries:

```rust
use premise_core::adapters::FactQuery;
use premise_core::notes::FactType;

let facts = FactQuery::new()
    .entity("Hero")
    .fact_type(FactType::Trait)
    .min_confidence(0.8)
    .category("personality")
    .execute(&context)?;
```

### Query Results

All queries return `Vec<Fact>` or `Vec<Beat>` with:

- **Evidence**: File:line references for verification
- **Confidence**: 0.0-1.0 score (1.0 = explicit, 0.7 = inferred)
- **Section Context**: Act/scene/cel where fact was found
- **Source**: `imported` (structural) or `llm-generated` (AI-extracted)

## Creating an Adapter

### 1. Create Adapter Directory

```bash
mkdir -p adapters/my-adapter
cd adapters/my-adapter
```

### 2. Create Manifest

**`adapter.json`**:

```json
{
  "id": "my-adapter",
  "name": "My Custom Adapter",
  "version": "1.0.0",
  "description": "My custom adapter description",
  "domains": ["my-domain"],
  "capabilities": {
    "generates_artifacts": true,
    "uses_notes_context": true,
    "contributes_facts": false,
    "output_formats": ["html"],
    "entity_types": ["custom-entity"]
  },
  "entry_point": "./generate.js"
}
```

### 3. Implement Entry Point

**`generate.js`** (Node.js example):

```javascript
#!/usr/bin/env node

// Read Premise IR from stdin
const fs = require("fs");
const input = fs.readFileSync(0, "utf-8");
const ir = JSON.parse(input);

// Access story structure
const acts = ir.story.acts;
const entities = ir.entities;

// Query notes for context (if enabled)
const notesPath = process.env.PREMISE_NOTES_PATH;
// ... query notes using notes CLI or direct JSONL read

// Generate output
const output = generateHTML(acts, entities);
console.log(output);
```

### 4. Make Executable

```bash
chmod +x generate.js
```

### 5. Test

```bash
# Verify adapter is discovered
premise adapters show my-adapter

# Run adapter (future feature)
# premise run my-adapter input.prem -o output.html
```

## Planned Features

See [docs/ADAPTERS_ROADMAP.md](./docs/ADAPTERS_ROADMAP.md) for planned features including:
- Adapter execution engine
- Provenance tracking
- Notes contribution

## Example Use Cases

### Screenplay Generation (Narrative Domain)

**Input** (`story.prem`):

```premise
@character MAYA CHEN: A determined investigator

= Act One

== INT. POLICE STATION - DAY

{MAYA CHEN} examines the evidence board.

MAYA CHEN
  (to herself)
  The pattern is right here. I just need to see it.
```

**Adapter**: `premise-screenplay-pdf`
**Output**: Professional PDF in industry-standard screenplay format

### Sales Call Analysis (Sales Domain)

**Input** (`call-transcript.prem`):

```premise
@participant Sarah (Sales Rep): Account Executive at SalesCorp
@participant John (Prospect): CTO at TechCorp
@company TechCorp: Enterprise software company

= Discovery Call 2024-01-15

== Introduction Segment

{Sarah} introduces the platform capabilities.

{John} expresses concerns about migration complexity.

== Objection Handling

{Sarah} addresses migration with case study data.
```

**Adapter**: `premise-sales-report`
**Output**: Call summary with:

- Participant insights
- Action items
- Objection tracking
- Sentiment analysis
- Next steps

### Architecture Documentation (Software Domain)

**Input** (`system-design.prem`):

```premise
@component AuthService: JWT-based authentication service
@component UserDB: PostgreSQL user database
@component APIGateway: Kong API gateway

= Authentication Module

== Login Flow

{APIGateway} routes request to {AuthService}.

{AuthService} validates credentials against {UserDB}.

=== Token Generation

{AuthService} generates JWT token with user claims.
```

**Adapter**: `premise-architecture-diagram`
**Output**:

- C4 diagrams (SVG)
- PlantUML source
- Mermaid diagrams
- Interactive HTML documentation

## Advanced Topics

### Multi-Domain Adapters

Adapters can support multiple domains:

```json
{
  "domains": ["narrative", "screenplay", "novel"],
  "entity_types": ["character", "location", "prop"]
}
```

### Universal Adapters

Use `"*"` to support all domains:

```json
{
  "domains": ["*"],
  "description": "Works with any Premise file regardless of domain"
}
```

## Best Practices

### 1. Design for Reusability

- Use domain mappings for flexibility
- Support multiple output formats
- Make configuration external (not hardcoded)

### 2. Leverage Notes Context

- Query facts before generating
- Avoid contradicting existing knowledge
- Use confidence scores to prioritize

### 3. Provide Good Metadata

- Write clear descriptions
- List all supported entity types
- Document output formats

### 4. Handle Errors Gracefully

- Validate input IR
- Provide helpful error messages
- Fall back to safe defaults

### 5. Version Carefully

- Use semantic versioning
- Document breaking changes
- Test with various Premise versions

## Troubleshooting

### Adapter Not Found

**Problem**: `premise adapters list` doesn't show your adapter

**Solutions**:

1. Check manifest file is named `adapter.json` or `premise-adapter.json`
2. Verify adapter is in a search path
3. Ensure JSON is valid: `cat adapter.json | jq`
4. Set `PREMISE_ADAPTERS_PATH` environment variable

### Invalid Manifest

**Problem**: Adapter discovered but shows errors

**Solutions**:

1. Validate required fields: `id`, `name`, `version`, `domains`, `capabilities`, `entry_point`
2. Check `capabilities` has all required boolean fields
3. Ensure `domains` is an array of strings

### Notes Context Empty

**Problem**: Adapter queries return no facts

**Solutions**:

1. Verify notes exist: `premise notes status .`
2. Run extraction: `premise notes extract-facts file.prem`
3. Rebuild index: `premise notes rebuild-index .`
4. Check story root path is correct

## API Reference

### Rust API

```rust
// Registry
use premise_core::adapters::AdapterRegistry;
let mut registry = AdapterRegistry::new();
registry.add_search_path("./adapters");
registry.discover()?;

// Domain Mapping
use premise_core::adapters::{DomainMapper, SalesDomainMapper};
let mapper = SalesDomainMapper;
let participant = mapper.map_entity_type("character"); // "participant"

// Notes Context
use premise_core::adapters::{NotesContext, FactQuery};
let context = NotesContext::new("/story/root");
let facts = context.get_entity_facts("Hero")?;
```

### CLI API

```bash
# List adapters
premise adapters list [--domain DOMAIN]

# Show adapter details
premise adapters show <adapter-id>

# Get JSON output
premise --format json adapters list
```

## See Also

- [docs/AI_ROADMAP.md](./docs/AI_ROADMAP.md) - Notes system reference
- [docs/ADAPTERS_ROADMAP.md](./docs/ADAPTERS_ROADMAP.md) - Planned features
- [premise-core/src/adapters/](./premise-core/src/adapters/) - Implementation source
- [adapters/](./adapters/) - Example adapter manifests
