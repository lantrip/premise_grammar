#!/bin/bash

# Zed Extension Development Mode Script
# Switches between local development and production repository references

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
ZED_EXTENSION_DIR="$PROJECT_ROOT/extensions/zed"
EXTENSION_TOML="$ZED_EXTENSION_DIR/extension.toml"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

usage() {
    echo "Usage: $0 [dev|prod]"
    echo ""
    echo "  dev   - Switch to development mode (local file:// repository)"
    echo "  prod  - Switch to production mode (GitHub repository)"
    echo ""
    echo "Development mode allows testing local changes immediately."
    echo "Production mode uses the committed GitHub repository."
    exit 1
}

check_extension_dir() {
    if [ ! -f "$EXTENSION_TOML" ]; then
        echo -e "${RED}Error: Zed extension.toml not found at $EXTENSION_TOML${NC}"
        exit 1
    fi
}

clean_grammars() {
    echo -e "${YELLOW}🧹 Cleaning old grammar directories...${NC}"
    rm -rf "$ZED_EXTENSION_DIR/grammars/premise"
    echo -e "${GREEN}✅ Cleaned grammar cache${NC}"
}

switch_to_dev() {
    echo -e "${YELLOW}🔧 Switching to development mode...${NC}"

    # Update extension.toml to use local file path
    sed -i '' 's|repository = "https://github\.com/lantrip/premise_grammar"|repository = "file:///Users/davidlantrip/repos/premise_grammar"|g' "$EXTENSION_TOML"

    # Remove the rev line entirely for local development
    sed -i '' '/^rev = /d' "$EXTENSION_TOML"

    clean_grammars

    echo -e "${GREEN}✅ Switched to development mode${NC}"
    echo -e "${GREEN}📝 Extension now uses local repository${NC}"
    echo ""
    echo -e "${YELLOW}Next steps:${NC}"
    echo "1. In Zed: Cmd+Shift+P → 'Install Dev Extension'"
    echo "2. Select: $ZED_EXTENSION_DIR"
    echo "3. Test your changes immediately!"
}

switch_to_prod() {
    echo -e "${YELLOW}🚀 Switching to production mode...${NC}"

    # Get the current git commit
    cd "$PROJECT_ROOT"
    CURRENT_REV=$(git rev-parse HEAD)

    # Update extension.toml to use GitHub repository
    sed -i '' 's|repository = "file:///Users/davidlantrip/repos/premise_grammar"|repository = "https://github.com/lantrip/premise_grammar"|g' "$EXTENSION_TOML"

    # Add or update the rev line
    if grep -q "^rev = " "$EXTENSION_TOML"; then
        sed -i '' "s|^rev = .*|rev = \"$CURRENT_REV\"|g" "$EXTENSION_TOML"
    else
        # Add rev line after repository line
        sed -i '' "/^repository = \"https:\/\/github\.com\/lantrip\/premise_grammar\"/a\\
rev = \"$CURRENT_REV\"
" "$EXTENSION_TOML"
    fi

    clean_grammars

    echo -e "${GREEN}✅ Switched to production mode${NC}"
    echo -e "${GREEN}📝 Extension now uses GitHub repository at rev: $CURRENT_REV${NC}"
    echo ""
    echo -e "${YELLOW}Next steps:${NC}"
    echo "1. Commit and push your changes to GitHub"
    echo "2. Update Zed extension registry with this revision"
}

show_current_mode() {
    if grep -q "file://" "$EXTENSION_TOML"; then
        echo -e "${GREEN}Current mode: Development (local repository)${NC}"
    else
        echo -e "${YELLOW}Current mode: Production (GitHub repository)${NC}"
        if grep -q "^rev = " "$EXTENSION_TOML"; then
            REV=$(grep "^rev = " "$EXTENSION_TOML" | cut -d'"' -f2)
            echo -e "${YELLOW}Current revision: $REV${NC}"
        fi
    fi
}

# Main script logic
check_extension_dir

if [ $# -eq 0 ]; then
    show_current_mode
    echo ""
    usage
fi

case "$1" in
    dev|development)
        switch_to_dev
        ;;
    prod|production)
        switch_to_prod
        ;;
    status)
        show_current_mode
        ;;
    *)
        echo -e "${RED}Error: Unknown mode '$1'${NC}"
        usage
        ;;
esac