SHELL := /bin/bash

# Default STORY_ROOT; override when invoking: make run-server STORY_ROOT=/abs/path
STORY_ROOT ?= $(PWD)/tests/notes_corpus/prem

.PHONY: run-server dev-frontend openapi gen-openapi install-cargo-watch watch-server

run-server:
	STORY_ROOT=$(STORY_ROOT) cargo run -p premise-server

install-cargo-watch:
	cargo install cargo-watch || true

watch-server: install-cargo-watch
	STORY_ROOT=$(STORY_ROOT) cargo watch -x 'run -p premise-server'

dev-frontend:
	cd frontend && npm run dev

openapi:
	cd frontend && npm run openapi:gen





