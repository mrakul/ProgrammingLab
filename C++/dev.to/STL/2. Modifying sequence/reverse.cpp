#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <algorithm>

/*** reverse() examples ***/

void printVector(auto &vectToOut);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create a vector and a list of the same content
    vector<int> myVector{1, 2, 3, 4, 3, 5, 3, 7, 8, 9};
    printVector(myVector);

    // 1. reverse() example
    reverse(myVector.begin(), myVector.end());                                          // Note that reverse() requires Bidirectional Iterators as input, so forward_list() can't be used
    printVector(myVector);

    // 2. reverse_copy(): nothing new() copies reversed input range to another container
    vector<int> myVector2{10, 20, 30, 40, 70, 90};
    printVector(myVector2);
    list<int> myList(6, 0);

    reverse_copy(myVector2.begin(), myVector2.end(), myList.begin());
    for_each(myList.begin(), myList.end(), [](auto &curItem){cout << curItem << " ";});

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem << ", ";
    cout << endl;
}