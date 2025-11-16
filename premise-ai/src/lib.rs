use serde::{Deserialize, Serialize};
use std::fs;
use std::path::{Path, PathBuf};

/// Minimal chat message for provider communication
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ChatMessage {
    pub role: String,
    pub content: String,
}

/// Provider-agnostic AI config
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct AiConfig {
    pub provider: String,
    pub endpoint: Option<String>,
    pub model: Option<String>,
    pub api_key_env: Option<String>,
    pub headers: Option<std::collections::HashMap<String, String>>,
    pub temperature: Option<f64>,
    pub max_tokens: Option<u32>,
}

/// Shared LLM provider interface used by extractors
pub trait LlmProvider: Send + Sync {
    fn name(&self) -> &str;
    fn config(&self) -> &AiConfig;
    /// Return JSON string or domain output as a string. Caller will parse.
    fn complete_chat(&self, messages: &[ChatMessage]) -> anyhow::Result<String>;
}

/// A no-op provider that falls back to heuristics. Useful for wiring and tests.
#[derive(Debug, Clone)]
pub struct NoopProvider {
    cfg: AiConfig,
}

impl NoopProvider {
    pub fn new(cfg: AiConfig) -> Self {
        Self { cfg }
    }
}

impl LlmProvider for NoopProvider {
    fn name(&self) -> &str {
        "noop"
    }
    fn config(&self) -> &AiConfig {
        &self.cfg
    }
    fn complete_chat(&self, _messages: &[ChatMessage]) -> anyhow::Result<String> {
        Ok("{}".to_string())
    }
}

/// Record/replay cache mode
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum CacheMode {
    Off,
    ReadOnly,
    ReadWrite,
}

/// File-backed record/replay cache under .premise-notes/.llm_sessions
pub struct LlmCache {
    root: PathBuf,
    mode: CacheMode,
}

impl LlmCache {
    pub fn new(project_root: &Path, mode: CacheMode) -> Self {
        let root = project_root.join(".premise-notes").join(".llm_sessions");
        Self { root, mode }
    }

    fn key_for(messages: &[ChatMessage], model: &str) -> String {
        use sha2::{Digest, Sha256};
        let mut hasher = Sha256::new();
        hasher.update(model.as_bytes());
        for m in messages {
            hasher.update(m.role.as_bytes());
            hasher.update(0x1fu8.to_le_bytes());
            hasher.update(m.content.as_bytes());
            hasher.update(0x2au8.to_le_bytes());
        }
        hex::encode(hasher.finalize())
    }

    fn path_for(&self, key: &str) -> PathBuf {
        self.root.join(format!("{}.json", key))
    }

    pub fn get(&self, key: &str) -> Option<String> {
        if self.mode == CacheMode::Off {
            return None;
        }
        let path = self.path_for(key);
        fs::read_to_string(path).ok()
    }

    pub fn put(&self, key: &str, value: &str) -> anyhow::Result<()> {
        if self.mode != CacheMode::ReadWrite {
            return Ok(());
        }
        if let Some(parent) = self.root.parent() {
            fs::create_dir_all(parent)?;
        }
        fs::create_dir_all(&self.root)?;
        let path = self.path_for(key);
        fs::write(path, value)?;
        Ok(())
    }
}

/// OpenRouter provider implementation using blocking reqwest
pub struct OpenRouterProvider {
    cfg: AiConfig,
    /// Optional record/replay cache
    cache: Option<LlmCache>,
}

impl OpenRouterProvider {
    pub fn new(cfg: AiConfig) -> Self {
        Self { cfg, cache: None }
    }
    pub fn with_cache(cfg: AiConfig, cache: LlmCache) -> Self {
        Self {
            cfg,
            cache: Some(cache),
        }
    }
}

impl LlmProvider for OpenRouterProvider {
    fn name(&self) -> &str {
        "openrouter"
    }
    fn config(&self) -> &AiConfig {
        &self.cfg
    }
    fn complete_chat(&self, messages: &[ChatMessage]) -> anyhow::Result<String> {
        let endpoint = self
            .cfg
            .endpoint
            .as_deref()
            .unwrap_or("https://openrouter.ai/api/v1/chat/completions");
        let model = self.cfg.model.as_deref().unwrap_or("openai/gpt-4o-mini");

        // Cache key
        if let Some(cache) = &self.cache {
            let key = LlmCache::key_for(messages, model);
            if let Some(resp) = cache.get(&key) {
                return Ok(resp);
            }
        }

        let api_key_env = self
            .cfg
            .api_key_env
            .as_deref()
            .unwrap_or("OPENROUTER_API_KEY");
        let api_key = std::env::var(api_key_env)
            .map_err(|_| anyhow::anyhow!("missing API key in {}", api_key_env))?;

        let mut headers = reqwest::header::HeaderMap::new();
        headers.insert(
            reqwest::header::AUTHORIZATION,
            format!("Bearer {}", api_key).parse()?,
        );
        headers.insert(reqwest::header::CONTENT_TYPE, "application/json".parse()?);
        if let Some(custom) = &self.cfg.headers {
            for (k, v) in custom {
                let name: reqwest::header::HeaderName = k.parse()?;
                let value: reqwest::header::HeaderValue = v.parse()?;
                headers.insert(name, value);
            }
        }

        #[derive(Serialize)]
        struct ReqMsg<'a> {
            role: &'a str,
            content: &'a str,
        }
        #[derive(Serialize)]
        struct ReqBody<'a> {
            model: &'a str,
            messages: Vec<ReqMsg<'a>>,
            #[serde(skip_serializing_if = "Option::is_none")]
            temperature: Option<f64>,
            #[serde(skip_serializing_if = "Option::is_none")]
            max_tokens: Option<u32>,
        }
        #[derive(Deserialize)]
        struct Choice {
            message: ChatMessage,
        }
        #[derive(Deserialize)]
        struct RespBody {
            choices: Vec<Choice>,
        }

        let body = ReqBody {
            model,
            messages: messages
                .iter()
                .map(|m| ReqMsg {
                    role: &m.role,
                    content: &m.content,
                })
                .collect(),
            temperature: self.cfg.temperature,
            max_tokens: self.cfg.max_tokens,
        };

        let client = reqwest::blocking::Client::new();
        let resp = client.post(endpoint).headers(headers).json(&body).send()?;

        if !resp.status().is_success() {
            return Err(anyhow::anyhow!("openrouter error: {}", resp.text()?));
        }
        let parsed: RespBody = resp.json()?;
        let out = parsed
            .choices
            .first()
            .map(|c| c.message.content.clone())
            .unwrap_or_else(|| "{}".to_string());

        if let Some(cache) = &self.cache {
            let key = LlmCache::key_for(messages, model);
            let _ = cache.put(&key, &out);
        }

        Ok(out)
    }
}

/// Load AI config using precedence: explicit path -> project -> user -> defaults
pub fn load_ai_config(
    explicit: Option<&std::path::Path>,
    story_root: Option<&std::path::Path>,
) -> AiConfig {
    if let Some(p) = explicit {
        if let Ok(cfg) = load_ai_config_from(p) {
            return cfg;
        }
    }
    if let Some(root) = story_root {
        for p in default_project_paths(root) {
            if p.exists() {
                if let Ok(cfg) = load_ai_config_from(&p) {
                    return cfg;
                }
            }
        }
    }
    for p in default_user_paths() {
        if p.exists() {
            if let Ok(cfg) = load_ai_config_from(&p) {
                return cfg;
            }
        }
    }
    AiConfig {
        provider: "openrouter".to_string(),
        endpoint: Some("https://openrouter.ai/api/v1/chat/completions".to_string()),
        model: Some("openai/gpt-4o-mini".to_string()),
        api_key_env: Some("OPENROUTER_API_KEY".to_string()),
        headers: None,
        temperature: Some(0.3),
        max_tokens: Some(1500),
    }
}

fn default_project_paths(story_root: &std::path::Path) -> Vec<std::path::PathBuf> {
    vec![story_root.join(".premise-notes").join("ai.json")]
}

fn default_user_paths() -> Vec<std::path::PathBuf> {
    let mut paths = Vec::new();
    if let Some(dir) = dirs::config_dir() {
        paths.push(dir.join("premise").join("ai.json"));
    }
    paths
}

pub fn load_ai_config_from(path: &std::path::Path) -> anyhow::Result<AiConfig> {
    let data = std::fs::read_to_string(path)
        .map_err(|e| anyhow::anyhow!("failed to read ai config at {}: {}", path.display(), e))?;
    let cfg: AiConfig = serde_json::from_str(&data)
        .map_err(|e| anyhow::anyhow!("failed to parse ai config at {}: {}", path.display(), e))?;
    Ok(cfg)
}
