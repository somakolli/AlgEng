use std::fmt;

#[derive(Copy, Clone)]
pub struct Node {
    pub id: usize,
    pub osm_id: u64,
    pub latitude: f64,
    pub longitude: f64,
    pub height: u64,
    pub level: u64,
    pub edges_begin: usize,
    pub edges_end: usize
}

impl fmt::Display for Node{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result
    {
        write!(f, "osm_id: {}, latitude: {}, longitude: {}, height: {}, level: {}, edges_begin: {}, edges_end: {}",
               self.osm_id, self.latitude, self.longitude, self.height, self.level, self.edges_begin, self.edges_end)
    }
}

