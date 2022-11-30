#include <iostream>

using namespace std;

void bubbleSort(int *arrayToSort, int arraySize);
void printArray(int const *const arrayPtr, const int arraySize);

int main(int argc, char const *argv[])
{
    const int ARRAY_SIZE = 10;
    int intArray[ARRAY_SIZE]{5, 3, 6, 8, 10, -1, 4, 7, -3, -5};
    printArray(intArray, ARRAY_SIZE);
    bubbleSort(intArray, ARRAY_SIZE);

    return 0;
}

void bubbleSort(int *arrayToSort, int arraySize)
{
    for (int i = 0; i < arraySize - 1; i++){                           // Number of cycles
        for (int j = 0; j < arraySize - i - 1; j++){                   // Type of the cycle depending on the iteration, cutting of the previous maximum
            if (arrayToSort[j] > arrayToSort[j + 1])
                swap(arrayToSort[j], arrayToSort[j + 1]);
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
