/** @file graphl.cpp */

#include "graphl.h"
#include <iomanip>  // for setw
using namespace std;

/**
 * Default constructor
 */
GraphL::GraphL() {
    // Initialize the array of graph nodes
    for (int i = 0; i < MAXNODES; i++) {
        node_arr[i].data = NULL;
        node_arr[i].edgeHead = NULL;
        node_arr[i].visited = false;
    }
}

/**
 * Destructor
*/
GraphL::~GraphL() {
    // Cycle through each node and delete the adjacency list
    for (int i = 1; i < (size + 1); i++) {
        // Delete the NodeData
        delete(node_arr[i].data);

        // Create some variable for traversing & deleted in the linked adjacancy node list
        EdgeNode* cur = node_arr[i].edgeHead;
        EdgeNode* tmp = NULL;

        while(cur != NULL) {
            // Set the tmp pointer to the next in the adj list
            tmp = cur->nextEdge;

            // delete current node and then set cur to tmp
            delete(cur);
            cur = tmp;
        }
    }
}

/**
 * Function takes the give ifstream, from input file in driver, and build's this object's node array adjacency list
 * Updates data member: node_arr[], size
 */
void GraphL::buildGraph(ifstream& input) {
    // Make sure we aren't at the end of the file before trying to store more info
    if (input.eof())
	    return;
    
    // First line will be number of nodes
    input >> size;

    // If more than maximum nodes is given, only take up to the max
    if (size > MAXNODES) {
        size = MAXNODES;
    }

    // Make sure we aren't at the end of the file before trying to store more info
    if (input.eof())
	    return;

    // Store each of the locations into the data array
    // Starting at index 1
    char loc_name[256];
    input.getline(loc_name, 256);  // move to next line

    for (int n = 1; n < (size + 1); n++) {
        // Make sure we aren't at the end of the file before trying to store more info
        if (input.eof())
	        return;
        input.getline(loc_name, 256);
        node_arr[n].data = new NodeData(loc_name);
    }

    // Then store the weights from node to node in the adjacency matrix
    int from, to = 0;
    while (true) {
        input >> from;
        input >> to;

        // Once we've receive the end of the node weights, stop
        if (from == 0) break;

        insertAdjNode(from, to);
    }

    return;
}

/**
 * Helper function for buildArray which inserts an adjacent node into the adjacency list
*/
void GraphL::insertAdjNode(int from, int to) {
    // First create a new EdgeNode object to insert
    EdgeNode* new_edge = new EdgeNode();
    new_edge->adjGraphNode = to;
    new_edge->nextEdge = NULL;

    // If there is no (non NULL) head in the from node's edgeHead, simply have new_edge be the head
    if (node_arr[from].edgeHead == NULL) {
        node_arr[from].edgeHead = new_edge;
        return;
    }

    // Otherwise, insert it before the existing head
    new_edge->nextEdge = node_arr[from].edgeHead;
    node_arr[from].edgeHead = new_edge;
    return;
}

/**
 * Displays each node information and edge in the graph, using cout & setw (for formatting)
*/
void GraphL::displayGraph() {
    // Initialize a var to be used to keep track of current pointer in linked adj list
    EdgeNode* cur = NULL;

    cout << "Graph:" << endl;
    for (int i = 1; i < (size + 1); i++) {
        // Cout the information about the node
        cout << "Node " << setw(8) << left << i << *(node_arr[i].data) << endl;
        cur = node_arr[i].edgeHead;

        // Cout the node's edges
        while (cur != NULL) {
            cout << setw(7) << right << "edge " << i << " " << cur->adjGraphNode << endl;
            cur = cur->nextEdge;
        }
    }
}

/**
 * Makes a depth-first search and displays each node in depth-first order
*/
void GraphL::depthFirstSearch() {
    cout << "Depth-first ordering: ";
    for (int i = 1 ; i < (size + 1); i++) {
        dfsHelper(i);
    }
    cout << endl;
}

/**
 * Helper function for depthFirstSearch
 * Will cout in depth-first order, using stack (recursive calls)
*/
void GraphL::dfsHelper(int node) {
    // If the node has already been visited - nothing else to do here
    if (node_arr[node].visited == true)
        return;

    // cout the node, mark as visited
    cout << node << " ";
    node_arr[node].visited = true;

    // Create a cursor to keep track of position in adj list
    EdgeNode* cur = node_arr[node].edgeHead;

    // Cycle through all adj nodes
    // When a non visited node is found, recursively call this function to evaluate as stack for depth-first search
    while (cur != NULL) {
        dfsHelper(cur->adjGraphNode);
        // Move cursor forward
        cur = cur->nextEdge;
    }
}