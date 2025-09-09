#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 181
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 85
#define ALIAS_COUNT 2
#define TOKEN_COUNT 52
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 31
#define MAX_ALIAS_SEQUENCE_LENGTH 11
#define PRODUCTION_ID_COUNT 40

enum {
  sym_line_comment = 1,
  aux_sym_file_header_token1 = 2,
  anon_sym_COLON = 3,
  aux_sym_file_header_token2 = 4,
  aux_sym_file_header_token3 = 5,
  anon_sym_EQ = 6,
  aux_sym_act_header_token1 = 7,
  aux_sym_act_header_token2 = 8,
  anon_sym_EQ_EQ = 9,
  anon_sym_EQ_EQ_EQ = 10,
  aux_sym_cel_header_token1 = 11,
  anon_sym_DASH = 12,
  aux_sym_cel_header_token2 = 13,
  anon_sym_SLASH_SLASH_SLASH = 14,
  anon_sym_SLASH_SLASH = 15,
  anon_sym_SLASH = 16,
  anon_sym_AT = 17,
  aux_sym_entity_definition_token1 = 18,
  aux_sym_entity_definition_token2 = 19,
  aux_sym_entity_block_token1 = 20,
  aux_sym_entity_block_token2 = 21,
  anon_sym_entities = 22,
  anon_sym_characters = 23,
  anon_sym_locations = 24,
  anon_sym_items = 25,
  anon_sym_creatures = 26,
  anon_sym_eras = 27,
  anon_sym_world_eras = 28,
  anon_sym_LBRACE = 29,
  anon_sym_RBRACE = 30,
  aux_sym_block_entity_item_token1 = 31,
  aux_sym_block_entity_item_token2 = 32,
  aux_sym_block_entity_item_token3 = 33,
  aux_sym_block_entity_item_token4 = 34,
  aux_sym_block_entity_item_token5 = 35,
  anon_sym_POUND = 36,
  aux_sym_block_comment_token1 = 37,
  anon_sym_ATimport = 38,
  anon_sym_LPAREN = 39,
  anon_sym_DQUOTE = 40,
  aux_sym_import_statement_token1 = 41,
  anon_sym_SQUOTE = 42,
  aux_sym_import_statement_token2 = 43,
  aux_sym_import_statement_token3 = 44,
  anon_sym_RPAREN = 45,
  aux_sym_import_statement_token4 = 46,
  anon_sym_ATadapter = 47,
  aux_sym_adapter_statement_token1 = 48,
  aux_sym_entity_reference_token1 = 49,
  aux_sym_parenthetical_token1 = 50,
  sym_prose_text = 51,
  sym_source_file = 52,
  sym_line = 53,
  sym_file_header = 54,
  sym_act_header = 55,
  sym_scene_header = 56,
  sym_cel_header = 57,
  sym_content_type_beat = 58,
  sym_content_type_treatment = 59,
  sym_content_type_narrative = 60,
  sym_entity_definition = 61,
  sym_entity_block = 62,
  sym_entity_block_start = 63,
  sym_entity_block_end = 64,
  sym_entity_block_content = 65,
  sym_block_entity_item = 66,
  sym_block_property = 67,
  sym_block_comment = 68,
  sym_nested_block = 69,
  sym_deeper_nested_block = 70,
  sym_import_statement = 71,
  sym_adapter_statement = 72,
  sym_metadata_line = 73,
  sym_prose_line = 74,
  sym_entity_reference = 75,
  sym_dialogue_speaker = 76,
  sym_parenthetical = 77,
  sym_newline = 78,
  aux_sym_source_file_repeat1 = 79,
  aux_sym_entity_block_repeat1 = 80,
  aux_sym_block_entity_item_repeat1 = 81,
  aux_sym_nested_block_repeat1 = 82,
  aux_sym_deeper_nested_block_repeat1 = 83,
  aux_sym_prose_line_repeat1 = 84,
  alias_sym_ref_close = 85,
  alias_sym_ref_open = 86,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_line_comment] = "line_comment",
  [aux_sym_file_header_token1] = "file_header_token1",
  [anon_sym_COLON] = ":",
  [aux_sym_file_header_token2] = "file_header_token2",
  [aux_sym_file_header_token3] = "file_header_token3",
  [anon_sym_EQ] = "=",
  [aux_sym_act_header_token1] = "act_header_token1",
  [aux_sym_act_header_token2] = "act_header_token2",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_EQ_EQ_EQ] = "===",
  [aux_sym_cel_header_token1] = "cel_header_token1",
  [anon_sym_DASH] = "-",
  [aux_sym_cel_header_token2] = "cel_header_token2",
  [anon_sym_SLASH_SLASH_SLASH] = "///",
  [anon_sym_SLASH_SLASH] = "//",
  [anon_sym_SLASH] = "/",
  [anon_sym_AT] = "@",
  [aux_sym_entity_definition_token1] = "entity_definition_token1",
  [aux_sym_entity_definition_token2] = "entity_definition_token2",
  [aux_sym_entity_block_token1] = "entity_block_token1",
  [aux_sym_entity_block_token2] = "entity_block_token2",
  [anon_sym_entities] = "entities",
  [anon_sym_characters] = "characters",
  [anon_sym_locations] = "locations",
  [anon_sym_items] = "items",
  [anon_sym_creatures] = "creatures",
  [anon_sym_eras] = "eras",
  [anon_sym_world_eras] = "world_eras",
  [anon_sym_LBRACE] = "open_brace",
  [anon_sym_RBRACE] = "close_brace",
  [aux_sym_block_entity_item_token1] = "block_entity_item_token1",
  [aux_sym_block_entity_item_token2] = "block_entity_item_token2",
  [aux_sym_block_entity_item_token3] = "block_entity_item_token3",
  [aux_sym_block_entity_item_token4] = "block_entity_item_token4",
  [aux_sym_block_entity_item_token5] = "block_entity_item_token5",
  [anon_sym_POUND] = "#",
  [aux_sym_block_comment_token1] = "block_comment_token1",
  [anon_sym_ATimport] = "@import",
  [anon_sym_LPAREN] = "open_paren",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_import_statement_token1] = "import_statement_token1",
  [anon_sym_SQUOTE] = "'",
  [aux_sym_import_statement_token2] = "import_statement_token2",
  [aux_sym_import_statement_token3] = "import_statement_token3",
  [anon_sym_RPAREN] = "close_paren",
  [aux_sym_import_statement_token4] = "import_statement_token4",
  [anon_sym_ATadapter] = "@adapter",
  [aux_sym_adapter_statement_token1] = "adapter_statement_token1",
  [aux_sym_entity_reference_token1] = "entity_reference_token1",
  [aux_sym_parenthetical_token1] = "parenthetical_token1",
  [sym_prose_text] = "prose_text",
  [sym_source_file] = "source_file",
  [sym_line] = "line",
  [sym_file_header] = "file_header",
  [sym_act_header] = "act_header",
  [sym_scene_header] = "scene_header",
  [sym_cel_header] = "cel_header",
  [sym_content_type_beat] = "content_type_beat",
  [sym_content_type_treatment] = "content_type_treatment",
  [sym_content_type_narrative] = "content_type_narrative",
  [sym_entity_definition] = "entity_definition",
  [sym_entity_block] = "entity_block",
  [sym_entity_block_start] = "entity_block_start",
  [sym_entity_block_end] = "entity_block_end",
  [sym_entity_block_content] = "entity_block_content",
  [sym_block_entity_item] = "block_entity_item",
  [sym_block_property] = "block_property",
  [sym_block_comment] = "block_comment",
  [sym_nested_block] = "nested_block",
  [sym_deeper_nested_block] = "deeper_nested_block",
  [sym_import_statement] = "import_statement",
  [sym_adapter_statement] = "adapter_statement",
  [sym_metadata_line] = "metadata_line",
  [sym_prose_line] = "prose_line",
  [sym_entity_reference] = "entity_reference",
  [sym_dialogue_speaker] = "dialogue_speaker",
  [sym_parenthetical] = "parenthetical",
  [sym_newline] = "newline",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_entity_block_repeat1] = "entity_block_repeat1",
  [aux_sym_block_entity_item_repeat1] = "block_entity_item_repeat1",
  [aux_sym_nested_block_repeat1] = "nested_block_repeat1",
  [aux_sym_deeper_nested_block_repeat1] = "deeper_nested_block_repeat1",
  [aux_sym_prose_line_repeat1] = "prose_line_repeat1",
  [alias_sym_ref_close] = "ref_close",
  [alias_sym_ref_open] = "ref_open",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_line_comment] = sym_line_comment,
  [aux_sym_file_header_token1] = aux_sym_file_header_token1,
  [anon_sym_COLON] = anon_sym_COLON,
  [aux_sym_file_header_token2] = aux_sym_file_header_token2,
  [aux_sym_file_header_token3] = aux_sym_file_header_token3,
  [anon_sym_EQ] = anon_sym_EQ,
  [aux_sym_act_header_token1] = aux_sym_act_header_token1,
  [aux_sym_act_header_token2] = aux_sym_act_header_token2,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_EQ_EQ_EQ] = anon_sym_EQ_EQ_EQ,
  [aux_sym_cel_header_token1] = aux_sym_cel_header_token1,
  [anon_sym_DASH] = anon_sym_DASH,
  [aux_sym_cel_header_token2] = aux_sym_cel_header_token2,
  [anon_sym_SLASH_SLASH_SLASH] = anon_sym_SLASH_SLASH_SLASH,
  [anon_sym_SLASH_SLASH] = anon_sym_SLASH_SLASH,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_AT] = anon_sym_AT,
  [aux_sym_entity_definition_token1] = aux_sym_entity_definition_token1,
  [aux_sym_entity_definition_token2] = aux_sym_entity_definition_token2,
  [aux_sym_entity_block_token1] = aux_sym_entity_block_token1,
  [aux_sym_entity_block_token2] = aux_sym_entity_block_token2,
  [anon_sym_entities] = anon_sym_entities,
  [anon_sym_characters] = anon_sym_characters,
  [anon_sym_locations] = anon_sym_locations,
  [anon_sym_items] = anon_sym_items,
  [anon_sym_creatures] = anon_sym_creatures,
  [anon_sym_eras] = anon_sym_eras,
  [anon_sym_world_eras] = anon_sym_world_eras,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [aux_sym_block_entity_item_token1] = aux_sym_block_entity_item_token1,
  [aux_sym_block_entity_item_token2] = aux_sym_block_entity_item_token2,
  [aux_sym_block_entity_item_token3] = aux_sym_block_entity_item_token3,
  [aux_sym_block_entity_item_token4] = aux_sym_block_entity_item_token4,
  [aux_sym_block_entity_item_token5] = aux_sym_block_entity_item_token5,
  [anon_sym_POUND] = anon_sym_POUND,
  [aux_sym_block_comment_token1] = aux_sym_block_comment_token1,
  [anon_sym_ATimport] = anon_sym_ATimport,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_import_statement_token1] = aux_sym_import_statement_token1,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [aux_sym_import_statement_token2] = aux_sym_import_statement_token2,
  [aux_sym_import_statement_token3] = aux_sym_import_statement_token3,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [aux_sym_import_statement_token4] = aux_sym_import_statement_token4,
  [anon_sym_ATadapter] = anon_sym_ATadapter,
  [aux_sym_adapter_statement_token1] = aux_sym_adapter_statement_token1,
  [aux_sym_entity_reference_token1] = aux_sym_entity_reference_token1,
  [aux_sym_parenthetical_token1] = aux_sym_parenthetical_token1,
  [sym_prose_text] = sym_prose_text,
  [sym_source_file] = sym_source_file,
  [sym_line] = sym_line,
  [sym_file_header] = sym_file_header,
  [sym_act_header] = sym_act_header,
  [sym_scene_header] = sym_scene_header,
  [sym_cel_header] = sym_cel_header,
  [sym_content_type_beat] = sym_content_type_beat,
  [sym_content_type_treatment] = sym_content_type_treatment,
  [sym_content_type_narrative] = sym_content_type_narrative,
  [sym_entity_definition] = sym_entity_definition,
  [sym_entity_block] = sym_entity_block,
  [sym_entity_block_start] = sym_entity_block_start,
  [sym_entity_block_end] = sym_entity_block_end,
  [sym_entity_block_content] = sym_entity_block_content,
  [sym_block_entity_item] = sym_block_entity_item,
  [sym_block_property] = sym_block_property,
  [sym_block_comment] = sym_block_comment,
  [sym_nested_block] = sym_nested_block,
  [sym_deeper_nested_block] = sym_deeper_nested_block,
  [sym_import_statement] = sym_import_statement,
  [sym_adapter_statement] = sym_adapter_statement,
  [sym_metadata_line] = sym_metadata_line,
  [sym_prose_line] = sym_prose_line,
  [sym_entity_reference] = sym_entity_reference,
  [sym_dialogue_speaker] = sym_dialogue_speaker,
  [sym_parenthetical] = sym_parenthetical,
  [sym_newline] = sym_newline,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_entity_block_repeat1] = aux_sym_entity_block_repeat1,
  [aux_sym_block_entity_item_repeat1] = aux_sym_block_entity_item_repeat1,
  [aux_sym_nested_block_repeat1] = aux_sym_nested_block_repeat1,
  [aux_sym_deeper_nested_block_repeat1] = aux_sym_deeper_nested_block_repeat1,
  [aux_sym_prose_line_repeat1] = aux_sym_prose_line_repeat1,
  [alias_sym_ref_close] = alias_sym_ref_close,
  [alias_sym_ref_open] = alias_sym_ref_open,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_line_comment] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_file_header_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_file_header_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_file_header_token3] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_act_header_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_act_header_token2] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_cel_header_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_cel_header_token2] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SLASH_SLASH_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AT] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_entity_definition_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_entity_definition_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_entity_block_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_entity_block_token2] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_entities] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_characters] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_locations] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_items] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_creatures] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_eras] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_world_eras] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_block_entity_item_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_entity_item_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_entity_item_token3] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_entity_item_token4] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_entity_item_token5] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_POUND] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_block_comment_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_ATimport] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_import_statement_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_import_statement_token2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_import_statement_token3] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_import_statement_token4] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_ATadapter] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_adapter_statement_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_entity_reference_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_parenthetical_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_prose_text] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_line] = {
    .visible = true,
    .named = true,
  },
  [sym_file_header] = {
    .visible = true,
    .named = true,
  },
  [sym_act_header] = {
    .visible = true,
    .named = true,
  },
  [sym_scene_header] = {
    .visible = true,
    .named = true,
  },
  [sym_cel_header] = {
    .visible = true,
    .named = true,
  },
  [sym_content_type_beat] = {
    .visible = true,
    .named = true,
  },
  [sym_content_type_treatment] = {
    .visible = true,
    .named = true,
  },
  [sym_content_type_narrative] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_block] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_block_start] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_block_end] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_block_content] = {
    .visible = true,
    .named = true,
  },
  [sym_block_entity_item] = {
    .visible = true,
    .named = true,
  },
  [sym_block_property] = {
    .visible = true,
    .named = true,
  },
  [sym_block_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_nested_block] = {
    .visible = true,
    .named = true,
  },
  [sym_deeper_nested_block] = {
    .visible = true,
    .named = true,
  },
  [sym_import_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_adapter_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_metadata_line] = {
    .visible = true,
    .named = true,
  },
  [sym_prose_line] = {
    .visible = true,
    .named = true,
  },
  [sym_entity_reference] = {
    .visible = true,
    .named = true,
  },
  [sym_dialogue_speaker] = {
    .visible = true,
    .named = true,
  },
  [sym_parenthetical] = {
    .visible = true,
    .named = true,
  },
  [sym_newline] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_entity_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_entity_item_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_nested_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_deeper_nested_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_prose_line_repeat1] = {
    .visible = false,
    .named = false,
  },
  [alias_sym_ref_close] = {
    .visible = true,
    .named = true,
  },
  [alias_sym_ref_open] = {
    .visible = true,
    .named = true,
  },
};

enum {
  field_adapter_name = 1,
  field_adapter_path = 2,
  field_alias = 3,
  field_block_type = 4,
  field_content = 5,
  field_description = 6,
  field_direction = 7,
  field_entity = 8,
  field_entity_desc = 9,
  field_entity_name = 10,
  field_entity_type = 11,
  field_item_key = 12,
  field_item_value = 13,
  field_key = 14,
  field_location_type = 15,
  field_meta_key = 16,
  field_meta_value = 17,
  field_name = 18,
  field_nested_key = 19,
  field_nested_type = 20,
  field_nested_value = 21,
  field_path = 22,
  field_prop_key = 23,
  field_prop_value = 24,
  field_proportion = 25,
  field_selector = 26,
  field_speaker = 27,
  field_time = 28,
  field_timing = 29,
  field_title = 30,
  field_value = 31,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_adapter_name] = "adapter_name",
  [field_adapter_path] = "adapter_path",
  [field_alias] = "alias",
  [field_block_type] = "block_type",
  [field_content] = "content",
  [field_description] = "description",
  [field_direction] = "direction",
  [field_entity] = "entity",
  [field_entity_desc] = "entity_desc",
  [field_entity_name] = "entity_name",
  [field_entity_type] = "entity_type",
  [field_item_key] = "item_key",
  [field_item_value] = "item_value",
  [field_key] = "key",
  [field_location_type] = "location_type",
  [field_meta_key] = "meta_key",
  [field_meta_value] = "meta_value",
  [field_name] = "name",
  [field_nested_key] = "nested_key",
  [field_nested_type] = "nested_type",
  [field_nested_value] = "nested_value",
  [field_path] = "path",
  [field_prop_key] = "prop_key",
  [field_prop_value] = "prop_value",
  [field_proportion] = "proportion",
  [field_selector] = "selector",
  [field_speaker] = "speaker",
  [field_time] = "time",
  [field_timing] = "timing",
  [field_title] = "title",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 2},
  [4] = {.index = 4, .length = 1},
  [5] = {.index = 5, .length = 1},
  [6] = {.index = 6, .length = 1},
  [7] = {.index = 7, .length = 2},
  [8] = {.index = 9, .length = 2},
  [9] = {.index = 11, .length = 2},
  [10] = {.index = 13, .length = 2},
  [11] = {.index = 15, .length = 1},
  [12] = {.index = 16, .length = 1},
  [13] = {.index = 17, .length = 2},
  [14] = {.index = 19, .length = 1},
  [15] = {.index = 20, .length = 1},
  [16] = {.index = 21, .length = 1},
  [17] = {.index = 22, .length = 3},
  [18] = {.index = 25, .length = 3},
  [19] = {.index = 28, .length = 1},
  [20] = {.index = 29, .length = 3},
  [21] = {.index = 32, .length = 2},
  [22] = {.index = 34, .length = 2},
  [23] = {.index = 36, .length = 2},
  [24] = {.index = 38, .length = 2},
  [25] = {.index = 40, .length = 1},
  [26] = {.index = 41, .length = 4},
  [27] = {.index = 45, .length = 2},
  [28] = {.index = 47, .length = 2},
  [29] = {.index = 49, .length = 2},
  [30] = {.index = 51, .length = 2},
  [31] = {.index = 53, .length = 3},
  [32] = {.index = 56, .length = 3},
  [33] = {.index = 59, .length = 3},
  [34] = {.index = 62, .length = 2},
  [35] = {.index = 64, .length = 1},
  [36] = {.index = 65, .length = 3},
  [37] = {.index = 68, .length = 2},
  [38] = {.index = 70, .length = 1},
  [39] = {.index = 71, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_key, 0},
  [1] =
    {field_content, 1},
  [2] =
    {field_key, 0},
    {field_value, 2},
  [4] =
    {field_title, 2},
  [5] =
    {field_entity, 1},
  [6] =
    {field_direction, 1},
  [7] =
    {field_key, 0},
    {field_value, 3},
  [9] =
    {field_proportion, 3},
    {field_title, 2},
  [11] =
    {field_meta_key, 1},
    {field_meta_value, 3},
  [13] =
    {field_entity_type, 1},
    {field_name, 3},
  [15] =
    {field_block_type, 1},
  [16] =
    {field_speaker, 1},
  [17] =
    {field_location_type, 4},
    {field_title, 2},
  [19] =
    {field_path, 3},
  [20] =
    {field_adapter_name, 2},
  [21] =
    {field_adapter_path, 3},
  [22] =
    {field_location_type, 4},
    {field_proportion, 5},
    {field_title, 2},
  [25] =
    {field_description, 5},
    {field_entity_type, 1},
    {field_name, 3},
  [28] =
    {field_path, 4},
  [29] =
    {field_location_type, 4},
    {field_time, 6},
    {field_title, 2},
  [32] =
    {field_alias, 6},
    {field_path, 3},
  [34] =
    {field_path, 3},
    {field_selector, 6},
  [36] =
    {field_adapter_path, 3},
    {field_timing, 6},
  [38] =
    {field_prop_key, 1},
    {field_prop_value, 3},
  [40] =
    {field_entity_name, 3},
  [41] =
    {field_location_type, 4},
    {field_proportion, 7},
    {field_time, 6},
    {field_title, 2},
  [45] =
    {field_alias, 7},
    {field_path, 4},
  [47] =
    {field_path, 4},
    {field_selector, 7},
  [49] =
    {field_path, 3},
    {field_selector, 7},
  [51] =
    {field_path, 4},
    {field_selector, 8},
  [53] =
    {field_alias, 6},
    {field_path, 3},
    {field_selector, 8},
  [56] =
    {field_alias, 7},
    {field_path, 4},
    {field_selector, 9},
  [59] =
    {field_alias, 6},
    {field_path, 3},
    {field_selector, 9},
  [62] =
    {field_entity_desc, 6},
    {field_entity_name, 3},
  [64] =
    {field_nested_type, 2},
  [65] =
    {field_alias, 7},
    {field_path, 4},
    {field_selector, 10},
  [68] =
    {field_item_key, 1},
    {field_item_value, 4},
  [70] =
    {field_key, 1},
  [71] =
    {field_nested_key, 1},
    {field_nested_value, 4},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [5] = {
    [0] = alias_sym_ref_open,
    [2] = alias_sym_ref_close,
  },
  [12] = {
    [0] = alias_sym_ref_open,
    [2] = alias_sym_ref_close,
  },
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 47,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 94,
  [95] = 95,
  [96] = 96,
  [97] = 97,
  [98] = 98,
  [99] = 99,
  [100] = 100,
  [101] = 101,
  [102] = 102,
  [103] = 103,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 107,
  [108] = 108,
  [109] = 109,
  [110] = 110,
  [111] = 111,
  [112] = 112,
  [113] = 113,
  [114] = 114,
  [115] = 115,
  [116] = 116,
  [117] = 117,
  [118] = 118,
  [119] = 119,
  [120] = 120,
  [121] = 121,
  [122] = 122,
  [123] = 123,
  [124] = 124,
  [125] = 125,
  [126] = 126,
  [127] = 127,
  [128] = 128,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
  [133] = 133,
  [134] = 134,
  [135] = 135,
  [136] = 136,
  [137] = 137,
  [138] = 138,
  [139] = 139,
  [140] = 140,
  [141] = 141,
  [142] = 142,
  [143] = 143,
  [144] = 144,
  [145] = 145,
  [146] = 146,
  [147] = 147,
  [148] = 148,
  [149] = 149,
  [150] = 150,
  [151] = 151,
  [152] = 152,
  [153] = 153,
  [154] = 154,
  [155] = 155,
  [156] = 156,
  [157] = 157,
  [158] = 158,
  [159] = 159,
  [160] = 160,
  [161] = 161,
  [162] = 162,
  [163] = 163,
  [164] = 164,
  [165] = 165,
  [166] = 166,
  [167] = 167,
  [168] = 168,
  [169] = 169,
  [170] = 170,
  [171] = 171,
  [172] = 172,
  [173] = 173,
  [174] = 174,
  [175] = 175,
  [176] = 176,
  [177] = 177,
  [178] = 178,
  [179] = 179,
  [180] = 180,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(176);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '"') ADVANCE(210);
      if (lookahead == '#') ADVANCE(202);
      if (lookahead == '\'') ADVANCE(213);
      if (lookahead == '(') ADVANCE(208);
      if (lookahead == ')') ADVANCE(218);
      if (lookahead == '-') ADVANCE(114);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == ':') ADVANCE(77);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(124);
      if (lookahead == 'c') ADVANCE(144);
      if (lookahead == 'e') ADVANCE(150);
      if (lookahead == 'i') ADVANCE(169);
      if (lookahead == 'l') ADVANCE(152);
      if (lookahead == 'w') ADVANCE(153);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '}') ADVANCE(189);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(1);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(176);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '"') ADVANCE(210);
      if (lookahead == '#') ADVANCE(202);
      if (lookahead == '\'') ADVANCE(213);
      if (lookahead == '(') ADVANCE(208);
      if (lookahead == ')') ADVANCE(218);
      if (lookahead == '-') ADVANCE(114);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == ':') ADVANCE(77);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(124);
      if (lookahead == 'c') ADVANCE(144);
      if (lookahead == 'e') ADVANCE(150);
      if (lookahead == 'i') ADVANCE(169);
      if (lookahead == 'l') ADVANCE(152);
      if (lookahead == 'w') ADVANCE(153);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '}') ADVANCE(189);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(1);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(176);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '#') ADVANCE(73);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(175);
      END_STATE();
    case 3:
      if (lookahead == '\n') ADVANCE(176);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(3);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(194);
      END_STATE();
    case 5:
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '"') ADVANCE(210);
      if (lookahead == '#') ADVANCE(73);
      if (lookahead == '\'') ADVANCE(213);
      if (lookahead == ':') ADVANCE(77);
      if (lookahead == '}') ADVANCE(189);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 6:
      if (lookahead == '\n') ADVANCE(195);
      if (lookahead == '#') ADVANCE(219);
      if (lookahead == 'a') ADVANCE(45);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      END_STATE();
    case 7:
      if (lookahead == '\n') ADVANCE(196);
      if (lookahead == '#') ADVANCE(219);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(14);
      END_STATE();
    case 8:
      if (lookahead == '\n') ADVANCE(198);
      if (lookahead == '@') ADVANCE(48);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(30);
      END_STATE();
    case 9:
      if (lookahead == '\n') ADVANCE(197);
      if (lookahead == '\r') ADVANCE(10);
      if (lookahead == '"') ADVANCE(210);
      if (lookahead == '#') ADVANCE(73);
      if (lookahead == '\'') ADVANCE(213);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == ')') ADVANCE(218);
      if (lookahead == ':') ADVANCE(78);
      if (lookahead == 'c') ADVANCE(144);
      if (lookahead == 'e') ADVANCE(150);
      if (lookahead == 'i') ADVANCE(169);
      if (lookahead == 'l') ADVANCE(152);
      if (lookahead == 'w') ADVANCE(153);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '}') ADVANCE(189);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 10:
      if (lookahead == '\n') ADVANCE(197);
      if (lookahead == ':') ADVANCE(199);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(29);
      END_STATE();
    case 11:
      if (lookahead == '#') ADVANCE(202);
      if (lookahead == '-') ADVANCE(114);
      if (lookahead == '@') ADVANCE(123);
      if (lookahead == '}') ADVANCE(189);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(11)
      END_STATE();
    case 12:
      if (lookahead == '#') ADVANCE(73);
      if (lookahead == ':') ADVANCE(77);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(83);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(84);
      END_STATE();
    case 13:
      if (lookahead == '#') ADVANCE(219);
      if (lookahead == 'a') ADVANCE(45);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      END_STATE();
    case 14:
      if (lookahead == '#') ADVANCE(219);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(14);
      END_STATE();
    case 15:
      if (lookahead == '#') ADVANCE(66);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(200);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(201);
      END_STATE();
    case 16:
      if (lookahead == '#') ADVANCE(70);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(190);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':' &&
          lookahead != '{') ADVANCE(191);
      END_STATE();
    case 17:
      if (lookahead == '#') ADVANCE(62);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(214);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(215);
      END_STATE();
    case 18:
      if (lookahead == '#') ADVANCE(63);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(211);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(212);
      END_STATE();
    case 19:
      if (lookahead == '#') ADVANCE(68);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(112);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '-') ADVANCE(113);
      END_STATE();
    case 20:
      if (lookahead == '#') ADVANCE(69);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(192);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '{') ADVANCE(193);
      END_STATE();
    case 21:
      if (lookahead == '#') ADVANCE(67);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(105);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(') ADVANCE(106);
      END_STATE();
    case 22:
      if (lookahead == '#') ADVANCE(71);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(115);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')') ADVANCE(116);
      END_STATE();
    case 23:
      if (lookahead == '#') ADVANCE(64);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(225);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(226);
      END_STATE();
    case 24:
      if (lookahead == '#') ADVANCE(65);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(223);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(224);
      END_STATE();
    case 25:
      if (lookahead == '%') ADVANCE(27);
      if (lookahead == '.') ADVANCE(51);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(25);
      END_STATE();
    case 26:
      if (lookahead == '%') ADVANCE(27);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(26);
      END_STATE();
    case 27:
      if (lookahead == ')') ADVANCE(107);
      END_STATE();
    case 28:
      if (lookahead == ':') ADVANCE(222);
      END_STATE();
    case 29:
      if (lookahead == ':') ADVANCE(199);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(29);
      END_STATE();
    case 30:
      if (lookahead == '@') ADVANCE(48);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(30);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(42);
      END_STATE();
    case 32:
      if (lookahead == 'd') ADVANCE(31);
      END_STATE();
    case 33:
      if (lookahead == 'e') ADVANCE(43);
      END_STATE();
    case 34:
      if (lookahead == 'g') ADVANCE(28);
      END_STATE();
    case 35:
      if (lookahead == 'i') ADVANCE(39);
      END_STATE();
    case 36:
      if (lookahead == 'i') ADVANCE(38);
      END_STATE();
    case 37:
      if (lookahead == 'm') ADVANCE(41);
      END_STATE();
    case 38:
      if (lookahead == 'm') ADVANCE(35);
      END_STATE();
    case 39:
      if (lookahead == 'n') ADVANCE(34);
      END_STATE();
    case 40:
      if (lookahead == 'o') ADVANCE(44);
      END_STATE();
    case 41:
      if (lookahead == 'p') ADVANCE(40);
      END_STATE();
    case 42:
      if (lookahead == 'p') ADVANCE(46);
      END_STATE();
    case 43:
      if (lookahead == 'r') ADVANCE(220);
      END_STATE();
    case 44:
      if (lookahead == 'r') ADVANCE(47);
      END_STATE();
    case 45:
      if (lookahead == 's') ADVANCE(49);
      END_STATE();
    case 46:
      if (lookahead == 't') ADVANCE(33);
      END_STATE();
    case 47:
      if (lookahead == 't') ADVANCE(205);
      END_STATE();
    case 48:
      if (lookahead == 't') ADVANCE(36);
      END_STATE();
    case 49:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(217);
      END_STATE();
    case 50:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(50);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(175);
      END_STATE();
    case 51:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(26);
      END_STATE();
    case 52:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(176);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(227);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 53:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(208);
      if (lookahead == '-') ADVANCE(114);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(228);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 54:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(208);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(229);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 55:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == ':') ADVANCE(77);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(230);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 56:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(231);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 57:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(195);
      if (lookahead == '\r') ADVANCE(6);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == ')') ADVANCE(218);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(232);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 58:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(196);
      if (lookahead == '\r') ADVANCE(7);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == ')') ADVANCE(218);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(233);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 59:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(198);
      if (lookahead == '\r') ADVANCE(8);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(234);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 60:
      if (eof) ADVANCE(61);
      if (lookahead == '\n') ADVANCE(197);
      if (lookahead == '\r') ADVANCE(10);
      if (lookahead == '"') ADVANCE(210);
      if (lookahead == '#') ADVANCE(73);
      if (lookahead == '\'') ADVANCE(213);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == ')') ADVANCE(218);
      if (lookahead == ':') ADVANCE(78);
      if (lookahead == 'c') ADVANCE(144);
      if (lookahead == 'e') ADVANCE(150);
      if (lookahead == 'i') ADVANCE(169);
      if (lookahead == 'l') ADVANCE(152);
      if (lookahead == 'w') ADVANCE(153);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '}') ADVANCE(189);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(215);
      if (lookahead == '\'') ADVANCE(73);
      if (lookahead != 0) ADVANCE(62);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(212);
      if (lookahead == '"') ADVANCE(73);
      if (lookahead != 0) ADVANCE(63);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(226);
      if (lookahead == ')') ADVANCE(73);
      if (lookahead != 0) ADVANCE(64);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(224);
      if (lookahead == '}') ADVANCE(73);
      if (lookahead != 0) ADVANCE(65);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r') ADVANCE(73);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(66);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '(') ADVANCE(73);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(67);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '-') ADVANCE(73);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(68);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '{') ADVANCE(73);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(69);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == ':' ||
          lookahead == '{') ADVANCE(73);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(70);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')') ADVANCE(73);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(71);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(73);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(72);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(73);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(74);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(76);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(199);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(84);
      if (lookahead == '\r') ADVANCE(81);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(79);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(84);
      if (lookahead == '\r') ADVANCE(82);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(80);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(84);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(81);
      if (lookahead != 0) ADVANCE(100);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(84);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(84);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(83);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(84);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(84);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead != 0) ADVANCE(100);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r') ADVANCE(85);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(209);
      if (lookahead == '/') ADVANCE(122);
      if (lookahead == '=') ADVANCE(104);
      if (lookahead == '@') ADVANCE(127);
      if (lookahead == '{') ADVANCE(188);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(86);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(100);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(74);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '#') ADVANCE(73);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(87);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(100);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'a') ADVANCE(94);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'd') ADVANCE(88);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'e') ADVANCE(95);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'm') ADVANCE(93);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'o') ADVANCE(96);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'p') ADVANCE(92);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'p') ADVANCE(97);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(221);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(98);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(90);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(206);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(100);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(61);
      if (lookahead == '\r') ADVANCE(81);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(209);
      if (lookahead == '/') ADVANCE(122);
      if (lookahead == '=') ADVANCE(104);
      if (lookahead == '@') ADVANCE(127);
      if (lookahead == '{') ADVANCE(188);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(79);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(100);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(74);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(61);
      if (lookahead == '\r') ADVANCE(85);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(209);
      if (lookahead == '/') ADVANCE(122);
      if (lookahead == '=') ADVANCE(104);
      if (lookahead == '@') ADVANCE(127);
      if (lookahead == '{') ADVANCE(188);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(86);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(100);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(74);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(108);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(109);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(aux_sym_act_header_token1);
      if (lookahead == '#') ADVANCE(67);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(105);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(') ADVANCE(106);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(aux_sym_act_header_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(') ADVANCE(106);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(aux_sym_act_header_token2);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      if (lookahead == '=') ADVANCE(110);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      if (lookahead == '=') ADVANCE(111);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(aux_sym_cel_header_token1);
      if (lookahead == '#') ADVANCE(68);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(112);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '-') ADVANCE(113);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(aux_sym_cel_header_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '-') ADVANCE(113);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(aux_sym_cel_header_token2);
      if (lookahead == '#') ADVANCE(71);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(115);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')') ADVANCE(116);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(aux_sym_cel_header_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')') ADVANCE(116);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH_SLASH);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH_SLASH);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead == '/') ADVANCE(117);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead == '/') ADVANCE(118);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '/') ADVANCE(119);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '/') ADVANCE(120);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(anon_sym_AT);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(32);
      if (lookahead == 'i') ADVANCE(37);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(237);
      if (lookahead == 'i') ADVANCE(242);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(237);
      if (lookahead == 'i') ADVANCE(242);
      if (lookahead == 't') ADVANCE(241);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(89);
      if (lookahead == 'i') ADVANCE(91);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == '_') ADVANCE(143);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(160);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(136);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(156);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(168);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(171);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(166);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'c') ADVANCE(133);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'c') ADVANCE(172);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'd') ADVANCE(128);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(149);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(132);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(162);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(158);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(163);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(157);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'h') ADVANCE(131);
      if (lookahead == 'r') ADVANCE(139);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'i') ADVANCE(154);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'i') ADVANCE(140);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'i') ADVANCE(170);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'l') ADVANCE(137);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'm') ADVANCE(161);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'n') ADVANCE(167);
      if (lookahead == 'r') ADVANCE(129);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'n') ADVANCE(164);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'o') ADVANCE(135);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'o') ADVANCE(155);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'o') ADVANCE(151);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(148);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(130);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(134);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(165);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(142);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(185);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(183);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(180);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(184);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(182);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(181);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(186);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(147);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(173);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(138);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(146);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(145);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(141);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'u') ADVANCE(159);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(aux_sym_entity_definition_token2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(50);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(175);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(aux_sym_entity_block_token1);
      if (lookahead == '\n') ADVANCE(176);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(3);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(aux_sym_entity_block_token2);
      if (lookahead == '\n') ADVANCE(84);
      if (lookahead == '\r') ADVANCE(82);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(80);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(aux_sym_entity_block_token2);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(178);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(179);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(aux_sym_entity_block_token2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(179);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(anon_sym_entities);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(anon_sym_characters);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(anon_sym_locations);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(anon_sym_items);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(anon_sym_creatures);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(anon_sym_eras);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(anon_sym_world_eras);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(174);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(100);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token1);
      if (lookahead == '#') ADVANCE(70);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(190);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':' &&
          lookahead != '{') ADVANCE(191);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':' &&
          lookahead != '{') ADVANCE(191);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token2);
      if (lookahead == '#') ADVANCE(69);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(192);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '{') ADVANCE(193);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '{') ADVANCE(193);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == '#') ADVANCE(219);
      if (lookahead == 'a') ADVANCE(45);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == '#') ADVANCE(219);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(14);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == ':') ADVANCE(199);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(29);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == '@') ADVANCE(48);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(30);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token4);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(199);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token5);
      if (lookahead == '#') ADVANCE(66);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(200);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(201);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token5);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(201);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(anon_sym_POUND);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(73);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(aux_sym_block_comment_token1);
      if (lookahead == '#') ADVANCE(66);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(203);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(204);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(aux_sym_block_comment_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(204);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(anon_sym_ATimport);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(anon_sym_ATimport);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(25);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(100);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(aux_sym_import_statement_token1);
      if (lookahead == '#') ADVANCE(63);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(211);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(212);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(aux_sym_import_statement_token1);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(212);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(aux_sym_import_statement_token2);
      if (lookahead == '#') ADVANCE(62);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(214);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(215);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(aux_sym_import_statement_token2);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(215);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(aux_sym_import_statement_token3);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(216);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(217);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(aux_sym_import_statement_token3);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(217);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(aux_sym_import_statement_token4);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_ATadapter);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(anon_sym_ATadapter);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(100);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(99);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(aux_sym_adapter_statement_token1);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(aux_sym_entity_reference_token1);
      if (lookahead == '#') ADVANCE(65);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(223);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(224);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(aux_sym_entity_reference_token1);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(224);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(aux_sym_parenthetical_token1);
      if (lookahead == '#') ADVANCE(64);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(225);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(226);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(aux_sym_parenthetical_token1);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(226);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(176);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(227);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(208);
      if (lookahead == '-') ADVANCE(114);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(228);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(208);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(229);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == ':') ADVANCE(77);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(230);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(194);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(231);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(195);
      if (lookahead == '\r') ADVANCE(6);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == ')') ADVANCE(218);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == 'a') ADVANCE(250);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(232);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(196);
      if (lookahead == '\r') ADVANCE(7);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == ')') ADVANCE(218);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(125);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(233);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(198);
      if (lookahead == '\r') ADVANCE(8);
      if (lookahead == '#') ADVANCE(72);
      if (lookahead == '(') ADVANCE(207);
      if (lookahead == '/') ADVANCE(121);
      if (lookahead == '=') ADVANCE(103);
      if (lookahead == '@') ADVANCE(126);
      if (lookahead == '{') ADVANCE(187);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(234);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(76);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == ':') ADVANCE(222);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'a') ADVANCE(247);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'd') ADVANCE(236);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'e') ADVANCE(248);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'g') ADVANCE(235);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'i') ADVANCE(244);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'i') ADVANCE(243);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'm') ADVANCE(246);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'm') ADVANCE(240);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'n') ADVANCE(239);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'o') ADVANCE(249);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'p') ADVANCE(245);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'p') ADVANCE(252);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'r') ADVANCE(220);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'r') ADVANCE(251);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 's') ADVANCE(253);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 't') ADVANCE(205);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 't') ADVANCE(238);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(216);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(217);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(254);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 56},
  [2] = {.lex_state = 56},
  [3] = {.lex_state = 56},
  [4] = {.lex_state = 56},
  [5] = {.lex_state = 56},
  [6] = {.lex_state = 57},
  [7] = {.lex_state = 57},
  [8] = {.lex_state = 58},
  [9] = {.lex_state = 53},
  [10] = {.lex_state = 58},
  [11] = {.lex_state = 101},
  [12] = {.lex_state = 53},
  [13] = {.lex_state = 54},
  [14] = {.lex_state = 58},
  [15] = {.lex_state = 59},
  [16] = {.lex_state = 58},
  [17] = {.lex_state = 55},
  [18] = {.lex_state = 58},
  [19] = {.lex_state = 102},
  [20] = {.lex_state = 102},
  [21] = {.lex_state = 102},
  [22] = {.lex_state = 58},
  [23] = {.lex_state = 102},
  [24] = {.lex_state = 52},
  [25] = {.lex_state = 54},
  [26] = {.lex_state = 54},
  [27] = {.lex_state = 56},
  [28] = {.lex_state = 56},
  [29] = {.lex_state = 56},
  [30] = {.lex_state = 56},
  [31] = {.lex_state = 56},
  [32] = {.lex_state = 56},
  [33] = {.lex_state = 56},
  [34] = {.lex_state = 56},
  [35] = {.lex_state = 56},
  [36] = {.lex_state = 56},
  [37] = {.lex_state = 56},
  [38] = {.lex_state = 56},
  [39] = {.lex_state = 56},
  [40] = {.lex_state = 56},
  [41] = {.lex_state = 56},
  [42] = {.lex_state = 56},
  [43] = {.lex_state = 56},
  [44] = {.lex_state = 56},
  [45] = {.lex_state = 56},
  [46] = {.lex_state = 56},
  [47] = {.lex_state = 56},
  [48] = {.lex_state = 56},
  [49] = {.lex_state = 56},
  [50] = {.lex_state = 56},
  [51] = {.lex_state = 56},
  [52] = {.lex_state = 56},
  [53] = {.lex_state = 56},
  [54] = {.lex_state = 56},
  [55] = {.lex_state = 56},
  [56] = {.lex_state = 177},
  [57] = {.lex_state = 177},
  [58] = {.lex_state = 177},
  [59] = {.lex_state = 177},
  [60] = {.lex_state = 177},
  [61] = {.lex_state = 60},
  [62] = {.lex_state = 177},
  [63] = {.lex_state = 177},
  [64] = {.lex_state = 177},
  [65] = {.lex_state = 177},
  [66] = {.lex_state = 177},
  [67] = {.lex_state = 177},
  [68] = {.lex_state = 177},
  [69] = {.lex_state = 11},
  [70] = {.lex_state = 11},
  [71] = {.lex_state = 177},
  [72] = {.lex_state = 11},
  [73] = {.lex_state = 177},
  [74] = {.lex_state = 177},
  [75] = {.lex_state = 177},
  [76] = {.lex_state = 177},
  [77] = {.lex_state = 177},
  [78] = {.lex_state = 177},
  [79] = {.lex_state = 177},
  [80] = {.lex_state = 177},
  [81] = {.lex_state = 177},
  [82] = {.lex_state = 60},
  [83] = {.lex_state = 11},
  [84] = {.lex_state = 177},
  [85] = {.lex_state = 5},
  [86] = {.lex_state = 177},
  [87] = {.lex_state = 177},
  [88] = {.lex_state = 60},
  [89] = {.lex_state = 177},
  [90] = {.lex_state = 11},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 60},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 12},
  [95] = {.lex_state = 178},
  [96] = {.lex_state = 11},
  [97] = {.lex_state = 5},
  [98] = {.lex_state = 5},
  [99] = {.lex_state = 15},
  [100] = {.lex_state = 5},
  [101] = {.lex_state = 16},
  [102] = {.lex_state = 5},
  [103] = {.lex_state = 15},
  [104] = {.lex_state = 15},
  [105] = {.lex_state = 5},
  [106] = {.lex_state = 5},
  [107] = {.lex_state = 60},
  [108] = {.lex_state = 60},
  [109] = {.lex_state = 60},
  [110] = {.lex_state = 87},
  [111] = {.lex_state = 5},
  [112] = {.lex_state = 203},
  [113] = {.lex_state = 15},
  [114] = {.lex_state = 5},
  [115] = {.lex_state = 15},
  [116] = {.lex_state = 178},
  [117] = {.lex_state = 5},
  [118] = {.lex_state = 60},
  [119] = {.lex_state = 178},
  [120] = {.lex_state = 60},
  [121] = {.lex_state = 60},
  [122] = {.lex_state = 2},
  [123] = {.lex_state = 60},
  [124] = {.lex_state = 60},
  [125] = {.lex_state = 15},
  [126] = {.lex_state = 60},
  [127] = {.lex_state = 17},
  [128] = {.lex_state = 15},
  [129] = {.lex_state = 18},
  [130] = {.lex_state = 18},
  [131] = {.lex_state = 2},
  [132] = {.lex_state = 2},
  [133] = {.lex_state = 19},
  [134] = {.lex_state = 15},
  [135] = {.lex_state = 5},
  [136] = {.lex_state = 5},
  [137] = {.lex_state = 17},
  [138] = {.lex_state = 5},
  [139] = {.lex_state = 20},
  [140] = {.lex_state = 178},
  [141] = {.lex_state = 178},
  [142] = {.lex_state = 17},
  [143] = {.lex_state = 15},
  [144] = {.lex_state = 18},
  [145] = {.lex_state = 60},
  [146] = {.lex_state = 5},
  [147] = {.lex_state = 2},
  [148] = {.lex_state = 87},
  [149] = {.lex_state = 5},
  [150] = {.lex_state = 60},
  [151] = {.lex_state = 60},
  [152] = {.lex_state = 178},
  [153] = {.lex_state = 5},
  [154] = {.lex_state = 5},
  [155] = {.lex_state = 19},
  [156] = {.lex_state = 21},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 178},
  [159] = {.lex_state = 21},
  [160] = {.lex_state = 5},
  [161] = {.lex_state = 60},
  [162] = {.lex_state = 15},
  [163] = {.lex_state = 2},
  [164] = {.lex_state = 2},
  [165] = {.lex_state = 5},
  [166] = {.lex_state = 60},
  [167] = {.lex_state = 12},
  [168] = {.lex_state = 22},
  [169] = {.lex_state = 23},
  [170] = {.lex_state = 5},
  [171] = {.lex_state = 178},
  [172] = {.lex_state = 5},
  [173] = {.lex_state = 24},
  [174] = {.lex_state = 178},
  [175] = {.lex_state = 12},
  [176] = {.lex_state = 5},
  [177] = {.lex_state = 15},
  [178] = {.lex_state = 5},
  [179] = {.lex_state = 12},
  [180] = {.lex_state = 12},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_line_comment] = ACTIONS(3),
    [aux_sym_file_header_token1] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [aux_sym_act_header_token2] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_EQ_EQ_EQ] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_SLASH_SLASH_SLASH] = ACTIONS(1),
    [anon_sym_SLASH_SLASH] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_AT] = ACTIONS(1),
    [aux_sym_entity_definition_token1] = ACTIONS(1),
    [aux_sym_entity_block_token1] = ACTIONS(1),
    [anon_sym_entities] = ACTIONS(1),
    [anon_sym_characters] = ACTIONS(1),
    [anon_sym_locations] = ACTIONS(1),
    [anon_sym_items] = ACTIONS(1),
    [anon_sym_creatures] = ACTIONS(1),
    [anon_sym_eras] = ACTIONS(1),
    [anon_sym_world_eras] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [aux_sym_block_entity_item_token3] = ACTIONS(1),
    [anon_sym_POUND] = ACTIONS(1),
    [anon_sym_ATimport] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_ATadapter] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(166),
    [sym_line] = STATE(3),
    [sym_file_header] = STATE(39),
    [sym_act_header] = STATE(39),
    [sym_scene_header] = STATE(39),
    [sym_cel_header] = STATE(39),
    [sym_content_type_beat] = STATE(39),
    [sym_content_type_treatment] = STATE(39),
    [sym_content_type_narrative] = STATE(39),
    [sym_entity_definition] = STATE(39),
    [sym_entity_block] = STATE(3),
    [sym_entity_block_start] = STATE(163),
    [sym_import_statement] = STATE(39),
    [sym_adapter_statement] = STATE(39),
    [sym_metadata_line] = STATE(39),
    [sym_prose_line] = STATE(39),
    [sym_entity_reference] = STATE(5),
    [sym_dialogue_speaker] = STATE(5),
    [sym_parenthetical] = STATE(5),
    [sym_newline] = STATE(3),
    [aux_sym_source_file_repeat1] = STATE(3),
    [aux_sym_prose_line_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_line_comment] = ACTIONS(3),
    [aux_sym_file_header_token1] = ACTIONS(7),
    [anon_sym_EQ] = ACTIONS(9),
    [anon_sym_EQ_EQ] = ACTIONS(11),
    [anon_sym_EQ_EQ_EQ] = ACTIONS(13),
    [anon_sym_SLASH_SLASH_SLASH] = ACTIONS(15),
    [anon_sym_SLASH_SLASH] = ACTIONS(17),
    [anon_sym_SLASH] = ACTIONS(19),
    [anon_sym_AT] = ACTIONS(21),
    [anon_sym_LBRACE] = ACTIONS(23),
    [aux_sym_block_entity_item_token3] = ACTIONS(25),
    [anon_sym_ATimport] = ACTIONS(27),
    [anon_sym_LPAREN] = ACTIONS(29),
    [anon_sym_ATadapter] = ACTIONS(31),
    [sym_prose_text] = ACTIONS(33),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 20,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(35), 1,
      ts_builtin_sym_end,
    ACTIONS(37), 1,
      aux_sym_file_header_token1,
    ACTIONS(40), 1,
      anon_sym_EQ,
    ACTIONS(43), 1,
      anon_sym_EQ_EQ,
    ACTIONS(46), 1,
      anon_sym_EQ_EQ_EQ,
    ACTIONS(49), 1,
      anon_sym_SLASH_SLASH_SLASH,
    ACTIONS(52), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(55), 1,
      anon_sym_SLASH,
    ACTIONS(58), 1,
      anon_sym_AT,
    ACTIONS(61), 1,
      anon_sym_LBRACE,
    ACTIONS(64), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(67), 1,
      anon_sym_ATimport,
    ACTIONS(70), 1,
      anon_sym_LPAREN,
    ACTIONS(73), 1,
      anon_sym_ATadapter,
    ACTIONS(76), 1,
      sym_prose_text,
    STATE(163), 1,
      sym_entity_block_start,
    STATE(2), 4,
      sym_line,
      sym_entity_block,
      sym_newline,
      aux_sym_source_file_repeat1,
    STATE(5), 4,
      sym_entity_reference,
      sym_dialogue_speaker,
      sym_parenthetical,
      aux_sym_prose_line_repeat1,
    STATE(39), 12,
      sym_file_header,
      sym_act_header,
      sym_scene_header,
      sym_cel_header,
      sym_content_type_beat,
      sym_content_type_treatment,
      sym_content_type_narrative,
      sym_entity_definition,
      sym_import_statement,
      sym_adapter_statement,
      sym_metadata_line,
      sym_prose_line,
  [78] = 20,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(7), 1,
      aux_sym_file_header_token1,
    ACTIONS(9), 1,
      anon_sym_EQ,
    ACTIONS(11), 1,
      anon_sym_EQ_EQ,
    ACTIONS(13), 1,
      anon_sym_EQ_EQ_EQ,
    ACTIONS(15), 1,
      anon_sym_SLASH_SLASH_SLASH,
    ACTIONS(17), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(19), 1,
      anon_sym_SLASH,
    ACTIONS(21), 1,
      anon_sym_AT,
    ACTIONS(23), 1,
      anon_sym_LBRACE,
    ACTIONS(25), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(27), 1,
      anon_sym_ATimport,
    ACTIONS(29), 1,
      anon_sym_LPAREN,
    ACTIONS(31), 1,
      anon_sym_ATadapter,
    ACTIONS(33), 1,
      sym_prose_text,
    ACTIONS(79), 1,
      ts_builtin_sym_end,
    STATE(163), 1,
      sym_entity_block_start,
    STATE(2), 4,
      sym_line,
      sym_entity_block,
      sym_newline,
      aux_sym_source_file_repeat1,
    STATE(5), 4,
      sym_entity_reference,
      sym_dialogue_speaker,
      sym_parenthetical,
      aux_sym_prose_line_repeat1,
    STATE(39), 12,
      sym_file_header,
      sym_act_header,
      sym_scene_header,
      sym_cel_header,
      sym_content_type_beat,
      sym_content_type_treatment,
      sym_content_type_narrative,
      sym_entity_definition,
      sym_import_statement,
      sym_adapter_statement,
      sym_metadata_line,
      sym_prose_line,
  [156] = 7,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(81), 1,
      ts_builtin_sym_end,
    ACTIONS(85), 1,
      anon_sym_LBRACE,
    ACTIONS(88), 1,
      anon_sym_LPAREN,
    ACTIONS(91), 1,
      sym_prose_text,
    STATE(4), 4,
      sym_entity_reference,
      sym_dialogue_speaker,
      sym_parenthetical,
      aux_sym_prose_line_repeat1,
    ACTIONS(83), 11,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_ATadapter,
  [191] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(94), 1,
      ts_builtin_sym_end,
    STATE(4), 4,
      sym_entity_reference,
      sym_dialogue_speaker,
      sym_parenthetical,
      aux_sym_prose_line_repeat1,
    ACTIONS(96), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [220] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(98), 1,
      ts_builtin_sym_end,
    ACTIONS(102), 1,
      aux_sym_import_statement_token3,
    ACTIONS(104), 1,
      anon_sym_RPAREN,
    ACTIONS(106), 1,
      aux_sym_import_statement_token4,
    ACTIONS(100), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [252] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(108), 1,
      ts_builtin_sym_end,
    ACTIONS(112), 1,
      aux_sym_import_statement_token3,
    ACTIONS(114), 1,
      anon_sym_RPAREN,
    ACTIONS(116), 1,
      aux_sym_import_statement_token4,
    ACTIONS(110), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [284] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(118), 1,
      ts_builtin_sym_end,
    ACTIONS(122), 1,
      anon_sym_RPAREN,
    ACTIONS(124), 1,
      aux_sym_import_statement_token4,
    ACTIONS(120), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [313] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(126), 1,
      ts_builtin_sym_end,
    ACTIONS(130), 1,
      aux_sym_act_header_token2,
    ACTIONS(132), 1,
      anon_sym_DASH,
    ACTIONS(128), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [342] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(134), 1,
      ts_builtin_sym_end,
    ACTIONS(138), 1,
      anon_sym_RPAREN,
    ACTIONS(140), 1,
      aux_sym_import_statement_token4,
    ACTIONS(136), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [371] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(142), 1,
      ts_builtin_sym_end,
    ACTIONS(146), 1,
      aux_sym_file_header_token2,
    ACTIONS(148), 1,
      aux_sym_file_header_token3,
    ACTIONS(144), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [400] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(150), 1,
      ts_builtin_sym_end,
    ACTIONS(154), 1,
      aux_sym_act_header_token2,
    ACTIONS(156), 1,
      anon_sym_DASH,
    ACTIONS(152), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [429] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(158), 1,
      ts_builtin_sym_end,
    ACTIONS(162), 1,
      aux_sym_act_header_token2,
    ACTIONS(160), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [455] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(164), 1,
      ts_builtin_sym_end,
    ACTIONS(168), 1,
      aux_sym_import_statement_token4,
    ACTIONS(166), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [481] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(170), 1,
      ts_builtin_sym_end,
    ACTIONS(174), 1,
      aux_sym_adapter_statement_token1,
    ACTIONS(172), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [507] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(176), 1,
      ts_builtin_sym_end,
    ACTIONS(180), 1,
      aux_sym_import_statement_token4,
    ACTIONS(178), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [533] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(182), 1,
      ts_builtin_sym_end,
    ACTIONS(186), 1,
      anon_sym_COLON,
    ACTIONS(184), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [559] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(188), 1,
      ts_builtin_sym_end,
    ACTIONS(192), 1,
      aux_sym_import_statement_token4,
    ACTIONS(190), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [585] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(194), 1,
      ts_builtin_sym_end,
    ACTIONS(198), 1,
      aux_sym_file_header_token3,
    ACTIONS(196), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [611] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(200), 1,
      ts_builtin_sym_end,
    ACTIONS(204), 1,
      aux_sym_file_header_token3,
    ACTIONS(202), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [637] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(206), 1,
      ts_builtin_sym_end,
    ACTIONS(210), 1,
      aux_sym_file_header_token3,
    ACTIONS(208), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [663] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(212), 1,
      ts_builtin_sym_end,
    ACTIONS(216), 1,
      aux_sym_import_statement_token4,
    ACTIONS(214), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [689] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(218), 1,
      ts_builtin_sym_end,
    ACTIONS(222), 1,
      aux_sym_file_header_token3,
    ACTIONS(220), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [715] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(224), 1,
      ts_builtin_sym_end,
    ACTIONS(228), 1,
      aux_sym_entity_block_token1,
    ACTIONS(226), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [741] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(230), 1,
      ts_builtin_sym_end,
    ACTIONS(234), 1,
      aux_sym_act_header_token2,
    ACTIONS(232), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [767] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(236), 1,
      ts_builtin_sym_end,
    ACTIONS(240), 1,
      aux_sym_act_header_token2,
    ACTIONS(238), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [793] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(242), 1,
      ts_builtin_sym_end,
    ACTIONS(244), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [816] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(246), 1,
      ts_builtin_sym_end,
    ACTIONS(248), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [839] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(250), 1,
      ts_builtin_sym_end,
    ACTIONS(252), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [862] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(254), 1,
      ts_builtin_sym_end,
    ACTIONS(256), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [885] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(258), 1,
      ts_builtin_sym_end,
    ACTIONS(260), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [908] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(262), 1,
      ts_builtin_sym_end,
    ACTIONS(264), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [931] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(266), 1,
      ts_builtin_sym_end,
    ACTIONS(268), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [954] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(270), 1,
      ts_builtin_sym_end,
    ACTIONS(272), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [977] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(274), 1,
      ts_builtin_sym_end,
    ACTIONS(276), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1000] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(278), 1,
      ts_builtin_sym_end,
    ACTIONS(280), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1023] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(282), 1,
      ts_builtin_sym_end,
    ACTIONS(284), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1046] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(286), 1,
      ts_builtin_sym_end,
    ACTIONS(288), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1069] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(290), 1,
      ts_builtin_sym_end,
    ACTIONS(292), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1092] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(294), 1,
      ts_builtin_sym_end,
    ACTIONS(296), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1115] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(298), 1,
      ts_builtin_sym_end,
    ACTIONS(300), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1138] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(302), 1,
      ts_builtin_sym_end,
    ACTIONS(304), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1161] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(306), 1,
      ts_builtin_sym_end,
    ACTIONS(308), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1184] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(310), 1,
      ts_builtin_sym_end,
    ACTIONS(312), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1207] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(314), 1,
      ts_builtin_sym_end,
    ACTIONS(316), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1230] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(318), 1,
      ts_builtin_sym_end,
    ACTIONS(320), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1253] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(322), 1,
      ts_builtin_sym_end,
    ACTIONS(324), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1276] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(326), 1,
      ts_builtin_sym_end,
    ACTIONS(328), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1299] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(330), 1,
      ts_builtin_sym_end,
    ACTIONS(332), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1322] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(334), 1,
      ts_builtin_sym_end,
    ACTIONS(336), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1345] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(338), 1,
      ts_builtin_sym_end,
    ACTIONS(340), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1368] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(342), 1,
      ts_builtin_sym_end,
    ACTIONS(344), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1391] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(346), 1,
      ts_builtin_sym_end,
    ACTIONS(348), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1414] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(350), 1,
      ts_builtin_sym_end,
    ACTIONS(352), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1437] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(354), 1,
      ts_builtin_sym_end,
    ACTIONS(356), 14,
      aux_sym_file_header_token1,
      anon_sym_EQ,
      anon_sym_EQ_EQ,
      anon_sym_EQ_EQ_EQ,
      anon_sym_SLASH_SLASH_SLASH,
      anon_sym_SLASH_SLASH,
      anon_sym_SLASH,
      anon_sym_AT,
      anon_sym_LBRACE,
      aux_sym_block_entity_item_token3,
      anon_sym_ATimport,
      anon_sym_LPAREN,
      anon_sym_ATadapter,
      sym_prose_text,
  [1460] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(358), 1,
      aux_sym_file_header_token2,
    ACTIONS(360), 1,
      aux_sym_entity_block_token2,
    ACTIONS(362), 1,
      aux_sym_block_entity_item_token3,
    STATE(73), 3,
      sym_block_entity_item,
      sym_block_property,
      sym_block_comment,
    STATE(57), 4,
      sym_entity_block_content,
      sym_nested_block,
      sym_newline,
      aux_sym_entity_block_repeat1,
  [1484] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(364), 1,
      aux_sym_file_header_token2,
    ACTIONS(367), 1,
      aux_sym_entity_block_token2,
    ACTIONS(370), 1,
      aux_sym_block_entity_item_token3,
    STATE(73), 3,
      sym_block_entity_item,
      sym_block_property,
      sym_block_comment,
    STATE(57), 4,
      sym_entity_block_content,
      sym_nested_block,
      sym_newline,
      aux_sym_entity_block_repeat1,
  [1508] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(358), 1,
      aux_sym_file_header_token2,
    ACTIONS(362), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(373), 1,
      aux_sym_entity_block_token2,
    STATE(73), 3,
      sym_block_entity_item,
      sym_block_property,
      sym_block_comment,
    STATE(56), 4,
      sym_entity_block_content,
      sym_nested_block,
      sym_newline,
      aux_sym_entity_block_repeat1,
  [1532] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(362), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(375), 1,
      aux_sym_file_header_token2,
    ACTIONS(377), 1,
      aux_sym_entity_block_token2,
    STATE(62), 5,
      sym_block_property,
      sym_block_comment,
      sym_deeper_nested_block,
      sym_newline,
      aux_sym_nested_block_repeat1,
  [1552] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(362), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(375), 1,
      aux_sym_file_header_token2,
    ACTIONS(379), 1,
      aux_sym_entity_block_token2,
    STATE(59), 5,
      sym_block_property,
      sym_block_comment,
      sym_deeper_nested_block,
      sym_newline,
      aux_sym_nested_block_repeat1,
  [1572] = 3,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(383), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(385), 7,
      anon_sym_entities,
      anon_sym_characters,
      anon_sym_locations,
      anon_sym_items,
      anon_sym_creatures,
      anon_sym_eras,
      anon_sym_world_eras,
  [1588] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(387), 1,
      aux_sym_file_header_token2,
    ACTIONS(390), 1,
      aux_sym_entity_block_token2,
    ACTIONS(393), 1,
      aux_sym_block_entity_item_token3,
    STATE(62), 5,
      sym_block_property,
      sym_block_comment,
      sym_deeper_nested_block,
      sym_newline,
      aux_sym_nested_block_repeat1,
  [1608] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(362), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(396), 1,
      aux_sym_file_header_token2,
    ACTIONS(398), 1,
      aux_sym_entity_block_token2,
    STATE(65), 4,
      sym_block_comment,
      sym_nested_block,
      sym_newline,
      aux_sym_block_entity_item_repeat1,
  [1627] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(400), 1,
      aux_sym_file_header_token2,
    ACTIONS(403), 1,
      aux_sym_entity_block_token2,
    ACTIONS(406), 1,
      aux_sym_block_entity_item_token3,
    STATE(64), 4,
      sym_block_comment,
      sym_nested_block,
      sym_newline,
      aux_sym_block_entity_item_repeat1,
  [1646] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(362), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(396), 1,
      aux_sym_file_header_token2,
    ACTIONS(409), 1,
      aux_sym_entity_block_token2,
    STATE(64), 4,
      sym_block_comment,
      sym_nested_block,
      sym_newline,
      aux_sym_block_entity_item_repeat1,
  [1665] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(362), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(411), 1,
      aux_sym_file_header_token2,
    ACTIONS(413), 1,
      aux_sym_entity_block_token2,
    STATE(67), 3,
      sym_block_comment,
      sym_newline,
      aux_sym_deeper_nested_block_repeat1,
  [1683] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(415), 1,
      aux_sym_file_header_token2,
    ACTIONS(418), 1,
      aux_sym_entity_block_token2,
    ACTIONS(421), 1,
      aux_sym_block_entity_item_token3,
    STATE(67), 3,
      sym_block_comment,
      sym_newline,
      aux_sym_deeper_nested_block_repeat1,
  [1701] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(362), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(413), 1,
      aux_sym_entity_block_token2,
    ACTIONS(424), 1,
      aux_sym_file_header_token2,
    STATE(66), 3,
      sym_block_comment,
      sym_newline,
      aux_sym_deeper_nested_block_repeat1,
  [1719] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(426), 1,
      anon_sym_DASH,
    ACTIONS(428), 1,
      anon_sym_AT,
    ACTIONS(430), 1,
      anon_sym_RBRACE,
    ACTIONS(432), 1,
      anon_sym_POUND,
    STATE(43), 1,
      sym_entity_block_end,
  [1738] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(426), 1,
      anon_sym_DASH,
    ACTIONS(428), 1,
      anon_sym_AT,
    ACTIONS(430), 1,
      anon_sym_RBRACE,
    ACTIONS(432), 1,
      anon_sym_POUND,
    STATE(44), 1,
      sym_entity_block_end,
  [1757] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(434), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1766] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(428), 1,
      anon_sym_AT,
    ACTIONS(432), 1,
      anon_sym_POUND,
    ACTIONS(436), 1,
      anon_sym_RBRACE,
  [1779] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(438), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1788] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(440), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1797] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(442), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1806] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(444), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1815] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(324), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1824] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(446), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1833] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(448), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1842] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(450), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1851] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(452), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1860] = 4,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(454), 1,
      anon_sym_COLON,
    ACTIONS(456), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(458), 1,
      aux_sym_block_entity_item_token4,
  [1873] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(428), 1,
      anon_sym_AT,
    ACTIONS(432), 1,
      anon_sym_POUND,
    ACTIONS(460), 1,
      anon_sym_RBRACE,
  [1886] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(462), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1895] = 4,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(464), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(466), 1,
      anon_sym_DQUOTE,
    ACTIONS(468), 1,
      anon_sym_SQUOTE,
  [1908] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(470), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1917] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(472), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1926] = 4,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(474), 1,
      anon_sym_LPAREN,
    ACTIONS(476), 1,
      anon_sym_DQUOTE,
    ACTIONS(478), 1,
      anon_sym_SQUOTE,
  [1939] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(480), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [1948] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(426), 1,
      anon_sym_DASH,
    ACTIONS(428), 1,
      anon_sym_AT,
    ACTIONS(432), 1,
      anon_sym_POUND,
  [1961] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(432), 1,
      anon_sym_POUND,
    ACTIONS(482), 1,
      anon_sym_RBRACE,
  [1971] = 3,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(484), 1,
      anon_sym_DQUOTE,
    ACTIONS(486), 1,
      anon_sym_SQUOTE,
  [1981] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(432), 1,
      anon_sym_POUND,
    ACTIONS(488), 1,
      anon_sym_RBRACE,
  [1991] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(490), 1,
      anon_sym_COLON,
    ACTIONS(492), 1,
      aux_sym_file_header_token2,
  [2001] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(494), 1,
      aux_sym_entity_block_token2,
    ACTIONS(496), 1,
      aux_sym_block_entity_item_token5,
  [2011] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(428), 1,
      anon_sym_AT,
    ACTIONS(432), 1,
      anon_sym_POUND,
  [2021] = 3,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(498), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(500), 1,
      anon_sym_RBRACE,
  [2031] = 3,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(498), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(502), 1,
      anon_sym_RBRACE,
  [2041] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(504), 1,
      aux_sym_block_entity_item_token5,
  [2048] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(506), 1,
      aux_sym_entity_definition_token1,
  [2055] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(508), 1,
      aux_sym_block_entity_item_token1,
  [2062] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(510), 1,
      aux_sym_entity_definition_token1,
  [2069] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(496), 1,
      aux_sym_block_entity_item_token5,
  [2076] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(512), 1,
      aux_sym_block_entity_item_token5,
  [2083] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(514), 1,
      aux_sym_entity_definition_token1,
  [2090] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(516), 1,
      aux_sym_block_entity_item_token3,
  [2097] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(518), 1,
      anon_sym_SQUOTE,
  [2104] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(520), 1,
      anon_sym_LBRACE,
  [2111] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(518), 1,
      anon_sym_DQUOTE,
  [2118] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(522), 1,
      aux_sym_file_header_token3,
  [2125] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(524), 1,
      aux_sym_entity_definition_token1,
  [2132] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(526), 1,
      aux_sym_block_comment_token1,
  [2139] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(528), 1,
      aux_sym_block_entity_item_token5,
  [2146] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(530), 1,
      aux_sym_entity_definition_token1,
  [2153] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(532), 1,
      aux_sym_block_entity_item_token5,
  [2160] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(534), 1,
      aux_sym_entity_block_token2,
  [2167] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(536), 1,
      anon_sym_COLON,
  [2174] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(538), 1,
      anon_sym_SQUOTE,
  [2181] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(540), 1,
      aux_sym_entity_block_token2,
  [2188] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(538), 1,
      anon_sym_DQUOTE,
  [2195] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(542), 1,
      anon_sym_LBRACE,
  [2202] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(544), 1,
      aux_sym_entity_block_token1,
  [2209] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(546), 1,
      anon_sym_LBRACE,
  [2216] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(548), 1,
      anon_sym_SQUOTE,
  [2223] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(550), 1,
      aux_sym_block_entity_item_token5,
  [2230] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(548), 1,
      anon_sym_DQUOTE,
  [2237] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(552), 1,
      aux_sym_import_statement_token2,
  [2244] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(554), 1,
      aux_sym_block_entity_item_token5,
  [2251] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(556), 1,
      aux_sym_import_statement_token1,
  [2258] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(558), 1,
      aux_sym_import_statement_token1,
  [2265] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(560), 1,
      aux_sym_entity_block_token1,
  [2272] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(562), 1,
      aux_sym_entity_block_token1,
  [2279] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(564), 1,
      aux_sym_cel_header_token1,
  [2286] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(566), 1,
      aux_sym_block_entity_item_token5,
  [2293] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(568), 1,
      aux_sym_entity_definition_token1,
  [2300] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(570), 1,
      anon_sym_COLON,
  [2307] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(572), 1,
      aux_sym_import_statement_token2,
  [2314] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(574), 1,
      aux_sym_block_entity_item_token3,
  [2321] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(576), 1,
      aux_sym_block_entity_item_token2,
  [2328] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(578), 1,
      aux_sym_entity_block_token2,
  [2335] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(580), 1,
      aux_sym_entity_block_token2,
  [2342] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(582), 1,
      aux_sym_import_statement_token2,
  [2349] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(584), 1,
      aux_sym_block_entity_item_token5,
  [2356] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(586), 1,
      aux_sym_import_statement_token1,
  [2363] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(588), 1,
      anon_sym_LBRACE,
  [2370] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(590), 1,
      aux_sym_entity_definition_token1,
  [2377] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(592), 1,
      aux_sym_entity_definition_token2,
  [2384] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(594), 1,
      aux_sym_file_header_token3,
  [2391] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(596), 1,
      anon_sym_COLON,
  [2398] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(598), 1,
      anon_sym_RPAREN,
  [2405] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(600), 1,
      anon_sym_RBRACE,
  [2412] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(602), 1,
      aux_sym_entity_block_token2,
  [2419] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(604), 1,
      anon_sym_COLON,
  [2426] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(606), 1,
      aux_sym_block_entity_item_token3,
  [2433] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(608), 1,
      aux_sym_cel_header_token1,
  [2440] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(610), 1,
      aux_sym_act_header_token1,
  [2447] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(432), 1,
      anon_sym_POUND,
  [2454] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(612), 1,
      aux_sym_entity_block_token2,
  [2461] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(614), 1,
      aux_sym_act_header_token1,
  [2468] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(616), 1,
      aux_sym_block_entity_item_token3,
  [2475] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(618), 1,
      anon_sym_LBRACE,
  [2482] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(620), 1,
      aux_sym_block_entity_item_token5,
  [2489] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(622), 1,
      aux_sym_entity_block_token1,
  [2496] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(624), 1,
      aux_sym_entity_block_token1,
  [2503] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(626), 1,
      aux_sym_block_entity_item_token3,
  [2510] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(628), 1,
      ts_builtin_sym_end,
  [2517] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(630), 1,
      aux_sym_file_header_token2,
  [2524] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(632), 1,
      aux_sym_cel_header_token2,
  [2531] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(634), 1,
      aux_sym_parenthetical_token1,
  [2538] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(636), 1,
      anon_sym_COLON,
  [2545] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(638), 1,
      aux_sym_entity_block_token2,
  [2552] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(640), 1,
      aux_sym_block_entity_item_token3,
  [2559] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(642), 1,
      aux_sym_entity_reference_token1,
  [2566] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(644), 1,
      aux_sym_entity_block_token2,
  [2573] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(646), 1,
      aux_sym_file_header_token2,
  [2580] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(498), 1,
      aux_sym_entity_definition_token1,
  [2587] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(648), 1,
      aux_sym_block_entity_item_token5,
  [2594] = 2,
    ACTIONS(381), 1,
      sym_line_comment,
    ACTIONS(650), 1,
      aux_sym_block_entity_item_token3,
  [2601] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(652), 1,
      aux_sym_file_header_token2,
  [2608] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(654), 1,
      aux_sym_file_header_token2,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 78,
  [SMALL_STATE(4)] = 156,
  [SMALL_STATE(5)] = 191,
  [SMALL_STATE(6)] = 220,
  [SMALL_STATE(7)] = 252,
  [SMALL_STATE(8)] = 284,
  [SMALL_STATE(9)] = 313,
  [SMALL_STATE(10)] = 342,
  [SMALL_STATE(11)] = 371,
  [SMALL_STATE(12)] = 400,
  [SMALL_STATE(13)] = 429,
  [SMALL_STATE(14)] = 455,
  [SMALL_STATE(15)] = 481,
  [SMALL_STATE(16)] = 507,
  [SMALL_STATE(17)] = 533,
  [SMALL_STATE(18)] = 559,
  [SMALL_STATE(19)] = 585,
  [SMALL_STATE(20)] = 611,
  [SMALL_STATE(21)] = 637,
  [SMALL_STATE(22)] = 663,
  [SMALL_STATE(23)] = 689,
  [SMALL_STATE(24)] = 715,
  [SMALL_STATE(25)] = 741,
  [SMALL_STATE(26)] = 767,
  [SMALL_STATE(27)] = 793,
  [SMALL_STATE(28)] = 816,
  [SMALL_STATE(29)] = 839,
  [SMALL_STATE(30)] = 862,
  [SMALL_STATE(31)] = 885,
  [SMALL_STATE(32)] = 908,
  [SMALL_STATE(33)] = 931,
  [SMALL_STATE(34)] = 954,
  [SMALL_STATE(35)] = 977,
  [SMALL_STATE(36)] = 1000,
  [SMALL_STATE(37)] = 1023,
  [SMALL_STATE(38)] = 1046,
  [SMALL_STATE(39)] = 1069,
  [SMALL_STATE(40)] = 1092,
  [SMALL_STATE(41)] = 1115,
  [SMALL_STATE(42)] = 1138,
  [SMALL_STATE(43)] = 1161,
  [SMALL_STATE(44)] = 1184,
  [SMALL_STATE(45)] = 1207,
  [SMALL_STATE(46)] = 1230,
  [SMALL_STATE(47)] = 1253,
  [SMALL_STATE(48)] = 1276,
  [SMALL_STATE(49)] = 1299,
  [SMALL_STATE(50)] = 1322,
  [SMALL_STATE(51)] = 1345,
  [SMALL_STATE(52)] = 1368,
  [SMALL_STATE(53)] = 1391,
  [SMALL_STATE(54)] = 1414,
  [SMALL_STATE(55)] = 1437,
  [SMALL_STATE(56)] = 1460,
  [SMALL_STATE(57)] = 1484,
  [SMALL_STATE(58)] = 1508,
  [SMALL_STATE(59)] = 1532,
  [SMALL_STATE(60)] = 1552,
  [SMALL_STATE(61)] = 1572,
  [SMALL_STATE(62)] = 1588,
  [SMALL_STATE(63)] = 1608,
  [SMALL_STATE(64)] = 1627,
  [SMALL_STATE(65)] = 1646,
  [SMALL_STATE(66)] = 1665,
  [SMALL_STATE(67)] = 1683,
  [SMALL_STATE(68)] = 1701,
  [SMALL_STATE(69)] = 1719,
  [SMALL_STATE(70)] = 1738,
  [SMALL_STATE(71)] = 1757,
  [SMALL_STATE(72)] = 1766,
  [SMALL_STATE(73)] = 1779,
  [SMALL_STATE(74)] = 1788,
  [SMALL_STATE(75)] = 1797,
  [SMALL_STATE(76)] = 1806,
  [SMALL_STATE(77)] = 1815,
  [SMALL_STATE(78)] = 1824,
  [SMALL_STATE(79)] = 1833,
  [SMALL_STATE(80)] = 1842,
  [SMALL_STATE(81)] = 1851,
  [SMALL_STATE(82)] = 1860,
  [SMALL_STATE(83)] = 1873,
  [SMALL_STATE(84)] = 1886,
  [SMALL_STATE(85)] = 1895,
  [SMALL_STATE(86)] = 1908,
  [SMALL_STATE(87)] = 1917,
  [SMALL_STATE(88)] = 1926,
  [SMALL_STATE(89)] = 1939,
  [SMALL_STATE(90)] = 1948,
  [SMALL_STATE(91)] = 1961,
  [SMALL_STATE(92)] = 1971,
  [SMALL_STATE(93)] = 1981,
  [SMALL_STATE(94)] = 1991,
  [SMALL_STATE(95)] = 2001,
  [SMALL_STATE(96)] = 2011,
  [SMALL_STATE(97)] = 2021,
  [SMALL_STATE(98)] = 2031,
  [SMALL_STATE(99)] = 2041,
  [SMALL_STATE(100)] = 2048,
  [SMALL_STATE(101)] = 2055,
  [SMALL_STATE(102)] = 2062,
  [SMALL_STATE(103)] = 2069,
  [SMALL_STATE(104)] = 2076,
  [SMALL_STATE(105)] = 2083,
  [SMALL_STATE(106)] = 2090,
  [SMALL_STATE(107)] = 2097,
  [SMALL_STATE(108)] = 2104,
  [SMALL_STATE(109)] = 2111,
  [SMALL_STATE(110)] = 2118,
  [SMALL_STATE(111)] = 2125,
  [SMALL_STATE(112)] = 2132,
  [SMALL_STATE(113)] = 2139,
  [SMALL_STATE(114)] = 2146,
  [SMALL_STATE(115)] = 2153,
  [SMALL_STATE(116)] = 2160,
  [SMALL_STATE(117)] = 2167,
  [SMALL_STATE(118)] = 2174,
  [SMALL_STATE(119)] = 2181,
  [SMALL_STATE(120)] = 2188,
  [SMALL_STATE(121)] = 2195,
  [SMALL_STATE(122)] = 2202,
  [SMALL_STATE(123)] = 2209,
  [SMALL_STATE(124)] = 2216,
  [SMALL_STATE(125)] = 2223,
  [SMALL_STATE(126)] = 2230,
  [SMALL_STATE(127)] = 2237,
  [SMALL_STATE(128)] = 2244,
  [SMALL_STATE(129)] = 2251,
  [SMALL_STATE(130)] = 2258,
  [SMALL_STATE(131)] = 2265,
  [SMALL_STATE(132)] = 2272,
  [SMALL_STATE(133)] = 2279,
  [SMALL_STATE(134)] = 2286,
  [SMALL_STATE(135)] = 2293,
  [SMALL_STATE(136)] = 2300,
  [SMALL_STATE(137)] = 2307,
  [SMALL_STATE(138)] = 2314,
  [SMALL_STATE(139)] = 2321,
  [SMALL_STATE(140)] = 2328,
  [SMALL_STATE(141)] = 2335,
  [SMALL_STATE(142)] = 2342,
  [SMALL_STATE(143)] = 2349,
  [SMALL_STATE(144)] = 2356,
  [SMALL_STATE(145)] = 2363,
  [SMALL_STATE(146)] = 2370,
  [SMALL_STATE(147)] = 2377,
  [SMALL_STATE(148)] = 2384,
  [SMALL_STATE(149)] = 2391,
  [SMALL_STATE(150)] = 2398,
  [SMALL_STATE(151)] = 2405,
  [SMALL_STATE(152)] = 2412,
  [SMALL_STATE(153)] = 2419,
  [SMALL_STATE(154)] = 2426,
  [SMALL_STATE(155)] = 2433,
  [SMALL_STATE(156)] = 2440,
  [SMALL_STATE(157)] = 2447,
  [SMALL_STATE(158)] = 2454,
  [SMALL_STATE(159)] = 2461,
  [SMALL_STATE(160)] = 2468,
  [SMALL_STATE(161)] = 2475,
  [SMALL_STATE(162)] = 2482,
  [SMALL_STATE(163)] = 2489,
  [SMALL_STATE(164)] = 2496,
  [SMALL_STATE(165)] = 2503,
  [SMALL_STATE(166)] = 2510,
  [SMALL_STATE(167)] = 2517,
  [SMALL_STATE(168)] = 2524,
  [SMALL_STATE(169)] = 2531,
  [SMALL_STATE(170)] = 2538,
  [SMALL_STATE(171)] = 2545,
  [SMALL_STATE(172)] = 2552,
  [SMALL_STATE(173)] = 2559,
  [SMALL_STATE(174)] = 2566,
  [SMALL_STATE(175)] = 2573,
  [SMALL_STATE(176)] = 2580,
  [SMALL_STATE(177)] = 2587,
  [SMALL_STATE(178)] = 2594,
  [SMALL_STATE(179)] = 2601,
  [SMALL_STATE(180)] = 2608,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(136),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(180),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(179),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(175),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(61),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(173),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(171),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(169),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(167),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [35] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [37] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(136),
  [40] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(180),
  [43] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(179),
  [46] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(175),
  [49] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(21),
  [52] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(20),
  [55] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(19),
  [58] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(61),
  [61] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(173),
  [64] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(47),
  [67] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(171),
  [70] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(169),
  [73] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(167),
  [76] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(5),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_prose_line_repeat1, 2),
  [83] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2),
  [85] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2), SHIFT_REPEAT(173),
  [88] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2), SHIFT_REPEAT(169),
  [91] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2), SHIFT_REPEAT(4),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prose_line, 1),
  [96] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_prose_line, 1),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 6, .production_id = 19),
  [100] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 6, .production_id = 19),
  [102] = {.entry = {.count = 1, .reusable = false}}, SHIFT(100),
  [104] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [106] = {.entry = {.count = 1, .reusable = false}}, SHIFT(113),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 5, .production_id = 14),
  [110] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 5, .production_id = 14),
  [112] = {.entry = {.count = 1, .reusable = false}}, SHIFT(102),
  [114] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [116] = {.entry = {.count = 1, .reusable = false}}, SHIFT(104),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 7, .production_id = 21),
  [120] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 7, .production_id = 21),
  [122] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [124] = {.entry = {.count = 1, .reusable = false}}, SHIFT(128),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 5, .production_id = 13),
  [128] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 5, .production_id = 13),
  [130] = {.entry = {.count = 1, .reusable = false}}, SHIFT(30),
  [132] = {.entry = {.count = 1, .reusable = false}}, SHIFT(168),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 27),
  [136] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 27),
  [138] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [140] = {.entry = {.count = 1, .reusable = false}}, SHIFT(134),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 2, .production_id = 1),
  [144] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 2, .production_id = 1),
  [146] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [148] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 3, .production_id = 4),
  [152] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 3, .production_id = 4),
  [154] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [156] = {.entry = {.count = 1, .reusable = false}}, SHIFT(133),
  [158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 7, .production_id = 20),
  [160] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 7, .production_id = 20),
  [162] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [164] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 7, .production_id = 19),
  [166] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 7, .production_id = 19),
  [168] = {.entry = {.count = 1, .reusable = false}}, SHIFT(125),
  [170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_adapter_statement, 5, .production_id = 16),
  [172] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_adapter_statement, 5, .production_id = 16),
  [174] = {.entry = {.count = 1, .reusable = false}}, SHIFT(105),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 21),
  [178] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 21),
  [180] = {.entry = {.count = 1, .reusable = false}}, SHIFT(99),
  [182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_definition, 4, .production_id = 10),
  [184] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_definition, 4, .production_id = 10),
  [186] = {.entry = {.count = 1, .reusable = false}}, SHIFT(110),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 9, .production_id = 27),
  [190] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 9, .production_id = 27),
  [192] = {.entry = {.count = 1, .reusable = false}}, SHIFT(143),
  [194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 1),
  [196] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 1),
  [198] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 1),
  [202] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 1),
  [204] = {.entry = {.count = 1, .reusable = false}}, SHIFT(32),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 1),
  [208] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 1),
  [210] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 6, .production_id = 14),
  [214] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 6, .production_id = 14),
  [216] = {.entry = {.count = 1, .reusable = false}}, SHIFT(115),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 3, .production_id = 1),
  [220] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 3, .production_id = 1),
  [222] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [224] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_reference, 3, .production_id = 5),
  [226] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_reference, 3, .production_id = 5),
  [228] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [230] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_act_header, 3, .production_id = 4),
  [232] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_act_header, 3, .production_id = 4),
  [234] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [236] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_header, 3, .production_id = 4),
  [238] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_header, 3, .production_id = 4),
  [240] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 10, .production_id = 33),
  [244] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 10, .production_id = 33),
  [246] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 4, .production_id = 8),
  [248] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 4, .production_id = 8),
  [250] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 28),
  [252] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 28),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 6, .production_id = 17),
  [256] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 6, .production_id = 17),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 2, .production_id = 2),
  [260] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 2, .production_id = 2),
  [262] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 2, .production_id = 2),
  [264] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 2, .production_id = 2),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 2, .production_id = 2),
  [268] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 2, .production_id = 2),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 11, .production_id = 36),
  [272] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 11, .production_id = 36),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dialogue_speaker, 4, .production_id = 12),
  [276] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dialogue_speaker, 4, .production_id = 12),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_definition, 6, .production_id = 18),
  [280] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_definition, 6, .production_id = 18),
  [282] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_adapter_statement, 5, .production_id = 15),
  [284] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_adapter_statement, 5, .production_id = 15),
  [286] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 29),
  [288] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 29),
  [290] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_line, 1),
  [292] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_line, 1),
  [294] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metadata_line, 4, .production_id = 9),
  [296] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_metadata_line, 4, .production_id = 9),
  [298] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 3, .production_id = 3),
  [300] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 3, .production_id = 3),
  [302] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_act_header, 4, .production_id = 8),
  [304] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_act_header, 4, .production_id = 8),
  [306] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block, 4),
  [308] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block, 4),
  [310] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block, 5),
  [312] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block, 5),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 10, .production_id = 32),
  [316] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 10, .production_id = 32),
  [318] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_header, 4, .production_id = 8),
  [320] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_header, 4, .production_id = 8),
  [322] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_newline, 1),
  [324] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_newline, 1),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthetical, 3, .production_id = 6),
  [328] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthetical, 3, .production_id = 6),
  [330] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 9, .production_id = 31),
  [332] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 9, .production_id = 31),
  [334] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 9, .production_id = 30),
  [336] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 9, .production_id = 30),
  [338] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block_end, 1),
  [340] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block_end, 1),
  [342] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 7, .production_id = 22),
  [344] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 7, .production_id = 22),
  [346] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_adapter_statement, 7, .production_id = 23),
  [348] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_adapter_statement, 7, .production_id = 23),
  [350] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 8, .production_id = 26),
  [352] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 8, .production_id = 26),
  [354] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 4, .production_id = 7),
  [356] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 4, .production_id = 7),
  [358] = {.entry = {.count = 1, .reusable = false}}, SHIFT(135),
  [360] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [362] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [364] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_entity_block_repeat1, 2), SHIFT_REPEAT(135),
  [367] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_entity_block_repeat1, 2), SHIFT_REPEAT(90),
  [370] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_entity_block_repeat1, 2), SHIFT_REPEAT(77),
  [373] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [375] = {.entry = {.count = 1, .reusable = false}}, SHIFT(111),
  [377] = {.entry = {.count = 1, .reusable = false}}, SHIFT(93),
  [379] = {.entry = {.count = 1, .reusable = false}}, SHIFT(91),
  [381] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [383] = {.entry = {.count = 1, .reusable = false}}, SHIFT(94),
  [385] = {.entry = {.count = 1, .reusable = false}}, SHIFT(152),
  [387] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_nested_block_repeat1, 2), SHIFT_REPEAT(111),
  [390] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_nested_block_repeat1, 2), SHIFT_REPEAT(157),
  [393] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_nested_block_repeat1, 2), SHIFT_REPEAT(77),
  [396] = {.entry = {.count = 1, .reusable = false}}, SHIFT(146),
  [398] = {.entry = {.count = 1, .reusable = false}}, SHIFT(83),
  [400] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_entity_item_repeat1, 2), SHIFT_REPEAT(146),
  [403] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_entity_item_repeat1, 2), SHIFT_REPEAT(96),
  [406] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_entity_item_repeat1, 2), SHIFT_REPEAT(77),
  [409] = {.entry = {.count = 1, .reusable = false}}, SHIFT(72),
  [411] = {.entry = {.count = 1, .reusable = false}}, SHIFT(97),
  [413] = {.entry = {.count = 1, .reusable = false}}, SHIFT(157),
  [415] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 2), SHIFT_REPEAT(176),
  [418] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 2), SHIFT_REPEAT(157),
  [421] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 2), SHIFT_REPEAT(77),
  [424] = {.entry = {.count = 1, .reusable = false}}, SHIFT(98),
  [426] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [428] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [432] = {.entry = {.count = 1, .reusable = false}}, SHIFT(112),
  [434] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 8, .production_id = 34),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [438] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block_content, 1),
  [440] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_block_entity_item_repeat1, 6, .production_id = 37),
  [442] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_nested_block, 9, .production_id = 35),
  [444] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 10, .production_id = 25),
  [446] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 11, .production_id = 25),
  [448] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_property, 5, .production_id = 24),
  [450] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_deeper_nested_block, 8, .production_id = 38),
  [452] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_comment, 4),
  [454] = {.entry = {.count = 1, .reusable = false}}, SHIFT(119),
  [456] = {.entry = {.count = 1, .reusable = false}}, SHIFT(84),
  [458] = {.entry = {.count = 1, .reusable = false}}, SHIFT(121),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [462] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 5, .production_id = 25),
  [464] = {.entry = {.count = 1, .reusable = true}}, SHIFT(116),
  [466] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [468] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [470] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_deeper_nested_block, 9, .production_id = 38),
  [472] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 6, .production_id = 39),
  [474] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [476] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [478] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [480] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_nested_block, 8, .production_id = 35),
  [482] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [484] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [486] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [488] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [490] = {.entry = {.count = 1, .reusable = false}}, SHIFT(148),
  [492] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [494] = {.entry = {.count = 1, .reusable = false}}, SHIFT(161),
  [496] = {.entry = {.count = 1, .reusable = false}}, SHIFT(106),
  [498] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [500] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [502] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [504] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [506] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [508] = {.entry = {.count = 1, .reusable = false}}, SHIFT(82),
  [510] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [512] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [514] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [516] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [518] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [520] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [522] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [524] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [526] = {.entry = {.count = 1, .reusable = false}}, SHIFT(172),
  [528] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [530] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [532] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [534] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [536] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [538] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [540] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [542] = {.entry = {.count = 1, .reusable = true}}, SHIFT(131),
  [544] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [546] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [548] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [550] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [552] = {.entry = {.count = 1, .reusable = false}}, SHIFT(107),
  [554] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [556] = {.entry = {.count = 1, .reusable = false}}, SHIFT(109),
  [558] = {.entry = {.count = 1, .reusable = false}}, SHIFT(120),
  [560] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [562] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block_start, 4, .production_id = 11),
  [564] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [566] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [568] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [570] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [572] = {.entry = {.count = 1, .reusable = false}}, SHIFT(118),
  [574] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [576] = {.entry = {.count = 1, .reusable = false}}, SHIFT(138),
  [578] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [580] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [582] = {.entry = {.count = 1, .reusable = false}}, SHIFT(124),
  [584] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [586] = {.entry = {.count = 1, .reusable = false}}, SHIFT(126),
  [588] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [590] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [592] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [594] = {.entry = {.count = 1, .reusable = false}}, SHIFT(40),
  [596] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [598] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [600] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [602] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [604] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [606] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [608] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [610] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [612] = {.entry = {.count = 1, .reusable = true}}, SHIFT(162),
  [614] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [616] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [618] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [620] = {.entry = {.count = 1, .reusable = false}}, SHIFT(165),
  [622] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [624] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [626] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [628] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [630] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [632] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [634] = {.entry = {.count = 1, .reusable = false}}, SHIFT(150),
  [636] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [638] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [640] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [642] = {.entry = {.count = 1, .reusable = false}}, SHIFT(151),
  [644] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [646] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [648] = {.entry = {.count = 1, .reusable = false}}, SHIFT(178),
  [650] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [652] = {.entry = {.count = 1, .reusable = true}}, SHIFT(156),
  [654] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_cuneiform(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
