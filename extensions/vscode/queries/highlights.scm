; Cuneiform Syntax Highlighting
; Simplified version without field references

; Comments - distinguish from story content
(line_comment) @comment.line

; File headers - metadata about the story
(file_header) @keyword.directive

; Structure headers - story organization
(act_header) @markup.heading.1.story.act
(scene_header) @markup.heading.2.story.scene
(cel_header) @markup.heading.3.story.cel

; Header markers - visual hierarchy
"=" @punctuation.definition.heading.story.act
"==" @punctuation.definition.heading.story.scene
"===" @punctuation.definition.heading.story.cel

; Content type markers - story layer indicators
(content_type_beat) @keyword.control.content.beat
(content_type_treatment) @keyword.control.content.treatment
(content_type_narrative) @keyword.control.content.narrative

; Content type punctuation - visual cues for story layers
"///" @punctuation.definition.content.beat
"//" @punctuation.definition.content.treatment
"/" @punctuation.definition.content.narrative

; Entity definitions
(entity_construct) @variable.special
"@" @punctuation.special

; Entity blocks
(entity_block) @type

; Entity lines within blocks - structured parsing
; Note: Field-level highlighting of entity_name/entity_desc requires
; more complex grammar rules with separate node types
(entity_line) @variable.definition.entity
; New: differentiate entity name vs value in list items
(entity_line (entity_name) @entity.name.definition)
(entity_line (entity_desc) @string.description.entity)
(entity_line ":" @punctuation.separator.entity)

; New: object values for nested entity properties
(entity_line (entity_object) @meta.object.entity)
(entity_object (open_brace) @punctuation.bracket)
(entity_object (close_brace) @punctuation.bracket)
(object_property (prop_key) @property.entity)
(object_property (prop_value) @string.description.entity)

; Nested blocks (handled by balanced_braces)
(balanced_braces) @type

; Note: @eras blocks are parsed as entity_block, not nested_block
; Specific eras highlighting is handled by the entity_block rule above

; Import and adapter statements
(import_statement) @keyword.import
(adapter_statement) @keyword

; Metadata
(metadata_line) @meta.property

; Entity references - character/location/item names in story
(entity_reference) @entity.name.reference

; Contextual entity references - more specific scoping for prose/narrative
(prose_line (entity_reference) @entity.name.reference.prose)
(prose_line (entity_reference (ref_open) @punctuation.definition.entity.begin.prose))
(prose_line (entity_reference (ref_close) @punctuation.definition.entity.end.prose))

; Generic entity reference punctuation (fallback)
(ref_open) @punctuation.definition.entity.begin
(ref_close) @punctuation.definition.entity.end

; Story content - different types of narrative text
(prose_line) @text.prose.line
(dialogue_speaker) @entity.name.character.speaker
(parenthetical) @text.parenthetical
(prose_text) @text.narrative

; Parenthetical punctuation - specific to dialogue/prose
(open_paren) @punctuation.definition.parenthetical.begin
(close_paren) @punctuation.definition.parenthetical.end

; General punctuation
":" @punctuation.delimiter
"{" @punctuation.bracket
"}" @punctuation.bracket
"-" @punctuation.special

; Error recovery
(ERROR) @error