package tree_sitter_cuneiform_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_cuneiform "github.com/lantrip/cuneiform_grammar/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_cuneiform.Language())
	if language == nil {
		t.Errorf("Error loading Cuneiform grammar")
	}
}
