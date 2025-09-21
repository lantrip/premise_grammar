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
exports.deactivate = exports.activate = void 0;
const vscode = __importStar(require("vscode"));
const web_tree_sitter_1 = require("web-tree-sitter");
const semanticTokens_1 = require("./semanticTokens");
async function activate(context) {
    console.log('Premise extension activating...');
    try {
        // Initialize Tree-sitter
        await web_tree_sitter_1.Parser.init();
        const parser = new web_tree_sitter_1.Parser();
        // Load WASM grammar
        const wasmPath = vscode.Uri.joinPath(context.extensionUri, 'tree-sitter-premise.wasm');
        const wasmBytes = await vscode.workspace.fs.readFile(wasmPath);
        const language = await web_tree_sitter_1.Language.load(wasmBytes);
        parser.setLanguage(language);
        console.log('Premise Tree-sitter grammar loaded successfully');
        // Register semantic token provider
        const semanticProvider = new semanticTokens_1.PremiseSemanticTokensProvider(parser);
        const semanticTokensProvider = vscode.languages.registerDocumentSemanticTokensProvider({ language: 'premise' }, semanticProvider, semanticProvider.legend);
        context.subscriptions.push(semanticTokensProvider);
        console.log('Premise semantic tokens provider registered');
        // TODO: Register document outline provider
        // TODO: Register hover provider for entity references
    }
    catch (error) {
        console.error('Failed to initialize Premise extension:', error);
        vscode.window.showErrorMessage('Failed to load Premise language support');
    }
}
exports.activate = activate;
function deactivate() {
    console.log('Premise extension deactivated');
}
exports.deactivate = deactivate;
//# sourceMappingURL=extension.js.map