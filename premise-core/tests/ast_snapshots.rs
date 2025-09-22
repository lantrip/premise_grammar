use std::fs;
use std::path::PathBuf;

use insta::assert_json_snapshot;

#[test]
fn snapshot_ast_for_cases() {
    let repo_root = PathBuf::from(env!("CARGO_MANIFEST_DIR")).parent().unwrap().to_path_buf();
    let cases_dir = repo_root.join("tests/cases");
    let entries = fs::read_dir(&cases_dir).expect("read cases");

    for entry in entries {
        let entry = entry.expect("dir entry");
        let path = entry.path();
        if path.extension().and_then(|s| s.to_str()) != Some("prem") {
            continue;
        }
        let name = path.file_stem().unwrap().to_string_lossy().to_string();
        let content = fs::read_to_string(&path).expect("read file");
        let mut parser = premise_core::Parser::new();
        let (_cst, diagnostics, ast) = parser.parse_str(&content);
        let value = serde_json::json!({
            "diagnostics": diagnostics,
            "ast": ast,
        });
        assert_json_snapshot!(name, value);
    }
}


