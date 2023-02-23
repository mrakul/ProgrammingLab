#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*** replace_n() implementation: replaces n number of encountered items in a container ***/

void printContainer(auto &containerToPrint);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create a vector, an iterator of the next item to be replaced and specify a number of items to be replaced
    vector<int> myVector{1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3};
    vector<int>::iterator nextToReplaceIt{myVector.begin()};
    size_t numOfItemsToReplace = 10;
    size_t initValToReplace = 3;
    size_t newValToSet = 99;

    printContainer(myVector);

    // 1. Make cycle checking number of items to replace and stop if the number is reached OR the end of the container is found (one past the end)
    for (size_t numOfReplaced = 0; numOfReplaced < numOfItemsToReplace && nextToReplaceIt != myVector.end(); ++numOfReplaced){
        nextToReplaceIt = find(nextToReplaceIt, myVector.end(), initValToReplace);                                              // Find from the previously replaced item
        replace(nextToReplaceIt, nextToReplaceIt + 1, initValToReplace, newValToSet);                                           // Replace the current found. Note: if we're at the end (no more items found to replace), it will not be replaced since initVal != newVal
        // advance(nextToReplaceIt, 1);                                                                                         // No need to move it forward, and if move it forward, will stop only when reach the numOfItemsToReplace since we can be at one past the end position already
        printContainer(myVector);
    }

    return 0;
}

void printContainer(auto &containerToPrint)
{
    cout << "Vector's size and capacity: " << containerToPrint.size() << " " << containerToPrint.capacity() << endl;
    for (auto &curItem : containerToPrint)
        cout << curItem << ", ";
    cout << endl;
}