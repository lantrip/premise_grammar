; Cuneiform Syntax Highlighting for Zed
; Using Zed-compatible scopes

; Comments
(line_comment) @comment

; File headers - prominent keywords
(file_header) @keyword

; Structure headers - using title for prominence
(act_header) @title
(scene_header) @title
(cel_header) @title

; Content type markers - keywords for story layers
(content_type_beat) @keyword
(content_type_treatment) @keyword
(content_type_narrative) @keyword

; Entity constructs - single line definitions
(entity_construct) @type

; Entity blocks - the @ symbol and type should be highlighted as keywords
(entity_block) @function

; Nested blocks (content within braces)
(balanced_braces) @string

; Import and adapter statements
(import_statement) @keyword
(adapter_statement) @keyword

; Metadata lines
(metadata_line) @property

; Entity references - character/location names
(entity_reference) @variable.special

; Reference punctuation
(ref_open) @punctuation.bracket
(ref_close) @punctuation.bracket

; Dialogue speakers
(dialogue_speaker) @emphasis.strong

; Parentheticals (stage directions)
(parenthetical) @comment

; Parenthetical punctuation
(open_paren) @punctuation.bracket
(close_paren) @punctuation.bracket

; Prose content
(prose_line) @text
(prose_text) @text

; Error recovery
(ERROR) @error