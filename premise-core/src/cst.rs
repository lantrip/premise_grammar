use crate::ast::Range;
use schemars::JsonSchema;
use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Cst {
    pub root_sexpr: String,
    pub range: Range,
}
