#include "Node.h"
#include <iostream>

/**
 * Basic implementation of a node for a directed graph
 * @author Sean Fox
 * @date 11/21/17
 */

Node::Node(){
    this->pageRank = 1.0f;
    numInNeigh = numOutNeigh = 0;
    name = "";
}

Node::~Node(){

}

float Node::getRank(){
    return pageRank;
}

/**
 * Sets the page rank.  Used for testing only.
 * @input inRank - rank to be assigned
 */
void Node::setRank(float inRank){
    this->pageRank = inRank;
}

/**
 * Adds a neighbor to the node whose edge leads towards the node
 * @input neigh - pointer to the neighbor
 */
void Node::addInNeigh(Node* neigh){
    inNeighbors.insert(inNeighbors.end(), neigh);
    this->numInNeigh+=1;
}

/**
 * Adds a neighbor to the node whose edge leads towards the neighbor
 * @input neigh - pointer to the neighbor
 */
void Node::addOutNeigh(Node* neigh){
    outNeighbors.insert(outNeighbors.end(), neigh);
    this->numOutNeigh+=1;
}

/**
 * Returns the vector of neighbors with inward edges
 */
std::vector<Node*> Node::getInNeigh(){
    return inNeighbors;
}

/**
 * Returns the vector of neighbors with inward edges
 */
std::vector<Node*> Node::getOutNeigh(){
    return outNeighbors;
}

/**
 * Returns the number of neighbors with inward edges
 */
int Node::getNumInNeigh() {
    return numInNeigh;
}

/**
 * Returns the number of neighbors with outward edges
 */
int Node::getNumOutNeigh() {
    return numOutNeigh;
}

/**
 * Sets the name of the node
 * @input str - string holding the node's name
 */
void Node::setStr(std::string str) {
    this -> name = str;
}

/**
 * Returns the name of the node
 */
std::string Node::toString() {
    return name;
}
