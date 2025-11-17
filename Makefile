SHELL := /bin/bash

.PHONY: build test validate-queries sync-extensions

# Build grammar and WASM
build:
	./build.sh

# Run tests
test:
	tree-sitter test

# Validate query files
validate-queries:
	./test_queries.sh

# Sync grammar artifacts to extensions
sync-extensions:
	./scripts/sync-extensions.sh

# Full development cycle
dev: build validate-queries sync-extensions





