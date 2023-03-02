#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include "../PersonClass/person.h"

/*** Partitioning algorithms examples ***/

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
    vector vectorOfNumbers{7, 9, 13, 2, 1, 8, 5, 6, 4};                                                 // C++20 allows class template argument deduction, so 'vector' keyword is enough
    for_each(vectorOfNumbers.begin(), vectorOfNumbers.end(), [](const int &curItem){cout << curItem << " ";});
    cout.put('\n');

    partial_sort(vectorOfNumbers.begin(), vectorOfNumbers.begin() + 4, vectorOfNumbers.end());          // Sorted is only [0; 4) part, the rest is random
    for_each(vectorOfNumbers.begin(), vectorOfNumbers.end(), [](const int &curItem){cout << curItem << " ";});
    cout.put('\n');

    // 4. partial_sort_copy(): noticeable that this function has full output range [out.begin(); out.end()), so this number of sorted items will be copied
    vector vectorOfNumbers2{7, 9, 13, 2, 1, 8, 5, 6, 4};
    vector outVector(vectorOfNumbers2.size(), 0);
    for_each(vectorOfNumbers2.begin(), vectorOfNumbers2.end(), [](const int &curItem){cout << curItem << " ";});
    cout.put('\n');

    auto numIsGreater = [](const int &firstNum, const int &secondNum){return (firstNum > secondNum);};
    auto sortedPartIt = partial_sort_copy(vectorOfNumbers2.begin(), vectorOfNumbers2.end(), outVector.begin(), outVector.begin() + 5, numIsGreater);
    for_each(outVector.begin(), sortedPartIt, [](const int &curItem){cout << curItem << " ";});                   // Copied only [0; 5) of sorted part according to the out range
    printVector(outVector);                                                                                       // Just as refresher that size and capacity are both 9/9 as before
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