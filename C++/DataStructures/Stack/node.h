#include <iostream>

/*** Stack's node template ***/
template <typename Type>
class Node
{
public:
    Type nodeData;
    Node<Type> *nextNodePtr;

    // Need a generic constructors to nullify nextNode pointer: adding default and copy constructor
    // For nodeData default constructor is called implicitly
    Node() : nextNodePtr(nullptr) {}
    Node(const Type &newNodeData) : nodeData(newNodeData), nextNodePtr(nullptr) {}              // And here, Type's copy constructor is called for nodeData
    void printNode(Node<Type> *nodeToPrint);
};

template <typename Type>
void Node<Type>::printNode(Node<Type> *nodeToPrint) { std::cout << nodeData; }
