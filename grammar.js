// Tree-sitter grammar for Cuneiform
module.exports = grammar({
  name: "cuneiform",

  extras: ($) => [/[ \t]/, $.line_comment],

  conflicts: ($) => [
    [$.entity_block, $.entity_block_content],
    [$.nested_block, $.deeper_nested_block]
  ],

  rules: {
    source_file: ($) => repeat(choice($.line, $.entity_block, $.newline)),

    line: ($) =>
      choice(
        $.file_header,
        $.act_header,
        $.scene_header,
        $.cel_header,
        $.content_type_beat,
        $.content_type_treatment,
        $.content_type_narrative,
        $.entity_definition,
        $.import_statement,
        $.adapter_statement,
        $.metadata_line,
        $.prose_line
      ),

    line_comment: ($) => token(seq("#", /.*/)),

    file_header: ($) => prec(10, seq(
      field("key", token(/[A-Z][A-Z_]*/)),
      ":",
      optional(/\s+/),
      optional(field("value", /.*/))
    )),

    act_header: ($) =>
      prec(10, seq(
        token("="),
        /\s+/,
        field("title", /[^\r\n(]+/),
        optional(field("proportion", /\(\d+(?:\.\d+)?%\)/))
      )),

    scene_header: ($) =>
      prec(10, seq(
        token("=="),
        /\s+/,
        field("title", /[^\r\n(]+/),
        optional(field("proportion", /\(\d+(?:\.\d+)?%\)/))
      )),

    cel_header: ($) =>
      prec(10, seq(
        token("==="),
        /\s+/,
        field("title", /[^\r\n-]+/),
        optional(seq(
          "-",
          field("location_type", /[^\r\n-]+/),
          optional(seq("-", field("time", /[^\r\n()]+/)))
        )),
        optional(field("proportion", /\(\d+(?:\.\d+)?%\)/))
      )),

    // Enhanced content types with multi-line support and labels
    content_type_beat: ($) => 
      prec(9, seq(token("///"), optional(field("content", /.*/)))),
    
    content_type_treatment: ($) =>
      prec(9, seq(token("//"), optional(field("content", /.*/)))),
    
    content_type_narrative: ($) =>
      prec(9, seq(token("/"), optional(field("content", /.*/)))),

    entity_definition: ($) =>
      prec(8, seq(
        "@",
        field("entity_type", /\w+/),
        /\s+/,
        field("name", /[A-Za-z0-9][A-Za-z0-9\s]*[A-Za-z0-9]|[A-Za-z0-9]/),
        optional(seq(":", field("description", /.*/)))
      )),

    // Enhanced entity block support
    entity_block: ($) =>
      seq(
        $.entity_block_start,
        /\s*\r?\n/,
        repeat(choice(
          $.entity_block_content,
          $.nested_block,
          $.newline
        )),
        /\s*/,
        $.entity_block_end
      ),

    entity_block_start: ($) =>
      seq(
        "@",
        field("block_type", choice(
          "entities",
          "characters", 
          "locations",
          "items",
          "creatures",
          "eras",
          "world_eras"
        )),
        /\s*/,
        alias("{", $.open_brace)
      ),

    entity_block_end: ($) => alias("}", $.close_brace),

    entity_block_content: ($) => 
      choice(
        $.block_entity_item,
        $.block_property,
        $.block_comment
      ),

    block_entity_item: ($) =>
      choice(
        // Simple list item
        seq(
          /\s*/,
          "-",
          /\s*/,
          field("entity_name", /[^\r\n:{]+/),
          optional(seq(":", /\s*/, field("entity_desc", /[^\r\n{]+/))),
          /\r?\n/
        ),
        // List item with nested block
        seq(
          /\s*/,
          "-",
          /\s*/,
          field("entity_name", /[^\r\n:{]+/),
          /\s*:\s*/,
          alias("{", $.open_brace),
          /\s*\r?\n/,
          repeat(choice(
            seq(/\s+/, field("item_key", /\w+/), ":", /\s*/, field("item_value", /[^\r\n]+/), /\r?\n/),
            $.nested_block,
            $.block_comment,
            $.newline
          )),
          /\s*/,
          alias("}", $.close_brace),
          /\r?\n/
        )
      ),

    block_property: ($) =>
      seq(
        /\s+/,
        field("prop_key", /\w+/),
        ":",
        field("prop_value", /[^\r\n]+/),
        /\r?\n/
      ),

    block_comment: ($) => 
      seq(/\s*/, "#", /[^\r\n]*/, /\r?\n/),

    // Support for nested blocks like @eras with proper indentation
    nested_block: ($) =>
      seq(
        /\s*/,
        "@",
        field("nested_type", /\w+/),
        /\s*/,
        alias("{", $.open_brace),
        /\s*\r?\n/,
        repeat(choice(
          $.block_property,
          $.block_comment,
          $.deeper_nested_block,
          $.newline
        )),
        /\s*/,
        alias("}", $.close_brace)
      ),
    
    // Support deeply nested blocks
    deeper_nested_block: ($) =>
      seq(
        /\s+/,
        field("key", /\w+/),
        ":",
        /\s*/,
        alias("{", $.open_brace),
        /\s*\r?\n/,
        repeat(choice(
          seq(/\s+/, field("nested_key", /\w+/), ":", /\s*/, field("nested_value", /[^\r\n]+/), /\r?\n/),
          $.block_comment,
          $.newline
        )),
        /\s+/,
        alias("}", $.close_brace)
      ),

    import_statement: ($) =>
      prec(8, seq(
        "@import",
        /\s*/,
        optional(alias("(", $.open_paren)),
        choice(
          seq('"', field("path", /[^"]+/), '"'),
          seq("'", field("path", /[^']+/), "'")
        ),
        optional(seq(/\s+as\s+/, field("alias", /\w+/))),
        optional(alias(")", $.close_paren)),
        optional(seq(/\s*#/, field("selector", /[^\r\n]+/)))
      )),

    adapter_statement: ($) =>
      prec(8, seq(
        "@adapter",
        /\s+/,
        choice(
          seq(
            choice(
              seq('"', field("adapter_path", /[^"]+/), '"'),
              seq("'", field("adapter_path", /[^']+/), "'")
            ),
            optional(seq(/\s+@timing:/, field("timing", /\w+/)))
          ),
          seq(
            field("adapter_name", /\w+/),
            /\s*/,
            alias("{", $.open_brace)
          )
        )
      )),

    metadata_line: ($) => prec(7, seq(
      "@",
      field("meta_key", /\w+/),
      ":",
      field("meta_value", /.*/)
    )),

    // Enhanced prose line to handle entity references
    prose_line: ($) => 
      prec.right(1, seq(
        repeat1(choice(
          $.entity_reference,
          $.dialogue_speaker,
          $.parenthetical,
          $.prose_text
        ))
      )),

    entity_reference: ($) =>
      seq(
        alias("{", $.ref_open),
        field("entity", /[^}]+/),
        alias("}", $.ref_close)
      ),

    dialogue_speaker: ($) =>
      prec.left(seq(
        alias("{", $.ref_open),
        field("speaker", /[^}]+/),
        alias("}", $.ref_close),
        /\s*\r?\n/
      )),

    parenthetical: ($) =>
      seq(
        alias("(", $.open_paren),
        field("direction", /[^)]+/),
        alias(")", $.close_paren)
      ),

    prose_text: ($) => token(prec(-1, /[^\r\n{()}]+/)),

    newline: ($) => /\r?\n/,
  },
});