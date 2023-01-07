#include <iostream>
#include <list>
#include <vector>
#include <stack>

using namespace std;

class Graph
{
    int numOfVertices;                                                      // Number of vertices: vertices are numbered from 0 sequentially
    list<int> *adjacentLists;                                               // Adjacent vertexes lists, just a pointer initially
public:
    Graph(int verticesNumber): numOfVertices(verticesNumber), adjacentLists(new list<int>[numOfVertices]) {}
    ~Graph();

    void addEdge(int sourceVertex, int targetVertex);                       // Add an edge of the graph

    // Depth-first search methods
    void DFSRecursively(int vertexToStart);                                 // Starting point of the Depth-First Search
    void DFSTraversing(int vertexNum, vector<bool> &visited);               // DFSTraversing is used for recursive calls of DFSRecursively
    void DFSIteratively(int vertexToStart);                                 // Make Depth-First Search iteratively

    // Determine cycles methods
    bool isCycledRecursively(int vertexToStart);                            // Determine if a graph have cycle for a starting point using DFS recursively, based on the DFSRecursively()
    bool isCycledTraverseRecursively(int vertexNum, vector<bool> &visited, vector<bool> &curVerticesPath);      // isCycledTraverseRecursively is used for recursive calls of isCycledRecursively, based on the DFSTraversing()
    bool isCycledIteratively(int vertexToStart);                            // Determine if a graph have cycle for a starting point using DFS iteratively
};

void Graph::addEdge(int sourceVertex, int targetVertex)
{
    adjacentLists[sourceVertex].push_back(targetVertex);                    // Push the targetVertex to the list of the sourceVertex's adjacents
}

/*** Depth-first search methods ***/
void Graph::DFSRecursively(int vertexToStart)
{
    vector<bool> visited(numOfVertices, false);                             // Create the vector of booleans here and pass it through DFSTraversing calls
    DFSTraversing(vertexToStart, visited);                                  // Start the recursion for the starting vertex
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

void Graph::DFSIteratively(int vertexNum)
{
    stack<int> nodesToProcess;                                              // Vertices which are still to be processed. They can be visited or not yet
    vector<bool> visited(numOfVertices, false);                             // Visited vertices
    int curNodeToProcess{vertexNum};                                        // Current node for processing

    nodesToProcess.push(curNodeToProcess);                                  // Push the initial vertex to the stack
    while (!nodesToProcess.empty()){                                        // While have vertices for processing

        curNodeToProcess = nodesToProcess.top();                            // Read the current vertex data
        if (!visited[curNodeToProcess]){                                    // If it is not visited
            visited[curNodeToProcess] = true;                               // Mark it as visited
            cout << curNodeToProcess << " ";                                // And process the vertex

            for (auto nextConnectedVertexIt = adjacentLists[curNodeToProcess].rbegin(); nextConnectedVertexIt != adjacentLists[curNodeToProcess].rend(); nextConnectedVertexIt++)
                if (!visited[*nextConnectedVertexIt])                       // Cycle above from the end of the list to process first which are in the beginning of adj.list
                    nodesToProcess.push(*nextConnectedVertexIt);            // Add non-visited vertices to the stack
        }
        else                                                                // If the vertex is visited
            nodesToProcess.pop();                                           // Pop the vertex out of the stack
    }
}

/*** Cycles determination methods ***/
bool Graph::isCycledRecursively(int vertexToStart)
{
    vector<bool> visited(numOfVertices, false);                             // Create the vector of booleans here and pass it through DFSTraversing calls
    vector<bool> curVerticesPath(numOfVertices, false);                     // Current path of encountered vertices
    bool hasCycle{false};                                                   // Return value: true if the graph has cycles

    hasCycle = isCycledTraverseRecursively(vertexToStart, visited, curVerticesPath);   // Start the recursion for the starting vertex

    return hasCycle;
}

bool Graph::isCycledTraverseRecursively(int vertexNum, vector<bool> &visited, vector<bool> &curVerticesPath)
{
    bool hasCycle{false};                                                            // Return value: true if the graph has cycles

    visited[vertexNum] = true;                                                       // Mark the vertex as visited
    curVerticesPath[vertexNum] = true;                                               // Mark the vertex as encountered during the current path
    // cout << vertexNum << " ";                                                     // Process the vertex (optionally)

    for (auto nextConnectedVertex : adjacentLists[vertexNum]){                       // Move through the adjacent nodes of the current vertex
        if (curVerticesPath[nextConnectedVertex])                                    // If the next vertex to go already encountered along the way during traversing
            hasCycle = true;                                                         // Mark it
        else if (!visited[nextConnectedVertex])                                      // Cycles not found yet AND the adjacent node is not visited yet
            hasCycle = isCycledTraverseRecursively(nextConnectedVertex, visited, curVerticesPath);      // Process the adjacent node's adjacents

        if (hasCycle)                                                                // Cycle is found at the current isCycledTraverseRecursively() call or at sub-call
            break;                                                                   // Then stop checking the current vertex's adjacents
    }

    curVerticesPath[vertexNum] = false;                                     // Reset the vertex's current path mark after processing its adjacents

    return hasCycle;
}

bool Graph::isCycledIteratively(int vertexToStart)
{
    stack<int> nodesToProcess;                                              // Vertices which are still to be processed. They can be visited or not yet
    vector<bool> visited(numOfVertices, false);                             // Visited vertices
    vector<bool> curVerticesPath(numOfVertices, false);                     // Current path of encountered vertices
    bool hasCycle{false};                                                   // Return value: true if the graph has cycles

    int curNodeToProcess{vertexToStart};                                    // Current node for processing

    nodesToProcess.push(curNodeToProcess);                                  // Push the initial vertex to the stack
    while (!nodesToProcess.empty() && !hasCycle){                           // While have vertices for processing AND still not found cycles

        curNodeToProcess = nodesToProcess.top();                            // Read the current vertex data
        if (!visited[curNodeToProcess]){                                    // If it is not visited

            visited[curNodeToProcess] = true;                               // Mark it as visited
            curVerticesPath[curNodeToProcess] = true;                       // Mark the vertex position at the current path
            // cout << curNodeToProcess << " ";                             // Process the vertex (optionally)

            for (auto nextConnectedVertexIt = adjacentLists[curNodeToProcess].rbegin(); nextConnectedVertexIt != adjacentLists[curNodeToProcess].rend() && !hasCycle; nextConnectedVertexIt++)      // Additional condition !hasCycle to stop immediately when cycling encountered
                if (curVerticesPath[*nextConnectedVertexIt])                // If next vertex to process already encountered on the way
                    hasCycle = true;                                        // Mark it to stop the loop
                else if (!visited[*nextConnectedVertexIt])                  // If no cycles determined, check if non-visited vertex to push on the stack
                    nodesToProcess.push(*nextConnectedVertexIt);            // Add non-visited vertices to the stack
        }
        else{                                                               // If the vertex is visited
            curVerticesPath[curNodeToProcess] = false;                      // Reset the vertex's current path mark when popping it out
            nodesToProcess.pop();                                           // Pop the vertex out of the stack
        }
    }

    return hasCycle;
}

Graph::~Graph()
{
    delete[] adjacentLists;
}