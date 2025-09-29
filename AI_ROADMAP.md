## Premise AI Roadmap

### Overview

This document outlines how we will extend the Premise extension and LSP with AI-assisted generation and maintenance workflows. The focus is not to have AI write the story for users, but to:

- **Generate Beats**: Propose `///` beat lines for a given treatment/narrative and scope, with entity associations.
- **Update Entity Descriptions**: Suggest updates to `@entity` descriptions based on story changes.

AI calls will be initiated from the editor extension (client-side) and grounded using data provided by the LSP (server-side helpers). Edits are applied directly to the workspace (no extra confirmation UI), appearing as normal file changes for the user to review and commit.

### Initial Provider: OpenRouter

- **Provider**: OpenRouter
- **Model**: user-configurable (examples: `openrouter/anthropic/claude-3.5-sonnet`, `openrouter/openai/gpt-4o-mini`)
- **Endpoint**: `https://openrouter.ai/api/v1/chat/completions`
- **Auth**: API key set by the user in the extension settings or environment

We will keep LLM credentials strictly on the client. The LSP will not make outbound LLM requests or handle secrets.

Note: This roadmap is now the consolidated source of truth for both AI features and the LSP. The older `LSP_Roadmap.md` is retained for history but is superseded by this document.

### User Configuration (Extension Settings)

Add the following settings in the VSCode extension:

- **premise.ai.provider**: `"openrouter"` (default)
- **premise.ai.model**: string, required (e.g., `openrouter/openai/gpt-4o-mini`)
- **premise.ai.apiKey**: string, required for OpenRouter
- **premise.ai.endpoint**: string, defaults to `https://openrouter.ai/api/v1/chat/completions`

- **premise.ai.chunkingMode**: `section` (default) or `file`; controls prompt chunking granularity
- **premise.ai.beatInsertPosition**: `append` (default) or `prepend`; where to place beats within a section
- **premise.ai.entityUpdatesChangedOnly**: boolean; limit entity updates to changed ranges in uncommitted scopes
- **premise.ai.rateLimitPerMinute**: number; sequential requests per minute for root scopes

Environment variable fallbacks (optional):

- `PREMISE_AI_PROVIDER`, `PREMISE_AI_MODEL`, `OPENROUTER_API_KEY`, `PREMISE_AI_ENDPOINT`

Data handling:

- Requests include only the scoped Premise text (file, project, or uncommitted diffs), entity names, and optional treatment; no telemetry by default.

### Editor Commands (Client)

We will add two user-facing commands in the extension:

- **Premise: Generate Beats…** (`premise.generateBeats`)

  - Scope picker: Current file, Story root (project), Uncommitted: current file, Uncommitted: story root
  - Optional: ask for a short treatment/narrative input
  - Calls the LLM and inserts `///` lines directly at the appropriate location. Anchor-based placement uses the nearest Cel/Scene/Act section, preferring changed regions when in uncommitted scope. Beats MUST use curly-braced entity references (e.g., `{Hero}`) and only from the canonical list.

- **Premise: Update Entity Descriptions…** (`premise.updateEntityDescriptions`)
  - Same scopes as above
  - Applies updates to `@entity` descriptions with evidence lines noted in the response
  - Supports per-run chunking override (section/file) with uncommitted-range bias

Implementation note: Both commands run fully on the client and use LSP helpers to gather structure and entity context.

Client-side anchoring and filtering rules:

- Match sections by exact `uri` equality (no substring/path-prefix matching).
- When anchors become stale, degrade gracefully to the nearest header in the same `uri` and surface a warning.

### LSP Helpers (Server)

Add executeCommand entries to expose structure and names without shipping full file-system logic to the client. Extend structure to carry exact `uri`, per-section `entityMentions`, and a stable `id` for durable client anchoring:

- `premise.getStoryRoot(uri) -> { root: string }`
- `premise.listEntityNames(uri) -> string[]`
- `premise.collectStructure(uris: string[]) -> { sections: Section[] }` (includes `uri`, `id`, and `entityMentions`) — STATUS: Implemented (initial; refining IDs/mentions)

`Section` captures hierarchical anchors for robust insertion. `uri` is authoritative for identity; `file` is a convenience alias for display only. `entityMentions` lists canonical entity names detected in the section text. `id` is stable across indexing passes when headings remain unchanged.

```json
{
  "uri": "file:///workspace/story/scene1.prem",
  "file": "story/scene1.prem",
  "id": "act-one/opening-scene/heros-introduction",
  "act": "Act One",
  "scene": "Opening Scene",
  "cel": "Hero's Introduction",
  "range": {
    "start": { "line": 10, "character": 0 },
    "end": { "line": 40, "character": 0 }
  },
  "entityMentions": ["Hero", "Castle"]
}
```

### Scopes

- **Current file**: Active `.prem` document.
- **Story root**: Files under the nearest directory containing `story/` (server resolves this).
- **Uncommitted: current file**: Changed hunks only (parse `git diff -U0 -- file`).
  - STATUS: Implemented in extension for both beats and entity-description commands.
- **Uncommitted: story root**: Changed hunks across `.prem` files under the story root.
  - STATUS: Implemented in extension (diff-based file list and per-file anchored insertion)

If `git` is unavailable, fall back to the full-file scope for that option.

Uncommitted scope robustness:

- Handle file renames and newly created files when parsing hunks. STATUS: Implemented
- If no hunks intersect any section in a file, fall back to file-level chunking for that file. STATUS: Implemented

### Chunking Strategy

- Modes: `section` (Cel/Scene/Act) or `file`.
- Per-run override: command shows a quick pick to choose chunking (defaults to setting).
- Section mode iterates sections in order; File mode sends full file. Both respect uncommitted ranges when provided.

### Processing Controls

- Sequential processing for root scopes with progress notifications and cancel support (default concurrency = 1).
- Rate-limit requests per minute; both values are user-configurable settings.

### LLM Prompts (Grounded)

Each request includes:

- Scope descriptor (file paths, story root, and/or hunks)
- Structured section map (Acts/Scenes/Cels) from `collectStructure`
- Canonical entity names from `listEntityNames`
- Optional user-provided treatment/narrative

We constrain outputs to strict JSON to avoid ambiguity. For beats, the prompt requires entity mentions to be wrapped in curly braces and to use only known entities.

When available, include `era` and `location` metadata to ground descriptions thematically and align updates with the meta associated to the location and era.

### Response Schemas

Beats generation:

```json
{
  "beats": [
    {
      "anchor": {
        "file": "story/scene1.prem",
        "scene": "Opening Scene",
        "cel": "Hero's Introduction"
      },
      "insertMode": "append",
      "beat": "Hero notices the broken seal on the door.",
      "entities": ["Hero", "Castle", "Sword"]
    }
  ]
}
```

Entity description updates:

```json
{
  "entities": [
    {
      "name": "Hero",
      "description": "A brave adventurer now burdened by a prophecy revealed in Act One.",
      "evidence": ["story/scene1.prem:12-16"]
    }
  ]
}
```

### Applying Edits

- Beats: Insert `/// <text>` at the end or start of the targeted section (anchor-based), preserving existing content and formatting.
  - Default insert position: end of section (`insertMode = "append"`). Provide a setting/override to place at the top.
  - Deduplicate within a section: do not re-insert the same normalized beat line.
  - Post-insert validation: verify `{Entity}` tokens exist in the canonical list; drop or flag beats with unknown entities.
- Entity descriptions: Locate `@entity` definitions (using index or AST), replace only the description portion; show a diff preview.
  - Coalesce multiple updates per entity per file into one final description.
  - Optional setting: only update entities referenced in the changed ranges for uncommitted scopes.
- If anchors are stale, degrade gracefully by placing near the closest header in the same file and surfacing a warning.

### Error Handling & Guardrails

- Reject entities not present in the canonical list unless the user opts in to create them.
- Limit payload size by chunking by Scene/Cel; stream or paginate results when needed.
- Provide a dry-run preview with per-edit checkboxes; nothing is applied automatically.

Quality guardrails (planned):

- Beat deduplication and post-insert entity validation as described above.
- Unknown-entity references are dropped by default; optionally surface a quick-fix to create missing entities.

### Milestones

1. Client scaffolding

- Add extension settings (`premise.ai.*`), read env fallbacks
- Add commands: `premise.generateBeats`, `premise.updateEntityDescriptions`
- Implement OpenRouter client wrapper (POST `chat/completions`), parse JSON
  - STATUS: Implemented for current-file scope; settings, commands, and direct-apply edits are in place.

2. Server helpers

- Implement `premise.getStoryRoot`, `premise.listEntityNames`, `premise.collectStructure`
  - STATUS: Implemented minimal versions (entity names, structure from IR, story root path).
  - Next: include exact `uri`, per-section `entityMentions`, and stable section `id`.

3. Scope handling

- Implement git hunk parsing for uncommitted modes
- Fallback to full-file when git missing
  - STATUS: Implemented; falls back to full-file when git is unavailable.
  - Next: handle renames/new files; file-level fallback when hunks do not intersect sections.

4. Edit application

- Anchor resolution and insert/update logic
  - STATUS: Beats now placed by section anchors (Cel > Scene > Act) and biased to changed hunks.
  - Next: within-section deduplication; insert-position override; post-insert entity validation; coalesce entity updates.
- Unified diff preview and apply with `WorkspaceEdit`
  - STATUS: Not planned; we apply directly and rely on normal VCS review flow.

5. QA and hardening

- Smoke tests on `test-lsp-smoke/`
- Latency guardrails (<800ms indexed fetch; LLM latency excluded)
- Unknown-entity detection and user prompts
  - STATUS: Pending

6. LSP enhancements

- Implement `workspace/symbol` for project-wide symbol search. STATUS: Implemented (basic entity definitions)
- Add `workspace/didChangeWatchedFiles` to auto-refresh index on file changes. STATUS: Implemented
- Extend `collectStructure` with `uri`, `id`, and per-section `entityMentions`. STATUS: In progress

#### LSP (Consolidated Overview)

- Priorities: diagnostics, document symbols, definition/references, hover, completion; optional code actions/rename.
- Delivered: server skeleton; diagnostics; story hierarchy symbols; cross-file defs/refs via index; completion for entity names.
- Recent: `workspace/symbol` (basic); `didChangeWatchedFiles` refresh; structure helpers used by AI anchoring.
- Next: refine section IDs/entity mentions; hover/completion quality; packaging bootstrap; Zed parity.

### Acceptance Criteria (Phase 1)

- Users can configure OpenRouter API key and model in settings.
- `Premise: Generate Beats…` proposes `///` beat insertions for the chosen scope; preview shows anchors and entity associations.
- `Premise: Update Entity Descriptions…` proposes precise `@entity` description diffs with evidence.
- All edits are opt-in, idempotent, and validated by the existing LSP on apply.

### Future Enhancements

- Provider abstraction for local models or other APIs.
- Inline quick-fixes to accept/reject single edits directly in diff view.
- Entity alias mapping and adapter-driven normalization.
- Project-wide consistency checks (entity drift, unused entities, conflicting beats).

### Upcoming and In-Progress Work

- **Grounding improvements**:

  - Extend `collectStructure` to return exact `uri`, stable `id`, and `entityMentions` per section. STATUS: In progress
  - Update client filtering to match by `uri` equality, not string contains. STATUS: Implemented

- **Beat insertion quality**:

  - Deduplicate beats within a section to avoid re-inserting the same line. STATUS: Implemented
  - Insert position option (top vs end); default end. STATUS: Implemented
  - Validate `{Entity}` references post-insert (drop/flag unknown). STATUS: Implemented

- **Entity updates quality**:

  - Coalesce multiple updates targeting the same entity into one final description per file. STATUS: Implemented
  - Optional setting to only update entities referenced in changed ranges. STATUS: Implemented
  - Incorporate era/location metadata to guide thematic updates. STATUS: Planned

- **Chunking/processing controls**:

  - Sequential processing with progress notifications and cancel for root scopes. STATUS: Implemented
  - Rate-limit requests per minute; configurable concurrency (default 1). STATUS: Implemented

- **Robust uncommitted scopes**:

  - Handle renames and newly created files in hunk parsing. STATUS: Implemented
  - Fall back to file-level chunking when no hunks match any section. STATUS: Implemented

- **LSP enhancements**:

  - Implement `workspace/symbol` and `workspace/didChangeWatchedFiles`. STATUS: Planned
  - Include per-section `entityMentions` and stable IDs in `collectStructure`. STATUS: In progress

- **Tests**:

  - LSP integration tests for `getStoryRoot`, `listEntityNames`, `collectStructure`. STATUS: Planned
  - VS Code extension tests scaffolded (mocha + @vscode/test-electron). STATUS: In progress

- **Packaging and parity**:

  - VSCode: bootstrap to download server binaries if missing. STATUS: Planned
  - Zed: register LSP command and confirm parity (diagnostics, symbols, defs/refs, hover, completion, helpers). STATUS: Planned

- **Observability**:

  - Add timing logs and counts (beats inserted, entities updated). STATUS: Planned
  - User setting to enable verbose trace for prompts (redact API key). STATUS: Planned

- **Documentation**:
  - Add “How to use AI features” to `extensions/vscode/README` with GIFs. STATUS: Planned
  - Update this roadmap after each milestone with acceptance criteria and known issues. STATUS: Planned
