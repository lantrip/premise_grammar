# Premise AI Features

## Current Features

### Beat Generation
- **Command**: `Premise: Generate Beats…`
- **Provider**: OpenRouter (configurable model)
- **Scopes**: Current file, story root, uncommitted changes
- **Modes**: Add new, update/fix, recreate all
- **Anchoring**: Section-based (Cel/Scene/Act)
- **Settings**: `premise.ai.*` (model, apiKey, endpoint, beatInsertPosition, beatQualityLevel)

### Entity Description Updates
- **Command**: `Premise: Update Entity Descriptions…`
- **Scopes**: Same as beat generation
- **Updates**: Coalesced per entity, optional changed-ranges-only
- **Settings**: `premise.ai.entityUpdateScope` (descriptions-only, relationships, comprehensive)

### Story Notes System
- **Architecture**: CLI-first (Rust core), VSCode calls `premise notes` commands
- **Commands**:
  - VSCode: `premise.extractFacts` (AI-enhanced), `premise.exportBeats` (via CLI)
  - CLI: `init`, `extract-facts`, `export-beats`, `extract-timeline`, `query`, `rebuild-index`, `status`
- **Format**: JSONL (JSON Lines) for beats, facts, timeline, consistency
- **Location**: `.premise-notes/` at story root
- **Extraction Intelligence**:
  - **Entity traits**: Auto-extracted from `@character Name: Description` definitions (confidence: 1.0)
  - **Co-occurrence relationships**: Discovers entity interactions by analyzing scenes/cels (confidence: 0.7)
  - **Section context**: Tracks act/scene/cel location for all extracted facts
- **Record Types**:
  - `Beat` - Story milestones with entity refs and section context
  - `Fact` - Traits, relationships, knowledge, events, state (with evidence and confidence)
  - `TimelineEvent` - Temporal ordering with entity involvement
  - `ConsistencyEntry` - State tracking
- **Settings**: `premise.notes.*` (enableTracking, factCategories, lspIntegration)
- **Documentation**: See [NOTES_SYSTEM.md](./NOTES_SYSTEM.md)

## LSP Helpers

Server-side commands for grounding AI operations:
- `premise.getStoryRoot(uri)` - Resolve story root path
- `premise.listEntityNames(uri)` - Get canonical entity names
- `premise.collectStructure(uris)` - Get Acts/Scenes/Cels with ranges and entity mentions

## Configuration

### AI Settings (`premise.ai.*`)
- `provider` - AI provider (default: "openrouter")
- `model` - Model identifier (e.g., "openai/gpt-4o-mini")
- `apiKey` - API key (or use OPENROUTER_API_KEY env var)
- `endpoint` - API endpoint
- `chunkingMode` - "section" or "file"
- `beatInsertPosition` - "append" or "prepend"
- `beatQualityLevel` - "concise", "detailed", or "comprehensive"
- `beatGenerationMode` - "add-new", "update-fix", or "recreate-all"
- `entityUpdateScope` - "descriptions-only", "relationships", or "comprehensive"
- `rateLimitPerMinute` - Rate limiting for batch operations

### Notes Settings (`premise.notes.*`)
- `enableTracking` - Auto-export beats after generation (default: false)
- `factCategories` - Which fact types to extract (default: ["trait", "relationship", "knowledge", "event"])
- `storageLocation` - Notes directory name (default: ".premise-notes")
- `lspIntegration` - Enable LSP features (experimental, default: false)

## Implementation Status

✅ **Complete**:
- Beat generation with section anchoring
- Entity description updates with evidence
- **Notes System (CLI-First Architecture)**:
  - ✅ Rust core module: `premise-core/src/notes/` (schema, I/O, extraction)
  - ✅ CLI commands: `init`, `extract-facts`, `export-beats`, `extract-timeline`, `query`, `rebuild-index`, `status`
  - ✅ VSCode integration via CLI execution (TypeScript → Rust CLI)
  - ✅ **Intelligent Extraction**:
    - Entity trait extraction from `@character Name: Description` (1.0 confidence)
    - Co-occurrence relationship discovery from dialogue/prose (0.7 confidence)
    - Section context preservation (act/scene/cel metadata)
  - ✅ **Testing**: 9 snapshot tests with deterministic output
  - ✅ **Error Handling**: Comprehensive error messages with actionable guidance
  - ✅ **Production Ready**: Validated with real story files
- **LSP Helpers**:
  - ✅ `premise.getStoryRoot` - Resolve story root path
  - ✅ `premise.listEntityNames` - Get canonical entity names
  - ✅ `premise.collectStructure` - Get Acts/Scenes/Cels with:
    - **Hierarchical stable IDs** (e.g., `act-one/the-beginning/training-montage`)
    - Parent context (scenes include act, cels include scene + act)
    - Entity mentions per section
    - Range information for precise anchoring
- Uncommitted scope support (git diff integration)
- Sequential processing with progress
- Rate limiting
- Deduplication and validation
- Preview mode for beat changes

🚧 **In Progress**:
- Performance optimization for large story files
- LSP integration for notes (diagnostics, hovers, code lenses)

✅ **Phase C - Adapter Framework (Foundation Complete)**:
- ✅ **Domain-Agnostic Architecture**:l
  - Adapter manifest schema with domain metadata
  - Registry system with auto-discovery
  - CLI commands: `premise adapters list/show`
  - Support for multiple search paths
- ✅ **Domain Abstraction Layer**:
  - `DomainMapper` trait for cross-domain transformation
  - Built-in mappers: Narrative, Sales, Architecture
  - Domain-agnostic entity and section representations
- ✅ **Notes Context API**:
  - Read-only adapter access to notes
  - Query by entity, type, confidence, category
  - Relationship discovery
  - Beat and section queries
- ✅ **Example Adapters** (3 domains):
  - `premise-screenplay-pdf` - Narrative domain (PDF, FDX output)
  - `premise-sales-report` - Sales domain (call analysis)
  - `premise-architecture-diagram` - Software domain (C4, UML, Mermaid)

📋 **Planned (Phase C - Next Steps)**:
- Adapter execution engine
- Provenance tracking for adapter-generated content
- Adapter contribution to notes (facts, beats)
- Advanced relationship inference (sentiment, intensity)
- Consistency validation using notes
- Provider abstraction for local models
- Packaging and binary distribution

## Future Enhancements

- Local model support (Ollama, etc.)
- Entity alias mapping
- Project-wide consistency checks
- Inline quick-fixes for AI suggestions
- Era/location metadata integration
