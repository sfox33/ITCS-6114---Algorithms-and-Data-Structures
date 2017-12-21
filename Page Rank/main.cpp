#include <iostream>
#include "Node.h"
#include "Graph.h"
#include <string>

/**
 * Calculates the Page Rank for the predetermined graphs.  Dampening factor and
 * number of rounds are determined by user.
 * @author Sean Fox
 * @date 11/21/17
 */

float calcPageRank(Node &page, int numPages, float dampening);

int main(){
    int graphSize;      //Size of the graph
    int maxGraph = 20;
    float newRank[maxGraph];    //Used to hold the new ranks per round for each graph
    float dampening;        //Holds the dampening value for computation
    int numRounds;          //Holds the iterations for each Page Rank calculation
    std::vector<Node*> nodes;   //Holds the nodes of a graph

    std::cout << "Enter the dampening value for these calculations: ";
    std::cin>>dampening;

    if(dampening <= 0 || dampening >= 1){
        std::cout << "Value is not between 0 and 1.  Defaulting to 0.85" << std::endl;
        dampening = 0.85;
    }

    std::cout << "Enter the rounds per calculation: ";
    std::cin>>numRounds;

    if(numRounds <= 0){
        std::cout << "Value is not a positive integer.  Defaulting to 100" << std::endl;
        numRounds = 100;
    }

    //Setup for first graph.
    Node g1_1, g1_2, g1_3, g1_4;
    Graph g1;

    g1_1.addOutNeigh(&g1_2);
    g1_1.addOutNeigh(&g1_4);
    g1_1.addInNeigh(&g1_3);
    g1_1.setStr("1");

    g1_2.addOutNeigh(&g1_4);
    g1_1.addInNeigh(&g1_1);
    g1_1.addInNeigh(&g1_3);
    g1_2.setStr("2");

    g1_3.addOutNeigh(&g1_1);
    g1_3.addOutNeigh(&g1_2);
    g1_3.addInNeigh(&g1_4);
    g1_3.setStr("3");

    g1_4.addOutNeigh(&g1_3);
    g1_1.addInNeigh(&g1_1);
    g1_1.addInNeigh(&g1_2);
    g1_4.setStr("4");

    g1.addNode(&g1_1);
    g1.addNode(&g1_2);
    g1.addNode(&g1_3);
    g1.addNode(&g1_4);
    graphSize = g1.getNumNodes();
    nodes = g1.getNodes();

    for(int i = 0; i < numRounds; i++) {
        for(int j = 0; j < graphSize; j++) {
            newRank[j] = calcPageRank(*nodes[j],graphSize,dampening);
        }
        for(int k = 0; k < graphSize; k++) {
            nodes[k]->setRank(newRank[k]);
        }
    }

    std::cout << "The page ranks for the first graph with d="<< dampening << " is as follow:\n";
    for(int k = 0; k < graphSize; k++) {
        std::cout << "Node " << nodes[k]->toString() << " has page rank " << nodes[k]->getRank() << ".\n";
    }

    //Setup for second graph.
    Node g2_1, g2_2, g2_3, g2_4, g2_5, g2_6, g2_7, g2_8;
    Graph g2;

    g2_1.addOutNeigh(&g2_7);
    g2_1.addInNeigh(&g2_3);
    g2_1.setStr("1");

    g2_2.addOutNeigh(&g2_6);
    g2_2.addInNeigh(&g2_5);
    g2_2.addInNeigh(&g2_7);
    g2_2.setStr("2");

    g2_3.addOutNeigh(&g2_1);
    g2_3.addOutNeigh(&g2_5);
    g2_3.setStr("3");

    g2_4.addOutNeigh(&g2_6);
    g2_4.addInNeigh(&g2_5);
    g2_4.setStr("4");

    g2_5.addOutNeigh(&g2_2);
    g2_5.addOutNeigh(&g2_4);
    g2_5.addInNeigh(&g2_3);
    g2_5.setStr("5");

    g2_6.addOutNeigh(&g2_8);
    g2_6.addInNeigh(&g2_2);
    g2_6.addInNeigh(&g2_4);
    g2_6.setStr("6");

    g2_7.addOutNeigh(&g2_2);
    g2_7.addOutNeigh(&g2_8);
    g2_7.addInNeigh(&g2_1);
    g2_7.setStr("7");

    g2_8.addInNeigh(&g2_6);
    g2_8.addInNeigh(&g2_7);
    g2_8.setStr("8");

    g2.addNode(&g2_1);
    g2.addNode(&g2_2);
    g2.addNode(&g2_3);
    g2.addNode(&g2_4);
    g2.addNode(&g2_5);
    g2.addNode(&g2_6);
    g2.addNode(&g2_7);
    g2.addNode(&g2_8);
    graphSize = g2.getNumNodes();
    nodes = g2.getNodes();

    for(int i = 0; i < numRounds; i++) {
        for(int j = 0; j < graphSize; j++) {
            newRank[j] = calcPageRank(*nodes[j],graphSize,dampening);
        }
        for(int k = 0; k < graphSize; k++) {
            nodes[k]->setRank(newRank[k]);
        }
    }

    std::cout << "The page ranks for the second graph with d="<< dampening << " is as follow:\n";
    for(int k = 0; k < graphSize; k++) {
        std::cout << "Node " << nodes[k]->toString() << " has page rank " << nodes[k]->getRank() << ".\n";
    }

    //For testing, setup the example graph found in the PowerPoint.
    Node A, B, C, D, E, F;
    Graph test;

    A.setStr("A");
    B.setStr("B");
    C.setStr("C");
    D.setStr("D");
    E.setStr("E");
    F.setStr("F");

    A.addInNeigh(&B);
    A.addInNeigh(&F);
    A.addOutNeigh(&B);
    A.addOutNeigh(&F);

    B.addInNeigh(&A);
    B.addInNeigh(&C);
    B.addInNeigh(&E);
    B.addOutNeigh(&A);
    B.addOutNeigh(&C);

    C.addInNeigh(&B);
    C.addInNeigh(&D);
    C.addOutNeigh(&B);
    C.addOutNeigh(&D);

    D.addInNeigh(&C);
    D.addInNeigh(&E);
    D.addOutNeigh(&C);
    D.addOutNeigh(&E);

    E.addInNeigh(&D);
    E.addInNeigh(&F);
    E.addOutNeigh(&B);
    E.addOutNeigh(&D);
    E.addOutNeigh(&F);

    F.addInNeigh(&A);
    F.addInNeigh(&E);
    F.addOutNeigh(&A);
    F.addOutNeigh(&E);

    test.addNode(&A);
    test.addNode(&B);
    test.addNode(&C);
    test.addNode(&D);
    test.addNode(&E);
    test.addNode(&F);
    graphSize = test.getNumNodes();
    nodes = test.getNodes();

    for(int i = 0; i < numRounds; i++) {
        for(int j = 0; j < graphSize; j++) {
            newRank[j] = calcPageRank(*nodes[j],graphSize,dampening);
        }
        for(int k = 0; k < graphSize; k++) {
            nodes[k]->setRank(newRank[k]);
        }
    }

    std::cout << "The page ranks for the test graph with d="<< dampening << " is as follow:\n";
    for(int k = 0; k < graphSize; k++) {
        std::cout << "Node " << nodes[k]->toString() << " has page rank " << nodes[k]->getRank() << ".\n";
    }

    return 0;
}

/**
 * Calculates the Page Rank for a given node of a graph
 * @input page - a pointer to a graph node
 * @input numPages - the number of pages (nodes) in the graph
 * @input dampening - the dampening factor to be used in calculations.
 */
float calcPageRank(Node &page, int numPages, float dampening) {
    std::vector<Node*> inNeigh = page.getInNeigh();
    float rank = (1.0f-dampening);

    for(int i = 0; i < inNeigh.size(); i++) {
        if(inNeigh[i]->getNumOutNeigh() != 0){
            rank += dampening * (inNeigh[i]->getRank() / inNeigh[i]->getNumOutNeigh());
        }
    }

    return rank;
}
