use std::fs;
use std::path::PathBuf;

use clap::{Parser as ClapParser, Subcommand, ValueEnum, Args};

use premise_core::{Parser, api};
use schemars::schema::RootSchema;

#[derive(Copy, Clone, Debug, ValueEnum)]
enum Format {
    Json,
    Pretty,
}

impl Format {
    fn is_json(&self) -> bool { matches!(self, Format::Json) }
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
        /// Type to emit schema for (parse|validate|analyze|plan|all)
        #[arg(long, default_value = "all")]
        r#type: String,
        /// Write to file instead of stdout
        #[arg(long)]
        out: Option<PathBuf>,
    }
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

            match cli.globals.format {
                Format::Json => println!("{}", serde_json::to_string_pretty(&out).unwrap()),
                Format::Pretty => println!("{}", out.cst.root_sexpr),
            }
        }
        Commands::Validate { file } => {
            let content = fs::read_to_string(&file).expect("failed to read file");
            let mut parser = Parser::new();
            let report = parser.validate(&content);
            match cli.globals.format {
                Format::Json => println!("{}", serde_json::to_string_pretty(&api::ValidateOutput { report }).unwrap()),
                Format::Pretty => {
                    for issue in report.issues {
                        println!("{:?}: {}", issue.code, issue.message);
                    }
                }
            }
        }
        Commands::Analyze { file } => {
            let content = fs::read_to_string(&file).expect("failed to read file");
            let mut parser = Parser::new();
            let ir = parser.analyze_ir(&content);
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
                "plan" => schemas.push(("PlanOutput".into(), schemars::schema_for!(api::PlanOutput))),
                _ => {
                    schemas.push(("ParseOutput".into(), schemars::schema_for!(api::ParseOutput)));
                    schemas.push(("ValidateOutput".into(), schemars::schema_for!(api::ValidateOutput)));
                    schemas.push(("AnalyzeOutput".into(), schemars::schema_for!(api::AnalyzeOutput)));
                    schemas.push(("PlanOutput".into(), schemars::schema_for!(api::PlanOutput)));
                }
            }

            let value = if schemas.len() == 1 {
                serde_json::to_value(&schemas[0].1).unwrap()
            } else {
                serde_json::json!(schemas.into_iter().map(|(name, schema)| (name, schema)).collect::<std::collections::BTreeMap<_, _>>())
            };
            if let Some(path) = out {
                std::fs::write(path, serde_json::to_string_pretty(&value).unwrap()).expect("failed to write schema file");
            } else {
                println!("{}", serde_json::to_string_pretty(&value).unwrap());
            }
        }
    }
}


