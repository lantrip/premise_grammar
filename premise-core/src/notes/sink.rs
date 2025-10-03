use std::fs;
use std::io::Write;
use std::path::{Path, PathBuf};

use premise_notes::schema::{Beat, Fact, TimelineEvent};

/// A pluggable sink for emitting extracted notes without assuming storage layout
pub trait NotesSink {
    fn emit_beats(&mut self, beats: &[Beat]) -> std::io::Result<()>;
    fn emit_facts(&mut self, facts: &[Fact]) -> std::io::Result<()>;
    fn emit_timeline(&mut self, events: &[TimelineEvent]) -> std::io::Result<()>;
}

/// Emit records to stdout (pretty JSON arrays by default)
pub struct StdoutSink {
    /// If true, print human-friendly summaries; otherwise print pretty JSON
    pretty: bool,
}

impl StdoutSink {
    pub fn new(pretty: bool) -> Self {
        Self { pretty }
    }

    fn write_json_array<T: serde::Serialize>(values: &[T]) -> std::io::Result<()> {
        let json = serde_json::to_string_pretty(values)?;
        println!("{}", json);
        Ok(())
    }
}

impl NotesSink for StdoutSink {
    fn emit_beats(&mut self, beats: &[Beat]) -> std::io::Result<()> {
        if self.pretty {
            println!("Beats: {}", beats.len());
            for b in beats {
                println!("- {}{}", b.text, if let Some(ref s) = b.section { if let Some(ref scene) = s.scene { format!(" (scene: {})", scene) } else { String::new() } } else { String::new() });
            }
            Ok(())
        } else {
            Self::write_json_array(beats)
        }
    }

    fn emit_facts(&mut self, facts: &[Fact]) -> std::io::Result<()> {
        if self.pretty {
            println!("Facts: {}", facts.len());
            for f in facts {
                if let Some(ref e) = f.entity {
                    println!("- [{}] {}", e, f.fact);
                } else {
                    println!("- {}", f.fact);
                }
            }
            Ok(())
        } else {
            Self::write_json_array(facts)
        }
    }

    fn emit_timeline(&mut self, events: &[TimelineEvent]) -> std::io::Result<()> {
        if self.pretty {
            println!("Timeline events: {}", events.len());
            for e in events {
                println!("- {}", e.event);
            }
            Ok(())
        } else {
            Self::write_json_array(events)
        }
    }
}

/// Append records to JSONL files in a directory
pub struct JsonlDirSink {
    dir: PathBuf,
}

impl JsonlDirSink {
    pub fn new<P: AsRef<Path>>(dir: P) -> std::io::Result<Self> {
        fs::create_dir_all(dir.as_ref())?;
        Ok(Self { dir: dir.as_ref().to_path_buf() })
    }
}

impl NotesSink for JsonlDirSink {
    fn emit_beats(&mut self, beats: &[Beat]) -> std::io::Result<()> {
        let path = self.dir.join("beats.jsonl");
        premise_notes::io::append_many_jsonl(&path, beats)
    }

    fn emit_facts(&mut self, facts: &[Fact]) -> std::io::Result<()> {
        let path = self.dir.join("facts.jsonl");
        premise_notes::io::append_many_jsonl(&path, facts)
    }

    fn emit_timeline(&mut self, events: &[TimelineEvent]) -> std::io::Result<()> {
        let path = self.dir.join("timeline.jsonl");
        premise_notes::io::append_many_jsonl(&path, events)
    }
}

/// Write each record as an individual JSON file under subdirectories
pub struct DirSink {
    dir: PathBuf,
}

impl DirSink {
    pub fn new<P: AsRef<Path>>(dir: P) -> std::io::Result<Self> {
        fs::create_dir_all(dir.as_ref())?;
        Ok(Self { dir: dir.as_ref().to_path_buf() })
    }

    fn write_many<T: serde::Serialize>(base: &Path, sub: &str, id_fn: impl Fn(&T) -> &str, values: &[T]) -> std::io::Result<()> {
        let out_dir = base.join(sub);
        fs::create_dir_all(&out_dir)?;
        for v in values {
            let id = id_fn(v);
            let path = out_dir.join(format!("{}.json", id));
            let content = serde_json::to_string_pretty(v)?;
            let mut f = fs::File::create(path)?;
            f.write_all(content.as_bytes())?;
        }
        Ok(())
    }
}

impl NotesSink for DirSink {
    fn emit_beats(&mut self, beats: &[Beat]) -> std::io::Result<()> {
        Self::write_many(&self.dir, "beats", |b: &Beat| b.id.as_str(), beats)
    }

    fn emit_facts(&mut self, facts: &[Fact]) -> std::io::Result<()> {
        Self::write_many(&self.dir, "facts", |f: &Fact| f.id.as_str(), facts)
    }

    fn emit_timeline(&mut self, events: &[TimelineEvent]) -> std::io::Result<()> {
        Self::write_many(&self.dir, "timeline", |e: &TimelineEvent| e.id.as_str(), events)
    }
}


