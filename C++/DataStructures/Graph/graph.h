#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph
{
    int numOfVertices;                                                      // Number of vertices
    list<int> *adjacentLists;                                               // Adjacent vertexes lists, just a pointer initially
public:
    Graph(int verticesNumber): numOfVertices(verticesNumber), adjacentLists(new list<int>[numOfVertices]) {}
    ~Graph();

    void addEdge(int sourceVertex, int targetVertex);
    void DFSRecursively(int vertexToStart);                                 // Starting point of the DFS
    void DFSTraversing(int vertexNum, vector<bool> &visited);               // DFSTraversing is used for recursive calls
};

void Graph::addEdge(int sourceVertex, int targetVertex)
{
    adjacentLists[sourceVertex].push_back(targetVertex);                    // Push the targetVertex to the list of the sourceVertex
}

void Graph::DFSTraversing(int vertexNum, vector<bool> &visited)
{
    visited[vertexNum] = true;                                              // Mark the vertex as visited
    cout << vertexNum << " ";                                               // Process the vertex

    for (auto nextConnectedVertex : adjacentLists[vertexNum]){              // Move through the adjacent nodes of the current vertex
        if (!visited[nextConnectedVertex])                                  // If the adjacent node is not visited yet
            DFSTraversing(nextConnectedVertex, visited);                    // Process the adjacent node's adjacents
    }
}

void Graph::DFSRecursively(int vertexToStart)
{
    vector<bool> visited(numOfVertices, false);                             // Create the vector of booleans here and pass it through DFSTraversing calls
    DFSTraversing(vertexToStart, visited);                                  // Start the recursion for the starting vertex
}

Graph::~Graph()
{
    delete[] adjacentLists;
}