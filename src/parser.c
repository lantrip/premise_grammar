#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef _MSC_VER
#pragma optimize("", off)
#elif defined(__clang__)
#pragma clang optimize off
#elif defined(__GNUC__)
#pragma GCC optimize ("O0")
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 205
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 88
#define ALIAS_COUNT 2
#define TOKEN_COUNT 55
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 31
#define MAX_ALIAS_SEQUENCE_LENGTH 11
#define PRODUCTION_ID_COUNT 43

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
  anon_sym_Beat = 15,
  anon_sym_SLASH_SLASH = 16,
  anon_sym_Treatment = 17,
  anon_sym_SLASH = 18,
  anon_sym_Narrative = 19,
  anon_sym_AT = 20,
  aux_sym_entity_definition_token1 = 21,
  aux_sym_entity_definition_token2 = 22,
  aux_sym_entity_block_token1 = 23,
  aux_sym_entity_block_token2 = 24,
  anon_sym_entities = 25,
  anon_sym_characters = 26,
  anon_sym_locations = 27,
  anon_sym_items = 28,
  anon_sym_creatures = 29,
  anon_sym_eras = 30,
  anon_sym_world_eras = 31,
  anon_sym_LBRACE = 32,
  anon_sym_RBRACE = 33,
  aux_sym_block_entity_item_token1 = 34,
  aux_sym_block_entity_item_token2 = 35,
  aux_sym_block_entity_item_token3 = 36,
  aux_sym_block_entity_item_token4 = 37,
  aux_sym_block_entity_item_token5 = 38,
  anon_sym_POUND = 39,
  aux_sym_block_comment_token1 = 40,
  anon_sym_ATimport = 41,
  anon_sym_LPAREN = 42,
  anon_sym_DQUOTE = 43,
  aux_sym_import_statement_token1 = 44,
  anon_sym_SQUOTE = 45,
  aux_sym_import_statement_token2 = 46,
  aux_sym_import_statement_token3 = 47,
  anon_sym_RPAREN = 48,
  aux_sym_import_statement_token4 = 49,
  anon_sym_ATadapter = 50,
  aux_sym_adapter_statement_token1 = 51,
  aux_sym_entity_reference_token1 = 52,
  aux_sym_parenthetical_token1 = 53,
  sym_prose_text = 54,
  sym_source_file = 55,
  sym_line = 56,
  sym_file_header = 57,
  sym_act_header = 58,
  sym_scene_header = 59,
  sym_cel_header = 60,
  sym_content_type_beat = 61,
  sym_content_type_treatment = 62,
  sym_content_type_narrative = 63,
  sym_entity_definition = 64,
  sym_entity_block = 65,
  sym_entity_block_start = 66,
  sym_entity_block_end = 67,
  sym_entity_block_content = 68,
  sym_block_entity_item = 69,
  sym_block_property = 70,
  sym_block_comment = 71,
  sym_nested_block = 72,
  sym_deeper_nested_block = 73,
  sym_import_statement = 74,
  sym_adapter_statement = 75,
  sym_metadata_line = 76,
  sym_prose_line = 77,
  sym_entity_reference = 78,
  sym_dialogue_speaker = 79,
  sym_parenthetical = 80,
  sym_newline = 81,
  aux_sym_source_file_repeat1 = 82,
  aux_sym_entity_block_repeat1 = 83,
  aux_sym_block_entity_item_repeat1 = 84,
  aux_sym_nested_block_repeat1 = 85,
  aux_sym_deeper_nested_block_repeat1 = 86,
  aux_sym_prose_line_repeat1 = 87,
  alias_sym_ref_close = 88,
  alias_sym_ref_open = 89,
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
  [anon_sym_Beat] = "Beat",
  [anon_sym_SLASH_SLASH] = "//",
  [anon_sym_Treatment] = "Treatment",
  [anon_sym_SLASH] = "/",
  [anon_sym_Narrative] = "Narrative",
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
  [anon_sym_Beat] = anon_sym_Beat,
  [anon_sym_SLASH_SLASH] = anon_sym_SLASH_SLASH,
  [anon_sym_Treatment] = anon_sym_Treatment,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_Narrative] = anon_sym_Narrative,
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
  [anon_sym_Beat] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Treatment] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_Narrative] = {
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
  [7] = {.index = 7, .length = 1},
  [8] = {.index = 8, .length = 2},
  [9] = {.index = 10, .length = 2},
  [10] = {.index = 12, .length = 1},
  [11] = {.index = 13, .length = 2},
  [12] = {.index = 15, .length = 2},
  [13] = {.index = 17, .length = 1},
  [14] = {.index = 18, .length = 1},
  [15] = {.index = 19, .length = 2},
  [16] = {.index = 21, .length = 1},
  [17] = {.index = 22, .length = 1},
  [18] = {.index = 23, .length = 1},
  [19] = {.index = 24, .length = 1},
  [20] = {.index = 25, .length = 3},
  [21] = {.index = 28, .length = 3},
  [22] = {.index = 31, .length = 1},
  [23] = {.index = 32, .length = 3},
  [24] = {.index = 35, .length = 2},
  [25] = {.index = 37, .length = 2},
  [26] = {.index = 39, .length = 2},
  [27] = {.index = 41, .length = 2},
  [28] = {.index = 43, .length = 1},
  [29] = {.index = 44, .length = 4},
  [30] = {.index = 48, .length = 2},
  [31] = {.index = 50, .length = 2},
  [32] = {.index = 52, .length = 2},
  [33] = {.index = 54, .length = 2},
  [34] = {.index = 56, .length = 3},
  [35] = {.index = 59, .length = 3},
  [36] = {.index = 62, .length = 3},
  [37] = {.index = 65, .length = 2},
  [38] = {.index = 67, .length = 1},
  [39] = {.index = 68, .length = 3},
  [40] = {.index = 71, .length = 2},
  [41] = {.index = 73, .length = 1},
  [42] = {.index = 74, .length = 2},
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
    {field_content, 2},
  [6] =
    {field_entity, 1},
  [7] =
    {field_direction, 1},
  [8] =
    {field_key, 0},
    {field_value, 3},
  [10] =
    {field_proportion, 3},
    {field_title, 2},
  [12] =
    {field_content, 3},
  [13] =
    {field_meta_key, 1},
    {field_meta_value, 3},
  [15] =
    {field_entity_type, 1},
    {field_name, 3},
  [17] =
    {field_block_type, 1},
  [18] =
    {field_speaker, 1},
  [19] =
    {field_location_type, 4},
    {field_title, 2},
  [21] =
    {field_content, 4},
  [22] =
    {field_path, 3},
  [23] =
    {field_adapter_name, 2},
  [24] =
    {field_adapter_path, 3},
  [25] =
    {field_location_type, 4},
    {field_proportion, 5},
    {field_title, 2},
  [28] =
    {field_description, 5},
    {field_entity_type, 1},
    {field_name, 3},
  [31] =
    {field_path, 4},
  [32] =
    {field_location_type, 4},
    {field_time, 6},
    {field_title, 2},
  [35] =
    {field_alias, 6},
    {field_path, 3},
  [37] =
    {field_path, 3},
    {field_selector, 6},
  [39] =
    {field_adapter_path, 3},
    {field_timing, 6},
  [41] =
    {field_prop_key, 1},
    {field_prop_value, 3},
  [43] =
    {field_entity_name, 3},
  [44] =
    {field_location_type, 4},
    {field_proportion, 7},
    {field_time, 6},
    {field_title, 2},
  [48] =
    {field_alias, 7},
    {field_path, 4},
  [50] =
    {field_path, 4},
    {field_selector, 7},
  [52] =
    {field_path, 3},
    {field_selector, 7},
  [54] =
    {field_path, 4},
    {field_selector, 8},
  [56] =
    {field_alias, 6},
    {field_path, 3},
    {field_selector, 8},
  [59] =
    {field_alias, 7},
    {field_path, 4},
    {field_selector, 9},
  [62] =
    {field_alias, 6},
    {field_path, 3},
    {field_selector, 9},
  [65] =
    {field_entity_desc, 6},
    {field_entity_name, 3},
  [67] =
    {field_nested_type, 2},
  [68] =
    {field_alias, 7},
    {field_path, 4},
    {field_selector, 10},
  [71] =
    {field_item_key, 1},
    {field_item_value, 4},
  [73] =
    {field_key, 1},
  [74] =
    {field_nested_key, 1},
    {field_nested_value, 4},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
  [6] = {
    [0] = alias_sym_ref_open,
    [2] = alias_sym_ref_close,
  },
  [14] = {
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
  [77] = 77,
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
  [97] = 47,
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
  [181] = 181,
  [182] = 182,
  [183] = 183,
  [184] = 184,
  [185] = 185,
  [186] = 186,
  [187] = 187,
  [188] = 188,
  [189] = 189,
  [190] = 190,
  [191] = 191,
  [192] = 192,
  [193] = 193,
  [194] = 194,
  [195] = 195,
  [196] = 196,
  [197] = 197,
  [198] = 198,
  [199] = 199,
  [200] = 200,
  [201] = 201,
  [202] = 202,
  [203] = 203,
  [204] = 204,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(274);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '"') ADVANCE(315);
      if (lookahead == '#') ADVANCE(307);
      if (lookahead == '\'') ADVANCE(318);
      if (lookahead == '(') ADVANCE(313);
      if (lookahead == ')') ADVANCE(323);
      if (lookahead == '-') ADVANCE(206);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == ':') ADVANCE(144);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(222);
      if (lookahead == 'B') ADVANCE(138);
      if (lookahead == 'N') ADVANCE(136);
      if (lookahead == 'T') ADVANCE(140);
      if (lookahead == 'c') ADVANCE(57);
      if (lookahead == 'e') ADVANCE(70);
      if (lookahead == 'i') ADVANCE(101);
      if (lookahead == 'l') ADVANCE(73);
      if (lookahead == 'w') ADVANCE(74);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '}') ADVANCE(294);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(1);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(274);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '"') ADVANCE(315);
      if (lookahead == '#') ADVANCE(307);
      if (lookahead == '\'') ADVANCE(318);
      if (lookahead == '(') ADVANCE(313);
      if (lookahead == ')') ADVANCE(323);
      if (lookahead == '-') ADVANCE(206);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == ':') ADVANCE(144);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(222);
      if (lookahead == 'B') ADVANCE(138);
      if (lookahead == 'N') ADVANCE(136);
      if (lookahead == 'T') ADVANCE(140);
      if (lookahead == 'c') ADVANCE(57);
      if (lookahead == 'e') ADVANCE(70);
      if (lookahead == 'i') ADVANCE(101);
      if (lookahead == 'l') ADVANCE(73);
      if (lookahead == 'w') ADVANCE(74);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '}') ADVANCE(294);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(1);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(274);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '#') ADVANCE(135);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(273);
      END_STATE();
    case 3:
      if (lookahead == '\n') ADVANCE(274);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(3);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(299);
      END_STATE();
    case 5:
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '"') ADVANCE(315);
      if (lookahead == '#') ADVANCE(135);
      if (lookahead == '\'') ADVANCE(318);
      if (lookahead == ':') ADVANCE(144);
      if (lookahead == '}') ADVANCE(294);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 6:
      if (lookahead == '\n') ADVANCE(300);
      if (lookahead == '#') ADVANCE(324);
      if (lookahead == 'a') ADVANCE(95);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      END_STATE();
    case 7:
      if (lookahead == '\n') ADVANCE(301);
      if (lookahead == '#') ADVANCE(324);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(14);
      END_STATE();
    case 8:
      if (lookahead == '\n') ADVANCE(303);
      if (lookahead == '@') ADVANCE(107);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(30);
      END_STATE();
    case 9:
      if (lookahead == '\n') ADVANCE(302);
      if (lookahead == '\r') ADVANCE(10);
      if (lookahead == '"') ADVANCE(315);
      if (lookahead == '#') ADVANCE(135);
      if (lookahead == '\'') ADVANCE(318);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == ')') ADVANCE(323);
      if (lookahead == ':') ADVANCE(145);
      if (lookahead == 'c') ADVANCE(242);
      if (lookahead == 'e') ADVANCE(248);
      if (lookahead == 'i') ADVANCE(267);
      if (lookahead == 'l') ADVANCE(250);
      if (lookahead == 'w') ADVANCE(251);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '}') ADVANCE(294);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 10:
      if (lookahead == '\n') ADVANCE(302);
      if (lookahead == ':') ADVANCE(304);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(29);
      END_STATE();
    case 11:
      if (lookahead == '#') ADVANCE(307);
      if (lookahead == '-') ADVANCE(206);
      if (lookahead == '@') ADVANCE(221);
      if (lookahead == '}') ADVANCE(294);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(11)
      END_STATE();
    case 12:
      if (lookahead == '#') ADVANCE(135);
      if (lookahead == ':') ADVANCE(144);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(150);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(151);
      END_STATE();
    case 13:
      if (lookahead == '#') ADVANCE(324);
      if (lookahead == 'a') ADVANCE(95);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      END_STATE();
    case 14:
      if (lookahead == '#') ADVANCE(324);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(14);
      END_STATE();
    case 15:
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(197);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(') ADVANCE(198);
      END_STATE();
    case 16:
      if (lookahead == '#') ADVANCE(128);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(305);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(306);
      END_STATE();
    case 17:
      if (lookahead == '#') ADVANCE(124);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(328);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(329);
      END_STATE();
    case 18:
      if (lookahead == '#') ADVANCE(125);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(330);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(331);
      END_STATE();
    case 19:
      if (lookahead == '#') ADVANCE(133);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(207);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')') ADVANCE(208);
      END_STATE();
    case 20:
      if (lookahead == '#') ADVANCE(132);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(295);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':' &&
          lookahead != '{') ADVANCE(296);
      END_STATE();
    case 21:
      if (lookahead == '#') ADVANCE(131);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(297);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '{') ADVANCE(298);
      END_STATE();
    case 22:
      if (lookahead == '#') ADVANCE(126);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(319);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(320);
      END_STATE();
    case 23:
      if (lookahead == '#') ADVANCE(127);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(316);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(317);
      END_STATE();
    case 24:
      if (lookahead == '#') ADVANCE(130);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(204);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '-') ADVANCE(205);
      END_STATE();
    case 25:
      if (lookahead == '%') ADVANCE(27);
      if (lookahead == '.') ADVANCE(113);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(25);
      END_STATE();
    case 26:
      if (lookahead == '%') ADVANCE(27);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(26);
      END_STATE();
    case 27:
      if (lookahead == ')') ADVANCE(199);
      END_STATE();
    case 28:
      if (lookahead == ':') ADVANCE(327);
      END_STATE();
    case 29:
      if (lookahead == ':') ADVANCE(304);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(29);
      END_STATE();
    case 30:
      if (lookahead == '@') ADVANCE(107);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(30);
      END_STATE();
    case 31:
      if (lookahead == '_') ADVANCE(54);
      END_STATE();
    case 32:
      if (lookahead == 'a') ADVANCE(88);
      END_STATE();
    case 33:
      if (lookahead == 'a') ADVANCE(42);
      END_STATE();
    case 34:
      if (lookahead == 'a') ADVANCE(77);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(97);
      END_STATE();
    case 36:
      if (lookahead == 'a') ADVANCE(103);
      END_STATE();
    case 37:
      if (lookahead == 'a') ADVANCE(82);
      END_STATE();
    case 38:
      if (lookahead == 'a') ADVANCE(98);
      END_STATE();
    case 39:
      if (lookahead == 'a') ADVANCE(105);
      END_STATE();
    case 40:
      if (lookahead == 'a') ADVANCE(94);
      END_STATE();
    case 41:
      if (lookahead == 'a') ADVANCE(106);
      END_STATE();
    case 42:
      if (lookahead == 'c') ADVANCE(108);
      END_STATE();
    case 43:
      if (lookahead == 'c') ADVANCE(39);
      END_STATE();
    case 44:
      if (lookahead == 'd') ADVANCE(31);
      END_STATE();
    case 45:
      if (lookahead == 'd') ADVANCE(34);
      END_STATE();
    case 46:
      if (lookahead == 'e') ADVANCE(72);
      END_STATE();
    case 47:
      if (lookahead == 'e') ADVANCE(219);
      END_STATE();
    case 48:
      if (lookahead == 'e') ADVANCE(66);
      END_STATE();
    case 49:
      if (lookahead == 'e') ADVANCE(90);
      END_STATE();
    case 50:
      if (lookahead == 'e') ADVANCE(91);
      END_STATE();
    case 51:
      if (lookahead == 'e') ADVANCE(80);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(85);
      END_STATE();
    case 53:
      if (lookahead == 'e') ADVANCE(36);
      END_STATE();
    case 54:
      if (lookahead == 'e') ADVANCE(83);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(38);
      END_STATE();
    case 56:
      if (lookahead == 'g') ADVANCE(28);
      END_STATE();
    case 57:
      if (lookahead == 'h') ADVANCE(37);
      if (lookahead == 'r') ADVANCE(55);
      END_STATE();
    case 58:
      if (lookahead == 'i') ADVANCE(110);
      END_STATE();
    case 59:
      if (lookahead == 'i') ADVANCE(75);
      END_STATE();
    case 60:
      if (lookahead == 'i') ADVANCE(69);
      END_STATE();
    case 61:
      if (lookahead == 'i') ADVANCE(68);
      END_STATE();
    case 62:
      if (lookahead == 'i') ADVANCE(49);
      END_STATE();
    case 63:
      if (lookahead == 'i') ADVANCE(102);
      END_STATE();
    case 64:
      if (lookahead == 'l') ADVANCE(44);
      END_STATE();
    case 65:
      if (lookahead == 'm') ADVANCE(78);
      END_STATE();
    case 66:
      if (lookahead == 'm') ADVANCE(89);
      END_STATE();
    case 67:
      if (lookahead == 'm') ADVANCE(46);
      END_STATE();
    case 68:
      if (lookahead == 'm') ADVANCE(60);
      END_STATE();
    case 69:
      if (lookahead == 'n') ADVANCE(56);
      END_STATE();
    case 70:
      if (lookahead == 'n') ADVANCE(96);
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 71:
      if (lookahead == 'n') ADVANCE(92);
      END_STATE();
    case 72:
      if (lookahead == 'n') ADVANCE(100);
      END_STATE();
    case 73:
      if (lookahead == 'o') ADVANCE(43);
      END_STATE();
    case 74:
      if (lookahead == 'o') ADVANCE(79);
      END_STATE();
    case 75:
      if (lookahead == 'o') ADVANCE(71);
      END_STATE();
    case 76:
      if (lookahead == 'o') ADVANCE(86);
      END_STATE();
    case 77:
      if (lookahead == 'p') ADVANCE(104);
      END_STATE();
    case 78:
      if (lookahead == 'p') ADVANCE(76);
      END_STATE();
    case 79:
      if (lookahead == 'r') ADVANCE(64);
      END_STATE();
    case 80:
      if (lookahead == 'r') ADVANCE(325);
      END_STATE();
    case 81:
      if (lookahead == 'r') ADVANCE(87);
      END_STATE();
    case 82:
      if (lookahead == 'r') ADVANCE(33);
      END_STATE();
    case 83:
      if (lookahead == 'r') ADVANCE(40);
      END_STATE();
    case 84:
      if (lookahead == 'r') ADVANCE(50);
      END_STATE();
    case 85:
      if (lookahead == 'r') ADVANCE(93);
      END_STATE();
    case 86:
      if (lookahead == 'r') ADVANCE(99);
      END_STATE();
    case 87:
      if (lookahead == 'r') ADVANCE(41);
      END_STATE();
    case 88:
      if (lookahead == 's') ADVANCE(288);
      END_STATE();
    case 89:
      if (lookahead == 's') ADVANCE(284);
      END_STATE();
    case 90:
      if (lookahead == 's') ADVANCE(278);
      END_STATE();
    case 91:
      if (lookahead == 's') ADVANCE(286);
      END_STATE();
    case 92:
      if (lookahead == 's') ADVANCE(282);
      END_STATE();
    case 93:
      if (lookahead == 's') ADVANCE(280);
      END_STATE();
    case 94:
      if (lookahead == 's') ADVANCE(290);
      END_STATE();
    case 95:
      if (lookahead == 's') ADVANCE(111);
      END_STATE();
    case 96:
      if (lookahead == 't') ADVANCE(63);
      END_STATE();
    case 97:
      if (lookahead == 't') ADVANCE(211);
      END_STATE();
    case 98:
      if (lookahead == 't') ADVANCE(109);
      END_STATE();
    case 99:
      if (lookahead == 't') ADVANCE(310);
      END_STATE();
    case 100:
      if (lookahead == 't') ADVANCE(215);
      END_STATE();
    case 101:
      if (lookahead == 't') ADVANCE(48);
      END_STATE();
    case 102:
      if (lookahead == 't') ADVANCE(62);
      END_STATE();
    case 103:
      if (lookahead == 't') ADVANCE(67);
      END_STATE();
    case 104:
      if (lookahead == 't') ADVANCE(51);
      END_STATE();
    case 105:
      if (lookahead == 't') ADVANCE(59);
      END_STATE();
    case 106:
      if (lookahead == 't') ADVANCE(58);
      END_STATE();
    case 107:
      if (lookahead == 't') ADVANCE(61);
      END_STATE();
    case 108:
      if (lookahead == 't') ADVANCE(52);
      END_STATE();
    case 109:
      if (lookahead == 'u') ADVANCE(84);
      END_STATE();
    case 110:
      if (lookahead == 'v') ADVANCE(47);
      END_STATE();
    case 111:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(322);
      END_STATE();
    case 112:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(112);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(273);
      END_STATE();
    case 113:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(26);
      END_STATE();
    case 114:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(274);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(332);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 115:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(313);
      if (lookahead == '-') ADVANCE(206);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(333);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 116:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(313);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(334);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 117:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == ':') ADVANCE(144);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(335);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 118:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(336);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 119:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(300);
      if (lookahead == '\r') ADVANCE(6);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == ')') ADVANCE(323);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(337);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 120:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(301);
      if (lookahead == '\r') ADVANCE(7);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == ')') ADVANCE(323);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(338);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 121:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(303);
      if (lookahead == '\r') ADVANCE(8);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(339);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 122:
      if (eof) ADVANCE(123);
      if (lookahead == '\n') ADVANCE(302);
      if (lookahead == '\r') ADVANCE(10);
      if (lookahead == '"') ADVANCE(315);
      if (lookahead == '#') ADVANCE(135);
      if (lookahead == '\'') ADVANCE(318);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == ')') ADVANCE(323);
      if (lookahead == ':') ADVANCE(145);
      if (lookahead == 'c') ADVANCE(242);
      if (lookahead == 'e') ADVANCE(248);
      if (lookahead == 'i') ADVANCE(267);
      if (lookahead == 'l') ADVANCE(250);
      if (lookahead == 'w') ADVANCE(251);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '}') ADVANCE(294);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(9);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(329);
      if (lookahead == '}') ADVANCE(135);
      if (lookahead != 0) ADVANCE(124);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(331);
      if (lookahead == ')') ADVANCE(135);
      if (lookahead != 0) ADVANCE(125);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(320);
      if (lookahead == '\'') ADVANCE(135);
      if (lookahead != 0) ADVANCE(126);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(317);
      if (lookahead == '"') ADVANCE(135);
      if (lookahead != 0) ADVANCE(127);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r') ADVANCE(135);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(128);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '(') ADVANCE(135);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(129);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '-') ADVANCE(135);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(130);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '{') ADVANCE(135);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(131);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == ':' ||
          lookahead == '{') ADVANCE(135);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(132);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')') ADVANCE(135);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(133);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(135);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(134);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(135);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'a') ADVANCE(81);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(143);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'a') ADVANCE(176);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'e') ADVANCE(35);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(143);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'e') ADVANCE(158);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'r') ADVANCE(53);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(143);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'r') ADVANCE(166);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(143);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(304);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(151);
      if (lookahead == '\r') ADVANCE(148);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(146);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(151);
      if (lookahead == '\r') ADVANCE(149);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(147);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(151);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(148);
      if (lookahead != 0) ADVANCE(186);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(151);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(151);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(150);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(151);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(151);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead != 0) ADVANCE(186);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r') ADVANCE(152);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == 'B') ADVANCE(139);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(153);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r') ADVANCE(152);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == 'N') ADVANCE(137);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(154);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r') ADVANCE(152);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == 'T') ADVANCE(141);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(155);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r') ADVANCE(152);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(156);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '#') ADVANCE(135);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(157);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(186);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'a') ADVANCE(178);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'a') ADVANCE(173);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'a') ADVANCE(183);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'a') ADVANCE(182);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'd') ADVANCE(159);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'e') ADVANCE(170);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'e') ADVANCE(220);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'e') ADVANCE(174);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'e') ADVANCE(160);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'i') ADVANCE(184);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'm') ADVANCE(172);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'm') ADVANCE(163);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'n') ADVANCE(181);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'o') ADVANCE(175);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'p') ADVANCE(171);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'p') ADVANCE(179);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(326);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(180);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(177);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(161);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(212);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(165);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(311);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(216);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(167);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(169);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'v') ADVANCE(164);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(186);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(123);
      if (lookahead == '\r') ADVANCE(148);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == 'B') ADVANCE(139);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(146);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(123);
      if (lookahead == '\r') ADVANCE(148);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == 'N') ADVANCE(137);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(146);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(123);
      if (lookahead == '\r') ADVANCE(148);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == 'T') ADVANCE(141);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(146);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(123);
      if (lookahead == '\r') ADVANCE(148);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(146);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(123);
      if (lookahead == '\r') ADVANCE(152);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == 'B') ADVANCE(139);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(153);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(123);
      if (lookahead == '\r') ADVANCE(152);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == 'N') ADVANCE(137);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(154);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(123);
      if (lookahead == '\r') ADVANCE(152);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == 'T') ADVANCE(141);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(155);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(123);
      if (lookahead == '\r') ADVANCE(152);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(314);
      if (lookahead == '/') ADVANCE(218);
      if (lookahead == '=') ADVANCE(196);
      if (lookahead == '@') ADVANCE(225);
      if (lookahead == '{') ADVANCE(293);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(156);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(186);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(142);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(200);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(201);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(aux_sym_act_header_token1);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(197);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(') ADVANCE(198);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(aux_sym_act_header_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(') ADVANCE(198);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(aux_sym_act_header_token2);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      if (lookahead == '=') ADVANCE(202);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      if (lookahead == '=') ADVANCE(203);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(aux_sym_cel_header_token1);
      if (lookahead == '#') ADVANCE(130);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(204);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '-') ADVANCE(205);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(aux_sym_cel_header_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '-') ADVANCE(205);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(aux_sym_cel_header_token2);
      if (lookahead == '#') ADVANCE(133);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(207);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')') ADVANCE(208);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(aux_sym_cel_header_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')') ADVANCE(208);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH_SLASH);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH_SLASH);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(anon_sym_Beat);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(anon_sym_Beat);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead == '/') ADVANCE(209);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead == '/') ADVANCE(210);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(anon_sym_Treatment);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(anon_sym_Treatment);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '/') ADVANCE(213);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '/') ADVANCE(214);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_Narrative);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(anon_sym_Narrative);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(anon_sym_AT);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(45);
      if (lookahead == 'i') ADVANCE(65);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(342);
      if (lookahead == 'i') ADVANCE(347);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(342);
      if (lookahead == 'i') ADVANCE(347);
      if (lookahead == 't') ADVANCE(346);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(162);
      if (lookahead == 'i') ADVANCE(168);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == '_') ADVANCE(241);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(258);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(234);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(254);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(266);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(269);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(264);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'c') ADVANCE(231);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'c') ADVANCE(270);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'd') ADVANCE(226);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(247);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(230);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(260);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(256);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(261);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'h') ADVANCE(229);
      if (lookahead == 'r') ADVANCE(237);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'i') ADVANCE(252);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'i') ADVANCE(238);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'i') ADVANCE(268);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'l') ADVANCE(235);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'm') ADVANCE(259);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'n') ADVANCE(265);
      if (lookahead == 'r') ADVANCE(227);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'n') ADVANCE(262);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'o') ADVANCE(233);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'o') ADVANCE(253);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'o') ADVANCE(249);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(246);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(228);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(232);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(263);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(289);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(285);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(279);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(287);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(283);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(281);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(291);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(245);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(271);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(236);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(244);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(243);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(239);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'u') ADVANCE(257);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(aux_sym_entity_definition_token2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(112);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(273);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(aux_sym_entity_block_token1);
      if (lookahead == '\n') ADVANCE(274);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(3);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(aux_sym_entity_block_token2);
      if (lookahead == '\n') ADVANCE(151);
      if (lookahead == '\r') ADVANCE(149);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(147);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(aux_sym_entity_block_token2);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(276);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(277);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(aux_sym_entity_block_token2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(277);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(anon_sym_entities);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(anon_sym_entities);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(anon_sym_characters);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(anon_sym_characters);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(anon_sym_locations);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(anon_sym_locations);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(anon_sym_items);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(anon_sym_items);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(anon_sym_creatures);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(anon_sym_creatures);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(anon_sym_eras);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(anon_sym_eras);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(anon_sym_world_eras);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(anon_sym_world_eras);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(272);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(186);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token1);
      if (lookahead == '#') ADVANCE(132);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(295);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':' &&
          lookahead != '{') ADVANCE(296);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':' &&
          lookahead != '{') ADVANCE(296);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token2);
      if (lookahead == '#') ADVANCE(131);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(297);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '{') ADVANCE(298);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '{') ADVANCE(298);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == '#') ADVANCE(324);
      if (lookahead == 'a') ADVANCE(95);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(13);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == '#') ADVANCE(324);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(14);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == ':') ADVANCE(304);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(29);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == '@') ADVANCE(107);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(30);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token4);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(304);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token5);
      if (lookahead == '#') ADVANCE(128);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(305);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(306);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token5);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(306);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(anon_sym_POUND);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(135);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(aux_sym_block_comment_token1);
      if (lookahead == '#') ADVANCE(128);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(308);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(309);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(aux_sym_block_comment_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(309);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(anon_sym_ATimport);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(anon_sym_ATimport);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(25);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(186);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(aux_sym_import_statement_token1);
      if (lookahead == '#') ADVANCE(127);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(316);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(317);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(aux_sym_import_statement_token1);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(317);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(aux_sym_import_statement_token2);
      if (lookahead == '#') ADVANCE(126);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(319);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(320);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(aux_sym_import_statement_token2);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(320);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(aux_sym_import_statement_token3);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(321);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(322);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(aux_sym_import_statement_token3);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(322);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(aux_sym_import_statement_token4);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(anon_sym_ATadapter);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(anon_sym_ATadapter);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(186);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(185);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(aux_sym_adapter_statement_token1);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(aux_sym_entity_reference_token1);
      if (lookahead == '#') ADVANCE(124);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(328);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(329);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(aux_sym_entity_reference_token1);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(329);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(aux_sym_parenthetical_token1);
      if (lookahead == '#') ADVANCE(125);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(330);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(331);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(aux_sym_parenthetical_token1);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(331);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(274);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(332);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(313);
      if (lookahead == '-') ADVANCE(206);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(333);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(313);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(334);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == ':') ADVANCE(144);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(335);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(299);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(336);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(300);
      if (lookahead == '\r') ADVANCE(6);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == ')') ADVANCE(323);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == 'a') ADVANCE(355);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(337);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(301);
      if (lookahead == '\r') ADVANCE(7);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == ')') ADVANCE(323);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(223);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(338);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(303);
      if (lookahead == '\r') ADVANCE(8);
      if (lookahead == '#') ADVANCE(134);
      if (lookahead == '(') ADVANCE(312);
      if (lookahead == '/') ADVANCE(217);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '@') ADVANCE(224);
      if (lookahead == '{') ADVANCE(292);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(339);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(143);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == ':') ADVANCE(327);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'a') ADVANCE(352);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'd') ADVANCE(341);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'e') ADVANCE(353);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'g') ADVANCE(340);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'i') ADVANCE(349);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'i') ADVANCE(348);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'm') ADVANCE(351);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'm') ADVANCE(345);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'n') ADVANCE(344);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 350:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'o') ADVANCE(354);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 351:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'p') ADVANCE(350);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 352:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'p') ADVANCE(357);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 353:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'r') ADVANCE(325);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'r') ADVANCE(356);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 355:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 's') ADVANCE(358);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 356:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 't') ADVANCE(310);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 357:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 't') ADVANCE(343);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 358:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(321);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(322);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    case 359:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(359);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 118},
  [2] = {.lex_state = 118},
  [3] = {.lex_state = 118},
  [4] = {.lex_state = 118},
  [5] = {.lex_state = 118},
  [6] = {.lex_state = 119},
  [7] = {.lex_state = 187},
  [8] = {.lex_state = 189},
  [9] = {.lex_state = 188},
  [10] = {.lex_state = 119},
  [11] = {.lex_state = 192},
  [12] = {.lex_state = 190},
  [13] = {.lex_state = 120},
  [14] = {.lex_state = 190},
  [15] = {.lex_state = 190},
  [16] = {.lex_state = 190},
  [17] = {.lex_state = 115},
  [18] = {.lex_state = 115},
  [19] = {.lex_state = 120},
  [20] = {.lex_state = 190},
  [21] = {.lex_state = 190},
  [22] = {.lex_state = 193},
  [23] = {.lex_state = 190},
  [24] = {.lex_state = 191},
  [25] = {.lex_state = 117},
  [26] = {.lex_state = 120},
  [27] = {.lex_state = 116},
  [28] = {.lex_state = 116},
  [29] = {.lex_state = 194},
  [30] = {.lex_state = 194},
  [31] = {.lex_state = 194},
  [32] = {.lex_state = 121},
  [33] = {.lex_state = 194},
  [34] = {.lex_state = 120},
  [35] = {.lex_state = 194},
  [36] = {.lex_state = 194},
  [37] = {.lex_state = 116},
  [38] = {.lex_state = 194},
  [39] = {.lex_state = 114},
  [40] = {.lex_state = 120},
  [41] = {.lex_state = 120},
  [42] = {.lex_state = 118},
  [43] = {.lex_state = 118},
  [44] = {.lex_state = 118},
  [45] = {.lex_state = 118},
  [46] = {.lex_state = 118},
  [47] = {.lex_state = 118},
  [48] = {.lex_state = 118},
  [49] = {.lex_state = 118},
  [50] = {.lex_state = 118},
  [51] = {.lex_state = 118},
  [52] = {.lex_state = 118},
  [53] = {.lex_state = 118},
  [54] = {.lex_state = 118},
  [55] = {.lex_state = 118},
  [56] = {.lex_state = 118},
  [57] = {.lex_state = 118},
  [58] = {.lex_state = 118},
  [59] = {.lex_state = 118},
  [60] = {.lex_state = 118},
  [61] = {.lex_state = 118},
  [62] = {.lex_state = 118},
  [63] = {.lex_state = 118},
  [64] = {.lex_state = 118},
  [65] = {.lex_state = 118},
  [66] = {.lex_state = 118},
  [67] = {.lex_state = 118},
  [68] = {.lex_state = 118},
  [69] = {.lex_state = 118},
  [70] = {.lex_state = 118},
  [71] = {.lex_state = 118},
  [72] = {.lex_state = 118},
  [73] = {.lex_state = 118},
  [74] = {.lex_state = 118},
  [75] = {.lex_state = 118},
  [76] = {.lex_state = 118},
  [77] = {.lex_state = 118},
  [78] = {.lex_state = 118},
  [79] = {.lex_state = 118},
  [80] = {.lex_state = 275},
  [81] = {.lex_state = 275},
  [82] = {.lex_state = 275},
  [83] = {.lex_state = 275},
  [84] = {.lex_state = 275},
  [85] = {.lex_state = 122},
  [86] = {.lex_state = 275},
  [87] = {.lex_state = 275},
  [88] = {.lex_state = 275},
  [89] = {.lex_state = 275},
  [90] = {.lex_state = 275},
  [91] = {.lex_state = 275},
  [92] = {.lex_state = 275},
  [93] = {.lex_state = 11},
  [94] = {.lex_state = 11},
  [95] = {.lex_state = 275},
  [96] = {.lex_state = 122},
  [97] = {.lex_state = 275},
  [98] = {.lex_state = 275},
  [99] = {.lex_state = 275},
  [100] = {.lex_state = 275},
  [101] = {.lex_state = 275},
  [102] = {.lex_state = 275},
  [103] = {.lex_state = 275},
  [104] = {.lex_state = 122},
  [105] = {.lex_state = 275},
  [106] = {.lex_state = 11},
  [107] = {.lex_state = 275},
  [108] = {.lex_state = 275},
  [109] = {.lex_state = 275},
  [110] = {.lex_state = 275},
  [111] = {.lex_state = 275},
  [112] = {.lex_state = 11},
  [113] = {.lex_state = 11},
  [114] = {.lex_state = 5},
  [115] = {.lex_state = 276},
  [116] = {.lex_state = 5},
  [117] = {.lex_state = 5},
  [118] = {.lex_state = 122},
  [119] = {.lex_state = 12},
  [120] = {.lex_state = 11},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 0},
  [123] = {.lex_state = 15},
  [124] = {.lex_state = 276},
  [125] = {.lex_state = 5},
  [126] = {.lex_state = 276},
  [127] = {.lex_state = 122},
  [128] = {.lex_state = 16},
  [129] = {.lex_state = 276},
  [130] = {.lex_state = 5},
  [131] = {.lex_state = 17},
  [132] = {.lex_state = 16},
  [133] = {.lex_state = 5},
  [134] = {.lex_state = 16},
  [135] = {.lex_state = 18},
  [136] = {.lex_state = 19},
  [137] = {.lex_state = 5},
  [138] = {.lex_state = 276},
  [139] = {.lex_state = 276},
  [140] = {.lex_state = 122},
  [141] = {.lex_state = 2},
  [142] = {.lex_state = 20},
  [143] = {.lex_state = 12},
  [144] = {.lex_state = 16},
  [145] = {.lex_state = 16},
  [146] = {.lex_state = 12},
  [147] = {.lex_state = 16},
  [148] = {.lex_state = 12},
  [149] = {.lex_state = 21},
  [150] = {.lex_state = 2},
  [151] = {.lex_state = 122},
  [152] = {.lex_state = 12},
  [153] = {.lex_state = 16},
  [154] = {.lex_state = 122},
  [155] = {.lex_state = 16},
  [156] = {.lex_state = 122},
  [157] = {.lex_state = 5},
  [158] = {.lex_state = 157},
  [159] = {.lex_state = 5},
  [160] = {.lex_state = 2},
  [161] = {.lex_state = 308},
  [162] = {.lex_state = 16},
  [163] = {.lex_state = 5},
  [164] = {.lex_state = 5},
  [165] = {.lex_state = 5},
  [166] = {.lex_state = 5},
  [167] = {.lex_state = 122},
  [168] = {.lex_state = 122},
  [169] = {.lex_state = 5},
  [170] = {.lex_state = 122},
  [171] = {.lex_state = 122},
  [172] = {.lex_state = 122},
  [173] = {.lex_state = 22},
  [174] = {.lex_state = 5},
  [175] = {.lex_state = 5},
  [176] = {.lex_state = 23},
  [177] = {.lex_state = 2},
  [178] = {.lex_state = 24},
  [179] = {.lex_state = 15},
  [180] = {.lex_state = 0},
  [181] = {.lex_state = 276},
  [182] = {.lex_state = 5},
  [183] = {.lex_state = 5},
  [184] = {.lex_state = 24},
  [185] = {.lex_state = 122},
  [186] = {.lex_state = 16},
  [187] = {.lex_state = 5},
  [188] = {.lex_state = 2},
  [189] = {.lex_state = 5},
  [190] = {.lex_state = 22},
  [191] = {.lex_state = 23},
  [192] = {.lex_state = 276},
  [193] = {.lex_state = 22},
  [194] = {.lex_state = 5},
  [195] = {.lex_state = 23},
  [196] = {.lex_state = 122},
  [197] = {.lex_state = 2},
  [198] = {.lex_state = 276},
  [199] = {.lex_state = 157},
  [200] = {.lex_state = 5},
  [201] = {.lex_state = 16},
  [202] = {.lex_state = 5},
  [203] = {.lex_state = 122},
  [204] = {.lex_state = 122},
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
    [anon_sym_Beat] = ACTIONS(1),
    [anon_sym_SLASH_SLASH] = ACTIONS(1),
    [anon_sym_Treatment] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_Narrative] = ACTIONS(1),
    [anon_sym_AT] = ACTIONS(1),
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
    [sym_source_file] = STATE(151),
    [sym_line] = STATE(2),
    [sym_file_header] = STATE(69),
    [sym_act_header] = STATE(69),
    [sym_scene_header] = STATE(69),
    [sym_cel_header] = STATE(69),
    [sym_content_type_beat] = STATE(69),
    [sym_content_type_treatment] = STATE(69),
    [sym_content_type_narrative] = STATE(69),
    [sym_entity_definition] = STATE(69),
    [sym_entity_block] = STATE(2),
    [sym_entity_block_start] = STATE(160),
    [sym_import_statement] = STATE(69),
    [sym_adapter_statement] = STATE(69),
    [sym_metadata_line] = STATE(69),
    [sym_prose_line] = STATE(69),
    [sym_entity_reference] = STATE(5),
    [sym_dialogue_speaker] = STATE(5),
    [sym_parenthetical] = STATE(5),
    [sym_newline] = STATE(2),
    [aux_sym_source_file_repeat1] = STATE(2),
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
    ACTIONS(35), 1,
      ts_builtin_sym_end,
    STATE(160), 1,
      sym_entity_block_start,
    STATE(3), 4,
      sym_line,
      sym_entity_block,
      sym_newline,
      aux_sym_source_file_repeat1,
    STATE(5), 4,
      sym_entity_reference,
      sym_dialogue_speaker,
      sym_parenthetical,
      aux_sym_prose_line_repeat1,
    STATE(69), 12,
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
    ACTIONS(37), 1,
      ts_builtin_sym_end,
    ACTIONS(39), 1,
      aux_sym_file_header_token1,
    ACTIONS(42), 1,
      anon_sym_EQ,
    ACTIONS(45), 1,
      anon_sym_EQ_EQ,
    ACTIONS(48), 1,
      anon_sym_EQ_EQ_EQ,
    ACTIONS(51), 1,
      anon_sym_SLASH_SLASH_SLASH,
    ACTIONS(54), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(57), 1,
      anon_sym_SLASH,
    ACTIONS(60), 1,
      anon_sym_AT,
    ACTIONS(63), 1,
      anon_sym_LBRACE,
    ACTIONS(66), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(69), 1,
      anon_sym_ATimport,
    ACTIONS(72), 1,
      anon_sym_LPAREN,
    ACTIONS(75), 1,
      anon_sym_ATadapter,
    ACTIONS(78), 1,
      sym_prose_text,
    STATE(160), 1,
      sym_entity_block_start,
    STATE(3), 4,
      sym_line,
      sym_entity_block,
      sym_newline,
      aux_sym_source_file_repeat1,
    STATE(5), 4,
      sym_entity_reference,
      sym_dialogue_speaker,
      sym_parenthetical,
      aux_sym_prose_line_repeat1,
    STATE(69), 12,
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
      aux_sym_file_header_token2,
    ACTIONS(114), 1,
      aux_sym_file_header_token3,
    ACTIONS(116), 1,
      anon_sym_Beat,
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
  [284] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(118), 1,
      ts_builtin_sym_end,
    ACTIONS(122), 1,
      aux_sym_file_header_token2,
    ACTIONS(124), 1,
      aux_sym_file_header_token3,
    ACTIONS(126), 1,
      anon_sym_Treatment,
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
  [316] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(128), 1,
      ts_builtin_sym_end,
    ACTIONS(132), 1,
      aux_sym_file_header_token2,
    ACTIONS(134), 1,
      aux_sym_file_header_token3,
    ACTIONS(136), 1,
      anon_sym_Narrative,
    ACTIONS(130), 14,
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
  [348] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(138), 1,
      ts_builtin_sym_end,
    ACTIONS(142), 1,
      aux_sym_import_statement_token3,
    ACTIONS(144), 1,
      anon_sym_RPAREN,
    ACTIONS(146), 1,
      aux_sym_import_statement_token4,
    ACTIONS(140), 14,
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
  [380] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(148), 1,
      ts_builtin_sym_end,
    ACTIONS(152), 1,
      aux_sym_file_header_token3,
    ACTIONS(154), 1,
      anon_sym_Narrative,
    ACTIONS(150), 14,
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
  [409] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(156), 1,
      ts_builtin_sym_end,
    ACTIONS(160), 1,
      aux_sym_file_header_token2,
    ACTIONS(162), 1,
      aux_sym_file_header_token3,
    ACTIONS(158), 14,
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
  [438] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(164), 1,
      ts_builtin_sym_end,
    ACTIONS(168), 1,
      anon_sym_RPAREN,
    ACTIONS(170), 1,
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
  [467] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(172), 1,
      ts_builtin_sym_end,
    ACTIONS(176), 1,
      aux_sym_file_header_token2,
    ACTIONS(178), 1,
      aux_sym_file_header_token3,
    ACTIONS(174), 14,
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
  [496] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(180), 1,
      ts_builtin_sym_end,
    ACTIONS(184), 1,
      aux_sym_file_header_token2,
    ACTIONS(186), 1,
      aux_sym_file_header_token3,
    ACTIONS(182), 14,
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
  [525] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(148), 1,
      ts_builtin_sym_end,
    ACTIONS(152), 1,
      aux_sym_file_header_token3,
    ACTIONS(188), 1,
      aux_sym_file_header_token2,
    ACTIONS(150), 14,
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
  [554] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(190), 1,
      ts_builtin_sym_end,
    ACTIONS(194), 1,
      aux_sym_act_header_token2,
    ACTIONS(196), 1,
      anon_sym_DASH,
    ACTIONS(192), 14,
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
  [583] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(198), 1,
      ts_builtin_sym_end,
    ACTIONS(202), 1,
      aux_sym_act_header_token2,
    ACTIONS(204), 1,
      anon_sym_DASH,
    ACTIONS(200), 14,
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
  [612] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(206), 1,
      ts_builtin_sym_end,
    ACTIONS(210), 1,
      anon_sym_RPAREN,
    ACTIONS(212), 1,
      aux_sym_import_statement_token4,
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
  [641] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(214), 1,
      ts_builtin_sym_end,
    ACTIONS(218), 1,
      aux_sym_file_header_token2,
    ACTIONS(220), 1,
      aux_sym_file_header_token3,
    ACTIONS(216), 14,
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
  [670] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(222), 1,
      ts_builtin_sym_end,
    ACTIONS(226), 1,
      aux_sym_file_header_token2,
    ACTIONS(228), 1,
      aux_sym_file_header_token3,
    ACTIONS(224), 14,
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
  [699] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(222), 1,
      ts_builtin_sym_end,
    ACTIONS(228), 1,
      aux_sym_file_header_token3,
    ACTIONS(230), 1,
      anon_sym_Treatment,
    ACTIONS(224), 14,
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
  [728] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(232), 1,
      ts_builtin_sym_end,
    ACTIONS(236), 1,
      aux_sym_file_header_token2,
    ACTIONS(238), 1,
      aux_sym_file_header_token3,
    ACTIONS(234), 14,
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
  [757] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(156), 1,
      ts_builtin_sym_end,
    ACTIONS(162), 1,
      aux_sym_file_header_token3,
    ACTIONS(240), 1,
      anon_sym_Beat,
    ACTIONS(158), 14,
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
  [786] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(242), 1,
      ts_builtin_sym_end,
    ACTIONS(246), 1,
      anon_sym_COLON,
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
  [812] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(248), 1,
      ts_builtin_sym_end,
    ACTIONS(252), 1,
      aux_sym_import_statement_token4,
    ACTIONS(250), 14,
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
  [838] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(254), 1,
      ts_builtin_sym_end,
    ACTIONS(258), 1,
      aux_sym_act_header_token2,
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
  [864] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(260), 1,
      ts_builtin_sym_end,
    ACTIONS(264), 1,
      aux_sym_act_header_token2,
    ACTIONS(262), 14,
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
  [890] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(266), 1,
      ts_builtin_sym_end,
    ACTIONS(270), 1,
      aux_sym_file_header_token3,
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
  [916] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(272), 1,
      ts_builtin_sym_end,
    ACTIONS(276), 1,
      aux_sym_file_header_token3,
    ACTIONS(274), 14,
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
  [942] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(278), 1,
      ts_builtin_sym_end,
    ACTIONS(282), 1,
      aux_sym_file_header_token3,
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
  [968] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(284), 1,
      ts_builtin_sym_end,
    ACTIONS(288), 1,
      aux_sym_adapter_statement_token1,
    ACTIONS(286), 14,
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
  [994] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(232), 1,
      ts_builtin_sym_end,
    ACTIONS(238), 1,
      aux_sym_file_header_token3,
    ACTIONS(234), 14,
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
  [1020] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(290), 1,
      ts_builtin_sym_end,
    ACTIONS(294), 1,
      aux_sym_import_statement_token4,
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
  [1046] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(180), 1,
      ts_builtin_sym_end,
    ACTIONS(186), 1,
      aux_sym_file_header_token3,
    ACTIONS(182), 14,
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
  [1072] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(296), 1,
      ts_builtin_sym_end,
    ACTIONS(300), 1,
      aux_sym_file_header_token3,
    ACTIONS(298), 14,
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
  [1098] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(302), 1,
      ts_builtin_sym_end,
    ACTIONS(306), 1,
      aux_sym_act_header_token2,
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
  [1124] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(172), 1,
      ts_builtin_sym_end,
    ACTIONS(178), 1,
      aux_sym_file_header_token3,
    ACTIONS(174), 14,
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
  [1150] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(308), 1,
      ts_builtin_sym_end,
    ACTIONS(312), 1,
      aux_sym_entity_block_token1,
    ACTIONS(310), 14,
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
  [1176] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(314), 1,
      ts_builtin_sym_end,
    ACTIONS(318), 1,
      aux_sym_import_statement_token4,
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
  [1202] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(320), 1,
      ts_builtin_sym_end,
    ACTIONS(324), 1,
      aux_sym_import_statement_token4,
    ACTIONS(322), 14,
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
  [1228] = 3,
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
  [1251] = 3,
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
  [1274] = 3,
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
  [1297] = 3,
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
  [1320] = 3,
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
  [1343] = 3,
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
  [1366] = 3,
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
  [1389] = 3,
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
  [1412] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(358), 1,
      ts_builtin_sym_end,
    ACTIONS(360), 14,
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
  [1435] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(362), 1,
      ts_builtin_sym_end,
    ACTIONS(364), 14,
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
  [1458] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(366), 1,
      ts_builtin_sym_end,
    ACTIONS(368), 14,
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
  [1481] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(370), 1,
      ts_builtin_sym_end,
    ACTIONS(372), 14,
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
  [1504] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(374), 1,
      ts_builtin_sym_end,
    ACTIONS(376), 14,
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
  [1527] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(378), 1,
      ts_builtin_sym_end,
    ACTIONS(380), 14,
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
  [1550] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(382), 1,
      ts_builtin_sym_end,
    ACTIONS(384), 14,
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
  [1573] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(386), 1,
      ts_builtin_sym_end,
    ACTIONS(388), 14,
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
  [1596] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(390), 1,
      ts_builtin_sym_end,
    ACTIONS(392), 14,
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
  [1619] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(394), 1,
      ts_builtin_sym_end,
    ACTIONS(396), 14,
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
  [1642] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(398), 1,
      ts_builtin_sym_end,
    ACTIONS(400), 14,
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
  [1665] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(402), 1,
      ts_builtin_sym_end,
    ACTIONS(404), 14,
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
  [1688] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(406), 1,
      ts_builtin_sym_end,
    ACTIONS(408), 14,
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
  [1711] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(410), 1,
      ts_builtin_sym_end,
    ACTIONS(412), 14,
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
  [1734] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(414), 1,
      ts_builtin_sym_end,
    ACTIONS(416), 14,
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
  [1757] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(418), 1,
      ts_builtin_sym_end,
    ACTIONS(420), 14,
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
  [1780] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(422), 1,
      ts_builtin_sym_end,
    ACTIONS(424), 14,
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
  [1803] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(426), 1,
      ts_builtin_sym_end,
    ACTIONS(428), 14,
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
  [1826] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(430), 1,
      ts_builtin_sym_end,
    ACTIONS(432), 14,
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
  [1849] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(434), 1,
      ts_builtin_sym_end,
    ACTIONS(436), 14,
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
  [1872] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(438), 1,
      ts_builtin_sym_end,
    ACTIONS(440), 14,
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
  [1895] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(442), 1,
      ts_builtin_sym_end,
    ACTIONS(444), 14,
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
  [1918] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(446), 1,
      ts_builtin_sym_end,
    ACTIONS(448), 14,
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
  [1941] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(450), 1,
      ts_builtin_sym_end,
    ACTIONS(452), 14,
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
  [1964] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(454), 1,
      ts_builtin_sym_end,
    ACTIONS(456), 14,
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
  [1987] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(458), 1,
      ts_builtin_sym_end,
    ACTIONS(460), 14,
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
  [2010] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(462), 1,
      ts_builtin_sym_end,
    ACTIONS(464), 14,
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
  [2033] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(466), 1,
      ts_builtin_sym_end,
    ACTIONS(468), 14,
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
  [2056] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(470), 1,
      ts_builtin_sym_end,
    ACTIONS(472), 14,
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
  [2079] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(474), 1,
      ts_builtin_sym_end,
    ACTIONS(476), 14,
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
  [2102] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(478), 1,
      aux_sym_file_header_token2,
    ACTIONS(480), 1,
      aux_sym_entity_block_token2,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    STATE(102), 3,
      sym_block_entity_item,
      sym_block_property,
      sym_block_comment,
    STATE(81), 4,
      sym_entity_block_content,
      sym_nested_block,
      sym_newline,
      aux_sym_entity_block_repeat1,
  [2126] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(484), 1,
      aux_sym_file_header_token2,
    ACTIONS(487), 1,
      aux_sym_entity_block_token2,
    ACTIONS(490), 1,
      aux_sym_block_entity_item_token3,
    STATE(102), 3,
      sym_block_entity_item,
      sym_block_property,
      sym_block_comment,
    STATE(81), 4,
      sym_entity_block_content,
      sym_nested_block,
      sym_newline,
      aux_sym_entity_block_repeat1,
  [2150] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(478), 1,
      aux_sym_file_header_token2,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(493), 1,
      aux_sym_entity_block_token2,
    STATE(102), 3,
      sym_block_entity_item,
      sym_block_property,
      sym_block_comment,
    STATE(80), 4,
      sym_entity_block_content,
      sym_nested_block,
      sym_newline,
      aux_sym_entity_block_repeat1,
  [2174] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(495), 1,
      aux_sym_file_header_token2,
    ACTIONS(497), 1,
      aux_sym_entity_block_token2,
    STATE(86), 5,
      sym_block_property,
      sym_block_comment,
      sym_deeper_nested_block,
      sym_newline,
      aux_sym_nested_block_repeat1,
  [2194] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(495), 1,
      aux_sym_file_header_token2,
    ACTIONS(499), 1,
      aux_sym_entity_block_token2,
    STATE(83), 5,
      sym_block_property,
      sym_block_comment,
      sym_deeper_nested_block,
      sym_newline,
      aux_sym_nested_block_repeat1,
  [2214] = 3,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(503), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(505), 7,
      anon_sym_entities,
      anon_sym_characters,
      anon_sym_locations,
      anon_sym_items,
      anon_sym_creatures,
      anon_sym_eras,
      anon_sym_world_eras,
  [2230] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(507), 1,
      aux_sym_file_header_token2,
    ACTIONS(510), 1,
      aux_sym_entity_block_token2,
    ACTIONS(513), 1,
      aux_sym_block_entity_item_token3,
    STATE(86), 5,
      sym_block_property,
      sym_block_comment,
      sym_deeper_nested_block,
      sym_newline,
      aux_sym_nested_block_repeat1,
  [2250] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(516), 1,
      aux_sym_file_header_token2,
    ACTIONS(519), 1,
      aux_sym_entity_block_token2,
    ACTIONS(522), 1,
      aux_sym_block_entity_item_token3,
    STATE(87), 4,
      sym_block_comment,
      sym_nested_block,
      sym_newline,
      aux_sym_block_entity_item_repeat1,
  [2269] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(525), 1,
      aux_sym_file_header_token2,
    ACTIONS(527), 1,
      aux_sym_entity_block_token2,
    STATE(87), 4,
      sym_block_comment,
      sym_nested_block,
      sym_newline,
      aux_sym_block_entity_item_repeat1,
  [2288] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(525), 1,
      aux_sym_file_header_token2,
    ACTIONS(529), 1,
      aux_sym_entity_block_token2,
    STATE(88), 4,
      sym_block_comment,
      sym_nested_block,
      sym_newline,
      aux_sym_block_entity_item_repeat1,
  [2307] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(531), 1,
      aux_sym_file_header_token2,
    ACTIONS(534), 1,
      aux_sym_entity_block_token2,
    ACTIONS(537), 1,
      aux_sym_block_entity_item_token3,
    STATE(90), 3,
      sym_block_comment,
      sym_newline,
      aux_sym_deeper_nested_block_repeat1,
  [2325] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(540), 1,
      aux_sym_file_header_token2,
    ACTIONS(542), 1,
      aux_sym_entity_block_token2,
    STATE(90), 3,
      sym_block_comment,
      sym_newline,
      aux_sym_deeper_nested_block_repeat1,
  [2343] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(542), 1,
      aux_sym_entity_block_token2,
    ACTIONS(544), 1,
      aux_sym_file_header_token2,
    STATE(91), 3,
      sym_block_comment,
      sym_newline,
      aux_sym_deeper_nested_block_repeat1,
  [2361] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(546), 1,
      anon_sym_DASH,
    ACTIONS(548), 1,
      anon_sym_AT,
    ACTIONS(550), 1,
      anon_sym_RBRACE,
    ACTIONS(552), 1,
      anon_sym_POUND,
    STATE(52), 1,
      sym_entity_block_end,
  [2380] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(546), 1,
      anon_sym_DASH,
    ACTIONS(548), 1,
      anon_sym_AT,
    ACTIONS(550), 1,
      anon_sym_RBRACE,
    ACTIONS(552), 1,
      anon_sym_POUND,
    STATE(76), 1,
      sym_entity_block_end,
  [2399] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(554), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2408] = 4,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(556), 1,
      anon_sym_COLON,
    ACTIONS(558), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(560), 1,
      aux_sym_block_entity_item_token4,
  [2421] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(348), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2430] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(562), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2439] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(564), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2448] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(566), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2457] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(568), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2466] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(570), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2475] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(572), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2484] = 4,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(574), 1,
      anon_sym_LPAREN,
    ACTIONS(576), 1,
      anon_sym_DQUOTE,
    ACTIONS(578), 1,
      anon_sym_SQUOTE,
  [2497] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(580), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2506] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(548), 1,
      anon_sym_AT,
    ACTIONS(552), 1,
      anon_sym_POUND,
    ACTIONS(582), 1,
      anon_sym_RBRACE,
  [2519] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(584), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2528] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(586), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2537] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(588), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2546] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(590), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2555] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(592), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2564] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(548), 1,
      anon_sym_AT,
    ACTIONS(552), 1,
      anon_sym_POUND,
    ACTIONS(594), 1,
      anon_sym_RBRACE,
  [2577] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(546), 1,
      anon_sym_DASH,
    ACTIONS(548), 1,
      anon_sym_AT,
    ACTIONS(552), 1,
      anon_sym_POUND,
  [2590] = 4,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(596), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(598), 1,
      anon_sym_DQUOTE,
    ACTIONS(600), 1,
      anon_sym_SQUOTE,
  [2603] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(602), 1,
      aux_sym_entity_block_token2,
    ACTIONS(604), 1,
      aux_sym_block_entity_item_token5,
  [2613] = 3,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(606), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(608), 1,
      anon_sym_RBRACE,
  [2623] = 3,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(606), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(610), 1,
      anon_sym_RBRACE,
  [2633] = 3,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(612), 1,
      anon_sym_DQUOTE,
    ACTIONS(614), 1,
      anon_sym_SQUOTE,
  [2643] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(616), 1,
      anon_sym_COLON,
    ACTIONS(618), 1,
      aux_sym_file_header_token2,
  [2653] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(548), 1,
      anon_sym_AT,
    ACTIONS(552), 1,
      anon_sym_POUND,
  [2663] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(552), 1,
      anon_sym_POUND,
    ACTIONS(620), 1,
      anon_sym_RBRACE,
  [2673] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(552), 1,
      anon_sym_POUND,
    ACTIONS(622), 1,
      anon_sym_RBRACE,
  [2683] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(624), 1,
      aux_sym_act_header_token1,
  [2690] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(626), 1,
      aux_sym_entity_block_token2,
  [2697] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(628), 1,
      aux_sym_block_entity_item_token3,
  [2704] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(630), 1,
      aux_sym_entity_block_token2,
  [2711] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(632), 1,
      anon_sym_LBRACE,
  [2718] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(634), 1,
      aux_sym_block_entity_item_token5,
  [2725] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(636), 1,
      aux_sym_entity_block_token2,
  [2732] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(638), 1,
      aux_sym_entity_definition_token1,
  [2739] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(640), 1,
      aux_sym_entity_reference_token1,
  [2746] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(642), 1,
      aux_sym_block_entity_item_token5,
  [2753] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(644), 1,
      aux_sym_entity_definition_token1,
  [2760] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(646), 1,
      aux_sym_block_entity_item_token5,
  [2767] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(648), 1,
      aux_sym_parenthetical_token1,
  [2774] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(650), 1,
      aux_sym_cel_header_token2,
  [2781] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(652), 1,
      aux_sym_block_entity_item_token3,
  [2788] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(654), 1,
      aux_sym_entity_block_token2,
  [2795] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(656), 1,
      aux_sym_entity_block_token2,
  [2802] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(658), 1,
      anon_sym_LBRACE,
  [2809] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(660), 1,
      aux_sym_entity_block_token1,
  [2816] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(662), 1,
      aux_sym_block_entity_item_token1,
  [2823] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(664), 1,
      aux_sym_file_header_token2,
  [2830] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(666), 1,
      aux_sym_block_entity_item_token5,
  [2837] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(604), 1,
      aux_sym_block_entity_item_token5,
  [2844] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(668), 1,
      aux_sym_file_header_token2,
  [2851] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(670), 1,
      aux_sym_block_entity_item_token5,
  [2858] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(672), 1,
      aux_sym_file_header_token2,
  [2865] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(674), 1,
      aux_sym_block_entity_item_token2,
  [2872] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(676), 1,
      aux_sym_entity_block_token1,
  [2879] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(678), 1,
      ts_builtin_sym_end,
  [2886] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(680), 1,
      aux_sym_file_header_token2,
  [2893] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(682), 1,
      aux_sym_block_entity_item_token5,
  [2900] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(684), 1,
      anon_sym_SQUOTE,
  [2907] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(686), 1,
      aux_sym_block_entity_item_token5,
  [2914] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(684), 1,
      anon_sym_DQUOTE,
  [2921] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(688), 1,
      aux_sym_block_entity_item_token3,
  [2928] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(690), 1,
      aux_sym_file_header_token3,
  [2935] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(692), 1,
      aux_sym_entity_definition_token1,
  [2942] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(694), 1,
      aux_sym_entity_block_token1,
  [2949] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(696), 1,
      aux_sym_block_comment_token1,
  [2956] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(698), 1,
      aux_sym_block_entity_item_token5,
  [2963] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(700), 1,
      aux_sym_entity_definition_token1,
  [2970] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(702), 1,
      aux_sym_entity_definition_token1,
  [2977] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(704), 1,
      anon_sym_COLON,
  [2984] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(706), 1,
      aux_sym_entity_definition_token1,
  [2991] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(708), 1,
      anon_sym_SQUOTE,
  [2998] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(708), 1,
      anon_sym_DQUOTE,
  [3005] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(710), 1,
      anon_sym_COLON,
  [3012] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(712), 1,
      anon_sym_LBRACE,
  [3019] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(714), 1,
      anon_sym_SQUOTE,
  [3026] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(714), 1,
      anon_sym_DQUOTE,
  [3033] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(716), 1,
      aux_sym_import_statement_token2,
  [3040] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(718), 1,
      anon_sym_COLON,
  [3047] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(720), 1,
      aux_sym_block_entity_item_token3,
  [3054] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(722), 1,
      aux_sym_import_statement_token1,
  [3061] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(724), 1,
      aux_sym_entity_block_token1,
  [3068] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(726), 1,
      aux_sym_cel_header_token1,
  [3075] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(728), 1,
      aux_sym_act_header_token1,
  [3082] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(552), 1,
      anon_sym_POUND,
  [3089] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(730), 1,
      aux_sym_entity_block_token2,
  [3096] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(732), 1,
      anon_sym_COLON,
  [3103] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(734), 1,
      aux_sym_block_entity_item_token3,
  [3110] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(736), 1,
      aux_sym_cel_header_token1,
  [3117] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(738), 1,
      anon_sym_LBRACE,
  [3124] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(740), 1,
      aux_sym_block_entity_item_token5,
  [3131] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(742), 1,
      aux_sym_entity_definition_token1,
  [3138] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(744), 1,
      aux_sym_entity_block_token1,
  [3145] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(746), 1,
      aux_sym_block_entity_item_token3,
  [3152] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(748), 1,
      aux_sym_import_statement_token2,
  [3159] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(750), 1,
      aux_sym_import_statement_token1,
  [3166] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(752), 1,
      aux_sym_entity_block_token2,
  [3173] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(754), 1,
      aux_sym_import_statement_token2,
  [3180] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(756), 1,
      anon_sym_COLON,
  [3187] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(758), 1,
      aux_sym_import_statement_token1,
  [3194] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(760), 1,
      anon_sym_LBRACE,
  [3201] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(762), 1,
      aux_sym_entity_definition_token2,
  [3208] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(764), 1,
      aux_sym_entity_block_token2,
  [3215] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(766), 1,
      aux_sym_file_header_token3,
  [3222] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(606), 1,
      aux_sym_entity_definition_token1,
  [3229] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(768), 1,
      aux_sym_block_entity_item_token5,
  [3236] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(770), 1,
      aux_sym_block_entity_item_token3,
  [3243] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(772), 1,
      anon_sym_RPAREN,
  [3250] = 2,
    ACTIONS(501), 1,
      sym_line_comment,
    ACTIONS(774), 1,
      anon_sym_RBRACE,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 78,
  [SMALL_STATE(4)] = 156,
  [SMALL_STATE(5)] = 191,
  [SMALL_STATE(6)] = 220,
  [SMALL_STATE(7)] = 252,
  [SMALL_STATE(8)] = 284,
  [SMALL_STATE(9)] = 316,
  [SMALL_STATE(10)] = 348,
  [SMALL_STATE(11)] = 380,
  [SMALL_STATE(12)] = 409,
  [SMALL_STATE(13)] = 438,
  [SMALL_STATE(14)] = 467,
  [SMALL_STATE(15)] = 496,
  [SMALL_STATE(16)] = 525,
  [SMALL_STATE(17)] = 554,
  [SMALL_STATE(18)] = 583,
  [SMALL_STATE(19)] = 612,
  [SMALL_STATE(20)] = 641,
  [SMALL_STATE(21)] = 670,
  [SMALL_STATE(22)] = 699,
  [SMALL_STATE(23)] = 728,
  [SMALL_STATE(24)] = 757,
  [SMALL_STATE(25)] = 786,
  [SMALL_STATE(26)] = 812,
  [SMALL_STATE(27)] = 838,
  [SMALL_STATE(28)] = 864,
  [SMALL_STATE(29)] = 890,
  [SMALL_STATE(30)] = 916,
  [SMALL_STATE(31)] = 942,
  [SMALL_STATE(32)] = 968,
  [SMALL_STATE(33)] = 994,
  [SMALL_STATE(34)] = 1020,
  [SMALL_STATE(35)] = 1046,
  [SMALL_STATE(36)] = 1072,
  [SMALL_STATE(37)] = 1098,
  [SMALL_STATE(38)] = 1124,
  [SMALL_STATE(39)] = 1150,
  [SMALL_STATE(40)] = 1176,
  [SMALL_STATE(41)] = 1202,
  [SMALL_STATE(42)] = 1228,
  [SMALL_STATE(43)] = 1251,
  [SMALL_STATE(44)] = 1274,
  [SMALL_STATE(45)] = 1297,
  [SMALL_STATE(46)] = 1320,
  [SMALL_STATE(47)] = 1343,
  [SMALL_STATE(48)] = 1366,
  [SMALL_STATE(49)] = 1389,
  [SMALL_STATE(50)] = 1412,
  [SMALL_STATE(51)] = 1435,
  [SMALL_STATE(52)] = 1458,
  [SMALL_STATE(53)] = 1481,
  [SMALL_STATE(54)] = 1504,
  [SMALL_STATE(55)] = 1527,
  [SMALL_STATE(56)] = 1550,
  [SMALL_STATE(57)] = 1573,
  [SMALL_STATE(58)] = 1596,
  [SMALL_STATE(59)] = 1619,
  [SMALL_STATE(60)] = 1642,
  [SMALL_STATE(61)] = 1665,
  [SMALL_STATE(62)] = 1688,
  [SMALL_STATE(63)] = 1711,
  [SMALL_STATE(64)] = 1734,
  [SMALL_STATE(65)] = 1757,
  [SMALL_STATE(66)] = 1780,
  [SMALL_STATE(67)] = 1803,
  [SMALL_STATE(68)] = 1826,
  [SMALL_STATE(69)] = 1849,
  [SMALL_STATE(70)] = 1872,
  [SMALL_STATE(71)] = 1895,
  [SMALL_STATE(72)] = 1918,
  [SMALL_STATE(73)] = 1941,
  [SMALL_STATE(74)] = 1964,
  [SMALL_STATE(75)] = 1987,
  [SMALL_STATE(76)] = 2010,
  [SMALL_STATE(77)] = 2033,
  [SMALL_STATE(78)] = 2056,
  [SMALL_STATE(79)] = 2079,
  [SMALL_STATE(80)] = 2102,
  [SMALL_STATE(81)] = 2126,
  [SMALL_STATE(82)] = 2150,
  [SMALL_STATE(83)] = 2174,
  [SMALL_STATE(84)] = 2194,
  [SMALL_STATE(85)] = 2214,
  [SMALL_STATE(86)] = 2230,
  [SMALL_STATE(87)] = 2250,
  [SMALL_STATE(88)] = 2269,
  [SMALL_STATE(89)] = 2288,
  [SMALL_STATE(90)] = 2307,
  [SMALL_STATE(91)] = 2325,
  [SMALL_STATE(92)] = 2343,
  [SMALL_STATE(93)] = 2361,
  [SMALL_STATE(94)] = 2380,
  [SMALL_STATE(95)] = 2399,
  [SMALL_STATE(96)] = 2408,
  [SMALL_STATE(97)] = 2421,
  [SMALL_STATE(98)] = 2430,
  [SMALL_STATE(99)] = 2439,
  [SMALL_STATE(100)] = 2448,
  [SMALL_STATE(101)] = 2457,
  [SMALL_STATE(102)] = 2466,
  [SMALL_STATE(103)] = 2475,
  [SMALL_STATE(104)] = 2484,
  [SMALL_STATE(105)] = 2497,
  [SMALL_STATE(106)] = 2506,
  [SMALL_STATE(107)] = 2519,
  [SMALL_STATE(108)] = 2528,
  [SMALL_STATE(109)] = 2537,
  [SMALL_STATE(110)] = 2546,
  [SMALL_STATE(111)] = 2555,
  [SMALL_STATE(112)] = 2564,
  [SMALL_STATE(113)] = 2577,
  [SMALL_STATE(114)] = 2590,
  [SMALL_STATE(115)] = 2603,
  [SMALL_STATE(116)] = 2613,
  [SMALL_STATE(117)] = 2623,
  [SMALL_STATE(118)] = 2633,
  [SMALL_STATE(119)] = 2643,
  [SMALL_STATE(120)] = 2653,
  [SMALL_STATE(121)] = 2663,
  [SMALL_STATE(122)] = 2673,
  [SMALL_STATE(123)] = 2683,
  [SMALL_STATE(124)] = 2690,
  [SMALL_STATE(125)] = 2697,
  [SMALL_STATE(126)] = 2704,
  [SMALL_STATE(127)] = 2711,
  [SMALL_STATE(128)] = 2718,
  [SMALL_STATE(129)] = 2725,
  [SMALL_STATE(130)] = 2732,
  [SMALL_STATE(131)] = 2739,
  [SMALL_STATE(132)] = 2746,
  [SMALL_STATE(133)] = 2753,
  [SMALL_STATE(134)] = 2760,
  [SMALL_STATE(135)] = 2767,
  [SMALL_STATE(136)] = 2774,
  [SMALL_STATE(137)] = 2781,
  [SMALL_STATE(138)] = 2788,
  [SMALL_STATE(139)] = 2795,
  [SMALL_STATE(140)] = 2802,
  [SMALL_STATE(141)] = 2809,
  [SMALL_STATE(142)] = 2816,
  [SMALL_STATE(143)] = 2823,
  [SMALL_STATE(144)] = 2830,
  [SMALL_STATE(145)] = 2837,
  [SMALL_STATE(146)] = 2844,
  [SMALL_STATE(147)] = 2851,
  [SMALL_STATE(148)] = 2858,
  [SMALL_STATE(149)] = 2865,
  [SMALL_STATE(150)] = 2872,
  [SMALL_STATE(151)] = 2879,
  [SMALL_STATE(152)] = 2886,
  [SMALL_STATE(153)] = 2893,
  [SMALL_STATE(154)] = 2900,
  [SMALL_STATE(155)] = 2907,
  [SMALL_STATE(156)] = 2914,
  [SMALL_STATE(157)] = 2921,
  [SMALL_STATE(158)] = 2928,
  [SMALL_STATE(159)] = 2935,
  [SMALL_STATE(160)] = 2942,
  [SMALL_STATE(161)] = 2949,
  [SMALL_STATE(162)] = 2956,
  [SMALL_STATE(163)] = 2963,
  [SMALL_STATE(164)] = 2970,
  [SMALL_STATE(165)] = 2977,
  [SMALL_STATE(166)] = 2984,
  [SMALL_STATE(167)] = 2991,
  [SMALL_STATE(168)] = 2998,
  [SMALL_STATE(169)] = 3005,
  [SMALL_STATE(170)] = 3012,
  [SMALL_STATE(171)] = 3019,
  [SMALL_STATE(172)] = 3026,
  [SMALL_STATE(173)] = 3033,
  [SMALL_STATE(174)] = 3040,
  [SMALL_STATE(175)] = 3047,
  [SMALL_STATE(176)] = 3054,
  [SMALL_STATE(177)] = 3061,
  [SMALL_STATE(178)] = 3068,
  [SMALL_STATE(179)] = 3075,
  [SMALL_STATE(180)] = 3082,
  [SMALL_STATE(181)] = 3089,
  [SMALL_STATE(182)] = 3096,
  [SMALL_STATE(183)] = 3103,
  [SMALL_STATE(184)] = 3110,
  [SMALL_STATE(185)] = 3117,
  [SMALL_STATE(186)] = 3124,
  [SMALL_STATE(187)] = 3131,
  [SMALL_STATE(188)] = 3138,
  [SMALL_STATE(189)] = 3145,
  [SMALL_STATE(190)] = 3152,
  [SMALL_STATE(191)] = 3159,
  [SMALL_STATE(192)] = 3166,
  [SMALL_STATE(193)] = 3173,
  [SMALL_STATE(194)] = 3180,
  [SMALL_STATE(195)] = 3187,
  [SMALL_STATE(196)] = 3194,
  [SMALL_STATE(197)] = 3201,
  [SMALL_STATE(198)] = 3208,
  [SMALL_STATE(199)] = 3215,
  [SMALL_STATE(200)] = 3222,
  [SMALL_STATE(201)] = 3229,
  [SMALL_STATE(202)] = 3236,
  [SMALL_STATE(203)] = 3243,
  [SMALL_STATE(204)] = 3250,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(182),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(152),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(146),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(143),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(85),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(131),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(129),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(135),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(148),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [35] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [39] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(182),
  [42] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(152),
  [45] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(146),
  [48] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(143),
  [51] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(7),
  [54] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(8),
  [57] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(9),
  [60] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(85),
  [63] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(131),
  [66] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(47),
  [69] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(129),
  [72] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(135),
  [75] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(148),
  [78] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(5),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_prose_line_repeat1, 2),
  [83] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2),
  [85] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2), SHIFT_REPEAT(131),
  [88] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2), SHIFT_REPEAT(135),
  [91] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2), SHIFT_REPEAT(4),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prose_line, 1),
  [96] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_prose_line, 1),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 6, .production_id = 22),
  [100] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 6, .production_id = 22),
  [102] = {.entry = {.count = 1, .reusable = false}}, SHIFT(130),
  [104] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [106] = {.entry = {.count = 1, .reusable = false}}, SHIFT(132),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 1),
  [110] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 1),
  [112] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [114] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [116] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 1),
  [120] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 1),
  [122] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [124] = {.entry = {.count = 1, .reusable = false}}, SHIFT(45),
  [126] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 1),
  [130] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 1),
  [132] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [134] = {.entry = {.count = 1, .reusable = false}}, SHIFT(46),
  [136] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 5, .production_id = 17),
  [140] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 5, .production_id = 17),
  [142] = {.entry = {.count = 1, .reusable = false}}, SHIFT(133),
  [144] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [146] = {.entry = {.count = 1, .reusable = false}}, SHIFT(128),
  [148] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 2),
  [150] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 2),
  [152] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [154] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 2),
  [158] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 2),
  [160] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [162] = {.entry = {.count = 1, .reusable = false}}, SHIFT(55),
  [164] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 7, .production_id = 24),
  [166] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 7, .production_id = 24),
  [168] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [170] = {.entry = {.count = 1, .reusable = false}}, SHIFT(147),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 3),
  [174] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 3),
  [176] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [178] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 3),
  [182] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 3),
  [184] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [186] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [188] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 3, .production_id = 4),
  [192] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 3, .production_id = 4),
  [194] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [196] = {.entry = {.count = 1, .reusable = false}}, SHIFT(184),
  [198] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 5, .production_id = 15),
  [200] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 5, .production_id = 15),
  [202] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [204] = {.entry = {.count = 1, .reusable = false}}, SHIFT(136),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 30),
  [208] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 30),
  [210] = {.entry = {.count = 1, .reusable = false}}, SHIFT(40),
  [212] = {.entry = {.count = 1, .reusable = false}}, SHIFT(153),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 2, .production_id = 1),
  [216] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 2, .production_id = 1),
  [218] = {.entry = {.count = 1, .reusable = false}}, SHIFT(30),
  [220] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 2),
  [224] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 2),
  [226] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [228] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [230] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [232] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 3),
  [234] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 3),
  [236] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [238] = {.entry = {.count = 1, .reusable = false}}, SHIFT(71),
  [240] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_definition, 4, .production_id = 12),
  [244] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_definition, 4, .production_id = 12),
  [246] = {.entry = {.count = 1, .reusable = false}}, SHIFT(158),
  [248] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 7, .production_id = 22),
  [250] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 7, .production_id = 22),
  [252] = {.entry = {.count = 1, .reusable = false}}, SHIFT(144),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_act_header, 3, .production_id = 4),
  [256] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_act_header, 3, .production_id = 4),
  [258] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [260] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_header, 3, .production_id = 4),
  [262] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_header, 3, .production_id = 4),
  [264] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 4),
  [268] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 4),
  [270] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [272] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 3, .production_id = 1),
  [274] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 3, .production_id = 1),
  [276] = {.entry = {.count = 1, .reusable = false}}, SHIFT(72),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 4),
  [280] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 4),
  [282] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [284] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_adapter_statement, 5, .production_id = 19),
  [286] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_adapter_statement, 5, .production_id = 19),
  [288] = {.entry = {.count = 1, .reusable = false}}, SHIFT(164),
  [290] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 6, .production_id = 17),
  [292] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 6, .production_id = 17),
  [294] = {.entry = {.count = 1, .reusable = false}}, SHIFT(134),
  [296] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 4),
  [298] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 4),
  [300] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [302] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 7, .production_id = 23),
  [304] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 7, .production_id = 23),
  [306] = {.entry = {.count = 1, .reusable = false}}, SHIFT(59),
  [308] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_reference, 3, .production_id = 6),
  [310] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_reference, 3, .production_id = 6),
  [312] = {.entry = {.count = 1, .reusable = false}}, SHIFT(53),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 9, .production_id = 30),
  [316] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 9, .production_id = 30),
  [318] = {.entry = {.count = 1, .reusable = false}}, SHIFT(162),
  [320] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 24),
  [322] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 24),
  [324] = {.entry = {.count = 1, .reusable = false}}, SHIFT(155),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 5, .production_id = 16),
  [328] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 5, .production_id = 16),
  [330] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 9, .production_id = 33),
  [332] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 9, .production_id = 33),
  [334] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 2, .production_id = 2),
  [336] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 2, .production_id = 2),
  [338] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 2, .production_id = 2),
  [340] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 2, .production_id = 2),
  [342] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 2, .production_id = 2),
  [344] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 2, .production_id = 2),
  [346] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_newline, 1),
  [348] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_newline, 1),
  [350] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 11, .production_id = 39),
  [352] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 11, .production_id = 39),
  [354] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_definition, 6, .production_id = 21),
  [356] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_definition, 6, .production_id = 21),
  [358] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 7, .production_id = 25),
  [360] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 7, .production_id = 25),
  [362] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 6, .production_id = 20),
  [364] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 6, .production_id = 20),
  [366] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block, 5),
  [368] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block, 5),
  [370] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dialogue_speaker, 4, .production_id = 14),
  [372] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dialogue_speaker, 4, .production_id = 14),
  [374] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 3, .production_id = 3),
  [376] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 3, .production_id = 3),
  [378] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 3, .production_id = 5),
  [380] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 3, .production_id = 5),
  [382] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 3, .production_id = 5),
  [384] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 3, .production_id = 5),
  [386] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 3, .production_id = 5),
  [388] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 3, .production_id = 5),
  [390] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_adapter_statement, 7, .production_id = 26),
  [392] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_adapter_statement, 7, .production_id = 26),
  [394] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 8, .production_id = 29),
  [396] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 8, .production_id = 29),
  [398] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 31),
  [400] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 31),
  [402] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_adapter_statement, 5, .production_id = 18),
  [404] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_adapter_statement, 5, .production_id = 18),
  [406] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 32),
  [408] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 32),
  [410] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 10, .production_id = 35),
  [412] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 10, .production_id = 35),
  [414] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthetical, 3, .production_id = 7),
  [416] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthetical, 3, .production_id = 7),
  [418] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 10, .production_id = 36),
  [420] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 10, .production_id = 36),
  [422] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 9, .production_id = 34),
  [424] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 9, .production_id = 34),
  [426] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 5, .production_id = 16),
  [428] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 5, .production_id = 16),
  [430] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 5, .production_id = 16),
  [432] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 5, .production_id = 16),
  [434] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_line, 1),
  [436] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_line, 1),
  [438] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metadata_line, 4, .production_id = 11),
  [440] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_metadata_line, 4, .production_id = 11),
  [442] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 4, .production_id = 10),
  [444] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 4, .production_id = 10),
  [446] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 4, .production_id = 8),
  [448] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 4, .production_id = 8),
  [450] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_act_header, 4, .production_id = 9),
  [452] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_act_header, 4, .production_id = 9),
  [454] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_header, 4, .production_id = 9),
  [456] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_header, 4, .production_id = 9),
  [458] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 4, .production_id = 9),
  [460] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 4, .production_id = 9),
  [462] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block, 4),
  [464] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block, 4),
  [466] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 4, .production_id = 10),
  [468] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 4, .production_id = 10),
  [470] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block_end, 1),
  [472] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block_end, 1),
  [474] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 4, .production_id = 10),
  [476] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 4, .production_id = 10),
  [478] = {.entry = {.count = 1, .reusable = false}}, SHIFT(187),
  [480] = {.entry = {.count = 1, .reusable = false}}, SHIFT(93),
  [482] = {.entry = {.count = 1, .reusable = false}}, SHIFT(97),
  [484] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_entity_block_repeat1, 2), SHIFT_REPEAT(187),
  [487] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_entity_block_repeat1, 2), SHIFT_REPEAT(113),
  [490] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_entity_block_repeat1, 2), SHIFT_REPEAT(97),
  [493] = {.entry = {.count = 1, .reusable = false}}, SHIFT(94),
  [495] = {.entry = {.count = 1, .reusable = false}}, SHIFT(159),
  [497] = {.entry = {.count = 1, .reusable = false}}, SHIFT(122),
  [499] = {.entry = {.count = 1, .reusable = false}}, SHIFT(121),
  [501] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [503] = {.entry = {.count = 1, .reusable = false}}, SHIFT(119),
  [505] = {.entry = {.count = 1, .reusable = false}}, SHIFT(126),
  [507] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_nested_block_repeat1, 2), SHIFT_REPEAT(159),
  [510] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_nested_block_repeat1, 2), SHIFT_REPEAT(180),
  [513] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_nested_block_repeat1, 2), SHIFT_REPEAT(97),
  [516] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_entity_item_repeat1, 2), SHIFT_REPEAT(166),
  [519] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_entity_item_repeat1, 2), SHIFT_REPEAT(120),
  [522] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_block_entity_item_repeat1, 2), SHIFT_REPEAT(97),
  [525] = {.entry = {.count = 1, .reusable = false}}, SHIFT(166),
  [527] = {.entry = {.count = 1, .reusable = false}}, SHIFT(106),
  [529] = {.entry = {.count = 1, .reusable = false}}, SHIFT(112),
  [531] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 2), SHIFT_REPEAT(200),
  [534] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 2), SHIFT_REPEAT(180),
  [537] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 2), SHIFT_REPEAT(97),
  [540] = {.entry = {.count = 1, .reusable = false}}, SHIFT(117),
  [542] = {.entry = {.count = 1, .reusable = false}}, SHIFT(180),
  [544] = {.entry = {.count = 1, .reusable = false}}, SHIFT(116),
  [546] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [548] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [550] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [552] = {.entry = {.count = 1, .reusable = false}}, SHIFT(161),
  [554] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_comment, 4),
  [556] = {.entry = {.count = 1, .reusable = false}}, SHIFT(138),
  [558] = {.entry = {.count = 1, .reusable = false}}, SHIFT(110),
  [560] = {.entry = {.count = 1, .reusable = false}}, SHIFT(140),
  [562] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 6, .production_id = 42),
  [564] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_nested_block, 9, .production_id = 38),
  [566] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 10, .production_id = 28),
  [568] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_nested_block, 8, .production_id = 38),
  [570] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block_content, 1),
  [572] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_deeper_nested_block, 9, .production_id = 41),
  [574] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [576] = {.entry = {.count = 1, .reusable = true}}, SHIFT(195),
  [578] = {.entry = {.count = 1, .reusable = true}}, SHIFT(193),
  [580] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 11, .production_id = 28),
  [582] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [584] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_block_entity_item_repeat1, 6, .production_id = 40),
  [586] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 8, .production_id = 37),
  [588] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_deeper_nested_block, 8, .production_id = 41),
  [590] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 5, .production_id = 28),
  [592] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_property, 5, .production_id = 27),
  [594] = {.entry = {.count = 1, .reusable = true}}, SHIFT(175),
  [596] = {.entry = {.count = 1, .reusable = true}}, SHIFT(192),
  [598] = {.entry = {.count = 1, .reusable = true}}, SHIFT(191),
  [600] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [602] = {.entry = {.count = 1, .reusable = false}}, SHIFT(185),
  [604] = {.entry = {.count = 1, .reusable = false}}, SHIFT(125),
  [606] = {.entry = {.count = 1, .reusable = true}}, SHIFT(194),
  [608] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [610] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [612] = {.entry = {.count = 1, .reusable = true}}, SHIFT(176),
  [614] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [616] = {.entry = {.count = 1, .reusable = false}}, SHIFT(199),
  [618] = {.entry = {.count = 1, .reusable = true}}, SHIFT(197),
  [620] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [622] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [624] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [626] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [628] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [630] = {.entry = {.count = 1, .reusable = true}}, SHIFT(196),
  [632] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [634] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [636] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [638] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [640] = {.entry = {.count = 1, .reusable = false}}, SHIFT(204),
  [642] = {.entry = {.count = 1, .reusable = false}}, SHIFT(60),
  [644] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [646] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [648] = {.entry = {.count = 1, .reusable = false}}, SHIFT(203),
  [650] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [652] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [654] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [656] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [658] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [660] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [662] = {.entry = {.count = 1, .reusable = false}}, SHIFT(96),
  [664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [666] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [668] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [670] = {.entry = {.count = 1, .reusable = false}}, SHIFT(66),
  [672] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [674] = {.entry = {.count = 1, .reusable = false}}, SHIFT(157),
  [676] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [678] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [680] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [682] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [684] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [686] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [688] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [690] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [692] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [694] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [696] = {.entry = {.count = 1, .reusable = false}}, SHIFT(137),
  [698] = {.entry = {.count = 1, .reusable = false}}, SHIFT(48),
  [700] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [702] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [704] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [706] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [708] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [710] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [712] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [714] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [716] = {.entry = {.count = 1, .reusable = false}}, SHIFT(154),
  [718] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [720] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [722] = {.entry = {.count = 1, .reusable = false}}, SHIFT(156),
  [724] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block_start, 4, .production_id = 13),
  [726] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [728] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [730] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [732] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [734] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [736] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [738] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [740] = {.entry = {.count = 1, .reusable = false}}, SHIFT(189),
  [742] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [744] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [746] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [748] = {.entry = {.count = 1, .reusable = false}}, SHIFT(167),
  [750] = {.entry = {.count = 1, .reusable = false}}, SHIFT(168),
  [752] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [754] = {.entry = {.count = 1, .reusable = false}}, SHIFT(171),
  [756] = {.entry = {.count = 1, .reusable = true}}, SHIFT(198),
  [758] = {.entry = {.count = 1, .reusable = false}}, SHIFT(172),
  [760] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [762] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [764] = {.entry = {.count = 1, .reusable = true}}, SHIFT(201),
  [766] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [768] = {.entry = {.count = 1, .reusable = false}}, SHIFT(202),
  [770] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [772] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [774] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
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
