import * as assert from "assert";
import * as vscode from "vscode";

suite("Anchored insertion and dedupe", () => {
  test("Inserts at end of section and dedupes existing beat", async () => {
    const doc = await vscode.workspace.openTextDocument({
      language: "premise",
      content: `Act: One\nScene: Opening\nCel: Intro\n/// Existing beat\nSome text\n`,
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
    const mod = await import("../../extension");
    await (mod as any).insertBeatsAnchored(
      editor,
      ["Existing beat", "New beat"],
      structure,
      undefined,
      ["Hero"],
      "append"
    );
    const full = doc.getText();
    const occurrences = (full.match(/^\/\/\/ Existing beat/m) || []).length;
    assert.strictEqual(occurrences, 1, "existing beat should be deduped");
    assert.ok(full.includes("/// New beat"), "should insert new beat");
  });
});
