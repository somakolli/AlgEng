//
// Created by sokol on 21.11.18.
//

#ifndef PROGRAM_DIJKSTRA_H
#define PROGRAM_DIJKSTRA_H

#include "Graph.h"

namespace alg_eng{
    class Dijkstra {
    private:
        alg_eng::Graph graph;
        std::vector<uint32_t> costs;
        bool costCompare(const uint32_t& first, const uint32_t& second);
    public:
        Dijkstra(const Graph &graph);
        uint32_t shortestPath(uint32_t src, uint32_t target);
    };

}



#endif //PROGRAM_DIJKSTRA_H
