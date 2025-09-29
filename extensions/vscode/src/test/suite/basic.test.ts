import * as assert from "assert";
import * as vscode from "vscode";

suite("Basic Extension Tests", () => {
  test("Extension activates", async () => {
    const ext = vscode.extensions.getExtension("premise-lang.premise");
    assert.ok(ext, "Extension not found");
    await ext!.activate();
    assert.strictEqual(ext!.isActive, true);
  });
});
