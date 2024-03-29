#include <iostream>

using namespace std;

// Additional notes: bubble sort is stable.
// "A sorting algorithm is stable if two objects with equal keys are in the same order in the sorted output as they were in the input data set"

void bubbleSort(int *arrayToSort, int const arraySize);
void printArray(int const *const arrayPtr, const int arraySize);

int main(int argc, char const *argv[])
{
    const int ARRAY_SIZE = 10;
    int intArray[ARRAY_SIZE]{5, 3, 6, 8, 10, -1, 4, 7, -3, -5};
    cout << "Print the initial array state:\n";
    printArray(intArray, ARRAY_SIZE);
    cout.put('\n');

    cout << "Print the steps of soritng:\n";
    bubbleSort(intArray, ARRAY_SIZE);

    return 0;
}

void bubbleSort(int *arrayToSort, int const arraySize)
{
    for (int i = 0; i < arraySize - 1; i++){                           // Number of cycles: 9 max findings for 10-length array
        for (int j = 0; j < arraySize - i - 1; j++){                   // Type of the cycle depending on the iteration, cutting of the previous maximum
            if (arrayToSort[j] > arrayToSort[j + 1])                   // If the current is more than the next
                swap(arrayToSort[j], arrayToSort[j + 1]);              // Swap them
            printArray(arrayToSort, arraySize);                        // Print after step of comparing
        }
        // printArray(arrayToSort, arraySize);                         // Print after every cycle "bubbling" maximum on the top
    }
}

void printArray(int const *const arrayPtr, const int arraySize)
{
    for (int i = 0; i < arraySize; i++)
        cout << arrayPtr[i] << " ";
    cout << endl;
}
