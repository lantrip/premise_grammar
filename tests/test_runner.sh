#!/bin/bash
set -e

# Premise Grammar Test Runner
# Tests grammar against various syntax patterns

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "🧪 Running Premise Grammar Tests..."
echo

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

run_test() {
    local test_file=$1
    local test_name=$(basename "$test_file" .prem)
    
    echo -n "Testing $test_name... "
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Parse the file and check for errors
    if tree-sitter parse "$test_file" > /tmp/parse_output 2>&1; then
        # Check if there are any ERROR nodes in the output
        if grep -q "ERROR" /tmp/parse_output; then
            echo -e "${RED}FAILED${NC} (contains ERROR nodes)"
            echo "  Error details:"
            grep "ERROR" /tmp/parse_output | sed 's/^/    /'
            FAILED_TESTS=$((FAILED_TESTS + 1))
        else
            echo -e "${GREEN}PASSED${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        fi
    else
        echo -e "${RED}FAILED${NC} (parse error)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# Test individual pattern files
echo "📋 Testing individual syntax patterns:"
for test_file in cases/*.prem; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

echo

# Test the main example file
echo "📋 Testing main example file:"
EXAMPLE_FILE="../../../examples/habitatable/world_with_inline_eras.prem"
if [ -f "$EXAMPLE_FILE" ]; then
    run_test "$EXAMPLE_FILE"
else
    echo "❌ Example file not found: $EXAMPLE_FILE"
fi

echo
echo "📊 Test Results:"
echo "  Total Tests: $TOTAL_TESTS"
echo -e "  Passed: ${GREEN}$PASSED_TESTS${NC}"
echo -e "  Failed: ${RED}$FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n🎉 ${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "\n❌ ${RED}$FAILED_TESTS test(s) failed${NC}"
    exit 1
fi