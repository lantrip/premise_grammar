# Premise Quick Start

A concise guide to writing Premise files and consuming the Rust core (premise-core) from the CLI and Python.

## 1) Write in Premise

Premise is a story authoring format with hierarchical structure, entities, imports, adapters, and screenplay-friendly notation.

Minimal example (story.prem):

```
TITLE: The Heist
WORLD: Neon City
FORMAT: screenplay

= Act 1 / 25%
== Opening Scene / 10%
=== Rooftop.Night

@characters {
  - Hero: A skilled thief
  - Mentor: A retired safecracker
}

{Hero}
We do this my way.

(whisper)
Or not at all.

+mood: tense

@import "shared/entities.prem"
@adapter "adapters/pdf_export.ts"
```

Copy-paste starter (blank template):

```
TITLE: Untitled Story
WORLD:
FORMAT: screenplay

= Act 1
== Opening Scene
=== Location.Time

@characters {
  - Protagonist:
  - Antagonist:
}

{Protagonist}
Your first line goes here.

(beat)
Something happens.

@import "shared/common.prem"
@adapter "adapters/example.ts"
```

Quick validate (one-liner):

```bash
cd premise-core && cargo run -- validate story.prem
```

JSON variant:

```bash
cd premise-core && cargo run -- --format json validate story.prem
```

Parse my file (JSON):

```bash
cd premise-core && cargo run -- --format json parse story.prem --ast --symbols --imports
```

Plan adapters (graph-only):

```bash
cd premise-core && cargo run -- --format json plan story.prem --graph-only
```

Highlights:

- =, ==, ===: Act / Scene / Cel headers (optionally with proportions like 25%)
- @characters { … }: Define entities inside a block; reference with {Hero}
- Dialogue: Use speaker references ({Hero}), parentheticals (whisper), and plain text
- +key: value: Metadata lines
- @import: Include another .prem file; @adapter: declare adapter usage

Optional content layers:

- /// beats, // treatment, / narrative

## 2) Parse and Inspect with the CLI

From the premise-core directory:

```bash
# Pretty CST (S-expressions)
cargo run -- parse examples/theming_showcase.prem

# JSON output with extras
cargo run -- --format json parse examples/theming_showcase.prem \
  --ast --symbols --imports --resolved-imports

# Validate (duplicates, unknown refs, simple cycles)
cargo run -- --format json validate path/to/file.prem

# Analyze to IR (story + adapter refs)
cargo run -- --format json analyze path/to/file.prem

# Plan adapters; graph-only view
cargo run -- --format json plan path/to/file.prem --graph-only

# Emit JSON Schemas for outputs
cargo run -- schema --type all > schemas.json
```

What you get:

- parse --format json: cst, diagnostics, plus optional ast, symbols, imports, resolved_imports
- validate: ValidationReport with issue codes and ranges
- analyze: IrAnalysis with StoryGraph (acts/scenes/cels) and adapter references
- plan: PlanAnalysis with deterministic adapter steps and graph

## 3) Consume from Python

Install the Python bindings with maturin (one-time):

```bash
cd premisecore
python -m venv .venv && source .venv/bin/activate
pip install maturin
maturin develop
```

Example usage:

```python
import json
import premisecore as pc

p = pc.Parser()
source = open("story.prem").read()

# Parse with optional extras
print(json.dumps(json.loads(p.parse_json(source, True, True, True)), indent=2))

# Validate
print(json.dumps(json.loads(p.validate_json(source)), indent=2))

# Analyze IR
print(json.dumps(json.loads(p.analyze_json(source)), indent=2))

# Plan adapters
print(json.dumps(json.loads(p.plan_json(source)), indent=2))

# JSON Schema for outputs (parse|validate|analyze|plan|all)
print(pc.schema("all"))
```

## 4) Data Shapes (at a glance)

Schemas are available via the CLI and Python, but here are key top-level structures:

- Parse: ParseOutput { cst, diagnostics, ast?, symbols?, imports?, resolved_imports? }
- Validate: ValidateOutput { report: ValidationReport { issues[] } }
- Analyze: AnalyzeOutput { ir: Ir { story: StoryGraph, adapters[] } }
- Plan: PlanOutput { plan: PlanAnalysis { plan.steps[], graph{nodes[],edges[]}, diagnostics[] } }

Generate full JSON Schemas:

```bash
cd premise-core
cargo run -- schema --type all > schemas.json
```

## 5) Next Steps

- Adapters: list/show, execution engine (sequential), provenance, hydration
- Artifacts: stable naming with hashes, optional on-disk outputs
- Hardening: limits/timeouts, caching, benchmarks, fuzzing

That’s it—write .prem, inspect via CLI, or integrate via Python.
