#include <iostream>
#include "graph.h"

int main(int argc, char const *argv[])
{
    // 1. Create graph specifying number of vertices and add edges
    Graph myGraph(5);
    Graph myGraph2(4);

    // myGraph.addEdge(0, 1);
    myGraph.addEdge(0, 2);
    myGraph.addEdge(0, 4);
    myGraph.addEdge(1, 0);
    myGraph.addEdge(1, 2);
    myGraph.addEdge(2, 3);
    // myGraph.addEdge(3, 3);
    myGraph.addEdge(3, 1);

    myGraph2.addEdge(0, 1);
    myGraph2.addEdge(1, 2);
    myGraph2.addEdge(0, 3);
    myGraph2.addEdge(3, 3);

    // 2. Check the DFS recursively
    cout << "Depth-first search recursively:" << endl;
    myGraph.DFSRecursively(3);
    cout.put('\n');

    cout << "Depth-first search iteratively:" << endl;
    myGraph.DFSIteratively(3);
    cout.put('\n');

    // 3. Cycles determination
    cout << "Graph has cycles: " << (myGraph.isCycledRecursively(3) ? "yes" : "no") << '\n';
    cout << "Graph has cycles: " << (myGraph2.isCycledRecursively(0) ? "yes" : "no") << '\n';
    // Determine iteratively
    cout << "Graph has cycles: " << (myGraph.isCycledIteratively(3) ? "yes" : "no") << '\n';
    cout << "Graph has cycles: " << (myGraph2.isCycledIteratively(0) ? "yes" : "no") << '\n';

    return 0;
}