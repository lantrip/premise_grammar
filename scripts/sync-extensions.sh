#!/bin/bash
# Sync grammar artifacts to extensions

set -e

echo "🔄 Syncing grammar artifacts to extensions..."

# Ensure we're in the grammar root
if [ ! -f "grammar.js" ]; then
    echo "❌ Error: Must run from grammar repository root"
    exit 1
fi

# Build grammar and WASM
echo "📦 Building grammar..."
./build.sh

# Sync to Zed extension
echo "🦓 Syncing to Zed extension..."
cp -r queries/* extensions/zed/languages/premise/
echo "   ✅ Copied query files to Zed"

# Sync to VSCode extension (WASM only; VSCode extension does not read query .scm files)
echo "📘 Syncing to VSCode extension..."
cp tree-sitter-premise.wasm extensions/vscode/
echo "   ✅ Copied WASM to VSCode"

# Copy example files for testing
echo "📋 Copying example files..."
cp examples/theming_showcase.prem extensions/zed/
cp examples/theming_showcase.prem extensions/vscode/
echo "   ✅ Copied example files"

echo ""
echo "✨ Extensions synchronized!"
echo ""
echo "Next steps:"
echo "  Zed: Use 'Install Dev Extension' in Zed command palette"
echo "  VSCode: cd extensions/vscode && npm run compile && code --install-extension ."