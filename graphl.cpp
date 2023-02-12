#include "graphl.h"
#include <iomanip>

// Default constructor
GraphL::GraphL()
{
    numofNodes_l = 0;

    for (int i = 1; i < MAXNODES_L; ++i)
    {
        node_array[i].visited = false;
        node_array[i].edgeHead = NULL;
        node_array[i].data = NULL;
    }
}

// Destructor
GraphL::~GraphL()
{
    makeEmpty();
}

void GraphL::makeEmpty()
{
    for (int i = 1; i <= numofNodes_l; ++i)
    {
        node_array[i].visited = false;
        if (node_array[i].data != NULL) // check for linked list in array index
        {
            delete node_array[i].data; // delete  edge name
            node_array[i].data = NULL; // set edge name to NULL
        }
        EdgeNode *curr = node_array[i].edgeHead;
        while (curr != NULL) // traversing linked list
        {
            EdgeNode *next = curr->nextEdge;
            delete curr; // delete node
            curr = next;
        }
        node_array[i].edgeHead = NULL; // set to null and move head
    }
    numofNodes_l = 0;
}

// Builds up graph node information and adjacency list of edges between each
// node reading from a data file
void GraphL::buildGraph(ifstream &input2)
{
    // Read the number of nodes from the input file
    input2 >> numofNodes_l;

    // Read the name of each node
    string nodeName;
    getline(input2, nodeName);

    // Loop through the number of nodes to insert the node names
    for (int i = 1; i <= numofNodes_l; i++)
    {
        getline(input2, nodeName);
        NodeData *tmp = new NodeData(nodeName);
        node_array[i].data = tmp;
    }

    int from, to;

    // Read the edges and fill the linked list
    while (input2 >> from >> to)
    {
        if (from == 0)
        {
            break;
        }

        // If this is the first edge at the current index of the node array
        if (node_array[from].edgeHead == NULL)
        {
            EdgeNode *node = new EdgeNode;
            node->adjGraphNode = to;
            node_array[from].edgeHead = node;
            node_array[from].edgeHead->nextEdge = NULL;
        }
        else // For additional edges in the linked list
        {
            EdgeNode *node = new EdgeNode;
            node->adjGraphNode = to;                    // insert adj
            node->nextEdge = node_array[from].edgeHead; // move pointer
            node_array[from].edgeHead = node;           // assign as head
        }
    }
}
