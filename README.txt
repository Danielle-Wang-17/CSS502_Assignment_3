Breaking down the findShortestPath() function
-This function is implementing Dijkstra's shortest path algorithm.
-The purpose of this function is to fun the shortest distance from one node (source node) to all its neighbour nodes.
-It finds the shortest distance from one node (source node) to all other nodes in a weighted graph (A weighted graph is a graph in which each branch is given a numerical weight.)
 represented by an adjacency matrix.

The algorithm uses two data structures, adjMatrix and Table.
1. adjMatrix is the adjacency matrix representation of the graph
2. Table is used to keep track of the current distance from the source node to other nodes and whether a node is visited or not.

-The 'for' loop iterates over all nodes, where the variable source is the source node for each iteration.
-At the start of each iteration, the distance of the source node to itself is set to zero and marked as visited. 
-The inner 'for' loop then initializes the distances and paths of all nodes directly connected to the source node.

The algorithm (loop) repeats the following steps until all nodes are VISITED:

-Find the closest node to the source node that has not been visited. This node is assigned to the variable v.
Mark node v as visited.
-Update the distances of all unvisited nodes connected to node v if the new distance is shorter than the current distance.
The path to the updated node is set to node v.
-Repeat steps 1 to 3 until all nodes are visited.
-The algorithm terminates when there is no more node that has not been visited.
And can be connected to the source node with a shorter distance and stored in an array.



int min = INT_MAX;
int v = 0;
while (true)
{
    for (int i = 1; i <= numOfNodes; i++)
    {
        if (!Table[source][i].visited && (adjMatrix[source][i] < min))
        {
            min = adjMatrix[source][i];
            v = i;
        }
    }

    if (v == 0)
    {
        break;
    }

    Table[source][v].visited = true;

    for (int w = 1; w <= numOfNodes; w++)
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

    min = INT_MAX;
    v = 0;
}
