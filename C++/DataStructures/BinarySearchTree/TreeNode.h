#ifndef TREENODE_H
#define TREENODE_H

template <typename Key>
class TreeNode
{
public:
    Key key;
    TreeNode<Key> *leftSubTreePtr;
    TreeNode<Key> *rightSubTreePtr;

    TreeNode() = delete;                                                                                          // Restrict default constructor without specifying the key value
    TreeNode(const Key &keyToCreate): key(keyToCreate), leftSubTreePtr(nullptr), rightSubTreePtr(nullptr) {}      // Copy constructor of Key is called here,
};
#endif