#!/usr/bin/env python3
"""
Scope Validation Script for Premise Grammar

This script validates that all semantic scopes defined in highlights.scm
correspond to actual nodes in the grammar and test files.
"""

import re
import subprocess
import sys
from pathlib import Path
from typing import Set, Dict, List, Tuple


class ScopeValidator:
    def __init__(self, repo_root: Path):
        self.repo_root = repo_root
        self.queries_dir = repo_root / "queries"
        self.tests_dir = repo_root / "tests"
        self.errors: List[str] = []
        self.warnings: List[str] = []

    def extract_scopes_from_highlights(self) -> Dict[str, Set[str]]:
        """Extract all @scope definitions from highlights.scm"""
        highlights_path = self.queries_dir / "highlights.scm"
        if not highlights_path.exists():
            self.errors.append(f"highlights.scm not found at {highlights_path}")
            return {}

        scopes = {}
        with open(highlights_path, "r") as f:
            content = f.read()

        # Extract scope definitions ONLY from Tree-sitter query context
        # Pattern: (node_name) @scope.name or "string" @scope.name
        # This avoids false matches from comments or other content
        scope_pattern = (
            r'(?:\([^)]+\)|"[^"]+")[ \t]+@([a-zA-Z0-9._]+(?:\.[a-zA-Z0-9._]+)*)'
        )

        for match in re.finditer(scope_pattern, content):
            scope = match.group(1)
            # Track line number for debugging
            line_num = content[: match.start()].count("\n") + 1
            if scope not in scopes:
                scopes[scope] = set()
            scopes[scope].add(line_num)

        return scopes

    def extract_node_types_from_grammar(self) -> Set[str]:
        """Parse grammar.js to find all defined node types"""
        grammar_path = self.repo_root / "grammar.js"
        if not grammar_path.exists():
            self.errors.append(f"grammar.js not found at {grammar_path}")
            return set()

        node_types = set()
        with open(grammar_path, "r") as f:
            content = f.read()

        # Extract node definitions from grammar.js
        # Look for patterns like: node_name: $ =>
        node_pattern = r"(\w+):\s*\$\s*=>"
        for match in re.finditer(node_pattern, content):
            node_types.add(match.group(1))

        return node_types

    def parse_test_file(self, test_file: Path) -> Set[str]:
        """Use tree-sitter to parse a test file and extract node types"""
        try:
            result = subprocess.run(
                ["tree-sitter", "parse", str(test_file)],
                capture_output=True,
                text=True,
                cwd=self.repo_root,
            )

            if result.returncode != 0:
                self.warnings.append(f"Failed to parse {test_file}: {result.stderr}")
                return set()

            # Extract node types from parse output
            node_types = set()
            for line in result.stdout.split("\n"):
                # Extract node types from parse tree output
                match = re.search(r"\(([a-z_]+)", line)
                if match:
                    node_types.add(match.group(1))

            return node_types

        except subprocess.CalledProcessError as e:
            self.warnings.append(f"Error parsing {test_file}: {e}")
            return set()

    def validate_scope_semantics(self, scopes: Dict[str, Set[int]]) -> Dict[str, str]:
        """Validate that scope names follow semantic conventions"""
        semantic_rules = {
            "comment": "Comments and documentation",
            "keyword": "Language keywords and directives",
            "markup": "Document structure and headings",
            "punctuation": "Delimiters and special characters",
            "variable": "Variables and identifiers",
            "entity": "Named entities (characters, locations)",
            "text": "Story content and narrative",
            "type": "Type definitions and blocks",
            "meta": "Metadata and properties",
            "error": "Error nodes",
        }

        scope_validation = {}
        for scope in scopes:
            parts = scope.split(".")
            if parts[0] in semantic_rules:
                scope_validation[scope] = "valid"
            else:
                scope_validation[scope] = f"Unknown semantic category: {parts[0]}"
                self.warnings.append(
                    f"Scope '{scope}' uses non-standard category '{parts[0]}'"
                )

        return scope_validation

    def check_scope_coverage(self) -> Tuple[Set[str], Set[str]]:
        """Check which node types have scope coverage"""
        # Get all node types from grammar
        grammar_nodes = self.extract_node_types_from_grammar()

        # Get all node types from test files
        test_nodes = set()
        for test_file in self.tests_dir.glob("**/*.cune"):
            test_nodes.update(self.parse_test_file(test_file))

        # Get scopes from highlights
        scopes = self.extract_scopes_from_highlights()

        # Extract node references from highlights.scm
        highlights_path = self.queries_dir / "highlights.scm"
        covered_nodes = set()
        if highlights_path.exists():
            with open(highlights_path, "r") as f:
                content = f.read()
                # Look for (node_name) patterns
                for match in re.finditer(r"\(([a-z_]+)\)", content):
                    covered_nodes.add(match.group(1))

        # Find uncovered nodes
        all_nodes = grammar_nodes | test_nodes
        uncovered = all_nodes - covered_nodes

        return covered_nodes, uncovered

    def generate_report(self):
        """Generate validation report"""
        print("🔍 Premise Grammar Scope Validation Report\n")
        print("=" * 60)

        # Extract and validate scopes
        scopes = self.extract_scopes_from_highlights()
        print(f"\n📋 Found {len(scopes)} scope definitions in highlights.scm")

        # Validate semantic naming
        scope_validation = self.validate_scope_semantics(scopes)
        valid_count = sum(1 for v in scope_validation.values() if v == "valid")
        print(f"✅ {valid_count}/{len(scopes)} scopes follow semantic conventions")

        # Check node coverage
        covered, uncovered = self.check_scope_coverage()
        print(f"\n📊 Node Coverage:")
        print(f"  ✅ Covered nodes: {len(covered)}")
        print(f"  ⚠️  Uncovered nodes: {len(uncovered)}")

        if uncovered:
            print("\n⚠️  Uncovered node types:")
            for node in sorted(uncovered)[:10]:  # Show first 10
                print(f"    - {node}")
            if len(uncovered) > 10:
                print(f"    ... and {len(uncovered) - 10} more")

        # Report errors and warnings
        if self.errors:
            print(f"\n❌ Errors ({len(self.errors)}):")
            for error in self.errors:
                print(f"  - {error}")

        if self.warnings:
            print(f"\n⚠️  Warnings ({len(self.warnings)}):")
            for warning in self.warnings[:5]:  # Show first 5 warnings
                print(f"  - {warning}")
            if len(self.warnings) > 5:
                print(f"  ... and {len(self.warnings) - 5} more warnings")

        # Exit code based on validation
        if self.errors:
            return 1
        elif len(uncovered) > 20:  # Too many uncovered nodes
            print("\n⚠️  Consider adding scope coverage for more node types")
            return 1
        else:
            print("\n✅ Scope validation passed!")
            return 0


def main():
    repo_root = Path(__file__).parent.parent
    validator = ScopeValidator(repo_root)
    sys.exit(validator.generate_report())


if __name__ == "__main__":
    main()
