# Notes System Refinement

## Current Status

The notes system is **production-ready** with:
- ✅ CLI-first architecture (Rust core)
- ✅ Intelligent extraction (traits + co-occurrence)
- ✅ JSONL storage format
- ✅ Entity indexing and querying
- ✅ Comprehensive testing (9 snapshot tests)
- ✅ Error handling with actionable messages

## Areas for Refinement

### 1. Extraction Intelligence

**Current State**:
- Entity traits: Extracted from `@character Name: Description` (confidence: 1.0)
- Co-occurrence: Discovers entities in same scene (confidence: 0.7)
- Section context: Preserves act/scene/cel metadata

**Needs Improvement**:

#### A. Enhanced Entity Detection
- **Current**: Only extracts from `@character` definitions
- **Needed**: Extract from inline descriptions, dialogue, prose

```premise
// Current: Extracts trait from definition
@character Hero: A brave warrior

// Missed: Should extract from prose
Hero is a brave warrior with a mysterious past.

// Missed: Should extract from dialogue
MENTOR
  You're the bravest warrior I've ever trained, Hero.
```

**Proposed**:
- Pattern matching for entity descriptions in prose
- Sentiment analysis of dialogue for trait inference
- Action verb extraction (e.g., "Hero fights" → combat trait)

#### B. Relationship Types
- **Current**: Only "co-occurrence" relationships
- **Needed**: Relationship semantics

```premise
// Should detect relationship type
{Hero} mentors {Student}        → mentorship
{Hero} fights {Villain}         → antagonistic
{Hero} loves {Princess}         → romantic
{Hero} works with {Sidekick}    → collaborative
```

**Proposed**:
- Verb-based relationship classification
- Sentiment scoring (-1.0 to 1.0)
- Relationship strength (0.0 to 1.0)
- Temporal aspects (past/present/future)

#### C. Knowledge Extraction
- **Current**: Only structural extraction
- **Needed**: Implicit knowledge discovery

```premise
// Explicit knowledge (easy)
@character Maya: knows spirit rune magic

// Implicit knowledge (needs inference)
{Maya} draws a spirit rune on the door.
→ Fact: Maya knows spirit rune magic (confidence: 0.8)

{Maya} reads the ancient text without difficulty.
→ Fact: Maya reads ancient languages (confidence: 0.7)
```

**Proposed**:
- Action-to-knowledge mapping
- Skill inference from successful actions
- Knowledge prerequisites detection

### 2. Timeline & Causality

**Current State**:
- Basic timeline extraction from IR
- No causal relationships
- No temporal ordering beyond structure

**Needs Improvement**:

#### A. Event Sequencing
```premise
// Should create ordered timeline
{Hero} finds the sword.           → Event 1
{Hero} trains with the sword.     → Event 2 (after 1)
{Hero} defeats {Villain}.         → Event 3 (after 2)
```

**Proposed**:
- Dependency graph of events
- "before/after/during" relationships
- Flashback detection and reordering

#### B. Causal Links
```premise
// Detect cause and effect
{Hero} finds the sword.
Because of this discovery, {Hero} gains confidence.
→ Causal link: sword discovery → confidence gain
```

**Proposed**:
- Keyword detection (because, therefore, as a result)
- Proximity-based causality (events in same section)
- Confidence scoring for causal relationships

### 3. Consistency Validation

**Current State**:
- `consistency.jsonl` schema exists
- No automatic validation
- No contradiction detection

**Needs Improvement**:

#### A. State Tracking
```premise
// Track possession
=== Scene 1
{Hero} picks up the ancient sword.
→ State: Hero.possesses = "ancient sword"

=== Scene 5
{Hero} draws the ancient sword.
→ Validate: Hero still has sword? ✓

=== Scene 7
{Villain} wields the ancient sword.
→ Contradiction: How did Villain get it? ⚠️
```

**Proposed**:
- Possession tracking (who has what)
- Location tracking (who is where)
- State changes with timestamps
- Contradiction warnings

#### B. Trait Consistency
```premise
// Detect contradictions
@character Hero: afraid of heights

// Later in story:
{Hero} leaps across the rooftops without fear.
→ Contradiction: Hero's acrophobia not reflected ⚠️
```

**Proposed**:
- Trait vs. action validation
- Character arc tracking (traits can evolve)
- Confidence decay over time/sections

### 4. Performance Optimization

**Current State**:
- Works well for small-medium files
- Untested on large corpora (1000+ sections)
- No streaming or chunking

**Needs Improvement**:

#### A. Large File Handling
- **Issue**: O(n²) co-occurrence algorithm for many entities
- **Solution**: Chunked processing, early termination
- **Benchmark**: Test with 10K+ section files

#### B. Incremental Updates
- **Issue**: Full re-extraction on every run
- **Solution**: Delta extraction (only changed sections)
- **Approach**: Track file hashes, process diffs

#### C. Memory Efficiency
- **Issue**: Load entire facts.jsonl into memory
- **Solution**: Streaming JSONL reader
- **Approach**: Lazy loading, pagination

### 5. AI-Enhanced Extraction

**Current State**:
- VSCode command calls AI for facts
- No integration with structural extraction
- Separate workflows (CLI vs AI)

**Needs Improvement**:

#### A. Hybrid Extraction
```bash
# Proposed: Single command, best of both
premise notes extract-facts story.prem --hybrid

# Flow:
# 1. Structural extraction (traits, co-occurrence)
# 2. AI enhancement (implicit facts, relationships)
# 3. Merge with confidence weighting
# 4. Deduplicate and save
```

**Proposed**:
- Structural facts: confidence 1.0 (baseline)
- AI facts: confidence based on evidence strength
- Conflict resolution: prefer explicit > implicit

#### B. Confidence Calibration
- **Current**: Hard-coded scores (1.0 or 0.7)
- **Needed**: Evidence-based scoring

```
Confidence Formula:
- Explicit definition: 1.0
- Direct action: 0.9
- Dialogue implication: 0.8
- Co-occurrence: 0.7
- AI inference with 1 evidence: 0.6
- AI inference with 2+ evidence: 0.8
```

### 6. Query Enhancements

**Current State**:
- CLI: `premise notes query --entity Hero`
- API: Basic filters (type, confidence, entity)
- No aggregation or analytics

**Needs Improvement**:

#### A. Advanced Queries
```bash
# Entity summary
premise notes summary --entity Hero
# Output: All facts grouped by type, timeline view

# Relationship graph
premise notes relationships --entity Hero --depth 2
# Output: Hero's direct and indirect relationships

# Timeline view
premise notes timeline --act "Act One"
# Output: Ordered events with causal links

# Contradiction check
premise notes validate --entity Hero
# Output: Conflicting facts with evidence
```

#### B. Analytics
```bash
# Entity statistics
premise notes stats --entity Hero
# Output: Fact count, confidence avg, relationship count

# Coverage analysis
premise notes coverage
# Output: Which entities have most/least facts

# Quality metrics
premise notes quality
# Output: Avg confidence, evidence ratio, contradiction count
```

### 7. LSP Integration

**Current State**:
- Notes exist but LSP doesn't expose them
- No hovers, diagnostics, or code lenses

**Planned** (from AI_ROADMAP.md):

#### A. Diagnostics
```premise
{Hero} wields the ancient sword.
         ^^^^^^^^^^^^^^^^^^^
Warning: Hero doesn't possess this item (check scene 3)
```

#### B. Hover Hints
```premise
{Maya Chen}
^^^^^^^^^^
Hover:
- Trait: Determined investigator (confidence: 1.0)
- Relationship: Mentored by Keeper Aldrich
- Knowledge: Spirit rune magic
- Last seen: Act Two, Scene 3
```

#### C. Code Lenses
```premise
== The Confrontation
   [5 beats] [3 entities] [View timeline →]

{Hero} faces {Villain}.
```

### 8. Provenance & Versioning

**Current State**:
- Facts have `source` field (imported/llm-generated)
- No version tracking
- No rollback capability

**Needs Improvement**:

#### A. Fact Versioning
```jsonl
{"id":"f123","version":1,"fact":"Hero is brave","source":"imported"}
{"id":"f123","version":2,"fact":"Hero is courageous","source":"llm-generated","supersedes":"f123.v1"}
```

#### B. Rollback
```bash
# Rollback to previous state
premise notes rollback --to "2024-01-15T10:00:00Z"

# Remove all AI-generated facts
premise notes clean --source llm-generated

# Remove facts from specific adapter
premise notes clean --source adapter:premise-screenplay-pdf
```

## Priority Ranking

### High Priority (Core Functionality)
1. **Enhanced Entity Detection** - Extract from prose, not just definitions
2. **Relationship Types** - Semantic relationships, not just co-occurrence
3. **State Tracking** - Possession, location consistency
4. **Performance** - Handle large files efficiently

### Medium Priority (Polish)
5. **Knowledge Extraction** - Implicit knowledge from actions
6. **Timeline & Causality** - Event ordering, causal links
7. **Advanced Queries** - Summaries, analytics, validation

### Low Priority (Nice to Have)
8. **AI-Enhanced Extraction** - Hybrid structural + AI
9. **LSP Integration** - Hovers, diagnostics (separate epic)
10. **Provenance & Versioning** - Fact history, rollback

## Proposed Phases

### Phase 1: Core Intelligence (Weeks 1-2)
- [ ] Enhanced entity detection from prose
- [ ] Relationship type classification
- [ ] Basic state tracking (possession, location)
- [ ] Performance benchmarking

### Phase 2: Consistency & Validation (Week 3)
- [ ] Trait vs. action validation
- [ ] Contradiction detection
- [ ] Timeline ordering
- [ ] Advanced query commands

### Phase 3: AI Integration (Week 4)
- [ ] Hybrid extraction (structural + AI)
- [ ] Confidence calibration
- [ ] Evidence-based scoring
- [ ] Quality metrics

### Phase 4: Production Hardening (Week 5)
- [ ] Large file optimization
- [ ] Incremental updates
- [ ] Memory efficiency
- [ ] Comprehensive benchmarks

## Success Metrics

### Extraction Quality
- **Precision**: % of extracted facts that are correct
- **Recall**: % of possible facts extracted
- **F1 Score**: Harmonic mean of precision and recall
- **Target**: F1 > 0.85 for structural, > 0.75 for AI-enhanced

### Performance
- **Throughput**: Facts extracted per second
- **Target**: > 1000 facts/sec for structural extraction
- **Memory**: Peak memory usage
- **Target**: < 100MB for 10K section story

### Consistency
- **Contradiction Rate**: % of facts with conflicts
- **Target**: < 1% contradictions in final dataset
- **Coverage**: % of entities with comprehensive facts
- **Target**: > 80% of entities have 3+ facts

## Next Steps

**Immediate** (This Week):
1. Benchmark current extraction on large files
2. Design enhanced entity detection patterns
3. Create relationship type taxonomy
4. Draft state tracking schema

**Short Term** (This Month):
1. Implement enhanced extraction
2. Add relationship classification
3. Build consistency validator
4. Optimize for large files

**Long Term** (Next Quarter):
1. AI-hybrid extraction
2. LSP integration
3. Advanced analytics
4. Production deployment

## Open Questions

1. **Entity Resolution**: How to handle entity aliases/variations?
   - "Maya", "Maya Chen", "Detective Chen" → same entity?

2. **Fact Confidence Decay**: Should confidence decrease over story sections?
   - "Hero is brave" in Act 1 → still relevant in Act 3?

3. **Cross-File Facts**: How to merge facts from multiple files?
   - Story spread across chapter1.prem, chapter2.prem, etc.

4. **Fact Deduplication**: When are two facts "the same"?
   - "Hero is brave" vs "Hero shows courage" → dedupe or separate?

5. **Domain-Specific Extraction**: Different rules for sales vs narrative?
   - Sales: Extract commitments, objections
   - Narrative: Extract traits, relationships

## References

- [NOTES_SYSTEM.md](./NOTES_SYSTEM.md) - Current documentation
- [AI_ROADMAP.md](./AI_ROADMAP.md) - Implementation status
- [premise-core/src/notes/](./premise-core/src/notes/) - Implementation
- [premise-core/tests/notes_snapshots.rs](./premise-core/tests/notes_snapshots.rs) - Test suite
