import * as assert from "assert";
import * as vscode from "vscode";

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
    const mod = await import("../../extension");
    // Only "Hero" is allowed; beat referencing {Unknown} should be dropped
    await (mod as any).insertBeatsAnchored(
      editor,
      ["{Unknown} appears", "{Hero} does a thing"],
      structure,
      undefined,
      ["Hero"],
      "prepend"
    );
    const full = doc.getText().split(/\r?\n/);
    // Find section region start at line 3 (after headers), first beat should be at that line
    const beatLine = full[3] || "";
    assert.ok(beatLine.startsWith("/// "), "should insert a beat line");
    assert.ok(beatLine.includes("Hero"), "allowed entity should remain");
    assert.ok(
      !full.join("\n").includes("Unknown"),
      "unknown entity beat should be dropped"
    );
  });
});
