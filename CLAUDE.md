# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Tree-sitter grammar for the Cuneiform language - a domain-specific language for screenwriting that supports hierarchical content organization (acts/scenes/cels), entity definitions, content typing, and metadata.

## Development Commands

### Grammar Development
- `tree-sitter generate` - Generate parser from grammar.js
- `tree-sitter test` - Run parser tests
- `tree-sitter parse <file>` - Parse a file and show syntax tree
- `tree-sitter highlight <file>` - Apply syntax highlighting to a file

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