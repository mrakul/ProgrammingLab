#include <iostream>
#include "graph.h"

int main(int argc, char const *argv[])
{
    // 1. Create graph having 4 vertex and add edges
    Graph myGraph(5);

    myGraph.addEdge(0, 1);
    myGraph.addEdge(0, 2);
    myGraph.addEdge(0, 4);

    myGraph.addEdge(1, 0);
    myGraph.addEdge(1, 2);

    myGraph.addEdge(2, 3);
    myGraph.addEdge(3, 3);
    myGraph.addEdge(3, 1);

    // 2. Check the DFS recursively
    cout << "Depth-first traversal output:" << endl;
    myGraph.DFSRecursively(3);

    return 0;
}