#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

/*** replace() examples ***/

void printContainer(auto &containerToPrint);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create two vectors: source is filled and empty target. Note: for sets, replace() doesn't work since the keys are unchangeble things, so need to erase and insert a new data
    vector<int> sourceVector{1, 2, 3, 4, 5, 7, 8, 9};
    vector<int> targetVector;
    printContainer(sourceVector);

    // 1. Simple replace() example: replaces all values encountered with specified value
    replace(sourceVector.begin(), sourceVector.end(), 5, 11);
    printContainer(sourceVector);

    // 2. replace_if(): changes if an item satisfies the condition, use predicate
    replace_if(sourceVector.begin(), sourceVector.end(), [](int &curItem){return (curItem < 3 || curItem > 7);}, 33);
    printContainer(sourceVector);

    // 3. replace_copy(): replaces the old value with the specified and copy to the output container
    replace_copy(sourceVector.begin(), sourceVector.end(), sourceVector.begin(), 33, 55);                   // Use the same vector as the target
    printContainer(sourceVector);

    targetVector.reserve(sourceVector.size());                                                              // Expand the target vector before: capacity is increased, but size is 0, so need to use back_inserter() anyway to move the last position's iterator
    printContainer(targetVector);
    replace_copy(sourceVector.begin(), sourceVector.end(), back_inserter(targetVector), 33, 55);            // Copy to another vector
    printContainer(targetVector);

    // 4. replace_copy_if(): the same but replace if condition passed. Use the same target vector as input and output
    replace_copy_if(targetVector.begin(), targetVector.end(), targetVector.begin(), [](int &curItem){return (curItem == 55);}, 100);
    printContainer(targetVector);

    return 0;
}

void printContainer(auto &containerToPrint)
{
    cout << "Vector's size and capacity: " << containerToPrint.size() << " "  << containerToPrint.capacity() << endl;
    for (auto &curItem : containerToPrint)
        cout << curItem << ", ";
    cout << endl;
}