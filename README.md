# Premise Tree-sitter Grammar

Tree-sitter grammar for the Premise language - a domain-specific language for story authoring with hierarchical content organization, entity definitions, and screenplay-style dialogue.

## Overview

This repo now includes:

- Grammar and editor integrations (this root)
- Rust core crate `premise-core` with a CLI and JSON outputs
- Python bindings `premisecore` (PyO3/maturin)

Note: Python packages cannot contain hyphens; the Python crate/module is named `premisecore` while the Rust crate is `premise-core`.

Read the quick start guide: [QUICKSTART.md](./QUICKSTART.md)

### What we have now

- Production-ready Tree-sitter grammar and queries
- Editor extensions for VSCode/Cursor and Zed
- Rust core (`premise-core`):
  - `premise parse|validate|analyze|plan` with `--format json|pretty`
  - JSON Schemas via `premise schema --type <...>`
- Python package (`premisecore`): `Parser.parse_json`, `validate_json`, `analyze_json`, `plan_json`, and `schema()`

### What's next (adapters)

- Adapter registry and APIs (list/show, identity rules)
- Deterministic execution engine (sequential), provenance
- Hydration of domain models and artifact outputs
- Hardening: limits/timeouts, caching, benchmarks, fuzzing

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

Core CLI (premise-core)

```bash
cd premise-core
cargo build
cargo run -- --format json parse examples/theming_showcase.prem --ast --symbols --imports --resolved-imports
cargo run -- schema --type all
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
- See `CLAUDE.md` for detailed extension development workflow

## Repository Structure

- `grammar.js` - Grammar definition
- `queries/` - Editor queries (highlights, brackets, indentation)
- `examples/` - Reference `.prem` files for testing
- `scripts/` - Build and validation utilities
- `src/` - Generated parser artifacts
- `premise-core/` - Rust core with CLI (`premise`) and JSON outputs/schemas
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
```

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
