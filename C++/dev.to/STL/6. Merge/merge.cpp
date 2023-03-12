#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <set>

/*** Merging algorithms examples
 * Note: Since C++17 there is Execution Policy in the merge() function signatures. See: https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t
 * This is the stable algorithm!
 *
 * merge() can be used for sets also (associative containers), but there is another better algorithm: set_union()
***/

using namespace std;

void printVector(auto &vectToOut);

int main(int argc, char const *argv[])
{
    // 0. Create two vectors to merge and a resulting vector
    vector<int> myVector1{1, 3, 5, 7, 9, 11, 29};
    vector<int> myVector2{7, 8, 9, 10, 11, 12, 29};
    vector<int> resultVector(myVector1.size() * 3);
    printVector(myVector1);
    printVector(myVector2);
    printVector(resultVector);                                      // Size/Capacity: 21/21. Can use resultVector.resize(0), then need to use back_inserter(resultVector), surely

    // 1. merge() example: merge
    // Note: the behavior is undefined if the destination range overlaps either of the input ranges (the input ranges may overlap each other).
    auto endOfMergeIt = merge(myVector1.begin(), myVector1.end(), myVector2.begin(), myVector2.end(), resultVector.begin());                        // Fill over the filled vector or use back_inserter(resultVector) on unfilled vector
    printVector(resultVector);

    resultVector.erase(endOfMergeIt, resultVector.end());         // Cut-off unwanted part of the vector
    printVector(resultVector);

    // 2. merge() with Comparator Predicate, just to have it as a reference
    auto isLessThan = [](auto &firstContItem, auto &secondContItem){return (firstContItem < secondContItem);};

    resultVector.resize(0);                                         // Now, resize the result vector to use back_inserter not to erase unwanted part then
    merge(myVector1.begin(), myVector1.end(), myVector2.begin(), myVector2.end(), back_inserter(resultVector), isLessThan);                         // Doesn't return resulting iterator when using back_inserter()
    printVector(resultVector);

    // 3. Try merge() on the lists
    list<int> myList1{1, 3, 5, 7, 9};
    list<int> myList2{10, 15, 20};
    list<int> resultList;

    merge(myList1.begin(), myList1.end(), myList2.begin(), myList2.end(), back_inserter(resultList));
    for_each(resultList.begin(), resultList.end(), [](auto &curItem){cout << curItem << " ";});
    cout.put('\n');

    // 4. merge() can be used for sets also, but there is another better algorithm: set_union()
    set<int> mySet1{1, 3, 5, 7, 9};
    set<int> mySet2{70, 80, 90};
    set<int> resultSet;

    merge(mySet1.begin(), mySet1.end(), mySet2.begin(), mySet2.end(), insert_iterator<set<int>>(resultSet, resultSet.begin()));                     // insert_iterator() should be used for sets, sure
    for_each(resultSet.begin(), resultSet.end(), [](auto &curItem){cout << curItem << " ";});
    cout.put('\n');

    // 5. merge_inplace(): merges two consecutive sorted ranges [first, middle) and [middle, last) into one sorted range [first, last)
    // Note: as I understood, merge_inplace() can use additional extra memory (GCC: __merge_adaptive) or without extra memory (GCC: __merge_without_buffer)
    // Signatures with Execution Policy and Comparator are available, sure.
    vector<int> inplaceVector{1, 3, 5, 10, 2, 4, 6, 8};

    inplace_merge(inplaceVector.begin(), inplaceVector.begin() + 4, inplaceVector.end());                       // Need to be sure that the middle iterator is the end of the first range (one past the end) and the begin of the second
    printVector(inplaceVector);

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem << " ";
    cout << endl;
}