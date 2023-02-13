/** @file graphm.cpp */

#include "graphm.h"
#include <climits>  // for INT_MAX
#include <iomanip>  // for setw
#include <sstream>  // for stringstream
#include <string>   // for to_string
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
 * Destructor (not much to do because nothing was dynamically allocated)
*/
GraphM::~GraphM() { }

/**
 * Function takes the give ifstream, from input file in driver, and build's this object's node list and adjacency matrix
 * Updates data members: size, data[], C[][]
 */
void GraphM::buildGraph(ifstream& input) {
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
    char loc_name[256];  // Question - do we need to be concerned with length of node nodes?
    input.getline(loc_name, 256);  // Why do I have to do this to get to the new line lol

    for (int n = 1; n < (size + 1); n++) {
        // Make sure we aren't at the end of the file before trying to store more info
        if (input.eof())
	        return;
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
void GraphM::insertEdge(int from, int to, int weight) {
    C[from][to] = weight;
    size++;
}

/**
 * Function removes an edge from the graph
 * Updates data member C[][]
*/
void GraphM::removeEdge(int from, int to) {
    C[from][to] = INT_MAX;
    size--;
}

/**
 * Function that find the shortest path from each node to another
*/
void GraphM::findShortestPath() {
    // For each starting location, find the shortest path to all possible destinations using helper function
    for (int loc = 1; loc < size + 1; loc++) {
        findShortestPathFromSource(loc);
    }
}

/**
 * Helper function that finds shortest path from given source node to others
*/
void GraphM::findShortestPathFromSource(int source) {
    // First establish the initial position, starting at source (source to source distance is 0)
    
    // Create an array to keep track of shortest path
    // I think I can remove this and just pull directly from T to optimize. Will do that after testing
    TableType path_arr[size + 1]; // size + 1 since not going to use index 0
    
    // Initialize this array
    for (int i = 1 ; i < size + 1 ; i++) {
        path_arr[i].dist = INT_MAX;
        path_arr[i].visited = false;
        path_arr[i].path = 0;
    }
    path_arr[source].dist = 0;

    // Some variables to be used to keep track of shortest path & which location to go to next (the new current location)
    int curr_location = 0;
    int min_nonvisited_path = INT_MAX;

    // Keep track of if we found a non visited adjacent location
    bool found_nonvisited = false;

    // Loop through all locations until we've visited all or there's no more connected path
    for (int loc = 1; loc < size + 1 ; loc++) {
        // Find the shortest path at this point, that is not visited to be the next current location
        for (int i = 1 ; i < size + 1 ; i++) {
            // Find the minimum path at this point
            if (path_arr[i].visited == false && path_arr[i].dist < min_nonvisited_path) {
                found_nonvisited = true;
                curr_location = i;
                min_nonvisited_path = path_arr[i].dist;
            }
        }

        // If there was nothing less than INT_MAX when looking for max, there's no more connected locations that we haven't visited already so we're done
        if (!found_nonvisited) {
            break;
        }

        // Mark the location as visited (aka we are currently there)
        path_arr[curr_location].visited = true;

        // // Print out the array for debugging
        // cout << "Current: " << curr_location << " | " << "[ ";
        // for (int i = 1; i < size + 1; i++) {
        //     cout << "(" << path_arr[i].visited << ", " << path_arr[i].path << ", " << path_arr[i].dist << ") , ";
        // }
        // cout << "] " << endl;

        // Go through adjacent nodes and update the shortest path (so far) to that node
        for (int adj_loc = 1 ; adj_loc < size + 1 ; adj_loc++) {
            // If there's a path between current loc and (potential) adjacent location
            if (C[curr_location][adj_loc] < INT_MAX) {
                // The shortest path to the adjacent node is the minimum of:
                // 1. Existing shortest path to that adj location
                // 2. Shortest path to the current location + the weight of traveling from current location -> adj location (aka this new path is faster)
                
                // Update the dist to the adjacent location if it fits criterea 2 above
                // Also update the adj location's path since coming from this current node was faster than existing path
                if ((path_arr[curr_location].dist + C[curr_location][adj_loc]) < path_arr[adj_loc].dist) {
                    path_arr[adj_loc].dist = path_arr[curr_location].dist + C[curr_location][adj_loc];
                    path_arr[adj_loc].path = curr_location;
                }
            }
        }

        // Reset the variables that keep track of where to go for next loop!
        min_nonvisited_path = INT_MAX;
        found_nonvisited = false;
    }

    // Once I've traversed all the locations and found shortest path to each from the source, update matrix T to match the path_arr we created
    for (int to = 1; to < size + 1 ; to++) {
        T[source][to].visited = path_arr[to].visited;
        T[source][to].dist = path_arr[to].dist;
        T[source][to].path = path_arr[to].path;
    }
}

/**
 * Function that cout's the path from the given source to destination using Dijkstra's algo
*/
void GraphM::display(int source, int dest) {
    cout << setw(10) << left << "From node"
        << setw(10) << left << "To node"
        << setw(15) << left << "Dijkstra's"
        << setw(15) << left << "Path"
        << endl;
    
    int curr = dest;
    stringstream path_str(""); // Using stringstream so that I can later >> to print out the names of the location

    // Starting at destination, go in reverse until we hit the source or there was not a previous location (aka not connected to source)
    while ((curr != source)) {
        // Add current to the front of the string (since we are going in reverse, but want to print in order)
        if (path_str.str() == "") { // First entry
            path_str.str(to_string(curr));
        } else { // Additional entry
            path_str.str(to_string(curr) + " " + path_str.str());
        }
        curr = T[source][curr].path;

        // If current is now 0, this means there was no a connection
        if (curr == 0) {
            cout << setw(10) << left << source
                << setw(10) << left << dest
                << setw(15) << left << "---"
                << setw(15) << left << ""
                << endl;
            return;
        }
    }

    // If I made it out of the while loop, I found the source!
    path_str.str(to_string(curr) + " " + path_str.str());

    // Print out path information
    cout << setw(10) << left << source
        << setw(10) << left << dest
        << setw(15) << left << T[source][dest].dist
        << setw(15) << left << path_str.str()
        << endl;

    // Now display the names of the locations in the path, in order
    int path_index = 0;

    while(!path_str.eof()) {
        path_str >> path_index;
        cout << data[path_index] << endl;
    }
}

/**
 * Function that cout's all the paths from all sources to destinations
*/
void GraphM::displayAll() {
    cout << setw(25) << left << "Description"
        << setw(10) << left << "From node"
        << setw(10) << left << "To node"
        << setw(15) << left << "Dijkstra's"
        << setw(15) << left << "Path"
        << endl;

    for (int source = 1; source < size + 1 ; source++) {
        cout << data[source] << endl;
        for (int dest = 1; dest < size + 1 ; dest++) {
            if (source == dest) // Don't need to show source to itself
                continue; 
            displayAllHelper(source, dest);
        }
    }
}

/**
 * Helper function for displayAll() that couts the shortest path and path into in expected format
*/
void GraphM::displayAllHelper(int source, int dest) {
    int curr = dest;
    string path_str = "";

    // Starting at destination, go in reverse until we hit the source or there was not a previous location (aka not connected to source)
    while ((curr != source)) {
        // Add current to the front of the string (since we are going in reverse, but want to print in order)
        path_str = to_string(curr) + " " + path_str;
        curr = T[source][curr].path;

        // If current is now 0, this means there was no a connection
        if (curr == 0) {
            cout << setw(25) << left << ""
                << setw(10) << left << source
                << setw(10) << left << dest
                << setw(15) << left << "---"
                << setw(15) << left << ""
                << endl;
            return;
        }
    }

    // If I made it out of the while loop, I found the source!
    path_str = to_string(source) + " " + path_str;

    cout << setw(25) << left << ""
        << setw(10) << left << source
        << setw(10) << left << dest
        << setw(15) << left << T[source][dest].dist
        << setw(15) << left << path_str
        << endl;
}