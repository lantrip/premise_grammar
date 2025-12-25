## Premise Core (Rust)

**Goal**

Build a production-grade Rust core that parses Premise source using the existing Tree-sitter grammar, constructs a typed AST → IR, validates and resolves symbols, and hydrates domain models (entities, story structure, adapters). Expose this core via a stable Rust API, a CLI, and Python wheels (PyO3/maturin). Keep this folder self-contained so it can be extracted into its own repo if needed.

**Scope**

- Parsing: wrap Tree-sitter Premise (incremental, tolerant) and produce CST with source maps
- AST/IR: typed nodes, symbol tables, story and adapter graphs
- Pipeline: deterministic passes (imports, validation, planning, transform, hydrate)
- Adapters: registry + execution order + provenance
- Diagnostics: structured, source-mapped; machine-readable and pretty
- APIs: Rust crate, CLI, and Python bindings; JSON serde for AST/IR/Story

**Non-goals (initially)**

- Network service deployment (can be added later)
- IDE/LSP features beyond CLI diagnostics (we already have editor integrations)

---

## Shipped Features

- Parsing: CST with source maps (Tree-sitter Premise)
- AST: typed nodes with ranges and children
- Symbols & Imports: symbol tables, import analysis, and resolution
- Validation: duplicates, unknown references, basic cycle detection
- IR & Planning: story graph (acts/scenes/cels), adapter refs, deterministic plan
- Notes System: JSONL-based story knowledge base (beats, facts, timeline, consistency)
- CLI: `parse`, `validate`, `analyze`, `plan`, `notes` with global `--format json|pretty`
- JSON Schemas: `premise schema --type parse|validate|analyze|plan|notes|all`
- Python bindings: `premisecore.Parser` with `parse_json`/`validate_json`/`analyze_json`/`plan_json` and `schema()`

## Roadmap

See [docs/PREMISE_CORE_ROADMAP.md](../docs/PREMISE_CORE_ROADMAP.md) for detailed implementation phases.

---

## Initial API Sketch (subject to change)

Rust

```rust
pub struct Parser { /* internal state */ }
pub struct Cst { /* nodes + ranges */ }
pub struct Ast { /* typed nodes + source maps */ }
pub struct Ir { /* symbol tables + graphs */ }
pub struct Diagnostics { /* messages + ranges + codes */ }

impl Parser {
    pub fn new() -> Self { /* ... */ }
    pub fn parse_str(&mut self, input: &str) -> (Cst, Diagnostics) { /* ... */ }
    pub fn parse_path<P: AsRef<Path>>(&mut self, path: P) -> (Cst, Diagnostics) { /* ... */ }
}

pub fn analyze(ast: &Ast) -> (Ir, Diagnostics) { /* ... */ }
pub fn hydrate(ir: &Ir) -> (Story, Diagnostics) { /* ... */ }
```

CLI

```bash
# Parse CST (S-expression) or JSON with optional extras
premise parse examples/theming_showcase.prem
premise --format json parse examples/theming_showcase.prem --ast --symbols --imports --resolved-imports

# Validate (duplicates, unknown refs)
premise --format json validate path/to/file.prem

# Analyze to IR (story/adapter refs)
premise --format json analyze path/to/file.prem

# Plan adapters and inspect graph
premise --format json plan path/to/file.prem
premise --format json plan path/to/file.prem --graph-only

# Emit JSON Schemas for public output types
premise schema --type all
premise schema --type parse --out schema.parse.json

# Story Notes Management
premise notes init --title "My Story"
premise notes export-beats story/chapter1.prem
premise notes extract-facts story/chapter1.prem
premise notes extract-timeline story/chapter1.prem
premise notes query --entity "Hero"
premise notes rebuild-index
premise notes status

# One-pass analysis with notes extraction
premise analyze story/chapter1.prem --extract-notes

# (Phase 4) Run adapters and hydrate
premise adapters list
premise adapters show <id>
premise run path/to/file.prem --json --provenance
premise hydrate path/to/file.prem --json --artifacts-out out/ --with-notes .premise-notes/
```

Python (via wheels)

```python
import premisecore as pc

p = pc.Parser()
source = open("story.prem").read()
print(p.parse_json(source, include_ast=True, include_symbols=True, include_imports=True))
print(pc.schema("all"))
```

---

## Repository Isolation

This folder is designed to be extracted:

- No cross-imports from the monorepo; use JSON fixtures under `tests/`
- Embed build script and CI config locally
- Feature flags for bindings/cli/service layers

