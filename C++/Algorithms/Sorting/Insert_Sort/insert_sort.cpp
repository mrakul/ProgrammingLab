#include <iostream>
#include <vector>

using namespace std;

/*** Inserting sort implementation ***/
// The idea is to mark the part of the array as sorted. Initially, only one element is sorted.
// Next value after sorted part is compared sequentially back to the firist element and placed to the correct place (stop when it is more than some of the )

void insertSort(int *arrayToSort, const int arraySize);
void printArray(int const *const arrayPtr, const int arraySize);

int main(int argc, char const *argv[])
{
    // 1. Check on the C array
    const int ARRAY_SIZE = 10;
    int intArray[ARRAY_SIZE]{5, 3, 6, 8, 10, -1, 4, 7, -3, -5};
    // int intArray[ARRAY_SIZE]{10, 7, 5, -3, - 10};

    cout << "Print the initial array state:\n";
    printArray(intArray, ARRAY_SIZE);
    cout.put('\n');
    cout << "Print the steps of soritng:\n";
    insertSort(intArray, ARRAY_SIZE);

    return 0;
}

void insertSort(int *arrayToSort, const int arraySize)
{
    for (int i = 1; i < arraySize; i++){                           // Start from the second element, since the first is considered sorted
        int sortedPartIdx = i - 1;                                 // Index of the sorted part is before the current to check at the end of the cycle

        while (sortedPartIdx >= 0 && arrayToSort[sortedPartIdx + 1] < arrayToSort[sortedPartIdx]){      // Go back until reaching the first element AND current value to insert is more than current in the sorted part
            swap(arrayToSort[sortedPartIdx], arrayToSort[sortedPartIdx + 1]);                           // Swap if sorted is more than the current to check
            sortedPartIdx--;                                                                            // Move sorted part back for one element (before where the current is placed) and move till the beginning of the array
        }
        printArray(arrayToSort, arraySize);                    // Print after every checking
    }
}

void printArray(int const *const arrayPtr, const int arraySize)
{
    for (int i = 0; i < arraySize; i++)
        cout << arrayPtr[i] << " ";
    cout << endl;
}
