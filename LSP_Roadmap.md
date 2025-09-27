# Premise LSP Roadmap

This roadmap tracks the incremental implementation of a Language Server for Premise. It leverages `premise-core` for parsing, symbols, imports, and validation, and serves VSCode/Cursor and Zed via standard LSP.

## Scope Priorities

- Diagnostics from `premise_core::validate`
- Document symbols (entities/imports/metadata)
- Definition/References (start intra-file, then cross-file)
- Hover and Completion
- Story-root–scoped resolution for `local.@` references

## Story Root Semantics (local.@)

- Definition: story root is the nearest ancestor directory containing `story/` (or itself named `story`).
- Resolution scope: current file, then other files within the story root and its ancestors up to workspace root.
- Behavior: `local.@Name` resolves only within that scope. Configurable via `premise.localScope = storyRoot`.

## Phases

### Phase 0 — Server Skeleton

- Create Rust crate `premise-lsp` using `tower-lsp`.
- Implement initialize/shutdown; advertise capabilities (`textDocumentSync`, `documentSymbol`, `definition`, `references`, `hover`, `completion`).
- Maintain WorldState: uri → { text, version, ast, symbols, imports }.

### Phase 1 — Diagnostics

- On open/change, parse and run `premise_core::validate`.
- Publish `textDocument/publishDiagnostics` with mapped ranges.

### Phase 2 — Document Symbols

- Use `premise_core::symbols` to produce hierarchical `DocumentSymbol`s:
  - Entities, Imports, Metadata (and adapters if helpful).

### Phase 3 — Intra-file Def/Refs

- Hit-test cursor within `entity_reference` nodes.
- Map to nearest matching entity in the same file via `SymbolTable`.
- Implement `textDocument/definition` and `textDocument/references`.

### Phase 4 — Story Root + local.@

- Detect story root (nearest ancestor with `story/`).
- Parse `local.@` tokens; resolve against an index of entities within story root scope.
- Implement cross-file def/refs consistent with local scope rules.

### Phase 5 — Workspace Index

- Index entities across `.prem` files within workspace folders.
- Maintain import graph and invalidate incrementally.
- Provide `workspace/symbol` for quick symbol lookup.

### Phase 6 — Hover

- Entities: show definition snippet, file path, metadata.
- Imports: show resolved path and existence diagnostics.

### Phase 7 — Completion

- In `entity_reference` contexts, suggest entities from scope.
- For `local.@`, offer entity names valid within story root scope.

### Phase 8 — Code Actions (Optional)

- Quick-fix: create missing entity, add import, deduplicate entity.

### Phase 9 — Rename (Optional)

- Symbol-aware rename across files with validation.

## Editor Integration

### VSCode / Cursor

- Add language client (`vscode-languageclient`) in `extensions/vscode`.
- Spawn LSP server via stdio; keep existing Tree-sitter highlighting.
- Multi-root support; file watching for `.prem`.
- Packaging: bundle or download platform binaries (macOS arm/x64, Linux x64, Windows x64).

### Zed

- Register LSP command in `extensions/zed/extension.toml` for `premise`.
- Ensure server binary is on PATH or packaged; keep existing grammars for syntax.

## Performance & Reliability

- Debounce `didChange`; reuse long-lived parser instances.
- Background indexing with throttling; progress reporting.
- Robust path/URI handling; tolerate missing files.

## Testing

- Use `test-lsp-story/` as fixtures for def/refs, hover, completion.
- Add golden tests for diagnostics and symbol lists.

---

## Progress (to date)

- Server: scaffolded `premise-lsp` (tower-lsp); text sync; diagnostics; document symbols re-enabled; logs routed to stderr; request tracing added in handlers.
- Navigation: intra-file hover/definition/references working for entity names; cross-file resolution currently not returning results; `local.@Name` path recognized but needs grammar-aligned handling.
- VSCode/Cursor: language client integrated; server starts via stdio; server binary packaged inside the extension; dedicated Output and Trace channels; `RUST_LOG` forwarded; syntax/semantic tokens preserved.
- Zed: grammar/themes working; LSP command registration still pending.

## Next Steps

- Cross-file defs/refs: fix reconciliation path. Verify story-root detection and fallback scan scope; normalize names consistently; add targeted tests in `test-lsp-story/`.
- `local.@` semantics: align tokenization with grammar (ensure the prefix is captured/normalized), then plumb through resolvers; add end-to-end tests.
- Workspace entity index: background build of entity map for fast cross-file navigation; expose `workspace/symbol` backed by the index.
- Hover: include short definition snippet and path relative to story root; for imports, show resolved path/existence.
- Completion: entity suggestions in reference contexts; smart `local.@` completions from story-root index.
- VSCode/Cursor: keep Output/Trace channels; optionally add setting to control server verbosity.
- Zed integration: register LSP command in `extensions/zed/extension.toml` and verify parity.
- Packaging: optional bootstrap to download per-OS server binaries when missing.

### Known issues (as of 2025-09-27)

- Cross-file goto-definition/references not returning results yet.
- `local.@` references parse but aren’t resolving consistently with grammar rules.
- LSP warns about unimplemented notifications (`didSave`, `workspace/didChangeWatchedFiles`) — low priority for now.

## Notes for Next Implementer

- Story root detection: nearest ancestor containing a `story/` directory; fallback to current file directory.
- Cross-file scan currently uses `walkdir` on every request; replace with cached index keyed by file mtime and workspace roots.
- Keep `premise_core::Parser` instances reused per-thread if you add indexing workers to avoid reinitialization costs.
- For multi-root workspaces, prefer the root containing the current file when building the search scope.
- The VSCode client allows overriding server path via `PREMISE_LSP_PATH` env var.

## Testing Strategy (initial)

- Manual smoke: open files in the new `test-lsp-smoke/` project; verify diagnostics, symbols, goto-definition/references (including `local.@`).
- Scenario tests (Rust): add a test harness that spins the LSP in-process and runs LSP requests against in-memory documents (e.g., using `tower_lsp::LspService` directly) to validate definition/ref/hover.
- Golden outputs: add CLI-based checks via `premise-core` binaries for `parse`, `validate`, and symbol lists against fixture files.
- Performance guardrails: seed a larger folder and measure first-response latency; target <200ms for intra-file, <800ms for cross-file before indexing; enforce via bench tests later.

## Next Agent Handoff — Concrete Steps

1. Build a workspace entity index (replace walkdir scans)

- Add `index.rs` in `premise-lsp` maintaining:
  - `name -> Vec<Location>` for entity definitions (and optionally references)
  - `path -> { mtime, entities }` for incremental updates
  - `roots: Vec<PathBuf>` from `initialize.workspace_folders` and current file’s root
- Implement file watchers: on `didOpen/didChange/didClose`, re-index that file; add a throttled background scan of roots on `initialized`.
- Expose async helpers: `index.get_defs(name)`, `index.list_entity_names(scope)`, `index.get_refs(name)`.
- Wire `gotoDefinition`/`references`/`completion` to the index; keep walkdir as cold-start fallback.

2. Implement `workspace/symbol`

- Return top-N matches from the index with fuzzy prefix matching.
- Optionally implement `workspaceSymbol/resolve` if you want extra details.

3. Hover improvements

- Show a short snippet from the definition line(s) and a path relative to the story root.
- For imports, show resolved path and existence (reuse `premise_core::resolve_imports_with_base`).

4. Completion improvements

- Context-aware filtering in `entity_reference` and `dialogue_speaker` nodes.
- Commit characters (`}`) and preselect best match; sort by proximity (same file > same folder > story root).

5. Tests (scaffold now)

- In `premise-lsp/tests/`, add integration-style tests that:
  - Spin up `LspService` in-process with a fake client
  - Send `initialize`, `initialized`, `didOpen` with contents from `test-lsp-smoke/`
  - Assert `textDocument/definition`, `references`, `hover`, and `completion` match expectations
- Add CLI sanity tests using `premise-core` outputs for parse/validate/symbols.

6. VSCode packaging

- Add a postinstall script to build/copy the Rust binary into `extensions/vscode/server/` for dev.
- For releases, plan a bootstrap that downloads platform binaries from GitHub Releases on first run.

7. Zed integration

- Update `extensions/zed/extension.toml` to register an LSP command pointing at the built binary.
- Verify features parity (diagnostics, symbols, defs/refs, hover, completion).

8. Configuration

- Add `premise.localScope` (default: `storyRoot`), `premise.indexing.enabled`, and `premise.trace.server` to server settings.
- Contribute settings in VSCode `package.json` and read them via `workspace/didChangeConfiguration`.

9. Observability & performance

- Add structured logs via `tracing`; document enabling with `RUST_LOG`.
- Time key operations; log slow paths; add counters for index size and latency.

10. Manual verification (quick smoke)

- Build server:

```bash
cargo build -p premise-lsp
```

- Point VSCode client:

```bash
export PREMISE_LSP_PATH="$(pwd)/premise-lsp/target/debug/premise-lsp"
```

- Compile VSCode extension and open the smoke project:

```bash
cd extensions/vscode && npm run compile
code ../../test-lsp-smoke
```

- In `test-lsp-smoke/story/scene1.prem`:
  - Hover on `{local.@Keeper Aldrich}` shows definition path
  - Go to definition jumps to `characters_locations.prem`
  - References highlights usages across files
  - Completion suggests `local.@Keeper Aldrich` and `local.@Burned District`

Acceptance criteria for this phase

- Cross-file defs/refs/hover/completion are index-backed and <250ms after warm-up.
- `workspace/symbol` returns entities from the story root.
- VSCode and Zed both start the server and show diagnostics/symbols/defs/refs/hover/completion.
