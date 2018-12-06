//
// Created by sokol on 21.11.18.
//

#include <queue>
#include <functional>
#include <iostream>
#include "Dijkstra.h"

uint32_t alg_eng::Dijkstra::shortestPath(uint32_t src, uint32_t target) {
    for(uint32_t i = 0; i < graph.numberOfNodes; i++){
        costs[i] = UINT32_MAX;
    }
    costs[src] = 0;
    auto costComp = [this](const uint32_t& a, const uint32_t& b) { return costs[a] < costs[b];};
    std::priority_queue<uint32_t, std::vector<uint32_t>, std::function<bool(std::uint32_t, std::uint32_t)>> priorityQueue(costComp);
    auto& nodes = graph.nodes;
    auto& edges = graph.edges;
    priorityQueue.push(src);
    while(!priorityQueue.empty()){
        uint32_t currentNode = priorityQueue.top();
        priorityQueue.pop();
        if(currentNode==target)
            return costs[target];
        uint32_t begin = nodes[currentNode].offset;
        uint32_t end = nodes[currentNode+1].offset;
        for(int i = begin; i < end; ++i){
            alg_eng::Graph::Edge& currentEdge = edges[i];
            if(costs[currentEdge.target] > costs[currentNode] + currentEdge.weight){
                costs[currentEdge.target] = costs[currentNode] + currentEdge.weight;
                priorityQueue.emplace(currentEdge.target);
                std::cout << priorityQueue.size() << std::endl;
            }
        }
    }
    return costs[target];
}

bool alg_eng::Dijkstra::costCompare(const uint32_t &first, const uint32_t &second) {
    return costs[first] < costs[second];
}

alg_eng::Dijkstra::Dijkstra(const alg_eng::Graph &graph) : graph(graph) {costs.reserve(graph.numberOfNodes);}

