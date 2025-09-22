use std::fs;
use std::path::PathBuf;

use insta::assert_json_snapshot;

#[test]
fn snapshot_validation_for_cases() {
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
        let report = premise_core::Parser::new().validate(&content);
        assert_json_snapshot!(name, report);
    }
}


