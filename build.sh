#!/bin/bash
set -e

# Cuneiform Grammar Build Script
# Builds the Tree-sitter WASM for use in VSCode extension

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "🔧 Building Cuneiform Tree-sitter Grammar..."

# Check if tree-sitter CLI is installed
if ! command -v tree-sitter &> /dev/null; then
    echo "📦 Installing tree-sitter CLI..."
    npm install -g tree-sitter-cli
fi

# Generate parser from grammar.js
echo "🌳 Generating parser..."
tree-sitter generate

# Build WASM
echo "🏗️  Building WASM..."
tree-sitter build --wasm

# The WASM should be generated as tree-sitter-cuneiform.wasm
if [ -f "tree-sitter-cuneiform.wasm" ]; then
    echo "✅ Successfully built tree-sitter-cuneiform.wasm"
    echo "   Size: $(ls -lh tree-sitter-cuneiform.wasm | awk '{print $5}')"
else
    echo "❌ Failed to build WASM"
    exit 1
fi

echo ""
echo "🎉 Grammar build complete!"
echo "📄 WASM file: tree-sitter-cuneiform.wasm"
echo ""
echo "Next steps:"
echo "  1. Test the grammar: tree-sitter test"
echo "  2. Build VSCode extension: cd ../vscode && ./build-install.sh"