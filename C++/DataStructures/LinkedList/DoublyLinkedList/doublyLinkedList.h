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
    bool addToHead(const Data &addedItem);
    bool addToTail(const Data &addedItem);
    bool addByIndex(size_t index, const Data &addedItem);

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

template <typename Data>
bool LinkedList<Data>::addToHead(const Data &addedItem)
{
    bool itemAddedSuccessfully = false;

    if (!listIsFull()){
        Node<Data> *newNodePtr = new (std::nothrow) Node<Data>{addedItem};       // Obtain memory and initialize at the same time by copy constructor of Data (Person)
        // If memory obtained successfully
        if (newNodePtr){
            if (listIsEmpty()){
                headPtr = newNodePtr;                       // headPtr is set in any case, so may carry out from if-else. Leaves for obviousness
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
void LinkedList<Data>::printInForwardDirection()
{
    auto curNode = headPtr;
    while (curNode){
        std::cout << curNode->nodeData << "->";
        curNode = curNode->nextNodePtr;
    }
}

template <typename Data>
void LinkedList<Data>::printInReverseDirection()
{
    auto curNode = tailPtr;
    while (curNode){
        std::cout << curNode->nodeData << "->";
        curNode = curNode->prevNodePtr;
    }
}