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
const assert = __importStar(require("assert"));
const vscode = __importStar(require("vscode"));
suite("Prepend insertion and entity validation", () => {
    test("Prepends beats and drops unknown entities", async () => {
        const doc = await vscode.workspace.openTextDocument({
            language: "premise",
            content: `Act: One\nScene: Opening\nCel: Intro\nSome text\n`,
        });
        const editor = await vscode.window.showTextDocument(doc);
        const structure = {
            sections: [
                {
                    act: "One",
                    range: {
                        start: { line: 0, character: 0 },
                        end: { line: 0, character: 0 },
                    },
                },
                {
                    scene: "Opening",
                    range: {
                        start: { line: 1, character: 0 },
                        end: { line: 1, character: 0 },
                    },
                },
                {
                    cel: "Intro",
                    range: {
                        start: { line: 2, character: 0 },
                        end: { line: 2, character: 0 },
                    },
                },
            ],
        };
        const mod = await Promise.resolve().then(() => __importStar(require("../../extension")));
        // Only "Hero" is allowed; beat referencing {Unknown} should be dropped
        await mod.insertBeatsAnchored(editor, ["{Unknown} appears", "{Hero} does a thing"], structure, undefined, ["Hero"], "prepend");
        const full = doc.getText().split(/\r?\n/);
        // Find section region start at line 3 (after headers), first beat should be at that line
        const beatLine = full[3] || "";
        assert.ok(beatLine.startsWith("/// "), "should insert a beat line");
        assert.ok(beatLine.includes("Hero"), "allowed entity should remain");
        assert.ok(!full.join("\n").includes("Unknown"), "unknown entity beat should be dropped");
    });
});
//# sourceMappingURL=prepend_validate.test.js.map