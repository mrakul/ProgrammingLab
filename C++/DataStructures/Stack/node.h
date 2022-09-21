#include <iostream>

/*** Stack's node template ***/
template <typename Data>
class Node
{
public:
    Data nodeData;
    Node<Data> *nextNodePtr;

    // Need a generic constructors to nullify nextNode pointer: adding default and copy constructor
    Node() : nextNodePtr(nullptr) {}                                         // For nodeData, default constructor is called implicitly
    Node(const Data &newNodeData) : nodeData(newNodeData), nextNodePtr(nullptr) {}         // And here, Data's copy constructor is called for nodeData

    void printNode(Node<Data> *nodeToPrintPtr);
};

template <typename Data>
void Node<Data>::printNode(Node<Data> *nodeToPrintPtr) { std::cout << nodeData; }               // operator<<() should be overloaded for the corresponding class