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

    void releaseNodes(Node<Data> *nodeToReleasePtr);                            // Auxiliary function to use in Destructor and Move Assignment operator
public:
    // Constructors, Destructor, Copy-Move assignment operators
    LinkedList();
    LinkedList(const LinkedList<Data> &copiedList);
    LinkedList<Data> &operator=(const LinkedList<Data> &listToCopyAssign);      // Note: the trick can be used to pass the list by value, thus creating a temporary automatically

    LinkedList(LinkedList<Data> &&movedList);
    LinkedList<Data> &operator=(LinkedList<Data> &&listToMoveAssign);

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
    bool appendList(LinkedList<Data> &&listToAppend);
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

/*** // Constructors, Destructor, Copy-Move assignment operators ***/
template <typename Data>
LinkedList<Data>::LinkedList(): headPtr(nullptr), tailPtr(nullptr), numOfElements(0) {}

// Copy Constructor
template <typename Data>
LinkedList<Data>::LinkedList(const LinkedList<Data> &copiedList) : headPtr(nullptr), tailPtr(nullptr), numOfElements(0)
{
    Node<Data> *curNodeToCopyPtr = copiedList.headPtr;
    while (curNodeToCopyPtr){
        insertToTail(curNodeToCopyPtr->nodeData);                           // Use existing function to DRY
        curNodeToCopyPtr = curNodeToCopyPtr->nextNodePtr;
    }
}

// Copy Assignment
template <typename Data>
LinkedList<Data> &LinkedList<Data>::operator=(const LinkedList<Data> &listToCopyAssign)
{
    LinkedList<Data> tempList{listToCopyAssign};                                               // Create a temporary list by Copy Constructor and swap the bookkeeping info
    std::swap(headPtr, tempList.headPtr);
    std::swap(tailPtr, tempList.tailPtr);
    std::swap(numOfElements, tempList.numOfElements);

    return *this;                                                                              // Return the reference to itself
}                                                                                              // (!) Here the target list (contained in tempList after swapping) is destroyed

// Move Constructor
template <typename Data>
LinkedList<Data>::LinkedList(LinkedList<Data> &&movedList): headPtr(nullptr), tailPtr(nullptr), numOfElements(0)
{
    std::swap(headPtr, movedList.headPtr);
    std::swap(tailPtr, movedList.tailPtr);
    std::swap(numOfElements, movedList.numOfElements);                                         // Just swap the bookkepping info since the target list is empty with null pointers
}

// Move Assignment
template <typename Data>
LinkedList<Data> &LinkedList<Data>::operator=(LinkedList<Data> &&listToMoveAssign)
{
    // First, release the target List memory and reset the members
    releaseNodes(headPtr);
    headPtr = nullptr;
    tailPtr = nullptr;
    numOfElements = 0;

    // After, we can just swap it as for Move Constructor
    std::swap(headPtr, listToMoveAssign.headPtr);
    std::swap(tailPtr, listToMoveAssign.tailPtr);
    std::swap(numOfElements, listToMoveAssign.numOfElements);

    return *this;                                                                              // Return the reference to itself
}

template <typename Data>
void LinkedList<Data>::releaseNodes(Node<Data> *nodeToReleasePtr)
{
    Node<Data> *curNodePtr = nodeToReleasePtr;
    while (curNodePtr != nullptr){
        auto nextNodePtr = curNodePtr->nextNodePtr;
        delete curNodePtr;
        curNodePtr = nextNodePtr;
    }

    /*** Recursive implementation, for fun ***/
    // if (nodeToReleasePtr)
    //     releaseNodes(nodeToReleasePtr->nextNodePtr);
    // delete nodeToReleasePtr;                                                // If we are the end of the list, delete is called for the NULL not to make the redundant check
}

template <typename Data>
LinkedList<Data>::~LinkedList()
{
    std::cout << "\t ### ~LinkedList() -> Released nodes: \n";
    if (headPtr)                                                               // If the list is non-empty
        releaseNodes(headPtr);
}

/*** Inserting items ***/
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

// Append another list using move-semantics
template <typename Data>
bool LinkedList<Data>::appendList(LinkedList<Data> &&listToAppend)
{
    if (this == &listToAppend)                                          // If try to append the list to itself
        return false;                                                   // Can't append the list to itself
    else                                                                // Appending another list
        if (listToAppend.headPtr != nullptr){                           // Append only if the appended list is non-empty
            if (this->headPtr == nullptr){                              // If source is empty, just transit pointers and num of elements exists
                this->headPtr = listToAppend.headPtr;
                this->tailPtr = listToAppend.tailPtr;
                this->numOfElements = listToAppend.numOfElements;
            }
            else{                                                         // If source is non-empty, link the last node of the source to the head of the appended list
                this->tailPtr->nextNodePtr = listToAppend.headPtr;
                listToAppend.headPtr->prevNodePtr = this->tailPtr;
                this->tailPtr = listToAppend.tailPtr;
                this->numOfElements += listToAppend.numOfElements;        // And also change the number of elements
            }
        }
    // Reset the appended list pointers and number of elements in any case
    listToAppend.tailPtr = nullptr;
    listToAppend.headPtr = nullptr;
    listToAppend.numOfElements = 0;

    return true;
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
int LinkedList<Data>::searchItem(const Data &searchedItem)
{

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