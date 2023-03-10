#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

/*** find() and variations of non-modifying sequence STL algorithms examples ***/

using namespace std;

int main(int argc, char const *argv[])
{
    set<int> mySet{1, 2, 3, 4, 5, 7, 8, 9};
    set<int> subSet{5, 7, 8};

    // 1. Check find(), finds the first match
    // Note: std::find() is used on the set just for example to demonstrate that these functions can be used for associative containers also.
    // Sets have its own set::find() member function having O(logN) time complexity (surely), not the O(N) as a general std::find()
    auto it = find(mySet.begin(), mySet.end(), 7);
    it != mySet.end() ? (cout << "Found item is: " << *it << endl) : (cout << "Item is not found." << endl);

    // 2. find_if()
    it = find_if(mySet.begin(), mySet.end(), [](const int &curNum){return ((curNum * curNum) == 256);});            // Find the item having value of 16
    it != mySet.end() ? (cout << "Found item is: " << *it << endl) : (cout << "Item is not found." << endl);

    // 3. find_if_not()
    it = find_if_not(mySet.begin(), mySet.end(), [](const int &curNum){return (curNum - 1 == 7);});                 // Find first having no value of 6
    it != mySet.end() ? (cout << "Found item is: " << *it << endl) : (cout << "Item is not found." << endl);

    // 4. find_end: finds subsequent from the end (searches for the last occurrence of the sequence [s_first, s_last) in the range [first, last))
    it = find_end(mySet.begin(), mySet.end(), subSet.begin(), subSet.end(), [](const int &setItem, const int &subSetItem){return (setItem == subSetItem);});        // Use a binary predicate
    it = find_end(mySet.begin(), mySet.end(), subSet.begin(), subSet.end());                                                                                        // This just compares numbers
    for (size_t i = 0; i != subSet.size(); ++i)                                 // Print out found subset iterating through the initial set (using subSet's size)
        cout << (*it++) << ' ';                                                 // Take the unchanged iterator value, dereference and as a side effect - incrementing for the next iteration
    cout.put('\n');

    // Mini-test of prefix and postfix operators
    // it = mySet.begin();
    // cout << *(it++++++) << endl;                                                // (!) This increments iterator itself ONCE: since associativity is left to right, iterator's value is taken, scheduled for decrementing in the sequence point and initial value is passed by value to the next postfix ++ for decrementing, so it doesn't make sense
    // cout << *it << endl;                                                        // So, this is the second element always
    // cout << *(++++++it) << endl;                                                // Gives 5-th element, since prefix returns a reference with right-to-left associativity
    // int i = 10;
    // // i++++;                                                                   // restricted: "expression must be a modifiable lvalue"
    // ++++++++i;
    // cout << i;

    // 5. find_first_of(): finds what item is the closest to the beginning of the first container comparing with all from the second
    // (finds the first occurence of any of the second pair of iterators within the first pair of iterators
    vector<int> myVector{1, 2, 3, 4, 5, 7, 8, 9};                               // Use vector here to subtract iterator value with the myVector.begin() after the finding to have an index
    vector<int> subVector{5, 7, 8, 2};                                          // May be used not vector (set or another container)

    auto it2 = find_first_of(myVector.begin(), myVector.end(), subVector.begin(), subVector.end());                                                               // Just compares by value
    it2 = find_first_of(myVector.begin(), myVector.end(), subVector.begin(), subVector.end(), [](const int &vectItem, const int &subVectItem){return (vectItem == subVectItem);});    // Or using binary predicate (should find value of 2)
    if (it2 != myVector.end())
        cout << "find_first_of(): " << *it2 << " at position: " << it2 - myVector.begin() << endl;

    // 6. search(): finds subsequence from the beginning, two variations
    subVector.pop_back();            // Remove 2 from subVector to have 5, 7, 8
    it2 = search(myVector.begin(), myVector.end(), subVector.begin(), subVector.end(), [](const int &setItem, const int &subSetItem){return (setItem == subSetItem);});        // Use a binary predicate
    it2 = search(myVector.begin(), myVector.end(), subVector.begin(), subVector.end());                                                                                        // This just compares numbers
    it2 != myVector.end() ? (cout << "Subsequent is found: "  << endl) : (cout << "Subsequent is not found. " << endl);

    // 7. search_n(): finds a sequence of n elements equal to specified (consecutive), or satisfying the condition
    it2 = search_n(myVector.begin(), myVector.end(), 1, 7);
    it2 != myVector.end() ? (cout << "Subsequent is found at: "  << it2 - myVector.begin() << endl) : (cout << "Subsequent is not found. " << endl);
    // search three elements more-equal than 4. Note: need to specify value in any case and use it as value
    it2 = search_n(myVector.begin(), myVector.end(), 3, 4, [](const int &curItem, const int &value){return (curItem >= value);});
    it2 != myVector.end() ? (cout << "Subsequent is found at: "  << it2 - myVector.begin() << endl) : (cout << "Subsequent is not found. " << endl);

    // 8. adjacent_find(): looks for any two neighbouring elements that are matching, or any two consecutive elements satisfying a condition passed in with the predicate
    myVector.push_back(9);                                      // Add 9 at the end to have two equal alements
    it2 = adjacent_find(myVector.begin(), myVector.end());      // Find to equal elements
    it2 != myVector.end() ? (cout << "Subsequent is found at: "  << it2 - myVector.begin() << endl) : (cout << "Subsequent is not found. " << endl);

    // Find two consecutive satisfying the condition. (!!) Need to check both items AND order is important: 2, 3 works. 3, 2 - doesn't work
    it2 = adjacent_find(myVector.begin(), myVector.end(), [](const int &firstItem, const int &secondItem){return (firstItem == 2) && (secondItem == 3);});
    it2 != myVector.end() ? (cout << "Subsequent is found at: "  << it2 - myVector.begin() << endl) : (cout << "Subsequent is not found. " << endl);

    return 0;
}
