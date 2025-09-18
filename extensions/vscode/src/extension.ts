import * as vscode from 'vscode';
import { Parser, Language } from 'web-tree-sitter';
import { CuneiformSemanticTokensProvider } from './semanticTokens';

export async function activate(context: vscode.ExtensionContext) {
    console.log('Cuneiform extension activating...');

    try {
        // Initialize Tree-sitter
        await Parser.init();
        const parser = new Parser();

        // Load WASM grammar
        const wasmPath = vscode.Uri.joinPath(context.extensionUri, 'tree-sitter-cuneiform.wasm');
        const wasmBytes = await vscode.workspace.fs.readFile(wasmPath);
        const language = await Language.load(wasmBytes);
        parser.setLanguage(language);

        console.log('Cuneiform Tree-sitter grammar loaded successfully');

        // Register semantic token provider
        const semanticProvider = new CuneiformSemanticTokensProvider(parser);
        const semanticTokensProvider = vscode.languages.registerDocumentSemanticTokensProvider(
            { language: 'cuneiform' },
            semanticProvider,
            semanticProvider.legend
        );

        context.subscriptions.push(semanticTokensProvider);
        console.log('Cuneiform semantic tokens provider registered');

        // TODO: Register document outline provider
        // TODO: Register hover provider for entity references

    } catch (error) {
        console.error('Failed to initialize Cuneiform extension:', error);
        vscode.window.showErrorMessage('Failed to load Cuneiform language support');
    }
}

export function deactivate() {
    console.log('Cuneiform extension deactivated');
}