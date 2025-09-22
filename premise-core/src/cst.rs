use serde::{Deserialize, Serialize};
use schemars::JsonSchema;
use crate::ast::Range;

#[derive(Debug, Clone, Serialize, Deserialize, JsonSchema)]
pub struct Cst {
    pub root_sexpr: String,
    pub range: Range,
}


