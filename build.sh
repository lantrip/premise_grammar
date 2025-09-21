#!/bin/bash
set -e

# Premise Grammar Build Script
# Builds the Tree-sitter WASM for use in VSCode extension

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "🔧 Building Premise Tree-sitter Grammar..."

# Check if tree-sitter CLI is installed
if ! command -v tree-sitter &> /dev/null; then
    echo "📦 Installing tree-sitter CLI..."
    npm install -g tree-sitter-cli
fi

# Generate parser from grammar.js
echo "🌳 Generating parser..."
tree-sitter generate

# Build native parser (for local CLI parsing/tests)
echo "🔨 Building native parser..."
tree-sitter build

# Build WASM
echo "🏗️  Building WASM..."
# Support both CLI syntaxes across versions
if tree-sitter build-wasm >/dev/null 2>&1; then
  tree-sitter build-wasm
else
  tree-sitter build --wasm
fi

# The WASM should be generated as tree-sitter-premise.wasm
if [ -f "tree-sitter-premise.wasm" ]; then
    echo "✅ Successfully built tree-sitter-premise.wasm"
    echo "   Size: $(ls -lh tree-sitter-premise.wasm | awk '{print $5}')"
else
    echo "❌ Failed to build WASM"
    exit 1
fi

echo ""
echo "🎉 Grammar build complete!"
echo "📄 WASM file: tree-sitter-premise.wasm"
echo ""
echo "Next steps:"
echo "  1. Test the grammar: tree-sitter test"
echo "  2. Build VSCode extension: cd ../vscode && ./build-install.sh"