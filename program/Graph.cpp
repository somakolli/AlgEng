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
    sourceEdges.reserve(numberOfEdges);
    nodes.reserve(numberOfNodes+1);
    sourceOffset.reserve(numberOfNodes+1);
    i = numberOfNodes + 1;
    uint32_t id;
    Node node{};
    while(--i > 0 &&
        (graphFileStream >> id >> node.osmId >> node.longitude >> node.latitude >> node.height)){
        nodes.emplace_back(node);
    }
    nodes.emplace_back(node);
    Edge edge{};
    while(graphFileStream >> edge.source >> edge.target >> edge.weight >> edge.type >> edge.maxSpeed){
        sourceEdges.emplace_back(edge);
    }
    graphFileStream.close();
    setOffset();
    clock_t end = clock();
    double elapsed_secs = double(end-begin) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << std::endl;
    std::cout << numberOfNodes << ":" << nodes.size() << std::endl;
    std::cout << numberOfEdges << ":" << sourceEdges.size() << std::endl;
}

void alg_eng::Graph::setOffset() {
	for(size_t i = 0; i < numberOfNodes; ++i ){
		sourceOffset.emplace_back(0);
	}
    for(size_t j = numberOfEdges; j-- > 0;){
        auto& edge = sourceEdges[j];
        sourceOffset.at(edge.source) = j;
    }
    for(size_t i = 1; i < numberOfNodes; i++){
        if(sourceOffset[i]==0)
        	sourceOffset[i] = sourceOffset[i+1];
    }
    sourceOffset.emplace_back(numberOfEdges);
}
