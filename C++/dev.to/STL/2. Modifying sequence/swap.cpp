#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "person.h"

/*** swap() examples ***/

void printVector(auto &vectToOut);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create two vectors of the same size and print their states. Person Class have Move Assignment operator defined
    vector<Person> sourceVector{{"Lane", "Fane"}, {"Wow", "Cringe"}, {"Jane", "Rain"}};
    vector<Person> targetVector(sourceVector.size() - 1);                                           // Make the target vector's size less than the source's intentionally
    printVector(sourceVector);
    printVector(targetVector);

    // 1. Swap the vectors' data and print it out, vector's names can be used explicitly even if the lengths are not equal
    swap(sourceVector, targetVector);
    printVector(sourceVector);
    printVector(targetVector);

    // 2. swap_range() example: it can be observed that it creates temporary Person objects for swapping (as the size of the source vector)
    // Again, the source's size es expected to be more than target. Anyway, Segmentation Fault when trying to printVector (or during swap_ranges())
    swap_ranges(sourceVector.begin(), sourceVector.end(), targetVector.begin());
    printVector(sourceVector);
    printVector(targetVector);

    // 3. iter_swap(): swaps iterators' content instead of the data itself. Also, creates a temporary Person object
    iter_swap(sourceVector.begin(), targetVector.begin());
    printVector(sourceVector);
    printVector(targetVector);

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem;
    cout << endl;
}