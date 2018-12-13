#include <iostream>
#include "Graph.h"
#include "Dijkstra.h"

int main() {
    alg_eng::Graph graph;
    graph.loadGraph("bw.graph");
    auto dijkstra = alg_eng::Dijkstra(graph);
    uint32_t src = 0;
    std::cout << dijkstra.shortestPath(0,2) << std::endl;
}