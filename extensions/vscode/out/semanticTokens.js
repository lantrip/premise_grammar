"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.CuneiformSemanticTokensProvider = void 0;
const vscode = __importStar(require("vscode"));
class CuneiformSemanticTokensProvider {
    constructor(parser) {
        this.parser = parser;
        this.legend = new vscode.SemanticTokensLegend([
            // Basic types
            'comment', 'keyword', 'string', 'number', 'operator',
            'namespace', 'type', 'class', 'enum', 'interface',
            'struct', 'typeParameter', 'parameter', 'variable',
            'property', 'enumMember', 'event', 'function',
            'method', 'macro', 'label',
            // Cuneiform-specific types
            'story-act', 'story-scene', 'story-cel',
            'content-beat', 'content-treatment', 'content-narrative',
            'entity-reference', 'character-speaker', 'entity-definition',
            'file-header', 'metadata', 'import'
        ], [
            'bold', 'italic', 'underline', 'strikethrough',
            'readonly', 'static', 'abstract', 'deprecated',
            'modification', 'documentation', 'defaultLibrary'
        ]);
    }
    provideDocumentSemanticTokens(document) {
        const tree = this.parser.parse(document.getText());
        const tokens = [];
        if (tree) {
            this.traverseTree(tree.rootNode, tokens, document);
        }
        return new vscode.SemanticTokens(new Uint32Array(tokens));
    }
    traverseTree(node, tokens, document) {
        // Map Tree-sitter grammar nodes to semantic tokens
        switch (node.type) {
            case 'act_header':
                this.addToken(tokens, node, 'story-act', ['bold'], document);
                break;
            case 'scene_header':
                this.addToken(tokens, node, 'story-scene', ['bold'], document);
                break;
            case 'cel_header':
                this.addToken(tokens, node, 'story-cel', ['bold'], document);
                break;
            case 'content_type_beat':
                this.addToken(tokens, node, 'content-beat', ['bold'], document);
                break;
            case 'content_type_treatment':
                this.addToken(tokens, node, 'content-treatment', ['bold'], document);
                break;
            case 'content_type_narrative':
                this.addToken(tokens, node, 'content-narrative', ['bold'], document);
                break;
            case 'entity_reference':
                this.addToken(tokens, node, 'entity-reference', [], document);
                break;
            case 'dialogue_speaker':
                this.addToken(tokens, node, 'character-speaker', ['bold'], document);
                break;
            case 'entity_construct':
                this.addToken(tokens, node, 'entity-definition', [], document);
                break;
            case 'file_header':
                this.addToken(tokens, node, 'file-header', ['bold'], document);
                break;
            case 'metadata_line':
                this.addToken(tokens, node, 'metadata', [], document);
                break;
            case 'import_statement':
                this.addToken(tokens, node, 'import', [], document);
                break;
            case 'adapter_statement':
                this.addToken(tokens, node, 'import', [], document);
                break;
            case 'line_comment':
                this.addToken(tokens, node, 'comment', ['italic'], document);
                break;
            case 'parenthetical':
                this.addToken(tokens, node, 'comment', ['italic'], document);
                break;
        }
        // Recursively process child nodes
        for (const child of node.children) {
            this.traverseTree(child, tokens, document);
        }
    }
    addToken(tokens, node, tokenType, modifiers, document) {
        const startPos = document.positionAt(node.startIndex);
        const endPos = document.positionAt(node.endIndex);
        const tokenTypeIndex = this.legend.tokenTypes.indexOf(tokenType);
        if (tokenTypeIndex === -1) {
            console.warn(`Unknown token type: ${tokenType}`);
            return;
        }
        tokens.push(startPos.line, startPos.character, endPos.character - startPos.character, tokenTypeIndex, this.encodeModifiers(modifiers));
    }
    encodeModifiers(modifiers) {
        let result = 0;
        for (const modifier of modifiers) {
            const index = this.legend.tokenModifiers.indexOf(modifier);
            if (index !== -1) {
                result |= (1 << index);
            }
        }
        return result;
    }
}
exports.CuneiformSemanticTokensProvider = CuneiformSemanticTokensProvider;
//# sourceMappingURL=semanticTokens.js.map