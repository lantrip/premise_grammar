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

; Import statements
(import_statement) @keyword

; Adapter statements
(adapter_statement) @keyword

; Metadata
(metadata_line) @property

; Prose/narrative text  
(prose_line) @text