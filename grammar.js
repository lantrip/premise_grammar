// Tree-sitter grammar for Premise
module.exports = grammar({
  name: "premise",

  extras: ($) => [/[ \t]/, $.line_comment],

  conflicts: ($) => [],

  rules: {
    source_file: ($) => repeat(choice($.line, $.newline, $.line_comment)),

    // Entity block rule - handle balanced braces (like @eras {...})
    entity_block: ($) =>
      seq(
        "@",
        field(
          "block_type",
          choice(
            /characters?\s*\{/,
            /locations?\s*\{/,
            /items?\s*\{/,
            /adapters\s*\{/,
            /entities\s*\{/,
            /themes\s*\{/,
            /custom_metadata\s*\{/,
            /notes\s*\{/,
            /metadata\s*\{/,
            /display\s*\{/,
            /requirements\s*\{/,
            // Eras support
            /world_eras\s*\{/,
            /entity_eras\s*\{/,
            /character_eras\s*\{/,
            /location_eras\s*\{/,
            /eras\s*\{/
          )
        ),
        repeat(
          choice(
            prec(3, $.entity_line), // Highest precedence for structured entity lines
            $.balanced_braces, // Handle { ... } patterns
            prec(-1, /[^{}\-\s][^{}]*/), // Fallback: Content not starting with dash/whitespace
            $.newline // Allow newlines
          )
        ),
        "}"
      ),

    // Entity line for structured parsing within entity blocks
    // Supports either a simple description or a nested object value
    entity_line: ($) =>
      seq(
        /[ \t]*-\s+/, // Dash with surrounding whitespace
        field("entity_name", $.entity_name),
        ":",
        /[ \t]*/,
        choice(
          field("entity_desc", $.entity_desc),
          field("entity_object", $.entity_object)
        )
      ),

    // Match balanced braces for nested patterns like @eras { ... }
    balanced_braces: ($) =>
      seq(
        "{",
        repeat(
          choice(
            $.balanced_braces, // Recursive for deeper nesting
            /[^{}]+/, // Content between braces
            $.newline
          )
        ),
        "}"
      ),

    // Entity object value: { key: value, ... } with one property per line
    entity_object: ($) =>
      seq(
        alias("{", $.open_brace),
        repeat(
          choice(
            $.object_property,
            $.adapter_list_property,
            $.block_comment,
            $.newline
          )
        ),
        alias("}", $.close_brace)
      ),

    // Property inside an entity object value
    object_property: ($) =>
      seq(
        /[ \t]*/,
        field("prop_key", $.prop_key),
        ":",
        /[ \t]*/,
        field("prop_value", $.prop_value)
      ),

    // Entity definition only (not unified anymore)
    entity_construct: ($) =>
      prec.dynamic(
        10,
        seq(
          "@",
          field("entity_type", /\w+/),
          /\s+/,
          field("name", /[A-Za-z0-9]+(?:\s+[A-Za-z0-9]+)*/), // Allow multi-word names
          ":",
          optional(/\s*/),
          field("description", /.+/)
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
        $.metadata_line,
        $.entity_construct, // Entity definitions
        $.entity_block, // Entity blocks with braces
        $.import_statement,
        $.adapter_statement,
        $.prose_line // Last resort - lowest precedence
      ),

    line_comment: ($) => token(seq("#", /.*/)),

    file_header: ($) =>
      prec(
        100, // Very high precedence
        seq(
          field("key", /[A-Z][A-Z_]*/), // One or more uppercase letters
          ":",
          optional(/\s+/),
          optional(field("value", /[^\r\n]+/))
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

    block_comment: ($) => seq(/\s*/, "#", /[^\r\n]*/),

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
      choice(
        // External adapter reference: @adapter "path": value
        prec(
          12,
          seq(
            token.immediate(seq("@", "adapter")),
            /\s+/,
            choice(
              seq('"', field("adapter_path", $.adapter_path), '"'),
              seq("'", field("adapter_path", $.adapter_path), "'")
            ),
            /\s*/,
            ":",
            /\s*/,
            field("adapter_spec", $.prop_value)
          )
        ),
        // Named inline adapter: @adapter name: { ... }
        prec(
          11,
          seq(
            token.immediate(seq("@", "adapter")),
            /\s+/,
            field("adapter_name", $.adapter_name),
            /\s*/,
            ":",
            /\s*/,
            $.object_value
          )
        )
      ),


    // Adapter list item property: dash-prefixed key-value
    adapter_list_property: ($) =>
      seq(
        /[ \t]*-\s+/,
        field("prop_key", $.prop_key),
        ":",
        /[ \t]*/,
        field("prop_value", $.prop_value)
      ),

    metadata_line: ($) =>
      prec(
        7, // Standard precedence, no conflicts with @ syntax
        seq("+", field("meta_key", /\w+/), ":", field("meta_value", /.*/))
      ),

    // Enhanced prose line to handle entity references (single line only)
    prose_line: ($) =>
      prec(
        -1,
        choice(
          // Standalone dialogue speaker (consumes newline)
          $.dialogue_speaker,
          // Mixed content on single line (no newlines)
          seq(
            repeat1(choice($.entity_reference, $.parenthetical, $.prose_text))
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

    prose_text: ($) => prec(-10, /[^\r\n{}()=@+\/]+/),

    newline: ($) => /\r?\n/,

    // Named tokens for entity parts
    entity_name: ($) => /[A-Za-z_][A-Za-z0-9_ ]*/,
    entity_desc: ($) => /[^\r\n{}]+/,
    prop_key: ($) => /[a-z_][a-z_0-9]*/,
    // Generic value for properties: supports inline simple values, nested objects, and YAML-style block scalars
    prop_value: ($) => choice($.object_value, $.block_scalar, $.simple_value),

    // Inline simple scalar (single line, no braces)
    simple_value: ($) => /[^\r\n{}]+/,

    // Object value reused across adapters and entities
    object_value: ($) =>
      seq(
        alias("{", $.open_brace),
        repeat(
          choice(
            $.object_property,
            $.adapter_list_property,
            $.block_comment,
            $.newline
          )
        ),
        alias("}", $.close_brace)
      ),

    // YAML-style block scalar: key: |\n  indented text...
    block_scalar: ($) =>
      seq("|", optional(/[ \t]*/), $.newline, repeat1($.indented_text_line)),

    indented_text_line: ($) => seq(/[ \t]+/, /[^\r\n]*/, $.newline),
    adapter_name: ($) => /[A-Za-z_][A-Za-z0-9_]*/,
    adapter_path: ($) => /[^"']+/,
    adapter_timing: ($) => /[A-Za-z_][A-Za-z0-9_]*/,
  },
});
