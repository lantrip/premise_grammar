# Premise Studio Extraction Plan

**Goal**: Extract AI features from `premise_grammar` into a new Hedgerow-based application called `premise-studio`.

## Architecture Overview

### premise_grammar (Language Foundation)
- Tree-sitter grammar definition
- Editor extensions (VSCode, Zed)
- LSP server for diagnostics and navigation
- `premise-core` - Parser library
- `premise-notes` - Schema-only library (no AI)
- CLI for structural operations only

### premise-studio (New Hedgerow App)
- All AI features via Hedgerow lenses
- Beat generation, entity discovery, fact extraction
- Custom Premise adapters for Hedgerow
- Story-specific UI
- Consumes `premise-core` and `premise-notes` as libraries

## Repository Structure

```
premise-studio/
├── adapters/
│   ├── premise-parser/
│   │   ├── Cargo.toml
│   │   ├── adapter.json
│   │   └── src/
│   │       ├── lib.rs              # Implements EngineProvider
│   │       ├── ast_to_json.rs      # AST → JSON conversion
│   │       └── entity_context.rs   # Extract entity context
│   ├── premise-notes/
│   │   ├── Cargo.toml
│   │   ├── adapter.json
│   │   └── src/
│   │       ├── lib.rs
│   │       ├── reader.rs           # Read .premise-notes/ JSONL
│   │       └── writer.rs           # Write .premise-notes/ JSONL
│   └── premise-validator/
│       ├── Cargo.toml
│       ├── adapter.json
│       └── src/
│           ├── lib.rs
│           └── beat_validator.rs   # Validate beat syntax
├── lenses/
│   ├── premise-parser.yaml         # Parse .prem file
│   ├── beat-generation.yaml        # Generate beats via LLM
│   ├── beat-validation.yaml        # Validate beat syntax
│   ├── entity-discovery.yaml       # Discover entities from text
│   ├── entity-enrichment.yaml      # Update entity descriptions
│   ├── fact-extraction.yaml        # Extract facts via LLM
│   └── consistency-check.yaml      # Check story consistency
├── stacks/
│   ├── bootstrap-story.yaml        # Full bootstrap: discover → entities → beats
│   ├── generate-beats.yaml         # Beat generation workflow
│   ├── enrich-entities.yaml        # Entity description updates
│   └── export-screenplay.yaml      # PDF generation
├── frontend/
│   ├── src/
│   │   ├── components/
│   │   │   ├── StoryExplorer.tsx   # File tree + structure
│   │   │   ├── BeatEditor.tsx      # Beat editing UI
│   │   │   ├── EntityGraph.tsx     # Entity relationships
│   │   │   ├── TimelineView.tsx    # Timeline visualization
│   │   │   └── LensExecutor.tsx    # Execute lens stacks
│   │   ├── App.tsx
│   │   └── main.tsx
│   ├── package.json
│   └── vite.config.ts
├── config/
│   ├── domains/
│   │   ├── narrative.yaml
│   │   ├── screenplay.yaml
│   │   └── novel.yaml
│   └── server.yaml                 # Hedgerow server config
├── Cargo.toml                      # Workspace root
└── README.md
```

## Implementation Plan

### Phase 1: Prepare premise_grammar (Clean Extraction)

**1.1 Refactor premise-notes (Remove AI)**

File: `premise-notes/src/lib.rs`
- Remove all LLM extraction logic
- Keep only: schemas, JSONL I/O, normalization, deduplication
- Remove dependency on `premise-ai`

File: `premise-notes/Cargo.toml`
- Remove `reqwest`, `sha2`, `hex` dependencies
- Keep only: `serde`, `serde_json`, `anyhow`, `chrono`

**1.2 Remove premise-ai crate**

```bash
rm -rf premise-ai/
```

Update `Cargo.toml`:
```toml
members = [
    "premise-core",
    "premise-notes",
    "premise-cli",
    "premise-lsp",
    "premisecore",  # Python bindings
]
# Remove premise-ai from members
```

**1.3 Remove AI from CLI**

File: `premise-cli/src/main.rs`
- Remove AI-related subcommands
- Keep: `parse`, `validate`, `analyze`, `schema`
- Remove: AI-enhanced `notes extract-facts`, `notes discover-entities`

File: `premise-cli/Cargo.toml`
- Remove `premise-ai` dependency

**1.4 Strip AI from VSCode Extension**

File: `extensions/vscode/src/extension.ts`
- Remove beat generation commands
- Remove entity discovery commands
- Remove all OpenRouter/LLM client code
- Keep: syntax highlighting, LSP client, structural commands

File: `extensions/vscode/package.json`
- Remove AI-related configuration settings
- Remove: `premise.ai.*` settings

**1.5 Update Documentation**

Files to update:
- `README.md` - Remove AI features
- `AI_ROADMAP.md` - Move to premise-studio
- `ADAPTERS.md` - Note adapter migration to Hedgerow

Add note:
```markdown
## AI Features Moved

AI-powered features (beat generation, entity discovery, fact extraction) have been moved to **premise-studio**, a Hedgerow-based application.

See: https://github.com/yourusername/premise-studio
```

**1.6 Git Tag**

```bash
git add .
git commit -m "Extract AI features - language foundation only"
git tag v1.0.0-language-only
git push origin main --tags
```

### Phase 2: Bootstrap premise-studio

**2.1 Create Repository**

```bash
cd ~/repos
mkdir premise-studio
cd premise-studio
git init
```

**2.2 Workspace Setup**

File: `Cargo.toml`
```toml
[workspace]
members = [
    "adapters/premise-parser",
    "adapters/premise-notes",
    "adapters/premise-validator",
]

[workspace.dependencies]
premise-core = { git = "https://github.com/yourusername/premise_grammar", tag = "v1.0.0-language-only" }
premise-notes = { git = "https://github.com/yourusername/premise_grammar", tag = "v1.0.0-language-only" }
hedgerow-runtime = { git = "https://github.com/yourusername/hedgerow", branch = "main" }
hedgerow-core = { git = "https://github.com/yourusername/hedgerow", branch = "main" }
serde = { version = "1.0", features = ["derive"] }
serde_json = "1.0"
anyhow = "1.0"
async-trait = "0.1"
```

**2.3 Directory Structure**

```bash
mkdir -p adapters/premise-parser/src
mkdir -p adapters/premise-notes/src
mkdir -p adapters/premise-validator/src
mkdir -p lenses
mkdir -p stacks
mkdir -p config/domains
mkdir -p frontend/src/components
```

### Phase 3: Implement Core Adapters

**3.1 Premise Parser Adapter**

File: `adapters/premise-parser/Cargo.toml`
```toml
[package]
name = "premise-parser-adapter"
version = "0.1.0"
edition = "2021"

[dependencies]
premise-core = { workspace = true }
hedgerow-runtime = { workspace = true }
serde = { workspace = true }
serde_json = { workspace = true }
anyhow = { workspace = true }
async-trait = { workspace = true }
```

File: `adapters/premise-parser/adapter.json`
```json
{
  "id": "premise-parser",
  "name": "Premise Parser Adapter",
  "version": "0.1.0",
  "description": "Parse .prem files and extract AST, entities, sections",
  "capabilities": {
    "generates_artifacts": true,
    "uses_notes_context": false
  },
  "targets": [
    "premise:parse",
    "premise:extract-entities",
    "premise:extract-sections"
  ]
}
```

File: `adapters/premise-parser/src/lib.rs`
```rust
use async_trait::async_trait;
use hedgerow_runtime::engines::{EngineProvider, Source, ResultEnvelope, ExecutionInfo};
use premise_core::Parser;
use serde_json::{json, Value};
use anyhow::{Result, anyhow};

pub struct PremiseParserAdapter {
    parser: Parser,
}

impl PremiseParserAdapter {
    pub fn new() -> Self {
        Self {
            parser: Parser::new(),
        }
    }
}

#[async_trait]
impl EngineProvider for PremiseParserAdapter {
    fn id(&self) -> &str {
        "premise"
    }

    fn matchers(&self) -> Vec<String> {
        vec!["premise:*".to_string()]
    }

    async fn execute(
        &self,
        target: &str,
        inputs: &[Source],
        _config: &ExecutionMeta,
        _meta: &ObjectiveMeta,
    ) -> Result<Vec<ResultEnvelope>> {
        let content = inputs.first()
            .ok_or_else(|| anyhow!("No input provided"))?
            .text()?;

        match target {
            "premise:parse" => {
                let ast = self.parser.parse(&content)?;

                Ok(vec![
                    ResultEnvelope::json(
                        "parsed_ast",
                        serde_json::to_value(&ast)?,
                        ExecutionInfo::new(target),
                    ),
                ])
            }
            "premise:extract-entities" => {
                let ast = self.parser.parse(&content)?;
                let entities: Vec<_> = ast.entities.iter()
                    .map(|e| json!({
                        "canonical_name": e.name,
                        "type": e.entity_type,
                        "description": e.description,
                    }))
                    .collect();

                Ok(vec![
                    ResultEnvelope::json(
                        "entities",
                        json!(entities),
                        ExecutionInfo::new(target),
                    ),
                ])
            }
            "premise:extract-sections" => {
                let ast = self.parser.parse(&content)?;
                let sections: Vec<_> = ast.sections.iter()
                    .map(|s| json!({
                        "id": s.id,
                        "title": s.title,
                        "level": s.level,
                        "entities": s.entity_mentions,
                    }))
                    .collect();

                Ok(vec![
                    ResultEnvelope::json(
                        "sections",
                        json!(sections),
                        ExecutionInfo::new(target),
                    ),
                ])
            }
            _ => Err(anyhow!("Unknown target: {}", target))
        }
    }
}
```

**3.2 Premise Notes Adapter**

File: `adapters/premise-notes/Cargo.toml`
```toml
[package]
name = "premise-notes-adapter"
version = "0.1.0"
edition = "2021"

[dependencies]
premise-notes = { workspace = true }
hedgerow-runtime = { workspace = true }
serde = { workspace = true }
serde_json = { workspace = true }
anyhow = { workspace = true }
async-trait = { workspace = true }
tokio = { version = "1.0", features = ["fs"] }
```

File: `adapters/premise-notes/adapter.json`
```json
{
  "id": "premise-notes",
  "name": "Premise Notes I/O Adapter",
  "version": "0.1.0",
  "description": "Read and write .premise-notes/ JSONL files",
  "capabilities": {
    "generates_artifacts": true,
    "uses_notes_context": true
  },
  "targets": [
    "premise:notes-reader",
    "premise:notes-writer",
    "premise:notes-query"
  ]
}
```

File: `adapters/premise-notes/src/lib.rs`
```rust
use async_trait::async_trait;
use hedgerow_runtime::engines::{EngineProvider, Source, ResultEnvelope, ExecutionInfo};
use premise_notes::{Beat, Fact, read_beats, write_beats};
use serde_json::{json, Value};
use anyhow::{Result, anyhow};
use std::path::PathBuf;

pub struct PremiseNotesAdapter {
    notes_root: PathBuf,
}

impl PremiseNotesAdapter {
    pub fn new(notes_root: PathBuf) -> Self {
        Self { notes_root }
    }
}

#[async_trait]
impl EngineProvider for PremiseNotesAdapter {
    fn id(&self) -> &str {
        "premise-notes"
    }

    fn matchers(&self) -> Vec<String> {
        vec!["premise:notes-*".to_string()]
    }

    async fn execute(
        &self,
        target: &str,
        inputs: &[Source],
        config: &ExecutionMeta,
        _meta: &ObjectiveMeta,
    ) -> Result<Vec<ResultEnvelope>> {
        match target {
            "premise:notes-reader" => {
                let file_type = config.metadata.get("file_type")
                    .and_then(|v| v.as_str())
                    .unwrap_or("beats");

                let path = self.notes_root.join(format!("{}.jsonl", file_type));
                let data = tokio::fs::read_to_string(&path).await?;

                Ok(vec![
                    ResultEnvelope::json(
                        file_type,
                        serde_json::from_str(&data)?,
                        ExecutionInfo::new(target),
                    ),
                ])
            }
            "premise:notes-writer" => {
                let file_type = config.metadata.get("file_type")
                    .and_then(|v| v.as_str())
                    .unwrap_or("beats");

                let data = inputs.first()
                    .ok_or_else(|| anyhow!("No input data"))?
                    .json()?;

                let path = self.notes_root.join(format!("{}.jsonl", file_type));
                let content = serde_json::to_string(&data)?;
                tokio::fs::write(&path, content).await?;

                Ok(vec![
                    ResultEnvelope::text(
                        "status",
                        format!("Wrote {} to {}", file_type, path.display()),
                        ExecutionInfo::new(target),
                    ),
                ])
            }
            _ => Err(anyhow!("Unknown target: {}", target))
        }
    }
}
```

**3.3 Premise Validator Adapter**

File: `adapters/premise-validator/src/lib.rs`
```rust
use async_trait::async_trait;
use hedgerow_runtime::engines::{EngineProvider, Source, ResultEnvelope, ExecutionInfo};
use serde_json::{json, Value};
use anyhow::{Result, anyhow};

pub struct PremiseValidatorAdapter;

#[async_trait]
impl EngineProvider for PremiseValidatorAdapter {
    fn id(&self) -> &str {
        "premise-validator"
    }

    fn matchers(&self) -> Vec<String> {
        vec!["premise:validate-*".to_string()]
    }

    async fn execute(
        &self,
        target: &str,
        inputs: &[Source],
        _config: &ExecutionMeta,
        _meta: &ObjectiveMeta,
    ) -> Result<Vec<ResultEnvelope>> {
        match target {
            "premise:validate-beats" => {
                let beats: Vec<Value> = inputs[0].json()?;
                let entities: Vec<String> = inputs[1].json()?;

                let mut validated = Vec::new();
                let mut errors = Vec::new();

                for beat in beats {
                    let text = beat["text"].as_str().unwrap_or("");
                    // Extract {Entity} references
                    let refs = extract_entity_refs(text);
                    let unknown: Vec<_> = refs.iter()
                        .filter(|r| !entities.contains(r))
                        .collect();

                    if unknown.is_empty() {
                        validated.push(beat);
                    } else {
                        errors.push(json!({
                            "beat": text,
                            "unknown_entities": unknown,
                        }));
                    }
                }

                Ok(vec![
                    ResultEnvelope::json("validated_beats", json!(validated), ExecutionInfo::new(target)),
                    ResultEnvelope::json("validation_errors", json!(errors), ExecutionInfo::new(target)),
                ])
            }
            _ => Err(anyhow!("Unknown target: {}", target))
        }
    }
}

fn extract_entity_refs(text: &str) -> Vec<String> {
    let re = regex::Regex::new(r"\{([^}]+)\}").unwrap();
    re.captures_iter(text)
        .map(|c| c[1].to_string())
        .collect()
}
```

### Phase 4: Create Lenses

**4.1 Beat Generation Lens**

File: `lenses/beat-generation.yaml`
```yaml
name: "PremiseBeatGeneration"
version: "1.0"
objectives:
  - id: generate
    description: "Generate story beats using LLM with entity validation"
    sources:
      entities:
        uris: ["input://entities.json"]
      sections:
        uris: ["input://sections.json"]
      existing_beats:
        uris: ["input://existing_beats.json"]
        optional: true
    results:
      - id: beats
        kind: json
        schema:
          type: array
          items:
            type: object
            properties:
              text:
                type: string
              entities:
                type: array
                items:
                  type: string
              section:
                type: string
              confidence:
                type: number
    configuration:
      execution:
        targets: ["llm:openrouter/anthropic/claude-3.5-sonnet"]
        metadata:
          temperature: 0.3
          max_tokens: 2000
          system_prompt: |
            You are a story analyst creating beats for a Premise story.

            ENTITY RULES:
            1. Use {Entity} syntax for ALL character/location references
            2. Use canonical entity names from the provided list; do not use aliases
            3. Keep each beat concise and actionable

            FORMAT:
            Output JSON array of objects with: text, entities[], section, confidence

            Canonical entities: {{entities}}
            Current sections: {{sections}}
```

**4.2 Entity Discovery Lens**

File: `lenses/entity-discovery.yaml`
```yaml
name: "PremiseEntityDiscovery"
version: "1.0"
objectives:
  - id: discover
    description: "Discover entities from narrative text"
    sources:
      content:
        uris: ["input://content.txt"]
      known_entities:
        uris: ["input://known_entities.json"]
        optional: true
    results:
      - id: discovered
        kind: json
        schema:
          type: array
          items:
            type: object
            properties:
              canonical_name:
                type: string
              type:
                type: string
                enum: [character, location, object, concept]
              aliases:
                type: array
                items:
                  type: string
              description:
                type: string
              evidence:
                type: array
              confidence:
                type: number
    configuration:
      execution:
        targets: ["llm:openrouter/anthropic/claude-3.5-sonnet"]
        metadata:
          temperature: 0.2
          system_prompt: |
            Identify potential entities (character, location, object, concept), aliases, brief descriptions, and evidence lines.

            RULES:
            1. Propose canonical names; list aliases (nicknames, titles)
            2. Classify type using context heuristics
            3. Provide evidence as line numbers/quotes
            4. Confidence: 1.0 explicit, 0.8 strong contextual, 0.5 ambiguous

            OUTPUT FORMAT:
            JSON array of entity candidates
```

**4.3 Fact Extraction Lens**

File: `lenses/fact-extraction.yaml`
```yaml
name: "PremiseFactExtraction"
version: "1.0"
objectives:
  - id: extract
    description: "Extract facts about entities from text"
    sources:
      content:
        uris: ["input://content.txt"]
      entities:
        uris: ["input://entities.json"]
    results:
      - id: facts
        kind: json
        schema:
          type: array
          items:
            type: object
            properties:
              type:
                type: string
              entity:
                type: string
              fact:
                type: string
              evidence:
                type: array
              confidence:
                type: number
    configuration:
      execution:
        targets: ["llm:openrouter/anthropic/claude-3.5-sonnet"]
        metadata:
          temperature: 0.2
          system_prompt: |
            Extract concise facts about entities from the provided text.

            RULES:
            1. Use canonical entity names when available
            2. Provide evidence as line references when possible
            3. Assign confidence 0.0–1.0 (explicit=1.0, strong≈0.8, weak≈0.6)

            OUTPUT FORMAT:
            JSON array of fact objects
```

### Phase 5: Create Lens Stacks

**5.1 Beat Generation Stack**

File: `stacks/generate-beats.yaml`
```yaml
version: "0.3"
steps:
  - id: parse_story
    lens:
      inline:
        name: "ParseStory"
        objectives:
          - id: parse
            sources:
              file:
                uris: ["input://story.prem"]
            results:
              - id: entities
                kind: json
              - id: sections
                kind: json
            configuration:
              execution:
                targets: ["premise:extract-entities", "premise:extract-sections"]

  - id: load_existing
    lens:
      inline:
        name: "LoadExisting"
        objectives:
          - id: read
            sources:
              notes:
                uris: ["file://.premise-notes/beats.jsonl"]
                optional: true
            results:
              - id: beats
                kind: json
            configuration:
              execution:
                targets: ["premise:notes-reader"]
                metadata:
                  file_type: "beats"

  - id: generate_beats
    lens:
      from: "./lenses/beat-generation.yaml"
    inputs:
      entities: "step://parse_story/entities"
      sections: "step://parse_story/sections"
      existing_beats: "step://load_existing/beats"
    depends_on: [parse_story, load_existing]

  - id: validate_beats
    lens:
      inline:
        name: "ValidateBeats"
        objectives:
          - id: validate
            sources:
              beats:
                uris: ["step://generate_beats/beats"]
              entities:
                uris: ["step://parse_story/entities"]
            results:
              - id: validated
                kind: json
              - id: errors
                kind: json
            configuration:
              execution:
                targets: ["premise:validate-beats"]
    depends_on: [generate_beats]

  - id: write_beats
    lens:
      inline:
        name: "WriteBeats"
        objectives:
          - id: write
            sources:
              beats:
                uris: ["step://validate_beats/validated"]
            results:
              - id: status
                kind: text
            configuration:
              execution:
                targets: ["premise:notes-writer"]
                metadata:
                  file_type: "beats"
    depends_on: [validate_beats]
```

**5.2 Bootstrap Story Stack**

File: `stacks/bootstrap-story.yaml`
```yaml
version: "0.3"
steps:
  - id: discover_entities
    lens:
      from: "./lenses/entity-discovery.yaml"
    inputs:
      content: "input://story.prem"

  - id: extract_facts
    lens:
      from: "./lenses/fact-extraction.yaml"
    inputs:
      content: "input://story.prem"
      entities: "step://discover_entities/discovered"
    depends_on: [discover_entities]

  - id: generate_beats
    lens:
      from: "./lenses/beat-generation.yaml"
    inputs:
      entities: "step://discover_entities/discovered"
      sections: "input://sections.json"
    depends_on: [discover_entities]

  - id: persist_all
    lens:
      inline:
        name: "PersistAll"
        objectives:
          - id: write_entities
            sources:
              data:
                uris: ["step://discover_entities/discovered"]
            configuration:
              execution:
                targets: ["premise:notes-writer"]
                metadata:
                  file_type: "entities"
          - id: write_facts
            sources:
              data:
                uris: ["step://extract_facts/facts"]
            configuration:
              execution:
                targets: ["premise:notes-writer"]
                metadata:
                  file_type: "facts"
          - id: write_beats
            sources:
              data:
                uris: ["step://generate_beats/beats"]
            configuration:
              execution:
                targets: ["premise:notes-writer"]
                metadata:
                  file_type: "beats"
    depends_on: [discover_entities, extract_facts, generate_beats]
```

### Phase 6: Frontend Setup

**6.1 Initialize React App**

```bash
cd frontend
npm create vite@latest . -- --template react-ts
npm install @tanstack/react-query axios recharts
```

**6.2 Core Components**

File: `frontend/src/components/LensExecutor.tsx`
```typescript
import { useState } from 'react';
import axios from 'axios';

interface LensExecutorProps {
  stackFile: string;
  inputs: Record<string, any>;
}

export function LensExecutor({ stackFile, inputs }: LensExecutorProps) {
  const [running, setRunning] = useState(false);
  const [result, setResult] = useState<any>(null);

  const execute = async () => {
    setRunning(true);
    try {
      const response = await axios.post('http://localhost:3000/api/v1/assessments', {
        stack_ref: stackFile,
        inputs,
      });
      setResult(response.data);
    } catch (error) {
      console.error('Execution failed:', error);
    } finally {
      setRunning(false);
    }
  };

  return (
    <div>
      <button onClick={execute} disabled={running}>
        {running ? 'Running...' : 'Execute Lens'}
      </button>
      {result && (
        <div>
          <h3>Result</h3>
          <pre>{JSON.stringify(result, null, 2)}</pre>
        </div>
      )}
    </div>
  );
}
```

File: `frontend/src/components/BeatEditor.tsx`
```typescript
import { useState, useEffect } from 'react';

interface Beat {
  id: string;
  text: string;
  entities: string[];
  section?: string;
}

export function BeatEditor() {
  const [beats, setBeats] = useState<Beat[]>([]);

  useEffect(() => {
    // Load beats from .premise-notes/beats.jsonl
    loadBeats();
  }, []);

  const loadBeats = async () => {
    // Call Hedgerow API to read notes
    const response = await fetch('/api/read-notes?type=beats');
    const data = await response.json();
    setBeats(data);
  };

  return (
    <div className="beat-editor">
      <h2>Story Beats</h2>
      {beats.map(beat => (
        <div key={beat.id} className="beat-item">
          <p>{beat.text}</p>
          <div className="entities">
            {beat.entities.map(e => (
              <span key={e} className="entity-tag">{e}</span>
            ))}
          </div>
        </div>
      ))}
    </div>
  );
}
```

### Phase 7: Configuration

**7.1 Hedgerow Server Config**

File: `config/server.yaml`
```yaml
server:
  host: "0.0.0.0"
  port: 3000

storage:
  metadata:
    type: filesystem
    root: ".hedgerow/metadata"
  blobs:
    type: filesystem
    root: ".hedgerow/blobs"

providers:
  - type: openrouter
    api_key_env: "OPENROUTER_API_KEY"
  - type: bedrock
    region: "us-west-2"

adapters:
  - path: "./adapters/premise-parser"
  - path: "./adapters/premise-notes"
  - path: "./adapters/premise-validator"
```

**7.2 Domain Templates**

File: `config/domains/narrative.yaml`
```yaml
id: narrative
name: "Narrative Story"
description: "Traditional story structure with characters, locations, and plot"
entity_types:
  - character
  - location
  - object
  - concept
section_types:
  - act
  - scene
  - cel
content_types:
  - beat
  - treatment
  - narrative
```

### Phase 8: Build and Test

**8.1 Build Adapters**

```bash
cd premise-studio
cargo build --release
```

**8.2 Test Parser Adapter**

```bash
# Create test file
cat > test.prem <<EOF
@character Hero: A brave adventurer

= Act One
== The Beginning
{Hero} sets out on a journey.
EOF

# Test parse
cargo run --bin hedgerow -- run --file test-stack.yaml
```

File: `test-stack.yaml`
```yaml
version: "0.3"
steps:
  - id: test_parse
    lens:
      inline:
        name: "TestParse"
        objectives:
          - id: parse
            sources:
              file:
                uris: ["file://test.prem"]
            results:
              - id: entities
                kind: json
            configuration:
              execution:
                targets: ["premise:extract-entities"]
```

**8.3 Test Beat Generation**

```bash
export OPENROUTER_API_KEY=sk-or-v1-...
cargo run --bin hedgerow -- run --file stacks/generate-beats.yaml
```

### Phase 9: Documentation

**9.1 Main README**

File: `README.md`
```markdown
# Premise Studio

AI-powered story writing application built on Hedgerow, using Premise grammar.

## Quick Start

### Prerequisites
- Rust toolchain
- Node.js 18+
- OpenRouter API key

### Installation

1. Clone repository:
   ```bash
   git clone https://github.com/yourusername/premise-studio
   cd premise-studio
   ```

2. Build adapters:
   ```bash
   cargo build --release
   ```

3. Start Hedgerow server:
   ```bash
   export OPENROUTER_API_KEY=sk-or-v1-...
   cargo run -p hedgerow-rest-server -- --config config/server.yaml
   ```

4. Start frontend:
   ```bash
   cd frontend
   npm install
   npm run dev
   ```

### Usage

#### Generate Beats

```bash
hedgerow run --file stacks/generate-beats.yaml --input story.prem
```

#### Bootstrap New Story

```bash
hedgerow run --file stacks/bootstrap-story.yaml --input draft.prem
```

#### Extract Facts

```bash
hedgerow run --file stacks/extract-facts.yaml --input chapter1.prem
```

## Architecture

- `adapters/` - Custom Premise adapters for Hedgerow
- `lenses/` - Reusable lens definitions
- `stacks/` - Complete workflows
- `frontend/` - React UI
- `config/` - Server and domain configuration

## Documentation

- [Lens Reference](docs/lenses.md)
- [Adapter Development](docs/adapters.md)
- [Premise Grammar](https://github.com/yourusername/premise_grammar)
```

**9.2 Adapter Development Guide**

File: `docs/adapters.md`
```markdown
# Adapter Development Guide

## Creating a Custom Adapter

1. Create crate:
   ```bash
   cargo new --lib adapters/my-adapter
   ```

2. Implement `EngineProvider`:
   ```rust
   use hedgerow_runtime::engines::EngineProvider;

   pub struct MyAdapter;

   #[async_trait]
   impl EngineProvider for MyAdapter {
       fn id(&self) -> &str { "my-adapter" }
       fn matchers(&self) -> Vec<String> { vec!["my:*".into()] }
       async fn execute(...) -> Result<Vec<ResultEnvelope>> { ... }
   }
   ```

3. Register in `config/server.yaml`:
   ```yaml
   adapters:
     - path: "./adapters/my-adapter"
   ```

## Testing Adapters

```bash
cargo test -p my-adapter
```
```

## Execution Checklist

- [ ] Phase 1: Clean premise_grammar (remove AI)
- [ ] Phase 2: Create premise-studio repo
- [ ] Phase 3: Implement adapters (parser, notes, validator)
- [ ] Phase 4: Create lenses (beat-gen, entity-discovery, fact-extraction)
- [ ] Phase 5: Create stacks (bootstrap, generate-beats)
- [ ] Phase 6: Build frontend
- [ ] Phase 7: Configuration files
- [ ] Phase 8: Build and test
- [ ] Phase 9: Documentation

## Success Criteria

✅ premise_grammar has no AI dependencies
✅ All AI features work via Hedgerow lenses
✅ Custom adapters integrate premise-core and premise-notes
✅ Beat generation produces valid output
✅ Entity discovery finds and validates entities
✅ Frontend can execute lens stacks
✅ Notes system persists to .premise-notes/
