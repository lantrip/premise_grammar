# Premise Core Roadmap

> This document tracks the implementation phases for the premise-core Rust library.

We iterate in small, verifiable phases. Each phase ships runnable code and tests.

## Completed (Phases 0–3)

- Core parser, AST, and diagnostics
- Symbols/imports/resolution and validation (duplicates, unknown refs, cycles)
- IR, story/adapter graphs, and deterministic planning
- CLI and JSON outputs; schemas; Python bindings

## Phase 4 — Adapter Execution & Hydration

- [ ] Adapter registry and APIs
- [ ] Apply transforms with provenance
- [ ] Hydrate domain: Entities, Story, AdapterResults

### Roadmap

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

### Key decisions to make

- Adapter identity: string IDs vs filesystem paths; normalization rules.
- Adapter configuration format: YAML/JSON/TOML; schema and validation.
- Transform model: initial high-level vs fine-grained edit scripts with ranges.
- Provenance granularity: per-transform vs per-adapter, and serialization format.
- Artifact storage: in-memory only vs on-disk with `--artifacts-out`.
- Execution sandboxing: timeouts, resource limits, and trust model for adapters.

## Phase 5 — Packaging & Bindings

- [x] Python wheels via PyO3/maturin
- [x] CLI polish and JSON schemas
- [ ] Benchmarks and fuzzing harness

## Phase 6 — Optional Service Wrapper

- [ ] HTTP/gRPC around the same core
- [ ] Caching and versioning

---

## Deliverables per Phase

- Code with unit tests and golden snapshots
- CLI commands for the features of the phase
- JSON schemas and example outputs
- Performance notes and known limitations

---

## Next Steps (working set)

1. Phase 4.1 implementation: types, registry, and `adapters list/show`
2. Phase 4.2 execution engine and `premise run`
3. Phase 4.3 hydration and snapshot outputs

We will update the checklist above as we complete items.
