SHELL := /bin/bash

.PHONY: help build test check clippy fmt lint clean setup
.PHONY: validate-queries sync-extensions install-extensions dev
.PHONY: parse test-rust test-grammar test-all
.PHONY: vscode-build vscode-install zed-install
.PHONY: build-spellcheck build-spellcheck-slim test-spellcheck
.PHONY: build-dict-webster1913 build-dict-wordnet

.DEFAULT_GOAL := help

##@ Help

help: ## Show this help message
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m<target>\033[0m\n"} /^[a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-20s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

##@ Grammar Development

build: ## Build grammar and WASM
	@./build.sh

validate-queries: ## Validate query files against grammar nodes
	@./test_queries.sh

parse: ## Parse a file (usage: make parse FILE=path/to/file.prem)
	@npx tree-sitter parse $(FILE)

##@ Rust Workspace

check: ## Check Rust code (fast compile check)
	@cargo check --workspace

test-rust: ## Run all Rust tests
	@cargo test --workspace

clippy: ## Run Rust linter
	@cargo clippy --workspace --all-targets

fmt: ## Format Rust code
	@cargo fmt --all

ci-lint: ## Run linter and formatter checks (CI-style)
	@echo "Checking code formatting..."
	@cargo fmt --all -- --check
	@echo "Running clippy..."
	@cargo clippy --workspace --all-targets -- -D warnings -A dead_code -A unused_imports
	@echo "✓ All checks passed"

##@ Testing

test-grammar: ## Run tree-sitter grammar tests
	@npx tree-sitter test

test-all: build validate-queries test-grammar test-rust ## Run all tests (grammar + Rust)
	@echo "✓ All tests passed"

test: test-all ## Alias for test-all

##@ Extensions

sync-extensions: ## Sync grammar artifacts to extensions
	@./scripts/sync-extensions.sh

vscode-build: ## Build VSCode extension
	@cd extensions/vscode && npm install && npm run compile

vscode-install: vscode-build ## Build and install VSCode extension
	@cd extensions/vscode && npx @vscode/vsce package && code --install-extension premise-*.vsix
	@echo "✓ VSCode extension installed. Reload window to activate."

zed-install: ## Install Zed extension (requires git push first)
	@./scripts/update-zed-rev.sh
	@echo "✓ Zed extension updated. Use 'Install Dev Extension' in Zed."

install-extensions: build sync-extensions vscode-install ## Build and install all extensions
	@echo ""
	@echo "Extensions installed. Reload editors to activate:"
	@echo "  VSCode: Cmd+Shift+P → 'Developer: Reload Window'"
	@echo "  Zed: Extensions auto-reload after install"

##@ Development Workflow

dev: build validate-queries sync-extensions ## Full dev cycle (build + validate + sync)
	@echo "✓ Development build complete"

watch: ## Watch for changes and rebuild (requires entr)
	@echo "Watching for changes... (Ctrl+C to stop)"
	@find grammar.js queries/ -type f | entr -c make dev

##@ CLI

cli-build: ## Build the premise CLI
	@cargo build --release -p premise-cli
	@echo "✓ CLI built: ./target/release/premise"

cli-install: cli-build ## Install premise CLI to ~/.cargo/bin
	@cargo install --path premise-cli
	@echo "✓ CLI installed to ~/.cargo/bin/premise"

##@ LSP

lsp-build: ## Build the LSP server
	@cargo build --release -p premise-lsp
	@echo "✓ LSP built: ./target/release/premise-lsp"

##@ Spellcheck WASM

build-spellcheck: ## Build spellcheck WASM module with thesaurus (default)
	@cd premise-spellcheck && wasm-pack build --target web --out-dir ../../frontend/src/wasm/premise-spellcheck
	@echo "✓ Spellcheck WASM built (with thesaurus) → frontend/src/wasm/premise-spellcheck/"

build-spellcheck-slim: ## Build spellcheck WASM without thesaurus (smaller binary)
	@cd premise-spellcheck && wasm-pack build --target web --out-dir ../../frontend/src/wasm/premise-spellcheck -- --no-default-features
	@echo "✓ Spellcheck WASM built (slim, no thesaurus) → frontend/src/wasm/premise-spellcheck/"

test-spellcheck: ## Run spellcheck unit tests
	@cargo test -p premise-spellcheck

##@ Dictionary Data

build-dict-webster1913: ## Build Webster's 1913 dictionary binary
	@cargo run --release -p premise-spellcheck --bin process-dictionary -- --source webster1913 --input $(INPUT) --output ../../frontend/public/assets/dict-webster1913.bin

build-dict-wordnet: ## Build English WordNet dictionary binary
	@cargo run --release -p premise-spellcheck --bin process-dictionary -- --source wordnet --input $(INPUT) --output ../../frontend/public/assets/dict-wordnet.bin

##@ Utilities

lint: clippy ## Alias for clippy

clean: ## Clean build artifacts
	@cargo clean
	@rm -f tree-sitter-premise.wasm parser.dylib
	@rm -rf node_modules
	@cd extensions/vscode && rm -rf node_modules out *.vsix
	@echo "✓ Cleaned"

setup: ## First-time project setup
	@echo "Setting up Premise Grammar development environment..."
	@echo ""
	@echo "[1/5] Checking dependencies..."
	@command -v cargo >/dev/null 2>&1 || { echo "❌ Rust not installed. Install from https://rustup.rs"; exit 1; }
	@command -v node >/dev/null 2>&1 || { echo "❌ Node.js not installed. Install from https://nodejs.org"; exit 1; }
	@command -v npm >/dev/null 2>&1 || { echo "❌ npm not installed"; exit 1; }
	@echo "✓ All dependencies found"
	@echo ""
	@echo "[2/5] Installing npm dependencies..."
	@npm install
	@echo ""
	@echo "[3/5] Building grammar..."
	@$(MAKE) build
	@echo ""
	@echo "[4/5] Validating queries..."
	@$(MAKE) validate-queries
	@echo ""
	@echo "[5/5] Building Rust workspace..."
	@cargo build --workspace
	@echo ""
	@echo "✓ Setup complete!"
	@echo ""
	@echo "Quick start:"
	@echo "  make dev              # Build and validate"
	@echo "  make test             # Run all tests"
	@echo "  make install-extensions  # Install editor extensions"
	@echo "  make help             # Show all targets"
