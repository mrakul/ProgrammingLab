#ifndef _STACK_H
#define _STACK_H
#include <iostream>
#include "node.h"

/*** Stack template ***/
template <typename Data>
class Stack
{
private:
    Node<Data> *headPtr = nullptr;
    size_t numOfElements = 0;
    const size_t MAX_NUM_OF_ELEM = 7;
    // Auxiliary functions
    bool stackIsEmpty() { return (!headPtr); }                                   // Returns true if the Stack is empty
    bool stackIsFull() { return numOfElements == MAX_NUM_OF_ELEM; }              // Returns true if the Stack is full
    void releaseNodes(Node<Data> *nodeToReleasePtr);

public:
    Stack();
    ~Stack();
    bool push(const Data &pushedItem);
    bool pop(Data &poppedItem);
};

/*** (!) Templated classes should exist in the same header file ***/
template <typename Data>
Stack<Data>::Stack() : headPtr(nullptr)
{
}

/*** Push item ***/
template <typename Data>
bool Stack<Data>::push(const Data &pushedItem)
{
    bool itemPushedSuccessfully = false;

    if (!stackIsFull()){
        Node<Data> *newNodePtr = new (std::nothrow) Node<Data>{pushedItem};       // Obtain memory and initialize at the same time by copy constructor of Data (Person)
        // If obtained memory successfully
        if (newNodePtr){
            if (!stackIsEmpty())
                newNodePtr->nextNodePtr = headPtr;
            // Note: else {newNode->nextNodePtr = nullptr;} is redundant, since nextNode always initialized to nullptr

            headPtr = newNodePtr;
            numOfElements++;
            itemPushedSuccessfully = true;

            std::cout << "==> " << newNodePtr->nodeData;                        // Print added data
        }

    }
    return itemPushedSuccessfully;
}

/*** Pop item ***/
template <typename Data>
bool Stack<Data>::pop(Data &poppedItem)
{
    bool itemPoppedSuccessfully = false;

    if (!stackIsEmpty()){
        Node<Data> *nextNodePtr = headPtr->nextNodePtr;                       // Save the next pointer before deleting the head node
        poppedItem = headPtr->nodeData;                                       // Save the data of the current head

        delete headPtr;                                                       // Destroy the current head node
        headPtr = nextNodePtr;                                                // Assign to the next. If nullptr, then reassign

        numOfElements--;
        itemPoppedSuccessfully = true;
    }

    return itemPoppedSuccessfully;
}

template <typename Data>
void Stack<Data>::releaseNodes(Node<Data> *nodeToReleasePtr)
{
    if (nodeToReleasePtr){
        releaseNodes(nodeToReleasePtr->nextNodePtr);

        // We are at the end of the stack, may go back and release memory
        delete nodeToReleasePtr;
    }
}

template <typename Data>
Stack<Data>::~Stack()
{
    std::cout << "\t Released nodes: " << std::endl;
    releaseNodes(headPtr);
}

#endif