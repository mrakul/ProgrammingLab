#include <iostream>
#include <vector>
#include <algorithm>

/*** Binary search algorithms examples
 *  Important note: binary_search() takes ForwardIterators as input, not Random as expected.
 *  https://en.cppreference.com/w/cpp/algorithm/binary_search gives a note: "...However, for non-LegacyRandomAccessIterators, number of iterator increments is linear".
 *  binary_search() uses lower_bound() under the hood, and lower_bound() uses distance(first, last) and advance(it, step), so it is effective for vectors since translated easily to operating of addresses.
 *  For the rest of the containers (for example, for the list), this results in counting and iterating through the container actually by iterators.
 */

void printVector(auto &vectToOut);
using namespace std;

int main(int argc, char const *argv[])
{

    // 0. Create an unsorted vector intentionally
    vector vectorOfNumbers{6, 7, 13, 2, 9, 8, 5, 1, 4};
    printVector(vectorOfNumbers);
    cout << boolalpha;

    // 1. Try binary_search() on the unsorted vector: the behavior is undefined for unsorted vector
    // To remember: std::distance(__first, __last) in stl_algobase.h of lower_bound() counts steps till the one past the end, that is the last passed to a function
    cout << "Vector contains number 1 : " << binary_search(vectorOfNumbers.begin(), vectorOfNumbers.end(), 1) << endl;

    // 2. Sort the vector and try again: it returns bool True/False if the value is found or not
    sort(vectorOfNumbers.begin(), vectorOfNumbers.end());
    printVector(vectorOfNumbers);
    cout << "Vector contains number 1: " << (binary_search(vectorOfNumbers.begin(), vectorOfNumbers.end(), 1) ? "True" : "False") << endl;

    // 2.1 binary_search() with Predicate: try to find 4. Important: uses Binary Predicate as an input, so the value should be provided.
    // Returns an iterator pointing to the first element in the range [first, last) that DOES NOT satisfy (element < value) (or comp(element, value)), (i.e. greater or equal to), or last if no such element is found.
    // Note: the lambda used for binary_search(), lower_bound() should have a form which returns ​true if the first argument is less than (i.e. is ordered before) the second,
    // that is divide a range in two ranges: LESS THAN and EQUAL-OR-GREATER ranges
    // As a result, the returned value's iterator is EQUAL-OR-GREATER than the value provided

    // Good to remember: If (curNum < number), move right from the middle item. Otherwise, (curNum >= number), move left from the middle
    auto isLessThan = [](const int &curItem, const int &number){return curItem < number;};                      // if (curItem == number), returns False meaning that this is okay for us, since finding first False
    cout << "Vector contains number 6 using Binary Predicate: " << binary_search(vectorOfNumbers.begin(), vectorOfNumbers.end(), 6, isLessThan) << endl;
    cout << "Vector contains number 3 using Binary Predicate: " << binary_search(vectorOfNumbers.begin(), vectorOfNumbers.end(), 3, isLessThan) << endl;
    cout << "Vector contains number 12 using Binary Predicate: " << binary_search(vectorOfNumbers.begin(), vectorOfNumbers.end(), 12, isLessThan) << endl;
    cout << "Vector contains number 13 using Binary Predicate: " << binary_search(vectorOfNumbers.begin(), vectorOfNumbers.end(), 13, isLessThan) << endl;

    // 3. lower_bound() example: returns the iterator of the first item which is not less than the value provided (or which is not satisfying the Predicate condition).
    // If not found, returns container.end(). Note: it actually uses Binary Search when searching the item.
    // In other words, it finds the first item when (curItem < number) returns True, meaning LESS THAN and EQUAL-OR-GREATER ranges
    auto lowerBound = lower_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), 3);
    cout << "Lower bound after searching 3 is: " << *lowerBound << endl;                                        // Need to make [if (lowerBound != vectorOfNumbers.end())] if the value can be missing, surely

    // 3.1 lower_bound() using Comparator Binary Precidate
    lowerBound = lower_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), 3, isLessThan);
    cout << "Lower bound after searching 3 with Predicate is: " << *lowerBound << endl;
    lowerBound = lower_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), 10, isLessThan);
    cout << "Lower bound after searching 10 with Predicate is: " << *lowerBound << endl;

    // Specifics: if a value is out of specified range: if it is less than the first, returns the first of the range. If more than the [last - 1], returns last (one past the end)
    lowerBound = lower_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), -1, isLessThan);
    cout << "Lower bound after searching -1 with Predicate is: " << *lowerBound << endl;
    lowerBound = lower_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), 15, isLessThan);
    cout << "Lower bound after searching 15 with Predicate is: " << *lowerBound << endl;

    // 4. upper_bound() example: returns the iterator of the first item which is greater than the value provided (or which is not satisfying the Predicate condition).
    // The same as lower_bound(), but uses if (!(value < *it)) condition when finding an element.
    // So, the lambda meant to compare (number < curItem ) to have an element strictly GREATER than the value provided, the places of the current item and number to compare are swapped for that purpose below for obviousness
    // Note: but actually, they can be used interchangeably, since both returns True for Item1 < Item2, Comp will use it correctly itself

    // Good to remember: If (number < curItem), move left from the middle item. Otherwise, (number >= curItem), move right from the middle
    auto isLessThan2 = [](const int &number, const int &curItem){return number < curItem;};                     // if (curItem == number), returns False meaning that this is NOT okay for us due to the standard,
                                                                                                                // since the intention to find the first True, that is curItem STRICTLY GREATER than the number to compare
    auto upperBound = upper_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), 6);
    cout << "Upper bound after searching 6 is: " << *upperBound << endl;

    upperBound = upper_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), 8);
    cout << "Upper bound after searching 8 is: " << *upperBound << endl;
    upperBound = upper_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), 8, isLessThan2);
    cout << "Upper bound after searching 8 with Predicate is: " << *upperBound << endl;
    upperBound = upper_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), 10, isLessThan2);
    cout << "Upper bound after searching 10 with Predicate is: " << *upperBound << endl;

    // Specifics: if a value is out of specified range, the same as for lower_bound():
    // if it is less than the first, returns the first of the range. If more than the [end - 1], returns last (one past the end)
    upperBound = upper_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), -1, isLessThan2);
    cout << "Upper bound after searching -1 with Predicate is: " << *upperBound << endl;
    upperBound = upper_bound(vectorOfNumbers.begin(), vectorOfNumbers.end(), 15, isLessThan2);
    cout << "Upper bound after searching 15 with Predicate is: " << *upperBound << endl;

    // 5. equal_range() example: returns a pair of iterators reflecting lower and upper bounds for the value specified. Actually, it calls lower_bound() and upper_bound() to return
    // The first iterator points to the first element that is not less than the searched value. The second iterator points to the first element that is greater than that value.

    // auto [lowerBoundRange, upperBoundRange] = equal_range(vectorOfNumbers.begin(), vectorOfNumbers.end(), -1);                       // Use structured bindings (since C++17)
    pair<vector<int>::iterator, vector<int>::iterator> pairRangeIt;                                                                     // Can be used auto rangeIteratorsPair, sure

    pairRangeIt = equal_range(vectorOfNumbers.begin(), vectorOfNumbers.end(), -1);
    cout << "Equal Ranges: " << endl;
    cout << "-1, Lower Bound : " << *pairRangeIt.first << " Upper Bound : " << *pairRangeIt.second << endl;                             // Both return first item

    pairRangeIt = equal_range(vectorOfNumbers.begin(), vectorOfNumbers.end(), 20);
    cout << "20, Lower Bound : " << *pairRangeIt.first << " Upper Bound : " <<  *pairRangeIt.second << endl;                            // Borh returns [end - 1]

    // Predicate versions: uses the same principle passing the Comparator function returnung True when the Item1 < Item2
    pairRangeIt = equal_range(vectorOfNumbers.begin(), vectorOfNumbers.end(), 3, isLessThan);                                           // Value is not found
    cout << "3, Lower Bound : " << *pairRangeIt.first << " Upper Bound : " << *pairRangeIt.second << endl;                              // Both returns 4

    pairRangeIt = equal_range(vectorOfNumbers.begin(), vectorOfNumbers.end(), 9, isLessThan);                                           // Value is found
    cout << "9, Lower Bound : " << *pairRangeIt.first << " Upper Bound : " << *pairRangeIt.second << endl;                              // Returns 9 and 13

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem << " ";
    cout << endl;
}