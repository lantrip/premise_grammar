// Tree-sitter grammar for Premise
module.exports = grammar({
  name: "premise",

  extras: ($) => [/[ \t]/, $.line_comment, $.block_comment],

  conflicts: ($) => [[$.block_free_line]],

  rules: {
    source_file: ($) => repeat(choice($.line, $.newline, $.line_comment, $.block_comment)),

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
            /eras\s*\{/,
            // World-building entity types
            /concepts?\s*\{/,
            /organizations?\s*\{/,
            /events?\s*\{/,
            /relationships?\s*\{/,
            /factions?\s*\{/
          )
        ),
        repeat(
          choice(
            prec(3, $.entity_line), // Highest precedence for structured entity lines
            prec(2, $.block_free_line), // Entity-reference lines (relationships)
            $.balanced_braces, // Handle { ... } patterns
            prec(-1, /[^{}\-\s][^{}]*/), // Fallback: Content not starting with dash/whitespace
            $.newline // Allow newlines
          )
        ),
        "}"
      ),

    // Lore/facts block - free-text entries that don't require Name: Description format
    // Supports: "- Free text content", "- Label: Description", and "- {Entity} reference lines"
    lore_block: ($) =>
      seq(
        "@",
        field(
          "block_type",
          choice(
            /lore\s*\{/,
            /facts?\s*\{/
          )
        ),
        repeat(
          choice(
            prec(2, $.block_free_line), // Entity-reference lines
            prec(1, $.lore_entry), // Free-text lore/fact entries
            $.newline
          )
        ),
        "}"
      ),

    // Cast block — maps premise/template roles to concrete entity references.
    // e.g. @cast { protagonist: {world.entities.characters[0]} }. Distinct from
    // entity_block because its body is `role: {reference}` lines (no dash, the
    // value is a reference rather than a description/object).
    cast_block: ($) =>
      seq(
        "@",
        field("block_type", /cast\s*\{/),
        repeat(
          choice(
            $.cast_line,
            $.newline
          )
        ),
        "}"
      ),

    // One role→reference mapping line inside @cast { }. The reference may carry
    // a dotted/indexed path (e.g. {world.entities.characters[0]}); entity_reference
    // captures everything up to the closing brace. Leading/inner spaces are
    // handled by `extras` — an explicit `/[ \t]*/` here would match a zero-width
    // token and trap the parser in cast_line on blank/closing lines.
    cast_line: ($) =>
      seq(
        field("cast_role", $.prop_key),
        ":",
        field("cast_ref", $.entity_reference)
      ),

    // Lore entry: "- Free text content" (any text, colons allowed)
    lore_entry: ($) =>
      seq(
        /[ \t]*-\s+/, // Dash with surrounding whitespace
        field("lore_text", $.lore_text)
      ),

    // Lore text content - captures entire line including colons
    lore_text: ($) => /[^\r\n{}]+/,

    // Template block for abstract story templates with role definitions
    // @template { @premise: {Slot} sentence  @role Name [type, flags]: description }
    template_block: ($) =>
      seq(
        "@",
        field("block_type", /template\s*\{/),
        repeat(
          choice(
            prec(4, $.premise_line), // Guided premise sentence(s)
            prec(3, $.role_line), // Role / slot definitions
            $.newline
          )
        ),
        "}"
      ),

    // Premise line within template block: @premise: {Slot} text {Slot} …
    // The guided premise sentence; {Slot} tokens reference @role names.
    premise_line: ($) =>
      seq(
        /[ \t]*@premise\s*/,
        ":",
        /[ \t]*/,
        field("premise_body", $.premise_body)
      ),

    // Premise body: interleaved slot references and free text
    premise_body: ($) => repeat1(choice($.entity_reference, $.premise_text)),

    // Free text between premise slot references (no braces, single line)
    premise_text: ($) => /[^\r\n{}]+/,

    // Image block for grouping image associations with rich metadata
    // @images { - Target [tags]: path | caption }
    image_block: ($) =>
      seq(
        token.immediate(seq("@", "images")),
        /\s*\{/,
        repeat(
          choice(
            prec(3, $.image_line), // Image association lines
            $.block_comment,
            $.newline
          )
        ),
        "}"
      ),

    // Image line within @images block: - Target [tags]: path | caption
    image_line: ($) =>
      seq(
        /[ \t]*-\s+/,
        field("image_target", $.image_target),
        optional(field("image_tags", $.image_tags)),
        ":",
        /[ \t]*/,
        field("image_path", $.image_path),
        optional(seq($.image_pipe, field("image_caption", $.image_caption)))
      ),

    // Image target name (entity, scene, or label)
    image_target: ($) => /[A-Za-z_][A-Za-z0-9_' ]*/,

    // Optional bracket tags: [portrait, close-up]
    image_tags: ($) => seq("[", field("tags", /[^\]]+/), "]"),

    // Image file path (everything up to | or end of line, trimmed)
    image_path: ($) => /[^\r\n|]+/,

    // Pipe separator for caption
    image_pipe: ($) => "|",

    // Image caption (rest of line after |)
    image_caption: ($) => /[^\r\n]+/,

    // Role line within template block: @role Name [type]: Description
    role_line: ($) =>
      seq(
        /[ \t]*@role\s+/,
        field("role_name", $.role_name),
        optional(field("role_type", $.role_type_hint)),
        ":",
        /[ \t]*/,
        field("role_desc", $.role_desc)
      ),

    // Role name (similar to entity name)
    role_name: ($) => /[A-Za-z_][A-Za-z0-9_]*/,

    // Optional type hint in brackets with optional flags:
    //   [character]  [character, required]  [item, optional]  [text]
    // First token is the entity type; subsequent comma-separated tokens are
    // slot flags (required | optional | text | …).
    // Note: no leading /\s*/ — extras handle inter-token whitespace
    role_type_hint: ($) =>
      seq(
        "[",
        field("type", /[a-z]+/),
        repeat(seq(",", field("flag", /[a-z]+/))),
        "]"
      ),

    // Role description (rest of line)
    role_desc: ($) => /[^\r\n]+/,

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

    // Free-form line in entity blocks for relationship patterns with entity references
    // e.g., - {Entity1} mentors {Entity2}
    // Must start with entity reference (disambiguates from entity_line via initial token)
    block_free_line: ($) =>
      seq(
        /[ \t]*-\s+/, // Dash with surrounding whitespace
        $.entity_reference, // Must start with {Name}
        repeat(
          choice(
            $.entity_reference, // More {Name} references
            $.entity_name // Text between references
          )
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
    // Supports optional parenthetical alias: @character Hero (The Chosen One): Description
    entity_construct: ($) =>
      prec.dynamic(
        10,
        seq(
          "@",
          field("entity_type", /\w+/),
          /\s+/,
          field("name", /[A-Za-z0-9']+(?:\s+[A-Za-z0-9']+)*/), // Allow multi-word names with apostrophes
          optional(seq(/\s+/, $.entity_alias)), // Optional alias with required space before
          ":",
          optional(/\s*/),
          field("description", /.+/)
        )
      ),

    // Inline image association: @image Target [tags]: path/to/image.png | optional caption
    // Uses token.immediate to create a single @image token (like @adapter)
    // Description field contains "path | caption" or just "path" - service layer splits on |
    image_construct: ($) =>
      prec(
        12,
        seq(
          token.immediate(seq("@", "image")),
          /\s+/,
          field("name", /[A-Za-z0-9]+(?:\s+[A-Za-z0-9]+)*/),
          optional(field("image_tags", $.image_tags)),
          ":",
          optional(/\s*/),
          field("description", /.+/)
        )
      ),

    // Parenthetical alias for entities: (The Chosen One)
    entity_alias: ($) =>
      seq("(", field("alias", /[^)]+/), ")"),

    line: ($) =>
      choice(
        $.file_header,
        $.act_header,
        $.scene_header,
        $.cel_header,
        $.content_type_beat,
        $.content_type_treatment,
        $.content_type_narrative,
        $.graveyard_prose, // Single-line graveyard: ^~ <prose>
        $.metadata_line,
        $.image_construct, // Inline image associations (before entity_construct)
        $.entity_construct, // Entity definitions
        $.entity_block, // Entity blocks with braces
        $.cast_block, // @cast { role: {Entity} } mapping blocks
        $.lore_block, // Lore/facts blocks with free-text entries
        $.template_block, // Template blocks with role definitions
        $.image_block, // Image association blocks
        $.import_statement,
        $.adapter_statement,
        $.prose_line // Last resort - lowest precedence
      ),

    line_comment: ($) => token(seq("//", /.*/)),

    file_header: ($) =>
      prec(
        100, // Very high precedence
        seq(
          field("key", alias(/[A-Z][A-Z_]*/, $.file_header_key)), // Named sub-node for highlighting
          ":",
          optional(/\s+/),
          optional(
            choice(
              field("block", $.block_scalar), // KEY: |\n  indented multiline...
              field("value", alias(/[^\r\n]+/, $.file_header_value)) // Single-line value
            )
          )
        )
      ),

    // Named node types for file header parts (used via alias for highlighting differentiation)
    file_header_key: ($) => /[A-Z][A-Z_]*/,
    file_header_value: ($) => /[^\r\n]+/,

    // `~` prefix on a header marks it (and its subtree, by the existing
    // nesting rules) as a graveyard region — visible in the source but
    // excluded from lens / KB extraction. High token precedence so the
    // lexer prefers it over `prose_text` when a line starts with `~`.
    graveyard_marker: ($) => token(prec(20, "~")),

    act_header: ($) =>
      prec(
        10,
        seq(
          optional(field("graveyard", $.graveyard_marker)),
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
          optional(field("graveyard", $.graveyard_marker)),
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
          optional(field("graveyard", $.graveyard_marker)),
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
    // Ordinality matches structure: # (beat/abstract) → ## (treatment) → ### (narrative/detailed)
    content_type_beat: ($) =>
      prec.right(
        9,
        seq(
          optional(field("graveyard", $.graveyard_marker)),
          "#",
          optional(field("content", /.*/))
        )
      ),

    content_type_treatment: ($) =>
      prec.right(
        9,
        seq(
          optional(field("graveyard", $.graveyard_marker)),
          "##",
          optional(field("content", /.*/))
        )
      ),

    content_type_narrative: ($) =>
      prec.right(
        9,
        seq(
          optional(field("graveyard", $.graveyard_marker)),
          "###",
          optional(field("content", /.*/))
        )
      ),

    // Single-line graveyard prose: `^~ <prose>`. The whole line is dead but
    // does not open or close any structural region. Matched as a single
    // high-precedence token so:
    //   - `~ killed` matches the entire line as one graveyard_prose node
    //   - `~just` (no space) does NOT match — the lexer falls back to the
    //     `~` marker token, which the surrounding context tries to attach
    //     to a header. If neither path applies (mid-prose `~`), the existing
    //     prose_text rule still consumes the `~` because it's not excluded.
    graveyard_prose: ($) => token(prec(20, /~ [^\r\n]*/)),

    // Multi-line C-style block comments
    block_comment: ($) =>
      token(seq("/*", /[^*]*\*+([^/*][^*]*\*+)*/, "/")),

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
          optional(seq(/\s*\/\//, field("selector", /[^\r\n]+/)))
        )
      ),

    // One unified @adapter statement. The target is a quoted external path OR
    // an unquoted name; the suffix is either `: <spec>` (the spec, via
    // `prop_value`, may be a simple value, an inline/multiline object, or a
    // block scalar) or one-or-more `key=value` args. Folding both targets and
    // both suffixes into a single rule (choices after a shared prefix) lets GLR
    // disambiguate on lookahead — separate prec-ranked rules pruned branches and
    // the named form's `object_value` was unreachable. Spaces around `:` and
    // between args are handled by `extras`.
    adapter_statement: ($) =>
      seq(
        // Require a trailing space/tab so this token can't swallow the
        // `@adapter` prefix of the `@adapters {` entity block (plural).
        token.immediate(seq("@", "adapter", /[ \t]/)),
        /\s*/,
        choice(
          seq('"', field("adapter_path", $.adapter_path), '"'),
          seq("'", field("adapter_path", $.adapter_path), "'"),
          field("adapter_name", $.adapter_name)
        ),
        choice(
          seq(":", field("adapter_spec", $.prop_value)),
          repeat1(field("adapter_arg", $.adapter_arg))
        )
      ),

    // key=value argument on the space-separated @adapter form. Inter-arg spaces
    // are handled by `extras`, so there is no explicit separator here.
    adapter_arg: ($) =>
      seq(
        field("arg_key", /[A-Za-z_][A-Za-z0-9_]*/),
        token.immediate("="),
        field("arg_value", token.immediate(/[^\s\r\n]+/))
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

    prose_text: ($) => prec(-10, /[^\r\n{}()=@+#]+/),

    newline: ($) => /\r?\n/,

    // Named tokens for entity parts
    entity_name: ($) => /[A-Za-z_][A-Za-z0-9_' ]*/,
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
