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
suite("Chunking and Anchors", () => {
    test("Section regions derived from structure are ordered and non-empty", async () => {
        const doc = await vscode.workspace.openTextDocument({
            language: "premise",
            content: `Act: One\nScene: Opening\nCel: Intro\n/// A beat\n`,
        });
        const fake = {
            sections: [
                {
                    range: {
                        start: { line: 0, character: 0 },
                        end: { line: 0, character: 0 },
                    },
                    act: "One",
                },
                {
                    range: {
                        start: { line: 1, character: 0 },
                        end: { line: 1, character: 0 },
                    },
                    scene: "Opening",
                },
                {
                    range: {
                        start: { line: 2, character: 0 },
                        end: { line: 2, character: 0 },
                    },
                    cel: "Intro",
                },
            ],
        };
        const mod = await Promise.resolve().then(() => __importStar(require("../../extension")));
        const regions = mod.getSectionRegionsForStructure?.(fake, doc) || [];
        assert.ok(Array.isArray(regions) && regions.length > 0);
        for (const r of regions) {
            assert.ok(r.end >= r.start);
        }
    });
});
//# sourceMappingURL=chunking.test.js.map