#include <iostream>

using namespace std;

/*** This is Lomuto's quick sort implementation: the last element is considered as pivot and two pointers are used: lessEqual of pivot and curItem */
// This algorithm is unstable!

void printArray(int const *const arrayPtr, const int arraySize);

// This function finding the correct place of the pivot - element dividing the array in two ranges: less-equal to the pivot and more than pivot.
// The last element is chosen as pivot.
int makePartitions(int *arrayToSort, int lowIndex, int highIndex)
{
    int lessEqualIdx = lowIndex;                                            // Set the first element as less-equal. If there are no less-equal, place the pivot here to the first element

    for (int curItem = lowIndex; curItem < highIndex; curItem++){           // Checks from the first till the one before the last, since there is the pivot value
        if (arrayToSort[curItem] < arrayToSort[highIndex]){                 // If the current is less-equal than the pivot. (?) Is it enough to be just less or need to be less-equal
            swap(arrayToSort[curItem], arrayToSort[lessEqualIdx]);          // Place it on the lessEqualIdx place
            lessEqualIdx++;                                                 // Move the less-equal position forward
        }
    }

    swap(arrayToSort[lessEqualIdx], arrayToSort[highIndex]);                // Place the pivot at the position right after all less-equal

    return lessEqualIdx;                                                    // Return the pivot position. Note: its position is unchanged till the end
}

void quickSort(int *arrayToSort, int lowIndex, int highIndex)
{
    if (lowIndex < highIndex){                                              // Stop recursion: high index can be -1 if the pivot given before is 0, then we stops here. Or lowIndex more than highIndex of the pivot at the end. Or they are equal
        int pivot = makePartitions(arrayToSort, lowIndex, highIndex);       // Find the pivot position

        quickSort(arrayToSort, lowIndex, pivot - 1);                        // Call for the part before the pivot
        quickSort(arrayToSort, pivot + 1, highIndex);                       // Call for the part after the pivot
    }
}

int main(int argc, char const *argv[])
{
    // int intArray[]{5, 3, -6, 6, 3, -10, -1, 3, 7, -3, 7};
    // int intArray[]{5, 4, 3, 2, 1};
    // int intArray[]{1, 2, 3, 4, 5};
    int intArray[]{3, 1, 5, 3, 7, 3};

    cout << "Print the initial array state:\n";
    int arraySize = sizeof(intArray) / sizeof(*intArray);
    printArray(intArray, arraySize);

    quickSort(intArray, 0, arraySize - 1);                                  // Call covering all the elements from the first till the last

    cout << "Print array after sorting:\n";
    printArray(intArray, arraySize);

    return 0;
}

void printArray(int const *const arrayPtr, const int arraySize)
{
    for (int i = 0; i < arraySize; i++)
        cout << arrayPtr[i] << " ";
    cout.put('\n');
}