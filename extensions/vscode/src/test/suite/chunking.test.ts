import * as assert from "assert";
import * as vscode from "vscode";

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
    const mod = await import("../../extension");
    const regions =
      (mod as any).getSectionRegionsForStructure?.(fake, doc) || [];
    assert.ok(Array.isArray(regions) && regions.length > 0);
    for (const r of regions) {
      assert.ok(r.end >= r.start);
    }
  });
});
