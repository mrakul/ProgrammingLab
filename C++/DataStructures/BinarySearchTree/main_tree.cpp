#include "BinarySearchTree.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    {
        BST<int> myBSTree;

        // 1. Checking nodes inserting and printing the tree
        myBSTree.insertNode(5);
        myBSTree.insertNode(3);
        myBSTree.insertNode(7);
        myBSTree.insertNode(1);
        myBSTree.insertNode(9);
        myBSTree.insertNode(4);
        myBSTree.insertNode(8);
        myBSTree.insertNode(2);
        myBSTree.insertNode(6);
        // Check of adding the value already existing in the tree
        std::cout << (myBSTree.insertNode(9) ? "Value 9 successfully added " : "Value 9 already exists") << '\n';
        std::cout << (myBSTree.insertNode(10) ? "Value 10 successfully added " : "Value 10 already exists") << '\n';

        // 2. Check DFS printing functions
        cout << "Print DFS InOrder recursively: \n";
        myBSTree.printInOrderRecursion();
        cout << '\n';

        cout << "Print DFS InOrder iteratively: \n";
        myBSTree.printInOrderIteratively();
        cout << '\n';

        cout << "Print DFS PostOrder recursively: \n";
        myBSTree.printPostOrderRecursion();
        cout << '\n';

        cout << "Print DFS PostOrder iteratively: \n";
        myBSTree.printDFSIeratively();
        cout << '\n';

        // 3. Check BFS printing function
        cout << "Print breadth-first search: \n";
        myBSTree.printBFS();
    }

    return 0;
}