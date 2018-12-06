//
// Created by sokol on 17.11.18.
//

#ifndef PROGRAM_GRAPH_H
#define PROGRAM_GRAPH_H

#include <string>
#include <vector>
#include <array>

namespace alg_eng{
    class Graph{
    public:
        struct Node{
            uint32_t osmId, height, offset;
            double longitude, latitude;
        };
        struct Edge{
            uint32_t source, target, weight, type, maxSpeed;
        };
    public:
        void loadGraph(std::string path);
        std::uint64_t numberOfNodes;
        std::uint64_t numberOfEdges;
        std::vector<Node> nodes;
        std::vector<Edge> edges;
    };
}

#endif //PROGRAM_GRAPH_H