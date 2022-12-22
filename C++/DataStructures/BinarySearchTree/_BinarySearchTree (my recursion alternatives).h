#include "TreeNode.h"
#include <iostream>

using namespace std;

/*
*   Note: This header differs from BinarySearchTree.h only in printInOrder() and releaseNodes() implementation.
*   Recursion stops not at nullptr (lack of subtree), but the function processed till the end.
*   There are more checks, but such implementation looks more clear to me, so save it just in case.
*/

template <typename Key>
class BST
{
    TreeNode<Key> *treeRoot;
    void releaseNodes(TreeNode<Key> *nodeToReleasePtr);                          // Auxiliary function for Destructor
public:
    BST(): treeRoot(nullptr) {}
    ~BST();

    // Inserting functions
    bool insertNode(Key itemToInsert);                                           // Wrapper function not to pass the root of the tree always
    bool insertNode(Key nodeToAdd, TreeNode<Key> *curSubTreeRoot);

    // Printing functions
    void printInOrder();                                                          // Wrapper function
    void printInOrder(TreeNode<Key> *curSubTreeRoot);

    // Getter functions
    auto getTreeRoot() { return treeRoot; }

};

/*** Inserting functions ***/
template<typename Key>
bool BST<Key>::insertNode(Key itemToInsert)                                        // Wrapper function
{
    return insertNode(itemToInsert, treeRoot);                                     // Call the function with passing the current root
}

template<typename Key>
bool BST<Key>::insertNode(Key itemToInsert, TreeNode<Key> *curSubTreeRoot)         // (!!!) We're inserting data/key, nodes are created basing on the key
{
    bool isInserted = true;                                                        // If a value being added not presents in the tree yet

    if (curSubTreeRoot == nullptr){                                                // If the tree is not filled yet
        treeRoot = new TreeNode{itemToInsert};                                     // Make the new node as the root
        return true;
    }

    if (itemToInsert == curSubTreeRoot->key)                                         // Restrict adding a value multiple times
        return false;                                                                // Key already exists, not inserted. Inherit false thorugh the calls

    if (itemToInsert < curSubTreeRoot->key){                                         // If node to add is less than the current node
        if (curSubTreeRoot->leftSubTreePtr != nullptr)                               // Left subtree exists
            isInserted = insertNode(itemToInsert, curSubTreeRoot->leftSubTreePtr);   // Move on to traverse and return if the value encountered during recursion
        else                                                                         // Left node doesn't exist
            curSubTreeRoot->leftSubTreePtr = new TreeNode<Key>{itemToInsert};        // Create a node and link it to the leftSubTree pointer
    }

    if (itemToInsert > curSubTreeRoot->key){                                         // If node to add is more than the current node
        if (curSubTreeRoot->rightSubTreePtr != nullptr)                              // Right subtree exists
            isInserted = insertNode(itemToInsert, curSubTreeRoot->rightSubTreePtr);  // Move on to traverse and return if the value encountered during recursion
        else                                                                         // Right node doesn't exist
            curSubTreeRoot->rightSubTreePtr = new TreeNode<Key>{itemToInsert};       // Create a node and link it to the rightSubTree pointer
    }

    return isInserted;                                                               // False meaning that some of the insertNode() call returned false, that is the value being added was encounterd during traversal
}

/*** Printing functions*/
template<typename Key>
void BST<Key>::printInOrder()                                                       // Wrapper function
{
    printInOrder(treeRoot);                                                         // Call the function with passing the current root
}

template<typename Key>
void BST<Key>::printInOrder(TreeNode<Key> *curSubTreeRoot)
{
    if (curSubTreeRoot->leftSubTreePtr != nullptr)                                // If has left subree
        printInOrder(curSubTreeRoot->leftSubTreePtr);                             // Move on in traversal

    cout << curSubTreeRoot->key << ' ';                                           // If no left subtree, this node is the minimum for now, print out it

    if (curSubTreeRoot->rightSubTreePtr != nullptr)                               // Continue with checking right subtree of the node
        printInOrder(curSubTreeRoot->rightSubTreePtr);                            // Move on in traversal

    // cout << "Return from " << curSubTreeRoot->key << ' ';
}

template <typename Key>
void BST<Key>::releaseNodes(TreeNode<Key> *curSubTreeRoot)                    // Release node using depth-first search (DFS)
{
    if (curSubTreeRoot == nullptr)                                            // Stop the recursion
        return;

    releaseNodes(curSubTreeRoot->leftSubTreePtr);                             // Go left as deep as possible
    releaseNodes(curSubTreeRoot->rightSubTreePtr);                            // Go right as left as possible

    delete curSubTreeRoot;                                                    // Delete the node when checked its subtrees
}

/*** Destructor ***/
template<typename Key>
BST<Key>::~BST()
{
    releaseNodes(treeRoot);                                                 // Destructor as a wrapper for releaseNodes function
}