; Comments
(line_comment) @comment

; File headers (TITLE:, WORLD:, etc.)
(file_header) @keyword

; Act, Scene, and Cel headers
(act_header) @markup.heading
(scene_header) @markup.heading  
(cel_header) @markup.heading

; Content types
(content_type_beat) @markup.bold
(content_type_treatment) @markup.italic
(content_type_narrative) @string

; Entity definitions
(entity_definition) @keyword

; Entity blocks
(entity_block_start) @keyword
(entity_block_end) @punctuation.bracket

; Entity block content  
(block_entity_item) @type
(block_property) @property
(block_comment) @comment

; Bracket highlighting
(open_brace) @punctuation.bracket
(close_brace) @punctuation.bracket

; Nested blocks like @eras
(nested_block) @keyword

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