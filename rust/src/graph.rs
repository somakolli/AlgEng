use std::fs::File;
use std::io;
use std::io::BufReader;
use std::io::BufRead;
use node;
use edge;

pub struct Graph{
    pub nodes: Vec<node::Node>,
    pub edges: Vec<edge::Edge>
}

pub trait Read {
    fn read_graph(&mut self, file_name: &str) -> Result<(), io::Error>;
}

pub trait Offset {
    fn set_offset(&mut self, src: bool);
}

pub trait DownGraph {
    fn calc_down_graph(&self) -> Graph;
}

impl DownGraph for Graph {
    fn calc_down_graph(&self) -> Graph {
        let mut graph:  Graph = Graph {
            nodes: Vec::new(),
            edges: Vec::new()
        };
        graph.nodes.reserve(self.nodes.len());
        graph.edges.reserve(self.edges.len());

        graph.edges = self.edges.clone();
        graph.nodes = self.nodes.clone();

        graph.edges.sort_by(|a,b| a.target_id.cmp(&b.target_id));
        graph.set_offset(false);
        graph
    }
}

impl Read for Graph {
    fn read_graph(&mut self, file_name: &str) -> Result<(), io::Error> {
        let file = File::open(file_name)?;
        let mut i  = 0;
        let mut number_of_nodes = 0;
        let mut number_of_edges = 0;

        //first loop read number of nodes and edges
        for line in BufReader::new(file).lines() {
            let l = line.unwrap();
            if l == "" || l.chars().next().unwrap() == '#' {
                continue;
            }
            match i {
                0 => {
                    number_of_nodes = l.parse::<usize>().unwrap();
                    self.nodes.reserve(number_of_nodes);
                },
                1 => {
                    number_of_edges = l.parse::<usize>().unwrap();
                    self.edges.reserve(number_of_edges);
                },
                _ => {}
            }
            i += 1;
        }

        i = 0;
        //second loop read nodes and edges
        let file = File::open(file_name)?;
        for line in BufReader::new(file).lines() {
            let l = line.unwrap();
            if l == "" || l.chars().next().unwrap() == '#'  {
                continue;
            }
            let _split = l.split(' ');
            let params: Vec<&str> = _split.collect();
            if i < number_of_nodes + 2 && params.len() >= 5 {
                self.nodes.push(node::Node{
                    id: params[0].parse::<usize>().unwrap(),
                    osm_id: params[1].parse::<u64>().unwrap(),
                    longitude: params[2].parse::<f64>().unwrap(),
                    latitude: params[3].parse::<f64>().unwrap(),
                    height: params[4].parse::<u64>().unwrap(),
                    level: params[5].parse::<u64>().unwrap(),
                    edges_begin: 0,
                    edges_end: 0
                });
            } else if params.len() >= 5 {
                self.edges.push(edge::Edge{
                    source_id: params[0].parse::<usize>().unwrap(),
                    target_id: params[1].parse::<usize>().unwrap(),
                    weight: params[2].parse::<u64>().unwrap(),
                    type_e: params[3].parse::<u16>().unwrap(),
                    max_speed: params[4].parse::<i32>().unwrap(),
                    edge_id_a: params[5].parse::<i64>().unwrap(),
                    edge_id_b: params[6].parse::<i64>().unwrap()
                });
            }
            i += 1;
        }

        println!("{}", number_of_nodes);
        println!("{}", number_of_edges);
        Ok(())
    }
}

impl Offset for Graph {
    fn set_offset(&mut self, src: bool){
        let mut i: usize = self.edges.len();
        for edge in self.edges.iter().rev() {
            match src {
                true =>  {
                    self.nodes[edge.source_id].edges_begin = i-1;
                },
                false => {
                    self.nodes[edge.target_id].edges_begin = i-1;
                }
            };
            i -= 1;
        }
        i = 1;
        for edge in &self.edges {
            match src {
                true => {
                    self.nodes[edge.source_id].edges_end = i;
                },
                false => {
                    self.nodes[edge.target_id].edges_end = i;
                }
            };
            i += 1;
        }
    }
}

