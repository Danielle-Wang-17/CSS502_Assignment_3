#include "graphm.h"
#include <climits>

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
// pseudocode from Professor
// void GraphM::findShortestPath()
// {
//     for (int source = 1; source <= numOfNodes; source++)
//     {
//         Table[source][source].dist = 0;

//         // finds the shortest distance from source to all other nodes
//         for (int i = 1; i <= numOfNodes; i++)
//         {
//          find v //not visited, shortest distance at this point
//          mark v visited
//          for each w adjacent to v
//            if (w is not visited)
//             T[source][w].dist=min(T[source][w].dist, T[source][v].dist+C[V][W])
//         }
//     }
// }

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
