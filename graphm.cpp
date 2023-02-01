#include "graphm.h"

#include <climits>
using namespace std;

/**
 * Default constructor
 */
GraphM::GraphM() {
    // Set everything in adjacency matrix to INF
    // Initialize all TableTypes in T
    for (int from = 0; from < MAXNODES; from++) {
        for (int to = 0; to < MAXNODES; to++) {
            C[from][to] = INT_MAX;
            T[from][to].visited = false;
            T[from][to].dist = 0;
            T[from][to].path = 0;
        }
    }

    // Set the # nodes in graph to 0
    size = 0;
}

/**
 * Function takes the give ifstream, from input file in driver, and build's this object's node list and adjacency matrix
 * Updates data members: size, data[], C[][]
 */
void GraphM::buildGraph(ifstream& input) {
    // First line will be number of nodes
    input >> size;

    // Store each of the locations into the data array
    // Starting at index 1
    char loc_name[256];  // Question - do we need to be concerned with length of node nodes?
    input.getline(loc_name, 256);  // Why do I have to do this to get to the new line lol

    for (int n = 1; n < (size + 1); n++) {
        input.getline(loc_name, 256);
        data[n] = NodeData(loc_name);
    }

    // Then store the weights from node to node in the adjacency matrix
    int from, to, weight = 0;
    while (true) {
        input >> from;
        input >> to;
        input >> weight;

        // Once we've receive the end of the node weights, stop
        if (from == 0) break;

        // Put into adjacency matrix
        C[from][to] = weight;
    }

    return;
}

/**
 * Function adds an edge into the graph
 * Updates data member C[][]
*/
void insertEdge(int from, int to, int weight) {
    C[from][to] = weight;
}

/**
 * Function removes an edge from the graph
 * Updates data member C[][]
*/
void removeEdge(int from, int to) {
    C[from][to] = INT_MAX;
}