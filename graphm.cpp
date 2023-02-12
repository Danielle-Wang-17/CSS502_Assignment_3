#include "graphm.h"
#include <climits>
#include <iomanip>

// Default constructor
// constructing an empty table and intilizing all the values
GraphM::GraphM()
{
    // setting the numOfNodes to 0
    numOfNodes = 0;

    for (int i = 1; i < MAXNODES; i++)
    {
        for (int j = 1; j < MAXNODES; j++)
        {
            adjMatrix[i][j] = INT_MAX;
            Table[i][j].visited = false;
            Table[i][j].dist = INT_MAX;
            Table[i][j].path = 0;
        }
    }
}

// building graph node ino an adj matrix of edges between the node and reading from a file
void GraphM::buildGraph(ifstream &input)
{
    // read from data file
    input >> numOfNodes;      // setting the number of nodes
    string nodeName = "";     // each node name
    getline(input, nodeName); // reading lines

    for (int i = 1; i <= numOfNodes; ++i)
    {
        data[i].setData(input); // setting node names
    }

    int from, to, cost;

    while (input >> from >> to >> cost)
    {
        if (from == 0)
        {
            break; // reading a file until the node reaches o
        }

        adjMatrix[from][to] = cost; // setting the adj matrix
    }
}

// This function finds the shortest path between every node to every other node in the graph using the Dijkstra's algorithm
void GraphM::findShortestPath()
{

    for (int source = 1; source <= numOfNodes; source++) // The loop iterates over all nodes, where the variable source is the source node for each iteration.
    {
        Table[source][source].dist = 0;
        Table[source][source].visited = true;

        for (int i = 1; i <= numOfNodes; i++) // The inner for loop then initializes the distances and paths
        {
            if (adjMatrix[source][i] != INT_MAX)
            {
                Table[source][i].dist = adjMatrix[source][i];
                Table[source][i].path = source;
            }
        }
        int min = INT_MAX;
        int v = 0;   // this is the smallest vertex, v - marking v as visited
        while (true) // finding the smallest weight
        {
            for (int i = 1; i <= numOfNodes; i++) // find closest child and continue search
            {
                if (!Table[source][i].visited && (adjMatrix[source][i] < min))
                {
                    min = adjMatrix[source][i];
                    v = i;
                }
            }

            if (v == 0)
            {
                break; // end loop
            }

            Table[source][v].visited = true; // this node is visited

            for (int w = 1; w <= numOfNodes; w++) // w - marking w as not visited
            {
                if (Table[source][w].visited)
                {
                    continue;
                }

                if (adjMatrix[v][w] == INT_MAX)
                {
                    continue;
                }

                if (v == w)
                {
                    continue;
                }

                if (Table[source][w].dist > Table[source][v].dist + adjMatrix[v][w])
                {
                    Table[source][w].dist = Table[source][v].dist + adjMatrix[v][w];
                    Table[source][w].path = v;
                }
            }

            int min = INT_MAX;
            v = 0;
        }

        while (v != 0)
            ; // end loop
    }
}

// Inserting an edge into a graph between the given two nodes
bool GraphM::insertEdge(int from, int to, int dist)
{
    // confirm the insert is possible
    if (from > numOfNodes || from < 1)
    {
        return false;
    }

    if (to > numOfNodes || to < 1)
    {
        return false;
    }

    if (dist != 0 && from == to)
    {
        return false;
    }

    if (dist < 0)
    {
        return false;
    }

    adjMatrix[from][to] = dist; // edge will be inserted here
    findShortestPath();         // repeat the Dijkstra's algorithm with changes

    return true;
}

// Removing an edge between the given two nodes
bool GraphM::removeEdge(int from, int to)
{
    // confirm whether the removal of the edge is possible
    if (from > numOfNodes || from < 1)
    {
        return false;
    }

    if (to > numOfNodes || to < 1)
    {
        return false;
    }

    adjMatrix[from][to] = INT_MAX; // edge will be removed
    findShortestPath();            // repeat thhe Dijkstra's algorithm with changes

    return true;
}

// Uses cout to show that the alogorithm works
// Uses the findPath()
void GraphM::displayAll()
{
    // print the table titles
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
         << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

    for (int from = 1; from <= numOfNodes; from++)
    {
        cout << data[from] << endl // print the node name
             << endl;

        for (int to = 1; to <= numOfNodes; to++)
        {
            if (Table[from][to].dist != 0)
            {
                cout << setw(27) << from; // print from node
                cout << setw(10) << to;   // print to node

                if (Table[from][to].dist == INT_MAX)
                {
                    cout << setw(12) << "----" << endl;
                }
                else
                {
                    cout << setw(12) << Table[from][to].dist; // no adj nodes and distance
                    cout << setw(10);

                    findPath(from, to); // call the findPath() helper function
                    cout << endl;
                }
            }
        }
    }
}

// Uses cout to display the shortest distance with path info between the from Node to the to Node
// Uses  findPath() helper function
// Uses  findData() helper function

void GraphM::display(int from, int to)
{
    if ((from > numOfNodes || from < 1) || (to > numOfNodes || to < 1))
    {
        cout << setw(7) << from << setw(7) << to; // print the data from and to
        cout << setw(15) << "----" << endl;       // not a valid outcome
        return;
    }

    cout << setw(7) << from << setw(7) << to; // print the data from and to

    if (Table[from][to].dist != INT_MAX) // adj check
    {
        cout << setw(12) << Table[from][to].dist << setw(15); // printing the distance
        findPath(from, to);                                   // call the helper function
        cout << endl;
        findData(from, to); // call the helper function
    }
    else
    {
        cout << setw(15) << "----" << endl; // no adj node
    }

    cout << endl;
}

// This is the helper function for display()
// The function will find the data for the given edge distance recursively
void GraphM::findData(int from, int to)
{
    if (Table[from][to].dist == INT_MAX)
    {
        return; // no data is available
    }

    if (from == to)
    {
        cout << data[to] << endl; // print the data
        return;
    }

    int nodeData = to;         // assign node to nodeData
    to = Table[from][to].path; // calling the helper function
    findData(from, to);
    cout << data[nodeData] << endl // print the data
         << endl;
}

// Helper function for display() and displayAll() functions
// The function finds the path for a given edge recursively
void GraphM::findPath(int from, int to)
{
    if (Table[from][to].dist == INT_MAX)
    {
        return; // no path
    }

    if (from == to)
    {
        cout << to << " "; // print the data
        return;
    }

    int dataPath = to; // asign path to dataPath
    to = Table[from][to].path;
    findPath(from, to);
    cout << dataPath << " "; // print path
}
