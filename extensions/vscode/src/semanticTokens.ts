import * as vscode from "vscode";
import { Parser } from "web-tree-sitter";

export class CuneiformSemanticTokensProvider
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

      // Cuneiform-specific types
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
    const tokens: number[] = [];

    if (tree) {
      this.traverseTree(tree.rootNode, tokens, document);
      console.log(`Cuneiform: Generated ${tokens.length / 5} semantic tokens`);
    }

    return new vscode.SemanticTokens(new Uint32Array(tokens));
  }

  private traverseTree(
    node: any,
    tokens: number[],
    document: vscode.TextDocument
  ) {
    // Map Tree-sitter grammar nodes to semantic tokens
    switch (node.type) {
      case "act_header":
        this.addToken(tokens, node, "story-act", ["bold"], document);
        break;
      case "scene_header":
        this.addToken(tokens, node, "story-scene", ["bold"], document);
        break;
      case "cel_header":
        this.addToken(tokens, node, "story-cel", ["bold"], document);
        break;
      case "content_type_beat":
        this.addToken(tokens, node, "content-beat", ["bold"], document);
        break;
      case "content_type_treatment":
        this.addToken(tokens, node, "content-treatment", ["bold"], document);
        break;
      case "content_type_narrative":
        this.addToken(tokens, node, "content-narrative", ["bold"], document);
        break;
      case "entity_reference":
        this.addToken(tokens, node, "entity-reference", [], document);
        break;
      case "dialogue_speaker":
        this.addToken(tokens, node, "character-speaker", ["bold"], document);
        break;
      case "entity_construct":
        this.addToken(tokens, node, "entity-definition", [], document);
        break;
      case "file_header":
        this.addToken(tokens, node, "file-header", ["bold"], document);
        break;
      case "metadata_line":
        this.addToken(tokens, node, "metadata", [], document);
        break;
      case "import_statement":
        this.addToken(tokens, node, "import", [], document);
        break;
      case "adapter_statement":
        this.addToken(tokens, node, "import", [], document);
        break;
      case "line_comment":
        this.addToken(tokens, node, "comment", ["italic"], document);
        break;
      case "parenthetical":
        this.addToken(tokens, node, "comment", ["italic"], document);
        break;
      case "entity_name":
        console.log(
          `Found entity_name: ${document
            .getText()
            .substring(node.startIndex, node.endIndex)}`
        );
        // Use standard token type so most themes colorize without customization
        this.addToken(tokens, node, "variable", ["readonly"], document);
        break;
      case "entity_desc":
        console.log(
          `Found entity_desc: ${document
            .getText()
            .substring(node.startIndex, node.endIndex)}`
        );
        this.addToken(tokens, node, "string", [], document);
        break;
      case "prop_key":
        this.addToken(tokens, node, "property", [], document);
        break;
      case "prop_value":
        this.addToken(tokens, node, "string", [], document);
        break;
    }

    // Recursively process child nodes
    for (const child of node.children) {
      this.traverseTree(child, tokens, document);
    }
  }

  private addToken(
    tokens: number[],
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

    tokens.push(
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
