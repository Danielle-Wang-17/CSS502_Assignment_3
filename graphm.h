#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <fstream>
#include <iostream>

using namespace std;

int const MAXNODES = 101; // constant size for Table and ajdMatrix table

class GraphM
{
public:
    // Default Constructor
    GraphM();

    // Functions
    void buildGraph(ifstream &);
    void findShortestPath();
    bool insertEdge(int from, int to, int dist);
    bool removeEdge(int from, int to);
    // void display(int from, int to);
    // void displayAll();

private:
    struct TableType
    {
        bool visited; // check if node is visited
        int dist;     // shortest distance from source known so far
        int path;     // previous node in path of min dist
    };

    NodeData data[MAXNODES];             // data for graph nodes
    int adjMatrix[MAXNODES][MAXNODES];   // cost array, the adjacency matrix
    int numOfNodes;                      // number of nodes in the graph
    TableType Table[MAXNODES][MAXNODES]; // stores visited, distance, path
};

#endif // GRAPHM_H