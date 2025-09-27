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
const path = __importStar(require("path"));
const fs = __importStar(require("fs"));
const web_tree_sitter_1 = require("web-tree-sitter");
const semanticTokens_1 = require("./semanticTokens");
const node_1 = require("vscode-languageclient/node");
let client;
async function activate(context) {
    console.log("Premise extension activating...");
    try {
        // Initialize Tree-sitter
        await web_tree_sitter_1.Parser.init();
        const parser = new web_tree_sitter_1.Parser();
        // Load WASM grammar
        const wasmPath = vscode.Uri.joinPath(context.extensionUri, "tree-sitter-premise.wasm");
        const wasmBytes = await vscode.workspace.fs.readFile(wasmPath);
        const language = await web_tree_sitter_1.Language.load(wasmBytes);
        parser.setLanguage(language);
        console.log("Premise Tree-sitter grammar loaded successfully");
        // Register semantic token provider
        const semanticProvider = new semanticTokens_1.PremiseSemanticTokensProvider(parser);
        const semanticTokensProvider = vscode.languages.registerDocumentSemanticTokensProvider({ language: "premise" }, semanticProvider, semanticProvider.legend);
        context.subscriptions.push(semanticTokensProvider);
        console.log("Premise semantic tokens provider registered");
        // Start LSP client (best-effort; gracefully degrade if not found)
        const serverPath = resolveServerPath(context);
        if (serverPath) {
            const outputChannel = vscode.window.createOutputChannel("Premise Language Server");
            const traceOutputChannel = vscode.window.createOutputChannel("Premise Language Server Trace");
            outputChannel.appendLine(`Using server: ${serverPath}`);
            const serverOptions = {
                run: {
                    command: serverPath,
                    transport: node_1.TransportKind.stdio,
                    options: {
                        env: { ...process.env, RUST_LOG: process.env.RUST_LOG || "info" },
                    },
                },
                debug: {
                    command: serverPath,
                    transport: node_1.TransportKind.stdio,
                    options: {
                        env: { ...process.env, RUST_LOG: process.env.RUST_LOG || "debug" },
                    },
                },
            };
            const clientOptions = {
                documentSelector: [{ language: "premise" }],
                synchronize: {
                    fileEvents: vscode.workspace.createFileSystemWatcher("**/*.prem"),
                },
                outputChannel,
                traceOutputChannel,
            };
            client = new node_1.LanguageClient("premiseLanguageServer", "Premise Language Server", serverOptions, clientOptions);
            context.subscriptions.push(outputChannel, traceOutputChannel, {
                dispose: () => client?.stop(),
            });
            await client.start();
            outputChannel.appendLine("LSP client start() returned");
            console.log("Premise LSP client started");
        }
        else {
            vscode.window.showWarningMessage("Premise LSP server binary not found. Syntax highlighting will still work.");
        }
    }
    catch (error) {
        console.error("Failed to initialize Premise extension:", error);
        vscode.window.showErrorMessage("Failed to load Premise language support");
    }
}
exports.activate = activate;
function deactivate() {
    console.log("Premise extension deactivated");
    if (client) {
        client.stop();
        client = undefined;
    }
}
exports.deactivate = deactivate;
function resolveServerPath(context) {
    // Allow override via env var for development
    const envPath = process.env.PREMISE_LSP_PATH;
    if (envPath && fs.existsSync(envPath))
        return envPath;
    const exe = process.platform === "win32" ? "premise-lsp.exe" : "premise-lsp";
    // Try sibling monorepo build outputs (debug then release)
    const candidates = [
        path.join(context.extensionUri.fsPath, "..", "..", "premise-lsp", "target", "debug", exe),
        path.join(context.extensionUri.fsPath, "..", "..", "premise-lsp", "target", "release", exe),
        // Fallback: within extension folder (if packaged with binary)
        path.join(context.extensionUri.fsPath, "server", exe),
    ];
    for (const p of candidates) {
        try {
            if (fs.existsSync(p))
                return p;
        }
        catch { }
    }
    return undefined;
}
//# sourceMappingURL=extension.js.map