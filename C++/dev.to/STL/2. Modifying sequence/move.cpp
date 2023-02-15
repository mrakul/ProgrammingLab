#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "person.h"

/*** move() examples ***/

void printVector(auto &vectToOut);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create two vectors of the same size and print their states. Person Class have Move Assignment operator defined
    vector<Person> sourceVector{{"Lane", "Fane"}, {"Wow", "Cringe"}, {"Jane", "Rain"}};
    vector<Person> targetVector(sourceVector.size());
    printVector(sourceVector);
    printVector(targetVector);

    // 1. Use move() to move data from the target to the source vector
    move(sourceVector.begin(), sourceVector.end(), targetVector.begin());

    // 2. Print the vectors again: target contains the data of the source, source data is empty, as expected
    printVector(sourceVector);
    printVector(targetVector);

    // move_backward() explanation is the same as for copy_backward, so omitting example

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem;
    cout << endl;
}