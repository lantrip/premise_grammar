#!/bin/bash
# Test all Tree-sitter queries against the grammar
set -e

echo "🧪 Testing Cuneiform Grammar Queries..."
echo

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# First, build the grammar
echo "📦 Building grammar..."
./build.sh > /dev/null 2>&1 || {
    echo -e "${RED}Failed to build grammar${NC}"
    exit 1
}
echo -e "${GREEN}✓ Grammar built successfully${NC}"
echo

# Function to test a query file
test_query() {
    local query_file=$1
    local query_name=$(basename "$query_file" .scm)

    echo -n "Testing $query_name query... "

    # Try to compile the query
    if tree-sitter query "$query_file" tests/cases/01_entity_definitions.cune 2>/tmp/query_error.txt > /dev/null; then
        echo -e "${GREEN}PASSED${NC}"
        return 0
    else
        echo -e "${RED}FAILED${NC}"
        echo "  Error:"
        cat /tmp/query_error.txt | sed 's/^/    /'
        return 1
    fi
}

# Function to discover available node types
discover_nodes() {
    echo "🔍 Discovering available node types..."
    echo

    # Parse a comprehensive test file and extract node types
    echo "Parsing test file to discover nodes..."
    tree-sitter parse tests/cases/04_story_structure.cune 2>/dev/null | \
        grep -o '([a-z_]*' | \
        sed 's/(//' | \
        sort -u > /tmp/available_nodes.txt

    echo "Available node types found:"
    cat /tmp/available_nodes.txt | sed 's/^/  - /'
    echo
}

# Discover available nodes first
discover_nodes

# Test each query file
echo "📋 Testing query files:"
echo

FAILED_QUERIES=""
for query_file in queries/*.scm; do
    if [ -f "$query_file" ]; then
        if ! test_query "$query_file"; then
            FAILED_QUERIES="$FAILED_QUERIES $query_file"
        fi
    fi
done

echo
if [ -z "$FAILED_QUERIES" ]; then
    echo -e "🎉 ${GREEN}All queries passed!${NC}"
    exit 0
else
    echo -e "❌ ${RED}Some queries failed:${NC}"
    for query in $FAILED_QUERIES; do
        echo "  - $(basename $query)"
    done
    echo
    echo "Fix these queries based on the available node types listed above."
    exit 1
fi