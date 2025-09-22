# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Tree-sitter grammar for the Premise language - a domain-specific language for story authoring that supports hierarchical content organization (acts/scenes/cels), entity definitions, screenplay-style dialogue, content typing, and metadata.

**Core Responsibility**: This repository is the **foundational layer** for all Premise editor support, providing:

- Grammar definition (`grammar.js`) - currently production-ready with all core features working
- **Story-focused semantic scopes** (`queries/highlights.scm`) that enable rich theming
- Editor queries for syntax highlighting, indentation, navigation, and brackets
- Validation tools and scripts to ensure query compatibility
- WASM build for web/VSCode integration

## Development Commands

### Essential Commands

- `./build.sh` - Build grammar and WASM (recommended)
- `./test_queries.sh` - **Critical**: Validate all query files before committing
- `tree-sitter generate` - Generate parser from grammar.js
- `tree-sitter test` - Run parser tests
- `tree-sitter parse <file>` - Parse a file and show syntax tree

### Query Development

- **Always run `./test_queries.sh` after modifying `queries/*.scm`**
- This validates that semantic scopes match actual grammar nodes
- Prevents editor extension errors from invalid queries

### Language Bindings

- **Node.js**: Built using binding.gyp with `node-gyp rebuild`
- **Rust**: Built with `cargo build` - includes test for grammar loading
- **Python (PyO3/maturin)**:
  - Location: `premisecore/`
  - Naming note: Python modules cannot contain hyphens, so the Python package/module is `premisecore` (no `-`). The Rust crate remains `premise-core`.
  - Build locally:
    ```bash
    cd premisecore
    python -m venv .venv && source .venv/bin/activate
    pip install maturin
    maturin develop
    ```
  - Usage:
    ```python
    import premisecore as pc
    p = pc.Parser()
    print(p.parse_json("", False, False, False))
    print(pc.schema("all"))
    ```

## CLI Additions (premise-core)

- Global flag: `--format json|pretty` (default pretty)
- Subcommands:
  - `parse <file> [--ast --symbols --imports --resolved-imports]`
  - `validate <file>`
  - `analyze <file>`
  - `plan <file> [--graph-only]`
  - `schema [--type parse|validate|analyze|plan|all] [--out path]`

Examples:

```bash
premise --format json parse examples/theming_showcase.prem --ast --symbols --imports --resolved-imports
premise --format json validate path/to/file.prem
premise schema --type all
```

## Premise Language Syntax

### Core Grammar Elements

- **Hierarchical Headers**: Acts (`=`), Scenes (`==`), Cels (`===`) with optional location/time markers
- **Screenplay Dialogue**: Character names as speakers (`{Hero}`), indented dialogue, parentheticals `(whisper)`
- **Content Types**: Beat (`///`), Treatment (`//`), Narrative (`/`) prefixes
- **Entity System**: Definitions (`@character Name`) and blocks (`@characters { }`), references (`{Name}`)
- **File Headers**: `TITLE:`, `WORLD:`, `FORMAT:` declarations
- **Imports/Adapters**: `@import` statements and `@adapter` configurations
- **Metadata**: `+key: value` pairs (note: `+` prefix, not `@`)
- **Comments**: `#` prefixed lines

### Repository Structure

- `grammar.js` - Core grammar definition
- `queries/` - Editor query files for syntax highlighting, brackets, indentation, and outline
- `examples/` - Reference files including `theming_showcase.prem` for theme development
- `scripts/` - Validation utilities including `validate_scopes.py`
- `tests/` - Test cases and test runner
- `src/` - Generated parser artifacts (do not edit manually)

## Semantic Scopes Architecture

### Story-Focused Theming (`queries/highlights.scm`)

The semantic scopes are designed specifically for story authors and enable rich theming across different writing workflows:

**Story Structure Hierarchy:**

- `markup.heading.1.story.act` - Act headers
- `markup.heading.2.story.scene` - Scene headers
- `markup.heading.3.story.cel` - Cel headers

**Content Type Layers:**

- `keyword.control.content.beat` - Structural story beats (`///`)
- `keyword.control.content.treatment` - Scene direction (`//`)
- `keyword.control.content.narrative` - Final story text (`/`)

**Dialogue & Screenplay Elements:**

- `entity.name.character.speaker` - Character speakers (`{Hero}`)
- `text.parenthetical` - Action directions `(whisper)`
- `markup.list.dialogue` - Indented dialogue content

**Author vs Story Content:**

- `comment.line` - Author notes (distinguished from story)
- `text.narrative` - Story prose and dialogue
- `entity.name.reference` - Character/location names (`{Hero}`)

### Critical Importance

These scopes are the **foundation** that enables:

- Story author themes (screenplay, novel, dark themes)
- Content layer distinction (planning vs final text)
- Visual hierarchy for different story elements
- Clear separation between author notes and story content

**Any changes to semantic scopes affect all editor extensions that consume this grammar.**

### Scope Validation

- Run `./test_queries.sh` after any changes to verify scopes match grammar nodes
- This prevents editor extension failures from invalid scope references
- Extensions depend on these scopes for proper theming functionality

## Grammar Status

**Production Ready**: All core features work reliably

- ✅ Story structure (acts/scenes/cels)
- ✅ Entity system with references
- ✅ Screenplay-style dialogue
- ✅ Content types and file headers
- ✅ Semantic highlighting with story-focused scopes

**Minor Edge Cases**: Intentional parsing constraints

- 🟡 Empty entity references `{}` (invalid by design)
- 🟡 Nested braces in entities (prevents ambiguity)
- 🟡 Multi-line entity names (maintains readability)

## Working with Examples

- Use `examples/theming_showcase.prem` for comprehensive syntax testing
- Reference `.prem` files in `examples/` rather than trying to document every syntax pattern
- All major language features are demonstrated in working example files
- Parse examples with `tree-sitter parse examples/file.prem` to understand structure

## Extension Development Workflow

### Monorepo Structure

This repository now includes editor extensions in `extensions/`:

- `extensions/zed/` - Zed editor extension
- `extensions/vscode/` - VSCode extension
- `themes/` - Shared theme definitions
- `scripts/` - Build and sync utilities

### Development vs Production

**Development (Local Testing):**

- Zed: Uses `file://` reference to local grammar in `extension.toml`
- VSCode: Copies WASM and queries from grammar root
- Test changes immediately without git commits

**Production (Publishing):**

- Zed: Must reference git repository with specific commit/rev
- VSCode: Bundles pre-built WASM in extension package
- Requires committed changes in main repository

### Extension Development Commands

**Sync Extensions from Grammar:**

```bash
# Copy WASM and queries to extensions
./scripts/sync-extensions.sh

# Test Zed extension (development)
cd extensions/zed
# Use "Install Dev Extension" in Zed command palette

# Test VSCode extension
cd extensions/vscode
npm run compile
code --install-extension .
```

### Zed Extension Development Workflow

**Simplified Workflow**: Always use GitHub repository with revision hash.

**Testing Zed Extension Changes:**

```bash
# 1. Make your grammar/query changes
# 2. Commit and push changes
git add . && git commit -m "Update grammar/queries"
git push

# 3. Update extension to use latest commit
./scripts/update-zed-rev.sh

# 4. Install in Zed
# In Zed: Cmd+Shift+P → "Install Dev Extension" → select extensions/zed/
```

**Key Points:**

- Extension always points to GitHub repository (no local file:// switching)
- Grammar/query changes must be committed and pushed before testing
- `./scripts/update-zed-rev.sh` updates the rev to current commit and cleans cache
- Simpler workflow eliminates local/remote repository confusion

**Publishing Extensions:**

```bash
# Update Zed extension.toml to reference git repo
# Commit grammar changes first
git commit -am "Update grammar"
git push

# Update rev/commit hash in extension.toml
# Submit to Zed extension registry

# Package VSCode extension
cd extensions/vscode
npm run vscode:prepublish
vsce package
vsce publish
```

## Debugging Syntax Highlighting Issues

When users report highlighting problems, use VSCode's **Token Inspector**:

1. Have user open the problematic `.prem` file
2. Place cursor on the incorrectly highlighted text
3. `Cmd+Shift+P` → "Developer: Inspect Editor Tokens and Scopes"
4. Analyze the token panel to identify issues:
   - **TextMate scopes**: Which patterns are matching (or not)
   - **Semantic token type**: Tree-sitter semantic tokens
   - **Foreground color**: Active theme rules

Common issues and fixes:

- **"No theme selector" / only `source.premise`**: TextMate pattern not matching

  - Check pattern ordering in `syntaxes/premise.tmLanguage.json`
  - Earlier patterns win - move specific patterns before general ones

- **Split token coloring** (e.g., `@adapt` different from `er`):

  - Semantic token conflict with TextMate
  - May need to disable semantic token in `semanticTokens.ts`

- **Wrong color despite correct scope**:

  - Missing theme support - add scope to all theme files
  - Semantic token overriding - check precedence

- **ERROR nodes in parse tree**:
  ```bash
  tree-sitter parse file.prem | grep ERROR
  ```
  - Grammar issue - fix in `grammar.js`

## Key Development Rules

1. **Always validate queries**: Run `./test_queries.sh` after any grammar or query changes
2. **Sync extensions**: Run `./scripts/sync-extensions.sh` after grammar updates
3. **Test locally first**: Use dev extension workflow before publishing
4. **Use example files**: Reference working `.prem` files rather than documenting syntax extensively
5. **Maintain semantic scopes**: These are critical for editor extension functionality
6. **Coordinate releases**: Update extensions after grammar changes are committed
7. **Debug with Token Inspector**: Use VSCode's inspector to diagnose highlighting issues

## New: Entity Block Highlighting – Implementation Notes

Goal: highlight entity names differently from their values inside entity blocks and support nested object values (e.g., `@eras`).

Changes you must preserve:

- Grammar
  - `entity_line` now: `- <entity_name>: <entity_desc | entity_object>`
  - Added nodes: `entity_object`, `object_property`, `prop_key`, `prop_value`
- Queries
  - Capture `(entity_line (entity_name))`, `(entity_line (entity_desc))`
  - Capture `(object_property (prop_key))` and `(prop_value)` for nested objects
- VSCode semantics
  - Map `entity_name` → `variable` (with `readonly` modifier)
  - Map `entity_desc`/`prop_value` → `string`
  - Map `prop_key` → `property`
- TextMate guard
  - Avoid TM rules that apply broad scopes which overshadow semantic tokens
  - We replaced a block `{…}` pattern with a minimal `{[^{}\n]+}` reference rule
- Themes
  - Ensure `"semanticHighlighting": true` and include a color for `property`

Debugging tips:

- Use Developer: Inspect Editor Tokens and Scopes to confirm semantic tokens
- Watch extension host logs for `Found entity_name`/`Found entity_desc` and token counts
- If you see “Semantic token with invalid length”, check for zero-length ranges and clamp
