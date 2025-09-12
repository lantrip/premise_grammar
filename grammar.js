// Tree-sitter grammar for Cuneiform
module.exports = grammar({
  name: "cuneiform",

  extras: ($) => [/[ \t]/, $.line_comment],

  conflicts: ($) => [[$.entity_block, $.entity_block_content]],

  rules: {
    source_file: ($) =>
      repeat(
        choice(
          $.line,
          $.entity_block,
          $.simple_entity_block,
          $.newline,
          $.line_comment
        )
      ),

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

    file_header: ($) =>
      prec(
        10,
        seq(
          field("key", /[A-Z][A-Z_]*/),
          ":",
          optional(/\s+/),
          optional(field("value", /.*/))
        )
      ),

    act_header: ($) =>
      prec(
        10,
        seq(
          "=",
          /\s+/,
          field("title", /[^\r\n(]+/),
          optional(field("proportion", /\(\d+(?:\.\d+)?%\)/))
        )
      ),

    scene_header: ($) =>
      prec(
        10,
        seq(
          "==",
          /\s+/,
          field("title", /[^\r\n(]+/),
          optional(field("proportion", /\(\d+(?:\.\d+)?%\)/))
        )
      ),

    cel_header: ($) =>
      prec(
        10,
        seq(
          "===",
          /\s+/,
          field("title", /[^\r\n-]+/),
          optional(
            seq(
              "-",
              field("location_type", /[^\r\n-]+/),
              optional(seq("-", field("time", /[^\r\n()]+/)))
            )
          ),
          optional(field("proportion", /\(\d+(?:\.\d+)?%\)/))
        )
      ),

    // Enhanced content types with multi-line support and labels
    content_type_beat: ($) =>
      prec.right(9, seq("///", optional(field("content", /.*/)))),

    content_type_treatment: ($) =>
      prec.right(9, seq("//", optional(field("content", /.*/)))),

    content_type_narrative: ($) =>
      prec.right(9, seq("/", optional(field("content", /.*/)))),

    entity_definition: ($) =>
      prec(
        8,
        seq(
          "@",
          field("entity_type", /\w+/),
          /\s+/,
          field("name", /[A-Za-z0-9][A-Za-z0-9\s]*[A-Za-z0-9]|[A-Za-z0-9]/),
          optional(seq(":", field("description", /.*/)))
        )
      ),

    // Enhanced entity block support
    entity_block: ($) =>
      seq(
        $.entity_block_start,
        repeat(
          choice(
            $.entity_block_content,
            $.nested_block,
            $.newline,
            /[^\r\n{}]+/ // Accept any content that's not braces or newlines
          )
        ),
        $.entity_block_end
      ),

    entity_block_start: ($) =>
      seq(
        "@",
        field("block_type", /[A-Za-z_][A-Za-z0-9_]*/),
        /\s*/,
        alias("{", $.open_brace)
      ),

    entity_block_end: ($) => alias("}", $.close_brace),

    entity_block_content: ($) =>
      choice(
        $.block_entity_item,
        $.block_property,
        $.block_comment,
        $.nested_block
      ),

    block_entity_item: ($) =>
      seq(
        /[ \t]*/,
        "-",
        /[ \t]+/,
        field("entity_name", /[A-Za-z][A-Za-z0-9 ]*/),
        ":",
        /[ \t]*/,
        field("entity_desc", /[^\r\n]+/)
      ),

    block_property: ($) =>
      seq(
        /[ \t]+/,
        field("prop_key", /[a-z_][a-z_0-9]*/),
        ":",
        /[ \t]*/,
        field("prop_value", /[^\r\n]+/)
      ),

    block_comment: ($) => seq(/\s*/, "#", /[^\r\n]*/),

    // Support for nested blocks like @eras with proper indentation
    nested_block: ($) =>
      prec.right(
        seq(
          /\s+/, // Must be indented
          "@",
          field("nested_type", /\w+/),
          /\s*/,
          alias("{", $.open_brace),
          repeat(
            choice(
              $.block_property,
              $.block_comment,
              $.deeper_nested_block,
              $.newline
            )
          ),
          optional(/\s+/), // Closing brace may or may not be indented
          alias("}", $.close_brace)
        )
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
        repeat(
          choice(
            seq(
              /\s+/,
              field("nested_key", /\w+/),
              ":",
              /\s*/,
              field("nested_value", /[^\r\n]+/),
              /\r?\n/
            ),
            $.block_comment,
            $.newline
          )
        ),
        /\s+/,
        alias("}", $.close_brace)
      ),

    import_statement: ($) =>
      prec(
        8,
        seq(
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
        )
      ),

    adapter_statement: ($) =>
      prec(
        8,
        seq(
          "@adapter",
          /\s+/,
          choice(
            // External adapter reference
            seq(
              choice(
                seq('"', field("adapter_path", /[^"]+/), '"'),
                seq("'", field("adapter_path", /[^']+/), "'")
              ),
              optional(seq(/\s+@timing:/, field("timing", /\w+/)))
            ),
            // Inline adapter definition
            $.adapter_inline_block
          )
        )
      ),

    adapter_inline_block: ($) =>
      seq(
        field("adapter_name", /\w+/),
        /\s*/,
        alias("{", $.open_brace),
        optional(/\s*\r?\n/),
        repeat(choice($.adapter_property, $.adapter_nested_block, $.newline)),
        optional(/\s*/),
        alias("}", $.close_brace)
      ),

    adapter_property: ($) =>
      seq(
        /\s+/,
        field("key", /\w+/),
        ":",
        optional(/\s*/),
        field("value", /[^\r\n]+/)
      ),

    adapter_nested_block: ($) =>
      prec.right(
        seq(
          /\s+/,
          field("block_key", /\w+/),
          ":",
          repeat(
            seq(
              /\s+/,
              "-",
              /\s*/,
              field("list_key", /\w+/),
              ":",
              optional(/\s*/),
              field("list_value", /[^\r\n]+/)
            )
          )
        )
      ),

    metadata_line: ($) =>
      prec(
        7,
        seq("@", field("meta_key", /\w+/), ":", field("meta_value", /.*/))
      ),

    // Enhanced prose line to handle entity references
    prose_line: ($) =>
      prec(
        -1,
        seq(
          repeat1(
            choice(
              $.entity_reference,
              $.dialogue_speaker,
              $.parenthetical,
              $.prose_text
            )
          )
        )
      ),

    entity_reference: ($) =>
      seq(
        alias("{", $.ref_open),
        field("entity", /[^}]+/),
        alias("}", $.ref_close)
      ),

    dialogue_speaker: ($) =>
      prec.left(
        seq(
          alias("{", $.ref_open),
          field("speaker", /[^}]+/),
          alias("}", $.ref_close),
          /\s*\r?\n/
        )
      ),

    parenthetical: ($) =>
      seq(
        alias("(", $.open_paren),
        field("direction", /[^)]+/),
        alias(")", $.close_paren)
      ),

    prose_text: ($) => token(prec(-1, /[^\r\n{()}]+/)),

    simple_entity_block: ($) =>
      seq(
        "@",
        /\w+/,
        /\s*/,
        "{",
        repeat(choice(/[^{}]+/, $.simple_entity_block, /\r?\n/)),
        "}"
      ),

    newline: ($) => /\r?\n/,
  },
});
