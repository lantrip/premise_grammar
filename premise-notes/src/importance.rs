use crate::schema::{Importance, ImportanceSource};

/// Pick the authoritative importance from a list using precedence and latest timestamp policy.
/// Precedence: User > Ai > Heuristic. Within each group, pick the latest by `updated`.
pub fn choose_authoritative(assessments: &[Importance]) -> Option<Importance> {
    if assessments.is_empty() {
        return None;
    }
    let mut users: Vec<&Importance> = assessments
        .iter()
        .filter(|i| matches!(i.assessed_by, ImportanceSource::User))
        .collect();
    let mut ais: Vec<&Importance> = assessments
        .iter()
        .filter(|i| matches!(i.assessed_by, ImportanceSource::Ai))
        .collect();
    let mut heuristics: Vec<&Importance> = assessments
        .iter()
        .filter(|i| matches!(i.assessed_by, ImportanceSource::Heuristic))
        .collect();

    users.sort_by(|a, b| a.updated.cmp(&b.updated));
    ais.sort_by(|a, b| a.updated.cmp(&b.updated));
    heuristics.sort_by(|a, b| a.updated.cmp(&b.updated));

    if let Some(last) = users.last() {
        return Some((*last).clone());
    }
    if let Some(last) = ais.last() {
        return Some((*last).clone());
    }
    if let Some(last) = heuristics.last() {
        return Some((*last).clone());
    }
    None
}
