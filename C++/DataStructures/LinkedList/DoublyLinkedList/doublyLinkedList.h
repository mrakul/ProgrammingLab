#include "twoWayNode.h"
#include <iostream>

template <typename Data>
class LinkedList
{
private:
    Node<Data> *headPtr;
    Node<Data> *tailPtr;

    size_t numOfElements;
    const size_t MAX_NUM_OF_ELEMENTS = 7;
public:
    LinkedList();
    ~LinkedList();

    // Get class members
    auto getHeadPtr() { return headPtr; }
    auto getTailPtr() { return tailPtr; }
    auto getNumOfElements() { return numOfElements; }
    // Auxiliary functions
    bool listIsEmpty() { return (!headPtr); }
    bool listIsFull() { return numOfElements == MAX_NUM_OF_ELEMENTS; }
    // Insert, remove, search methods
    bool insertToHead(const Data &insertedItem);
    bool insertToTail(const Data &insertedItem);
    bool insertByIndex(size_t index, const Data &insertedItem);

    bool removeFromHead();
    bool removeFromTail();
    bool removeByIndex(size_t index);

    size_t searchItem(const Data &searchedItem);

    void printInForwardDirection();
    void printInReverseDirection();
};

/*** Constructors, Destructor ***/
template <typename Data>
LinkedList<Data>::LinkedList() : headPtr(nullptr), tailPtr(nullptr), numOfElements(0) {}

template <typename Data>
LinkedList<Data>::~LinkedList() {}

/*** Adding items ***/
template <typename Data>
bool LinkedList<Data>::insertToHead(const Data &insertedItem)
{
    bool itemAddedSuccessfully = false;

    if (!listIsFull()){
        Node<Data> *newNodePtr = new (std::nothrow) Node<Data>{insertedItem};       // Obtain memory and initialize at the same time by copy constructor of Data (Person)
        // If memory obtained successfully
        if (newNodePtr){
            if (listIsEmpty()){
                headPtr = newNodePtr;                       // headPtr is set in any case, so may carry out from if-else. Left for obviousness
                tailPtr = newNodePtr;
            }
            else{
                newNodePtr->nextNodePtr = headPtr;
                headPtr->prevNodePtr = newNodePtr;
                headPtr = newNodePtr;
            }

            numOfElements++;
            itemAddedSuccessfully = true;
            std::cout << "==> " << newNodePtr->nodeData;                        // Print added data, operator<<() should be overloaded for the class
        }
    }
    return itemAddedSuccessfully;
}

template <typename Data>
bool LinkedList<Data>::insertToTail(const Data &insertedItem)
{
    bool itemAddedSuccessfully = false;

    if (!listIsFull()){
        Node<Data> *newNodePtr = new (std::nothrow) Node<Data>{insertedItem};       // Obtain memory and initialize at the same time by copy constructor of Data (Person)
        // If memory obtained successfully
        if (newNodePtr){
            if (listIsEmpty()){
                headPtr = newNodePtr;
                tailPtr = newNodePtr;
            }
            else{
                newNodePtr->prevNodePtr = tailPtr;
                tailPtr->nextNodePtr = newNodePtr;
                tailPtr = newNodePtr;
            }

            numOfElements++;
            itemAddedSuccessfully = true;
            std::cout << "==> " << newNodePtr->nodeData;                        // Print added data, operator<<() should be overloaded for the class
        }
    }
    return itemAddedSuccessfully;
}

template <typename Data>
bool LinkedList<Data>::insertByIndex(size_t index, const Data &insertedItem)
{
    bool itemAddedSuccessfully = false;

    if (!listIsFull()){
        if (index == 0)
            itemAddedSuccessfully = insertToHead(insertedItem);
        else if (index == numOfElements - 1)
            itemAddedSuccessfully = insertToTail(insertedItem);
        else{
            try{
                // Check out of bounds
                if (index >= numOfElements)
                    throw std::out_of_range("Index is out of bounds ");
                // The case when can insert an element
                else{
                    Node<Data> *curNode = headPtr;
                    for (size_t i = 0; i < index; i++){
                        curNode = curNode->nextNodePtr;     // curNode == required Node, so we need to place the new before the current
                    }

                    Node<Data> *newNodePtr = new Node<Data>{insertedItem};       // Obtain memory and initialize at the same time by copy constructor of Data (Person)

                    // Link the new node between (index; index - 1)
                    newNodePtr->nextNodePtr = curNode;
                    newNodePtr->prevNodePtr = curNode->prevNodePtr;
                    // Set (index and index- 1) nodes pointers to the new node
                    curNode->prevNodePtr->nextNodePtr = newNodePtr;
                    curNode->prevNodePtr = newNodePtr;

                    std::cout << "==> " << newNodePtr->nodeData;
                }
            }
            catch (const std::out_of_range &outOfRange){
                std::cout << outOfRange.what() << numOfElements << " elements in the list" << std::endl;
            }
        }
    }
    return itemAddedSuccessfully;
}

template <typename Data>
void LinkedList<Data>::printInForwardDirection()
{

    auto curNode = headPtr;
    std::cout << "\t ### Printing list nodes in forward direction ### \n" << "HEAD: ";
    while (curNode){
        (curNode != tailPtr) ? (((std::cout << curNode->nodeData) << "->")) : (std::cout << curNode->nodeData);
        curNode = curNode->nextNodePtr;
    }
}

template <typename Data>
void LinkedList<Data>::printInReverseDirection()
{
    std::cout << "\t ### Printing list nodes in reverse direction ### \n" << "TAIL: ";
    auto curNode = tailPtr;
    while (curNode){
        (curNode != headPtr) ? (((std::cout << curNode->nodeData) << "<-")) : (std::cout << curNode->nodeData);
        curNode = curNode->prevNodePtr;
    }
}