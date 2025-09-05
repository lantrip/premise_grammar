; Indentation rules
(entity_block_start) @indent
(entity_block_end) @outdent

; Content under headers should be indented
(act_header) @indent
(scene_header) @indent
(cel_header) @indent

; Content type markers maintain current indentation
(content_type_beat) @auto
(content_type_treatment) @auto
(content_type_narrative) @auto