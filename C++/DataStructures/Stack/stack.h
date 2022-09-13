#ifndef _STACK_H
#define _STACK_H
#include <iostream>
#include "node.h"

/*** Stack template ***/
template <typename Type>
class Stack
{
private:
    Node<Type> *headPtr = nullptr;
    const int MAX = 100;
    // Auxiliary functions
    bool isEmpty() { return (!headPtr); }                                   // Returns true if the Stack is empty
    void releaseNodes(Node<Type> *itemToRelease);

public:
    Stack();
    ~Stack();
    bool push(const Type &pushedItem);
    bool pop(const Type &poppedItem);
};

/*** (!) Templated classes should exist in the same header file ***/
template <typename Type>
Stack<Type>::Stack() : headPtr(nullptr)
{
}

/*** Push item ***/
template <typename Type>
bool Stack<Type>::push(const Type &pushedItem)
{
    Node<Type> *newNodePtr = new Node<Type>{pushedItem};       // Obtain memory and initialize at the same time by copy constructor of Type (Person)

    if (!isEmpty())
        newNodePtr->nextNodePtr = headPtr;
    // Note: else {newNode->nextNodePtr = nullptr;} is redundant, since nextNode always initialized to nullptr
    headPtr = newNodePtr;

    std::cout << "==> " << newNodePtr->nodeData;           // Print added data
    return true;
}

/*** Pop item ***/
template <typename Type>
bool Stack<Type>::pop(const Type &poppedItem)
{
    return true;
}

template <typename Type>
void Stack<Type>::releaseNodes(Node<Type> *itemToRelease)
{
    if (itemToRelease){
        releaseNodes(itemToRelease->nextNodePtr);
        // We are at the end of the stack, may go back and release memory
        itemToRelease->printNode(itemToRelease);
        delete itemToRelease;
    }
}

template <typename Type>
Stack<Type>::~Stack()
{
    releaseNodes(headPtr);
}


#endif