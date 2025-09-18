# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Tree-sitter grammar for the Cuneiform language - a domain-specific language for story authoring that supports hierarchical content organization (acts/scenes/cels), entity definitions, screenplay-style dialogue, content typing, and metadata.

**Core Responsibility**: This repository is the **foundational layer** for all Cuneiform editor support, providing:
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

## Cuneiform Language Syntax

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
- `examples/` - Reference files including `theming_showcase.cune` for theme development
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

- Use `examples/theming_showcase.cune` for comprehensive syntax testing
- Reference `.cune` files in `examples/` rather than trying to document every syntax pattern
- All major language features are demonstrated in working example files
- Parse examples with `tree-sitter parse examples/file.cune` to understand structure

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

## Key Development Rules

1. **Always validate queries**: Run `./test_queries.sh` after any grammar or query changes
2. **Sync extensions**: Run `./scripts/sync-extensions.sh` after grammar updates
3. **Test locally first**: Use dev extension workflow before publishing
4. **Use example files**: Reference working `.cune` files rather than documenting syntax extensively
5. **Maintain semantic scopes**: These are critical for editor extension functionality
6. **Coordinate releases**: Update extensions after grammar changes are committed