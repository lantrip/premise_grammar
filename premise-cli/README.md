## Premise CLI

The Premise CLI binary is `premise` (crate `premise`). It replaces the old stub in `premise-core`.

### Build

```bash
cargo build -p premise
```

### Usage (highlights)

Notes pipeline:

```bash
# Initialize notes in a story root
premise notes init ./my-story --title "My Story"

# Premise inputs
premise notes export-beats my-story/story.prem --sink notes --stable-ids
premise notes extract-facts my-story/story.prem --sink notes --stable-ids

# Markdown inputs (heuristic)
premise notes export-beats my-story/novel.md --input markdown --extractor heuristic --sink notes --stable-ids
premise notes extract-facts my-story/novel.md --input markdown --extractor heuristic --sink notes --stable-ids

# Markdown inputs (LLM)
premise notes export-beats my-story/novel.md --input markdown --extractor llm --llm-cache read-only --sink notes --stable-ids
premise notes extract-facts my-story/novel.md --input markdown --extractor llm --min-confidence 0.6 --llm-cache read-only --sink notes --stable-ids
```

### AI configuration precedence

`AiConfig` is auto-loaded with precedence:

1. Explicit path (if used by API)
2. Project: `<story_root>/.premise-notes/ai.json`
3. User: `~/.config/premise/ai.json` (on macOS/Linux)
4. Defaults (OpenRouter endpoint/model)

Example `ai.json`:

```json
{
  "provider": "openrouter",
  "endpoint": "https://openrouter.ai/api/v1/chat/completions",
  "model": "openai/gpt-4o-mini",
  "api_key_env": "OPENROUTER_API_KEY",
  "temperature": 0.2,
  "max_tokens": 1000
}
```

### LLM record/replay cache

Use `--llm-cache` with `off|read-only|read-write` to control record/replay under `.premise-notes/.llm_sessions/`.

In CI, prefer `read-only` to avoid network and ensure determinism.

## LLM overrides and precedence

The Notes commands for text extraction support LLM overrides:

- `--llm-provider` (e.g., openrouter, noop)
- `--model`
- `--endpoint`
- `--api-key-env`
- `--temperature`
- `--max-tokens`
- `--llm-replay` (alias for `--llm-cache`: off|read-only|read-write)

Precedence when resolving AI config:

1. CLI flags (highest)
2. Project config: `.premise-notes/ai.json`
3. User config: `~/.config/premise/ai.json`
4. Built-in defaults

These overrides currently affect `notes export-beats` and `notes extract-facts` when `--extractor llm` is selected. Timeline flags are accepted for consistency but not used yet.
