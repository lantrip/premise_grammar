# Premise Editor Extensions

This directory contains editor extensions that consume the Premise Tree-sitter grammar.

## Directory Structure

- `zed/` - Zed editor extension
- `vscode/` - VSCode extension
- Both extensions share the same grammar artifacts from the root directory

## Development Workflow

### Quick Install (Recommended)

```bash
# From repository root - rebuilds and installs everything
./scripts/dev.sh              # All editors
./scripts/dev.sh vscode       # VSCode only
./scripts/dev.sh cursor       # Cursor only
./scripts/dev.sh zed          # Zed only
```

### Brace Color Looks Wrong? Check Bracket Pair Colorization

- If entity reference braces `{` `}` appear with unexpected colors (e.g., same blue as parentheses), editor-level Bracket Pair Colorization may be overriding theme scopes.
- Fix: Disable for Premise files.
  - We ship a default in the extension to turn it off for `[premise]`, but a user/workspace override can re-enable it.
  - VS Code/Cursor → Settings → search: "Bracket Pair Colorization" → uncheck for Premise or remove overrides in `settings.json`.
  - Premise relies on TextMate scopes `punctuation.definition.entity.*` for subtle brace coloring.

### Manual Steps

#### 1. Build Grammar

```bash
# From repository root
./build.sh
```

#### 2. Sync to Extensions

```bash
# Copy WASM and queries to extensions
./scripts/sync-extensions.sh
```

#### 3. Install Extensions

```bash
# Automated install
./scripts/install-extensions.sh [vscode|cursor|zed|all]

# Or manually:
# Zed: Cmd+Shift+P → "zed: install dev extension" → select extensions/zed
# VSCode/Cursor: Built and installed automatically by script
```

## Production Publishing

### Zed Extension

1. Commit grammar changes to main repository
2. Update `extension.toml` to reference git repository instead of `file://`
3. Submit to Zed extension registry

### VSCode Extension

1. Build and sync extensions
2. Package extension: `vsce package`
3. Publish to marketplace: `vsce publish`

## Development vs Production Configuration

**Development:**

- Zed uses `file://../../` to reference local grammar
- VSCode copies WASM/queries from root directory
- Immediate testing without git commits

**Production:**

- Zed references committed git repository with rev/commit hash
- VSCode bundles pre-built artifacts
- Requires stable, committed grammar changes

## AI Features (Preview)

- VSCode commands:
  - “Premise: Generate Beats…” — adds `///` beats with `{Entity}` references.
  - “Premise: Update Entity Descriptions…” — updates `@entity` lines.
- Scopes: current file, story root, uncommitted (file/root).
- Chunking: per-run picker (section/file) and default setting `premise.ai.chunkingMode`.
- Settings: `premise.ai.provider` (OpenRouter), `premise.ai.model`, `premise.ai.apiKey`, `premise.ai.endpoint`, `premise.ai.beatInsertPosition`, `premise.ai.entityUpdatesChangedOnly`, `premise.ai.rateLimitPerMinute`.
- Notes: Edits apply directly; use VCS to review/commit changes.

### Behavior

- Beats insert at section anchors (Cel > Scene > Act), deduplicated within the section, and entity mentions are validated against canonical names.
- Entity updates are coalesced per file (last description wins). When `premise.ai.entityUpdatesChangedOnly` is true, updates are limited to changed ranges in uncommitted scopes.
- Uncommitted scopes prefer diff hunks; if no hunks intersect sections, the extension falls back to whole-file chunking.
