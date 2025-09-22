### Premise Prose Theme

**Core idea**: A prose-first, readable light theme that uses a tight, literary palette. Hierarchy headers progress from Caribbean Blue through Lapis Lazuli to Indigo Dye. Entities pop with Hyundai Yellow. Narrative layers (Beat/Treatment/Narrative) use Verdant Green accents. The result is a clean manuscript feel suitable for long-form writing in Cursor/VS Code.

- **Primary palette**

  - **Caribbean Blue** (`#00798C`): top-level hierarchy and key references
  - **Lapis Lazuli** (`#30638E`): mid-level hierarchy, functions/types
  - **Indigo Dye** (`#003D5B`): base prose, punctuation, strings
  - **Amaranth** (`#D1495B`): adapter keywords and important delimiters
  - **Hyundai Yellow** (`#EDAE49`): entities and references
  - **Verdant Green** (`#27AE60`): content markers (///, //, /)

- **VS Code theme file**: `extensions/vscode/themes/premise-prose.json`

- **Mapping overview**

  - **Hierarchy**
    - `story-act` → `#00798C` (bold)
    - `story-scene` → `#30638E` (bold)
    - `story-cel` → `#003D5B` (bold)
  - **Entities**
    - `keyword.entity.premise` → `#EDAE49`
    - `entity-definition*` → `#EDAE49`
    - `entity.name.reference.premise` → `#EDAE49`
    - `entity.name.type.premise` → `#30638E` (not bold)
    - `punctuation.definition.entity.reference.begin/end.premise` → lighter body color `#4F6E86`
  - **Content layers**
    - `content-beat` → `#27AE60` (bold)
    - `content-treatment` → `#27AE60`
    - `content-narrative` → `#27AE60`
  - **General text**
    - Editor fg → `#003D5B`, bg → `#ffffff`
    - Strings and narrative bodies → `#003D5B`
    - Punctuation/separators → `#003D5B`
    - Comments → `#6B7C93` italic
  - **Adapters/keywords/imports**
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
