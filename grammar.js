// Tree-sitter grammar for Cuneiform
module.exports = grammar({
  name: "cuneiform",

  extras: ($) => [/[ \t]/],

  rules: {
    source_file: ($) => repeat(choice($.line, $.newline)),

    line: ($) =>
      choice(
        $.line_comment,
        $.file_header,
        $.act_header,
        $.scene_header,
        $.cel_header,
        $.content_type_beat,
        $.content_type_treatment,
        $.content_type_narrative,
        $.entity_definition,
        $.entity_block_start,
        $.entity_block_end,
        $.import_statement,
        $.adapter_statement,
        $.metadata_line,
        $.prose_line
      ),

    line_comment: ($) => seq("#", /.*/),

    file_header: ($) => seq(/[A-Z][A-Z_]{1,}/, ":", /.*/),

    act_header: ($) =>
      seq("=", /\s+/, /[^\r\n(]+/, optional(/\(\d+(?:\.\d+)?%\)/)),

    scene_header: ($) =>
      seq("==", /\s+/, /[^\r\n(]+/, optional(/\(\d+(?:\.\d+)?%\)/)),

    cel_header: ($) =>
      seq(
        "===",
        /\s+/,
        /[^\r\n-]+/,
        optional(seq("-", /[^\r\n-]+/, optional(seq("-", /[^\r\n()]+/)))),
        optional(/\(\d+(?:\.\d+)?%\)/)
      ),

    content_type_beat: ($) => seq("///", /.*/),
    content_type_treatment: ($) => seq("//", /.*/),
    content_type_narrative: ($) => seq("/", /.*/),

    entity_definition: ($) =>
      seq(
        "@",
        /\w+/,
        /\s+/,
        /[A-Za-z0-9][A-Za-z0-9\s]*[A-Za-z0-9]|[A-Za-z0-9]/,
        optional(seq(":", /.*/))
      ),

    entity_block_start: ($) => seq("@", /\w+s?/, /\s*/, "{"),
    entity_block_end: ($) => "}",

    import_statement: ($) =>
      seq(
        "@import",
        /\s*/,
        optional("("),
        choice(seq('"', /[^"]+/, '"'), seq("'", /[^']+/, "'")),
        optional(seq(/\s+as\s+/, /\w+/)),
        optional(")"),
        optional(seq(/\s*#/, /[^\r\n]+/))
      ),

    adapter_statement: ($) =>
      seq(
        "@adapter",
        /\s+/,
        choice(
          seq(
            choice(seq('"', /[^"]+/, '"'), seq("'", /[^']+/, "'")),
            optional(seq(/\s+@timing:/, /\w+/))
          ),
          seq(/\w+/, /\s*/, "{")
        )
      ),

    metadata_line: ($) => seq("@", /\w+/, ":", /.*/),

    prose_line: ($) => /[^\r\n=@/#][^\r\n]*/,

    newline: ($) => /\r?\n/,
  },
});
