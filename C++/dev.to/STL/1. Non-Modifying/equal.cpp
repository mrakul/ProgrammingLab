#include <iostream>
#include <set>
#include <algorithm>

/*** equal() examples ***/

using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Define containers
    vector<int> myVector1{1, 2, 3, 4, 5, 7, 8, 9};
    vector<int> myVector2{myVector1};

    // 1. equal() example.
    // Note: equal() checks if the first passed range is part of the second one starting from the specified point defined by the third parameter
    bool areEqual = equal(myVector1.begin(), myVector1.end(), myVector2.begin());
    areEqual ? (cout << "Ranges are equal. " << endl) : (cout << "Ranges are not equal." << endl);

    myVector2.pop_back();                               // Size 7, capacity 8
    areEqual = equal(myVector1.begin(), myVector1.end(), myVector2.begin());                            // Equal
    areEqual ? (cout << "Ranges are equal. " << endl) : (cout << "Ranges are not equal." << endl);

    myVector2.shrink_to_fit();                          // Size 7, capacity 7
    areEqual = equal(myVector1.begin(), myVector1.end(), myVector2.begin());                            // Not equal
    areEqual ? (cout << "Ranges are equal. " << endl) : (cout << "Ranges are not equal." << endl);

    // 2. equal() using predicate
    myVector2.push_back(9);                             // Return 9 back
    areEqual = equal(myVector1.begin(), myVector1.end(), myVector2.begin(), [](const int &firstRangeItem, const int &secondRangeItem){return (firstRangeItem == secondRangeItem);});
    areEqual ? (cout << "Ranges are equal. " << endl) : (cout << "Ranges are not equal." << endl);

    // 3. equal() example to compare vector and set
    set<int> mySet{};
    vector<int> myVector3{5, 4, 3, 2, 1};
    copy(myVector3.begin(), myVector3.end(), insert_iterator<set<int>>(mySet, mySet.begin()));
    for_each(mySet.begin(), mySet.end(), [](const int &curItem){cout << curItem << " ";});

    // Check in forward direction => Not equal
    areEqual = equal(myVector3.begin(), myVector3.end(), mySet.begin());
    areEqual ? (cout << "Ranges are equal. " << endl) : (cout << "Ranges are not equal." << endl);

    // Check in reverse direction => Equal
    areEqual = equal(myVector3.rbegin(), myVector3.rend(), mySet.begin());
    areEqual ? (cout << "Ranges are equal. " << endl) : (cout << "Ranges are not equal." << endl);

    return 0;
}
