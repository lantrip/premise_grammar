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

async function registerCommandOnce(
  context: vscode.ExtensionContext,
  id: string,
  handler: (...args: any[]) => any
) {
  try {
    const existing = await vscode.commands.getCommands(true);
    if (existing.includes(id)) {
      return;
    }
  } catch {
    // If querying commands fails, fall through and attempt registration
  }
  const disp = vscode.commands.registerCommand(id, handler);
  context.subscriptions.push(disp);
}

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

      // Command: Show beats for entity under cursor
      await registerCommandOnce(
        context,
        "premise.showEntityBeats",
        async () => {
          const editor = vscode.window.activeTextEditor;
          if (!editor || !client) {
            return;
          }
          const doc = editor.document;
          const sel = editor.selection;
          // Prefer explicit selection text; else use word under cursor
          let raw = sel && !sel.isEmpty ? doc.getText(sel) : "";
          if (!raw) {
            const wordRange = doc.getWordRangeAtPosition(
              sel.active,
              /[^{}\s][^}]*?/
            );
            raw = wordRange ? doc.getText(wordRange) : "";
          }
          let name = raw.trim();
          if (name.startsWith("{") && name.endsWith("}")) {
            name = name.slice(1, -1).trim();
          }
          if (!name) {
            vscode.window.showInformationMessage(
              "Place cursor on an entity name."
            );
            return;
          }

          try {
            const res = await client.sendRequest<any>(
              "workspace/executeCommand",
              {
                command: "premise.entityBeats",
                arguments: [doc.uri.toString(), name],
              }
            );
            if (!Array.isArray(res) || res.length === 0) {
              vscode.window.showInformationMessage(
                `No beats found for ${name}.`
              );
              return;
            }
            const items = res.map((r: any) => {
              const scene = r.scene ? `Scene: ${r.scene}` : undefined;
              const cel = r.cel ? `Cel: ${r.cel}` : undefined;
              const beat = r.beat ? `Beat: ${r.beat}` : undefined;
              const detail = [scene, cel, beat].filter(Boolean).join(" • ");
              return {
                label: detail || `${r.uri}`,
                description: (r.uri as string).toString(),
                loc: r,
              } as vscode.QuickPickItem & { loc: any };
            });
            const pick = await vscode.window.showQuickPick(items, {
              placeHolder: `Beats for ${name}`,
            });
            if (pick) {
              const u = vscode.Uri.parse(pick.loc.uri as string);
              const rng = new vscode.Range(
                new vscode.Position(
                  pick.loc.range.start.line,
                  pick.loc.range.start.character
                ),
                new vscode.Position(
                  pick.loc.range.end.line,
                  pick.loc.range.end.character
                )
              );
              const d = await vscode.workspace.openTextDocument(u);
              const e = await vscode.window.showTextDocument(d);
              e.revealRange(rng, vscode.TextEditorRevealType.InCenter);
              e.selection = new vscode.Selection(rng.start, rng.end);
            }
          } catch (err) {
            outputChannel.appendLine(`entityBeats error: ${String(err)}`);
          }
        }
      );

      // Command: Scan workspace/story roots to warm index
      await registerCommandOnce(context, "premise.scanWorkspace", async () => {
        try {
          await client!.sendRequest("workspace/executeCommand", {
            command: "premise.scanWorkspace",
            arguments: [],
          });
          vscode.window.showInformationMessage(
            "Premise: workspace scan complete."
          );
        } catch (err) {
          outputChannel.appendLine(`scanWorkspace error: ${String(err)}`);
        }
      });
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
