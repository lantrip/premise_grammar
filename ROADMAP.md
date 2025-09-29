## Premise Roadmap (Combined)

This combined roadmap summarizes AI-assisted editor features and the Premise LSP.

### Highlights (Implemented)

- VSCode AI features:
  - Beat generation with dedupe, insert position (append/prepend), and entity validation
  - Entity description updates with per-file coalescing and changed-ranges-only option
  - Sequential processing with progress/cancel and rate limiting for root scopes
  - Uncommitted scopes: rename/new-file handling and file-level fallback when no hunks intersect sections
- LSP:
  - `workspace/symbol` (basic entity definitions)
  - `workspace/didChangeWatchedFiles` refresh
  - Structure helper returns `uri`, stable `id`, and `entityMentions` (initial)

### In Progress / Planned

- LSP:
  - Refine `collectStructure` section IDs and per-section entity mentions
  - Hover/Completion improvements; optional code actions
- Tests:
  - LSP integration tests for structure and helpers
  - Extension tests for chunking, insertion, changed-only updates, rate limiting
- Packaging & Parity:
  - VSCode bootstrap for server binaries; Zed LSP registration and parity verification
- Observability:
  - Timing logs, counters, and optional verbose trace of prompts (redacted)

For detailed plans, see `AI_ROADMAP.md` (consolidated). The old `LSP_Roadmap.md` is deprecated.
