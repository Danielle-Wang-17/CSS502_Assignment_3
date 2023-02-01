#include "graphm.h"

// Default constructor
// constructing an empty table and intilizing all the values
GraphM::GraphM()
{
    // setting the size to 0
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
    string nodeName = "";       // each node name
    getline(input, nodeName); // reading lines

    for (int i = 1; i <= numOfNodes; ++i)
    {
        nodeData[i].setData(input); // setting node names
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
