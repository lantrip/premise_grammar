#!/bin/bash
# Quick development workflow - rebuild and reinstall extensions

set -e

# Colors for minimal output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}🔄 Rebuilding Premise...${NC}"

# Build grammar
./build.sh > /dev/null 2>&1

# Sync to extensions
./scripts/sync-extensions.sh > /dev/null 2>&1

# Build and package LSP server into VSCode extension (dev path)
echo -e "${BLUE}🛠 Building LSP server...${NC}"
cargo build -p premise-lsp > /dev/null 2>&1 || true
BIN_NAME="premise-lsp"
if [[ "$(uname -s)" == *"MINGW"* || "$(uname -s)" == *"MSYS"* || "$(uname -s)" == *"CYGWIN"* ]]; then
    BIN_NAME="premise-lsp.exe"
fi
if [ -f "premise-lsp/target/debug/$BIN_NAME" ]; then
    mkdir -p extensions/vscode/server
    cp "premise-lsp/target/debug/$BIN_NAME" "extensions/vscode/server/$BIN_NAME"
    chmod +x "extensions/vscode/server/$BIN_NAME" || true
fi

# Install to editors
./scripts/install-extensions.sh "$@"

echo -e "${GREEN}✅ Ready for testing!${NC}"