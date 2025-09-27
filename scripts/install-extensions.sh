#!/bin/bash
# Install Premise extensions to local editors

set -e

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Ensure we're in the grammar root
if [ ! -f "grammar.js" ]; then
    echo -e "${RED}❌ Error: Must run from grammar repository root${NC}"
    exit 1
fi

# Parse command line arguments
INSTALL_VSCODE=false
INSTALL_CURSOR=false
INSTALL_ZED=false

if [ $# -eq 0 ]; then
    # No arguments, install to all available editors
    INSTALL_VSCODE=true
    INSTALL_CURSOR=true
    INSTALL_ZED=true
else
    for arg in "$@"; do
        case $arg in
            vscode|code)
                INSTALL_VSCODE=true
                ;;
            cursor)
                INSTALL_CURSOR=true
                ;;
            zed)
                INSTALL_ZED=true
                ;;
            all)
                INSTALL_VSCODE=true
                INSTALL_CURSOR=true
                INSTALL_ZED=true
                ;;
            *)
                echo "Usage: $0 [vscode|cursor|zed|all]"
                echo "  No arguments installs to all available editors"
                exit 1
                ;;
        esac
    done
fi

echo -e "${BLUE}🚀 Installing Premise extensions...${NC}"

# Build and sync first
echo -e "${BLUE}📦 Building grammar...${NC}"
./build.sh > /dev/null 2>&1
echo -e "${GREEN}✅ Grammar built${NC}"

echo -e "${BLUE}🔄 Syncing to extensions...${NC}"
./scripts/sync-extensions.sh > /dev/null 2>&1
echo -e "${GREEN}✅ Extensions synced${NC}"

# Build Premise LSP server and bundle into VSCode extension (for dev/local install)
echo -e "${BLUE}🛠 Building Premise LSP server...${NC}"
cargo build -p premise-lsp > /dev/null 2>&1 || {
    echo -e "${RED}❌ Failed to build premise-lsp binary${NC}"
    exit 1
}

BIN_NAME="premise-lsp"
if [[ "$(uname -s)" == *"MINGW"* || "$(uname -s)" == *"MSYS"* || "$(uname -s)" == *"CYGWIN"* ]]; then
    BIN_NAME="premise-lsp.exe"
fi

BIN_PATH_DEBUG="premise-lsp/target/debug/$BIN_NAME"
BIN_PATH_RELEASE="premise-lsp/target/release/$BIN_NAME"
# Also check workspace-level target directory (Cargo workspace layout)
BIN_PATH_WS_DEBUG="target/debug/$BIN_NAME"
BIN_PATH_WS_RELEASE="target/release/$BIN_NAME"
if [ -f "$BIN_PATH_DEBUG" ]; then
    BIN_SRC="$BIN_PATH_DEBUG"
elif [ -f "$BIN_PATH_RELEASE" ]; then
    BIN_SRC="$BIN_PATH_RELEASE"
elif [ -f "$BIN_PATH_WS_DEBUG" ]; then
    BIN_SRC="$BIN_PATH_WS_DEBUG"
elif [ -f "$BIN_PATH_WS_RELEASE" ]; then
    BIN_SRC="$BIN_PATH_WS_RELEASE"
else
    echo -e "${RED}❌ Built binary not found in target directories${NC}"
    exit 1
fi

mkdir -p extensions/vscode/server
cp "$BIN_SRC" "extensions/vscode/server/$BIN_NAME"
chmod +x "extensions/vscode/server/$BIN_NAME" || true
echo -e "${GREEN}✅ Packaged LSP server into VSCode extension (server/$BIN_NAME)${NC}"

# Function to install VSCode/Cursor extension
install_vscode_extension() {
    local editor_cmd=$1
    local editor_name=$2

    if ! command -v "$editor_cmd" &> /dev/null; then
        echo -e "${YELLOW}⏭️  $editor_name not found, skipping${NC}"
        return
    fi

    echo -e "${BLUE}📘 Installing to $editor_name...${NC}"

    cd extensions/vscode

    # Install dependencies if needed
    if [ ! -d "node_modules" ]; then
        echo "   Installing dependencies..."
        npm install --silent > /dev/null 2>&1
    fi

    # Compile TypeScript
    echo "   Compiling extension..."
    npm run compile > /dev/null 2>&1

    # Package extension
    if ! command -v vsce &> /dev/null; then
        echo "   Installing vsce..."
        npm install -g @vscode/vsce --silent > /dev/null 2>&1
    fi

    echo "   Packaging extension..."
    rm -f *.vsix
    vsce package --allow-missing-repository > /dev/null 2>&1

    # Install extension
    VSIX_FILE=$(ls -t *.vsix | head -n1)
    if [[ -z "$VSIX_FILE" ]]; then
        echo -e "${RED}   ❌ Failed to create package${NC}"
        cd ../..
        return
    fi

    "$editor_cmd" --install-extension "$VSIX_FILE" > /dev/null 2>&1
    echo -e "${GREEN}   ✅ Installed to $editor_name${NC}"

    cd ../..
}

# Function to install Zed extension
install_zed_extension() {
    if ! command -v zed &> /dev/null; then
        echo -e "${YELLOW}⏭️  Zed not found, skipping${NC}"
        return
    fi

    echo -e "${BLUE}🦓 Installing to Zed...${NC}"
    echo -e "${YELLOW}   ⚠️  Open Zed and use Command Palette:${NC}"
    echo "      1. Press Cmd+Shift+P (Mac) or Ctrl+Shift+P"
    echo "      2. Type: 'zed: install dev extension'"
    echo "      3. Select: $(pwd)/extensions/zed"
    echo -e "${GREEN}   ✅ Zed extension ready for manual install${NC}"
}

# Install to selected editors
if [ "$INSTALL_VSCODE" = true ]; then
    install_vscode_extension "code" "VSCode"
fi

if [ "$INSTALL_CURSOR" = true ]; then
    install_vscode_extension "cursor" "Cursor"
fi

if [ "$INSTALL_ZED" = true ]; then
    install_zed_extension
fi

echo ""
echo -e "${GREEN}✨ Installation complete!${NC}"
echo ""
echo "To reload extensions:"
echo "  VSCode/Cursor: Cmd+Shift+P → 'Developer: Reload Window'"
echo "  Zed: Extensions auto-reload after install"