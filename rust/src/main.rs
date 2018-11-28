use std::time::{Instant};
use graph::Read;
use graph::Offset;
use graph::DownGraph;
use dijsktra::ShortestDistance;
#[macro_use]
extern crate text_io;
extern crate core;

mod node;
mod edge;
mod graph;
mod dijsktra;

fn main() {
    let now = Instant::now();
    let mut graph = graph::Graph {
        nodes: Vec::new(),
        edges: Vec::new()
    };

    graph.read_graph("bw.ch").expect("error reading file!");
    println!("{}", graph.nodes.len());
    println!("{}", graph.edges.len());
    graph.set_offset(true);
    let down_graph:  graph::Graph = graph.calc_down_graph();

    println!("time to load graph: {}", now.elapsed().as_secs());

    loop {
        let source = read!();
        let target = read!();
        let now = Instant::now();
        ch_query(source, target, &graph, &down_graph);
        let elapsed = now.elapsed();
        println!("Elapsed Time: {} ms", (elapsed.as_secs() * 1_000) + (elapsed.subsec_nanos() / 1_000_000) as u64);
    }

}

fn ch_query(source: usize, target: usize, up_graph: &graph::Graph, down_graph: &graph::Graph) {
    let mut up_dijkstra = dijsktra::init(up_graph);
    let mut down_dijkstra = dijsktra::init(down_graph);

    up_dijkstra.shortest_distance(source, false);
    down_dijkstra.shortest_distance(target, true);

    let mut up_settled_nodes = up_dijkstra.settled_nodes.clone();
    let mut down_settled_nodes = down_dijkstra.settled_nodes.clone();

    up_settled_nodes.sort();
    down_settled_nodes.sort();

    let mut lowest_distance = std::u64::MAX;


    let mut i1:usize = 0;
    let mut i2:usize = 0;
    while i1 < up_settled_nodes.len() && i2 < down_settled_nodes.len() {
        if up_settled_nodes[i1] < down_settled_nodes[i2] {
            i1 += 1;
        } else if up_settled_nodes[i1] > down_settled_nodes[i2] {
            i2 += 1;
        } else {
            let up_cost = up_dijkstra.get_distance(up_settled_nodes[i1]);
            let down_cost = down_dijkstra.get_distance(down_settled_nodes[i2]);
            let cost = up_cost + down_cost;
            if cost < lowest_distance {
                lowest_distance = cost;
            }
            i1 += 1;
            i2 += 1;
        }
    }

    println!("distance: {}", lowest_distance);

}
