// Tree-sitter grammar for Cuneiform
module.exports = grammar({
  name: "cuneiform",

  extras: ($) => [/[ \t]/, $.line_comment],

  conflicts: ($) => [
    [$.entity_block, $.entity_block_content]
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

    file_header: ($) => seq(
      field("key", /[A-Z][A-Z_]{1,}/),
      ":",
      field("value", /.*/)
    ),

    act_header: ($) =>
      seq(
        "=",
        /\s+/,
        field("title", /[^\r\n(]+/),
        optional(field("proportion", /\(\d+(?:\.\d+)?%\)/))
      ),

    scene_header: ($) =>
      seq(
        "==",
        /\s+/,
        field("title", /[^\r\n(]+/),
        optional(field("proportion", /\(\d+(?:\.\d+)?%\)/))
      ),

    cel_header: ($) =>
      seq(
        "===",
        /\s+/,
        field("title", /[^\r\n-]+/),
        optional(seq(
          "-",
          field("location_type", /[^\r\n-]+/),
          optional(seq("-", field("time", /[^\r\n()]+/)))
        )),
        optional(field("proportion", /\(\d+(?:\.\d+)?%\)/))
      ),

    content_type_beat: ($) => seq("///", field("content", /.*/)),
    content_type_treatment: ($) => seq("//", field("content", /.*/)),
    content_type_narrative: ($) => seq("/", field("content", /.*/)),

    entity_definition: ($) =>
      seq(
        "@",
        field("entity_type", /\w+/),
        /\s+/,
        field("name", /[A-Za-z0-9][A-Za-z0-9\s]*[A-Za-z0-9]|[A-Za-z0-9]/),
        optional(seq(":", field("description", /.*/)))
      ),

    // Enhanced entity block support
    entity_block: ($) =>
      seq(
        $.entity_block_start,
        repeat(choice(
          $.entity_block_content,
          $.nested_block,
          $.newline
        )),
        $.entity_block_end
      ),

    entity_block_start: ($) =>
      seq(
        "@",
        field("block_type", /\w+s?/),
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
      seq(
        /\s*/,
        "-",
        /\s*/,
        field("entity_name", /[^\r\n:]+/),
        optional(seq(":", field("entity_desc", /[^\r\n]+/))),
        /\r?\n/
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

    // Support for nested blocks like @eras
    nested_block: ($) =>
      seq(
        /\s*/,
        "@",
        field("nested_type", /\w+/),
        /\s*/,
        alias("{", $.open_brace),
        repeat(choice(
          $.block_property,
          $.block_comment,
          $.newline
        )),
        /\s*/,
        alias("}", $.close_brace)
      ),

    import_statement: ($) =>
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
      ),

    adapter_statement: ($) =>
      seq(
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
      ),

    metadata_line: ($) => seq(
      "@",
      field("meta_key", /\w+/),
      ":",
      field("meta_value", /.*/)
    ),

    // Enhanced prose line to handle entity references
    prose_line: ($) => 
      prec.right(seq(
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

    prose_text: ($) => /[^\r\n{()}]+/,

    newline: ($) => /\r?\n/,
  },
});