/** @file graphl.cpp */

#ifndef GRAPHL_G
#define GRAPHL_G
#include <iostream>
#include "nodedata.h"
using namespace std;

struct EdgeNode;         // forward reference for the compiler
struct GraphNode {       // structs used for simplicity, use classes if desired
    EdgeNode* edgeHead;  // head of the list of edges
    NodeData* data;      // data information about each node
    bool visited;
};
struct EdgeNode {
    int adjGraphNode;  // subscript of the adjacent graph node
    EdgeNode* nextEdge;
};

class GraphL {
   public:
    GraphL();   // Default constructor
    ~GraphL();  // Deconstructor
    void buildGraph(ifstream& input); // Pass the ifstream, from file in driver file, by reference
    void displayGraph(); // Displays each node information and edge in the graph
    void depthFirstSearch(); // Makes a depth-first search and displays each node in depth-first order

   private:
    static const int MAXNODES = 101;  // constant for max nodes (101 since not using index 0)

    GraphNode node_arr[MAXNODES]; // array that contains all GraphNodes
    int size; // keep track of the number of nodes

    void insertAdjNode(int from, int to); // Inserts an adjacent node into the adjency list
    void dfsHelper(int node); // Helper function for depthFirstSearch()
};

#endif