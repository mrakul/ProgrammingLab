#include <iostream>
#include <vector>

using namespace std;

/*** Selection sort implementation ***/
// The idea is to go through an array finding the minimum on the every iteration.
// After finding the mininum it is placed on the first position of the current cycle.
// Below is unstable implementation (default of selection algorithm). But there is another stable implementation.

void selectionSort(int *arrayToSort, const int arraySize);
void selectionSortVector(vector<int> &vectorToSort);

void printArray(int const *const arrayPtr, const int arraySize);

int main(int argc, char const *argv[])
{
    // 1. Check on the C array
    const int ARRAY_SIZE = 10;
    int intArray[ARRAY_SIZE]{5, 3, 6, 8, 10, -1, 4, 7, -3, -5};
    // int intArray[ARRAY_SIZE]{10, 7, 5, -3, - 10};

    vector<int> intVector(intArray, intArray + ARRAY_SIZE);         // Initialize vector to check the same

    cout << "Print the initial array state:\n";
    printArray(intArray, ARRAY_SIZE);
    cout.put('\n');
    cout << "Print the steps of soritng:\n";
    selectionSort(intArray, ARRAY_SIZE);

    // 2. Check on the vector
    cout << "Print the initial vector state:\n";
    for_each(intVector.begin(), intVector.end(), [](decltype(intVector)::value_type &curInt){cout << curInt << " ";});
    cout.put('\n');

    cout << "Print the steps of soritng:\n";
    selectionSortVector(intVector);

    return 0;
}

void selectionSort(int *arrayToSort, const int arraySize)
{
    for (int i = 0; i < arraySize - 1; i++){                        // Number of cycles: 9 min findings for 10-length array
        int curMinIdx = i;                                          // The current minimum index is the first in the cycle

        for (int j = i; j < arraySize; j++)                         // Starting from the next after finding the previous min
            if (arrayToSort[j] < arrayToSort[curMinIdx])
                curMinIdx = j;                                      // Save the current min index

        if (i != curMinIdx)                                         // If initial minimum is not the found minimum
            swap(arrayToSort[i], arrayToSort[curMinIdx]);           // Place the minimun of the current cycle

        printArray(arrayToSort, arraySize);                         // Print after the current minumim placement at its new position
    }
}

void selectionSortVector(vector<int> &vectorToSort)
{
    for (vector<int>::size_type i = 0; i < vectorToSort.size() - 1; i++){                    // Number of cycles: 9 min findings for 10-length array
        unsigned int curMinIdx = i;                                                          // The current minimum index is the first in the cycle

        for (vector<int>::size_type j = i; j < vectorToSort.size(); j++)                     // Starting from the next after finding the previous min
            if (vectorToSort.at(j) < vectorToSort.at(curMinIdx))
                curMinIdx = j;                                                               // Save the current min index

        if (i != curMinIdx)                                                                  // If initial minimum is not the found minimum
            swap(vectorToSort.at(i), vectorToSort.at(curMinIdx));                            // Place the minimun of the current cycle

        for_each(vectorToSort.begin(), vectorToSort.end(), [](vector<int>::value_type const &curInt){cout << curInt << " ";});     // Print after the current minumim placement at its new position
        cout.put('\n');
    }
}

void printArray(int const *const arrayPtr, const int arraySize)
{
    for (int i = 0; i < arraySize; i++)
        cout << arrayPtr[i] << " ";
    cout << endl;
}
