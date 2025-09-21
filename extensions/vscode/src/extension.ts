import * as vscode from 'vscode';
import { Parser, Language } from 'web-tree-sitter';
import { PremiseSemanticTokensProvider } from './semanticTokens';

export async function activate(context: vscode.ExtensionContext) {
    console.log('Premise extension activating...');

    try {
        // Initialize Tree-sitter
        await Parser.init();
        const parser = new Parser();

        // Load WASM grammar
        const wasmPath = vscode.Uri.joinPath(context.extensionUri, 'tree-sitter-premise.wasm');
        const wasmBytes = await vscode.workspace.fs.readFile(wasmPath);
        const language = await Language.load(wasmBytes);
        parser.setLanguage(language);

        console.log('Premise Tree-sitter grammar loaded successfully');

        // Register semantic token provider
        const semanticProvider = new PremiseSemanticTokensProvider(parser);
        const semanticTokensProvider = vscode.languages.registerDocumentSemanticTokensProvider(
            { language: 'premise' },
            semanticProvider,
            semanticProvider.legend
        );

        context.subscriptions.push(semanticTokensProvider);
        console.log('Premise semantic tokens provider registered');

        // TODO: Register document outline provider
        // TODO: Register hover provider for entity references

    } catch (error) {
        console.error('Failed to initialize Premise extension:', error);
        vscode.window.showErrorMessage('Failed to load Premise language support');
    }
}

export function deactivate() {
    console.log('Premise extension deactivated');
}