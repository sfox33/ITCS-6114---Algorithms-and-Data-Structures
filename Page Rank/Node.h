#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>

/**
 * Header for Node.cpp
 * @author Sean Fox
 * @date 11/21/17
 */


class Node {
    public:
        Node();
        ~Node();
        float getRank();
        void setRank(float inRank);
        void addInNeigh(Node* neigh);
        void addOutNeigh(Node* neigh);
        std::vector<Node*> getInNeigh();
        std::vector<Node*> getOutNeigh();
        int getNumInNeigh();
        int getNumOutNeigh();
        void setStr(std::string str);
        std::string toString();
    private:
        float pageRank;     //Page rank of node
        std::vector<Node*> inNeighbors;     //Holds the neighbors with inward directed edges
        std::vector<Node*> outNeighbors;    //Holds the neighbors with outward directed edges
        int numInNeigh;     //Holds the number of neighbors with inward directed edges
        int numOutNeigh;    //Holds the number of neighbors with outward directed edges
        std::string name;   //Hold the name of the node
};

#endif
