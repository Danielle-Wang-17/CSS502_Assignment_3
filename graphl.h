
#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <fstream>
#include <iostream>
using namespace std;

int const MAXNODES_L = 101;
class GraphL
{
public:
    // Constructor and Destructor
    GraphL();
    ~GraphL();

    // Functions
    void buildGraph(ifstream &);
    // void depthFirstSearch();
    // void displayGraph();

private:
    int numofNodes_l;
    struct EdgeNode; // struct declaration
    struct GraphNode
    {
        EdgeNode *edgeHead; // head of the list of edges
        NodeData *data;     // data information about each node
        bool visited;
    };
    GraphNode node_array[MAXNODES_L];

    struct EdgeNode
    {
        int adjGraphNode;   // subscript of the adjacent graph node
        EdgeNode *nextEdge; // next node
    };

    // Delete object
    void makeEmpty();

    // helper for depthFirstSearch()
    // void depthFirstSearchHelper(int v);
};

#endif // GRAPHL_H