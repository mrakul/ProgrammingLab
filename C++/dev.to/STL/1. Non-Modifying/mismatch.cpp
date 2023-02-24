#include <iostream>
#include <set>
#include <algorithm>

/*** mismatch() examples ***/

using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Define containers
    vector<int> myVector1{1, 2, 3, 4, 5};
    vector<int> myVector2{1, 2, 3, 7};                  // Since vector2 is less than vector1, first mismatch will be 4 and 7. But if remove 7, the first mismatch will be 4 and the value at the myVector2.end() position (one past the end)

    // 1. mismatch() example. It supposed that the second range is more than the first - general rule for the STL algorithms!
    auto mismatchPair = mismatch(myVector1.begin(), myVector1.end(), myVector2.begin());                                // Returns a pair of iterators

    if (mismatchPair.first != myVector1.end())                                                                          // If there are mismatches
        cout << "Mismatching elements are " << *mismatchPair.first << " and " << *mismatchPair.second << "\n";

    // 2. The same using predicate
    mismatchPair = mismatch(myVector1.begin(), myVector1.end(), myVector2.begin(), [](const int &firstRangeItem, const int &secondRangeItem){return (firstRangeItem == secondRangeItem);});
    if (mismatchPair.first != myVector1.end())
        cout << "Mismatching elements are " << *mismatchPair.first << " and " << *mismatchPair.second << "\n";

    return 0;
}
