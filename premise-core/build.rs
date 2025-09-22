use std::env;
use std::path::{Path, PathBuf};

fn main() {
    // Allow override for parser.c path
    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").expect("CARGO_MANIFEST_DIR"));

    let env_override = env::var("PREMISE_PARSER_C_PATH").ok().map(PathBuf::from);
    let (parser_c, include_dir, origin) = resolve_paths(&manifest_dir, env_override.as_deref());

    println!("cargo:rerun-if-changed={}", parser_c.display());
    // Compile the grammar's generated C against local headers and tree-sitter headers
    let mut build = cc::Build::new();
    build.file(&parser_c);
    build.include(&include_dir); // for "tree_sitter/parser.h" in repo

    // Also include the Rust tree-sitter crate headers to align ABI if needed
    if let Ok(ts_include) = env::var("DEP_TREE_SITTER_INCLUDE") {
        build.include(&ts_include);
        println!("cargo:rerun-if-env-changed=DEP_TREE_SITTER_INCLUDE");
        println!("cargo:warning=Using tree-sitter include path: {}", ts_include);
    }

    build.define("TREE_SITTER_BUILD", None);
    build.warnings(false);
    build.compile("tree-sitter-premise");

    // Helpful log
    println!(
        "cargo:warning=tree-sitter-premise C compiled from {}\n  parser: {}\n  include: {}",
        origin,
        parser_c.display(),
        include_dir.display()
    );
}

fn resolve_paths(manifest_dir: &Path, override_path: Option<&Path>) -> (PathBuf, PathBuf, &'static str) {
    if let Some(path) = override_path {
        let include_from_override = manifest_dir.join("vendor/tree-sitter/include/tree_sitter");
        return (path.to_pathbuf(), include_from_override, "ENV_OVERRIDE");
    }

    // Prefer vendored layout for isolation
    let vendored_parser = manifest_dir.join("vendor/tree-sitter-premise/src/parser.c");
    let vendored_include = manifest_dir.join("vendor/tree-sitter/include/tree_sitter");
    if vendored_parser.exists() {
        return (vendored_parser, vendored_include, "VENDORED");
    }

    // Fallback to monorepo root (not fully isolated; good for bootstrapping)
    let fallback_parser = manifest_dir.join("../src/parser.c");
    let fallback_include = manifest_dir.join("../src/tree_sitter");
    if fallback_parser.exists() {
        return (fallback_parser, fallback_include, "FALLBACK_REPO_ROOT");
    }

    panic!(
        "Could not locate parser.c. Place it under vendor/tree-sitter-premise/src/parser.c or set PREMISE_PARSER_C_PATH."
    );
}

trait ToPathBuf {
    fn to_pathbuf(&self) -> PathBuf;
}

impl ToPathBuf for &Path {
    fn to_pathbuf(&self) -> PathBuf { self.to_path_buf() }
}


