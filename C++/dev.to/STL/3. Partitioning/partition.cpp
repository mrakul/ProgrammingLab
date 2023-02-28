#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include "person.h"

/*** Partitioning algorithms examples ***/

void printVector(auto &vectToOut);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create a vector of partitioned and a list of non-partitioned Persons
    vector<Person> vectorOfPersons{{"Adam", "Simpson"}, {"Jack", "Simpson"}, {"Donald", "Trump"}, {"Lisa", "Simpson"}};
    list<Person> listOfPersons{{"Adam", "Simpson"}, {"Jack", "Simpson"}, {"Lisa", "Simpson"}, {"Donald", "Trump"}};

    // 1. is_partitioned(): checks if all the elements in the range [first,last) for which Predicate returns True precede those for which it returns False.
    // Important: main() is made a friend function to a Person class just for obviousness
    auto lambdaIsSimpson = [](const Person &curPerson){ return (curPerson.surname == "Simpson");};          // (!) Obligatory to have CONST Person& here
    auto vectorIsPartitioned = is_partitioned(vectorOfPersons.begin(), vectorOfPersons.end(), lambdaIsSimpson);
    auto listIsPartitioned = is_partitioned(listOfPersons.begin(), listOfPersons.end(), lambdaIsSimpson);

    cout << "Vector is partitioned: " << (vectorIsPartitioned ? "True" : "False") << endl;                  // Not all Simpsons are before the rest => False
    cout << "List is partitioned: " << (listIsPartitioned ? "True" : "False") << endl;                      // Simpsons are before the rest (for which the predicate gives false) = True

    // 1.1. is_paritioned(), try check with the set. Note: bool operator<() was implemented in Person.h and compares only surnames
    set<Person> setOfPersons;
    setOfPersons.insert({"Adam", "Simpson"});
    setOfPersons.insert({"Jack", "Simpson"});
    setOfPersons.insert({"List", "Simpson"});
    setOfPersons.insert({"Trump", "Simpson"});

    auto setIsPartitioned = is_partitioned(setOfPersons.begin(), setOfPersons.end(), lambdaIsSimpson);
    cout << "Set is partitioned: " << (setIsPartitioned ? "True" : "False") << endl;                        // All Simpsons are before the rest => True

    setOfPersons.insert(Person{"Ben", "Brooks"});                                                           // Brooks will be added before Simpsons according to the operator<() implementation
    setIsPartitioned = is_partitioned(setOfPersons.begin(), setOfPersons.end(), lambdaIsSimpson);
    cout << "Set is partitioned: " << (setIsPartitioned ? "True" : "False") << endl;                        // All Simpsons are before the rest => False

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem;
    cout << endl;
}