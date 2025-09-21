#!/bin/bash

# Update Zed Extension Revision
# Updates the rev in extension.toml to current git commit

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
ZED_EXTENSION_DIR="$PROJECT_ROOT/extensions/zed"
EXTENSION_TOML="$ZED_EXTENSION_DIR/extension.toml"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

cd "$PROJECT_ROOT"

# Get the current git commit
CURRENT_REV=$(git rev-parse HEAD)

# Update the rev line in extension.toml
sed -i '' "s|^rev = .*|rev = \"$CURRENT_REV\"|g" "$EXTENSION_TOML"

# Clean old grammar cache
rm -rf "$ZED_EXTENSION_DIR/grammars/premise"

echo -e "${GREEN}✅ Updated Zed extension rev to: $CURRENT_REV${NC}"
echo -e "${YELLOW}📝 Make sure your changes are pushed to GitHub!${NC}"
echo ""
echo -e "${YELLOW}Next steps:${NC}"
echo "1. In Zed: Cmd+Shift+P → 'Install Dev Extension'"
echo "2. Select: $ZED_EXTENSION_DIR"