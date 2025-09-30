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
exports.insertBeatsAnchored = exports.getSectionRegionsForStructure = exports.insertBeatsAnchoredIntoDocument = exports.deactivate = exports.activate = void 0;
const vscode = __importStar(require("vscode"));
const path = __importStar(require("path"));
const fs = __importStar(require("fs"));
const https = __importStar(require("https"));
const cp = __importStar(require("child_process"));
const web_tree_sitter_1 = require("web-tree-sitter");
const semanticTokens_1 = require("./semanticTokens");
const node_1 = require("vscode-languageclient/node");
let client;
async function safeOpenTextDocument(uri) {
    try {
        return await vscode.workspace.openTextDocument(uri);
    }
    catch (err) {
        try {
            // Retry via fsPath normalization if available
            if (uri.scheme === "file" && uri.fsPath) {
                const normalized = vscode.Uri.file(uri.fsPath);
                return await vscode.workspace.openTextDocument(normalized);
            }
        }
        catch { }
        // Swallow error; caller should handle undefined
        return undefined;
    }
}
function normalizeFileUri(input) {
    try {
        const u = typeof input === "string" ? vscode.Uri.parse(input) : input;
        if (u.scheme === "file") {
            return vscode.Uri.file(u.fsPath);
        }
        return u;
    }
    catch {
        // Fallback: try as file path string
        if (typeof input === "string") {
            try {
                return vscode.Uri.file(input);
            }
            catch { }
        }
        // As a last resort, return a dummy URI which should never match
        return vscode.Uri.file("/");
    }
}
function coerceToFileUri(input) {
    try {
        if (!input)
            return undefined;
        if (input instanceof vscode.Uri)
            return normalizeFileUri(input);
        if (typeof input === "string")
            return normalizeFileUri(input);
        // VSCode UriComponents shape
        if (typeof input === "object" && typeof input.scheme === "string") {
            try {
                const u = vscode.Uri.from(input);
                return normalizeFileUri(u);
            }
            catch { }
        }
        // LSP Url encoded as { path: string, scheme: string }
        if (typeof input === "object" &&
            typeof input.path === "string" &&
            typeof input.scheme === "string") {
            try {
                const u = vscode.Uri.from({
                    scheme: input.scheme,
                    path: input.path,
                });
                return normalizeFileUri(u);
            }
            catch { }
        }
        return undefined;
    }
    catch {
        return undefined;
    }
}
async function registerCommandOnce(context, id, handler) {
    try {
        const existing = await vscode.commands.getCommands(true);
        if (existing.includes(id)) {
            return;
        }
    }
    catch {
        // If querying commands fails, fall through and attempt registration
    }
    const disp = vscode.commands.registerCommand(id, handler);
    context.subscriptions.push(disp);
}
async function activate(context) {
    console.log("🚀 Premise extension activate() called - timestamp:", Date.now());
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
            // Command: Show beats for entity under cursor
            await registerCommandOnce(context, "premise.showEntityBeats", async () => {
                const editor = vscode.window.activeTextEditor;
                if (!editor || !client) {
                    return;
                }
                const doc = editor.document;
                const sel = editor.selection;
                // Prefer explicit selection text; else infer entity under cursor (including within braces)
                let raw = sel && !sel.isEmpty ? doc.getText(sel) : "";
                if (!raw) {
                    // Try to expand to surrounding { ... } on the same line
                    const pos = sel.active;
                    const lineText = doc.lineAt(pos.line).text;
                    const left = lineText.lastIndexOf("{", pos.character);
                    const right = lineText.indexOf("}", Math.max(pos.character, 0));
                    if (left !== -1 && right !== -1 && right > left) {
                        raw = lineText.substring(left + 1, right);
                    }
                }
                if (!raw) {
                    const wordRange = doc.getWordRangeAtPosition(sel.active, /[^{}\s][^}]*?/);
                    raw = wordRange ? doc.getText(wordRange) : "";
                }
                let name = raw.trim();
                if (name.startsWith("{") && name.endsWith("}")) {
                    name = name.slice(1, -1).trim();
                }
                if (!name) {
                    vscode.window.showInformationMessage("Place cursor on an entity name.");
                    return;
                }
                try {
                    const res = await client.sendRequest("workspace/executeCommand", {
                        command: "premise.entityBeats",
                        arguments: [doc.uri.toString(), name],
                    });
                    if (!Array.isArray(res) || res.length === 0) {
                        vscode.window.showInformationMessage(`No beats found for ${name}.`);
                        return;
                    }
                    const items = res.map((r) => {
                        const scene = r.scene ? `Scene: ${r.scene}` : undefined;
                        const cel = r.cel ? `Cel: ${r.cel}` : undefined;
                        const beat = r.beat ? `Beat: ${r.beat}` : undefined;
                        const detail = [scene, cel, beat].filter(Boolean).join(" • ");
                        return {
                            label: detail || `${r.uri}`,
                            description: r.uri.toString(),
                            loc: r,
                        };
                    });
                    const pick = await vscode.window.showQuickPick(items, {
                        placeHolder: `Beats for ${name}`,
                    });
                    if (pick) {
                        const u = normalizeFileUri(pick.loc.uri);
                        const rng = new vscode.Range(new vscode.Position(pick.loc.range.start.line, pick.loc.range.start.character), new vscode.Position(pick.loc.range.end.line, pick.loc.range.end.character));
                        const d = (await safeOpenTextDocument(u)) || doc;
                        const e = await vscode.window.showTextDocument(d);
                        e.revealRange(rng, vscode.TextEditorRevealType.InCenter);
                        e.selection = new vscode.Selection(rng.start, rng.end);
                    }
                }
                catch (err) {
                    outputChannel.appendLine(`entityBeats error: ${String(err)}`);
                }
            });
            // Command: Scan workspace/story roots to warm index
            await registerCommandOnce(context, "premise.scanWorkspace", async () => {
                try {
                    await client.sendRequest("workspace/executeCommand", {
                        command: "premise.scanWorkspace",
                        arguments: [],
                    });
                    vscode.window.showInformationMessage("Premise: workspace scan complete.");
                }
                catch (err) {
                    outputChannel.appendLine(`scanWorkspace error: ${String(err)}`);
                }
            });
            // Command: Generate beats (file / uncommitted-file scopes)
            await registerCommandOnce(context, "premise.generateBeats", async () => {
                console.log("🔥 premise.generateBeats command started - timestamp:", Date.now());
                const editor = vscode.window.activeTextEditor;
                if (!editor)
                    return;
                const doc = editor.document;
                if (doc.languageId !== "premise")
                    return;
                const scope = await pickScope();
                if (!scope)
                    return;
                const mode = await pickBeatGenerationMode();
                if (!mode)
                    return;
                const cfg = vscode.workspace.getConfiguration("premise");
                const provider = cfg.get("ai.provider", "openrouter");
                const model = cfg.get("ai.model", "openai/gpt-4o-mini");
                const endpoint = cfg.get("ai.endpoint", "https://openrouter.ai/api/v1/chat/completions");
                const apiKey = cfg.get("ai.apiKey") || process.env.OPENROUTER_API_KEY || "";
                if (provider !== "openrouter") {
                    vscode.window.showWarningMessage("Only OpenRouter is supported in this preview.");
                    return;
                }
                if (!apiKey) {
                    vscode.window.showErrorMessage("Set OpenRouter API key in settings (premise.ai.apiKey) or OPENROUTER_API_KEY.");
                    return;
                }
                const fileText = doc.getText();
                // Resolve entity names early so all flows (including single-section fast path) can use them
                const entityNames = await listEntityNamesForUri(doc.uri).catch(() => []);
                const structure = await collectStructureForUris([
                    doc.uri.toString(),
                ]).catch(() => ({ sections: [] }));
                const cfg_ai = vscode.workspace.getConfiguration("premise.ai");
                const qualityLevel = cfg_ai.get("beatQualityLevel", "concise");
                const enablePreview = cfg_ai.get("enablePreviewMode", true);
                const system = getBeatSystemPrompt(mode, qualityLevel);
                const schema = getBeatSchemaPrompt(mode, qualityLevel);
                let extra = "";
                let textToProcess = fileText;
                let structureToProcess = structure;
                let singleSectionRegion;
                if (scope === "current-section") {
                    // Find the current section based on cursor position
                    const cursorLine = editor.selection.active.line;
                    console.log("🔍 Looking for section at cursor line:", cursorLine);
                    console.log("🔍 Current document URI:", doc.uri.toString());
                    console.log("🔍 Available structure:", JSON.stringify(structure, null, 2));
                    const currentSection = findCurrentSection(structure, cursorLine);
                    if (currentSection) {
                        textToProcess = getSectionText(doc, currentSection);
                        // Ensure the section uses the current document's URI, not whatever was in the structure
                        const correctedSection = {
                            ...currentSection,
                            uri: doc.uri.toString(),
                            file: doc.uri.toString(),
                        };
                        structureToProcess = { sections: [correctedSection] };
                        // Use the explicit section range for a single-region flow
                        try {
                            const s = correctedSection;
                            const sStart = Number(s?.range?.start?.line) || 0;
                            const sEnd = Number(s?.range?.end?.line) || doc.lineCount - 1;
                            singleSectionRegion = {
                                start: Math.max(0, sStart + 1),
                                end: Math.max(sStart + 1, sEnd),
                            };
                        }
                        catch {
                            singleSectionRegion = undefined;
                        }
                        console.log("🎯 Processing current section:", correctedSection);
                        console.log("🎯 Section text to process:", textToProcess.substring(0, 200) + "...");
                    }
                    else {
                        console.log("❌ No section found at cursor line:", cursorLine);
                        // Heuristic fallback: infer region by scanning for nearest header lines (=== / == / =)
                        try {
                            const isHeader = (lineText) => {
                                // Return header level (# of leading '=') if matches, else undefined
                                const m = lineText.match(/^=+/);
                                return m ? m[0].length : undefined;
                            };
                            // Find the nearest header at or before cursor
                            let headerLine = -1;
                            let headerLevel = undefined;
                            for (let i = cursorLine; i >= 0; i--) {
                                const lt = doc.lineAt(i).text;
                                const lvl = isHeader(lt);
                                if (lvl) {
                                    headerLine = i;
                                    headerLevel = lvl;
                                    break;
                                }
                            }
                            // Find the next header after cursor (any level)
                            let nextHeaderLine = -1;
                            for (let i = Math.max(0, headerLine) + 1; i < doc.lineCount; i++) {
                                const lt = doc.lineAt(i).text;
                                if (isHeader(lt)) {
                                    nextHeaderLine = i;
                                    break;
                                }
                            }
                            const regionStart = Math.max(0, headerLine >= 0 ? headerLine + 1 : 0);
                            const regionEnd = nextHeaderLine >= 0
                                ? Math.max(nextHeaderLine - 1, regionStart)
                                : doc.lineCount - 1;
                            // Build a minimal synthetic section for downstream logic
                            const synthetic = {
                                uri: doc.uri.toString(),
                                file: doc.uri.toString(),
                                range: {
                                    start: { line: Math.max(0, headerLine), character: 0 },
                                    end: {
                                        line: regionEnd,
                                        character: doc.lineAt(regionEnd).range.end.character,
                                    },
                                },
                            };
                            // Assign a best-effort kind so headers/regions can be computed
                            if (headerLevel && headerLevel >= 3)
                                synthetic.cel = "";
                            else if (headerLevel && headerLevel === 2)
                                synthetic.scene = "";
                            else
                                synthetic.act = "";
                            structureToProcess = { sections: [synthetic] };
                            singleSectionRegion = { start: regionStart, end: regionEnd };
                            textToProcess = getDocumentTextRange(doc, regionStart, regionEnd);
                            console.log("🧭 Using inferred section region:", singleSectionRegion);
                            console.log("🧭 Synthetic section:", synthetic);
                            // Do not early-return; continue with fast-path flow using the inferred region
                        }
                        catch (e) {
                            vscode.window.showWarningMessage("No section found at cursor position");
                            return;
                        }
                    }
                }
                else if (scope === "uncommitted-file") {
                    const ranges = await getUncommittedChangedRangesForFile(doc.uri.fsPath);
                    extra = `\\nChangedRanges: ${JSON.stringify(ranges)}`;
                }
                const user = `File: ${doc.uri.fsPath}\\nEntities: ${JSON.stringify(entityNames)}\\nStructure: ${JSON.stringify(structureToProcess)}${extra}\\n---\\n${textToProcess}\\n---\\n${schema}`;
                try {
                    const rateCfg = vscode.workspace.getConfiguration("premise.ai");
                    const rpm = Math.max(1, rateCfg.get("rateLimitPerMinute", 60));
                    const minIntervalMs = Math.floor(60000 / rpm);
                    let lastCall = 0;
                    // Fast path: current-section -> single call only
                    if (scope === "current-section" && singleSectionRegion) {
                        const previewInserts = vscode.workspace
                            .getConfiguration("premise.ai")
                            .get("previewInserts", false);
                        const neighborInfo = (() => {
                            try {
                                const headers = getSectionRegionsForStructure(structureToProcess, doc);
                                const idx = headers.findIndex((h) => h.start === singleSectionRegion.start &&
                                    h.end === singleSectionRegion.end);
                                const prev = idx > 0 ? headers[idx - 1] : undefined;
                                const next = idx >= 0 && idx + 1 < headers.length
                                    ? headers[idx + 1]
                                    : undefined;
                                const fmt = (x) => (x ? `${x.kind}${x.title ? ` — ${x.title}` : ""}` : "");
                                const prevStr = fmt(prev);
                                const nextStr = fmt(next);
                                return prevStr || nextStr
                                    ? `\nNeighbors: ${prevStr ? `Prev: ${prevStr}` : ""}${prevStr && nextStr ? "; " : ""}${nextStr ? `Next: ${nextStr}` : ""}`
                                    : "";
                            }
                            catch {
                                return "";
                            }
                        })();
                        const sectionText = getDocumentTextRange(doc, singleSectionRegion.start, singleSectionRegion.end);
                        const userSection = `File: ${doc.uri.fsPath}\nEntities: ${JSON.stringify(entityNames)}\nSection: lines ${singleSectionRegion.start}-${singleSectionRegion.end}${neighborInfo}\n---\n${sectionText}\n---\n${schema}`;
                        const content = await openRouterChat({
                            endpoint,
                            apiKey,
                            model,
                            messages: [
                                { role: "system", content: system },
                                { role: "user", content: userSection },
                            ],
                        });
                        const beats = extractBeats(content);
                        console.log("🎯 Extracted beats:", beats);
                        if (beats.length > 0) {
                            const insertPos = getBeatInsertPosition();
                            if (previewInserts) {
                                const choice = await vscode.window.showInformationMessage(`Insert ${beats.length} beat(s) into ${path.basename(doc.uri.fsPath)}?`, { modal: true, detail: beats.join("\n") }, "Apply", "Cancel");
                                if (choice !== "Apply")
                                    return;
                            }
                            await insertBeatsAnchored(editor, beats, structureToProcess, [
                                {
                                    startLine: singleSectionRegion.start,
                                    endLine: singleSectionRegion.end,
                                },
                            ], entityNames, insertPos, mode);
                        }
                        // Single-section handled; stop here
                        console.log("✅ current-section flow completed");
                        return;
                    }
                    const runSequential = async (items, worker, token) => {
                        for (const it of items) {
                            for (const region of it.regions) {
                                if (token.isCancellationRequested)
                                    return;
                                const now = Date.now();
                                const elapsed = now - lastCall;
                                if (elapsed < minIntervalMs) {
                                    await new Promise((r) => setTimeout(r, minIntervalMs - elapsed));
                                }
                                await worker({ uri: it.uri, structure: it.structure, region });
                                lastCall = Date.now();
                            }
                        }
                    };
                    // Determine target files for this scope
                    const targets = [];
                    if (scope === "current-section") {
                        const text = doc.getText();
                        const changed = undefined;
                        targets.push({
                            uri: doc.uri,
                            text,
                            structure: structureToProcess,
                            changed,
                        });
                    }
                    else if (scope === "file" || scope === "uncommitted-file") {
                        const text = doc.getText();
                        const changed = scope === "uncommitted-file"
                            ? await getUncommittedChangedRangesForFile(doc.uri.fsPath)
                            : undefined;
                        targets.push({ uri: doc.uri, text, structure, changed });
                    }
                    else {
                        const rootPath = (await getStoryRootPathForUri(doc.uri)) ||
                            path.dirname(doc.uri.fsPath);
                        const uris = scope === "root"
                            ? await listPremFilesUnderRoot(rootPath)
                            : await listUncommittedPremFilesUnderRoot(rootPath);
                        if (uris.length === 0) {
                            vscode.window.showInformationMessage("No files to process in selected scope.");
                            return;
                        }
                        const allStruct = await collectStructureForUris(uris.map((u) => normalizeFileUri(u).toString()));
                        for (const u of uris) {
                            const nu = normalizeFileUri(u);
                            const d = (await safeOpenTextDocument(nu)) || doc;
                            const text = d.getText();
                            const per = {
                                sections: (allStruct?.sections || []).filter((s) => {
                                    // Prefer strict URI equality if provided
                                    if (s.uri) {
                                        try {
                                            const suri = typeof s.uri === "string"
                                                ? normalizeFileUri(s.uri)
                                                : coerceToFileUri(s.uri) || nu;
                                            if (suri.toString() === nu.toString())
                                                return true;
                                        }
                                        catch { }
                                    }
                                    // Back-compat: also accept exact match on file URI object/string
                                    if (s.file) {
                                        try {
                                            const sf = typeof s.file === "string"
                                                ? normalizeFileUri(s.file)
                                                : coerceToFileUri(s.file) || nu;
                                            if (sf.toString() === nu.toString())
                                                return true;
                                        }
                                        catch { }
                                    }
                                    return false;
                                }),
                            };
                            const changed = scope === "uncommitted-root"
                                ? await getUncommittedChangedRangesForFile(nu.fsPath)
                                : undefined;
                            targets.push({ uri: nu, text, structure: per, changed });
                        }
                    }
                    // entityNames already resolved above
                    const perSectionSystem = system;
                    const perSectionSchema = schema;
                    const previewInserts = vscode.workspace
                        .getConfiguration("premise.ai")
                        .get("previewInserts", false);
                    let totalBeats = 0;
                    let totalEntities = 0;
                    let applyAllConfirmed = false;
                    await vscode.window.withProgress({
                        location: vscode.ProgressLocation.Notification,
                        title: "Premise: Generating beats and updates",
                        cancellable: true,
                    }, async (progress, token) => {
                        const work = [];
                        for (const t of targets) {
                            const d = t.uri.toString() === doc.uri.toString()
                                ? doc
                                : (await safeOpenTextDocument(t.uri)) || doc;
                            const regions = getSectionRegionsForStructure(t.structure, d);
                            let filtered = t.changed && t.changed.length > 0
                                ? regions.filter((r) => t.changed.some((cr) => !(r.end < cr.startLine || r.start > cr.endLine)))
                                : regions;
                            if (filtered.length === 0 &&
                                t.changed &&
                                t.changed.length > 0) {
                                filtered = [{ start: 0, end: d.lineCount - 1 }];
                            }
                            work.push({
                                uri: t.uri,
                                structure: t.structure,
                                regions: filtered.map((r) => ({
                                    start: r.start,
                                    end: r.end,
                                    kind: r.kind,
                                    title: r.title,
                                })),
                            });
                        }
                        let processed = 0;
                        await runSequential(work, async ({ uri, region, structure: perStructure }) => {
                            if (token.isCancellationRequested)
                                return;
                            const d = uri.toString() === doc.uri.toString()
                                ? doc
                                : (await safeOpenTextDocument(uri)) || doc;
                            const sectionText = getDocumentTextRange(d, region.start, region.end);
                            const neighborInfo = (() => {
                                try {
                                    const headers = getSectionRegionsForStructure(perStructure, d);
                                    const idx = headers.findIndex((h) => h.start === region.start && h.end === region.end);
                                    const prev = idx > 0 ? headers[idx - 1] : undefined;
                                    const next = idx >= 0 && idx + 1 < headers.length
                                        ? headers[idx + 1]
                                        : undefined;
                                    const fmt = (x) => x ? `${x.kind}${x.title ? ` — ${x.title}` : ""}` : "";
                                    const prevStr = fmt(prev);
                                    const nextStr = fmt(next);
                                    return prevStr || nextStr
                                        ? `\nNeighbors: ${prevStr ? `Prev: ${prevStr}` : ""}${prevStr && nextStr ? "; " : ""}${nextStr ? `Next: ${nextStr}` : ""}`
                                        : "";
                                }
                                catch {
                                    return "";
                                }
                            })();
                            const userSection = `File: ${uri.fsPath}\nEntities: ${JSON.stringify(entityNames)}\nSection: lines ${region.start}-${region.end}${neighborInfo}\n---\n${sectionText}\n---\n${perSectionSchema}`;
                            const content = await openRouterChat({
                                endpoint,
                                apiKey,
                                model,
                                messages: [
                                    { role: "system", content: perSectionSystem },
                                    { role: "user", content: userSection },
                                ],
                            });
                            const beats = extractBeats(content);
                            console.log("🎯 Extracted beats:", beats);
                            if (beats.length > 0) {
                                totalBeats += beats.length;
                                const changedRangeForSection = [
                                    { startLine: region.start, endLine: region.end },
                                ];
                                const insertPos = getBeatInsertPosition();
                                if (previewInserts && !applyAllConfirmed) {
                                    const hdr = `${region.kind || "section"}${region.title ? ` — ${region.title}` : ""}`;
                                    const previewText = beats.join("\n");
                                    const choice = await vscode.window.showInformationMessage(`Insert ${beats.length} beat(s) into ${path.basename(uri.fsPath)} (${hdr})?`, { modal: true, detail: previewText }, "Apply", "Skip", "Apply All", "Cancel");
                                    if (choice === "Cancel") {
                                        return;
                                    }
                                    else if (choice === "Skip") {
                                        processed += 1;
                                        progress.report({
                                            message: `Processed ${processed}/${work.reduce((a, w) => a + w.regions.length, 0)} sections`,
                                        });
                                        return;
                                    }
                                    else if (choice === "Apply All") {
                                        applyAllConfirmed = true;
                                    }
                                    else if (choice !== "Apply") {
                                        processed += 1;
                                        progress.report({
                                            message: `Processed ${processed}/${work.reduce((a, w) => a + w.regions.length, 0)} sections`,
                                        });
                                        return;
                                    }
                                }
                                if (uri.toString() === doc.uri.toString()) {
                                    await insertBeatsAnchored(editor, beats, perStructure, changedRangeForSection, entityNames, insertPos, mode);
                                }
                                else {
                                    await insertBeatsAnchoredIntoDocument(d, beats, perStructure, changedRangeForSection, entityNames, insertPos, mode);
                                }
                            }
                            processed += 1;
                            progress.report({
                                message: `Processed ${processed}/${work.reduce((a, w) => a + w.regions.length, 0)} sections`,
                            });
                        }, token);
                    });
                    if (totalBeats === 0 && totalEntities === 0) {
                        vscode.window.showInformationMessage("No beats or entity updates generated.");
                    }
                    else {
                        vscode.window.setStatusBarMessage(`Inserted ${totalBeats} beat(s); updated ${totalEntities} entit(y/ies).`, 4000);
                    }
                }
                catch (err) {
                    console.log("🔥 premise.generateBeats command failed - timestamp:", Date.now());
                    vscode.window.showErrorMessage(`Generate beats failed: ${String(err)}`);
                }
                console.log("🔥 premise.generateBeats command finished - timestamp:", Date.now());
            });
            // Command: Update entity descriptions (file / uncommitted-file scopes)
            await registerCommandOnce(context, "premise.updateEntityDescriptions", async () => {
                const editor = vscode.window.activeTextEditor;
                if (!editor)
                    return;
                const doc = editor.document;
                if (doc.languageId !== "premise")
                    return;
                const scope = await pickScope();
                if (!scope)
                    return;
                const cfg = vscode.workspace.getConfiguration("premise");
                const provider = cfg.get("ai.provider", "openrouter");
                const model = cfg.get("ai.model", "openai/gpt-4o-mini");
                const endpoint = cfg.get("ai.endpoint", "https://openrouter.ai/api/v1/chat/completions");
                const apiKey = cfg.get("ai.apiKey") ||
                    process.env.OPENROUTER_API_KEY ||
                    "";
                if (provider !== "openrouter") {
                    vscode.window.showWarningMessage("Only OpenRouter is supported in this preview.");
                    return;
                }
                if (!apiKey) {
                    vscode.window.showErrorMessage("Set OpenRouter API key in settings (premise.ai.apiKey) or OPENROUTER_API_KEY.");
                    return;
                }
                const cfg2 = vscode.workspace.getConfiguration("premise");
                const chunkDefault = cfg2.get("ai.chunkingMode", "section");
                const chunkPick = await vscode.window.showQuickPick([
                    { label: "Chunk by sections (Cel/Scene/Act)", val: "section" },
                    { label: "Chunk by files", val: "file" },
                ], { placeHolder: "Select chunking granularity", ignoreFocusOut: true });
                const chunkingMode = chunkPick?.val || chunkDefault;
                const entityNames = await listEntityNamesForUri(doc.uri).catch(() => []);
                const structure = await collectStructureForUris([
                    doc.uri.toString(),
                ]).catch(() => ({ sections: [] }));
                // Determine targets by scope
                const targets = [];
                if (scope === "file" || scope === "uncommitted-file") {
                    const text = doc.getText();
                    const changed = scope === "uncommitted-file"
                        ? await getUncommittedChangedRangesForFile(doc.uri.fsPath)
                        : undefined;
                    targets.push({ uri: doc.uri, text, structure, changed });
                }
                else {
                    const rootPath = (await getStoryRootPathForUri(doc.uri)) ||
                        path.dirname(doc.uri.fsPath);
                    const uris = scope === "root"
                        ? await listPremFilesUnderRoot(rootPath)
                        : await listUncommittedPremFilesUnderRoot(rootPath);
                    if (uris.length === 0) {
                        vscode.window.showInformationMessage("No files to process in selected scope.");
                        return;
                    }
                    const allStruct = await collectStructureForUris(uris.map((u) => normalizeFileUri(u).toString()));
                    for (const u of uris) {
                        const nu = normalizeFileUri(u);
                        const d = (await safeOpenTextDocument(nu)) || doc;
                        const text = d.getText();
                        const per = {
                            sections: (allStruct?.sections || []).filter((s) => {
                                try {
                                    const suri = s.uri
                                        ? typeof s.uri === "string"
                                            ? normalizeFileUri(s.uri)
                                            : coerceToFileUri(s.uri)
                                        : undefined;
                                    const sfile = s.file
                                        ? typeof s.file === "string"
                                            ? normalizeFileUri(s.file)
                                            : coerceToFileUri(s.file)
                                        : undefined;
                                    const cand = suri || sfile;
                                    return cand ? cand.toString() === nu.toString() : false;
                                }
                                catch {
                                    return false;
                                }
                            }),
                        };
                        const changed = scope === "uncommitted-root"
                            ? await getUncommittedChangedRangesForFile(nu.fsPath)
                            : undefined;
                        targets.push({ uri: nu, text, structure: per, changed });
                    }
                }
                let totalEntities = 0;
                // Get entity update scope from configuration
                const cfg_ai = vscode.workspace.getConfiguration("premise.ai");
                const entityUpdateScope = cfg_ai.get("entityUpdateScope", "descriptions-only");
                const systemFile = getEntitySystemPrompt(entityUpdateScope, true);
                const schemaFile = getEntitySchemaPrompt(entityUpdateScope);
                const systemSection = getEntitySystemPrompt(entityUpdateScope, false);
                const schemaSection = getEntitySchemaPrompt(entityUpdateScope);
                for (const t of targets) {
                    const d = t.uri.toString() === doc.uri.toString()
                        ? doc
                        : (await safeOpenTextDocument(t.uri)) || doc;
                    if (chunkingMode === "file") {
                        const extra = t.changed && t.changed.length > 0
                            ? `\\nChangedRanges: ${JSON.stringify(t.changed)}`
                            : "";
                        const user = `File: ${t.uri.fsPath}\\nEntities: ${JSON.stringify(entityNames)}${extra}\\n---\\n${t.text}\\n---\\n${schemaFile}`;
                        const content = await openRouterChat({
                            endpoint,
                            apiKey,
                            model,
                            messages: [
                                { role: "system", content: systemFile },
                                { role: "user", content: user },
                            ],
                        });
                        const updates = extractEntityUpdates(content);
                        if (updates.length > 0) {
                            totalEntities += await applyEntityDescriptionUpdatesInDocument(d, updates);
                        }
                    }
                    else {
                        const regions = getSectionRegionsForStructure(t.structure, d);
                        const filteredRegions = t.changed && t.changed.length > 0
                            ? regions.filter((r) => t.changed.some((cr) => !(r.end < cr.startLine || r.start > cr.endLine)))
                            : regions;
                        for (const r of filteredRegions) {
                            const sectionText = getDocumentTextRange(d, r.start, r.end);
                            const extra = `\\nSection: ${r.kind}${r.title ? ` — ${r.title}` : ""} (lines ${r.start}-${r.end})`;
                            const user = `File: ${t.uri.fsPath}\\nEntities: ${JSON.stringify(entityNames)}${extra}\\n---\\n${sectionText}\\n---\\n${schemaSection}`;
                            const content = await openRouterChat({
                                endpoint,
                                apiKey,
                                model,
                                messages: [
                                    { role: "system", content: systemSection },
                                    { role: "user", content: user },
                                ],
                            });
                            const updates = extractEntityUpdates(content);
                            if (updates.length > 0) {
                                totalEntities +=
                                    await applyEntityDescriptionUpdatesInDocument(d, updates);
                            }
                        }
                    }
                }
                if (totalEntities === 0) {
                    vscode.window.showInformationMessage("No entity updates suggested.");
                }
                else {
                    vscode.window.setStatusBarMessage(`Updated ${totalEntities} entit(y/ies).`, 3000);
                }
            });
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
async function openRouterChat(params) {
    const body = JSON.stringify({
        model: params.model,
        messages: params.messages,
        temperature: 0.3,
        response_format: { type: "json_object" },
    });
    const url = new URL(params.endpoint);
    const options = {
        method: "POST",
        hostname: url.hostname,
        path: url.pathname + (url.search || ""),
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${params.apiKey}`,
            "HTTP-Referer": "https://github.com/davidlantrip/premise-grammar",
            "X-Title": "Premise VSCode Extension",
        },
    };
    const payload = await new Promise((resolve, reject) => {
        const req = https.request(options, (res) => {
            const chunks = [];
            res.on("data", (d) => chunks.push(d));
            res.on("end", () => resolve(Buffer.concat(chunks).toString("utf8")));
        });
        req.on("error", reject);
        req.write(body);
        req.end();
    });
    let json;
    try {
        json = JSON.parse(payload);
    }
    catch (e) {
        console.error("Failed to parse provider response:", payload);
        throw new Error(`Invalid JSON from provider: ${e}`);
    }
    // Debug logging to understand the response structure
    console.log("Provider response:", JSON.stringify(json, null, 2));
    // Check for error responses
    if (json?.error) {
        console.error("Provider returned error:", json.error);
        throw new Error(`Provider error: ${json.error.message || json.error.type || JSON.stringify(json.error)}`);
    }
    const content = json?.choices?.[0]?.message?.content;
    if (typeof content !== "string") {
        console.error("Unexpected response structure:", {
            hasChoices: !!json?.choices,
            choicesLength: json?.choices?.length,
            firstChoice: json?.choices?.[0],
            fullResponse: json,
        });
        throw new Error("Provider response missing content");
    }
    return content.trim();
}
async function pickScope() {
    const items = [
        { label: "Current section (where cursor is)", val: "current-section" },
        { label: "Current file", val: "file" },
        { label: "Uncommitted: current file", val: "uncommitted-file" },
        { label: "Story root (all .prem files)", val: "root" },
        { label: "Uncommitted: story root", val: "uncommitted-root" },
    ];
    const pick = await vscode.window.showQuickPick(items, {
        placeHolder: "Select scope",
    });
    return pick?.val;
}
async function pickBeatGenerationMode() {
    const cfg = vscode.workspace.getConfiguration("premise.ai");
    const defaultMode = cfg.get("beatGenerationMode", "add-new");
    const items = [
        {
            label: "Add New Beats",
            val: "add-new",
            detail: "Generate new beats without changing existing ones (default behavior)",
            picked: defaultMode === "add-new"
        },
        {
            label: "Update/Fix Beats",
            val: "update-fix",
            detail: "Analyze and improve existing beats based on current narrative",
            picked: defaultMode === "update-fix"
        },
        {
            label: "Recreate All Beats",
            val: "recreate-all",
            detail: "Replace all existing beats with completely new ones",
            picked: defaultMode === "recreate-all"
        },
    ];
    const pick = await vscode.window.showQuickPick(items, {
        placeHolder: "Select beat generation mode",
        matchOnDetail: true,
    });
    return pick?.val;
}
function getBeatSystemPrompt(mode, qualityLevel) {
    const basePrompt = `You are a story analyst creating beats for a Premise story. Beats are MAJOR STORY MILESTONES, not every detail.

IMPORTANT: Generate 3-8 beats maximum per section. Focus on KEY TURNING POINTS only.

For SHORT sections (< 500 words): 3-5 simple, direct beats
For MEDIUM sections (500-1500 words): 5-7 beats with more nuance
For LONG sections (> 1500 words): 6-8 comprehensive beats

WRONG (too many details): Every small action and description
RIGHT (key events only): Major character decisions, plot turns, revelations

Examples:
WRONG: "Mist clings to robes" + "Traces markings" + "Fingers tremble" (too granular)
RIGHT: "{Character} investigates ancient markings" (combines related actions)

NEVER copy text. Summarize ONLY the most important story events. Return ONLY strict JSON.`;
    switch (mode) {
        case "add-new":
            return `${basePrompt} Add ONLY major events not already covered. Maximum 5 new beats.`;
        case "update-fix":
            return `${basePrompt} Improve existing beats to better capture KEY story moments. Keep total under 8.`;
        case "recreate-all":
            return `${basePrompt} Create 3-8 beats covering ONLY the most significant story events.`;
        default:
            return basePrompt;
    }
}
function getBeatSchemaPrompt(mode, qualityLevel) {
    const lengthConstraint = qualityLevel === "concise" ? "10-50" :
        qualityLevel === "detailed" ? "30-80" :
            "50-120";
    const baseSchema = `Schema: { "beats": [ string, string, ... ] }

CRITICAL RULES:
1. Generate 3-8 beats maximum - focus on SIGNIFICANCE not quantity
2. Each beat must be ${lengthConstraint} chars
3. Combine related minor actions into single important beats
4. Ask yourself: "Is this a turning point, decision, or revelation?"
5. Use format: "{Character} does action" or "Major event happens"

Examples of SIGNIFICANT beats (GOOD):
   - "{Maya Chen} discovers forbidden knowledge"
   - "{Character} makes dangerous choice"
   - "Ancient power awakens"
   - "Alliance forms between enemies"

Examples of INSIGNIFICANT details (AVOID):
   - "Mist appears" (atmospheric detail)
   - "Character walks somewhere" (unless crucial)
   - "Lantern flickers" (minor description)

Only include beats that would matter to someone outlining the key story moments.`;
    switch (mode) {
        case "add-new":
            return `${baseSchema}\\nAdd ONLY major events not covered. Maximum 3-5 new beats total.`;
        case "update-fix":
            return `${baseSchema}\\nImprove to focus on KEY moments. Final total should be 3-8 beats maximum.`;
        case "recreate-all":
            return `${baseSchema}\\nCreate 3-8 beats covering ONLY the most crucial story developments.`;
        default:
            return baseSchema;
    }
}
async function applyBeatsToSection(editor, beats, regionStart, regionEnd, entityNames, insertPosition = "append", mode = "add-new", sectionInfo = {}, showPreview = true) {
    const doc = editor.document;
    // Collect existing beats in region
    const existingSet = new Set();
    const existingBeats = [];
    let firstBeatLine;
    let lastBeatLine;
    for (let i = regionStart; i <= regionEnd && i < doc.lineCount; i++) {
        const lineText = doc.lineAt(i).text;
        if (lineText.trimStart().startsWith("///")) {
            const beatText = lineText.replace(/^\s*\/\/\//, "").trim();
            const normalized = normalizeBeat(beatText);
            if (normalized) {
                existingSet.add(normalized);
                existingBeats.push(beatText);
            }
            if (firstBeatLine === undefined)
                firstBeatLine = i;
            lastBeatLine = i;
        }
    }
    const canon = Array.isArray(entityNames) ? new Set(entityNames) : undefined;
    // Filter and validate beats first
    const validatedBeats = beats
        .map((b) => normalizeBeat(b))
        .filter((b) => !!b)
        .filter((b) => {
        if (!canon)
            return true;
        const tokens = extractEntityTokens(b);
        return tokens.every((t) => canon.has(t));
    })
        .filter((b, idx, arr) => arr.indexOf(b) === idx);
    if (validatedBeats.length === 0)
        return;
    // Show preview if enabled
    if (showPreview) {
        const previewResult = await showBeatPreview(validatedBeats, mode, sectionInfo, existingBeats);
        if (previewResult === "cancel")
            return;
        if (previewResult === "skip")
            return;
        // "apply" and "apply-all" continue
    }
    // Mode-specific beat processing
    let filteredBeats;
    if (mode === "recreate-all") {
        // Replace all existing beats
        filteredBeats = validatedBeats;
        // Clear existing beats in the region
        if (firstBeatLine !== undefined && lastBeatLine !== undefined) {
            const edit = new vscode.WorkspaceEdit();
            const startPos = new vscode.Position(firstBeatLine, 0);
            const endPos = new vscode.Position(lastBeatLine + 1, 0);
            edit.delete(doc.uri, new vscode.Range(startPos, endPos));
            await vscode.workspace.applyEdit(edit);
            firstBeatLine = undefined;
            lastBeatLine = undefined;
        }
    }
    else if (mode === "update-fix") {
        // Include all beats (both improved and new)
        filteredBeats = validatedBeats;
        // Clear existing beats since we're replacing with improved versions
        if (firstBeatLine !== undefined && lastBeatLine !== undefined) {
            const edit = new vscode.WorkspaceEdit();
            const startPos = new vscode.Position(firstBeatLine, 0);
            const endPos = new vscode.Position(lastBeatLine + 1, 0);
            edit.delete(doc.uri, new vscode.Range(startPos, endPos));
            await vscode.workspace.applyEdit(edit);
            firstBeatLine = undefined;
            lastBeatLine = undefined;
        }
    }
    else {
        // "add-new" mode - only add non-duplicate beats
        filteredBeats = validatedBeats.filter((b) => !existingSet.has(b));
    }
    if (filteredBeats.length === 0)
        return;
    // Insert beats
    let needsHeader = firstBeatLine === undefined;
    let insertLine = regionStart;
    let insertText = "";
    if (needsHeader) {
        insertText = "///\n" + filteredBeats.join("\n") + "\n";
        insertLine = regionStart;
    }
    else {
        if (insertPosition === "append") {
            insertLine = lastBeatLine !== undefined ? lastBeatLine + 1 : regionStart;
        }
        else {
            insertLine = firstBeatLine !== undefined ? firstBeatLine : regionStart;
        }
        insertText = filteredBeats.join("\n") + "\n";
    }
    const pos = new vscode.Position(insertLine, 0);
    await editor.edit((builder) => {
        builder.insert(pos, insertText);
    });
}
async function showBeatPreview(beats, mode, sectionInfo, existingBeats = []) {
    const newBeatsText = beats.join("\n");
    const existingBeatsText = existingBeats.length > 0
        ? existingBeats.map(b => `/// ${b}`).join("\n")
        : "(No existing beats)";
    let previewText = "";
    if (mode === "add-new") {
        previewText = `**Adding ${beats.length} new beat(s):**\n\n${newBeatsText}`;
    }
    else if (mode === "update-fix") {
        previewText = `**Existing beats:**\n${existingBeatsText}\n\n**Updated/improved beats:**\n${newBeatsText}`;
    }
    else if (mode === "recreate-all") {
        previewText = `**Current beats:**\n${existingBeatsText}\n\n**Replacing with ${beats.length} new beat(s):**\n${newBeatsText}`;
    }
    const sectionTitle = sectionInfo.title ? ` (${sectionInfo.title})` : "";
    const message = `Apply ${mode} mode to ${sectionInfo.kind || "section"}${sectionTitle}?`;
    const choice = await vscode.window.showInformationMessage(message, {
        modal: true,
        detail: previewText
    }, "Apply", "Skip", "Apply All", "Cancel");
    switch (choice) {
        case "Apply": return "apply";
        case "Skip": return "skip";
        case "Apply All": return "apply-all";
        default: return "cancel";
    }
}
function getEntitySystemPrompt(updateScope, isFile) {
    const basePrompt = `You analyze Premise ${isFile ? "file" : "section"} and produce JSON updates to entity descriptions defined with @entity lines. Return ONLY strict JSON.`;
    switch (updateScope) {
        case "relationships":
            return `${basePrompt} Focus on character relationships, interactions, and how entities relate to each other. Update descriptions to reflect current story dynamics.`;
        case "comprehensive":
            return `${basePrompt} Provide comprehensive analysis including character development, relationships, story role, and any significant changes. Create detailed, rich descriptions.`;
        default: // "descriptions-only"
            return `${basePrompt} Focus on basic entity descriptions, keeping them concise and consistent with the story content.`;
    }
}
function getEntitySchemaPrompt(updateScope) {
    const baseSchema = "Schema: { entities: [ { name: string, description: string } ] }\\nRules: Only include entities already defined in the file. Use only provided entity names.";
    switch (updateScope) {
        case "relationships":
            return `${baseSchema} Include relationship dynamics and character interactions. Descriptions should reflect how entities relate to others in the story.`;
        case "comprehensive":
            return `${baseSchema} Provide detailed descriptions including character motivations, relationships, story significance, and development. Length can be 2-3 sentences for important entities.`;
        default: // "descriptions-only"
            return `${baseSchema} Keep descriptions concise and consistent with the content. Focus on essential characteristics and current story role.`;
    }
}
function findCurrentSection(structure, cursorLine) {
    if (!structure?.sections || !Array.isArray(structure.sections)) {
        console.log("❌ No sections in structure or not an array");
        return undefined;
    }
    console.log("🔍 Searching through", structure.sections.length, "sections:");
    let lastSectionBefore = undefined;
    // Find the section that contains the cursor line or the last section before cursor
    for (let i = 0; i < structure.sections.length; i++) {
        const section = structure.sections[i];
        const start = section?.range?.start?.line;
        const end = section?.range?.end?.line;
        console.log(`  Section ${i}:`, {
            start,
            end,
            cursorLine,
            contains: typeof start === "number" &&
                typeof end === "number" &&
                cursorLine >= start &&
                cursorLine <= end,
            section: section,
        });
        if (typeof start === "number" && typeof end === "number") {
            // If cursor is exactly in the section range
            if (cursorLine >= start && cursorLine <= end) {
                console.log("✅ Found exact matching section:", section);
                return section;
            }
            // Track the last section that starts before or at the cursor
            if (start <= cursorLine) {
                lastSectionBefore = section;
            }
        }
    }
    // If no exact match, use the last section before cursor (cursor is in content after section header)
    if (lastSectionBefore) {
        console.log("✅ Using last section before cursor:", lastSectionBefore);
        // Extend the section to include content up to cursor line
        const extendedSection = {
            ...lastSectionBefore,
            range: {
                ...lastSectionBefore.range,
                end: {
                    line: cursorLine + 10,
                    character: 0,
                },
            },
        };
        console.log("📝 Extended section range to include content:", extendedSection);
        return extendedSection;
    }
    console.log("❌ No section found for cursor line", cursorLine);
    return undefined;
}
function getSectionText(doc, section) {
    const start = section?.range?.start?.line || 0;
    const end = section?.range?.end?.line || doc.lineCount - 1;
    const startPos = new vscode.Position(start, 0);
    const endPos = new vscode.Position(Math.min(end, doc.lineCount - 1), 0);
    const range = new vscode.Range(startPos, endPos);
    return doc.getText(range);
}
async function getUncommittedChangedRangesForFile(absPath) {
    try {
        const cwd = path.dirname(absPath);
        // Use relative path for better rename handling; include rename detection
        const rel = path.relative(cwd, absPath);
        const out = cp.execSync(`git -C ${JSON.stringify(cwd)} diff -U0 -M -- ${JSON.stringify(rel)}`, { encoding: "utf8" });
        const ranges = [];
        const re = /\+\+(?:\s*)@@\s*-\d+(?:,\d+)?\s*\+(\d+)(?:,(\d+))?\s*@@/g;
        let m;
        while ((m = re.exec(out))) {
            const start = parseInt(m[1], 10);
            const count = m[2] ? parseInt(m[2], 10) : 1;
            const end = start + Math.max(count, 1) - 1;
            ranges.push({
                startLine: Math.max(start - 1, 0),
                endLine: Math.max(end - 1, 0),
            });
        }
        return ranges;
    }
    catch {
        return [];
    }
}
async function getStoryRootPathForUri(uri) {
    if (!client)
        return undefined;
    try {
        console.log("🐛 getStoryRootPathForUri - uri:", uri.toString());
        const res = await client.sendRequest("workspace/executeCommand", {
            command: "premise.getStoryRoot",
            arguments: [uri.toString()],
        });
        const root = res?.root;
        console.log("🐛 getStoryRootPathForUri - LSP returned root:", root);
        return typeof root === "string" ? root : undefined;
    }
    catch (err) {
        console.log("🐛 getStoryRootPathForUri - error:", err);
        return undefined;
    }
}
async function listPremFilesUnderRoot(rootPath) {
    const rootUri = vscode.Uri.file(rootPath);
    const pattern = new vscode.RelativePattern(rootUri, "**/*.prem");
    return vscode.workspace.findFiles(pattern);
}
function resolveGitTopLevel(startPath) {
    try {
        const out = cp.execSync(`git -C ${JSON.stringify(startPath)} rev-parse --show-toplevel`, { encoding: "utf8" });
        const top = out.trim();
        if (top && fs.existsSync(top))
            return top;
    }
    catch { }
    // Fallback: walk up looking for .git directory
    try {
        let cur = startPath;
        for (let i = 0; i < 10; i++) {
            const dotgit = path.join(cur, ".git");
            if (fs.existsSync(dotgit))
                return cur;
            const parent = path.dirname(cur);
            if (!parent || parent === cur)
                break;
            cur = parent;
        }
    }
    catch { }
    return undefined;
}
async function listUncommittedPremFilesUnderRoot(rootPath) {
    try {
        console.log("🐛 listUncommittedPremFilesUnderRoot - rootPath:", rootPath);
        // Resolve actual git top-level; fall back to provided rootPath
        const topLevel = resolveGitTopLevel(rootPath) || rootPath;
        console.log("🐛 listUncommittedPremFilesUnderRoot - topLevel:", topLevel);
        // Include renames and added files; names are printed relative to repo top-level
        const out = cp.execSync(`git -C ${JSON.stringify(topLevel)} diff --name-only --diff-filter=ACMR`, { encoding: "utf8" });
        console.log("🐛 listUncommittedPremFilesUnderRoot - git diff output:", out);
        const files = out
            .split(/\r?\n/)
            .map((s) => s.trim())
            .filter((s) => s.endsWith(".prem") && s.length > 0)
            .map((rel) => (path.isAbsolute(rel) ? rel : path.join(topLevel, rel)))
            // Keep only files within the requested story root
            .filter((abs) => abs === rootPath || abs.startsWith(rootPath + path.sep));
        console.log("🐛 listUncommittedPremFilesUnderRoot - files after processing:", files);
        // Deduplicate
        const set = new Set(files);
        const result = Array.from(set).map((p) => normalizeFileUri(vscode.Uri.file(p)));
        console.log("🐛 listUncommittedPremFilesUnderRoot - final URIs:", result.map(u => u.toString()));
        return result;
    }
    catch (err) {
        console.log("🐛 listUncommittedPremFilesUnderRoot - error:", err);
        return [];
    }
}
async function insertBeatsAnchoredIntoDocument(doc, beats, structure, changedRanges, entityNames, insertPosition = "append", mode = "add-new") {
    const headers = [];
    const secs = Array.isArray(structure?.sections)
        ? structure.sections
        : [];
    for (const s of secs) {
        const start = s?.range?.start?.line;
        if (typeof start === "number") {
            if (typeof s.cel === "string")
                headers.push({ kind: "cel", start });
            else if (typeof s.scene === "string")
                headers.push({ kind: "scene", start });
            else if (typeof s.act === "string")
                headers.push({ kind: "act", start });
        }
    }
    headers.sort((a, b) => a.start - b.start);
    const pickFrom = (kinds) => {
        const list = headers.filter((h) => kinds.includes(h.kind));
        if (list.length === 0)
            return undefined;
        if (!changedRanges || changedRanges.length === 0)
            return list[list.length - 1];
        const inChanged = list.filter((h) => changedRanges.some((r) => h.start >= r.startLine && h.start <= r.endLine));
        if (inChanged.length > 0)
            return inChanged[inChanged.length - 1];
        const maxChanged = Math.max(...changedRanges.map((r) => Math.max(r.startLine, r.endLine)));
        const before = list.filter((h) => h.start <= maxChanged);
        return before.length > 0
            ? before[before.length - 1]
            : list[list.length - 1];
    };
    const anchor = pickFrom(["cel"]) || pickFrom(["scene"]) || pickFrom(["act"]);
    if (!anchor) {
        const last = doc.lineAt(doc.lineCount - 1).range.end;
        const canon = Array.isArray(entityNames) ? new Set(entityNames) : undefined;
        const filteredBeats = beats
            .map((b) => normalizeBeat(b))
            .filter((b) => !!b)
            .filter((b) => {
            if (!canon)
                return true;
            const tokens = extractEntityTokens(b);
            return tokens.every((t) => canon.has(t));
        })
            .filter((b, idx, arr) => arr.indexOf(b) === idx);
        if (filteredBeats.length === 0)
            return;
        const text = "\n" + filteredBeats.join("\n") + "\n";
        const edit = new vscode.WorkspaceEdit();
        edit.insert(doc.uri, last, text);
        await vscode.workspace.applyEdit(edit);
        return;
    }
    const headersSorted = headers;
    const idx = headersSorted.indexOf(anchor);
    const next = idx >= 0 && idx + 1 < headersSorted.length
        ? headersSorted[idx + 1]
        : undefined;
    const regionStart = anchor.start + 1;
    const regionEnd = next
        ? Math.max(next.start - 1, regionStart)
        : doc.lineCount - 1;
    // Use the new helper function for mode-specific beat processing
    // Convert to editor-like interface for the helper function
    const editor = await vscode.window.showTextDocument(doc);
    // Get section info for preview
    const sectionInfo = { title: "Document Section", kind: "section" };
    const cfg = vscode.workspace.getConfiguration("premise.ai");
    const enablePreview = cfg.get("enablePreviewMode", true);
    await applyBeatsToSection(editor, beats, regionStart, regionEnd, entityNames, insertPosition, mode, sectionInfo, enablePreview);
}
exports.insertBeatsAnchoredIntoDocument = insertBeatsAnchoredIntoDocument;
function getSectionRegionsForStructure(structure, doc) {
    const secs = Array.isArray(structure?.sections)
        ? structure.sections
        : [];
    const headers = [];
    for (const s of secs) {
        const start = s?.range?.start?.line;
        if (typeof start === "number") {
            if (typeof s.cel === "string")
                headers.push({ kind: "cel", title: s.cel, start });
            else if (typeof s.scene === "string")
                headers.push({ kind: "scene", title: s.scene, start });
            else if (typeof s.act === "string")
                headers.push({ kind: "act", title: s.act, start });
        }
    }
    headers.sort((a, b) => a.start - b.start);
    const regions = [];
    for (let i = 0; i < headers.length; i++) {
        const cur = headers[i];
        const next = i + 1 < headers.length ? headers[i + 1] : undefined;
        const start = cur.start + 1;
        const end = next ? Math.max(next.start - 1, start) : doc.lineCount - 1;
        regions.push({ kind: cur.kind, title: cur.title, start, end });
    }
    return regions;
}
exports.getSectionRegionsForStructure = getSectionRegionsForStructure;
function getDocumentTextRange(doc, startLine, endLine) {
    const startPos = new vscode.Position(Math.max(0, startLine), 0);
    const endPos = new vscode.Position(Math.min(doc.lineCount - 1, endLine), doc.lineAt(Math.min(doc.lineCount - 1, endLine)).range.end.character);
    return doc.getText(new vscode.Range(startPos, endPos));
}
async function applyEntityDescriptionUpdatesInDocument(doc, updates) {
    const text = doc.getText();
    const lines = text.split(/\r?\n/);
    const map = new Map();
    for (const u of updates)
        map.set(u.name, u.description);
    let edits = [];
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        const m = line.match(/^@(\w+)\s+([^:]+):\s*(.*)$/);
        if (m) {
            const entityName = m[2].trim();
            if (map.has(entityName)) {
                const newLine = `@${m[1]} ${entityName}: ${map.get(entityName)}`;
                const range = new vscode.Range(new vscode.Position(i, 0), new vscode.Position(i, line.length));
                edits.push({ range, newText: newLine });
            }
        }
    }
    if (edits.length === 0)
        return 0;
    const we = new vscode.WorkspaceEdit();
    for (const e of edits)
        we.replace(doc.uri, e.range, e.newText);
    await vscode.workspace.applyEdit(we);
    return edits.length;
}
async function listEntityNamesForUri(uri) {
    if (!client)
        return [];
    try {
        const res = await client.sendRequest("workspace/executeCommand", {
            command: "premise.listEntityNames",
            arguments: [uri.toString()],
        });
        return Array.isArray(res) ? res : [];
    }
    catch {
        return [];
    }
}
async function collectStructureForUris(uris) {
    if (!client)
        return { sections: [] };
    try {
        const res = await client.sendRequest("workspace/executeCommand", {
            command: "premise.collectStructure",
            arguments: [uris],
        });
        return res || { sections: [] };
    }
    catch {
        return { sections: [] };
    }
}
function extractBeats(content) {
    try {
        const parsed = JSON.parse(content);
        if (Array.isArray(parsed?.beats)) {
            return parsed.beats
                .map((b) => {
                // Handle both formats: plain string or object with beat property
                let beatText = "";
                if (typeof b === "string") {
                    // Direct string format (new simplified format)
                    beatText = b.trim();
                }
                else if (typeof b?.beat === "string") {
                    // Object format with beat property (old format)
                    beatText = b.beat.trim();
                }
                if (beatText) {
                    // Remove /// prefix if AI included it
                    beatText = beatText.replace(/^(\/\/\/\s*)+/, "");
                    console.log("🔧 Processed beat:", JSON.stringify(b), "->", JSON.stringify(beatText));
                    return beatText;
                }
                return "";
            })
                .filter((s) => !!s);
        }
    }
    catch (err) {
        console.log("❌ Failed to extract beats:", err);
    }
    return [];
}
function normalizeBeat(text) {
    return String(text || "")
        .trim()
        .replace(/\s+/g, " ");
}
function extractEntityTokens(beat) {
    const out = [];
    const re = /\{([^}]+)\}/g;
    let m;
    while ((m = re.exec(beat)) !== null) {
        const name = (m[1] || "").trim();
        if (name)
            out.push(name);
    }
    return out;
}
function getBeatInsertPosition() {
    const cfg = vscode.workspace.getConfiguration("premise.ai");
    const pos = cfg.get("beatInsertPosition", "append");
    return pos === "prepend" ? "prepend" : "append";
}
async function insertBeatsAtEnd(editor, beats) {
    const e = editor;
    const doc = e.document;
    const lastLine = doc.lineAt(doc.lineCount - 1).range.end;
    const insertText = "\n" + beats.join("\n") + "\n";
    await e.edit((builder) => {
        builder.insert(lastLine, insertText);
    });
}
async function insertBeatsAnchored(editor, beats, structure, changedRanges, entityNames, insertPosition = "append", mode = "add-new") {
    const doc = editor.document;
    const headers = [];
    const secs = Array.isArray(structure?.sections)
        ? structure.sections
        : [];
    for (const s of secs) {
        const start = s?.range?.start?.line;
        if (typeof start === "number") {
            if (typeof s.cel === "string")
                headers.push({ kind: "cel", start });
            else if (typeof s.scene === "string")
                headers.push({ kind: "scene", start });
            else if (typeof s.act === "string")
                headers.push({ kind: "act", start });
        }
    }
    headers.sort((a, b) => a.start - b.start);
    // Pick anchor: prefer cel, else scene, else act. Prefer one intersecting changedRanges if provided.
    const pickFrom = (kinds) => {
        const list = headers.filter((h) => kinds.includes(h.kind));
        if (list.length === 0)
            return undefined;
        if (!changedRanges || changedRanges.length === 0)
            return list[list.length - 1];
        // Find the last header whose start lies within or before any changed range
        const inChanged = list.filter((h) => changedRanges.some((r) => h.start >= r.startLine && h.start <= r.endLine));
        if (inChanged.length > 0)
            return inChanged[inChanged.length - 1];
        const maxChanged = Math.max(...changedRanges.map((r) => Math.max(r.startLine, r.endLine)));
        const before = list.filter((h) => h.start <= maxChanged);
        return before.length > 0
            ? before[before.length - 1]
            : list[list.length - 1];
    };
    const anchor = pickFrom(["cel"]) || pickFrom(["scene"]) || pickFrom(["act"]);
    if (!anchor) {
        // No clear section: dedupe across entire doc and append at EOF
        const existing = new Set();
        for (let i = 0; i < doc.lineCount; i++) {
            const lineText = doc.lineAt(i).text;
            if (lineText.trimStart().startsWith("///")) {
                const norm = normalizeBeat(lineText.replace(/^\s*\/\/\//, "").trim());
                if (norm)
                    existing.add(norm);
            }
        }
        const canon = Array.isArray(entityNames) ? new Set(entityNames) : undefined;
        const filtered = beats
            .map((b) => normalizeBeat(b))
            .filter((b) => !!b)
            .filter((b) => {
            if (!canon)
                return true;
            const tokens = extractEntityTokens(b);
            return tokens.every((t) => canon.has(t));
        })
            .filter((b, idx, arr) => arr.indexOf(b) === idx)
            .filter((b) => !existing.has(b));
        if (filtered.length === 0)
            return;
        await insertBeatsAtEnd(editor, filtered);
        return;
    }
    // Determine section end: next header start - 1, or EOF
    const idx = headers.indexOf(anchor);
    const next = idx >= 0 && idx + 1 < headers.length ? headers[idx + 1] : undefined;
    const regionStart = anchor.start + 1;
    const regionEnd = next
        ? Math.max(next.start - 1, regionStart)
        : doc.lineCount - 1;
    // Collect existing beats in region and compute insertion line according to insertPosition
    const existingSet = new Set();
    let firstBeatLine;
    let lastBeatLine;
    for (let i = regionStart; i <= regionEnd; i++) {
        const lineText = doc.lineAt(i).text;
        if (lineText.trimStart().startsWith("///")) {
            const normalized = normalizeBeat(lineText.replace(/^\s*\/\/\//, "").trim());
            if (normalized)
                existingSet.add(normalized);
            if (firstBeatLine === undefined)
                firstBeatLine = i;
            lastBeatLine = i;
        }
    }
    const canon = Array.isArray(entityNames) ? new Set(entityNames) : undefined;
    const filteredBeats = beats
        .map((b) => normalizeBeat(b))
        .filter((b) => !!b)
        .filter((b) => {
        if (!canon)
            return true;
        const tokens = extractEntityTokens(b);
        return tokens.every((t) => canon.has(t));
    })
        .filter((b, idx, arr) => arr.indexOf(b) === idx)
        .filter((b) => !existingSet.has(b));
    if (filteredBeats.length === 0)
        return;
    // Check if we need to add a /// section header
    let needsHeader = firstBeatLine === undefined; // No existing beats in this section
    let insertLine = regionStart;
    let insertText = "";
    if (needsHeader) {
        // Add /// header before the beats
        insertText = "///\n" + filteredBeats.join("\n") + "\n";
        insertLine = regionStart;
    }
    else {
        // Insert beats after existing beats
        if (insertPosition === "append") {
            insertLine = lastBeatLine !== undefined ? lastBeatLine + 1 : regionStart;
        }
        else {
            insertLine = firstBeatLine !== undefined ? firstBeatLine : regionStart;
        }
        insertText = filteredBeats.join("\n") + "\n";
    }
    const pos = new vscode.Position(insertLine, 0);
    await editor.edit((builder) => {
        builder.insert(pos, insertText);
    });
}
exports.insertBeatsAnchored = insertBeatsAnchored;
function extractEntityUpdates(content) {
    try {
        const parsed = JSON.parse(content);
        if (Array.isArray(parsed?.entities)) {
            return parsed.entities
                .map((e) => ({
                name: String(e?.name || "").trim(),
                description: String(e?.description || "").trim(),
            }))
                .filter((e) => e.name && e.description);
        }
    }
    catch {
        // ignore
    }
    return [];
}
async function applyEntityDescriptionUpdatesInCurrentFile(editor, updates) {
    const doc = editor.document;
    const text = doc.getText();
    const lines = text.split(/\r?\n/);
    const map = new Map();
    for (const u of updates)
        map.set(u.name, u.description);
    let edits = [];
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        // Match entity lines like: @character Name: Description
        const m = line.match(/^@(\w+)\s+([^:]+):\s*(.*)$/);
        if (m) {
            const entityName = m[2].trim();
            if (map.has(entityName)) {
                const newLine = `@${m[1]} ${entityName}: ${map.get(entityName)}`;
                const range = new vscode.Range(new vscode.Position(i, 0), new vscode.Position(i, line.length));
                edits.push({ range, newText: newLine });
            }
        }
    }
    if (edits.length === 0)
        return 0;
    await editor.edit((builder) => {
        for (const e of edits)
            builder.replace(e.range, e.newText);
    });
    return edits.length;
}
//# sourceMappingURL=extension.js.map