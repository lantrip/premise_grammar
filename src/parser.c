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
#define STATE_COUNT 188
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 85
#define ALIAS_COUNT 2
#define TOKEN_COUNT 53
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 29
#define MAX_ALIAS_SEQUENCE_LENGTH 11
#define PRODUCTION_ID_COUNT 42

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
  anon_sym_POUND = 37,
  aux_sym_block_comment_token1 = 38,
  anon_sym_ATimport = 39,
  anon_sym_LPAREN = 40,
  anon_sym_DQUOTE = 41,
  aux_sym_import_statement_token1 = 42,
  anon_sym_SQUOTE = 43,
  aux_sym_import_statement_token2 = 44,
  aux_sym_import_statement_token3 = 45,
  anon_sym_RPAREN = 46,
  aux_sym_import_statement_token4 = 47,
  anon_sym_ATadapter = 48,
  aux_sym_adapter_statement_token1 = 49,
  aux_sym_entity_reference_token1 = 50,
  aux_sym_parenthetical_token1 = 51,
  sym_prose_text = 52,
  sym_source_file = 53,
  sym_line = 54,
  sym_file_header = 55,
  sym_act_header = 56,
  sym_scene_header = 57,
  sym_cel_header = 58,
  sym_content_type_beat = 59,
  sym_content_type_treatment = 60,
  sym_content_type_narrative = 61,
  sym_entity_definition = 62,
  sym_entity_block = 63,
  sym_entity_block_start = 64,
  sym_entity_block_end = 65,
  sym_entity_block_content = 66,
  sym_block_entity_item = 67,
  sym_block_property = 68,
  sym_block_comment = 69,
  sym_nested_block = 70,
  sym_deeper_nested_block = 71,
  sym_import_statement = 72,
  sym_adapter_statement = 73,
  sym_metadata_line = 74,
  sym_prose_line = 75,
  sym_entity_reference = 76,
  sym_dialogue_speaker = 77,
  sym_parenthetical = 78,
  sym_newline = 79,
  aux_sym_source_file_repeat1 = 80,
  aux_sym_entity_block_repeat1 = 81,
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
  field_key = 12,
  field_location_type = 13,
  field_meta_key = 14,
  field_meta_value = 15,
  field_name = 16,
  field_nested_key = 17,
  field_nested_type = 18,
  field_nested_value = 19,
  field_path = 20,
  field_prop_key = 21,
  field_prop_value = 22,
  field_proportion = 23,
  field_selector = 24,
  field_speaker = 25,
  field_time = 26,
  field_timing = 27,
  field_title = 28,
  field_value = 29,
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
  [40] = {.index = 71, .length = 1},
  [41] = {.index = 72, .length = 2},
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
    {field_key, 1},
  [72] =
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
  [94] = 70,
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
  [181] = 181,
  [182] = 182,
  [183] = 183,
  [184] = 184,
  [185] = 185,
  [186] = 186,
  [187] = 187,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(268);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '"') ADVANCE(305);
      if (lookahead == '#') ADVANCE(297);
      if (lookahead == '\'') ADVANCE(308);
      if (lookahead == '(') ADVANCE(303);
      if (lookahead == ')') ADVANCE(313);
      if (lookahead == '-') ADVANCE(200);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == ':') ADVANCE(139);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(216);
      if (lookahead == 'B') ADVANCE(133);
      if (lookahead == 'N') ADVANCE(131);
      if (lookahead == 'T') ADVANCE(135);
      if (lookahead == 'c') ADVANCE(53);
      if (lookahead == 'e') ADVANCE(66);
      if (lookahead == 'i') ADVANCE(97);
      if (lookahead == 'l') ADVANCE(69);
      if (lookahead == 'w') ADVANCE(70);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '}') ADVANCE(288);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(1);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(268);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '"') ADVANCE(305);
      if (lookahead == '#') ADVANCE(297);
      if (lookahead == '\'') ADVANCE(308);
      if (lookahead == '(') ADVANCE(303);
      if (lookahead == ')') ADVANCE(313);
      if (lookahead == '-') ADVANCE(200);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == ':') ADVANCE(139);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(216);
      if (lookahead == 'B') ADVANCE(133);
      if (lookahead == 'N') ADVANCE(131);
      if (lookahead == 'T') ADVANCE(135);
      if (lookahead == 'c') ADVANCE(53);
      if (lookahead == 'e') ADVANCE(66);
      if (lookahead == 'i') ADVANCE(97);
      if (lookahead == 'l') ADVANCE(69);
      if (lookahead == 'w') ADVANCE(70);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '}') ADVANCE(288);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(1);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(268);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '"') ADVANCE(305);
      if (lookahead == '#') ADVANCE(130);
      if (lookahead == '\'') ADVANCE(308);
      if (lookahead == '}') ADVANCE(288);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(2);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 3:
      if (lookahead == '\n') ADVANCE(268);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(3);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(293);
      END_STATE();
    case 5:
      if (lookahead == '\n') ADVANCE(294);
      if (lookahead == '#') ADVANCE(314);
      if (lookahead == 'a') ADVANCE(91);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(11);
      END_STATE();
    case 6:
      if (lookahead == '\n') ADVANCE(295);
      if (lookahead == '#') ADVANCE(314);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(12);
      END_STATE();
    case 7:
      if (lookahead == '\n') ADVANCE(296);
      if (lookahead == '@') ADVANCE(103);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(26);
      END_STATE();
    case 8:
      if (lookahead == '#') ADVANCE(297);
      if (lookahead == '-') ADVANCE(200);
      if (lookahead == '@') ADVANCE(215);
      if (lookahead == '}') ADVANCE(288);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(8)
      END_STATE();
    case 9:
      if (lookahead == '#') ADVANCE(130);
      if (lookahead == ':') ADVANCE(139);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(144);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(145);
      END_STATE();
    case 10:
      if (lookahead == '#') ADVANCE(130);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(10)
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(267);
      END_STATE();
    case 11:
      if (lookahead == '#') ADVANCE(314);
      if (lookahead == 'a') ADVANCE(91);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(11);
      END_STATE();
    case 12:
      if (lookahead == '#') ADVANCE(314);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(12);
      END_STATE();
    case 13:
      if (lookahead == '#') ADVANCE(124);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(291);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(292);
      END_STATE();
    case 14:
      if (lookahead == '#') ADVANCE(126);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(198);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '-') ADVANCE(199);
      END_STATE();
    case 15:
      if (lookahead == '#') ADVANCE(127);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(289);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':' &&
          lookahead != '{') ADVANCE(290);
      END_STATE();
    case 16:
      if (lookahead == '#') ADVANCE(120);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(309);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(310);
      END_STATE();
    case 17:
      if (lookahead == '#') ADVANCE(128);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(201);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')') ADVANCE(202);
      END_STATE();
    case 18:
      if (lookahead == '#') ADVANCE(121);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(306);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(307);
      END_STATE();
    case 19:
      if (lookahead == '#') ADVANCE(125);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(191);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(') ADVANCE(192);
      END_STATE();
    case 20:
      if (lookahead == '#') ADVANCE(122);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(320);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(321);
      END_STATE();
    case 21:
      if (lookahead == '#') ADVANCE(123);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(318);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(319);
      END_STATE();
    case 22:
      if (lookahead == '%') ADVANCE(24);
      if (lookahead == '.') ADVANCE(109);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(22);
      END_STATE();
    case 23:
      if (lookahead == '%') ADVANCE(24);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      END_STATE();
    case 24:
      if (lookahead == ')') ADVANCE(193);
      END_STATE();
    case 25:
      if (lookahead == ':') ADVANCE(317);
      END_STATE();
    case 26:
      if (lookahead == '@') ADVANCE(103);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(26);
      END_STATE();
    case 27:
      if (lookahead == '_') ADVANCE(50);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(84);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(38);
      END_STATE();
    case 30:
      if (lookahead == 'a') ADVANCE(73);
      END_STATE();
    case 31:
      if (lookahead == 'a') ADVANCE(93);
      END_STATE();
    case 32:
      if (lookahead == 'a') ADVANCE(99);
      END_STATE();
    case 33:
      if (lookahead == 'a') ADVANCE(78);
      END_STATE();
    case 34:
      if (lookahead == 'a') ADVANCE(94);
      END_STATE();
    case 35:
      if (lookahead == 'a') ADVANCE(101);
      END_STATE();
    case 36:
      if (lookahead == 'a') ADVANCE(90);
      END_STATE();
    case 37:
      if (lookahead == 'a') ADVANCE(102);
      END_STATE();
    case 38:
      if (lookahead == 'c') ADVANCE(104);
      END_STATE();
    case 39:
      if (lookahead == 'c') ADVANCE(35);
      END_STATE();
    case 40:
      if (lookahead == 'd') ADVANCE(27);
      END_STATE();
    case 41:
      if (lookahead == 'd') ADVANCE(30);
      END_STATE();
    case 42:
      if (lookahead == 'e') ADVANCE(68);
      END_STATE();
    case 43:
      if (lookahead == 'e') ADVANCE(213);
      END_STATE();
    case 44:
      if (lookahead == 'e') ADVANCE(62);
      END_STATE();
    case 45:
      if (lookahead == 'e') ADVANCE(86);
      END_STATE();
    case 46:
      if (lookahead == 'e') ADVANCE(87);
      END_STATE();
    case 47:
      if (lookahead == 'e') ADVANCE(76);
      END_STATE();
    case 48:
      if (lookahead == 'e') ADVANCE(81);
      END_STATE();
    case 49:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 50:
      if (lookahead == 'e') ADVANCE(79);
      END_STATE();
    case 51:
      if (lookahead == 'e') ADVANCE(34);
      END_STATE();
    case 52:
      if (lookahead == 'g') ADVANCE(25);
      END_STATE();
    case 53:
      if (lookahead == 'h') ADVANCE(33);
      if (lookahead == 'r') ADVANCE(51);
      END_STATE();
    case 54:
      if (lookahead == 'i') ADVANCE(106);
      END_STATE();
    case 55:
      if (lookahead == 'i') ADVANCE(71);
      END_STATE();
    case 56:
      if (lookahead == 'i') ADVANCE(65);
      END_STATE();
    case 57:
      if (lookahead == 'i') ADVANCE(64);
      END_STATE();
    case 58:
      if (lookahead == 'i') ADVANCE(45);
      END_STATE();
    case 59:
      if (lookahead == 'i') ADVANCE(98);
      END_STATE();
    case 60:
      if (lookahead == 'l') ADVANCE(40);
      END_STATE();
    case 61:
      if (lookahead == 'm') ADVANCE(74);
      END_STATE();
    case 62:
      if (lookahead == 'm') ADVANCE(85);
      END_STATE();
    case 63:
      if (lookahead == 'm') ADVANCE(42);
      END_STATE();
    case 64:
      if (lookahead == 'm') ADVANCE(56);
      END_STATE();
    case 65:
      if (lookahead == 'n') ADVANCE(52);
      END_STATE();
    case 66:
      if (lookahead == 'n') ADVANCE(92);
      if (lookahead == 'r') ADVANCE(28);
      END_STATE();
    case 67:
      if (lookahead == 'n') ADVANCE(88);
      END_STATE();
    case 68:
      if (lookahead == 'n') ADVANCE(96);
      END_STATE();
    case 69:
      if (lookahead == 'o') ADVANCE(39);
      END_STATE();
    case 70:
      if (lookahead == 'o') ADVANCE(75);
      END_STATE();
    case 71:
      if (lookahead == 'o') ADVANCE(67);
      END_STATE();
    case 72:
      if (lookahead == 'o') ADVANCE(82);
      END_STATE();
    case 73:
      if (lookahead == 'p') ADVANCE(100);
      END_STATE();
    case 74:
      if (lookahead == 'p') ADVANCE(72);
      END_STATE();
    case 75:
      if (lookahead == 'r') ADVANCE(60);
      END_STATE();
    case 76:
      if (lookahead == 'r') ADVANCE(315);
      END_STATE();
    case 77:
      if (lookahead == 'r') ADVANCE(83);
      END_STATE();
    case 78:
      if (lookahead == 'r') ADVANCE(29);
      END_STATE();
    case 79:
      if (lookahead == 'r') ADVANCE(36);
      END_STATE();
    case 80:
      if (lookahead == 'r') ADVANCE(46);
      END_STATE();
    case 81:
      if (lookahead == 'r') ADVANCE(89);
      END_STATE();
    case 82:
      if (lookahead == 'r') ADVANCE(95);
      END_STATE();
    case 83:
      if (lookahead == 'r') ADVANCE(37);
      END_STATE();
    case 84:
      if (lookahead == 's') ADVANCE(282);
      END_STATE();
    case 85:
      if (lookahead == 's') ADVANCE(278);
      END_STATE();
    case 86:
      if (lookahead == 's') ADVANCE(272);
      END_STATE();
    case 87:
      if (lookahead == 's') ADVANCE(280);
      END_STATE();
    case 88:
      if (lookahead == 's') ADVANCE(276);
      END_STATE();
    case 89:
      if (lookahead == 's') ADVANCE(274);
      END_STATE();
    case 90:
      if (lookahead == 's') ADVANCE(284);
      END_STATE();
    case 91:
      if (lookahead == 's') ADVANCE(107);
      END_STATE();
    case 92:
      if (lookahead == 't') ADVANCE(59);
      END_STATE();
    case 93:
      if (lookahead == 't') ADVANCE(205);
      END_STATE();
    case 94:
      if (lookahead == 't') ADVANCE(105);
      END_STATE();
    case 95:
      if (lookahead == 't') ADVANCE(300);
      END_STATE();
    case 96:
      if (lookahead == 't') ADVANCE(209);
      END_STATE();
    case 97:
      if (lookahead == 't') ADVANCE(44);
      END_STATE();
    case 98:
      if (lookahead == 't') ADVANCE(58);
      END_STATE();
    case 99:
      if (lookahead == 't') ADVANCE(63);
      END_STATE();
    case 100:
      if (lookahead == 't') ADVANCE(47);
      END_STATE();
    case 101:
      if (lookahead == 't') ADVANCE(55);
      END_STATE();
    case 102:
      if (lookahead == 't') ADVANCE(54);
      END_STATE();
    case 103:
      if (lookahead == 't') ADVANCE(57);
      END_STATE();
    case 104:
      if (lookahead == 't') ADVANCE(48);
      END_STATE();
    case 105:
      if (lookahead == 'u') ADVANCE(80);
      END_STATE();
    case 106:
      if (lookahead == 'v') ADVANCE(43);
      END_STATE();
    case 107:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(312);
      END_STATE();
    case 108:
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(108);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(267);
      END_STATE();
    case 109:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      END_STATE();
    case 110:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(268);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(322);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 111:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '"') ADVANCE(305);
      if (lookahead == '#') ADVANCE(130);
      if (lookahead == '\'') ADVANCE(308);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == ')') ADVANCE(313);
      if (lookahead == ':') ADVANCE(139);
      if (lookahead == 'c') ADVANCE(236);
      if (lookahead == 'e') ADVANCE(242);
      if (lookahead == 'i') ADVANCE(261);
      if (lookahead == 'l') ADVANCE(244);
      if (lookahead == 'w') ADVANCE(245);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '}') ADVANCE(288);
      if (lookahead == '\t' ||
          lookahead == ' ') SKIP(111)
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 112:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(303);
      if (lookahead == '-') ADVANCE(200);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(323);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 113:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(303);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(324);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 114:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == ':') ADVANCE(139);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(325);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 115:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(326);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 116:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(294);
      if (lookahead == '\r') ADVANCE(5);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == ')') ADVANCE(313);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(327);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 117:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(295);
      if (lookahead == '\r') ADVANCE(6);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == ')') ADVANCE(313);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(328);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 118:
      if (eof) ADVANCE(119);
      if (lookahead == '\n') ADVANCE(296);
      if (lookahead == '\r') ADVANCE(7);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(329);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(310);
      if (lookahead == '\'') ADVANCE(130);
      if (lookahead != 0) ADVANCE(120);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(307);
      if (lookahead == '"') ADVANCE(130);
      if (lookahead != 0) ADVANCE(121);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(321);
      if (lookahead == ')') ADVANCE(130);
      if (lookahead != 0) ADVANCE(122);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\n') ADVANCE(319);
      if (lookahead == '}') ADVANCE(130);
      if (lookahead != 0) ADVANCE(123);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r') ADVANCE(130);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(124);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '(') ADVANCE(130);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(125);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '-') ADVANCE(130);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(126);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == ':' ||
          lookahead == '{') ADVANCE(130);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(127);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')') ADVANCE(130);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(128);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(130);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(129);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(sym_line_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(130);
      END_STATE();
    case 131:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'a') ADVANCE(77);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(138);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'a') ADVANCE(170);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'e') ADVANCE(31);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(138);
      END_STATE();
    case 134:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'e') ADVANCE(152);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 135:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'r') ADVANCE(49);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(138);
      END_STATE();
    case 136:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == 'r') ADVANCE(160);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 137:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 138:
      ACCEPT_TOKEN(aux_sym_file_header_token1);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_') ADVANCE(138);
      END_STATE();
    case 139:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 140:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(145);
      if (lookahead == '\r') ADVANCE(142);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(140);
      END_STATE();
    case 141:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(145);
      if (lookahead == '\r') ADVANCE(143);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(141);
      END_STATE();
    case 142:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(145);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(142);
      if (lookahead != 0) ADVANCE(180);
      END_STATE();
    case 143:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\n') ADVANCE(145);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(145);
      END_STATE();
    case 144:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(144);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(145);
      END_STATE();
    case 145:
      ACCEPT_TOKEN(aux_sym_file_header_token2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(145);
      END_STATE();
    case 146:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead != 0) ADVANCE(180);
      END_STATE();
    case 147:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r') ADVANCE(146);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == 'B') ADVANCE(134);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(147);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 148:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r') ADVANCE(146);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == 'N') ADVANCE(132);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(148);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 149:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r') ADVANCE(146);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == 'T') ADVANCE(136);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(149);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 150:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r') ADVANCE(146);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(150);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 151:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '#') ADVANCE(130);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(151);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(180);
      END_STATE();
    case 152:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'a') ADVANCE(172);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 153:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'a') ADVANCE(167);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 154:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'a') ADVANCE(177);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'a') ADVANCE(176);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 156:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'd') ADVANCE(153);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 157:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'e') ADVANCE(164);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 158:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'e') ADVANCE(214);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 159:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'e') ADVANCE(168);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 160:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'e') ADVANCE(154);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 161:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'i') ADVANCE(178);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 162:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'm') ADVANCE(166);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 163:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'm') ADVANCE(157);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 164:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'n') ADVANCE(175);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 165:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'o') ADVANCE(169);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 166:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'p') ADVANCE(165);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'p') ADVANCE(173);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 168:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(316);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 169:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(174);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 170:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(171);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 171:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'r') ADVANCE(155);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 172:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(206);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 173:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(159);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 174:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(301);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(210);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 176:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(161);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 177:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 't') ADVANCE(163);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 178:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == 'v') ADVANCE(158);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 180:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(180);
      END_STATE();
    case 181:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(119);
      if (lookahead == '\r') ADVANCE(142);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == 'B') ADVANCE(134);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(140);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 182:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(119);
      if (lookahead == '\r') ADVANCE(142);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == 'N') ADVANCE(132);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(140);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 183:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(119);
      if (lookahead == '\r') ADVANCE(142);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == 'T') ADVANCE(136);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(140);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 184:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(119);
      if (lookahead == '\r') ADVANCE(142);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(140);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 185:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(119);
      if (lookahead == '\r') ADVANCE(146);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == 'B') ADVANCE(134);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(147);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 186:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(119);
      if (lookahead == '\r') ADVANCE(146);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == 'N') ADVANCE(132);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(148);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 187:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(119);
      if (lookahead == '\r') ADVANCE(146);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == 'T') ADVANCE(136);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(149);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(aux_sym_file_header_token3);
      if (eof) ADVANCE(119);
      if (lookahead == '\r') ADVANCE(146);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(304);
      if (lookahead == '/') ADVANCE(212);
      if (lookahead == '=') ADVANCE(190);
      if (lookahead == '@') ADVANCE(219);
      if (lookahead == '{') ADVANCE(287);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(150);
      if (lookahead == ')' ||
          lookahead == '}') ADVANCE(180);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(137);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 189:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(194);
      END_STATE();
    case 190:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(195);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 191:
      ACCEPT_TOKEN(aux_sym_act_header_token1);
      if (lookahead == '#') ADVANCE(125);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(191);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(') ADVANCE(192);
      END_STATE();
    case 192:
      ACCEPT_TOKEN(aux_sym_act_header_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(') ADVANCE(192);
      END_STATE();
    case 193:
      ACCEPT_TOKEN(aux_sym_act_header_token2);
      END_STATE();
    case 194:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      if (lookahead == '=') ADVANCE(196);
      END_STATE();
    case 195:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      if (lookahead == '=') ADVANCE(197);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 196:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ);
      END_STATE();
    case 197:
      ACCEPT_TOKEN(anon_sym_EQ_EQ_EQ);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 198:
      ACCEPT_TOKEN(aux_sym_cel_header_token1);
      if (lookahead == '#') ADVANCE(126);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(198);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '-') ADVANCE(199);
      END_STATE();
    case 199:
      ACCEPT_TOKEN(aux_sym_cel_header_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '-') ADVANCE(199);
      END_STATE();
    case 200:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 201:
      ACCEPT_TOKEN(aux_sym_cel_header_token2);
      if (lookahead == '#') ADVANCE(128);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(201);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')') ADVANCE(202);
      END_STATE();
    case 202:
      ACCEPT_TOKEN(aux_sym_cel_header_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')') ADVANCE(202);
      END_STATE();
    case 203:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH_SLASH);
      END_STATE();
    case 204:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH_SLASH);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 205:
      ACCEPT_TOKEN(anon_sym_Beat);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(anon_sym_Beat);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 207:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead == '/') ADVANCE(203);
      END_STATE();
    case 208:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead == '/') ADVANCE(204);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 209:
      ACCEPT_TOKEN(anon_sym_Treatment);
      END_STATE();
    case 210:
      ACCEPT_TOKEN(anon_sym_Treatment);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 211:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '/') ADVANCE(207);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '/') ADVANCE(208);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 213:
      ACCEPT_TOKEN(anon_sym_Narrative);
      END_STATE();
    case 214:
      ACCEPT_TOKEN(anon_sym_Narrative);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 215:
      ACCEPT_TOKEN(anon_sym_AT);
      END_STATE();
    case 216:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(41);
      if (lookahead == 'i') ADVANCE(61);
      END_STATE();
    case 217:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(332);
      if (lookahead == 'i') ADVANCE(337);
      END_STATE();
    case 218:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(332);
      if (lookahead == 'i') ADVANCE(337);
      if (lookahead == 't') ADVANCE(336);
      END_STATE();
    case 219:
      ACCEPT_TOKEN(anon_sym_AT);
      if (lookahead == 'a') ADVANCE(156);
      if (lookahead == 'i') ADVANCE(162);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 220:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == '_') ADVANCE(235);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 221:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(252);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 222:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(228);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 223:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(248);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 224:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(260);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 225:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(263);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 226:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'a') ADVANCE(258);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 227:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'c') ADVANCE(225);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 228:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'c') ADVANCE(264);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 229:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'd') ADVANCE(220);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 230:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(241);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 231:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(224);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 232:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(254);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(250);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(255);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'e') ADVANCE(249);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'h') ADVANCE(223);
      if (lookahead == 'r') ADVANCE(231);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'i') ADVANCE(246);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'i') ADVANCE(232);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'i') ADVANCE(262);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'l') ADVANCE(229);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'm') ADVANCE(253);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'n') ADVANCE(259);
      if (lookahead == 'r') ADVANCE(221);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'n') ADVANCE(256);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'o') ADVANCE(227);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'o') ADVANCE(247);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'o') ADVANCE(243);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(240);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(222);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(226);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(257);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'r') ADVANCE(234);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(283);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(279);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(273);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(281);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(277);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(275);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 's') ADVANCE(285);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(239);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(265);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(230);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(238);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(237);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 't') ADVANCE(233);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (lookahead == 'u') ADVANCE(251);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(aux_sym_entity_definition_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(aux_sym_entity_definition_token2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(108);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(267);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(aux_sym_entity_block_token1);
      if (lookahead == '\n') ADVANCE(268);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(3);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(aux_sym_entity_block_token2);
      if (lookahead == '\n') ADVANCE(145);
      if (lookahead == '\r') ADVANCE(143);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(141);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(aux_sym_entity_block_token2);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(270);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(271);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(aux_sym_entity_block_token2);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(271);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(anon_sym_entities);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(anon_sym_entities);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(anon_sym_characters);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(anon_sym_characters);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(anon_sym_locations);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(anon_sym_locations);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(anon_sym_items);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(anon_sym_items);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(anon_sym_creatures);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(anon_sym_creatures);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(anon_sym_eras);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(anon_sym_eras);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(anon_sym_world_eras);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(anon_sym_world_eras);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(266);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(180);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token1);
      if (lookahead == '#') ADVANCE(127);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(289);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':' &&
          lookahead != '{') ADVANCE(290);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != ':' &&
          lookahead != '{') ADVANCE(290);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token2);
      if (lookahead == '#') ADVANCE(124);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(291);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(292);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(292);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == '#') ADVANCE(314);
      if (lookahead == 'a') ADVANCE(91);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(11);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == '#') ADVANCE(314);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(12);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(aux_sym_block_entity_item_token3);
      if (lookahead == '@') ADVANCE(103);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(26);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(anon_sym_POUND);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(130);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(aux_sym_block_comment_token1);
      if (lookahead == '#') ADVANCE(124);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(298);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(299);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(aux_sym_block_comment_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r') ADVANCE(299);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(anon_sym_ATimport);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(anon_sym_ATimport);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(22);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(180);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(aux_sym_import_statement_token1);
      if (lookahead == '#') ADVANCE(121);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(306);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(307);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(aux_sym_import_statement_token1);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(307);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(aux_sym_import_statement_token2);
      if (lookahead == '#') ADVANCE(120);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(309);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(310);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(aux_sym_import_statement_token2);
      if (lookahead != 0 &&
          lookahead != '\'') ADVANCE(310);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(aux_sym_import_statement_token3);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(311);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(312);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(aux_sym_import_statement_token3);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(312);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(aux_sym_import_statement_token4);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(anon_sym_ATadapter);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(anon_sym_ATadapter);
      if (lookahead == '\r' ||
          lookahead == '(' ||
          lookahead == ')' ||
          lookahead == '{' ||
          lookahead == '}') ADVANCE(180);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(179);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(aux_sym_adapter_statement_token1);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(aux_sym_entity_reference_token1);
      if (lookahead == '#') ADVANCE(123);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(318);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(319);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(aux_sym_entity_reference_token1);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(319);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(aux_sym_parenthetical_token1);
      if (lookahead == '#') ADVANCE(122);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(320);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(321);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(aux_sym_parenthetical_token1);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(321);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(268);
      if (lookahead == '\r') ADVANCE(3);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(322);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(303);
      if (lookahead == '-') ADVANCE(200);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(323);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(303);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(324);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == ':') ADVANCE(139);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(325);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(293);
      if (lookahead == '\r') ADVANCE(4);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(326);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(294);
      if (lookahead == '\r') ADVANCE(5);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == ')') ADVANCE(313);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == 'a') ADVANCE(345);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(327);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(295);
      if (lookahead == '\r') ADVANCE(6);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == ')') ADVANCE(313);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(217);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(328);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\n') ADVANCE(296);
      if (lookahead == '\r') ADVANCE(7);
      if (lookahead == '#') ADVANCE(129);
      if (lookahead == '(') ADVANCE(302);
      if (lookahead == '/') ADVANCE(211);
      if (lookahead == '=') ADVANCE(189);
      if (lookahead == '@') ADVANCE(218);
      if (lookahead == '{') ADVANCE(286);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(329);
      if (('A' <= lookahead && lookahead <= 'Z')) ADVANCE(138);
      if (lookahead != 0 &&
          lookahead != ')' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == ':') ADVANCE(317);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'a') ADVANCE(342);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'd') ADVANCE(331);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'e') ADVANCE(343);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'g') ADVANCE(330);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'i') ADVANCE(339);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'i') ADVANCE(338);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'm') ADVANCE(341);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'm') ADVANCE(335);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'n') ADVANCE(334);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'o') ADVANCE(344);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'p') ADVANCE(340);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'p') ADVANCE(347);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'r') ADVANCE(315);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 'r') ADVANCE(346);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 's') ADVANCE(348);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 't') ADVANCE(300);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == 't') ADVANCE(333);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead == '\t' ||
          lookahead == ' ') ADVANCE(311);
      if (lookahead == '\n' ||
          lookahead == '\r') ADVANCE(312);
      if (lookahead != 0 &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(sym_prose_text);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\r' &&
          lookahead != '(' &&
          lookahead != ')' &&
          lookahead != '{' &&
          lookahead != '}') ADVANCE(349);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 115},
  [2] = {.lex_state = 115},
  [3] = {.lex_state = 115},
  [4] = {.lex_state = 115},
  [5] = {.lex_state = 115},
  [6] = {.lex_state = 116},
  [7] = {.lex_state = 181},
  [8] = {.lex_state = 183},
  [9] = {.lex_state = 182},
  [10] = {.lex_state = 116},
  [11] = {.lex_state = 184},
  [12] = {.lex_state = 184},
  [13] = {.lex_state = 112},
  [14] = {.lex_state = 112},
  [15] = {.lex_state = 117},
  [16] = {.lex_state = 184},
  [17] = {.lex_state = 184},
  [18] = {.lex_state = 186},
  [19] = {.lex_state = 117},
  [20] = {.lex_state = 184},
  [21] = {.lex_state = 184},
  [22] = {.lex_state = 187},
  [23] = {.lex_state = 184},
  [24] = {.lex_state = 185},
  [25] = {.lex_state = 188},
  [26] = {.lex_state = 188},
  [27] = {.lex_state = 188},
  [28] = {.lex_state = 117},
  [29] = {.lex_state = 188},
  [30] = {.lex_state = 117},
  [31] = {.lex_state = 188},
  [32] = {.lex_state = 110},
  [33] = {.lex_state = 117},
  [34] = {.lex_state = 113},
  [35] = {.lex_state = 117},
  [36] = {.lex_state = 118},
  [37] = {.lex_state = 188},
  [38] = {.lex_state = 113},
  [39] = {.lex_state = 113},
  [40] = {.lex_state = 188},
  [41] = {.lex_state = 114},
  [42] = {.lex_state = 115},
  [43] = {.lex_state = 115},
  [44] = {.lex_state = 115},
  [45] = {.lex_state = 115},
  [46] = {.lex_state = 115},
  [47] = {.lex_state = 115},
  [48] = {.lex_state = 115},
  [49] = {.lex_state = 115},
  [50] = {.lex_state = 115},
  [51] = {.lex_state = 115},
  [52] = {.lex_state = 115},
  [53] = {.lex_state = 115},
  [54] = {.lex_state = 115},
  [55] = {.lex_state = 115},
  [56] = {.lex_state = 115},
  [57] = {.lex_state = 115},
  [58] = {.lex_state = 115},
  [59] = {.lex_state = 115},
  [60] = {.lex_state = 115},
  [61] = {.lex_state = 115},
  [62] = {.lex_state = 115},
  [63] = {.lex_state = 115},
  [64] = {.lex_state = 115},
  [65] = {.lex_state = 115},
  [66] = {.lex_state = 115},
  [67] = {.lex_state = 115},
  [68] = {.lex_state = 115},
  [69] = {.lex_state = 115},
  [70] = {.lex_state = 115},
  [71] = {.lex_state = 115},
  [72] = {.lex_state = 115},
  [73] = {.lex_state = 115},
  [74] = {.lex_state = 115},
  [75] = {.lex_state = 115},
  [76] = {.lex_state = 115},
  [77] = {.lex_state = 115},
  [78] = {.lex_state = 115},
  [79] = {.lex_state = 115},
  [80] = {.lex_state = 269},
  [81] = {.lex_state = 269},
  [82] = {.lex_state = 269},
  [83] = {.lex_state = 111},
  [84] = {.lex_state = 269},
  [85] = {.lex_state = 269},
  [86] = {.lex_state = 269},
  [87] = {.lex_state = 269},
  [88] = {.lex_state = 269},
  [89] = {.lex_state = 269},
  [90] = {.lex_state = 8},
  [91] = {.lex_state = 8},
  [92] = {.lex_state = 269},
  [93] = {.lex_state = 269},
  [94] = {.lex_state = 269},
  [95] = {.lex_state = 269},
  [96] = {.lex_state = 269},
  [97] = {.lex_state = 2},
  [98] = {.lex_state = 269},
  [99] = {.lex_state = 269},
  [100] = {.lex_state = 269},
  [101] = {.lex_state = 269},
  [102] = {.lex_state = 269},
  [103] = {.lex_state = 269},
  [104] = {.lex_state = 269},
  [105] = {.lex_state = 8},
  [106] = {.lex_state = 111},
  [107] = {.lex_state = 9},
  [108] = {.lex_state = 111},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 270},
  [112] = {.lex_state = 111},
  [113] = {.lex_state = 2},
  [114] = {.lex_state = 2},
  [115] = {.lex_state = 111},
  [116] = {.lex_state = 13},
  [117] = {.lex_state = 14},
  [118] = {.lex_state = 13},
  [119] = {.lex_state = 15},
  [120] = {.lex_state = 270},
  [121] = {.lex_state = 111},
  [122] = {.lex_state = 2},
  [123] = {.lex_state = 16},
  [124] = {.lex_state = 17},
  [125] = {.lex_state = 18},
  [126] = {.lex_state = 270},
  [127] = {.lex_state = 2},
  [128] = {.lex_state = 16},
  [129] = {.lex_state = 13},
  [130] = {.lex_state = 2},
  [131] = {.lex_state = 111},
  [132] = {.lex_state = 111},
  [133] = {.lex_state = 18},
  [134] = {.lex_state = 2},
  [135] = {.lex_state = 13},
  [136] = {.lex_state = 111},
  [137] = {.lex_state = 13},
  [138] = {.lex_state = 10},
  [139] = {.lex_state = 151},
  [140] = {.lex_state = 270},
  [141] = {.lex_state = 2},
  [142] = {.lex_state = 111},
  [143] = {.lex_state = 111},
  [144] = {.lex_state = 13},
  [145] = {.lex_state = 111},
  [146] = {.lex_state = 270},
  [147] = {.lex_state = 13},
  [148] = {.lex_state = 111},
  [149] = {.lex_state = 13},
  [150] = {.lex_state = 14},
  [151] = {.lex_state = 19},
  [152] = {.lex_state = 111},
  [153] = {.lex_state = 19},
  [154] = {.lex_state = 13},
  [155] = {.lex_state = 2},
  [156] = {.lex_state = 111},
  [157] = {.lex_state = 2},
  [158] = {.lex_state = 151},
  [159] = {.lex_state = 111},
  [160] = {.lex_state = 13},
  [161] = {.lex_state = 9},
  [162] = {.lex_state = 20},
  [163] = {.lex_state = 2},
  [164] = {.lex_state = 111},
  [165] = {.lex_state = 18},
  [166] = {.lex_state = 16},
  [167] = {.lex_state = 270},
  [168] = {.lex_state = 21},
  [169] = {.lex_state = 111},
  [170] = {.lex_state = 111},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 111},
  [173] = {.lex_state = 2},
  [174] = {.lex_state = 9},
  [175] = {.lex_state = 111},
  [176] = {.lex_state = 9},
  [177] = {.lex_state = 111},
  [178] = {.lex_state = 111},
  [179] = {.lex_state = 298},
  [180] = {.lex_state = 9},
  [181] = {.lex_state = 270},
  [182] = {.lex_state = 111},
  [183] = {.lex_state = 2},
  [184] = {.lex_state = 13},
  [185] = {.lex_state = 111},
  [186] = {.lex_state = 2},
  [187] = {.lex_state = 270},
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
    [sym_source_file] = STATE(159),
    [sym_line] = STATE(2),
    [sym_file_header] = STATE(59),
    [sym_act_header] = STATE(59),
    [sym_scene_header] = STATE(59),
    [sym_cel_header] = STATE(59),
    [sym_content_type_beat] = STATE(59),
    [sym_content_type_treatment] = STATE(59),
    [sym_content_type_narrative] = STATE(59),
    [sym_entity_definition] = STATE(59),
    [sym_entity_block] = STATE(2),
    [sym_entity_block_start] = STATE(155),
    [sym_import_statement] = STATE(59),
    [sym_adapter_statement] = STATE(59),
    [sym_metadata_line] = STATE(59),
    [sym_prose_line] = STATE(59),
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
    STATE(155), 1,
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
    STATE(59), 12,
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
    STATE(155), 1,
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
    STATE(59), 12,
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
      aux_sym_file_header_token2,
    ACTIONS(154), 1,
      aux_sym_file_header_token3,
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
      aux_sym_act_header_token2,
    ACTIONS(170), 1,
      anon_sym_DASH,
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
      aux_sym_act_header_token2,
    ACTIONS(178), 1,
      anon_sym_DASH,
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
      anon_sym_RPAREN,
    ACTIONS(186), 1,
      aux_sym_import_statement_token4,
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
    ACTIONS(188), 1,
      ts_builtin_sym_end,
    ACTIONS(192), 1,
      aux_sym_file_header_token2,
    ACTIONS(194), 1,
      aux_sym_file_header_token3,
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
  [554] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(196), 1,
      ts_builtin_sym_end,
    ACTIONS(200), 1,
      aux_sym_file_header_token2,
    ACTIONS(202), 1,
      aux_sym_file_header_token3,
    ACTIONS(198), 14,
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
    ACTIONS(196), 1,
      ts_builtin_sym_end,
    ACTIONS(202), 1,
      aux_sym_file_header_token3,
    ACTIONS(204), 1,
      anon_sym_Narrative,
    ACTIONS(198), 14,
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
    ACTIONS(214), 1,
      ts_builtin_sym_end,
    ACTIONS(220), 1,
      aux_sym_file_header_token3,
    ACTIONS(230), 1,
      anon_sym_Treatment,
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
    ACTIONS(222), 1,
      ts_builtin_sym_end,
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
  [812] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(242), 1,
      ts_builtin_sym_end,
    ACTIONS(246), 1,
      aux_sym_file_header_token3,
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
  [838] = 4,
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
  [864] = 4,
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
  [890] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(254), 1,
      ts_builtin_sym_end,
    ACTIONS(258), 1,
      aux_sym_file_header_token3,
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
  [916] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(260), 1,
      ts_builtin_sym_end,
    ACTIONS(264), 1,
      aux_sym_import_statement_token4,
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
  [942] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(188), 1,
      ts_builtin_sym_end,
    ACTIONS(194), 1,
      aux_sym_file_header_token3,
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
  [968] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(266), 1,
      ts_builtin_sym_end,
    ACTIONS(270), 1,
      aux_sym_entity_block_token1,
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
  [994] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(272), 1,
      ts_builtin_sym_end,
    ACTIONS(276), 1,
      aux_sym_import_statement_token4,
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
  [1020] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(278), 1,
      ts_builtin_sym_end,
    ACTIONS(282), 1,
      aux_sym_act_header_token2,
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
  [1046] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(284), 1,
      ts_builtin_sym_end,
    ACTIONS(288), 1,
      aux_sym_import_statement_token4,
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
  [1072] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(290), 1,
      ts_builtin_sym_end,
    ACTIONS(294), 1,
      aux_sym_adapter_statement_token1,
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
  [1098] = 4,
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
  [1124] = 4,
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
  [1150] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(308), 1,
      ts_builtin_sym_end,
    ACTIONS(312), 1,
      aux_sym_act_header_token2,
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
      aux_sym_file_header_token3,
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
      anon_sym_COLON,
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
  [2102] = 7,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(478), 1,
      aux_sym_file_header_token2,
    ACTIONS(480), 1,
      aux_sym_entity_block_token2,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    STATE(102), 1,
      sym_nested_block,
    STATE(82), 3,
      sym_entity_block_content,
      sym_newline,
      aux_sym_entity_block_repeat1,
    STATE(101), 3,
      sym_block_entity_item,
      sym_block_property,
      sym_block_comment,
  [2128] = 7,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(478), 1,
      aux_sym_file_header_token2,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(484), 1,
      aux_sym_entity_block_token2,
    STATE(102), 1,
      sym_nested_block,
    STATE(80), 3,
      sym_entity_block_content,
      sym_newline,
      aux_sym_entity_block_repeat1,
    STATE(101), 3,
      sym_block_entity_item,
      sym_block_property,
      sym_block_comment,
  [2154] = 7,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(486), 1,
      aux_sym_file_header_token2,
    ACTIONS(489), 1,
      aux_sym_entity_block_token2,
    ACTIONS(492), 1,
      aux_sym_block_entity_item_token3,
    STATE(102), 1,
      sym_nested_block,
    STATE(82), 3,
      sym_entity_block_content,
      sym_newline,
      aux_sym_entity_block_repeat1,
    STATE(101), 3,
      sym_block_entity_item,
      sym_block_property,
      sym_block_comment,
  [2180] = 3,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(497), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(499), 7,
      anon_sym_entities,
      anon_sym_characters,
      anon_sym_locations,
      anon_sym_items,
      anon_sym_creatures,
      anon_sym_eras,
      anon_sym_world_eras,
  [2196] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(501), 1,
      aux_sym_file_header_token2,
    ACTIONS(504), 1,
      aux_sym_entity_block_token2,
    ACTIONS(507), 1,
      aux_sym_block_entity_item_token3,
    STATE(84), 5,
      sym_block_property,
      sym_block_comment,
      sym_deeper_nested_block,
      sym_newline,
      aux_sym_nested_block_repeat1,
  [2216] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(510), 1,
      aux_sym_file_header_token2,
    ACTIONS(512), 1,
      aux_sym_entity_block_token2,
    STATE(84), 5,
      sym_block_property,
      sym_block_comment,
      sym_deeper_nested_block,
      sym_newline,
      aux_sym_nested_block_repeat1,
  [2236] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(510), 1,
      aux_sym_file_header_token2,
    ACTIONS(514), 1,
      aux_sym_entity_block_token2,
    STATE(85), 5,
      sym_block_property,
      sym_block_comment,
      sym_deeper_nested_block,
      sym_newline,
      aux_sym_nested_block_repeat1,
  [2256] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(516), 1,
      aux_sym_file_header_token2,
    ACTIONS(518), 1,
      aux_sym_entity_block_token2,
    STATE(88), 3,
      sym_block_comment,
      sym_newline,
      aux_sym_deeper_nested_block_repeat1,
  [2274] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(482), 1,
      aux_sym_block_entity_item_token3,
    ACTIONS(518), 1,
      aux_sym_entity_block_token2,
    ACTIONS(520), 1,
      aux_sym_file_header_token2,
    STATE(89), 3,
      sym_block_comment,
      sym_newline,
      aux_sym_deeper_nested_block_repeat1,
  [2292] = 5,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(522), 1,
      aux_sym_file_header_token2,
    ACTIONS(525), 1,
      aux_sym_entity_block_token2,
    ACTIONS(528), 1,
      aux_sym_block_entity_item_token3,
    STATE(89), 3,
      sym_block_comment,
      sym_newline,
      aux_sym_deeper_nested_block_repeat1,
  [2310] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(531), 1,
      anon_sym_DASH,
    ACTIONS(533), 1,
      anon_sym_AT,
    ACTIONS(535), 1,
      anon_sym_RBRACE,
    ACTIONS(537), 1,
      anon_sym_POUND,
    STATE(55), 1,
      sym_entity_block_end,
  [2329] = 6,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(531), 1,
      anon_sym_DASH,
    ACTIONS(533), 1,
      anon_sym_AT,
    ACTIONS(535), 1,
      anon_sym_RBRACE,
    ACTIONS(537), 1,
      anon_sym_POUND,
    STATE(66), 1,
      sym_entity_block_end,
  [2348] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(539), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2357] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(541), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2366] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(440), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2375] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(543), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2384] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(545), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2393] = 4,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(547), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(549), 1,
      anon_sym_DQUOTE,
    ACTIONS(551), 1,
      anon_sym_SQUOTE,
  [2406] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(553), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2415] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(555), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2424] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(557), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2433] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(559), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2442] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(561), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2451] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(564), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2460] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(566), 3,
      aux_sym_file_header_token2,
      aux_sym_entity_block_token2,
      aux_sym_block_entity_item_token3,
  [2469] = 4,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(531), 1,
      anon_sym_DASH,
    ACTIONS(533), 1,
      anon_sym_AT,
    ACTIONS(537), 1,
      anon_sym_POUND,
  [2482] = 4,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(568), 1,
      anon_sym_LPAREN,
    ACTIONS(570), 1,
      anon_sym_DQUOTE,
    ACTIONS(572), 1,
      anon_sym_SQUOTE,
  [2495] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(574), 1,
      anon_sym_COLON,
    ACTIONS(576), 1,
      aux_sym_file_header_token2,
  [2505] = 3,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(578), 1,
      anon_sym_COLON,
    ACTIONS(580), 1,
      aux_sym_block_entity_item_token3,
  [2515] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(537), 1,
      anon_sym_POUND,
    ACTIONS(582), 1,
      anon_sym_RBRACE,
  [2525] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(537), 1,
      anon_sym_POUND,
    ACTIONS(584), 1,
      anon_sym_RBRACE,
  [2535] = 3,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(586), 1,
      aux_sym_entity_block_token2,
    ACTIONS(588), 1,
      aux_sym_block_entity_item_token2,
  [2545] = 3,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(590), 1,
      anon_sym_DQUOTE,
    ACTIONS(592), 1,
      anon_sym_SQUOTE,
  [2555] = 3,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(594), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(596), 1,
      anon_sym_RBRACE,
  [2565] = 3,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(594), 1,
      aux_sym_entity_definition_token1,
    ACTIONS(598), 1,
      anon_sym_RBRACE,
  [2575] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(600), 1,
      aux_sym_block_entity_item_token3,
  [2582] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(602), 1,
      aux_sym_block_entity_item_token2,
  [2589] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(604), 1,
      aux_sym_cel_header_token1,
  [2596] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(588), 1,
      aux_sym_block_entity_item_token2,
  [2603] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(606), 1,
      aux_sym_block_entity_item_token1,
  [2610] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(608), 1,
      aux_sym_entity_block_token2,
  [2617] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(610), 1,
      anon_sym_SQUOTE,
  [2624] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(612), 1,
      aux_sym_entity_definition_token1,
  [2631] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(614), 1,
      aux_sym_import_statement_token2,
  [2638] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(616), 1,
      aux_sym_cel_header_token2,
  [2645] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(618), 1,
      aux_sym_import_statement_token1,
  [2652] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(620), 1,
      aux_sym_entity_block_token2,
  [2659] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(622), 1,
      aux_sym_entity_definition_token1,
  [2666] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(624), 1,
      aux_sym_import_statement_token2,
  [2673] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(626), 1,
      aux_sym_block_entity_item_token2,
  [2680] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(628), 1,
      aux_sym_entity_definition_token1,
  [2687] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(630), 1,
      aux_sym_block_entity_item_token3,
  [2694] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(632), 1,
      anon_sym_LBRACE,
  [2701] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(634), 1,
      aux_sym_import_statement_token1,
  [2708] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(636), 1,
      aux_sym_entity_definition_token1,
  [2715] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(638), 1,
      aux_sym_block_entity_item_token2,
  [2722] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(640), 1,
      anon_sym_LBRACE,
  [2729] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(642), 1,
      aux_sym_block_entity_item_token2,
  [2736] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(644), 1,
      aux_sym_entity_definition_token2,
  [2743] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(646), 1,
      aux_sym_file_header_token3,
  [2750] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(648), 1,
      aux_sym_entity_block_token2,
  [2757] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(650), 1,
      aux_sym_entity_block_token1,
  [2764] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(652), 1,
      anon_sym_RPAREN,
  [2771] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(654), 1,
      anon_sym_COLON,
  [2778] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(656), 1,
      aux_sym_block_entity_item_token2,
  [2785] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(658), 1,
      anon_sym_RBRACE,
  [2792] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(660), 1,
      aux_sym_entity_block_token2,
  [2799] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(662), 1,
      aux_sym_block_entity_item_token2,
  [2806] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(664), 1,
      anon_sym_DQUOTE,
  [2813] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(666), 1,
      aux_sym_block_entity_item_token2,
  [2820] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(668), 1,
      aux_sym_cel_header_token1,
  [2827] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(670), 1,
      aux_sym_act_header_token1,
  [2834] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(664), 1,
      anon_sym_SQUOTE,
  [2841] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(672), 1,
      aux_sym_act_header_token1,
  [2848] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(674), 1,
      aux_sym_block_entity_item_token2,
  [2855] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(676), 1,
      aux_sym_entity_block_token1,
  [2862] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(678), 1,
      aux_sym_block_entity_item_token3,
  [2869] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(680), 1,
      aux_sym_entity_definition_token1,
  [2876] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(682), 1,
      aux_sym_file_header_token3,
  [2883] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(684), 1,
      ts_builtin_sym_end,
  [2890] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(686), 1,
      aux_sym_block_entity_item_token2,
  [2897] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(688), 1,
      aux_sym_file_header_token2,
  [2904] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(690), 1,
      aux_sym_parenthetical_token1,
  [2911] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(692), 1,
      aux_sym_entity_block_token1,
  [2918] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(694), 1,
      anon_sym_COLON,
  [2925] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(696), 1,
      aux_sym_import_statement_token1,
  [2932] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(698), 1,
      aux_sym_import_statement_token2,
  [2939] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(700), 1,
      aux_sym_entity_block_token2,
  [2946] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(702), 1,
      aux_sym_entity_reference_token1,
  [2953] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(704), 1,
      anon_sym_DQUOTE,
  [2960] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(704), 1,
      anon_sym_SQUOTE,
  [2967] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(537), 1,
      anon_sym_POUND,
  [2974] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(706), 1,
      anon_sym_LBRACE,
  [2981] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(708), 1,
      aux_sym_entity_block_token1,
  [2988] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(710), 1,
      aux_sym_file_header_token2,
  [2995] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(712), 1,
      anon_sym_COLON,
  [3002] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(714), 1,
      aux_sym_file_header_token2,
  [3009] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(716), 1,
      anon_sym_COLON,
  [3016] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(610), 1,
      anon_sym_DQUOTE,
  [3023] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(718), 1,
      aux_sym_block_comment_token1,
  [3030] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(720), 1,
      aux_sym_file_header_token2,
  [3037] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(722), 1,
      aux_sym_entity_block_token2,
  [3044] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(724), 1,
      anon_sym_LBRACE,
  [3051] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(594), 1,
      aux_sym_entity_definition_token1,
  [3058] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(726), 1,
      aux_sym_block_entity_item_token2,
  [3065] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(728), 1,
      aux_sym_block_entity_item_token3,
  [3072] = 2,
    ACTIONS(495), 1,
      sym_line_comment,
    ACTIONS(730), 1,
      aux_sym_entity_definition_token1,
  [3079] = 2,
    ACTIONS(3), 1,
      sym_line_comment,
    ACTIONS(732), 1,
      aux_sym_entity_block_token2,
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
  [SMALL_STATE(81)] = 2128,
  [SMALL_STATE(82)] = 2154,
  [SMALL_STATE(83)] = 2180,
  [SMALL_STATE(84)] = 2196,
  [SMALL_STATE(85)] = 2216,
  [SMALL_STATE(86)] = 2236,
  [SMALL_STATE(87)] = 2256,
  [SMALL_STATE(88)] = 2274,
  [SMALL_STATE(89)] = 2292,
  [SMALL_STATE(90)] = 2310,
  [SMALL_STATE(91)] = 2329,
  [SMALL_STATE(92)] = 2348,
  [SMALL_STATE(93)] = 2357,
  [SMALL_STATE(94)] = 2366,
  [SMALL_STATE(95)] = 2375,
  [SMALL_STATE(96)] = 2384,
  [SMALL_STATE(97)] = 2393,
  [SMALL_STATE(98)] = 2406,
  [SMALL_STATE(99)] = 2415,
  [SMALL_STATE(100)] = 2424,
  [SMALL_STATE(101)] = 2433,
  [SMALL_STATE(102)] = 2442,
  [SMALL_STATE(103)] = 2451,
  [SMALL_STATE(104)] = 2460,
  [SMALL_STATE(105)] = 2469,
  [SMALL_STATE(106)] = 2482,
  [SMALL_STATE(107)] = 2495,
  [SMALL_STATE(108)] = 2505,
  [SMALL_STATE(109)] = 2515,
  [SMALL_STATE(110)] = 2525,
  [SMALL_STATE(111)] = 2535,
  [SMALL_STATE(112)] = 2545,
  [SMALL_STATE(113)] = 2555,
  [SMALL_STATE(114)] = 2565,
  [SMALL_STATE(115)] = 2575,
  [SMALL_STATE(116)] = 2582,
  [SMALL_STATE(117)] = 2589,
  [SMALL_STATE(118)] = 2596,
  [SMALL_STATE(119)] = 2603,
  [SMALL_STATE(120)] = 2610,
  [SMALL_STATE(121)] = 2617,
  [SMALL_STATE(122)] = 2624,
  [SMALL_STATE(123)] = 2631,
  [SMALL_STATE(124)] = 2638,
  [SMALL_STATE(125)] = 2645,
  [SMALL_STATE(126)] = 2652,
  [SMALL_STATE(127)] = 2659,
  [SMALL_STATE(128)] = 2666,
  [SMALL_STATE(129)] = 2673,
  [SMALL_STATE(130)] = 2680,
  [SMALL_STATE(131)] = 2687,
  [SMALL_STATE(132)] = 2694,
  [SMALL_STATE(133)] = 2701,
  [SMALL_STATE(134)] = 2708,
  [SMALL_STATE(135)] = 2715,
  [SMALL_STATE(136)] = 2722,
  [SMALL_STATE(137)] = 2729,
  [SMALL_STATE(138)] = 2736,
  [SMALL_STATE(139)] = 2743,
  [SMALL_STATE(140)] = 2750,
  [SMALL_STATE(141)] = 2757,
  [SMALL_STATE(142)] = 2764,
  [SMALL_STATE(143)] = 2771,
  [SMALL_STATE(144)] = 2778,
  [SMALL_STATE(145)] = 2785,
  [SMALL_STATE(146)] = 2792,
  [SMALL_STATE(147)] = 2799,
  [SMALL_STATE(148)] = 2806,
  [SMALL_STATE(149)] = 2813,
  [SMALL_STATE(150)] = 2820,
  [SMALL_STATE(151)] = 2827,
  [SMALL_STATE(152)] = 2834,
  [SMALL_STATE(153)] = 2841,
  [SMALL_STATE(154)] = 2848,
  [SMALL_STATE(155)] = 2855,
  [SMALL_STATE(156)] = 2862,
  [SMALL_STATE(157)] = 2869,
  [SMALL_STATE(158)] = 2876,
  [SMALL_STATE(159)] = 2883,
  [SMALL_STATE(160)] = 2890,
  [SMALL_STATE(161)] = 2897,
  [SMALL_STATE(162)] = 2904,
  [SMALL_STATE(163)] = 2911,
  [SMALL_STATE(164)] = 2918,
  [SMALL_STATE(165)] = 2925,
  [SMALL_STATE(166)] = 2932,
  [SMALL_STATE(167)] = 2939,
  [SMALL_STATE(168)] = 2946,
  [SMALL_STATE(169)] = 2953,
  [SMALL_STATE(170)] = 2960,
  [SMALL_STATE(171)] = 2967,
  [SMALL_STATE(172)] = 2974,
  [SMALL_STATE(173)] = 2981,
  [SMALL_STATE(174)] = 2988,
  [SMALL_STATE(175)] = 2995,
  [SMALL_STATE(176)] = 3002,
  [SMALL_STATE(177)] = 3009,
  [SMALL_STATE(178)] = 3016,
  [SMALL_STATE(179)] = 3023,
  [SMALL_STATE(180)] = 3030,
  [SMALL_STATE(181)] = 3037,
  [SMALL_STATE(182)] = 3044,
  [SMALL_STATE(183)] = 3051,
  [SMALL_STATE(184)] = 3058,
  [SMALL_STATE(185)] = 3065,
  [SMALL_STATE(186)] = 3072,
  [SMALL_STATE(187)] = 3079,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(175),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(180),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(176),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(174),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [19] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [21] = {.entry = {.count = 1, .reusable = false}}, SHIFT(83),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(168),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(167),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(162),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(161),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [35] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [39] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(175),
  [42] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(180),
  [45] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(176),
  [48] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(174),
  [51] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(7),
  [54] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(8),
  [57] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(9),
  [60] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(83),
  [63] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(168),
  [66] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(70),
  [69] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(167),
  [72] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(162),
  [75] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(161),
  [78] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(5),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_prose_line_repeat1, 2),
  [83] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2),
  [85] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2), SHIFT_REPEAT(168),
  [88] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2), SHIFT_REPEAT(162),
  [91] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_prose_line_repeat1, 2), SHIFT_REPEAT(4),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_prose_line, 1),
  [96] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_prose_line, 1),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 6, .production_id = 22),
  [100] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 6, .production_id = 22),
  [102] = {.entry = {.count = 1, .reusable = false}}, SHIFT(134),
  [104] = {.entry = {.count = 1, .reusable = false}}, SHIFT(30),
  [106] = {.entry = {.count = 1, .reusable = false}}, SHIFT(135),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 1),
  [110] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 1),
  [112] = {.entry = {.count = 1, .reusable = false}}, SHIFT(24),
  [114] = {.entry = {.count = 1, .reusable = false}}, SHIFT(54),
  [116] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 1),
  [120] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 1),
  [122] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [124] = {.entry = {.count = 1, .reusable = false}}, SHIFT(52),
  [126] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 1),
  [130] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 1),
  [132] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [134] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [136] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 5, .production_id = 17),
  [140] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 5, .production_id = 17),
  [142] = {.entry = {.count = 1, .reusable = false}}, SHIFT(127),
  [144] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [146] = {.entry = {.count = 1, .reusable = false}}, SHIFT(129),
  [148] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 2, .production_id = 1),
  [150] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 2, .production_id = 1),
  [152] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [154] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [156] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 2),
  [158] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 2),
  [160] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [162] = {.entry = {.count = 1, .reusable = false}}, SHIFT(47),
  [164] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 5, .production_id = 15),
  [166] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 5, .production_id = 15),
  [168] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [170] = {.entry = {.count = 1, .reusable = false}}, SHIFT(124),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 3, .production_id = 4),
  [174] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 3, .production_id = 4),
  [176] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [178] = {.entry = {.count = 1, .reusable = false}}, SHIFT(117),
  [180] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 30),
  [182] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 30),
  [184] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [186] = {.entry = {.count = 1, .reusable = false}}, SHIFT(116),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 3),
  [190] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 3),
  [192] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [194] = {.entry = {.count = 1, .reusable = false}}, SHIFT(78),
  [196] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 2),
  [198] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 2),
  [200] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [202] = {.entry = {.count = 1, .reusable = false}}, SHIFT(53),
  [204] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 7, .production_id = 24),
  [208] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 7, .production_id = 24),
  [210] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [212] = {.entry = {.count = 1, .reusable = false}}, SHIFT(147),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 2),
  [216] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 2),
  [218] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [220] = {.entry = {.count = 1, .reusable = false}}, SHIFT(50),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 3),
  [224] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 3),
  [226] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [228] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [230] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [232] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 3),
  [234] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 3),
  [236] = {.entry = {.count = 1, .reusable = false}}, SHIFT(40),
  [238] = {.entry = {.count = 1, .reusable = false}}, SHIFT(71),
  [240] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [242] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 4),
  [244] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 4),
  [246] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [248] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 9, .production_id = 30),
  [250] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 9, .production_id = 30),
  [252] = {.entry = {.count = 1, .reusable = false}}, SHIFT(160),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 3, .production_id = 1),
  [256] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 3, .production_id = 1),
  [258] = {.entry = {.count = 1, .reusable = false}}, SHIFT(72),
  [260] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 7, .production_id = 22),
  [262] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 7, .production_id = 22),
  [264] = {.entry = {.count = 1, .reusable = false}}, SHIFT(144),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_reference, 3, .production_id = 6),
  [268] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_reference, 3, .production_id = 6),
  [270] = {.entry = {.count = 1, .reusable = false}}, SHIFT(61),
  [272] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 24),
  [274] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 24),
  [276] = {.entry = {.count = 1, .reusable = false}}, SHIFT(154),
  [278] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 7, .production_id = 23),
  [280] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 7, .production_id = 23),
  [282] = {.entry = {.count = 1, .reusable = false}}, SHIFT(48),
  [284] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 6, .production_id = 17),
  [286] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 6, .production_id = 17),
  [288] = {.entry = {.count = 1, .reusable = false}}, SHIFT(137),
  [290] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_adapter_statement, 5, .production_id = 19),
  [292] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_adapter_statement, 5, .production_id = 19),
  [294] = {.entry = {.count = 1, .reusable = false}}, SHIFT(130),
  [296] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 4),
  [298] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 4),
  [300] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [302] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scene_header, 3, .production_id = 4),
  [304] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_scene_header, 3, .production_id = 4),
  [306] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [308] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_act_header, 3, .production_id = 4),
  [310] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_act_header, 3, .production_id = 4),
  [312] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 4),
  [316] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 4),
  [318] = {.entry = {.count = 1, .reusable = false}}, SHIFT(76),
  [320] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_definition, 4, .production_id = 12),
  [322] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_definition, 4, .production_id = 12),
  [324] = {.entry = {.count = 1, .reusable = false}}, SHIFT(158),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 32),
  [328] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 32),
  [330] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 10, .production_id = 36),
  [332] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 10, .production_id = 36),
  [334] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_file_header, 3, .production_id = 3),
  [336] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_file_header, 3, .production_id = 3),
  [338] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block_end, 1),
  [340] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block_end, 1),
  [342] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_adapter_statement, 7, .production_id = 26),
  [344] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_adapter_statement, 7, .production_id = 26),
  [346] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 3, .production_id = 5),
  [348] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 3, .production_id = 5),
  [350] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 8, .production_id = 29),
  [352] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 8, .production_id = 29),
  [354] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 8, .production_id = 31),
  [356] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 8, .production_id = 31),
  [358] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 3, .production_id = 5),
  [360] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 3, .production_id = 5),
  [362] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 2, .production_id = 2),
  [364] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 2, .production_id = 2),
  [366] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 2, .production_id = 2),
  [368] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 2, .production_id = 2),
  [370] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 3, .production_id = 5),
  [372] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 3, .production_id = 5),
  [374] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 2, .production_id = 2),
  [376] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 2, .production_id = 2),
  [378] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block, 4),
  [380] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block, 4),
  [382] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 7, .production_id = 25),
  [384] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 7, .production_id = 25),
  [386] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 5, .production_id = 16),
  [388] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 5, .production_id = 16),
  [390] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 9, .production_id = 33),
  [392] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 9, .production_id = 33),
  [394] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_line, 1),
  [396] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_line, 1),
  [398] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 9, .production_id = 34),
  [400] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 9, .production_id = 34),
  [402] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dialogue_speaker, 4, .production_id = 14),
  [404] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dialogue_speaker, 4, .production_id = 14),
  [406] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 10, .production_id = 35),
  [408] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 10, .production_id = 35),
  [410] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthetical, 3, .production_id = 7),
  [412] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthetical, 3, .production_id = 7),
  [414] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_definition, 6, .production_id = 21),
  [416] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_definition, 6, .production_id = 21),
  [418] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cel_header, 6, .production_id = 20),
  [420] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cel_header, 6, .production_id = 20),
  [422] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block, 5),
  [424] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block, 5),
  [426] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 5, .production_id = 16),
  [428] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 5, .production_id = 16),
  [430] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metadata_line, 4, .production_id = 11),
  [432] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_metadata_line, 4, .production_id = 11),
  [434] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_adapter_statement, 5, .production_id = 18),
  [436] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_adapter_statement, 5, .production_id = 18),
  [438] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_newline, 1),
  [440] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_newline, 1),
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
  [462] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_narrative, 5, .production_id = 16),
  [464] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_narrative, 5, .production_id = 16),
  [466] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_statement, 11, .production_id = 39),
  [468] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_import_statement, 11, .production_id = 39),
  [470] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_beat, 4, .production_id = 10),
  [472] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_beat, 4, .production_id = 10),
  [474] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_content_type_treatment, 4, .production_id = 10),
  [476] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_content_type_treatment, 4, .production_id = 10),
  [478] = {.entry = {.count = 1, .reusable = false}}, SHIFT(122),
  [480] = {.entry = {.count = 1, .reusable = false}}, SHIFT(91),
  [482] = {.entry = {.count = 1, .reusable = false}}, SHIFT(94),
  [484] = {.entry = {.count = 1, .reusable = false}}, SHIFT(90),
  [486] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_entity_block_repeat1, 2), SHIFT_REPEAT(122),
  [489] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_entity_block_repeat1, 2), SHIFT_REPEAT(105),
  [492] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_entity_block_repeat1, 2), SHIFT_REPEAT(94),
  [495] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [497] = {.entry = {.count = 1, .reusable = false}}, SHIFT(107),
  [499] = {.entry = {.count = 1, .reusable = false}}, SHIFT(146),
  [501] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_nested_block_repeat1, 2), SHIFT_REPEAT(157),
  [504] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_nested_block_repeat1, 2), SHIFT_REPEAT(171),
  [507] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_nested_block_repeat1, 2), SHIFT_REPEAT(94),
  [510] = {.entry = {.count = 1, .reusable = false}}, SHIFT(157),
  [512] = {.entry = {.count = 1, .reusable = false}}, SHIFT(110),
  [514] = {.entry = {.count = 1, .reusable = false}}, SHIFT(109),
  [516] = {.entry = {.count = 1, .reusable = false}}, SHIFT(113),
  [518] = {.entry = {.count = 1, .reusable = false}}, SHIFT(171),
  [520] = {.entry = {.count = 1, .reusable = false}}, SHIFT(114),
  [522] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 2), SHIFT_REPEAT(183),
  [525] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 2), SHIFT_REPEAT(171),
  [528] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 2), SHIFT_REPEAT(94),
  [531] = {.entry = {.count = 1, .reusable = true}}, SHIFT(187),
  [533] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [535] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [537] = {.entry = {.count = 1, .reusable = false}}, SHIFT(179),
  [539] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 5, .production_id = 28),
  [541] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_nested_block, 8, .production_id = 38),
  [543] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_deeper_nested_block_repeat1, 6, .production_id = 41),
  [545] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_deeper_nested_block, 9, .production_id = 40),
  [547] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [549] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [551] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [553] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_deeper_nested_block, 8, .production_id = 40),
  [555] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_comment, 4),
  [557] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_nested_block, 9, .production_id = 38),
  [559] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_entity_block_content, 1),
  [561] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_entity_block_content, 1), REDUCE(aux_sym_entity_block_repeat1, 1),
  [564] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_property, 5, .production_id = 27),
  [566] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_block_entity_item, 8, .production_id = 37),
  [568] = {.entry = {.count = 1, .reusable = true}}, SHIFT(112),
  [570] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [572] = {.entry = {.count = 1, .reusable = true}}, SHIFT(128),
  [574] = {.entry = {.count = 1, .reusable = false}}, SHIFT(139),
  [576] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [578] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [580] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [582] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [584] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [586] = {.entry = {.count = 1, .reusable = false}}, SHIFT(172),
  [588] = {.entry = {.count = 1, .reusable = false}}, SHIFT(131),
  [590] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [592] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [594] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [596] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [598] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [600] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [602] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [604] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [606] = {.entry = {.count = 1, .reusable = false}}, SHIFT(108),
  [608] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [610] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [612] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [614] = {.entry = {.count = 1, .reusable = false}}, SHIFT(121),
  [616] = {.entry = {.count = 1, .reusable = false}}, SHIFT(34),
  [618] = {.entry = {.count = 1, .reusable = false}}, SHIFT(178),
  [620] = {.entry = {.count = 1, .reusable = true}}, SHIFT(182),
  [622] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [624] = {.entry = {.count = 1, .reusable = false}}, SHIFT(170),
  [626] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [628] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [630] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [632] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [634] = {.entry = {.count = 1, .reusable = false}}, SHIFT(169),
  [636] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [638] = {.entry = {.count = 1, .reusable = false}}, SHIFT(49),
  [640] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [642] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [644] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [646] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [648] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [650] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [652] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [654] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [656] = {.entry = {.count = 1, .reusable = false}}, SHIFT(58),
  [658] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [660] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [662] = {.entry = {.count = 1, .reusable = false}}, SHIFT(60),
  [664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [666] = {.entry = {.count = 1, .reusable = false}}, SHIFT(156),
  [668] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [670] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [672] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [674] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [676] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [678] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [680] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [682] = {.entry = {.count = 1, .reusable = false}}, SHIFT(64),
  [684] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [686] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [688] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [690] = {.entry = {.count = 1, .reusable = false}}, SHIFT(142),
  [692] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_entity_block_start, 4, .production_id = 13),
  [694] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [696] = {.entry = {.count = 1, .reusable = false}}, SHIFT(148),
  [698] = {.entry = {.count = 1, .reusable = false}}, SHIFT(152),
  [700] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [702] = {.entry = {.count = 1, .reusable = false}}, SHIFT(145),
  [704] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [706] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [708] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [710] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [712] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [714] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [716] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [718] = {.entry = {.count = 1, .reusable = false}}, SHIFT(115),
  [720] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [722] = {.entry = {.count = 1, .reusable = true}}, SHIFT(184),
  [724] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [726] = {.entry = {.count = 1, .reusable = false}}, SHIFT(185),
  [728] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [730] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [732] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
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
