//
// Created by sokol on 17.11.18.
//
#include<iostream>
#include <fstream>
#include "Graph.h"
#include "ctime"

void alg_eng::Graph::loadGraph(std::string fileName) {
    clock_t begin = clock();
    std::ifstream graphFileStream;
    graphFileStream.open("/home/sokol/Uni/AlgEng/program/" + fileName);
    std::string line;
    uint64_t i = 5;
    while (i>0){
        i--;
        std::getline(graphFileStream, line);
    }
    std::getline(graphFileStream, line);
    numberOfNodes = static_cast<uint64_t>(std::stol(line));
    std::getline(graphFileStream, line);
    numberOfEdges = static_cast<uint64_t>(std::stol(line));
    edges.reserve(numberOfEdges);
    nodes.reserve(numberOfNodes+1);
    i = numberOfNodes + 1;
    uint32_t id;
    Node node{};
    while(--i > 0 &&
        (graphFileStream >> id >> node.osmId >> node.longitude >> node.latitude >> node.height)){
        node.offset = 0;
        nodes.emplace_back(node);
    }
    nodes.emplace_back(node);
    nodes[0].offset = 0;
    Edge edge{};
    //read the first edge before going into the while loop
    graphFileStream >> edge.source >> edge.target >> edge.weight >> edge.type >> edge.maxSpeed;
    edges.emplace_back(edge);
    uint32_t offset = 1;
    uint32_t j = 0;
    i = 1;
    while(graphFileStream >> edge.source >> edge.target >> edge.weight >> edge.type >> edge.maxSpeed){
        edges.emplace_back(edge);
        // set the offset to all nodes which have no edge
        for (int32_t k = edges[i].source - edges[i-1].source; k>0; k--){
            j++;
            nodes[j].offset = offset;
        }
        i++;
        offset++;
    }
    nodes[numberOfNodes].offset = offset;
    graphFileStream.close();
    clock_t end = clock();
    double elapsed_secs = double(end-begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << std::endl;
}
