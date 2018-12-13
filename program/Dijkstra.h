//
// Created by sokol on 21.11.18.
//

#ifndef PROGRAM_DIJKSTRA_H
#define PROGRAM_DIJKSTRA_H

#include "Graph.h"
#include "tuple"

namespace alg_eng{
	typedef size_t NodeId;
	typedef size_t EdgeId;
    class Dijkstra {
    	class PQElement {
    	public:
    		NodeId id;
    		size_t cost;
    		bool operator <(const PQElement& rhs) const
			{
    			return cost > rhs.cost;
			}
			PQElement(NodeId id, size_t cost);
    	};
    private:
        alg_eng::Graph graph;
        std::vector<size_t> costs;
    public:
        Dijkstra(const Graph &graph);
        double shortestPath(NodeId src, NodeId target);
    };

}



#endif //PROGRAM_DIJKSTRA_H
