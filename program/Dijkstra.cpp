//
// Created by sokol on 21.11.18.
//

#include <queue>
#include <functional>
#include <iostream>
#include "Dijkstra.h"

double alg_eng::Dijkstra::shortestPath(NodeId src, NodeId target) {
    for(size_t i = 0; i < graph.numberOfNodes; i++){
        costs.emplace_back(SIZE_MAX);
    }
    costs[src] = 0;
    std::priority_queue<PQElement> priorityQueue;
    auto& nodes = graph.nodes;
    auto& sourceOffset = graph.sourceOffset;
    auto& edges = graph.sourceEdges;
    priorityQueue.emplace(src, 0);
    while(!priorityQueue.empty()){
        PQElement currentNode = priorityQueue.top();
        priorityQueue.pop();
        if((currentNode.id)==target)
            return (currentNode.cost);
        std::size_t begin = sourceOffset[currentNode.id];
        std::size_t end = sourceOffset[currentNode.id+1];
        for(size_t i = begin; i <= end; ++i){
            alg_eng::Graph::Edge& currentEdge = edges[i];
            auto addedCost = currentNode.cost + currentEdge.weight;
            if(costs[currentEdge.target] > addedCost){
                costs[currentEdge.target] = addedCost;
                priorityQueue.emplace(currentEdge.target, addedCost);
            }
        }
    }
    return costs.at(target);
}


alg_eng::Dijkstra::Dijkstra(const alg_eng::Graph &graph) : graph(graph) {costs.reserve(graph.numberOfNodes);}

alg_eng::Dijkstra::PQElement::PQElement(alg_eng::NodeId id, size_t cost) : id(id), cost(cost) {}
