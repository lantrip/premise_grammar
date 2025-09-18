# Cuneiform Tree-sitter Grammar

Tree-sitter grammar for the Cuneiform language - a domain-specific language for story authoring with hierarchical content organization, entity definitions, and screenplay-style dialogue.

## Quick Start

```bash
# Build grammar and WASM
./build.sh

# Validate all query files
./test_queries.sh

# Test on a file
tree-sitter parse examples/theming_showcase.cune
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
```

## Repository Structure

- `grammar.js` - Grammar definition
- `queries/` - Editor queries (highlights, brackets, indentation)
- `examples/` - Reference `.cune` files for testing
- `scripts/` - Build and validation utilities
- `src/` - Generated parser artifacts
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

See `examples/theming_showcase.cune` for comprehensive syntax demonstration.

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
- If using non-Cuneiform themes, semantic tokens still work because we use standard token types (`variable`, `string`, `property`).

## Integration

**VSCode/Cursor Extension**: Uses this grammar for syntax highlighting, outline, and navigation
**Web/WASM**: `tree-sitter-cuneiform.wasm` for browser-based editing
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

## Contributing

1. Edit `grammar.js` and/or `queries/*.scm`
2. Run `./build.sh` to build
3. Run `./test_queries.sh` to validate
4. Run `./scripts/sync-extensions.sh` to update extensions
5. Test extensions with example files

**Key Rule**: Always validate queries with `./test_queries.sh` before committing to prevent editor extension errors.
