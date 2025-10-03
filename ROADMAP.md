## Notes System Roadmap (Testable Flow)

This roadmap captures a practical, iterative path from story text → parsed entities/beats/facts with deterministic outputs and simple importance filters.

### Alignment with AI_ROADMAP.md

- Entity Discovery (Pass 1): `discover-entities` (Premise) and plain-text discovery API for proposing canon + aliases.
- Beat/Fact Extraction (Pass 2): `export-beats`, `extract-facts`, `extract-timeline` with `{?Entity}` allowed and alias normalization.
- Alias Management: centralized `.premise-notes/aliases.json`, `merge-aliases`, `apply-alias-delta`, and `normalize`.
- Storage & Sinks: JSONL + index (managed `.premise-notes/`) and modular sinks.
- Determinism & Tests: stable IDs, schema validation, snapshot tests.

### Testable End-to-End Flow

1. Create a small corpus under `tests/notes_corpus/`:

- `prem/` — `.prem` files with `@character` and narrative lines
- `plain/` — `novel.txt` and `novel.md` (headings as chapters/sections)
- `aliases/alias_seed.json` — initial canonical → aliases

2. Run the pipeline deterministically:

```bash
# Premise inputs
premise notes export-beats tests/notes_corpus/prem/ch1.prem --sink notes --stable-ids
premise notes extract-facts tests/notes_corpus/prem/ch1.prem --sink notes --stable-ids

# Markdown/Plain inputs
premise notes export-beats tests/notes_corpus/plain/novel.md --input markdown --sink notes --stable-ids
premise notes extract-facts tests/notes_corpus/plain/novel.md --input markdown --sink notes --stable-ids

# Aliases: merge/apply and re-normalize
premise notes merge-aliases --aliases tests/notes_corpus/aliases/alias_seed.json --path . --dry-run
premise notes apply-alias-delta --delta tests/notes_corpus/aliases/alias_delta.json --path . --dry-run
premise notes normalize .

# Unknowns
premise notes summarize-uncertain --path .
```

3. Surface “important” records via simple, explainable filters (tune later):

```bash
# Beats: multi-entity + substantive text length
jq 'select((.entities|length)>=2 and (.text|length)>=60)' .premise-notes/beats.jsonl > out/important_beats.jsonl

# Facts: high confidence or structural types
jq 'select(((.confidence // 0)>=0.7) or (.type=="event") or (.type=="relationship"))' .premise-notes/facts.jsonl > out/important_facts.jsonl

# Optional: dedupe by text
jq -s 'unique_by(.text)' out/important_beats.jsonl > out/important_beats_dedup.json
```

4. Golden snapshots (CI-friendly):

```bash
jq -s '.' out/important_beats.jsonl > premise-core/tests/snapshots/important_beats.snap
jq -s '.' out/important_facts.jsonl > premise-core/tests/snapshots/important_facts.snap
```

5. Schema validation (optional CI step):

```bash
cargo run -p premise-notes --bin generate_schemas
# Validate output JSONL lines against schemas using your preferred tool (e.g., ajv)
```

### Near-Term Enhancements

- Add a simple importance score utility in `premise-notes` and a CLI flag to filter by score (keeps jq fallback).
- Add plain-text `discover-entities` CLI to propose alias deltas (parity with Premise discovery).
- Expand snapshot suites for prem-only, md-only, and mixed corpora.
- Track metrics: counts of unknowns, conflicts on alias deltas, important subsets.
