import * as vscode from "vscode";
import * as path from "path";
import * as fs from "fs";
import { Parser, Language } from "web-tree-sitter";
import { PremiseSemanticTokensProvider } from "./semanticTokens";
import {
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
  TransportKind,
} from "vscode-languageclient/node";

let client: LanguageClient | undefined;

export async function activate(context: vscode.ExtensionContext) {
  console.log("Premise extension activating...");

  try {
    // Initialize Tree-sitter
    await Parser.init();
    const parser = new Parser();

    // Load WASM grammar
    const wasmPath = vscode.Uri.joinPath(
      context.extensionUri,
      "tree-sitter-premise.wasm"
    );
    const wasmBytes = await vscode.workspace.fs.readFile(wasmPath);
    const language = await Language.load(wasmBytes);
    parser.setLanguage(language);

    console.log("Premise Tree-sitter grammar loaded successfully");

    // Register semantic token provider
    const semanticProvider = new PremiseSemanticTokensProvider(parser);
    const semanticTokensProvider =
      vscode.languages.registerDocumentSemanticTokensProvider(
        { language: "premise" },
        semanticProvider,
        semanticProvider.legend
      );

    context.subscriptions.push(semanticTokensProvider);
    console.log("Premise semantic tokens provider registered");

    // Start LSP client (best-effort; gracefully degrade if not found)
    const serverPath = resolveServerPath(context);
    if (serverPath) {
      const outputChannel = vscode.window.createOutputChannel(
        "Premise Language Server"
      );
      const traceOutputChannel = vscode.window.createOutputChannel(
        "Premise Language Server Trace"
      );

      outputChannel.appendLine(`Using server: ${serverPath}`);

      const serverOptions: ServerOptions = {
        run: {
          command: serverPath,
          transport: TransportKind.stdio,
          options: {
            env: { ...process.env, RUST_LOG: process.env.RUST_LOG || "info" },
          },
        },
        debug: {
          command: serverPath,
          transport: TransportKind.stdio,
          options: {
            env: { ...process.env, RUST_LOG: process.env.RUST_LOG || "debug" },
          },
        },
      };

      const clientOptions: LanguageClientOptions = {
        documentSelector: [{ language: "premise" }],
        synchronize: {
          fileEvents: vscode.workspace.createFileSystemWatcher("**/*.prem"),
        },
        outputChannel,
        traceOutputChannel,
      };

      client = new LanguageClient(
        "premiseLanguageServer",
        "Premise Language Server",
        serverOptions,
        clientOptions
      );

      context.subscriptions.push(outputChannel, traceOutputChannel, {
        dispose: () => client?.stop(),
      });
      await client.start();
      outputChannel.appendLine("LSP client start() returned");
      console.log("Premise LSP client started");
    } else {
      vscode.window.showWarningMessage(
        "Premise LSP server binary not found. Syntax highlighting will still work."
      );
    }
  } catch (error) {
    console.error("Failed to initialize Premise extension:", error);
    vscode.window.showErrorMessage("Failed to load Premise language support");
  }
}

export function deactivate() {
  console.log("Premise extension deactivated");
  if (client) {
    client.stop();
    client = undefined;
  }
}

function resolveServerPath(
  context: vscode.ExtensionContext
): string | undefined {
  // Allow override via env var for development
  const envPath = process.env.PREMISE_LSP_PATH;
  if (envPath && fs.existsSync(envPath)) return envPath;

  const exe = process.platform === "win32" ? "premise-lsp.exe" : "premise-lsp";
  // Try sibling monorepo build outputs (debug then release)
  const candidates = [
    path.join(
      context.extensionUri.fsPath,
      "..",
      "..",
      "premise-lsp",
      "target",
      "debug",
      exe
    ),
    path.join(
      context.extensionUri.fsPath,
      "..",
      "..",
      "premise-lsp",
      "target",
      "release",
      exe
    ),
    // Fallback: within extension folder (if packaged with binary)
    path.join(context.extensionUri.fsPath, "server", exe),
  ];
  for (const p of candidates) {
    try {
      if (fs.existsSync(p)) return p;
    } catch {}
  }
  return undefined;
}
