#!/bin/bash
# Quick development workflow - rebuild and reinstall extensions

set -e

# Colors for minimal output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}🔄 Rebuilding Cuneiform...${NC}"

# Build grammar
./build.sh > /dev/null 2>&1

# Sync to extensions
./scripts/sync-extensions.sh > /dev/null 2>&1

# Install to editors
./scripts/install-extensions.sh "$@"

echo -e "${GREEN}✅ Ready for testing!${NC}"