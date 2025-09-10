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

; Content type text
(content_type_beat content: (_) @markup.bold)
(content_type_treatment content: (_) @markup.italic)
(content_type_narrative content: (_) @string)

; Entity definitions - highlight all @ symbols and types
(entity_definition) @keyword
(entity_definition "@" @keyword)
(entity_definition entity_type: (_) @type)
(entity_definition name: (_) @variable.special)
(entity_definition description: (_) @string)

; Entity blocks - highlight all @ symbols and block types
(entity_block_start) @keyword  
(entity_block_start "@" @keyword)
(entity_block_start block_type: (_) @type)
(entity_block_end) @punctuation.bracket

; Entity block content  
(block_entity_item entity_name: (_) @type.builtin)
(block_entity_item entity_desc: (_) @string)
(block_property prop_key: (_) @property)
(block_property prop_value: (_) @string)
(block_comment) @comment

; Bracket highlighting
(open_brace) @punctuation.bracket
(close_brace) @punctuation.bracket

; Nested blocks like @eras - highlight all @ symbols
(nested_block) @keyword
(nested_block "@" @keyword)
(nested_block nested_type: (_) @type)
(deeper_nested_block key: (_) @property)
(deeper_nested_block nested_key: (_) @property)
(deeper_nested_block nested_value: (_) @string)

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