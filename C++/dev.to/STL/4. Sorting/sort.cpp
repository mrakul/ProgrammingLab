#include <iostream>
#include <vector>
#include <algorithm>
#include "../PersonClass/person.h"

/*** Sorting algorithms examples ***/

void printVector(auto &vectToOut);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create a vector of partitioned and a list of non-partitioned Persons
    vector<Person> vectorOfPersons{{"Adam", "Simpson"}, {"Jack", "Simpson"}, {"Donald", "Trump"}, {"Lisa", "Simpson"}};
    printVector(vectorOfPersons);

    // 1. sort() example using predefined operator<() of being sorted items.
    // Note: it uses Random Access Iterators, so for the list its member function list::sort() should be used. Sort is unstable, so the relative order of items is not preserved
    sort(vectorOfPersons.begin(), vectorOfPersons.end());                           // Sort by surnames. Can be observed that Move semantics is used (Constructors and Move Assignment)
    printVector(vectorOfPersons);

    // 1.1 sort() using Binary Predicate to sort in descending order by names, for example, swap if Person1.name > Person2.name
    sort(vectorOfPersons.begin(), vectorOfPersons.end(), [](const Person &firstPerson, const Person &secondPerson){return (firstPerson.name > secondPerson.name);});
    printVector(vectorOfPersons);                               // Lisa => Jack => Donald => Adam, as expected. Move Semantics is used for creating temporary objects and operator=(&&) for swapping

    // 2. stable_sort(): it preserves the relative order of being sorted items. Note: list::sort() is guaranteed to be stable according to the C++ standard
    vector<Person> vectorOfPersons2{{"Adam", "Simpson"}, {"Jack", "Simpson"}, {"Donald", "Trump"}, {"Lisa", "Simpson"}};         // Try on the same input data
    printVector(vectorOfPersons);

    // sort(vectorOfPersons.begin(), vectorOfPersons.end(), [](const Person &firstPerson, const Person &secondPerson){return (firstPerson.surname > secondPerson.surname);});                                                             // Sort with no predicate, using operator<() of the class
    stable_sort(vectorOfPersons.begin(), vectorOfPersons.end(), [](const Person &firstPerson, const Person &secondPerson){return (firstPerson.surname > secondPerson.surname);});                                                             // Sort with no predicate, using operator<() of the class
    printVector(vectorOfPersons);                           // For this example, sort() and stable_sort() give the same results: Trump => Lisa Simpson => Jack Simpson => Adam Simpson

    // 3. partial_sort(): makes sorted only the first part of the container until up the middle iterator considering ALL the items of the source, the rest is in random state
    auto printOutNum = [](const int &curItem){cout << curItem << " ";};                                 // Lambda for all for_each()'es to print out the numbers

    vector vectorOfNumbers{7, 9, 13, 2, 1, 8, 5, 6, 4};                                                 // C++20 allows class template argument deduction, so 'vector' keyword is enough
    for_each(vectorOfNumbers.begin(), vectorOfNumbers.end(), printOutNum);
    cout.put('\n');

    partial_sort(vectorOfNumbers.begin(), vectorOfNumbers.begin() + 4, vectorOfNumbers.end());          // Sorted is only [0; 4) part, the rest is random
    for_each(vectorOfNumbers.begin(), vectorOfNumbers.end(), printOutNum);
    cout.put('\n');

    // 4. partial_sort_copy(): noticeable that this function has full output range [out.begin(); out.end()), so this number of sorted items will be copied
    vector vectorOfNumbers2{7, 9, 13, 2, 1, 8, 5, 6, 4};
    vector outVector(vectorOfNumbers2.size(), 0);
    for_each(vectorOfNumbers2.begin(), vectorOfNumbers2.end(), printOutNum);
    cout.put('\n');

    auto numIsGreater = [](const int &firstNum, const int &secondNum){return (firstNum > secondNum);};
    auto sortedPartIt = partial_sort_copy(vectorOfNumbers2.begin(), vectorOfNumbers2.end(), outVector.begin(), outVector.begin() + 5, numIsGreater);
    for_each(outVector.begin(), sortedPartIt, printOutNum);                                                       // Copied only [0; 5) of sorted part according to the out range
    printVector(outVector);                                                                                       // Just as refresher that size and capacity are both 9/9 as before
    cout.put('\n');

    // 5. is_sorted(): just returns bool of the result, and a Predicate can be passed
    for_each(vectorOfNumbers2.begin(), vectorOfNumbers2.end(), printOutNum);
    cout.put('\n');
    cout << boolalpha << "Vector is sorted: " << is_sorted(vectorOfNumbers2.begin(), vectorOfNumbers2.end()) << endl;

    sort(vectorOfNumbers2.begin(), vectorOfNumbers2.end());                                                       // Sort the vector using default operator<() of the class (ascending order)
    for_each(vectorOfNumbers2.begin(), vectorOfNumbers2.end(), printOutNum);
    cout.put('\n');
    cout << boolalpha << "Vector is sorted: " << is_sorted(vectorOfNumbers2.begin(), vectorOfNumbers2.end()) << endl;

    auto descendingNums = [](auto &firstItem, auto &secondItem){return firstItem > secondItem;};
    sort(vectorOfNumbers2.begin(), vectorOfNumbers2.end(), descendingNums);                                       // Sort the vector using Predicate in descending order
    for_each(vectorOfNumbers2.begin(), vectorOfNumbers2.end(), printOutNum);
    cout.put('\n');

    cout << boolalpha << "Vector is sorted in ascending order: " << is_sorted(vectorOfNumbers2.begin(), vectorOfNumbers2.end()) << endl;                    // Check ascending order first
    cout << boolalpha << "Vector is sorted in descending order: " << is_sorted(vectorOfNumbers2.begin(), vectorOfNumbers2.end(), descendingNums) << endl;   // Check descending order

    // 6. is_sorted_until(): returns the iterator after the sorted range, after the last element which is sorted
    vector<int> vectorOfNumbers3{1, 2, 3, 4, 22, 10, 11, 12, 13};
    for_each(vectorOfNumbers3.begin(), vectorOfNumbers3.end(), printOutNum);
    cout.put('\n');

    vector<int>::iterator sortedItemIt = is_sorted_until(vectorOfNumbers3.begin(), vectorOfNumbers3.end());       // Returns the iterator on the item after the last sorted
    cout << "Item after the sorted range is: " << *sortedItemIt << endl;

    sort(vectorOfNumbers3.begin(), vectorOfNumbers3.end());                                                       // Now, sort the vector and check the returned item
    for_each(vectorOfNumbers3.begin(), vectorOfNumbers3.end(), printOutNum);
    cout.put('\n');
    sortedItemIt = is_sorted_until(vectorOfNumbers3.begin(), vectorOfNumbers3.end());                             // Returns the iterator on the item after the last sorted
    cout << "Item after the sorted range is: " <<
            (sortedItemIt == vectorOfNumbers3.end() ? "One past the end" : to_string(*sortedItemIt)) << endl;     // Without to_string() "operand types are incompatible ("const char *" and "int")" message

    // 7. nth_element(): rearranges items and place on the n-th position an item as if the container would be sorted
    // Before the n-th are smaller or equal items with no particular order and larger items are after the n-th.
    // In other words, finds the n-th largest (or smallest) and places it on its corresponding placeS
    vector<int> vectorOfNumbers4{1, 2, 3, 4, 22, 10, 11, 12, 13};
    for_each(vectorOfNumbers4.begin(), vectorOfNumbers4.end(), printOutNum);
    cout.put('\n');

    nth_element(vectorOfNumbers4.begin(), vectorOfNumbers4.begin() + 4,  vectorOfNumbers4.end());                 // Find the 4-th largest and place it at the corresponding place ([4])
    for_each(vectorOfNumbers4.begin(), vectorOfNumbers4.end(), printOutNum);
    cout.put('\n');

    sort(vectorOfNumbers4.begin(),  vectorOfNumbers4.end());                                                      // Sort everything and check the place of the 4-th
    for_each(vectorOfNumbers4.begin(), vectorOfNumbers4.end(), printOutNum);
    cout.put('\n');

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem;
    cout << endl;
}