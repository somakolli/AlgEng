use graph;
use std::collections::BinaryHeap;
use std::cmp::Ordering;

pub struct Dijkstra<'a> {
    pub graph: &'a graph::Graph,
    cost: Vec<u64>,
    touched_nodes: Vec<usize>,
    pub settled_nodes: Vec<usize>
}

#[derive(Copy, Clone, Eq, PartialEq)]
struct CostNode {
    cost: u64,
    position: usize
}

impl Ord for CostNode {
    fn cmp(&self, other: &Self) -> Ordering {
        other.cost.cmp(&self.cost)
            .then_with(|| self.position.cmp(&other.position))
    }
}

impl PartialOrd for CostNode {
    fn partial_cmp(&self, other: &CostNode) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

pub fn init(graph: &graph::Graph) -> Dijkstra {
    // init cost array with u64::MAX
    let cost: Vec<u64> = (0..graph.nodes.len()).map(|_| std::u64::MAX).collect();
    let touched_nodes : Vec<usize> = Vec::new();
    let settled_nodes : Vec<usize> = Vec::new();
    Dijkstra {
        graph,
        cost,
        touched_nodes,
        settled_nodes
    }
}

pub trait ShortestDistance {
    fn shortest_distance(&mut self, source_id: usize, down: bool);
    fn get_distance(&mut self, target_id: usize) -> u64;
    fn clean_touched_nodes(&mut self);
}

impl<'a> ShortestDistance for Dijkstra<'a> {
    fn shortest_distance(&mut self, source_id: usize, down: bool) {
        self.clean_touched_nodes();
        self.cost[source_id] = 0;
        let mut prio_queue = BinaryHeap::new();
        prio_queue.push(CostNode{ cost: 0, position: source_id});
        while let Some(CostNode {cost, position} ) = prio_queue.pop() {
            self.settled_nodes.push(position);
            let node = self.graph.nodes[position];
            for i in node.edges_begin .. node.edges_end{
                let edge = self.graph.edges[i];
                let target_id = match down { true => edge.source_id, false => edge.target_id };
                let target_node = self.graph.nodes[target_id];
                if target_node.level < node.level {
                    continue;
                }
                let next_node = CostNode { cost: cost + edge.weight, position: target_id };
                let has_lower_cost = cost + edge.weight < self.cost[target_id];
                if has_lower_cost {
                    prio_queue.push(next_node);
                    self.cost[next_node.position] = next_node.cost;
                    self.touched_nodes.push(next_node.position);
                }
            }
        }
    }

    fn get_distance(&mut self, target_id: usize) -> u64 {
        self.cost[target_id]
    }

    fn clean_touched_nodes(&mut self) {
        for node in &self.touched_nodes {
            self.cost[*node] = std::u64::MAX;
        }
    }
}

