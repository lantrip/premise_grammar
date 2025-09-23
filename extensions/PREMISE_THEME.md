### Premise Prose Theme

**Core idea**: A prose-first, readable light theme that uses a tight, literary palette. Hierarchy headers progress from Caribbean Blue through Lapis Lazuli to Indigo Dye. Entities pop with Hyundai Yellow. Narrative layers (Beat/Treatment/Narrative) use Verdant Green accents. The result is a clean manuscript feel suitable for long-form writing in Cursor/VS Code.

- **Primary palette**

  - **Indigo Dye** (`#003D5B`): base prose, punctuation, strings
  - **Amaranth** (`#D1495B`): adapter keywords and important delimiters
  - **Purple** (`#b86798`): content markers (///, //, /)
  - **Blue** (`#0e87d0`): hierarchy markers (###, ##, #)
  - **BluePurple** (`#7089b4`): entities and references

- **VS Code theme file**: `extensions/vscode/themes/premise-prose.json`

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
  - **General text**
    - Editor fg → `#003D5B`, bg → `#ffffff`
    - Strings and narrative bodies → `#003D5B`
    - Punctuation/separators → `#003D5B`
    - Comments → `#6B7C93` italic
  - **Adapters/keywords/imports**
    - Entity block keyword (`keyword.entity.premise`) → `#D1495B`
    - `@` punctuation (`punctuation.definition.keyword.premise`) → lighter amaranth `#DA6D7C` (not bold)
    - Adapter keywords/delimiters → `#D1495B` (bold)
    - Adapter names/functions → `#00798C` (bold)
    - Properties → `#003D5B`
    - File header/import/meta → `#30638E`/`#6B7C93`

- **Rationale**

  - Keep prose legible with deep cool base (`#003D5B`) and restrained accenting.
  - Entities are highlighted with yellow to stand out within narrative.
  - Hierarchy uses a cool-to-deep progression for visual structure.
  - Content markers are green for immediate visual parsing of layers.

- **Tuning notes**

  - If yellow reads too strong on some displays, consider `#E3A43F`.
  - For higher contrast body text, test `#08334A` for `editor.foreground`.
  - Cursor dark variant could invert base/accents while keeping the same mapping.

- **Troubleshooting**
  - If `{` `}` braces for entity references appear blue (like parentheses), bracket pair colorization is overriding theme scopes.
  - Solution: Disable bracket pair colorization for Premise files. We set `"editor.bracketPairColorization.enabled": false` in `[premise]` via extension defaults, but local settings can override.
  - Dialogue speaker names use `#00798C` bold via `entity.name.character.screenplay.premise`. Entity references in prose use `#003D5B` via `entity.name.reference.premise`.
