### Premise Prose Theme

**Core idea**: A prose-first, readable light theme that uses a tight, literary palette. Hierarchy headers progress from Caribbean Blue through Lapis Lazuli to Indigo Dye. Entities pop with Hyundai Yellow. Narrative layers (Beat/Treatment/Narrative) use Verdant Green accents. The result is a clean manuscript feel suitable for long-form writing in Cursor/VS Code.

- **Primary palette**

  - **Indigo Dye** (`#003D5B`): base prose, punctuation, strings
  - **Amaranth** (`#D1495B`): adapter keywords and important delimiters
  - **Purple** (`#b86798`): content markers (///, //, /)
  - **Blue** (`#0e87d0`): hierarchy markers (###, ##, #)
  - **BluePurple** (`#7089b4`): entities and references

- **VS Code theme file**: `extensions/vscode/themes/premise-prose.json`

  - Default editor font for Premise files: Courier Prime (with fallbacks)

- **Mapping overview**

  - **Hierarchy (Blue)**
    - `story-act` → `#0e87d0` (bold)
    - `story-scene` → `#0e87d0` (bold)
    - `story-cel` → `#0e87d0` (bold)
  - **Entities (BluePurple)**
    - `keyword.entity.premise` → `#7089b4`
    - `entity-definition*` → `#7089b4`
    - `entity.name.reference.premise` → `#0079BC`
    - `entity.name.type.premise` → `#7089b4` (not bold)
      - `punctuation.definition.entity.reference.begin/end.premise` → subtle, slightly lighter than text `#4F6E86`
  - **Content layers (Purple)**
    - `content-beat` → `#b86798` (bold)
    - `content-treatment` → `#b86798`
    - `content-narrative` → `#b86798`
  - **Screenplay dialogue**
    - Speaker name (`entity.name.character.screenplay.premise`) → `#00798C` (bold)
    - Separator colon (`punctuation.separator.dialogue.premise`) → `#00798C`
    - Dialogue text (`text.dialogue.screenplay.premise`) → `#003D5B` (italic)
      - Includes indented continuation lines after the speaker line
    - Parentheticals (`meta.screenplay.parenthetical.premise`) → `#003D5B` (not italic)
  - **General text**
    - Editor fg → `
