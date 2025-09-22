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
- CLI: `parse`, `validate`, `analyze`, `plan` with global `--format json|pretty`
- JSON Schemas: `premise schema --type parse|validate|analyze|plan|all`
- Python bindings: `premisecore.Parser` with `parse_json`/`validate_json`/`analyze_json`/`plan_json` and `schema()`

## Roadmap & Phases

We iterate in small, verifiable phases. Each phase ships runnable code and tests.

### Completed (Phases 0–3)

- Core parser, AST, and diagnostics
- Symbols/imports/resolution and validation (duplicates, unknown refs, cycles)
- IR, story/adapter graphs, and deterministic planning
- CLI and JSON outputs; schemas; Python bindings

### Phase 4 — Adapter Execution & Hydration

- [ ] Adapter registry and APIs
- [ ] Apply transforms with provenance
- [ ] Hydrate domain: Entities, Story, AdapterResults

#### Roadmap

- Adapters (short):

  - Registry & APIs: `Adapter`, `AdapterContext`, `AdapterResult`, `Transform`, `Provenance`; CLI `adapters list/show`
  - Execution: sequential `run_adapters(...)->ExecutionReport`; CLI `run --provenance`
  - Hydration: `hydrate(ir, exec)->HydratedStory`; CLI `hydrate --json [--artifacts-out]`
  - Artifacts & provenance: stable names, enriched diagnostics
  - Hardening: optional concurrency, caching, benchmarks

- Phase 4.1 — Foundations

  - Define `Adapter`, `AdapterContext`, `AdapterResult`, `Transform`, `Provenance`.
  - Implement `Registry` (built-ins + file-backed) with deterministic listing.
  - CLI: `premise adapters list`, `premise adapters show <id>`.
  - Tests: trait object execution with a mock adapter; JSON serde for results.

- Phase 4.2 — Execution engine

  - Implement `run_adapters(ctx, registry, ir, plan) -> ExecutionReport` (sequential).
  - CLI: `premise run <file> --json --provenance`.
  - Snapshot tests: execution reports per `tests/cases`, deterministic ordering.

- Phase 4.3 — Hydration

  - Implement `hydrate(ir, exec) -> HydratedStory` and apply `Transform`s.
  - CLI: `premise hydrate <file> --json [--artifacts-out dir/]`.
  - Snapshots: hydrated story outputs; provenance integrity.

- Phase 4.4 — Artifacts & provenance polish

  - Write artifacts to disk with stable naming; include hashes.
  - Enrich diagnostics (codes, ranges) across adapter failures.
  - Limits/timeouts and size caps for safety.

- Phase 4.5 — Hardening
  - Optional concurrency when independent; default remains deterministic sequential.
  - Basic caching by content hash; benchmarks.

#### Key decisions to make

- Adapter identity: string IDs vs filesystem paths; normalization rules.
- Adapter configuration format: YAML/JSON/TOML; schema and validation.
- Transform model: initial high-level vs fine-grained edit scripts with ranges.
- Provenance granularity: per-transform vs per-adapter, and serialization format.
- Artifact storage: in-memory only vs on-disk with `--artifacts-out`.
- Execution sandboxing: timeouts, resource limits, and trust model for adapters.

### Phase 5 — Packaging & Bindings

- [x] Python wheels via PyO3/maturin
- [x] CLI polish and JSON schemas
- [ ] Benchmarks and fuzzing harness

### Phase 6 — Optional Service Wrapper

- [ ] HTTP/gRPC around the same core
- [ ] Caching and versioning

---

## Deliverables per Phase

- Code with unit tests and golden snapshots
- CLI commands for the features of the phase
- JSON schemas and example outputs
- Performance notes and known limitations

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

# (Phase 4) Run adapters and hydrate
premise adapters list
premise adapters show <id>
premise run path/to/file.prem --json --provenance
premise hydrate path/to/file.prem --json --artifacts-out out/

# (Phase 4+) Hydration TBD
# premise hydrate path/to/file.prem --out hydrated.json
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

---

## Next Steps (working set)

1. Phase 4.1 implementation: types, registry, and `adapters list/show`
2. Phase 4.2 execution engine and `premise run`
3. Phase 4.3 hydration and snapshot outputs

We will update the checklist above as we complete items.
