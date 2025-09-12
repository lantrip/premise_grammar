; Comments
(line_comment) @comment

; File headers (TITLE:, WORLD:, etc.)
(file_header) @keyword

; Act, Scene, and Cel headers
(act_header) @markup.heading.1
(scene_header) @markup.heading.2  
(cel_header) @markup.heading.3

; Header markers
(act_header "=" @punctuation.special)
(scene_header "==" @punctuation.special)
(cel_header "===" @punctuation.special)

; Content types and their markers
(content_type_beat) @keyword.control
(content_type_treatment) @keyword.control  
(content_type_narrative) @keyword.control

; Entity definitions - highlight all @ symbols and types
(entity_definition) @keyword
(entity_definition "@" @keyword)
(entity_definition entity_type: (_) @type)
(entity_definition name: (_) @variable.special)
(entity_definition description: (_) @string)

; Entity blocks
(entity_block_start) @keyword
(entity_block_start "@" @keyword)
(entity_block_start block_type: (_) @type)
(open_brace) @punctuation.bracket
(entity_block_end) @punctuation.bracket

; Block list items like "- Name: description"
(block_entity_item) @type.builtin
(block_entity_item "-" @punctuation)
(block_entity_item entity_name: (_) @type.builtin)
(block_entity_item ":" @punctuation)
(block_entity_item entity_desc: (_) @string)

; Block properties like "key: value"
(block_property) @property
(block_property prop_key: (_) @property)
(block_property ":" @punctuation)
(block_property prop_value: (_) @string)

; Nested blocks like "  @eras { ... }"
(nested_block) @keyword
(nested_block "@" @keyword)
(nested_block nested_type: (_) @type)

; Import statements
(import_statement) @keyword

; Adapter statements
(adapter_statement) @keyword

; Metadata
(metadata_line) @property

; Entity references in prose
(entity_reference) @variable.special
(ref_open) @punctuation.special
(ref_close) @punctuation.special

; Dialogue speakers
(dialogue_speaker) @character

; Parentheticals
(parenthetical) @comment.doc
(open_paren) @punctuation.bracket
(close_paren) @punctuation.bracket

; Prose/narrative text  
(prose_text) @text