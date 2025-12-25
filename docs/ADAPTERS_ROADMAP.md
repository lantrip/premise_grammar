# Adapters Roadmap

> This document tracks planned features for the Premise Adapter Framework.

## Adapter Execution

**Planned workflow**:

```bash
# Run adapter on a file
premise run <adapter-id> <file.prem> [options]

# Examples
premise run premise-screenplay-pdf story.prem -o screenplay.pdf
premise run premise-sales-report call.prem --format html
premise run premise-architecture-diagram arch.prem -o diagram.svg
```

**Execution flow**:

1. Parse `.prem` file to IR (JSON)
2. Pass IR to adapter via stdin
3. Provide notes context via environment/API
4. Capture adapter output
5. Track provenance (which adapter generated what)

## Provenance Tracking

**Goal**: Track which adapter generated content

```jsonl
{"type":"fact","id":"f123","fact":"Hero is brave","source":"adapter:premise-screenplay-pdf","adapter_version":"1.0.0"}
{"type":"beat","id":"b456","text":"Hero confronts villain","source":"adapter:premise-screenplay-pdf"}
```

**Benefits**:

- **Trust**: Know the source of generated content
- **Rollback**: Remove all facts from a specific adapter
- **Reproducibility**: Re-run specific adapter versions
- **Debugging**: Trace issues to specific adapters

## Adapter Composition

Chain adapters together:

```bash
premise run analyzer input.prem | premise run visualizer -o output.html
```

## Notes Contribution

Adapters can write facts back to notes:

```json
{
  "capabilities": {
    "contributes_facts": true
  }
}
```

Example contributions:

- **Screenplay adapter**: Extract dialogue patterns, scene lengths
- **Sales adapter**: Detect objections, commitment signals
- **Architecture adapter**: Identify dependencies, complexity metrics
