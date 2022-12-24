#include "TreeNode.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <typename Key>
class BST
{
    TreeNode<Key> *treeRoot;
    void releaseNodes(TreeNode<Key> *nodeToReleasePtr);                          // Auxiliary function for Destructor
    bool insertNode(Key nodeToAdd, TreeNode<Key> *curSubTreeRoot);               // Make the wrapped function private

public:
    BST(): treeRoot(nullptr) {}
    ~BST();

    // Inserting functions
    bool insertNode(Key itemToInsert);                                           // Wrapper function not to pass the root of the tree every time

    // Printing functions
    void printInOrderRecursion();                                                // Wrapper function
    void printInOrderRecursion(TreeNode<Key> *curSubTreeRoot);                   // Depth-first search using call stack recursion

    void printInOrderIteratively();                                              // Wrapper function
    void printInOrderIteratively(TreeNode<Key> *curSubTreeRoot);                 // Depth-first search using stack implementation

    void printBFS();                                                             // Wrapper function
    void printBFS(TreeNode<Key> *curSubTreeRoot);                                // Breadth-first search using queue

    // Getter functions
    auto getTreeRoot() { return treeRoot; }

};

/*** Inserting functions ***/
template<typename Key>
bool BST<Key>::insertNode(Key itemToInsert)                                          // Wrapper function
{
    return insertNode(itemToInsert, treeRoot);                                       // Call the function with passing the current root
}

// Note:  My recursion alternative: the idea is that we stop when having lack of subtree and adding a new node before calling insertNode() once again
template<typename Key>
bool BST<Key>::insertNode(Key itemToInsert, TreeNode<Key> *curSubTreeRoot)           // (!) We're inserting data/key, nodes are created basing on the key
{
    bool isInserted = true;                                                          // If a value being added not presents in the tree yet

    if (curSubTreeRoot == nullptr){                                                  // If the tree is not filled yet
        treeRoot = new TreeNode{itemToInsert};                                       // Make the new node as the root
        return true;
    }

    if (itemToInsert == curSubTreeRoot->key)                                         // Restrict adding a value multiple times
        return false;                                                                // Key already exists, not inserted. Inherit false thorugh the calls

    if (itemToInsert < curSubTreeRoot->key){                                         // If node to add is less than the current node
        if (curSubTreeRoot->leftSubTreePtr != nullptr)                               // Left subtree exists
            isInserted = insertNode(itemToInsert, curSubTreeRoot->leftSubTreePtr);   // Move on to traverse and return nullptr if the value encountered during recursion. isInserted inherited up
        else                                                                         // Left node doesn't exist
            curSubTreeRoot->leftSubTreePtr = new TreeNode<Key>{itemToInsert};        // Create a node and link it to the leftSubTree pointer
    }

    if (itemToInsert > curSubTreeRoot->key){                                         // If node to add is more than the current node
        if (curSubTreeRoot->rightSubTreePtr != nullptr)                              // Right subtree exists
            isInserted = insertNode(itemToInsert, curSubTreeRoot->rightSubTreePtr);  // Move on to traverse and return nullptr if the value encountered during recursion. isInserted inherited up
        else                                                                         // Right node doesn't exist
            curSubTreeRoot->rightSubTreePtr = new TreeNode<Key>{itemToInsert};       // Create a node and link it to the rightSubTree pointer
    }

    return isInserted;                                                               // False meaning that some of the insertNode() call returned false, that is the value being added was encounterd during traversal
}

// Note: below is canonical implementation with recursion
//
// template<typename Key>
// bool BST<Key>::insertNode(Key itemToInsert)                                        // Wrapper function
// {
//     if (treeRoot == nullptr)                                                       // If a tree doesn't filled yet
//         return (treeRoot = new TreeNode{itemToInsert});                                 // Create a new node, set the root and return it as bool
//     else                                                                           // A tree contains nodes already
//         return insertNode(itemToInsert, treeRoot);                                 // Call the function with passing the current root
// }

// template<typename Key>
// TreeNode<Key> *BST<Key>::insertNode(Key itemToInsert, TreeNode<Key> *curSubTreeRoot)         // (!) We're inserting data/key, nodes are created basing on the key
// {
//     if (curSubTreeRoot == nullptr)                                                  // If encountered nullptr, stop the recursion
//         return (new TreeNode{itemToInsert});                                        // Create a new node with the inserted key and return this pointer

//     if (itemToInsert < curSubTreeRoot->key)                                         // If node to add is less than the current node
//         curSubTreeRoot->leftSubTreePtr = insertNode(itemToInsert, curSubTreeRoot->leftSubTreePtr);          // Move on to traverse and link left subtree or nullptr if encountered the same key

//     if (itemToInsert > curSubTreeRoot->key)                                         // If node to add is more than the current node
//         curSubTreeRoot->rightSubTreePtr = insertNode(itemToInsert, curSubTreeRoot->rightSubTreePtr);         // Move on to traverse and return added node pointer or nullptr if encountered the same key

//     return curSubTreeRoot;                                                          // (!) Return the current node, this way on the way back it will be rewritten
// }


/*** Printing functions*/
template<typename Key>
void BST<Key>::printInOrderRecursion()                                              // Wrapper function
{
    printInOrderRecursion(treeRoot);                                                // Call the function with passing the current root
}

template<typename Key>
void BST<Key>::printInOrderRecursion(TreeNode<Key> *curSubTreeRoot)
{
    if (curSubTreeRoot == nullptr)                                                  // Stop the recursion
        return;

    printInOrderRecursion(curSubTreeRoot->leftSubTreePtr);                          // Check the left subtree, go left as deep as possible

    cout << curSubTreeRoot->key << ' ';                                             // If no left subtree, this node is the minimum for now, print out it

    printInOrderRecursion(curSubTreeRoot->rightSubTreePtr);                         // Check the right subtree, go right as deep as possible

    // cout << "Return from " << curSubTreeRoot->key << ' ';
}

// Or to stop before getting to nullptr, but above is canonical
// template<typename Key>
// void BST<Key>::printInOrderRecursion(TreeNode<Key> *curSubTreeRoot)
// {
//     if (curSubTreeRoot->leftSubTreePtr != nullptr)                                // If has left subree
//         printInOrderRecursion(curSubTreeRoot->leftSubTreePtr);                             // Move on in traversal
//
//     cout << curSubTreeRoot->key << ' ';                                           // If no left subtree, this node is the minimum for now, print out it
//
//     if (curSubTreeRoot->rightSubTreePtr != nullptr)                               // Continue with checking right subtree of the node
//         printInOrderRecursion(curSubTreeRoot->rightSubTreePtr);                   // Move on in traversal
//
//     // cout << "Return from " << curSubTreeRoot->key << ' ';
// }

template <typename Key>
void BST<Key>::printInOrderIteratively()
{
    printInOrderIteratively(treeRoot);                                               // Start with the root of the tree
}

template <typename Key>
void BST<Key>::printInOrderIteratively(TreeNode<Key> *curSubTreeRoot)
{
    stack<TreeNode<Key> *> nodesToProcess;                                           // Having stack to push the nodes there which aren't processed yet
    TreeNode<Key> *nextNodeToProcess = curSubTreeRoot;                               // Start with the root of the tree, but not adding it to the stack.

    while (!nodesToProcess.empty() || nextNodeToProcess){                            // Continue either nodes to be processed exists on the stack or node to be processes is saved (for example, we got to the root back, so no nodes on the stack, but it has the right subtree). Otherwise, the tree is processed
        while (nextNodeToProcess){                                                   // Until left subtree node is nullptr
            nodesToProcess.push(nextNodeToProcess);                                  // Push the nodes encountered on the way
            nextNodeToProcess = nextNodeToProcess->leftSubTreePtr;                   // Go left as much as possible
        }                                                                            // At the end, current node has no left subtree

        cout << nodesToProcess.top()->key << ' ';                                    // Process the node
        nextNodeToProcess = nodesToProcess.top()->rightSubTreePtr;                   // Left subtree is processed, so we may move right
        nodesToProcess.pop();                                                        // Pop the node out since it is processed
    }
}

template <typename Key>
void BST<Key>::printBFS()
{
    printBFS(treeRoot);                                                      // Start with the root of the tree
}

template <typename Key>
void BST<Key>::printBFS(TreeNode<Key> *curSubTreeRoot)
{
    queue<TreeNode<Key> *> nodesToProcess;                                   // Having queue to push the nodes there which aren't processed yet
    TreeNode<Key> *curNodeToProcess{nullptr};                                // Current node to be processed which is used to store the front value of the queue

    nodesToProcess.push(curSubTreeRoot);                                     // Push the root node to the queue
    while (!nodesToProcess.empty()){                                         // While queue has nodes to process
        curNodeToProcess = nodesToProcess.front();                           // Got the first node waiting in the queue

        if (curNodeToProcess->leftSubTreePtr)                                // If the current node has left subtree
            nodesToProcess.push(curNodeToProcess->leftSubTreePtr);           // Push the current root to the queue

        if (curNodeToProcess->rightSubTreePtr)                               // If the current node has right subtree
            nodesToProcess.push(curNodeToProcess->rightSubTreePtr);          // Push the current root to the queue

        cout << nodesToProcess.front()->key << ' ';                          // Process the node after we placed it children to the queue
        nodesToProcess.pop();                                                // Pop the node out of the queue since it is processed and its subtrees are counted
    }
}

template <typename Key>
void BST<Key>::releaseNodes(TreeNode<Key> *curSubTreeRoot)                    // Release node using depth-first search (DFS)
{
    if (curSubTreeRoot == nullptr)                                            // Stop the recursion
        return;

    releaseNodes(curSubTreeRoot->leftSubTreePtr);                             // Go left as deep as possible
    releaseNodes(curSubTreeRoot->rightSubTreePtr);                            // Go right as left as possible

    delete curSubTreeRoot;                                                    // Delete the node when checked its subtrees. Note: this is the PostOrder traversal actually, delete is after checking both subtrees
}

/*** Destructor ***/
template<typename Key>
BST<Key>::~BST()
{
    releaseNodes(treeRoot);                                                 // Destructor as a wrapper for releaseNodes function
}