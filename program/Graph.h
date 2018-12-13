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
            std::size_t osmId, height;
            double longitude, latitude;
        };
        struct Edge{
            std::size_t source, target;
            std::size_t weight, type, maxSpeed;
        };
    public:
        void loadGraph(std::string path);
        void setOffset();
        std::size_t numberOfNodes;
        std::size_t numberOfEdges;
        std::vector<Node> nodes;
        std::vector<Edge> sourceEdges;
        std::vector<Edge> targetEdges;
        std::vector<size_t> sourceOffset;
        std::vector<size_t> targetOffset;
    };
}

#endif //PROGRAM_GRAPH_H