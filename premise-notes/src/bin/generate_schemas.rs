use std::env;
use std::fs;
use std::path::PathBuf;

fn main() {
    let out_dir = env::var("SCHEMAS_OUT_DIR")
        .ok()
        .map(PathBuf::from)
        .unwrap_or_else(|| {
            // Default to crate-local schemas/
            let mut p = PathBuf::from(env!("CARGO_MANIFEST_DIR"));
            p.push("schemas");
            p
        });
    fs::create_dir_all(&out_dir).expect("failed to create schemas directory");

    let entries = premise_notes::export_all();
    for (name, schema) in entries {
        let file = out_dir.join(format!("notes.{}.schema.json", name));
        let content = serde_json::to_string_pretty(&schema).expect("failed to serialize schema");
        fs::write(&file, content).expect("failed to write schema file");
        eprintln!("wrote {}", file.display());
    }
}
