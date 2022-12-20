#include "TreeNode.h"

template <typename Key>
class BST
{
    TreeNode<Key> *treeRoot;

public:
    BST(): root(nullptr) {}
    bool insertNode(TreeNode<Key> nodeToAdd, TreeNode<Key> *curSubTreeRoot);
};

template<typename Key>
bool BST<Key>::insertNode(TreeNode<Key> nodeToAdd, TreeNode<Key> *curSubTreeRoot)
{
    if (nodeToAdd == curSubTree)                                                // Restrict adding the a value multiple times
        return false;

    if (nodeToAdd > curSubTreeRoot)                                             // If node to add is more than the current node
        if (curSubTreeRoot->rightSubTreePtr != nullptr)                         // Right node exists
            return(insertNode(nodeToAdd, curSubTreeRoot->rightSubTreePtr));     // Move on AND return the value frome the insertNode
        else{                                                                   // Right node doesn't exist
            // place the node here
            return true;
        }

    if (nodeToAdd < curSubTreeRoot)                                             // If node to add is less than the current node
        if (curSubTreeRoot->rightSubTreePtr != nullptr)                         // Left node exists
            return(insertNode(nodeToAdd, curSubTreeRoot->rightSubTreePtr));     // Move on AND return the value frome the insertNode
        else{                                                                   // Left node doesn't exist
            // place the node here
            return true;
        }

}