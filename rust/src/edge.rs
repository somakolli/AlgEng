use std::fmt;

#[derive(Copy, Clone)]
pub struct Edge {
    pub source_id: usize,
    pub target_id: usize,
    pub weight: u64,
    pub type_e: u16,
    pub max_speed: i32,
    pub edge_id_a: i64,
    pub edge_id_b: i64
}

impl fmt::Display for Edge {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result
    {
        write!(f, "source_id: {}, target_id: {}, weight: {}, type_e: {}, max_speed: {}, edge_id_a: {}, edge_id_b: {}",
               self.source_id, self.target_id, self.weight, self.type_e, self.max_speed, self.edge_id_a, self.edge_id_b)
    }
}
