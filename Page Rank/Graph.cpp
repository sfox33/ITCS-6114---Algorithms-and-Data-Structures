#include "Graph.h"

/**
 * Basic implementation of a graph data structure.
 * @author Sean Fox
 * @date 11/21/17
 */

Graph::Graph() {
    numNodes = 0;
}

Graph::~Graph() {

}

/**
 * Returns the vector of nodes within the graph
 */
std::vector<Node*> Graph::getNodes() {
    return nodes;
}

/**
 * Appends a node onto the graph
 * @input newNode - Pointer to a node to be added to graph
 */
void Graph::addNode(Node* newNode) {
    nodes.insert(nodes.end(),newNode);
    numNodes++;
}

/**
 * Returns the number of nodes within the graph
 */
int Graph::getNumNodes() {
    return numNodes;
}
