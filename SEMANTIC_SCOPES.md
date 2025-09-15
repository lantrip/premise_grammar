# Cuneiform Grammar Semantic Scopes Reference

This document provides comprehensive documentation for all semantic scopes used in the Cuneiform grammar's syntax highlighting queries. These scopes are designed to enable rich theming support in editors like VS Code, Cursor, and Zed.

## Table of Contents

- [Overview](#overview)
- [Scope Categories](#scope-categories)
- [Complete Scope Reference](#complete-scope-reference)
- [Theming Integration](#theming-integration)
- [Backward Compatibility](#backward-compatibility)
- [Contributing Guidelines](#contributing-guidelines)

## Overview

The Cuneiform grammar uses semantic scopes to provide fine-grained control over syntax highlighting and theming. Each scope follows a hierarchical naming convention that allows theme authors to target specific elements or broader categories.

### Scope Naming Convention

Scopes follow the pattern: `category.subcategory.specific.context`

For example:
- `markup.heading.1.story.act` - Act headers in story structure
- `keyword.control.content.beat` - Beat content type markers
- `entity.name.character.speaker` - Character names in dialogue

## Scope Categories

### Comments (`comment.*`)
Documentation and non-story text that should be visually distinguished.

| Scope | Description | Example |
|-------|-------------|---------|
| `comment.line` | Single-line comments | `# This is a comment` |

### Keywords (`keyword.*`)
Language keywords, directives, and control structures.

| Scope | Description | Example |
|-------|-------------|---------|
| `keyword.directive` | File headers and directives | `@premise: novel` |
| `keyword.import` | Import statements | `@import "world.yaml"` |
| `keyword.control.content.beat` | Beat content markers | `///` |
| `keyword.control.content.treatment` | Treatment content markers | `//` |
| `keyword.control.content.narrative` | Narrative content markers | `/` |

### Markup (`markup.*`)
Document structure and hierarchy elements.

| Scope | Description | Example |
|-------|-------------|---------|
| `markup.heading.1.story.act` | Act headers | `= Act One` |
| `markup.heading.2.story.scene` | Scene headers | `== Opening Scene` |
| `markup.heading.3.story.cel` | Cel headers | `=== INT. Castle` |

### Punctuation (`punctuation.*`)
Special characters and delimiters with semantic meaning.

| Scope | Description | Example |
|-------|-------------|---------|
| `punctuation.definition.heading.story.act` | Act header markers | `=` |
| `punctuation.definition.heading.story.scene` | Scene header markers | `==` |
| `punctuation.definition.heading.story.cel` | Cel header markers | `===` |
| `punctuation.definition.content.beat` | Beat markers | `///` |
| `punctuation.definition.content.treatment` | Treatment markers | `//` |
| `punctuation.definition.content.narrative` | Narrative markers | `/` |
| `punctuation.definition.entity.begin` | Entity reference start | `{` in `{Hero}` |
| `punctuation.definition.entity.end` | Entity reference end | `}` in `{Hero}` |
| `punctuation.definition.parenthetical.begin` | Parenthetical start | `(` in `(softly)` |
| `punctuation.definition.parenthetical.end` | Parenthetical end | `)` in `(softly)` |
| `punctuation.special` | Special characters | `@`, `-` |
| `punctuation.delimiter` | Delimiters | `:` |
| `punctuation.bracket` | Brackets | `{`, `}` |

### Variables (`variable.*`)
Variable-like constructs and special definitions.

| Scope | Description | Example |
|-------|-------------|---------|
| `variable.special` | Entity constructs | `@character Hero: Brave` |

### Types (`type.*`)
Type definitions and block structures.

| Scope | Description | Example |
|-------|-------------|---------|
| `type` | Entity blocks and definitions | `@characters { ... }` |

### Entities (`entity.*`)
Named entities within the story content.

| Scope | Description | Example |
|-------|-------------|---------|
| `entity.name.reference` | Entity references in text | `{Hero}`, `{Castle}` |
| `entity.name.character.speaker` | Character names in dialogue | `HERO:` in dialogue |

### Text (`text.*`)
Story content and narrative elements.

| Scope | Description | Example |
|-------|-------------|---------|
| `text.prose.line` | Prose line container | Lines containing mixed prose content |
| `text.narrative` | General prose text | Story narrative |
| `text.parenthetical` | Parenthetical notes | `(softly)` in dialogue |

### Metadata (`meta.*`)
Metadata and property definitions.

| Scope | Description | Example |
|-------|-------------|---------|
| `meta.property` | Metadata lines | `location: Castle` |

### Errors (`error`)
Parse errors and invalid syntax.

| Scope | Description | Example |
|-------|-------------|---------|
| `error` | Invalid syntax | Malformed constructs |

## Complete Scope Reference

```scheme
; From queries/highlights.scm

; Comments
(line_comment) @comment.line

; File headers
(file_header) @keyword.directive

; Story structure
(act_header) @markup.heading.1.story.act
(scene_header) @markup.heading.2.story.scene
(cel_header) @markup.heading.3.story.cel

; Structure markers
"=" @punctuation.definition.heading.story.act
"==" @punctuation.definition.heading.story.scene
"===" @punctuation.definition.heading.story.cel

; Content types
(content_type_beat) @keyword.control.content.beat
(content_type_treatment) @keyword.control.content.treatment
(content_type_narrative) @keyword.control.content.narrative

; Content markers
"///" @punctuation.definition.content.beat
"//" @punctuation.definition.content.treatment
"/" @punctuation.definition.content.narrative

; Entity definitions
(entity_construct) @variable.special
"@" @punctuation.special

; Entity blocks
(entity_block) @type
(balanced_braces) @type

; Imports
(import_statement) @keyword.import
(adapter_statement) @keyword

; Metadata
(metadata_line) @meta.property

; Entity references
(entity_reference) @entity.name.reference
(ref_open) @punctuation.definition.entity.begin
(ref_close) @punctuation.definition.entity.end

; Story content
(dialogue_speaker) @entity.name.character.speaker
(parenthetical) @text.parenthetical
(prose_text) @text.narrative

; General punctuation
":" @punctuation.delimiter
"{" @punctuation.bracket
"}" @punctuation.bracket
"-" @punctuation.special

; Error recovery
(ERROR) @error
```

## Theming Integration

### VS Code / Cursor Themes

Theme authors can target these scopes in their theme JSON:

```json
{
  "tokenColors": [
    {
      "name": "Cuneiform Story Act Headers",
      "scope": "markup.heading.1.story.act",
      "settings": {
        "foreground": "#FF6B6B",
        "fontStyle": "bold"
      }
    },
    {
      "name": "Cuneiform Entity References",
      "scope": "entity.name.reference",
      "settings": {
        "foreground": "#4ECDC4",
        "fontStyle": "italic"
      }
    },
    {
      "name": "Cuneiform Beat Content",
      "scope": "keyword.control.content.beat",
      "settings": {
        "foreground": "#95E77E",
        "fontStyle": "bold"
      }
    }
  ]
}
```

### Zed Themes

Zed themes can similarly target these scopes:

```toml
[syntax]
"markup.heading.1.story.act" = { color = "#FF6B6B", font_style = "bold" }
"entity.name.reference" = { color = "#4ECDC4", font_style = "italic" }
"keyword.control.content.beat" = { color = "#95E77E" }
```

### Scope Hierarchy

Themes can target scopes at different levels of specificity:

- `markup` - All markup elements
- `markup.heading` - All headings
- `markup.heading.1` - All level-1 headings
- `markup.heading.1.story` - Story-specific level-1 headings
- `markup.heading.1.story.act` - Act headers specifically

## Backward Compatibility

### Maintaining Compatibility

When modifying scopes:

1. **Never remove** existing scopes without a deprecation period
2. **Add new scopes** as more specific variants of existing ones
3. **Document changes** in this file with version numbers
4. **Test with existing themes** before releasing

### Deprecation Process

1. Mark scope as deprecated in this document
2. Add comment in highlights.scm: `; DEPRECATED: Will be removed in v2.0`
3. Maintain for at least 2 minor versions
4. Provide migration guide for theme authors

### Version History

| Version | Changes | Date |
|---------|---------|------|
| 1.0.0 | Initial semantic scope system | 2024-09 |

## Contributing Guidelines

### Adding New Scopes

1. **Check existing scopes** - Reuse before creating new ones
2. **Follow naming conventions** - Use dot-separated hierarchical names
3. **Document thoroughly** - Add to this file with examples
4. **Test with themes** - Ensure new scopes work with existing themes
5. **Update validation** - Add to scripts/validate_scopes.py

### Scope Naming Rules

1. Use lowercase letters, numbers, dots
2. Start with a standard category (comment, keyword, markup, etc.)
3. Add context-specific suffixes for clarity
4. Keep names semantic, not visual (e.g., `entity.name` not `blue.text`)

### Testing Scopes

Before submitting changes:

```bash
# Run query tests
./test_queries.sh

# Validate scopes
python3 scripts/validate_scopes.py

# Test with example file
tree-sitter highlight examples/theming_showcase.cune
```

### Pull Request Checklist

- [ ] Scopes follow naming conventions
- [ ] Added to SEMANTIC_SCOPES.md with examples
- [ ] Updated theming_showcase.cune to demonstrate new scopes
- [ ] Tested with at least one theme
- [ ] Validation scripts pass
- [ ] No breaking changes to existing scopes

## Examples

### Story Structure Example

```cuneiform
= Act One: The Beginning
== Opening Scene - Morning
=== INT. Castle - Day

/// The hero discovers their destiny
// A young farmer finds an ancient sword
/ The morning sun cast long shadows across the courtyard as {Hero}
  approached the mysterious {Sword} embedded in stone.
```

### Entity Definition Example

```cuneiform
@character Hero: A brave young farmer
@location Castle: An ancient fortress

@characters {
  Mentor: Wise old wizard
  Villain: Dark sorcerer
}
```

### Dialogue Example

```cuneiform
HERO: I must save the kingdom!
      (drawing sword)
      This ends now!

MENTOR: (nodding wisely)
        Your destiny awaits.
```

## Support

For questions or issues with semantic scopes:

1. Check this documentation first
2. Review examples in `examples/theming_showcase.cune`
3. Run validation: `python3 scripts/validate_scopes.py`
4. Open an issue with the `scopes` label

## See Also

- [README.md](README.md) - Grammar overview
- [queries/highlights.scm](queries/highlights.scm) - Scope definitions
- [examples/theming_showcase.cune](examples/theming_showcase.cune) - Live examples