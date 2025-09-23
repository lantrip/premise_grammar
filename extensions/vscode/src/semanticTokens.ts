import * as vscode from "vscode";
import { Parser } from "web-tree-sitter";

export class PremiseSemanticTokensProvider
  implements vscode.DocumentSemanticTokensProvider
{
  readonly legend = new vscode.SemanticTokensLegend(
    [
      // Basic types
      "comment",
      "keyword",
      "string",
      "number",
      "operator",
      "namespace",
      "type",
      "class",
      "enum",
      "interface",
      "struct",
      "typeParameter",
      "parameter",
      "variable",
      "property",
      "enumMember",
      "event",
      "function",
      "method",
      "macro",
      "label",

      // Premise-specific types
      "story-act",
      "story-scene",
      "story-cel",
      "content-beat",
      "content-treatment",
      "content-narrative",
      "entity-reference",
      "character-speaker",
      "entity-definition",
      "file-header",
      "metadata",
      "import",
    ],
    [
      "bold",
      "italic",
      "underline",
      "strikethrough",
      "readonly",
      "static",
      "abstract",
      "deprecated",
      "modification",
      "documentation",
      "defaultLibrary",
    ]
  );

  constructor(private parser: Parser) {}

  provideDocumentSemanticTokens(
    document: vscode.TextDocument
  ): vscode.SemanticTokens {
    const tree = this.parser.parse(document.getText());
    const builder = new vscode.SemanticTokensBuilder(this.legend);

    if (tree) {
      this.traverseTree(tree.rootNode, builder, document);
    }

    const result = builder.build();
    const count = (result.data?.length ?? 0) / 5;
    console.log(`Premise: Generated ${count} semantic tokens`);
    return result;
  }

  private traverseTree(
    node: any,
    builder: vscode.SemanticTokensBuilder,
    document: vscode.TextDocument
  ) {
    // Map Tree-sitter grammar nodes to semantic tokens
    switch (node.type) {
      case "act_header":
        this.addToken(builder, node, "story-act", ["bold"], document);
        break;
      case "scene_header":
        this.addToken(builder, node, "story-scene", ["bold"], document);
        break;
      case "cel_header":
        this.addToken(builder, node, "story-cel", ["bold"], document);
        break;
      case "content_type_beat":
        this.addToken(builder, node, "content-beat", ["bold"], document);
        break;
      case "content_type_treatment":
        this.addToken(builder, node, "content-treatment", ["bold"], document);
        break;
      case "content_type_narrative":
        this.addToken(builder, node, "content-narrative", ["bold"], document);
        break;
      // Disable semantic token coloring for entity references so TextMate
      // scopes can precisely color braces and names separately.
      case "entity_reference":
        break;
      case "dialogue_speaker":
        this.addToken(builder, node, "character-speaker", ["bold"], document);
        break;
      case "entity_construct":
        this.addToken(builder, node, "entity-definition", [], document);
        break;
      case "file_header":
        this.addToken(builder, node, "file-header", ["bold"], document);
        break;
      case "metadata_line":
        this.addToken(builder, node, "metadata", [], document);
        break;
      case "import_statement":
        this.addToken(builder, node, "import", [], document);
        break;
      case "adapter_statement":
        // Skip semantic tokens for adapter_statement - TextMate handles this better
        break;
      case "line_comment":
        this.addToken(builder, node, "comment", ["italic"], document);
        break;
      case "parenthetical":
        this.addToken(builder, node, "comment", ["italic"], document);
        break;
      case "entity_name":
        this.addToken(builder, node, "variable", ["readonly"], document);
        break;
      case "entity_desc":
        this.addToken(builder, node, "string", [], document);
        break;
      case "prop_key":
        this.addToken(builder, node, "property", [], document);
        break;
      case "prop_value":
        this.addToken(builder, node, "string", [], document);
        break;
      case "block_scalar":
        this.addToken(builder, node, "string", [], document);
        break;
      // Do not color whole narrative lines via semantic tokens; allow TextMate
      // to style inline entity references and punctuation precisely.
      case "indented_text_line":
        break;
      case "adapter_name":
        this.addToken(builder, node, "variable", ["readonly"], document);
        break;
      case "adapter_path":
        this.addToken(builder, node, "string", [], document);
        break;
      case "adapter_timing":
        this.addToken(builder, node, "keyword", [], document);
        break;
      // Avoid coloring braces via semantic tokens; TextMate handles specific
      // scopes for entity-reference braces and other curly punctuation.
      case "open_brace":
      case "close_brace":
        break;
    }

    // Recursively process child nodes
    for (const child of node.children) {
      this.traverseTree(child, builder, document);
    }
  }

  private addToken(
    builder: vscode.SemanticTokensBuilder,
    node: any,
    tokenType: string,
    modifiers: string[],
    document: vscode.TextDocument
  ) {
    const startPos = document.positionAt(node.startIndex);
    const endPos = document.positionAt(node.endIndex);

    const tokenTypeIndex = this.legend.tokenTypes.indexOf(tokenType);
    if (tokenTypeIndex === -1) {
      console.warn(`Unknown token type: ${tokenType}`);
      return;
    }

    const length = endPos.character - startPos.character;
    if (length <= 0) {
      return;
    }

    builder.push(
      startPos.line,
      startPos.character,
      length,
      tokenTypeIndex,
      this.encodeModifiers(modifiers)
    );
  }

  private encodeModifiers(modifiers: string[]): number {
    let result = 0;
    for (const modifier of modifiers) {
      const index = this.legend.tokenModifiers.indexOf(modifier);
      if (index !== -1) {
        result |= 1 << index;
      }
    }
    return result;
  }
}
