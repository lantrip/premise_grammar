use std::fs;
use std::path::PathBuf;

use clap::{Args, Parser as ClapParser, Subcommand, ValueEnum};

use premise_core::{api, Parser};
use schemars::schema::RootSchema;

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
    },
    /// Extract facts from a file to notes directory
    ExtractFacts {
        /// Path to the .prem file
        file: PathBuf,
    },
    /// Extract timeline from a file
    ExtractTimeline {
        /// Path to the .prem file
        file: PathBuf,
    },
    /// Rebuild the notes index
    RebuildIndex {
        /// Story root path (defaults to current directory)
        #[arg(default_value = ".")]
        path: PathBuf,
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
        Commands::Parse {
            file,
            json,
            ast,
            symbols,
            imports,
            resolved_imports,
        } => {
            let content = fs::read_to_string(&file).expect("failed to read file");
            let mut parser = Parser::new();
            let (cst, diagnostics, ast_value) = parser.parse_str(&content);

            let mut out = api::ParseOutput {
                cst: premise_core::cst::Cst {
                    root_sexpr: cst.root_sexpr,
                    range: cst.range,
                },
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

            // If --json is passed for parse command, force JSON output regardless of global format
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
                // Get story root (parent directory of file)
                let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));

                // Initialize notes if needed
                premise_core::notes::initialize_notes(story_root, None)
                    .expect("failed to initialize notes");

                // Extract and save notes
                let file_str = file.to_str().unwrap_or("unknown");
                let facts = premise_core::notes::extract_facts_from_ir(&ir, file_str);
                premise_core::notes::append_facts(story_root, &facts)
                    .expect("failed to append facts");

                let timeline = premise_core::notes::extract_timeline_from_ir(&ir, file_str);
                let timeline_path = premise_core::notes::get_notes_dir(story_root).join("timeline.jsonl");
                premise_core::notes::append_many_jsonl(&timeline_path, &timeline)
                    .expect("failed to append timeline");

                // Rebuild index
                premise_core::notes::rebuild_index(story_root)
                    .expect("failed to rebuild index");
            }

            match cli.globals.format {
                Format::Json => println!(
                    "{}",
                    serde_json::to_string_pretty(&api::AnalyzeOutput { ir }).unwrap()
                ),
                Format::Pretty => println!(
                    "{}",
                    serde_json::to_string_pretty(&api::AnalyzeOutput { ir }).unwrap()
                ),
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
                "parse" => schemas.push((
                    "ParseOutput".into(),
                    schemars::schema_for!(api::ParseOutput),
                )),
                "validate" => schemas.push((
                    "ValidateOutput".into(),
                    schemars::schema_for!(api::ValidateOutput),
                )),
                "analyze" => schemas.push((
                    "AnalyzeOutput".into(),
                    schemars::schema_for!(api::AnalyzeOutput),
                )),
                "plan" => {
                    schemas.push(("PlanOutput".into(), schemars::schema_for!(api::PlanOutput)))
                }
                "notes" => {
                    schemas.push(("Beat".into(), schemars::schema_for!(premise_core::notes::Beat)));
                    schemas.push(("Fact".into(), schemars::schema_for!(premise_core::notes::Fact)));
                    schemas.push(("TimelineEvent".into(), schemars::schema_for!(premise_core::notes::TimelineEvent)));
                    schemas.push(("ConsistencyEntry".into(), schemars::schema_for!(premise_core::notes::ConsistencyEntry)));
                    schemas.push(("NotesIndex".into(), schemars::schema_for!(premise_core::notes::NotesIndex)));
                    schemas.push(("NotesMetadata".into(), schemars::schema_for!(premise_core::notes::NotesMetadata)));
                }
                _ => {
                    schemas.push((
                        "ParseOutput".into(),
                        schemars::schema_for!(api::ParseOutput),
                    ));
                    schemas.push((
                        "ValidateOutput".into(),
                        schemars::schema_for!(api::ValidateOutput),
                    ));
                    schemas.push((
                        "AnalyzeOutput".into(),
                        schemars::schema_for!(api::AnalyzeOutput),
                    ));
                    schemas.push(("PlanOutput".into(), schemars::schema_for!(api::PlanOutput)));
                    schemas.push(("Beat".into(), schemars::schema_for!(premise_core::notes::Beat)));
                    schemas.push(("Fact".into(), schemars::schema_for!(premise_core::notes::Fact)));
                    schemas.push(("TimelineEvent".into(), schemars::schema_for!(premise_core::notes::TimelineEvent)));
                    schemas.push(("ConsistencyEntry".into(), schemars::schema_for!(premise_core::notes::ConsistencyEntry)));
                    schemas.push(("NotesIndex".into(), schemars::schema_for!(premise_core::notes::NotesIndex)));
                    schemas.push(("NotesMetadata".into(), schemars::schema_for!(premise_core::notes::NotesMetadata)));
                }
            }

            let value = if schemas.len() == 1 {
                serde_json::to_value(&schemas[0].1).unwrap()
            } else {
                serde_json::json!(schemas
                    .into_iter()
                    .collect::<std::collections::BTreeMap<_, _>>())
            };
            if let Some(path) = out {
                std::fs::write(path, serde_json::to_string_pretty(&value).unwrap())
                    .expect("failed to write schema file");
            } else {
                println!("{}", serde_json::to_string_pretty(&value).unwrap());
            }
        }
        Commands::Notes(notes_cmd) => {
            match notes_cmd {
                NotesCommands::Init { path, title } => {
                    match premise_core::notes::initialize_notes(&path, title) {
                        Ok(_) => println!("Initialized notes directory at {}", path.display()),
                        Err(e) => {
                            eprintln!("Error: Failed to initialize notes directory at {}: {}", path.display(), e);
                            std::process::exit(1);
                        }
                    }
                }
                NotesCommands::ExportBeats { file, append: _ } => {
                    let content = match fs::read_to_string(&file) {
                        Ok(c) => c,
                        Err(e) => {
                            eprintln!("Error: Failed to read file {}: {}", file.display(), e);
                            std::process::exit(1);
                        }
                    };
                    let mut parser = Parser::new();

                    // Parse and get tree-sitter tree
                    let tree = match parser.internal.parse(&content, None) {
                        Some(t) => t,
                        None => {
                            eprintln!("Error: Failed to parse file {}", file.display());
                            std::process::exit(1);
                        }
                    };
                    let root = tree.root_node();

                    let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                    if let Err(e) = premise_core::notes::initialize_notes(story_root, None) {
                        eprintln!("Error: Failed to initialize notes at {}: {}", story_root.display(), e);
                        std::process::exit(1);
                    }

                    let file_str = file.to_str().unwrap_or("unknown");
                    // Use enhanced extraction with source text
                    let beats = premise_core::notes::extract_beats_from_tree(&root, &content, file_str);

                    if let Err(e) = premise_core::notes::append_beats(story_root, &beats) {
                        eprintln!("Error: Failed to save beats: {}", e);
                        std::process::exit(1);
                    }

                    if let Err(e) = premise_core::notes::rebuild_index(story_root) {
                        eprintln!("Warning: Failed to rebuild index: {}", e);
                    }

                    println!("Exported {} beats from {}", beats.len(), file.display());
                }
                NotesCommands::ExtractFacts { file } => {
                    let content = match fs::read_to_string(&file) {
                        Ok(c) => c,
                        Err(e) => {
                            eprintln!("Error: Failed to read file {}: {}", file.display(), e);
                            std::process::exit(1);
                        }
                    };
                    let mut parser = Parser::new();

                    // Parse and get tree-sitter tree
                    let tree = match parser.internal.parse(&content, None) {
                        Some(t) => t,
                        None => {
                            eprintln!("Error: Failed to parse file {}", file.display());
                            std::process::exit(1);
                        }
                    };
                    let root = tree.root_node();

                    let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                    if let Err(e) = premise_core::notes::initialize_notes(story_root, None) {
                        eprintln!("Error: Failed to initialize notes at {}: {}", story_root.display(), e);
                        std::process::exit(1);
                    }

                    let file_str = file.to_str().unwrap_or("unknown");
                    // Use enhanced extraction with source text
                    let facts = premise_core::notes::extract_all_facts_from_tree(&root, &content, file_str);

                    if let Err(e) = premise_core::notes::append_facts(story_root, &facts) {
                        eprintln!("Error: Failed to save facts: {}", e);
                        std::process::exit(1);
                    }

                    if let Err(e) = premise_core::notes::rebuild_index(story_root) {
                        eprintln!("Warning: Failed to rebuild index: {}", e);
                    }

                    println!("Extracted {} facts from {}", facts.len(), file.display());
                }
                NotesCommands::ExtractTimeline { file } => {
                    let content = fs::read_to_string(&file).expect("failed to read file");
                    let mut parser = Parser::new();
                    let ir = parser.analyze_ir(&content);

                    let story_root = file.parent().unwrap_or_else(|| std::path::Path::new("."));
                    premise_core::notes::initialize_notes(story_root, None)
                        .expect("failed to initialize notes");

                    let file_str = file.to_str().unwrap_or("unknown");
                    let timeline = premise_core::notes::extract_timeline_from_ir(&ir, file_str);
                    let timeline_path = premise_core::notes::get_notes_dir(story_root).join("timeline.jsonl");
                    premise_core::notes::append_many_jsonl(&timeline_path, &timeline)
                        .expect("failed to append timeline");

                    premise_core::notes::rebuild_index(story_root)
                        .expect("failed to rebuild index");

                    println!("Extracted {} timeline events from {}", timeline.len(), file.display());
                }
                NotesCommands::RebuildIndex { path } => {
                    let index = match premise_core::notes::rebuild_index(&path) {
                        Ok(idx) => idx,
                        Err(e) => {
                            eprintln!("Error: Failed to rebuild index at {}: {}", path.display(), e);
                            std::process::exit(1);
                        }
                    };
                    match cli.globals.format {
                        Format::Json => println!("{}", serde_json::to_string_pretty(&index).unwrap()),
                        Format::Pretty => {
                            println!("Index rebuilt successfully");
                            println!("  Beats: {}", index.stats.beats);
                            println!("  Facts: {}", index.stats.facts);
                            println!("  Timeline events: {}", index.stats.timeline_events);
                            println!("  Consistency entries: {}", index.stats.consistency_entries);
                            println!("  Entities tracked: {}", index.stats.entities_tracked);
                        }
                    }
                }
                NotesCommands::Query { entity, path } => {
                    let index = match premise_core::notes::read_index(&path) {
                        Ok(Some(idx)) => idx,
                        Ok(None) => {
                            eprintln!("Error: Index not found at {}. Run 'premise notes rebuild-index' first.", path.display());
                            std::process::exit(1);
                        }
                        Err(e) => {
                            eprintln!("Error: Failed to read index at {}: {}", path.display(), e);
                            std::process::exit(1);
                        }
                    };

                    if let Some(record_ids) = index.entity_index.get(&entity) {
                        let beats = premise_core::notes::read_beats(&path)
                            .expect("failed to read beats");
                        let facts = premise_core::notes::read_facts(&path)
                            .expect("failed to read facts");

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
        }
        Commands::Adapters(adapters_cmd) => {
            match adapters_cmd {
                AdaptersCommands::List { domain } => {
                    let mut registry = premise_core::adapters::AdapterRegistry::new();

                    // Add default search paths
                    for path in premise_core::adapters::default_search_paths() {
                        registry.add_search_path(path);
                    }

                    // Discover adapters
                    match registry.discover() {
                        Ok(count) => {
                            if cli.globals.format.is_json() {
                                eprintln!("Discovered {} adapters", count);
                            }
                        }
                        Err(e) => {
                            eprintln!("Warning: Failed to discover adapters: {}", e);
                        }
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

                    // Add default search paths
                    for path in premise_core::adapters::default_search_paths() {
                        registry.add_search_path(path);
                    }

                    // Discover adapters
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
