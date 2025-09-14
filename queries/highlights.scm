; Cuneiform Syntax Highlighting
; Simplified version without field references

; Comments
(line_comment) @comment

; File headers
(file_header) @keyword.control

; Structure headers
(act_header) @markup.heading.1
(scene_header) @markup.heading.2  
(cel_header) @markup.heading.3

; Header markers
"=" @punctuation.special
"==" @punctuation.special
"===" @punctuation.special

; Content type markers
(content_type_beat) @keyword.control
(content_type_treatment) @keyword.control  
(content_type_narrative) @keyword.control

"///" @punctuation.special
"//" @punctuation.special
"/" @punctuation.special

; Entity definitions
(entity_construct) @variable.special
"@" @punctuation.special

; Entity blocks
(entity_block) @type

; Nested blocks (handled by balanced_braces)
(balanced_braces) @type

; Note: @eras blocks are parsed as entity_block, not nested_block
; Specific eras highlighting is handled by the entity_block rule above

; Import and adapter statements
(import_statement) @keyword.import
(adapter_statement) @keyword

; Metadata
(metadata_line) @property

; Entity references
(entity_reference) @variable.special
(ref_open) @punctuation.special
(ref_close) @punctuation.special

; Dialogue and prose
(dialogue_speaker) @character
(parenthetical) @comment.doc
(prose_text) @text

; Punctuation
":" @punctuation.delimiter
"{" @punctuation.bracket
"}" @punctuation.bracket
"-" @punctuation.special

; Error recovery
(ERROR) @error