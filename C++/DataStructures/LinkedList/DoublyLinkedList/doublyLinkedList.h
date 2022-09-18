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
    Node<Data> *getNodeByIndex(size_t index);

    // Auxiliary functions
    bool listIsEmpty() { return (!headPtr); }
    bool listIsFull() { return numOfElements == MAX_NUM_OF_ELEMENTS; }
    // Insert, remove, search methods
    bool insertToHead(const Data &insertedItem);
    bool insertToTail(const Data &insertedItem);
    bool insertByIndex(size_t index, const Data &insertedItem);
    // Removing functions
    bool removeFromHead();
    bool removeFromTail();
    bool removeByIndex(size_t index);
    // Search item
    int searchItem(const Data &searchedItem);
    // Printing functions
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
        else if (index == numOfElements)                                        // (!) We should insert before the index, so if index == numOfElements, consider it as inserting new tail
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

                    numOfElements++;
                    itemAddedSuccessfully = true;

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
bool LinkedList<Data>::removeFromHead()
{
    bool itemRemovedSuccessfully = false;
    if (!listIsEmpty()){
        auto curHeadPtr = headPtr;
        headPtr = headPtr->nextNodePtr;         // If no next pointer, it sets to nullptr (no nodes more)

        if (headPtr)                            // If elements are still in the list
            headPtr->prevNodePtr = nullptr;     // Resets the prevNodePtr, since now it is head
        else                                    // No more elements in the list
            tailPtr = nullptr;                  // Reset tailPtr also

        delete curHeadPtr;
        numOfElements--;
        itemRemovedSuccessfully = true;
    }

    return itemRemovedSuccessfully;
}

template <typename Data>
bool LinkedList<Data>::removeFromTail()
{
    bool itemRemovedSuccessfully = false;
    if (!listIsEmpty()){
        auto curTailPtr = tailPtr;
        tailPtr = tailPtr->prevNodePtr;         // If no prev pointer, it sets to nullptr (no nodes more)

        if (tailPtr)                            // If elements are still in the list
            tailPtr->nextNodePtr = nullptr;     // Resets the nextNodePtr, since now it is tail
        else                                    // No more elements in the list
            headPtr = nullptr;                  // Reset headPtr also

        delete curTailPtr;
        numOfElements--;
        itemRemovedSuccessfully = true;
    }

    return itemRemovedSuccessfully;
}

template <typename Data>
bool LinkedList<Data>::removeByIndex(size_t index)
{
    bool itemRemovedSuccessfully = false;

    if (!listIsEmpty()){
        if (index == 0)
            itemRemovedSuccessfully = removeFromHead();
        else if (index == numOfElements - 1)
            itemRemovedSuccessfully = removeFromTail();
        else{
            try{
                // Check out of bounds
                if (index >= numOfElements)
                    throw std::out_of_range("Index is out of bounds ");
                else{
                    Node<Data> *curNode = headPtr;
                    for (size_t i = 0; i < index; i++){
                        curNode = curNode->nextNodePtr;     // curNode == required Node, so we need to remove it
                    }
                    // Already considered the removing from the head and from the tail, and the case when only one node

                    curNode->prevNodePtr->nextNodePtr = curNode->nextNodePtr;
                    curNode->nextNodePtr->prevNodePtr = curNode->prevNodePtr;

                    delete curNode;
                    numOfElements--;
                    itemRemovedSuccessfully = true;
                }
            }
            catch (const std::out_of_range &outOfRange){
                std::cout << outOfRange.what() << numOfElements << " elements in the list" << std::endl;
            }
        }

        itemRemovedSuccessfully = true;
    }

    return itemRemovedSuccessfully;
}

template <typename Data>
int LinkedList<Data>::searchItem(const Data &searchedItem){

    if (!listIsEmpty()){
        int index = 0;
        for (auto curNode = headPtr; curNode != nullptr; curNode = curNode->nextNodePtr, index++){
            if (curNode->nodeData == searchedItem)
                return index;
        }
    }

    return -1;          // Getting here means that the item is not found
}

template <typename Data>
Node<Data> *LinkedList<Data>::getNodeByIndex(size_t index)
{
    if (!listIsEmpty()){

        if (index == 0)
            return headPtr;
        else if (index == numOfElements - 1)
            return tailPtr;
        else{
            try{
                // Check out of bounds
                if (index >= numOfElements)
                    throw std::out_of_range("Index is out of bounds ");
                else{
                    Node<Data> *curNode = headPtr;

                    for (size_t i = 0; i < index; i++){
                        curNode = curNode->nextNodePtr;     // curNode == required Node, so we need to remove it
                    }
                    return curNode;
                }
            }
            catch (const std::out_of_range &outOfRange){
                std::cout << outOfRange.what() << numOfElements << " elements in the list" << std::endl;
            }
        }
    }
    return nullptr;
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