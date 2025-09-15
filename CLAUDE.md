# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Tree-sitter grammar for the Cuneiform language - a domain-specific language for story authoring that supports hierarchical content organization (acts/scenes/cels), entity definitions, content typing, and metadata.

**Core Responsibility**: This repository is the **foundational layer** for all Cuneiform editor support, providing:
- Grammar definition (`grammar.js`)
- **Story-focused semantic scopes** (`queries/highlights.scm`) that enable rich theming
- Editor queries for syntax highlighting, indentation, and navigation
- Validation tools to ensure query compatibility

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

## Architecture

### Core Grammar (grammar.js)
The grammar defines syntax rules for Cuneiform language elements:
- **Hierarchical Headers**: Acts (`=`), Scenes (`==`), Cels (`===`) with optional percentage markers
- **Content Types**: Beat (`///`), Treatment (`//`), Narrative (`/`) prefixes
- **Entity System**: Definitions (`@entity Name`) and blocks (`@entities { }`)
- **Imports/Adapters**: `@import` statements and `@adapter` configurations
- **Metadata**: `@key: value` pairs
- **Comments**: `#` prefixed lines

### Generated Files
- `src/parser.c` - Generated C parser (do not edit)
- `src/grammar.json` - JSON representation of grammar rules
- `src/node-types.json` - Node type definitions for language bindings

### Bindings Structure
- `bindings/node/` - Node.js binding with fallback loading logic
- `bindings/rust/` - Rust crate with language function and tests
- Query files in `queries/` for syntax highlighting and editor features

### Grammar Rules Organization
Rules follow Tree-sitter conventions with `$` references and use regex patterns for content matching. The grammar prioritizes prose content while providing structure for screenplay elements.

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