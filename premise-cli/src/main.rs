use std::fs;
use std::path::PathBuf;

use clap::{Args, Parser as ClapParser, Subcommand, ValueEnum};
use premise_notes::NotesSink;

use premise_core::{api, Parser};
use schemars::schema::RootSchema;
use clap::ValueEnum as ClapValueEnum;
use premise_core::notes::entity_discovery::{EntityCandidate as CoreEntityCandidate, EntityType as CoreEntityType};
use premise_core::notes::entity_discovery::{extract_entities_with_aliases, discover_entities_from_narrative, merge_aliases_with_candidates};

#[derive(Copy, Clone, Debug, ValueEnum)]
enum Format {
    Json,
    Pretty,
}

impl Format {
    fn is_json(&self) -> bool {
        matches!(self, Format::Json)
    }
}

#[derive(Copy, Clone, Debug, ValueEnum)]
enum Sink {
    /// Use the managed .premise-notes directory (default)
    Notes,
    /// Print to stdout (respects --format)
    Stdout,
    /// Append JSONL files to a directory (beats.jsonl, facts.jsonl, timeline.jsonl)
    JsonlDir,
    /// Write individual JSON files to a directory (beats/, facts/, timeline/)
    Dir,
}

#[derive(Copy, Clone, Debug, ValueEnum)]
enum InputMode {
    /// Parse Premise (.prem) using tree-sitter (default)
    Prem,
    /// Treat input as plain text
    Plain,
    /// Treat input as Markdown (treated like plain text initially)
    Markdown,
}


#[derive(Copy, Clone, Debug, ClapValueEnum)]
enum ImportanceOrigin {
    User,
    Ai,
    Heuristic,
}

#[derive(Args, Debug)]
struct GlobalOpts {
    /// Output format
    #[arg(long, value_enum, default_value_t = Format::Pretty)]
    format: Format,
}

#[derive(ClapParser)]
#[command(name = "premise", version, about = "Premise core CLI")]
struct Cli {
    #[command(flatten)]
    globals: GlobalOpts,
    #[command(subcommand)]
    command: Commands,
}

#[derive(Subcommand)]
enum Commands {
    /// Parse a Premise file and print the syntax tree
    Parse {
        /// Path to the .prem file
        file: PathBuf,
        /// Emit JSON instead of S-expression
        #[arg(long)]
        json: bool,
        /// Include AST in JSON output
        #[arg(long)]
        ast: bool,
        /// Include symbol table in JSON output
        #[arg(long)]
        symbols: bool,
        /// Include import analysis in JSON output
        #[arg(long)]
        imports: bool,
        /// Include resolved imports in JSON output (uses file path as base)
        #[arg(long)]
        resolved_imports: bool,
    },
    /// Validate a Premise file and emit issues
    Validate {
        /// Path to the .prem file
        file: PathBuf,
    },
    /// Analyze a Premise file and emit IR JSON
    Analyze {
        /// Path to the .prem file
        file: PathBuf,
        /// Extract notes during analysis
        #[arg(long)]
        extract_notes: bool,
    },
    /// Plan adapters deterministically
    Plan {
        /// Path to the .prem file
        file: PathBuf,
        /// Emit only the adapter graph JSON
        #[arg(long)]
        graph_only: bool,
    },
    /// Emit JSON Schemas for public output types
    Schema {
        /// Type to emit schema for (parse|validate|analyze|plan|notes|all)
        #[arg(long, default_value = "all")]
        r#type: String,
        /// Write to file instead of stdout
        #[arg(long)]
        out: Option<PathBuf>,
    },
    /// Story notes management
    #[command(subcommand)]
    Notes(NotesCommands),
    /// Adapter management
    #[command(subcommand)]
    Adapters(AdaptersCommands),
}

#[derive(Subcommand)]
enum NotesCommands {
    /// Initialize notes directory for a story
    Init {
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
        /// Optional story title
        #[arg(long)]
        title: Option<String>,
    },
    /// Export beats from a file to notes directory
    ExportBeats {
        /// Path to the .prem file
        file: PathBuf,
        /// Append to existing beats (default: true)
        #[arg(long, default_value = "true")]
        append: bool,
        /// Output sink (notes|stdout|jsonl-dir|dir)
        #[arg(long, value_enum, default_value_t = Sink::Notes)]
        sink: Sink,
        /// Output directory (used for jsonl-dir|dir)
        #[arg(long)]
        out_dir: Option<PathBuf>,
        /// Input mode: prem|plain|markdown
        #[arg(long, value_enum, default_value_t = InputMode::Prem)]
        input: InputMode,
        /// Read content from STDIN instead of file
        #[arg(long, default_value = "false")]
        stdin: bool,
        /// Aliases file (JSON: canonical -> [aliases]) for normalization in text modes
        #[arg(long)]
        aliases: Option<PathBuf>,
        /// Dry-run: print beats instead of writing
        #[arg(long, default_value = "false")]
        dry_run: bool,
        /// Generate deterministic IDs based on file/line/text
        #[arg(long, default_value = "false")]
        stable_ids: bool,
        /// Minimum importance threshold to include
        #[arg(long)]
        min_importance: Option<f64>,
    },
    /// Extract facts from a file to notes directory
    ExtractFacts {
        /// Path to the .prem file
        file: PathBuf,
        /// Output sink (notes|stdout|jsonl-dir|dir)
        #[arg(long, value_enum, default_value_t = Sink::Notes)]
        sink: Sink,
        /// Output directory (used for jsonl-dir|dir)
        #[arg(long)]
        out_dir: Option<PathBuf>,
        /// Input mode: prem|plain|markdown
        #[arg(long, value_enum, default_value_t = InputMode::Prem)]
        input: InputMode,
        /// Read content from STDIN instead of file
        #[arg(long, default_value = "false")]
        stdin: bool,
        /// Aliases file (JSON: canonical -> [aliases]) for normalization in text modes
        #[arg(long)]
        aliases: Option<PathBuf>,
        /// Dry-run: print facts instead of writing
        #[arg(long, default_value = "false")]
        dry_run: bool,
        /// Generate deterministic IDs based on evidence and content
        #[arg(long, default_value = "false")]
        stable_ids: bool,
        /// Minimum importance threshold to include
        #[arg(long)]
        min_importance: Option<f64>,
    },
    /// Extract timeline from a file
    ExtractTimeline {
        /// Path to the .prem file
        file: PathBuf,
        /// Output sink (notes|stdout|jsonl-dir|dir)
        #[arg(long, value_enum, default_value_t = Sink::Notes)]
        sink: Sink,
        /// Output directory (used for jsonl-dir|dir)
        #[arg(long)]
        out_dir: Option<PathBuf>,
        /// Input mode: prem|plain|markdown
        #[arg(long, value_enum, default_value_t = InputMode::Prem)]
        input: InputMode,
        /// Read content from STDIN instead of file
        #[arg(long, default_value = "false")]
        stdin: bool,
        /// Aliases file (JSON: canonical -> [aliases]) for normalization in text modes
        #[arg(long)]
        aliases: Option<PathBuf>,
        /// Dry-run: print timeline instead of writing
        #[arg(long, default_value = "false")]
        dry_run: bool,
        /// Generate deterministic IDs based on source and event
        #[arg(long, default_value = "false")]
        stable_ids: bool,
        /// Minimum importance threshold to include (not used for timeline yet)
        #[arg(long)]
        min_importance: Option<f64>,
    },
    /// Rebuild the notes index
    RebuildIndex {
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
    },
    /// Summarize unknown/uncertain entity references across notes
    SummarizeUncertain {
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
    },
    /// Merge alias updates from a JSON file into notes aliases
    MergeAliases {
        /// Path to alias updates file (JSON: canonical -> [aliases])
        #[arg(long)]
        aliases: PathBuf,
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
        /// Dry-run: show changes without writing
        #[arg(long, default_value = "false")]
        dry_run: bool,
    },
    /// Set or append an importance assessment to a record and recompute authoritative importance
    SetImportance {
        /// Record id (beat or fact)
        #[arg(long)]
        id: String,
        /// Importance score 0.0..1.0
        #[arg(long)]
        score: f64,
        /// Source of assessment: user|ai|heuristic
        #[arg(long, value_enum)]
        source: ImportanceOrigin,
        /// Optional method descriptor (e.g., "manual", "prompt:v1", "heuristic:v1")
        #[arg(long)]
        method: Option<String>,
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
    },
    /// Apply an alias delta JSON (canonical -> [aliases]) with conflict reporting
    ApplyAliasDelta {
        /// Delta JSON file path
        #[arg(long)]
        delta: PathBuf,
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
        /// Dry-run: show changes without writing
        #[arg(long, default_value = "false")]
        dry_run: bool,
    },
    /// Normalize existing notes against current aliases
    Normalize {
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
        /// Dry-run: print normalized output instead of writing
        #[arg(long, default_value = "false")]
        dry_run: bool,
    },
    /// Query notes by entity
    Query {
        /// Entity name to query
        #[arg(long)]
        entity: String,
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
    },
    /// Show notes directory status
    Status {
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
    },
    /// Discover entities from narrative text
    DiscoverEntities {
        /// Path to the .prem file
        file: PathBuf,
        /// Input mode: prem|plain|markdown
        #[arg(long, value_enum, default_value_t = InputMode::Prem)]
        input: InputMode,
        /// Read content from STDIN instead of file
        #[arg(long, default_value = "false")]
        stdin: bool,
        /// Optional aliases file (JSON: canonical -> [aliases]) for text modes
        #[arg(long)]
        aliases: Option<PathBuf>,
        /// Include uncertain references ({?Entity})
        #[arg(long, default_value = "true")]
        include_uncertain: bool,
        /// Minimum confidence threshold (0.0-1.0)
        #[arg(long, default_value = "0.5")]
        min_confidence: f64,
    },
    /// List all entities with their aliases
    ListEntities {
        /// Path to the .prem file or story root
        path: PathBuf,
    },
    /// Review extraction proposal and produce actions JSON (non-interactive)
    ReviewExtraction {
        /// Proposal JSON file path (or '-' for STDIN)
        #[arg(long)]
        proposal: String,
        /// Story root path (defaults to current directory)
        #[arg(long, default_value = ".")]
        path: PathBuf,
        /// Strategy: auto|approve-high-confidence|approve-known-entities|approve-new-only
        #[arg(long, default_value = "auto")]
        strategy: String,
        /// Minimum confidence threshold
        #[arg(long)]
        min_confidence: Option<f64>,
        /// Minimum importance threshold
        #[arg(long)]
        min_importance: Option<f64>,
        /// Dedupe key: text|id
        #[arg(long, default_value = "text")]
        dedupe_by: String,
        /// Output actions file (JSON)
        #[arg(long)]
        out_actions: Option<PathBuf>,
        /// Apply changes to notes immediately
        #[arg(long, default_value = "false")]
        apply: bool,
    },
    /// Apply review actions JSON to notes
    ApplyActions {
        /// Actions JSON file path
        #[arg(long)]
        actions: PathBuf,
        /// Story root path (defaults to current directory)
        #[arg(long, default_value = ".")]
        path: PathBuf,
        /// Dry-run: show changes without writing
        #[arg(long, default_value = "false")]
        dry_run: bool,
    },
}

#[derive(Subcommand)]
enum AdaptersCommands {
    /// List all available adapters
    List {
        /// Filter by domain
        #[arg(long)]
        domain: Option<String>,
    },
    /// Show details for a specific adapter
    Show {
        /// Adapter ID
        id: String,
    },
}

fn main() {
    let cli = Cli::parse();
    match cli.command {
        Commands::Parse { file, json, ast, symbols, imports, resolved_imports } => {
            let content = fs::read_to_string(&file).expect("failed to read file");
            let mut parser = Parser::new();
            let (cst, diagnostics, ast_value) = parser.parse_str(&content);

            let mut out = api::ParseOutput {
                cst: premise_core::cst::Cst { root_sexpr: cst.root_sexpr, range: cst.range },
                diagnostics,
                ast: if ast { ast_value } else { None },
                symbols: None,
                imports: None,
                resolved_imports: None,
            };
            if symbols {
                let analysis = premise_core::Parser::new().analyze_symbols(&content);
                out.symbols = Some(analysis);
            }
            if imports {
                let imports = premise_core::Parser::new().analyze_imports(&content);
                out.imports = Some(imports);
            }
            if resolved_imports {
                let mut p = premise_core::Parser::new();
                let res = p.resolve_imports_from_path(&file);
                out.resolved_imports = Some(res);
            }

            let emit_json = json || cli.globals.format.is_json();
            if emit_json {
                println!("{}", serde_json::to_string_pretty(&out).unwrap());
            } else {
                println!("{}", out.cst.root_sexpr);
            }
        }
        Commands::Validate { file } => {
            let content = fs::read_to_string(&file).expect("failed to read file");
            let mut parser = Parser::new();
            let report = parser.validate(&content);
            match cli.globals.format {
                Format::Json => println!(
                    "{}",
                    serde_json::to_string_pretty(&api::ValidateOutput { report }).unwrap()
                ),
                Format::Pretty => {
                    for issue in report.issues {
                        println!("{:?}: {}", issue.code, issue.message);
                    }
                }
            }
        }
        Commands::Analyze { file, extract_notes } => {
            let content = fs::read_to_string(&file).expect("failed to read file");
            let mut parser = Parser::new();
            let ir = parser.analyze_ir(&content);

            if extract_notes {
                let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                premise_core::notes::initialize_notes(story_root, None).expect("failed to initialize notes");

                let file_str = file.to_str().unwrap_or("unknown");
                let facts = premise_core::notes::extract_facts_from_ir(&ir, file_str);
                premise_core::notes::append_facts(story_root, &facts).expect("failed to append facts");

                let timeline = premise_core::notes::extract_timeline_from_ir(&ir, file_str);
                let timeline_path = premise_core::notes::get_notes_dir(story_root).join("timeline.jsonl");
                premise_core::notes::append_many_jsonl(&timeline_path, &timeline).expect("failed to append timeline");

                premise_core::notes::rebuild_index(story_root).expect("failed to rebuild index");
            }

            match cli.globals.format {
                Format::Json => println!("{}", serde_json::to_string_pretty(&api::AnalyzeOutput { ir }).unwrap()),
                Format::Pretty => println!("{}", serde_json::to_string_pretty(&api::AnalyzeOutput { ir }).unwrap()),
            }
        }
        Commands::Plan { file, graph_only } => {
            let content = fs::read_to_string(&file).expect("failed to read file");
            let mut parser = Parser::new();
            let plan = parser.plan_adapters(&content);
            if graph_only {
                let graph = &plan.graph;
                match cli.globals.format {
                    Format::Json => println!("{}", serde_json::to_string_pretty(&graph).unwrap()),
                    Format::Pretty => println!("{}", serde_json::to_string_pretty(&graph).unwrap()),
                }
            } else {
                match cli.globals.format {
                    Format::Json => println!("{}", serde_json::to_string_pretty(&plan).unwrap()),
                    Format::Pretty => println!("{}", serde_json::to_string_pretty(&plan).unwrap()),
                }
            }
        }
        Commands::Schema { r#type, out } => {
            let mut schemas: Vec<(String, RootSchema)> = Vec::new();
            match r#type.as_str() {
                "parse" => schemas.push(("ParseOutput".into(), schemars::schema_for!(api::ParseOutput))),
                "validate" => schemas.push(("ValidateOutput".into(), schemars::schema_for!(api::ValidateOutput))),
                "analyze" => schemas.push(("AnalyzeOutput".into(), schemars::schema_for!(api::AnalyzeOutput))),
                "plan" => { schemas.push(("PlanOutput".into(), schemars::schema_for!(api::PlanOutput))) }
                "notes" => {
                    schemas.push(("Beat".into(), schemars::schema_for!(premise_core::notes::Beat)));
                    schemas.push(("Fact".into(), schemars::schema_for!(premise_core::notes::Fact)));
                    schemas.push(("TimelineEvent".into(), schemars::schema_for!(premise_core::notes::TimelineEvent)));
                    schemas.push(("ConsistencyEntry".into(), schemars::schema_for!(premise_core::notes::ConsistencyEntry)));
                    schemas.push(("NotesIndex".into(), schemars::schema_for!(premise_core::notes::NotesIndex)));
                    schemas.push(("NotesMetadata".into(), schemars::schema_for!(premise_core::notes::NotesMetadata)));
                }
                _ => {
                    schemas.push(("ParseOutput".into(), schemars::schema_for!(api::ParseOutput)));
                    schemas.push(("ValidateOutput".into(), schemars::schema_for!(api::ValidateOutput)));
                    schemas.push(("AnalyzeOutput".into(), schemars::schema_for!(api::AnalyzeOutput)));
                    schemas.push(("PlanOutput".into(), schemars::schema_for!(api::PlanOutput)));
                    schemas.push(("Beat".into(), schemars::schema_for!(premise_core::notes::Beat)));
                    schemas.push(("Fact".into(), schemars::schema_for!(premise_core::notes::Fact)));
                    schemas.push(("TimelineEvent".into(), schemars::schema_for!(premise_core::notes::TimelineEvent)));
                    schemas.push(("ConsistencyEntry".into(), schemars::schema_for!(premise_core::notes::ConsistencyEntry)));
                    schemas.push(("NotesIndex".into(), schemars::schema_for!(premise_core::notes::NotesIndex)));
                    schemas.push(("NotesMetadata".into(), schemars::schema_for!(premise_core::notes::NotesMetadata)));
                }
            }

            let value = if schemas.len() == 1 { serde_json::to_value(&schemas[0].1).unwrap() } else { serde_json::json!(schemas.into_iter().collect::<std::collections::BTreeMap<_, _>>()) };
            if let Some(path) = out { std::fs::write(path, serde_json::to_string_pretty(&value).unwrap()).expect("failed to write schema file"); } else { println!("{}", serde_json::to_string_pretty(&value).unwrap()); }
        }
        Commands::Notes(notes_cmd) => {
            match notes_cmd {
                NotesCommands::Init { path, title } => {
                    match premise_core::notes::initialize_notes(&path, title) {
                        Ok(_) => println!("Initialized notes directory at {}", path.display()),
                        Err(e) => { eprintln!("Error: Failed to initialize notes directory at {}: {}", path.display(), e); std::process::exit(1); }
                    }
                }
                NotesCommands::ExportBeats { file, append: _, sink, out_dir, input, stdin, aliases, dry_run, stable_ids, min_importance } => {
                    let file_str = file.to_str().unwrap_or("unknown");
                    let content = if stdin { use std::io::Read; let mut buf = String::new(); std::io::stdin().read_to_string(&mut buf).expect("failed to read stdin"); buf } else { match fs::read_to_string(&file) { Ok(c) => c, Err(e) => { eprintln!("Error: Failed to read file {}: {}", file.display(), e); std::process::exit(1);} } };

                    let canonical: std::collections::HashSet<String>;
                    let reverse: std::collections::HashMap<String, String>;

                    let beats = match input {
                        InputMode::Prem => {
                            let mut parser = Parser::new();
                            let tree = match parser.internal.parse(&content, None) { Some(t) => t, None => { eprintln!("Error: Failed to parse file {}", file.display()); std::process::exit(1);} };
                            let root = tree.root_node();
                            let beats = premise_core::notes::extract_beats_from_tree(&root, &content, file_str);
                            let alias_map = extract_entities_with_aliases(&root, &content, file_str);
                            canonical = alias_map.keys().cloned().collect();
                            reverse = premise_core::notes::build_reverse_alias_map(&alias_map);
                            beats
                        }
                        InputMode::Plain | InputMode::Markdown => {
                            let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                            let alias_map = if let Some(path) = aliases { std::fs::read_to_string(&path).ok().and_then(|s| serde_json::from_str(&s).ok()).unwrap_or_default() } else { let (map, _) = premise_notes::io::load_aliases_with(story_root, &[]).unwrap_or((std::collections::HashMap::new(), premise_notes::io::AliasMergeReport{ added:0, conflicts: vec![] })); map };
                            canonical = alias_map.keys().cloned().collect();
                            reverse = premise_core::notes::build_reverse_alias_map(&alias_map);

                            let params = premise_notes::extract_pipeline::BeatParams{
                                content: &content,
                                file_label: file_str,
                                markdown_sections: matches!(input, InputMode::Markdown),
                                aliases: Some(&alias_map),
                                min_importance,
                                stable_ids
                            };
                            premise_notes::ExtractPipeline::beats_from_text(params)
                        }
                    };

                    let beats = premise_core::notes::normalize_beats(beats, &canonical, &reverse);

                    if stable_ids {
                        let mut beats = beats;
                        for b in &mut beats {
                            let line_str = b.line.map(|n| n.to_string()).unwrap_or_default();
                            let id = premise_notes::io::stable_id("beat_", &[&b.file, &line_str, &b.text]);
                            b.id = id;
                        }
                        if dry_run {
                            let pretty = matches!(cli.globals.format, Format::Pretty);
                            if pretty { println!("Beats ({}):", beats.len()); for b in &beats { println!("- {}", b.text); } } else { println!("{}", serde_json::to_string_pretty(&beats).unwrap()); }
                            return;
                        }
                        match sink {
                            Sink::Notes => {
                                let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                                if let Err(e) = premise_core::notes::initialize_notes(story_root, None) { eprintln!("Error: Failed to initialize notes at {}: {}", story_root.display(), e); std::process::exit(1); }
                                if let Err(e) = premise_core::notes::append_beats(story_root, &beats) { eprintln!("Error: Failed to save beats: {}", e); std::process::exit(1); }
                                if let Err(e) = premise_core::notes::rebuild_index(story_root) { eprintln!("Warning: Failed to rebuild index: {}", e); }
                                let mut total_uncertain: usize = 0; for b in &beats { let u = premise_core::notes::collect_uncertain_entities_from_text(&b.text); if !u.is_empty() { total_uncertain += 1; } }
                                if total_uncertain > 0 { eprintln!("Note: {} beat(s) contain uncertain entities (e.g., {{?Name}}). Consider running 'premise notes discover-entities'.", total_uncertain); }
                                println!("Exported {} beats from {}", beats.len(), file.display());
                            }
                            Sink::Stdout => { let pretty = matches!(cli.globals.format, Format::Pretty); let mut s = premise_core::notes::StdoutSink::new(pretty); if let Err(e) = s.emit_beats(&beats) { eprintln!("Error: Failed to emit beats: {}", e); std::process::exit(1); } }
                            Sink::JsonlDir => { let dir = out_dir.unwrap_or_else(|| PathBuf::from(".")); let mut s = match premise_core::notes::JsonlDirSink::new(&dir) { Ok(s) => s, Err(e) => { eprintln!("Error: Failed to prepare output dir {}: {}", dir.display(), e); std::process::exit(1);} }; if let Err(e) = s.emit_beats(&beats) { eprintln!("Error: Failed to write beats: {}", e); std::process::exit(1); } eprintln!("Wrote beats to {}/beats.jsonl", dir.display()); }
                            Sink::Dir => { let dir = out_dir.unwrap_or_else(|| PathBuf::from(".")); let mut s = match premise_core::notes::DirSink::new(&dir) { Ok(s) => s, Err(e) => { eprintln!("Error: Failed to prepare output dir {}: {}", dir.display(), e); std::process::exit(1);} }; if let Err(e) = s.emit_beats(&beats) { eprintln!("Error: Failed to write beats: {}", e); std::process::exit(1); } eprintln!("Wrote beats to {}", dir.display()); }
                        }
                    } else {
                        // No stable IDs; proceed with sink output directly
                        if dry_run {
                            let pretty = matches!(cli.globals.format, Format::Pretty);
                            if pretty { println!("Beats ({}):", beats.len()); for b in &beats { println!("- {}", b.text); } } else { println!("{}", serde_json::to_string_pretty(&beats).unwrap()); }
                            return;
                        }
                        match sink {
                            Sink::Notes => {
                                let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                                if let Err(e) = premise_core::notes::initialize_notes(story_root, None) {
                                    eprintln!("Error: Failed to initialize notes at {}: {}", story_root.display(), e);
                                    std::process::exit(1);
                                }
                                if let Err(e) = premise_core::notes::append_beats(story_root, &beats) {
                                    eprintln!("Error: Failed to save beats: {}", e);
                                    std::process::exit(1);
                                }
                                if let Err(e) = premise_core::notes::rebuild_index(story_root) {
                                    eprintln!("Warning: Failed to rebuild index: {}", e);
                                }
                                let mut total_uncertain: usize = 0;
                                for b in &beats {
                                    let u = premise_core::notes::collect_uncertain_entities_from_text(&b.text);
                                    if !u.is_empty() { total_uncertain += 1; }
                                }
                                if total_uncertain > 0 {
                                    eprintln!(
                                        "Note: {} beat(s) contain uncertain entities (e.g., {{?Name}}). Consider running 'premise notes discover-entities'.",
                                        total_uncertain
                                    );
                                }
                                println!("Exported {} beats from {}", beats.len(), file.display());
                            }
                            Sink::Stdout => {
                                let pretty = matches!(cli.globals.format, Format::Pretty);
                                let mut s = premise_core::notes::StdoutSink::new(pretty);
                                if let Err(e) = s.emit_beats(&beats) {
                                    eprintln!("Error: Failed to emit beats: {}", e);
                                    std::process::exit(1);
                                }
                            }
                            Sink::JsonlDir => {
                                let dir = out_dir.unwrap_or_else(|| PathBuf::from("."));
                                let mut s = match premise_core::notes::JsonlDirSink::new(&dir) {
                                    Ok(s) => s,
                                    Err(e) => {
                                        eprintln!("Error: Failed to prepare output dir {}: {}", dir.display(), e);
                                        std::process::exit(1);
                                    }
                                };
                                if let Err(e) = s.emit_beats(&beats) {
                                    eprintln!("Error: Failed to write beats: {}", e);
                                    std::process::exit(1);
                                }
                                eprintln!("Wrote beats to {}/beats.jsonl", dir.display());
                            }
                            Sink::Dir => {
                                let dir = out_dir.unwrap_or_else(|| PathBuf::from("."));
                                let mut s = match premise_core::notes::DirSink::new(&dir) {
                                    Ok(s) => s,
                                    Err(e) => {
                                        eprintln!("Error: Failed to prepare output dir {}: {}", dir.display(), e);
                                        std::process::exit(1);
                                    }
                                };
                                if let Err(e) = s.emit_beats(&beats) {
                                    eprintln!("Error: Failed to write beats: {}", e);
                                    std::process::exit(1);
                                }
                                eprintln!("Wrote beats to {}", dir.display());
                            }
                        }
                    }
                }
                NotesCommands::ExtractFacts { file, sink, out_dir, input, stdin, aliases, dry_run, stable_ids, min_importance } => {
                    let file_str = file.to_str().unwrap_or("unknown");
                    let content = if stdin { use std::io::Read; let mut buf = String::new(); std::io::stdin().read_to_string(&mut buf).expect("failed to read stdin"); buf } else { match fs::read_to_string(&file) { Ok(c) => c, Err(e) => { eprintln!("Error: Failed to read file {}: {}", file.display(), e); std::process::exit(1);} } };

                    let alias_map: std::collections::HashMap<String, Vec<String>>;

                    let facts = match input {
                        InputMode::Prem => {
                            let mut parser = Parser::new();
                            let tree = match parser.internal.parse(&content, None) { Some(t) => t, None => { eprintln!("Error: Failed to parse file {}", file.display()); std::process::exit(1);} };
                            let root = tree.root_node();
                            let facts = premise_core::notes::extract_all_facts_from_tree(&root, &content, file_str);
                            alias_map = extract_entities_with_aliases(&root, &content, file_str);
                            facts
                        }
                        InputMode::Plain | InputMode::Markdown => {
                            let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                            alias_map = if let Some(path) = aliases { std::fs::read_to_string(&path).ok().and_then(|s| serde_json::from_str(&s).ok()).unwrap_or_default() } else { let (map, _) = premise_notes::io::load_aliases_with(story_root, &[]).unwrap_or((std::collections::HashMap::new(), premise_notes::io::AliasMergeReport{ added:0, conflicts: vec![] })); map };
                            let params = premise_notes::extract_pipeline::FactParams{ content: &content, file_label: file_str, aliases: Some(&alias_map), min_importance, min_confidence: None, stable_ids };
                            premise_notes::ExtractPipeline::facts_from_text(params)
                        }
                    };

                    let reverse = premise_core::notes::build_reverse_alias_map(&alias_map);
                    let mut facts = premise_core::notes::normalize_facts(facts, &reverse);

                    if stable_ids { for f in &mut facts { let ev = f.evidence.first().cloned().unwrap_or_default(); let id = premise_notes::io::stable_id("fact_", &[&ev, &f.fact]); f.id = id; } }

                    for f in &mut facts {
                        if f.importance.is_none() {
                            let base = if matches!(f.fact_type, premise_notes::schema::FactType::Event | premise_notes::schema::FactType::Relationship) { 0.8 } else { 0.4 };
                            let conf = f.confidence.unwrap_or(0.6);
                            let score = (base + conf) / 2.0;
                            if score >= 0.5 {
                                f.importance = Some(premise_notes::schema::Importance { score, assessed_by: premise_notes::schema::ImportanceSource::Heuristic, method: Some("type_weight+confidence".to_string()), updated: chrono::Utc::now().to_rfc3339() });
                                if let Some(list) = &mut f.importance_assessments { list.push(f.importance.clone().unwrap()); } else { f.importance_assessments = Some(vec![f.importance.clone().unwrap()]); }
                            }
                        }
                    }

                    if let Some(threshold) = min_importance { facts.retain(|f| f.importance.as_ref().map(|i| i.score >= threshold).unwrap_or(false)); }

                    if dry_run { let pretty = matches!(cli.globals.format, Format::Pretty); if pretty { println!("Facts ({}):", facts.len()); for f in &facts { println!("- {}", f.fact); } } else { println!("{}", serde_json::to_string_pretty(&facts).unwrap()); } return; }

                    match sink {
                        Sink::Notes => {
                            let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                            if let Err(e) = premise_core::notes::initialize_notes(story_root, None) { eprintln!("Error: Failed to initialize notes at {}: {}", story_root.display(), e); std::process::exit(1); }
                            if let Err(e) = premise_core::notes::append_facts(story_root, &facts) { eprintln!("Error: Failed to save facts: {}", e); std::process::exit(1); }
                            if let Err(e) = premise_core::notes::rebuild_index(story_root) { eprintln!("Warning: Failed to rebuild index: {}", e); }
                            let canonical: std::collections::HashSet<String> = alias_map.keys().cloned().collect();
                            let unknowns = premise_core::notes::collect_unknown_fact_entities(&facts, &canonical);
                            if !unknowns.is_empty() { eprintln!("Note: {} unknown entity reference(s) found in facts: {}", unknowns.len(), unknowns.join(", ")); eprintln!("Consider running 'premise notes discover-entities'."); }
                            println!("Extracted {} facts from {}", facts.len(), file.display());
                        }
                        Sink::Stdout => { let pretty = matches!(cli.globals.format, Format::Pretty); let mut s = premise_core::notes::StdoutSink::new(pretty); if let Err(e) = s.emit_facts(&facts) { eprintln!("Error: Failed to emit facts: {}", e); std::process::exit(1); } }
                        Sink::JsonlDir => { let dir = out_dir.unwrap_or_else(|| PathBuf::from(".")); let mut s = match premise_core::notes::JsonlDirSink::new(&dir) { Ok(s) => s, Err(e) => { eprintln!("Error: Failed to prepare output dir {}: {}", dir.display(), e); std::process::exit(1);} }; if let Err(e) = s.emit_facts(&facts) { eprintln!("Error: Failed to write facts: {}", e); std::process::exit(1); } eprintln!("Wrote facts to {}/facts.jsonl", dir.display()); }
                        Sink::Dir => { let dir = out_dir.unwrap_or_else(|| PathBuf::from(".")); let mut s = match premise_core::notes::DirSink::new(&dir) { Ok(s) => s, Err(e) => { eprintln!("Error: Failed to prepare output dir {}: {}", dir.display(), e); std::process::exit(1);} }; if let Err(e) = s.emit_facts(&facts) { eprintln!("Error: Failed to write facts: {}", e); std::process::exit(1); } eprintln!("Wrote facts to {}", dir.display()); }
                    }
                }
                NotesCommands::ExtractTimeline { file, sink, out_dir, input, stdin, aliases: _, dry_run, stable_ids, .. } => {
                    let file_str = file.to_str().unwrap_or("unknown");
                    let content = if stdin { use std::io::Read; let mut buf = String::new(); std::io::stdin().read_to_string(&mut buf).expect("failed to read stdin"); buf } else { fs::read_to_string(&file).expect("failed to read file") };
                    let mut timeline = match input {
                        InputMode::Prem => { let mut parser = Parser::new(); let ir = parser.analyze_ir(&content); premise_core::notes::extract_timeline_from_ir(&ir, file_str) }
                        InputMode::Plain | InputMode::Markdown => { premise_notes::extract_text::extract_timeline_from_text(&content, file_str) }
                    };

                    if stable_ids { for ev in &mut timeline { let src = ev.source.first().cloned().unwrap_or_default(); let id = premise_notes::io::stable_id("timeline_", &[&src, &ev.event]); ev.id = id; } }

                    if dry_run { let pretty = matches!(cli.globals.format, Format::Pretty); if pretty { println!("Timeline events ({}):", timeline.len()); for e in &timeline { println!("- {}", e.event); } } else { println!("{}", serde_json::to_string_pretty(&timeline).unwrap()); } return; }

                    match sink {
                        Sink::Notes => { let story_root = file.parent().unwrap_or_else(|| std::path::Path::new(".")); premise_core::notes::initialize_notes(story_root, None).expect("failed to initialize notes"); let timeline_path = premise_core::notes::get_notes_dir(story_root).join("timeline.jsonl"); premise_core::notes::append_many_jsonl(&timeline_path, &timeline).expect("failed to append timeline"); premise_core::notes::rebuild_index(story_root).expect("failed to rebuild index"); let mut total_uncertain: usize = 0; for ev in &timeline { let u = premise_core::notes::collect_uncertain_entities_from_text(&ev.event); if !u.is_empty() { total_uncertain += 1; } } if total_uncertain > 0 { eprintln!("Note: {} timeline event(s) contain uncertain entities (e.g., {{?Name}}). Consider running 'premise notes discover-entities'.", total_uncertain); } println!("Extracted {} timeline events from {}", timeline.len(), file.display()); }
                        Sink::Stdout => { let pretty = matches!(cli.globals.format, Format::Pretty); let mut s = premise_core::notes::StdoutSink::new(pretty); if let Err(e) = s.emit_timeline(&timeline) { eprintln!("Error: Failed to emit timeline: {}", e); std::process::exit(1); } }
                        Sink::JsonlDir => { let dir = out_dir.unwrap_or_else(|| PathBuf::from(".")); let mut s = match premise_core::notes::JsonlDirSink::new(&dir) { Ok(s) => s, Err(e) => { eprintln!("Error: Failed to prepare output dir {}: {}", dir.display(), e); std::process::exit(1);} }; if let Err(e) = s.emit_timeline(&timeline) { eprintln!("Error: Failed to write timeline: {}", e); std::process::exit(1); } eprintln!("Wrote timeline to {}/timeline.jsonl", dir.display()); }
                        Sink::Dir => { let dir = out_dir.unwrap_or_else(|| PathBuf::from(".")); let mut s = match premise_core::notes::DirSink::new(&dir) { Ok(s) => s, Err(e) => { eprintln!("Error: Failed to prepare output dir {}: {}", dir.display(), e); std::process::exit(1);} }; if let Err(e) = s.emit_timeline(&timeline) { eprintln!("Error: Failed to write timeline: {}", e); std::process::exit(1); } eprintln!("Wrote timeline to {}", dir.display()); }
                    }
                }
                NotesCommands::Normalize { path, dry_run } => {
                    use std::collections::{HashMap, HashSet};

                    let beats = match premise_core::notes::read_beats(&path) { Ok(b) => b, Err(e) => { eprintln!("Error: Failed to read beats at {}: {}", path.display(), e); std::process::exit(1); } };
                    let facts = match premise_core::notes::read_facts(&path) { Ok(f) => f, Err(e) => { eprintln!("Error: Failed to read facts at {}: {}", path.display(), e); std::process::exit(1); } };

                    let mut files: HashSet<String> = HashSet::new();
                    for b in &beats { if !b.file.is_empty() { files.insert(b.file.clone()); } }
                    for f in &facts { for ev in &f.evidence { if let Some(fp) = ev.split(':').next() { if !fp.is_empty() { files.insert(fp.to_string()); } } } }

                    struct Mapping { canonical: HashSet<String>, reverse: HashMap<String, String> }
                    let mut per_file: HashMap<String, Mapping> = HashMap::new();

                    for fpath in files.iter() {
                        let candidate = std::path::PathBuf::from(fpath);
                        let full_path = if candidate.is_absolute() { candidate } else { path.join(&candidate) };
                        let content = match fs::read_to_string(&full_path) { Ok(c) => c, Err(e) => { eprintln!("Warning: Failed to read source file {}: {}", full_path.display(), e); continue; } };
                        let mut parser = Parser::new();
                        let tree = match parser.internal.parse(&content, None) { Some(t) => t, None => { eprintln!("Warning: Failed to parse source file {}", full_path.display()); continue; } };
                        let root = tree.root_node();
                        let alias_map = extract_entities_with_aliases(&root, &content, full_path.to_str().unwrap_or("unknown"));
                        let canonical: HashSet<String> = alias_map.keys().cloned().collect();
                        let reverse = premise_core::notes::build_reverse_alias_map(&alias_map);
                        per_file.insert(fpath.clone(), Mapping { canonical, reverse });
                    }

                    let mut global_canonical: HashSet<String> = HashSet::new();
                    let mut global_reverse: HashMap<String, String> = HashMap::new();
                    for m in per_file.values() { for c in &m.canonical { global_canonical.insert(c.clone()); } for (alias, canon) in &m.reverse { if let Some(existing) = global_reverse.get(alias) { if existing != canon { continue; } } global_reverse.insert(alias.clone(), canon.clone()); } }

                    let mut normalized_beats = Vec::with_capacity(beats.len());
                    let mut beats_uncertain_count: usize = 0;
                    for mut b in beats {
                        let (text, ents) = if let Some(m) = per_file.get(&b.file) { premise_core::notes::normalize_beat_text(&b.text, &m.canonical, &m.reverse) } else { premise_core::notes::normalize_beat_text(&b.text, &global_canonical, &global_reverse) };
                        if !premise_core::notes::collect_uncertain_entities_from_text(&text).is_empty() { beats_uncertain_count += 1; }
                        b.text = text;
                        b.entities = ents;
                        normalized_beats.push(b);
                    }

                    let normalized_facts = premise_core::notes::normalize_facts(facts, &global_reverse);

                    let notes_dir = premise_core::notes::get_notes_dir(&path);
                    let beats_path = notes_dir.join("beats.jsonl");
                    let facts_path = notes_dir.join("facts.jsonl");
                    if dry_run {
                        let output = serde_json::json!({ "beats": &normalized_beats, "facts": &normalized_facts });
                        println!("{}", serde_json::to_string_pretty(&output).unwrap());
                    } else {
                        if let Err(e) = premise_core::notes::write_jsonl(&beats_path, &normalized_beats) {
                            eprintln!("Error: Failed to write normalized beats: {}", e);
                            std::process::exit(1);
                        }
                        if let Err(e) = premise_core::notes::write_jsonl(&facts_path, &normalized_facts) {
                            eprintln!("Error: Failed to write normalized facts: {}", e);
                            std::process::exit(1);
                        }
                        if let Err(e) = premise_core::notes::rebuild_index(&path) {
                            eprintln!("Warning: Failed to rebuild index: {}", e);
                        }
                    }

                    eprintln!("Normalized {} beat(s) and {} fact(s) at {}", normalized_beats.len(), normalized_facts.len(), path.display());
                    if beats_uncertain_count > 0 { eprintln!("Note: {} beat(s) still contain uncertain entities (e.g., {{?Name}}). Consider running 'premise notes discover-entities'.", beats_uncertain_count); }
                    println!("Normalization complete.");
                }
                NotesCommands::RebuildIndex { path } => {
                    let index = match premise_core::notes::rebuild_index(&path) { Ok(idx) => idx, Err(e) => { eprintln!("Error: Failed to rebuild index at {}: {}", path.display(), e); std::process::exit(1);} };
                    match cli.globals.format { Format::Json => println!("{}", serde_json::to_string_pretty(&index).unwrap()), Format::Pretty => { println!("Index rebuilt successfully"); println!("  Beats: {}", index.stats.beats); println!("  Facts: {}", index.stats.facts); println!("  Timeline events: {}", index.stats.timeline_events); println!("  Consistency entries: {}", index.stats.consistency_entries); println!("  Entities tracked: {}", index.stats.entities_tracked); } }
                }
                NotesCommands::Query { entity, path } => {
                    let index = match premise_core::notes::read_index(&path) { Ok(Some(idx)) => idx, Ok(None) => { eprintln!("Error: Index not found at {}. Run 'premise notes rebuild-index' first.", path.display()); std::process::exit(1); } Err(e) => { eprintln!("Error: Failed to read index at {}: {}", path.display(), e); std::process::exit(1); } };

                    if let Some(record_ids) = index.entity_index.get(&entity) {
                        let beats = premise_core::notes::read_beats(&path).expect("failed to read beats");
                        let facts = premise_core::notes::read_facts(&path).expect("failed to read facts");
                        let mut results = Vec::new();
                        for id in record_ids {
                            if let Some(beat) = beats.iter().find(|b| &b.id == id) {
                                results.push(serde_json::to_value(beat).unwrap());
                            }
                            if let Some(fact) = facts.iter().find(|f| &f.id == id) {
                                results.push(serde_json::to_value(fact).unwrap());
                            }
                        }
                        println!("{}", serde_json::to_string_pretty(&results).unwrap());
                    } else {
                        println!("No records found for entity: {}", entity);
                    }
                }
                NotesCommands::SummarizeUncertain { path } => {
                    match premise_notes::orchestrate::summarize_uncertainties(&path) {
                        Ok((unknown_entities, files)) => {
                            match cli.globals.format {
                                Format::Json => { let out = serde_json::json!({ "unknown_entities": unknown_entities, "files": files }); println!("{}", serde_json::to_string_pretty(&out).unwrap()); }
                                Format::Pretty => {
                                    if unknown_entities.is_empty() { println!("No unknown or uncertain entities found."); } else { println!("Unknown/uncertain entities ({}):", unknown_entities.len()); for e in &unknown_entities { println!("  {}", e); } }
                                    if !files.is_empty() { println!("\nReferenced files:"); for f in &files { println!("  {}", f); } }
                                }
                            }
                        }
                        Err(e) => { eprintln!("Error: {}", e); std::process::exit(1); }
                    }
                }
                NotesCommands::MergeAliases { aliases, path, dry_run } => {
                    let incoming: std::collections::HashMap<String, Vec<String>> = match std::fs::read_to_string(&aliases).ok().and_then(|s| serde_json::from_str(&s).ok()) { Some(m) => m, None => { eprintln!("Error: Failed to read aliases file {}", aliases.display()); std::process::exit(1); } };
                    let mut base = match premise_notes::io::read_alias_map(&path) { Ok(m) => m, Err(e) => { eprintln!("Error: Failed to read existing aliases: {}", e); std::process::exit(1); } };
                    let report = premise_notes::io::merge_alias_maps(&mut base, &incoming);
                    if dry_run { println!("{}", serde_json::to_string_pretty(&serde_json::json!({ "added": report.added, "conflicts": report.conflicts })).unwrap()); } else if let Err(e) = premise_notes::io::write_alias_map(&path, &base) { eprintln!("Error: Failed to write aliases: {}", e); std::process::exit(1);} else { println!("Merged aliases. Added: {}. Conflicts: {}", report.added, report.conflicts.len()); }
                }
                NotesCommands::ApplyAliasDelta { delta, path, dry_run } => {
                    let incoming: std::collections::HashMap<String, Vec<String>> = match std::fs::read_to_string(&delta).ok().and_then(|s| serde_json::from_str(&s).ok()) { Some(m) => m, None => { eprintln!("Error: Failed to read delta file {}", delta.display()); std::process::exit(1); } };
                    let mut base = match premise_notes::io::read_alias_map(&path) { Ok(m) => m, Err(e) => { eprintln!("Error: Failed to read existing aliases: {}", e); std::process::exit(1); } };
                    let report = premise_notes::io::apply_alias_delta(&mut base, &incoming);
                    if dry_run { println!("{}", serde_json::to_string_pretty(&serde_json::json!({ "added": report.added, "conflicts": report.conflicts })).unwrap()); } else if let Err(e) = premise_notes::io::write_alias_map(&path, &base) { eprintln!("Error: Failed to write aliases: {}", e); std::process::exit(1);} else { println!("Applied alias delta. Added: {}. Conflicts: {}", report.added, report.conflicts.len()); }
                }
                NotesCommands::SetImportance { id, score, source, method, path } => {
                    let mut beats = match premise_core::notes::read_beats(&path) { Ok(b) => b, Err(e) => { eprintln!("Error: {}", e); std::process::exit(1); } };
                    let mut facts = match premise_core::notes::read_facts(&path) { Ok(f) => f, Err(e) => { eprintln!("Error: {}", e); std::process::exit(1); } };

                    let src = match source { ImportanceOrigin::User => premise_notes::schema::ImportanceSource::User, ImportanceOrigin::Ai => premise_notes::schema::ImportanceSource::Ai, ImportanceOrigin::Heuristic => premise_notes::schema::ImportanceSource::Heuristic };
                    let imp = premise_notes::schema::Importance { score, assessed_by: src, method, updated: chrono::Utc::now().to_rfc3339() };

                    let mut updated = false;
                    for b in &mut beats { if b.id == id { if let Some(list) = &mut b.importance_assessments { list.push(imp.clone()); } else { b.importance_assessments = Some(vec![imp.clone()]); }

                        if let Some(list) = &b.importance_assessments { b.importance = premise_notes::importance::choose_authoritative(list); }
                        updated = true; break; } }
                    if !updated { for f in &mut facts { if f.id == id { if let Some(list) = &mut f.importance_assessments { list.push(imp.clone()); } else { f.importance_assessments = Some(vec![imp.clone()]); }

                            if let Some(list) = &f.importance_assessments { f.importance = premise_notes::importance::choose_authoritative(list); }
                            updated = true; break; } } }

                    if !updated { eprintln!("Error: Record id '{}' not found in beats or facts", id); std::process::exit(1); }

                    let notes_dir = premise_core::notes::get_notes_dir(&path);
                    let beats_path = notes_dir.join("beats.jsonl");
                    let facts_path = notes_dir.join("facts.jsonl");
                    if let Err(e) = premise_core::notes::write_jsonl(&beats_path, &beats) { eprintln!("Error writing beats: {}", e); std::process::exit(1);} 
                    if let Err(e) = premise_core::notes::write_jsonl(&facts_path, &facts) { eprintln!("Error writing facts: {}", e); std::process::exit(1);} 
                    println!("Set importance for '{}' successfully.", id);
                }
                NotesCommands::DiscoverEntities { file, input, stdin, aliases, include_uncertain, min_confidence } => {
                    use std::collections::HashSet;

                    let file_str = file.to_str().unwrap_or("unknown");
                    let content = if stdin { use std::io::Read; let mut buf = String::new(); std::io::stdin().read_to_string(&mut buf).expect("failed to read stdin"); buf } else { match fs::read_to_string(&file) { Ok(c) => c, Err(e) => { eprintln!("Error: Failed to read file {}: {}", file.display(), e); std::process::exit(1);} } };

                    let alias_map: std::collections::HashMap<String, Vec<String>>;
                    let mut candidates: Vec<CoreEntityCandidate>;
                    match input {
                        InputMode::Prem => {
                            let mut parser = Parser::new();
                            let tree = match parser.internal.parse(&content, None) { Some(t) => t, None => { eprintln!("Error: Failed to parse file {}", file.display()); std::process::exit(1);} };
                            let root = tree.root_node();
                            alias_map = extract_entities_with_aliases(&root, &content, file_str);
                            let known_entities: HashSet<String> = alias_map.keys().cloned().collect();
                            candidates = discover_entities_from_narrative(&root, &content, file_str, &known_entities);
                        }
                        InputMode::Plain | InputMode::Markdown => {
                            if let Some(path) = aliases { alias_map = std::fs::read_to_string(&path).ok().and_then(|s| serde_json::from_str(&s).ok()).unwrap_or_default(); } else { let story_root = file.parent().unwrap_or_else(|| std::path::Path::new(".")); let (loaded, _report) = premise_notes::io::load_aliases_with(story_root, &[]).unwrap_or((std::collections::HashMap::new(), premise_notes::io::AliasMergeReport{ added:0, conflicts: vec![] })); alias_map = loaded; }
                            let known_entities: HashSet<String> = alias_map.keys().cloned().collect();
                            candidates = premise_notes::discovery::discover_entities_from_text(&content, &known_entities).into_iter().map(|c| CoreEntityCandidate{ canonical_name: c.canonical_name, entity_type: match c.entity_type.as_str() { "location" => CoreEntityType::Location, "object" => CoreEntityType::Object, "concept" => CoreEntityType::Concept, _ => CoreEntityType::Character }, aliases: c.aliases, description: c.description, evidence: c.evidence, confidence: c.confidence }).collect();
                        }
                    }

                    candidates.retain(|c| { c.confidence >= min_confidence && (include_uncertain || c.confidence >= 0.7) });

                    merge_aliases_with_candidates(&mut candidates, &alias_map);

                    let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                    let mut uncertain_refs: Vec<String> = Vec::new();
                    if let Ok(existing_beats) = premise_core::notes::read_beats(story_root) { for b in existing_beats { let mut u = premise_core::notes::collect_uncertain_entities_from_text(&b.text); uncertain_refs.append(&mut u); } }
                    uncertain_refs.sort();
                    uncertain_refs.dedup();

                    let delta = { let canon_candidates: Vec<premise_notes::discovery::EntityCandidate> = candidates.iter().map(|c| premise_notes::discovery::EntityCandidate{ canonical_name: c.canonical_name.clone(), entity_type: match c.entity_type { CoreEntityType::Location => premise_notes::discovery::EntityType::Location, CoreEntityType::Object => premise_notes::discovery::EntityType::Object, CoreEntityType::Concept => premise_notes::discovery::EntityType::Concept, _ => premise_notes::discovery::EntityType::Character }, aliases: c.aliases.clone(), description: c.description.clone(), evidence: c.evidence.clone(), confidence: c.confidence }).collect(); premise_notes::orchestrate::propose_alias_updates_api(&canon_candidates, &alias_map) };

                    match cli.globals.format {
                        Format::Json => { let output = serde_json::json!({ "known_entities": alias_map, "discovered": candidates.iter().map(|c| { serde_json::json!({ "canonical_name": c.canonical_name, "type": c.entity_type.as_str(), "aliases": c.aliases, "description": c.description, "evidence": c.evidence, "confidence": c.confidence }) }).collect::<Vec<_>>(), "uncertain_references": uncertain_refs, "alias_delta": delta.additions, }); println!("{}", serde_json::to_string_pretty(&output).unwrap()); }
                        Format::Pretty => {
                            println!("Known entities: {}", alias_map.len());
                            for (name, aliases) in &alias_map { if !aliases.is_empty() { println!("  {} (aliases: {})", name, aliases.join(", ")); } else { println!("  {}", name); } }
                            println!("\nDiscovered {} new entity candidates:", candidates.len());
                            for candidate in &candidates { println!("  {} [{}] (confidence: {:.2})", candidate.canonical_name, candidate.entity_type.as_str(), candidate.confidence); if !candidate.aliases.is_empty() { println!("    Aliases: {}", candidate.aliases.join(", ")); } println!("    Evidence: {}", candidate.evidence.join(", ")); }
                            if !uncertain_refs.is_empty() { println!("\nUncertain entity references found in beats:"); for name in &uncertain_refs { println!("  {{?{}}}", name); } }
                            if !delta.additions.is_empty() { println!("\nProposed alias additions:"); for (canon, aliases) in delta.additions.iter() { println!("  {} += [{}]", canon, aliases.join(", ")); } }
                        }
                    }
                }
                NotesCommands::ListEntities { path } => {
                    let content = match fs::read_to_string(&path) { Ok(c) => c, Err(e) => { eprintln!("Error: Failed to read file {}: {}", path.display(), e); std::process::exit(1); } };

                    let mut parser = Parser::new();
                    let tree = match parser.internal.parse(&content, None) { Some(t) => t, None => { eprintln!("Error: Failed to parse file {}", path.display()); std::process::exit(1);} };
                    let root = tree.root_node();
                    let file_str = path.to_str().unwrap_or("unknown");

                    let alias_map = extract_entities_with_aliases(&root, &content, file_str);

                    match cli.globals.format {
                        Format::Json => { println!("{}", serde_json::to_string_pretty(&alias_map).unwrap()); }
                        Format::Pretty => {
                            println!("Entities defined in {}:", path.display());
                            for (name, aliases) in &alias_map { if !aliases.is_empty() { println!("  {} (aliases: {})", name, aliases.join(", ")); } else { println!("  {}", name); } }
                            println!("\nTotal: {} entities", alias_map.len());
                        }
                    }
                }
                NotesCommands::ReviewExtraction { proposal, path, strategy, min_confidence, min_importance, dedupe_by, out_actions, apply } => {
                    // Read proposal JSON
                    let proposal_str = if proposal == "-" { let mut s = String::new(); use std::io::Read; std::io::stdin().read_to_string(&mut s).expect("failed to read stdin"); s } else { match fs::read_to_string(&proposal) { Ok(s) => s, Err(e) => { eprintln!("Error: Failed to read proposal {}: {}", proposal, e); std::process::exit(1);} } };
                    #[derive(serde::Deserialize)]
                    struct Proposal { #[serde(default)] beats: Vec<premise_notes::schema::Beat>, #[serde(default)] facts: Vec<premise_notes::schema::Fact>, #[serde(default)] alias_delta: std::collections::HashMap<String, Vec<String>> }

                    let mut proposal: Proposal = match serde_json::from_str(&proposal_str) { Ok(p) => p, Err(e) => { eprintln!("Error: Invalid proposal JSON: {}", e); std::process::exit(1);} };

                    // Dedupe
                    if dedupe_by == "text" {
                        use std::collections::HashSet;
                        let mut seen_b = HashSet::new();
                        proposal.beats.retain(|b| seen_b.insert(b.text.clone()));
                        let mut seen_f = HashSet::new();
                        proposal.facts.retain(|f| seen_f.insert(f.fact.clone()));
                    }

                    // Strategy filters
                    let mut accepted_beats = Vec::new();
                    let mut accepted_facts = Vec::new();
                    let canonical: std::collections::HashSet<String> = premise_notes::io::read_alias_map(&path).unwrap_or_default().keys().cloned().collect();
                    let conf_min = min_confidence.unwrap_or(0.0);
                    let imp_min = min_importance.unwrap_or(0.0);
                    let strat = strategy.as_str();
                    for b in proposal.beats.into_iter() {
                        let good_conf = true; // beats have no confidence, skip
                        let good_imp = b.importance.as_ref().map(|i| i.score >= imp_min).unwrap_or(false) || imp_min == 0.0;
                        let known = b.entities.iter().all(|e| canonical.contains(e));
                        let approve = match strat {
                            "approve-high-confidence" => good_conf && good_imp,
                            "approve-known-entities" => known,
                            "approve-new-only" => !known,
                            _ => good_imp || known,
                        };
                        if approve { accepted_beats.push(b); }
                    }
                    for f in proposal.facts.into_iter() {
                        let good_conf = f.confidence.unwrap_or(0.0) >= conf_min;
                        let good_imp = f.importance.as_ref().map(|i| i.score >= imp_min).unwrap_or(false) || imp_min == 0.0;
                        let ents = f
                            .entities
                            .clone()
                            .or_else(|| f.entity.as_ref().map(|e| vec![e.clone()]))
                            .unwrap_or_default();
                        let known = ents.iter().all(|e| canonical.contains(e));
                        let approve = match strat {
                            "approve-high-confidence" => good_conf && good_imp,
                            "approve-known-entities" => known,
                            "approve-new-only" => !known,
                            _ => (good_conf && good_imp) || known,
                        };
                        if approve { accepted_facts.push(f); }
                    }

                    #[derive(serde::Serialize)]
                    struct Actions<'a> {
                        accept_beats: &'a [premise_notes::schema::Beat],
                        accept_facts: &'a [premise_notes::schema::Fact],
                        apply_alias_delta: &'a std::collections::HashMap<String, Vec<String>>,
                        summary: serde_json::Value,
                    }
                    let summary = serde_json::json!({
                        "accepted_beats": accepted_beats.len(),
                        "accepted_facts": accepted_facts.len(),
                        "alias_additions": proposal.alias_delta.values().map(|v| v.len()).sum::<usize>()
                    });
                    let actions = Actions { accept_beats: &accepted_beats, accept_facts: &accepted_facts, apply_alias_delta: &proposal.alias_delta, summary };

                    if let Some(out) = out_actions.as_ref() {
                        if let Err(e) = std::fs::write(out, serde_json::to_string_pretty(&actions).unwrap()) { eprintln!("Error: Failed to write actions {}: {}", out.display(), e); std::process::exit(1); }
                    }

                    match cli.globals.format {
                        Format::Json => println!("{}", serde_json::to_string_pretty(&actions).unwrap()),
                        Format::Pretty => {
                            println!("Accepted beats: {}", accepted_beats.len());
                            println!("Accepted facts: {}", accepted_facts.len());
                        }
                    }

                    if apply {
                        // Apply immediately
                        let notes_dir = premise_core::notes::get_notes_dir(&path);
                        let beats_path = notes_dir.join("beats.jsonl");
                        let facts_path = notes_dir.join("facts.jsonl");
                        premise_core::notes::initialize_notes(&path, None).ok();
                        if let Err(e) = premise_core::notes::append_many_jsonl(&beats_path, &accepted_beats) { eprintln!("Error: {}", e); std::process::exit(1); }
                        if let Err(e) = premise_core::notes::append_many_jsonl(&facts_path, &accepted_facts) { eprintln!("Error: {}", e); std::process::exit(1); }
                        if !proposal.alias_delta.is_empty() {
                            let mut base = premise_notes::io::read_alias_map(&path).unwrap_or_default();
                            let _ = premise_notes::io::merge_alias_maps(&mut base, &proposal.alias_delta);
                            if let Err(e) = premise_notes::io::write_alias_map(&path, &base) { eprintln!("Error: {}", e); std::process::exit(1); }
                        }
                        let _ = premise_core::notes::rebuild_index(&path);
                    }
                }
                NotesCommands::ApplyActions { actions, path, dry_run } => {
                    let data = match std::fs::read_to_string(&actions) { Ok(s) => s, Err(e) => { eprintln!("Error: Failed to read actions {}: {}", actions.display(), e); std::process::exit(1); } };
                    #[derive(serde::Deserialize)]
                    struct ActionsIn { #[serde(default)] accept_beats: Vec<premise_notes::schema::Beat>, #[serde(default)] accept_facts: Vec<premise_notes::schema::Fact>, #[serde(default)] apply_alias_delta: std::collections::HashMap<String, Vec<String>> }
                    let actions: ActionsIn = match serde_json::from_str(&data) { Ok(v) => v, Err(e) => { eprintln!("Error: Invalid actions JSON: {}", e); std::process::exit(1); } };
                    if dry_run {
                        let summary = serde_json::json!({ "accept_beats": actions.accept_beats.len(), "accept_facts": actions.accept_facts.len(), "alias_additions": actions.apply_alias_delta.values().map(|v| v.len()).sum::<usize>() });
                        println!("{}", serde_json::to_string_pretty(&summary).unwrap());
                        return;
                    }
                    let notes_dir = premise_core::notes::get_notes_dir(&path);
                    let beats_path = notes_dir.join("beats.jsonl");
                    let facts_path = notes_dir.join("facts.jsonl");
                    premise_core::notes::initialize_notes(&path, None).ok();
                    if let Err(e) = premise_core::notes::append_many_jsonl(&beats_path, &actions.accept_beats) { eprintln!("Error: {}", e); std::process::exit(1); }
                    if let Err(e) = premise_core::notes::append_many_jsonl(&facts_path, &actions.accept_facts) { eprintln!("Error: {}", e); std::process::exit(1); }
                    if !actions.apply_alias_delta.is_empty() {
                        let mut base = premise_notes::io::read_alias_map(&path).unwrap_or_default();
                        let _ = premise_notes::io::merge_alias_maps(&mut base, &actions.apply_alias_delta);
                        if let Err(e) = premise_notes::io::write_alias_map(&path, &base) { eprintln!("Error: {}", e); std::process::exit(1); }
                    }
                    let _ = premise_core::notes::rebuild_index(&path);
                }
                NotesCommands::Status { path } => {
                    let (exists, initialized, stats) = premise_core::notes::get_notes_status(&path)
                        .expect("failed to get notes status");
                    match cli.globals.format {
                        Format::Json => {
                            let status = serde_json::json!({
                                "exists": exists,
                                "initialized": initialized,
                                "stats": stats
                            });
                            println!("{}", serde_json::to_string_pretty(&status).unwrap());
                        }
                        Format::Pretty => {
                            println!("Notes directory: {}", if exists { "exists" } else { "not found" });
                            println!("Initialized: {}", if initialized { "yes" } else { "no" });
                            if let Some(stats) = stats {
                                println!("  Beats: {}", stats.beats);
                                println!("  Facts: {}", stats.facts);
                                println!("  Timeline events: {}", stats.timeline_events);
                                println!("  Consistency entries: {}", stats.consistency_entries);
                                println!("  Entities tracked: {}", stats.entities_tracked);
                            }
                        }
                    }
                }
            }
            // Ensure exhaustive match
            // (No-op: already handled all variants above)
        }
        Commands::Adapters(adapters_cmd) => {
            match adapters_cmd {
                AdaptersCommands::List { domain } => {
                    let mut registry = premise_core::adapters::AdapterRegistry::new();
                    for path in premise_core::adapters::default_search_paths() {
                        registry.add_search_path(path);
                    }
                    if let Err(e) = registry.discover() {
                        eprintln!("Warning: Failed to discover adapters: {}", e);
                    }
                    let adapters = if let Some(domain) = domain {
                        registry.find_by_domain(&domain)
                    } else {
                        registry.list_all().iter().collect()
                    };
                    match cli.globals.format {
                        Format::Json => {
                            println!("{}", serde_json::to_string_pretty(&adapters).unwrap());
                        }
                        Format::Pretty => {
                            if adapters.is_empty() {
                                println!("No adapters found.");
                            } else {
                                println!("Available adapters:");
                                for adapter in adapters {
                                    println!("\n  {} ({})", adapter.name, adapter.id);
                                    println!("    Version: {}", adapter.version);
                                    println!("    Domains: {}", adapter.domains.join(", "));
                                    println!("    Description: {}", adapter.description);
                                    if let Some(ref author) = adapter.author {
                                        println!("    Author: {}", author);
                                    }
                                }
                            }
                        }
                    }
                }
                AdaptersCommands::Show { id } => {
                    let mut registry = premise_core::adapters::AdapterRegistry::new();
                    for path in premise_core::adapters::default_search_paths() {
                        registry.add_search_path(path);
                    }
                    let _ = registry.discover();
                    if let Some(adapter) = registry.find_by_id(&id) {
                        match cli.globals.format {
                            Format::Json => {
                                println!("{}", serde_json::to_string_pretty(adapter).unwrap());
                            }
                            Format::Pretty => {
                                println!("Adapter: {} ({})", adapter.name, adapter.id);
                                println!("Version: {}", adapter.version);
                                println!("Description: {}", adapter.description);
                                println!("Domains: {}", adapter.domains.join(", "));
                                if let Some(ref author) = adapter.author {
                                    println!("Author: {}", author);
                                }
                                if let Some(ref repo) = adapter.repository {
                                    println!("Repository: {}", repo);
                                }
                                println!("\nCapabilities:");
                                println!("  Generates artifacts: {}", adapter.capabilities.generates_artifacts);
                                println!("  Uses notes context: {}", adapter.capabilities.uses_notes_context);
                                println!("  Contributes facts: {}", adapter.capabilities.contributes_facts);
                                println!("  Output formats: {}", adapter.capabilities.output_formats.join(", "));
                                println!("  Entity types: {}", adapter.capabilities.entity_types.join(", "));
                                println!("\nEntry point: {}", adapter.entry_point);
                            }
                        }
                    } else {
                        eprintln!("Error: Adapter '{}' not found", id);
                        std::process::exit(1);
                    }
                }
            }
        }
    }
}
