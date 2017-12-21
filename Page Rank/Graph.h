#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Node.h"

/**
 * Header for Graph.cpp
 * @author Sean Fox
 * @date 11/21/17
 */


class Graph {
    public:
        Graph();
        ~Graph();
        std::vector<Node*> getNodes();
        void addNode(Node* newNode);
        int getNumNodes();
    private:
        std::vector<Node*> nodes;   //Holds the nodes in the graph
        int numNodes;   //Holds the size of the graph
};

#endif
