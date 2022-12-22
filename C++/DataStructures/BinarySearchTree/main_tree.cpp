#include "BinarySearchTree.h"
#include <iostream>

int main(int argc, char const *argv[])
{

    // 1. Checking nodes inserting
    {
        BST<int> myBSTree;

        myBSTree.insertNode(5);
        myBSTree.insertNode(3);
        myBSTree.insertNode(7);
        myBSTree.insertNode(1);
        myBSTree.insertNode(9);
        myBSTree.insertNode(4);
        myBSTree.insertNode(8);
        myBSTree.insertNode(2);
        myBSTree.insertNode(6);
        // Checking print in order
        myBSTree.printInOrder();

        // Check of adding the value already existing in the tree
        std::cout << (myBSTree.insertNode(9) ? "Value 9 successfully added " : "Value 9 already exists") << '\n';
        std::cout << (myBSTree.insertNode(10) ? "Value 10 successfully added " : "Value 10 already exists") << '\n';
    }

    return 0;
}

