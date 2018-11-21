//
// Created by sokol on 17.11.18.
//
#include<iostream>
#include <fstream>
#include "graph.h"
#include "ctime"

void alg_eng::Graph::loadGraph(std::string path) {
    clock_t begin = clock();
    std::ifstream graphFileStream;
    graphFileStream.open("/home/sokol/Uni/AlgEng/program/bw.graph");
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
    nodes.reserve(numberOfNodes);
    i = numberOfNodes + 1;
    uint32_t id;
    Node node{};
    while(--i > 0 &&
        (graphFileStream >> id >> node.osmId >> node.longitude >> node.latitude >> node.height)){
        nodes.emplace_back(node);
    }
    i = 0;
    Edge edge{};
    nodes[0].offset = 0;
    while(graphFileStream >> edge.source >> edge.target >> edge.weight >> edge.type >> edge.maxSpeed){
        edges.emplace_back(edge);
        nodes[edge.source+1].offset++;
    }
    graphFileStream.close();
    clock_t end = clock();
    double elapsed_secs = double(end-begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs;
}
