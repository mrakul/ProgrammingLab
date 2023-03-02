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

    // 2. partition(): makes a range partitioned, that is moves all the items satisfying the condition to the front
    // Important: partition() is not stable, so the relative order may be not preserved after partitioning
    vectorIsPartitioned = is_partitioned(vectorOfPersons.begin(), vectorOfPersons.end(), lambdaIsSimpson);
    cout << "Vector is partitioned: " << (vectorIsPartitioned ? "True" : "False") << endl;                  // Not all Simpsons are before the rest => False

    auto afterTruePart = partition(vectorOfPersons.begin(), vectorOfPersons.end(), lambdaIsSimpson);        // Make partition, Move Assignment is used. Returns one past the end of True section
    vectorIsPartitioned = is_partitioned(vectorOfPersons.begin(), vectorOfPersons.end(), lambdaIsSimpson);  // Now, all Simpsons are before the rest => True
    cout << "Vector is partitioned: " << (vectorIsPartitioned ? "True" : "False") << endl;

    printVector(vectorOfPersons);                                                                           // Print the vector after partitioning
    cout << "The first after True section is: " << *afterTruePart << endl;                                  // Print the first after the True section (Trump)

    // 3. partition_copy(): specifics, that the 3-rd parameter specifies the start for the passed predicate (True) and 4-th is the start for failed (False)
    // Also, it returns a pair of iterators pointing to one past the passed predicate region (True) and the same for failed (False)
    vector<Person> targetVector(vectorOfPersons.size() * 2);                                                // Makes the target vector 2 sizes of the source

    auto lambdaIsTrump = [](const Person &curPerson){ return (curPerson.surname == "Trump");};              // Now, have lambda for Trump. (!) Obligatory to have CONST Person& here
    pair<vector<Person>::iterator, vector<Person>::iterator> trueFalseStart;
    trueFalseStart = partition_copy(vectorOfPersons.begin(), vectorOfPersons.end(),
                                    targetVector.begin(), targetVector.begin() + 3, lambdaIsTrump);         // Place True at the beginning, and False at 3-rd position
                                                                                                            // In the source vector, all Simpsons are at the beginning, Trump at the end

    vectorIsPartitioned = is_partitioned(targetVector.begin(), targetVector.end(), lambdaIsTrump);          // Trump is at the top now
    cout << "Vector is partitioned: " << (vectorIsPartitioned ? "True" : "False") << endl;                  // Returns True
    printVector(targetVector);                                                                              // [0] = Trump, [1], [2] = NoName, since we placed false at the 3-rd, [3].. = Simpsons

    cout << "First of passed predicate is: " << *(trueFalseStart.first - 1)
         << "First of failed predicate is: " << *(trueFalseStart.second - 1) << endl;                       // Just to check the value of iterators returned: print out last Persons of True and False regions

    // 4. stable_partition(): the same as partition, but it preserves the relative order of items
    stable_partition(targetVector.begin(), targetVector.end(), lambdaIsSimpson);                            // Move Simpsons to the top
    vectorIsPartitioned = is_partitioned(targetVector.begin(), targetVector.end(), lambdaIsSimpson);
    cout << "Vector is partitioned: " << (vectorIsPartitioned ? "True" : "False") << endl;                  // Returns True
    printVector(targetVector);                                                                              // Order between Simpsons is preserved

    // 5. partition_point(): finds the one past the end of parition, that is works with paritioned ranges
    // Returns an iterator to the first element in the partitioned range [first,last) for which pred is not true, indicating its partition point
    vector<Person>::iterator partPoint = partition_point(targetVector.begin(), targetVector.end(), lambdaIsSimpson);    // Find an item following all the Simpsons
    cout << "Partition point is: " << *partPoint << endl;                                                               // Trump is expected

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem;
    cout << endl;
}