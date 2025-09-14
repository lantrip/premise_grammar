# Cuneiform Tree-sitter Grammar (Single Source of Truth)

This is the canonical source for the Cuneiform language grammar and editor support. Both VSCode/Cursor and other editors consume this grammar to provide consistent language features.

## What's in here

- `grammar.js`: Tree-sitter grammar definition (authoritative source)
- `queries/`: Editor queries shared across IDEs
  - `highlights.scm`: Syntax highlighting captures
  - `indents.scm`: Indentation behavior  
  - `outline.scm`: Symbols/outline
  - `brackets.scm`: Bracket/brace matching
- `src/`: Generated parser artifacts (C code, JSON definitions)
- `tree-sitter-cuneiform.wasm`: Web build of the parser (for VSCode/web)
- `build.sh`: Build script for generating parser and WASM

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

### 3. Test Grammar

```bash
npx tree-sitter test          # Run test corpus
npx tree-sitter parse example.cune  # Test on a file
```

### 4. Update VSCode Extension

```bash
cd ../vscode
./build-install.sh            # Rebuilds and installs to VSCode/Cursor
```

### 5. Reload Editor

Restart your editor or run "Developer: Reload Window" to see changes.

## Grammar Features (v0.2.0)

The grammar supports all Cuneiform syntax elements:

### ✅ Working Features

#### Entity Blocks
- **Block definitions**: `@characters { ... }` with arbitrary content
- **Nested blocks**: `@eras { ... }` within entities using balanced braces algorithm
- **Multi-line content**: Properly handles newlines and indentation within blocks

#### Nested Structure Support (NEW!)
- **Balanced braces**: Recursive parsing of nested `{ ... }` patterns
- **Real-world tested**: Successfully parses `habitatable/world_with_inline_eras.cune`
- **No conflicts**: Resolved parsing ambiguities between top-level and nested blocks

### 🚧 In Progress

#### Structure
- **Headers**: `= Act`, `== Scene`, `=== Cel with location`
- **File headers**: `TITLE:`, `WORLD:`, `TEMPLATE:`, etc.

#### Entities
- **Inline definitions**: `@character Hero: A brave adventurer` (parsing issues)
- **Entity references**: `{Hero}` in content

#### Content Types
- `///` - Beats (structural story beats)
- `//` - Treatments (scene direction and mood)
- `/` - Narrative (final story text)

### Imports & Adapters
- **Imports**: `@import "file.yaml" #selector`
- **Adapters**: `@adapter "adapter.yaml" @timing:pre`

### Metadata
- **Properties**: `@structure_mode: hierarchical`
- **Comments**: `# This is a comment`

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

### Test Suite

Run the comprehensive test suite:

```bash
# Run all grammar tests
./test_runner.sh

# Test individual files
tree-sitter parse test_cases/02_entity_blocks.cune
tree-sitter parse test_cases/03_nested_blocks.cune

# Test with real-world examples
tree-sitter parse ../../examples/habitatable/world_with_inline_eras.cune
```

### Current Test Status (2/6 passing)

| Test File | Status | Description |
|-----------|--------|-------------|
| `01_entity_definitions.cune` | ❌ Failed | Entity definitions need fixing |
| `02_entity_blocks.cune` | ✅ Passed | Basic entity blocks work |
| `03_nested_blocks.cune` | ✅ Passed | Nested @eras blocks work! |
| `04_story_structure.cune` | ❌ Failed | Headers not yet implemented |
| `05_imports_and_metadata.cune` | ❌ Failed | Import/adapter syntax pending |
| `world_with_inline_eras.cune` | ❌ Failed | Full file has additional syntax |

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
