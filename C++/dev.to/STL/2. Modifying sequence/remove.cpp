#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "person.h"

/*** remove() examples:
***/

void printVector(auto &vectToOut);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create a vector and a list of the same content
    vector<int> myVector{1, 2, 3, 4, 3, 5, 3, 7, 8, 9};

    list<int> myList(myVector.size());
    copy(myVector.begin(), myVector.end(), myList.begin());
    list<int> myList2(myList);

    // 1. remove() example: use erase-remove idiom (as in the Jacek Galowicz's example)
    cout << "Vector's state before remove: " << endl;
    printVector(myVector);

    auto removedPartVect = remove(myVector.begin(), myVector.end(), 3);                         // Returns an iterator to the part moved at the end of the vector (non-removed items moved at the removed items place sequentially)
    cout << "Vector's state after remove: " << endl;
    printVector(myVector);                                                                      // Size and capacity are the same

    myVector.erase(removedPartVect, myVector.end());                                            // Cut off the last part containing unwanted elements
    printVector(myVector);                                                                      // Size has been changed, but capacity is the same

    myVector.shrink_to_fit();                                                                   // We can decrease capacity if required
    printVector(myVector);                                                                      // Capacity has been changed

    // 2. remove() example with the list: it works the same as for vector,
    for_each(myList.begin(), myList.end(), [](const int &curItem){cout << curItem << " ";});
    cout.put('\n');

    auto removedPartList = remove(myList.begin(), myList.end(), 3);                             // The same as for vector: non-removed items moved to the removed items place
    for_each(myList.begin(), myList.end(), [](const int &curItem){cout << curItem << " ";});
    cout.put('\n');

    myList.erase(removedPartList, myList.end());                                                // Cut off the end part of the list
    for_each(myList.begin(), myList.end(), [](const int &curItem){cout << curItem << " ";});
    cout.put('\n');

    // Check list.remove() instead
    for_each(myList2.begin(), myList2.end(), [](const int &curItem){cout << curItem << " ";});
    cout.put('\n');

    myList2.remove(3);
    for_each(myList2.begin(), myList2.end(), [](const int &curItem){cout << curItem << " ";});
    cout.put('\n');

    // (!) 3. Check with Person.h: demonstrate that Destructor is called only when container::erase() is called or, for the list, when list::remove()
    vector<Person> vectorOfPersons{{"One", "Cringe"}, {"Second", "Binge"}, {"Third", "Dringe"}, {"Fourth", "Fourth"}};
    list<Person> listOfPersons{{"One", "Cringe"}, {"Second", "Binge"}, {"Third", "Dringe"}, {"Fourth", "Fourth"}};
    list<Person> listOfPersons2{{"One", "Cringe"}, {"Second", "Binge"}, {"Third", "Dringe"}, {"Fourth", "Fourth"}};

    auto removedPartVect2 = remove(vectorOfPersons.begin(), vectorOfPersons.end(), Person{"Second", "Binge"});    // Returns an iterator to the part moved at the end of the vector (non-removed items moved at the removed items place)
    cout << "Vector's state after remove: " << endl;                                                              // No Destructors were called
    printVector(vectorOfPersons);                                                                                 // (!) Can be observed that move-semantics is used to move non-removed items at the place of removed close to the beginning sequentially

    vectorOfPersons.erase(removedPartVect2, vectorOfPersons.end());                                               // Cut off the last part containing unwanted elements. (!) Destructors are called by vector::erase()
    printVector(vectorOfPersons);                                                                                 // Note: I do not move ID of the object, only names are stolen as if ID gets another names

    // Check erase-remove with the list of Persons
    auto removedPartList2 = remove(listOfPersons.begin(), listOfPersons.end(), Person{"Second", "Binge"});        // (!) The same algorithm for the list: non-removed items are moved at the places of moved using move-semantics, holding their relative positions
    for_each(listOfPersons.begin(), listOfPersons.end(), [](auto &curItem){cout << curItem << " ";});
    cout.put('\n');

    listOfPersons.erase(removedPartList2, listOfPersons.end());                                                   // Destructor is called here for removed Person, which is at the end at this moment
    for_each(listOfPersons.begin(), listOfPersons.end(), [](auto &curItem){cout << curItem << " ";});
    cout.put('\n');

    // Check the list::remove() to see the Destructors calls
    listOfPersons2.remove(Person{"Second", "Binge"});                                                             // Here, for the list::remove() member function, destructor is called here: specified item is foind and destroyed (pointers are correctly )
    for_each(listOfPersons2.begin(), listOfPersons2.end(), [](auto &curItem){cout << curItem << " ";});           // No moving anything, IDs contains their names specified initially
    cout.put('\n');

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem << ", ";
    cout << endl;
}