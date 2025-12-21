# Interactive Grammar Roadmap

A minimal, incremental path to support CYOA/interactive fiction in Premise grammar.

**Goal:** Capture the structure of interactive elements at the grammar level while deferring execution semantics to the runtime (Hedgerow).

**Philosophy:** Start with the least grammar required to parse the most useful patterns. Extend incrementally.

---

## Phase 1: Section Navigation (Foundation)

The core of any branching story is the ability to name sections and jump between them.

### 1.1 Section IDs

Add `@id:name` suffix to section headers:

```prem
= The Entrance Hall @id:entrance
== A Dark Corridor @id:corridor
=== The Red Door @id:red_door
```

**Grammar change:** Modify `act_header`, `scene_header`, `cel_header` to accept optional trailing `@id:identifier`.

**Why first:** Every other interactive feature depends on addressable sections.

### 1.2 @goto

Unconditional navigation to a named section:

```prem
@goto entrance
```

**Grammar change:** New `goto_statement` rule.

**Validates:** Section ID parsing works end-to-end.

---

## Phase 2: Slots (User Input)

Slots capture user responses. Two types: `input` (free text) and `choice` (discrete options).

### 2.1 Basic Slot Block

```prem
@slot player_name {
  type: input
  prompt: "What is your name?"
}

@slot door_choice {
  type: choice
  prompt: "Which door?"
  options:
    - id: red
      label: "Red door"
    - id: blue
      label: "Blue door"
}
```

**Grammar change:** Extend `entity_block` to recognize `@slot name {`. The interior uses existing `object_property` and `adapter_list_property` rules.

**No new interior parsing needed** - treat slot contents as key-value pairs (already supported).

### 2.2 Option-Level goto (Ergonomic CYOA)

The most common pattern: choice leads directly to a section.

```prem
@slot door_choice {
  type: choice
  prompt: "Which door?"
  options:
    - id: red
      label: "Red door"
      goto: red_room
    - id: blue
      label: "Blue door"
      goto: blue_room
}
```

**Grammar change:** None - `goto: section_id` is just another property. Highlighting can emphasize it.

**This alone enables simple CYOA stories.**

---

## Phase 3: Template Interpolation

Reference filled slot values in narrative:

```prem
/ Welcome, {slot.player_name.value}.
/ You chose the {slot.door_choice.label}.
```

**Grammar change:** None - existing `entity_reference` rule captures `{...}` content.

**Highlighting change:** Add query to distinguish `{slot.*}`, `{state.*}`, `{gate.*}` from entity references.

---

## Phase 4: Conditional Routing (Advanced)

For stories needing state-based branching beyond simple choice-to-section.

### 4.1 @gate (Named Conditions)

```prem
@gate has_key {
  state.has_key == true
}
```

**Grammar change:** Extend `entity_block` for `@gate name {`. Interior captured as raw text (no expression parsing in grammar).

### 4.2 @branch with @path

```prem
@branch unlock_door {
  @path open -> treasure { when: gate.has_key }
  @path default -> stuck
}
```

**Grammar change:**
- Extend `entity_block` for `@branch name {`
- New `branch_path` rule for `@path name -> dest { when: ... }`

### 4.3 State Metadata

Use existing metadata syntax:

```prem
+state.has_key: true
+state.trust_level: 0.7
```

**Grammar change:** None - `+key: value` already parsed as `metadata_line`.

---

## What We're NOT Doing (Yet)

| Feature | Status | Rationale |
|---------|--------|-----------|
| Full expression parsing | Deferred | Capture as string; validate in runtime |
| @turn blocks | Deferred | Implicit turns cover most cases |
| `effects:` on options | Deferred | Use `+state.*` inline for now |
| `from: llm` execution | Out of scope | Runtime/Hedgerow concern |
| Session sidecar format | Out of scope | Runtime concern |

---

## Grammar Rules Summary

### New Rules

| Rule | Syntax | Phase |
|------|--------|-------|
| `section_id` | `@id:name` | 1 |
| `goto_statement` | `@goto section_id` | 1 |
| `branch_path` | `@path name -> dest { when: ... }` | 4 |

### Extended Rules

| Rule | Addition | Phase |
|------|----------|-------|
| `act_header` | Optional `section_id` suffix | 1 |
| `scene_header` | Optional `section_id` suffix | 1 |
| `cel_header` | Optional `section_id` suffix | 1 |
| `entity_block` | Patterns for `@slot`, `@gate`, `@branch` | 2, 4 |

### Unchanged (Reused)

| Rule | Used For |
|------|----------|
| `object_property` | Slot properties (`type:`, `prompt:`, etc.) |
| `adapter_list_property` | Choice options (`- id: red`) |
| `entity_reference` | Interpolation (`{slot.name.value}`) |
| `metadata_line` | State (`+state.key: value`) |

---

## Syntax Highlighting Additions

```scheme
; Section IDs
(section_id "@id:" @punctuation.special)
(section_id (id) @tag)

; @goto
(goto_statement "@goto" @keyword.control)
(goto_statement (target) @tag)

; Interactive blocks
(entity_block
  (block_type) @keyword
  (#match? @keyword "^(slot|gate|branch)"))

; Slot/state interpolation
(entity_reference
  (entity) @variable.builtin
  (#match? @entity "^(slot|state|gate)\\."))
```

---

## Test Cases to Create

```
tests/cases/
  10_interactive_section_ids.prem    # Phase 1
  11_interactive_goto.prem           # Phase 1
  12_interactive_slot_input.prem     # Phase 2
  13_interactive_slot_choice.prem    # Phase 2
  14_interactive_interpolation.prem  # Phase 3
  15_interactive_gate_branch.prem    # Phase 4
```

---

## Minimal Viable Example

After Phase 2, this complete CYOA story should parse:

```prem
TITLE: Pick A Door
+mode: interactive
+entry: hall

= The Hall @id:hall

/ You stand before three doors.

@slot door_choice {
  type: choice
  prompt: "Which door do you open?"
  options:
    - id: red
      label: "The red door"
      goto: red_room
    - id: blue
      label: "The blue door"
      goto: blue_room
}

= Red Room @id:red_room

/ Warm light floods the room. You found the treasure!

= Blue Room @id:blue_room

/ Cold air bites your skin. The room is empty.
```

---

## Next Steps

1. **Agree on this roadmap** - confirm Phase 1-2 scope
2. **Implement Phase 1** - section IDs and @goto
3. **Add test cases** - validate parsing
4. **Implement Phase 2** - @slot blocks
5. **Update highlighting** - interactive constructs
6. **Iterate** - Phase 3-4 as needed

---

## References

- [PREMISE_INTERACTION.md](../../docs/PREMISE_INTERACTION.md) - Full spec (superset of this roadmap)
- [PREMISE_BRANCHING.md](../../docs/PREMISE_BRANCHING.md) - Comprehensive branching documentation
- [grammar.js](../grammar.js) - Current Tree-sitter grammar
