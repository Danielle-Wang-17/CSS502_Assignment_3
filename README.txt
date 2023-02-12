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

GraphL

The function buildGraph() is a member function of the class GraphL. It takes an input stream 'input2' as a parameter, which is expected to contain information about a graph.

The function starts by reading the number of nodes in the graph from the input file and storing it in the 'numofNodes_l' member variable of the class.

Then, it reads the name of each node, and for each name, it creates a new NodeData object and stores it in the 'node_array' member array at the corresponding index.

After reading the node names, the function reads the edges of the graph. It uses a while loop that continues until the input stream 'input2' reaches the end. In each iteration of the loop, it reads two integers 'from' and to, which represent the source and destination nodes of an edge, respectively. The loop continues until 'from' is equal to zero, which is used as a marker to indicate the end of the edge information.

For each edge, the function inserts the edge into a linked list stored in the corresponding 'node_array' element. If the current node doesn't have any edges yet, it creates a new 'EdgeNode' object and sets it as the head of the linked list. If there are already edges for the current node, it creates a new 'EdgeNode' object, sets its adjGraphNode to the destination node, and adds it to the head of the linked list by updating the next pointer.
