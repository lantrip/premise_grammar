# Premise Tree-sitter Grammar

Tree-sitter grammar for the Premise language - a domain-specific language for story authoring with hierarchical content organization, entity definitions, and screenplay-style dialogue.

## Overview

This repo now includes:

- Grammar and editor integrations (this root)
- Rust core crate `premise-core` (library only; CLI split to `premise` crate)
- Python bindings `premisecore` (PyO3/maturin)

Note: Python packages cannot contain hyphens; the Python crate/module is named `premisecore` while the Rust crate is `premise-core`.

### What we have now

- Production-ready Tree-sitter grammar and queries
- Editor extensions for VSCode/Cursor and Zed
- Rust CLI (`premise` crate):
  - `premise parse|validate|analyze|plan` with `--format json|pretty`
  - JSON Schemas via `premise schema --type <...>`
  - Notes LLM overrides for text modes (`--extractor llm`): `--llm-provider`, `--model`, `--endpoint`, `--api-key-env`, `--temperature`, `--max-tokens`, `--llm-replay`
- Python package (`premisecore`): `Parser.parse_json`, `validate_json`, `analyze_json`, `plan_json`, and `schema()`

### Adapter Framework (Foundation Complete ✅)

**Domain-agnostic content transformation** - Same `.prem` file works as story, sales call, or architecture doc.

- ✅ Adapter registry with auto-discovery (`premise adapters list/show`)
- ✅ Domain abstraction (Narrative/Sales/Architecture mappers)
- ✅ Notes Context API (adapters query story knowledge)
- ✅ Example adapters for 3 domains

**What's next**: Execution engine, provenance tracking, adapter writes to notes

📖 **Full guide**: [ADAPTERS.md](./ADAPTERS.md)

### Roadmap concepts to be aware of

- Deterministic ordering and reproducibility
- Import resolution base paths and diagnostics
- Adapter identity (IDs vs paths) and config format
- Provenance and artifact naming/stability

## Quick Start

```bash
# Build grammar and WASM
./build.sh

# Validate all query files
./test_queries.sh

# Test on a file
tree-sitter parse examples/theming_showcase.prem
```

Core CLI (premise)

```bash
cargo build -p premise
./target/debug/premise --format json parse examples/theming_showcase.prem --ast --symbols --imports --resolved-imports
./target/debug/premise schema --type all
```

Python (premisecore)

```bash
cd premisecore
python -m venv .venv && source .venv/bin/activate
pip install maturin
maturin develop
python - <<'PY'
import premisecore as pc
p = pc.Parser()
print(pc.schema('parse'))
print(p.parse_json('', False, False, False))
PY
```

## Core Features

**Story Structure**

- Hierarchical headers: `= Act`, `== Scene`, `=== Cel`
- Content types: `///` (beats), `//` (treatment), `/` (narrative)
- File headers: `TITLE:`, `WORLD:`, `FORMAT:`

**Entity System**

- Definitions: `@character Hero: Description`
- Blocks: `@characters { ... }` with nested content support
- References: `{Hero}` with semantic highlighting

**Screenplay Elements**

- Character speakers: `{Hero}` as dialogue markers
- Parentheticals: `(whisper)` action directions
- Clean indented dialogue without quotes

**Metadata & Imports**

- Metadata: `+key: value` (note: `+` prefix)
- Imports: `@import "file.yaml"`
- Adapters: `@adapter "path.ts"`
- Comments: `# text`

## Development

```bash
# Core workflow
tree-sitter generate        # Generate parser
tree-sitter build --wasm    # Build WASM
./test_queries.sh           # Validate queries

# Testing
tree-sitter test            # Run test suite
tree-sitter parse file.cune # Test specific file

# Extension development
./scripts/sync-extensions.sh     # Sync WASM/queries to extensions
./scripts/update-zed-rev.sh      # Update Zed extension to current commit
```

### Editor Extension Development

**Quick Setup:**

```bash
# Zed - Push changes, then update and install
git push && ./scripts/update-zed-rev.sh
# Then: Zed → Cmd+Shift+P → "Install Dev Extension" → select extensions/zed/

# VSCode - Build and install
cd extensions/vscode && npm run compile && code --install-extension .
```

**Key Points:**

- Zed extension always uses GitHub repository (push changes first)
- Always run `./test_queries.sh` after changing `queries/*.scm`
- Use `./scripts/sync-extensions.sh` to copy updates to extensions
- Use `./scripts/update-zed-rev.sh` to point Zed to latest commit
- VSCode/Cursor extension now includes an LSP client that supports diagnostics, document symbols (with story hierarchy), hover/definition/references, completion, and commands:
  - Command Palette: “Premise: Show Beats for Entity Under Cursor”
  - Context menu: right-click with a selection in a `.prem` file
  - “Premise: Scan Workspace” to force a full rescan
- Shared notes schemas now live in `premise-notes/` (see `premise-notes/README.md`).
- See `AI_ROADMAP.md` for consolidated status and next steps

### AI Features

**Beat & Entity Generation**

- `Premise: Generate Beats…` — AI-generated `///` beats anchored to sections
- `Premise: Update Entity Descriptions…` — Update `@entity` descriptions from story
- Provider: OpenRouter (Settings → `premise.ai.*`)

**Story Notes System** (`.premise-notes/`) — Production Ready

Structured story knowledge base with intelligent extraction and CLI-first architecture. Supports modular sinks and alias/uncertainty normalization.

**Key Features**

- ✅ Entity trait extraction from `@character Name: Description` (1.0 confidence)
- ✅ Co-occurrence relationship discovery from scenes/dialogue (≈0.7 confidence)
- ✅ Section context for all records (act/scene/cel)
- ✅ JSONL storage (append/merge/tool-friendly)
- ✅ Deterministic outputs with snapshot tests
- ✅ Actionable error messages

**CLI Commands**

````bash
# Initialize notes directory
premise notes init . --title "My Story"

# Export beats (with normalization of {Alias}→{Canonical}, unknown → {?Name})
premise notes export-beats story/scene1.prem --sink notes [--dry-run] [--stable-ids]
# Sinks: --sink stdout|jsonl-dir|dir (use with --out-dir ./out)
# Ingest non-Premise text: --input plain|markdown --stdin; normalize with --aliases aliases.json

# Extract facts (AI-enhanced heuristics + alias normalization)
premise notes extract-facts story/scene1.prem --sink notes [--dry-run] [--stable-ids]

# Extract timeline events
premise notes extract-timeline story/scene1.prem --sink notes [--dry-run] [--stable-ids]

# Normalize existing notes against current aliases
premise notes normalize . [--dry-run]

# Entity utilities
premise notes discover-entities story/scene1.prem --format json
premise notes list-entities story/scene1.prem

# Unknowns & Aliases
premise notes summarize-uncertain --path .
premise notes merge-aliases --aliases aliases_update.json --path . [--dry-run]

## Alias Workflow (Quick Reference)

Keep aliases simple: map canonical names to a few nicknames.

```json
// .premise-notes/aliases.json
{
  "Maya Chen": ["Maya", "Chen"],
  "Last Library": ["Library"]
}
````

### LLM flags and precedence (text modes)

When using `--extractor llm` for plain/markdown inputs, you can override AI settings:

```bash
premise notes export-beats novel.md --input markdown --extractor llm \
  --llm-provider openrouter --model openai/gpt-4o-mini --llm-replay read_write

premise notes extract-facts novel.md --input markdown --extractor llm \
  --api-key-env OPENROUTER_API_KEY --temperature 0.2 --max-tokens 1500
```

Precedence for AI config: CLI flags > `.premise-notes/ai.json` > `~/.config/premise/ai.json` > defaults.

```json
// alias-delta.json (additions only)
{
  "Maya Chen": ["M"],
  "Kai Ito": ["Kai"]
}
```

```bash
# Preview changes
premise notes apply-alias-delta --delta alias-delta.json --path . --dry-run
# Apply changes
premise notes apply-alias-delta --delta alias-delta.json --path .
```

# Review & apply (non-interactive)

```bash
# Review a proposal (from prior extraction), auto-approve high-confidence
premise notes review-extraction --proposal proposal.json --path . \
  --strategy approve-high-confidence --min-confidence 0.7 --out-actions actions.json --format json

# Apply the actions to notes (dry-run first)
premise notes apply-actions --actions actions.json --path . --dry-run
premise notes apply-actions --actions actions.json --path .
```

# Query and index

premise notes query --entity "Hero" .
premise notes rebuild-index .

# Handy shell queries

grep '"Hero"' .premise-notes/facts.jsonl | jq 'select(.type=="trait")'
jq 'select(.confidence >= 0.9)' .premise-notes/facts.jsonl

````

**VSCode Commands**

- `Premise: Extract Facts to Notes…`
- `Premise: Export Beats to Notes…`
- `Premise: Discover Entities…` (planned UI; available via CLI today)

📖 See `AI_ROADMAP.md` for full specs and policies. Notes schemas: `premise-notes/src/schema.rs`.

## Repository Structure

- `grammar.js` - Grammar definition
- `queries/` - Editor queries (highlights, brackets, indentation)
- `examples/` - Reference `.prem` files for testing
- `scripts/` - Build and validation utilities
- `src/` - Generated parser artifacts
- `premise-core/` - Rust core library (parser/IR/plan; Premise-specific extractors)
- `premise/` - Rust CLI crate (was in `premise-core`), invokes `premise-core` and `premise-notes`
- `premise-notes/` - Domain-agnostic notes (schemas, I/O, sinks, normalize, discovery, text extraction)
- `premise-ai/` - Shared AI config/provider for LLM-backed extraction
- `premisecore/` - Python bindings (PyO3/maturin)
- `extensions/` - Editor extensions (Zed, VSCode)
  - `zed/` - Zed editor extension
  - `vscode/` - VSCode extension
  - `README.md` - Extension development guide

## Grammar Status

✅ **Production Ready** - All core features work reliably

- Story structure, entity system, dialogue parsing
- Semantic highlighting with story-focused scopes
- Editor integration (VSCode, Cursor, Zed)

🟡 **Minor Edge Cases** - Intentional parsing constraints

- Empty entity references `{}` (invalid)
- Nested braces in entities (ambiguous)
- Multi-line entity names (readability)

See `examples/theming_showcase.prem` for comprehensive syntax demonstration.

## Entity Block Highlighting: Core Fix Notes

We recently improved how entity list items inside blocks (e.g., `@characters { - Mentor: A wise... }`) are parsed and highlighted so that the entity key (`Mentor`) is styled differently than the description value.

What changed:

- Added grammar nodes for structured block items:
  - `entity_line` now supports either `entity_desc` or a nested `entity_object` value
  - New nodes: `entity_object`, `object_property`, `prop_key`, `prop_value`
- Updated highlight queries (`queries/highlights.scm` and extension copies) to capture:
  - `(entity_line (entity_name))` as the entity key
  - `(entity_line (entity_desc))` as the value
  - `(object_property (prop_key))` and `(prop_value)` inside nested objects (e.g., `@eras`)
- VSCode semantic tokens map:
  - `entity_name` → standard `variable` (readonly) for broad theme support
  - `entity_desc`/`prop_value` → `string`
  - `prop_key` → `property`

Why this was needed:

- Previously, entity lines in blocks were not split into key/value nodes, so we couldn’t theme names and descriptions separately.
- TextMate patterns could also overshadow semantic tokens by applying a wide scope. We narrowed the TextMate rule for `{Entity}` references to avoid capturing large regions and let semantic tokens show through.

Editor/theme notes:

- VSCode themes must have semantic highlighting enabled. Our themes now set `"semanticHighlighting": true` and include colors for the `property` token.
- If using non-Premise themes, semantic tokens still work because we use standard token types (`variable`, `string`, `property`).

## Integration

**VSCode/Cursor Extension**: Uses this grammar for syntax highlighting, outline, and navigation
**Web/WASM**: `tree-sitter-premise.wasm` for browser-based editing
**Other Editors**: Reference `queries/` for syntax highlighting rules

## Semantic Scopes

Story-focused scopes for rich theming:

- `markup.heading.*.story.*` - Story structure hierarchy
- `keyword.control.content.*` - Content type markers
- `entity.name.*` - Character/location references
- `comment.line` vs `text.narrative` - Author notes vs story content

## Extension Development

This repository includes editor extensions in `extensions/`:

```bash
# Quick development workflow (rebuild + install)
./scripts/dev.sh              # Install to all available editors
./scripts/dev.sh vscode       # Install to VSCode only
./scripts/dev.sh cursor       # Install to Cursor only
./scripts/dev.sh zed          # Prepare Zed extension

# Or manually:
./scripts/install-extensions.sh [vscode|cursor|zed|all]
````

The extensions auto-build and install to your local editors for immediate testing.
See `extensions/README.md` for detailed extension development workflow.

## Debugging Syntax Highlighting

**VSCode Token Inspector** (Essential for debugging highlighting issues):

1. Open a `.prem` file in VSCode
2. Place cursor on the problematic text
3. Press `Cmd+Shift+P` → "Developer: Inspect Editor Tokens and Scopes"
4. Review the token information panel:
   - **TextMate scopes**: Shows which grammar rules are matching
   - **Semantic token type**: Shows Tree-sitter semantic tokens
   - **Foreground color**: Shows which theme rule is being applied

Common debugging scenarios:

- **No TextMate scopes** (only `source.premise`): Pattern isn't matching - check pattern precedence
- **Semantic token overriding TextMate**: Semantic tokens take priority - may need to disable semantic token for that node
- **Split coloring** (e.g., `@adapt` vs `er`): Conflicting tokens - check both semantic and TextMate rules
- **Wrong scope matching**: Earlier pattern taking precedence - reorder patterns in `syntaxes/premise.tmLanguage.json`

Tree-sitter debugging:

```bash
# Parse file and show syntax tree
tree-sitter parse examples/theming_showcase.prem

# Test specific text
echo '@adapter test: { }' | tree-sitter parse

# Check for ERROR nodes (indicates grammar issues)
tree-sitter parse file.prem | grep ERROR
```

## Contributing

1. Edit `grammar.js` and/or `queries/*.scm`
2. Run `./build.sh` to build
3. Run `./test_queries.sh` to validate
4. Run `./scripts/sync-extensions.sh` to update extensions
5. Test extensions with example files
6. Use VSCode's token inspector to verify highlighting

**Key Rule**: Always validate queries with `./test_queries.sh` before committing to prevent editor extension errors.
