/** @file graphm.h */

#ifndef GRAPHM_H
#define GRAPHM_H
#include <iostream>
#include "nodedata.h"
using namespace std;

const int MAXNODES = 101;  // constant for max nodes (101 since not using index 0)

/* struct to be used to keep track of shortest distance & path info */
struct TableType {
    bool visited;  // whether node has been visited
    int dist;      // shortest distance from source known so far
    int path;      // previous node in path of min dist
};

class GraphM {
   public:
    GraphM();                                       // Default constuctor
    ~GraphM();                                      // Destructor
    void buildGraph(ifstream& input);               // Pass the ifstream, from file in driver file, by reference
    void insertEdge(int from, int to, int weight);  // Insert an Edge
    void removeEdge(int from, int to);              // Remove an edge
    void findShortestPath();                        // Find the shortest path from all nodes to each other
    void display(int source, int dest);             // Display the shortest path from given source to dest
    void displayAll();                              // Displays the shortest path from every source to dest

   private:
    NodeData data[MAXNODES];          // data for graph nodes
    int C[MAXNODES][MAXNODES];        // Cost array, the adjacency matrix
    int size;                         // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];  // stores visited, distance, path

    void findShortestPathFromSource(int source);  // Helper function for findShortestPath, finds shortest path from source to all other nodes
    void displayAllHelper(int source, int dest);  // Helper function to cout shortest path in expected format
};

#endif