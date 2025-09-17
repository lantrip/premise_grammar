# Cuneiform Tree-sitter Grammar (Single Source of Truth)

This is the canonical source for the Cuneiform language grammar and editor support. Both VSCode/Cursor and other editors consume this grammar to provide consistent language features.

## What's in here

- `grammar.js`: Tree-sitter grammar definition (authoritative source)
- `queries/`: Editor queries shared across IDEs
  - `highlights.scm`: **Story-focused semantic scopes** for theming
  - `indents.scm`: Indentation behavior
  - `outline.scm`: Symbols/outline
  - `brackets.scm`: Bracket/brace matching
- `scripts/`: Validation and testing utilities
  - `validate_scopes.py`: Semantic scope validation and coverage analysis
- `examples/`: Reference implementations and showcases
  - `theming_showcase.cune`: Demonstrates all semantic scopes for theme development
- `src/`: Generated parser artifacts (C code, JSON definitions)
- `tree-sitter-cuneiform.wasm`: Web build of the parser (for VSCode/web)
- `build.sh`: Build script for generating parser and WASM
- `test_queries.sh`: Enhanced validation tool with scope checking
- `SEMANTIC_SCOPES.md`: Complete documentation of all semantic scopes

## Development Workflow

### 1. Edit Grammar

Make changes to `grammar.js` and/or query files in `queries/`.

### 2. Build Grammar

```bash
# Quick build with the build script
./build.sh

# Or manually:
npx tree-sitter generate      # Generate parser from grammar.js
npx tree-sitter build --wasm   # Build WASM for VSCode
```

### 3. Test Grammar & Queries

```bash
npx tree-sitter test          # Run test corpus
npx tree-sitter parse example.cune  # Test on a file

# Test all query files with scope validation (recommended)
./test_queries.sh             # Validates highlights, brackets, and semantic scopes

# Validate semantic scopes independently
python3 scripts/validate_scopes.py  # Check scope coverage and conventions

# Test theming with showcase file
npx tree-sitter highlight examples/theming_showcase.cune
```

### 4. Update VSCode Extension

```bash
cd ../vscode
./build-install.sh            # Rebuilds and installs to VSCode/Cursor
```

### 5. Reload Editor

Restart your editor or run "Developer: Reload Window" to see changes.

## Semantic Scopes for Story Authors

The grammar provides **story-focused semantic scopes** that enable rich theming for different writing workflows. These scopes are defined in `queries/highlights.scm` and consumed by editor extensions.

### Core Story Structure Scopes
- `markup.heading.1.story.act` - Act headers (`= Act One`)
- `markup.heading.2.story.scene` - Scene headers (`== Opening Scene`)
- `markup.heading.3.story.cel` - Cel headers (`=== Hero's Introduction`)

### Content Type Scopes
- `keyword.control.content.beat` - Beat markers (`///`)
- `keyword.control.content.treatment` - Treatment markers (`//`)
- `keyword.control.content.narrative` - Narrative markers (`/`)

### Author vs Story Content
- `comment.line` - Author notes (`# comments`)
- `text.narrative` - Story prose and dialogue
- `text.parenthetical` - Action directions
- `entity.name.reference` - Character/location references (`{Hero}`)

### Theme Integration
These semantic scopes enable:
- **Story author themes** optimized for screenplay, novel, or general writing
- **Content layer distinction** between planning (beats) and final text (narrative)
- **Visual hierarchy** with acts > scenes > cels
- **Clear separation** between author notes and story content

Extensions use these scopes to provide themes like "Cuneiform Screenplay" (Courier fonts, script colors) or "Cuneiform Novel" (serif fonts, prose-optimized colors).

## Grammar Features (v1.0 - Production Ready)

The grammar successfully supports all major Cuneiform syntax elements:

### ✅ Fully Working Features

#### Story Structure
- **Headers**: `= Act`, `== Scene`, `=== Cel with location/time`
- **File headers**: `TITLE:`, `WORLD:`, `FORMAT:`, etc.
- **Content hierarchy**: Acts → Scenes → Cels organization

#### Screenplay-Style Dialogue
- **Character speakers**: `{Hero}` as dialogue speaker names
- **Indented dialogue**: Clean dialogue without quotes
- **Parentheticals**: `(whispering)` action directions
- **Mixed content**: Seamless integration of dialogue and prose

#### Entity System
- **Definitions**: `@character Hero`, `@location Castle`, etc.
- **Block definitions**: `@characters { ... }` with arbitrary content
- **Nested blocks**: `@eras { ... }` within entities using balanced braces algorithm
- **Entity references**: `{Hero}` in content with semantic highlighting

#### Content Types
- `///` - Beats (structural story beats)
- `//` - Treatments (scene direction and mood)
- `/` - Narrative (final story text)

#### Imports & Adapters
- **Imports**: `@import "file.yaml" #selector`
- **Adapters**: `@adapter "adapter.yaml" @timing:pre`

#### Metadata & Comments
- **Metadata**: `+key: value` pairs (note: `+` prefix)
- **Comments**: `# This is a comment`

### 🟡 Minor Edge Cases (Production Ready)
- 16 minor parsing errors in comprehensive test files
- All core features work reliably
- Fallback highlighting handles edge cases gracefully
- See `PARSING_STATUS.md` for detailed status

## Integration Points

### VSCode/Cursor Extension

The VSCode extension (`../vscode/`) uses this grammar to provide:
- Syntax highlighting via semantic tokens
- Document outline and symbols
- Hover information for entities
- Go-to-definition for entity references
- Code folding for blocks

### Zed Extension  

For Zed editor integration, reference this grammar directly from the extension manifest.

### Web Playground

The WASM build can be used in web applications for browser-based Cuneiform editing.

## Testing

### Grammar & Query Validation

Run the comprehensive test suite:

```bash
# Validate all queries against grammar (recommended first step)
./test_queries.sh

# Run all grammar tests
./test_runner.sh

# Test individual files
tree-sitter parse test_cases/02_entity_blocks.cune
tree-sitter parse test_cases/03_nested_blocks.cune

# Test with real-world examples
tree-sitter parse ../../examples/habitatable/world_with_inline_eras.cune
```

### Query Validation (`test_queries.sh`)

This script validates that all editor queries work with the current grammar:
- Tests `highlights.scm` semantic scopes against actual parse nodes
- Validates `brackets.scm`, `indents.scm`, and `outline.scm`
- Discovers available node types for debugging
- **Must pass before updating extensions** to avoid editor errors

### Grammar Status Summary

✅ **Production Ready**: All core features work reliably
- Story structure (acts/scenes/cels) ✅
- Screenplay-style dialogue ✅
- Entity system with references ✅
- Content types (beats/treatment/narrative) ✅
- File headers and metadata ✅
- Import/adapter statements ✅

🟡 **Minor Edge Cases**: 16 parsing errors in comprehensive test files
- All handled gracefully with fallback highlighting
- Do not affect practical story writing usage
- Detailed status in `PARSING_STATUS.md`

### Tree-sitter Commands

```bash
# Run all tests
npx tree-sitter test

# Test specific file
npx tree-sitter parse test.cune

# Generate test expectations
npx tree-sitter test -u
```

## Extracting to Separate Repository

When ready to make this a standalone package:

1. **Copy this directory** to a new repository
2. **Initialize as npm package**: 
   ```bash
   npm init
   npm install --save-dev tree-sitter-cli
   ```
3. **Set up CI/CD** for automated builds
4. **Publish to npm** as `tree-sitter-cuneiform`
5. **Update consumers** to reference the npm package

## Files to Keep in Sync

When making changes, ensure these stay aligned:
- `grammar.js` - Core grammar definition
- `queries/*.scm` - Query files for editor features
- `../vscode/extension.js` - VSCode patterns should match grammar
- Test corpus - Keep tests up to date with new features

## Semantic Scopes for Theming

The Cuneiform grammar provides rich semantic scopes designed specifically for story-focused theming. This enables theme authors to create specialized color schemes that highlight different narrative elements.

### Key Semantic Categories

- **Story Structure**: `markup.heading.*.story.*` - Act, scene, and cel headers
- **Content Types**: `keyword.control.content.*` - Beat, treatment, narrative markers
- **Entity References**: `entity.name.*` - Characters, locations, items in story text
- **Dialogue**: `entity.name.character.speaker`, `text.parenthetical` - Screenplay-style dialogue

### Testing Your Theme

Use the provided showcase file to test all semantic scopes:

```bash
# View with syntax highlighting
npx tree-sitter highlight examples/theming_showcase.cune

# Validate scopes are working
python3 scripts/validate_scopes.py
```

### Documentation

See [SEMANTIC_SCOPES.md](SEMANTIC_SCOPES.md) for complete documentation of all scopes, theming integration examples, and contribution guidelines.

## Technical Implementation

### Balanced Braces Algorithm (v0.2.0)

The key innovation in this version is the balanced braces approach for handling nested blocks:

```javascript
// Entity blocks can contain nested { ... } patterns
entity_block: ($) =>
  seq(
    "@", field("block_type", /\w+/), /\s*/, "{",
    repeat(choice(
      $.balanced_braces,  // Handles nested @eras { ... }
      /[^{}]+/,          // Regular content
      $.newline
    )),
    "}"
  ),

// Recursive rule for balanced braces
balanced_braces: ($) =>
  seq(
    "{",
    repeat(choice(
      $.balanced_braces,  // Recursive for deeper nesting
      /[^{}]+/,
      $.newline
    )),
    "}"
  )
```

This solves the fundamental parsing conflict where `@eras {` inside `@characters {` was being interpreted as a new top-level entity block.

## Common Issues

### WASM not updating
- Ensure you run `tree-sitter build --wasm` after grammar changes
- Clear VSCode extension cache if needed

### Highlighting not working
- Check `queries/highlights.scm` for proper captures
- Verify semantic token mapping in VSCode extension

### Parser conflicts
- Run `tree-sitter generate` to see conflict warnings
- Adjust rule precedence in `grammar.js` as needed

### Nested blocks not parsing
- Fixed in v0.2.0 with balanced braces algorithm
- Ensure you're using the latest grammar build

## Contributing

1. Make changes only in this directory (not in individual editor extensions)
2. Run tests to ensure nothing breaks
3. Build both parser and WASM
4. Test in VSCode extension before committing
5. Document any new syntax features in this README# Updated Sun Sep 14 10:24:53 EDT 2025
