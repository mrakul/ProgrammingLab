#include <iostream>

using namespace std;
/*** This is Lomuto's Quick Sort implementation: the last item value is considered as the pivot value. ***/
// This algorithm is unstable!

void printArray(int const *const arrayPtr, const int arraySize);

// makeParitions() is to find the corresponding place of the pivot - the item dividing the array in two ranges: less than the pivot and more-equal than the pivot.
// The last item value is chosen as the pivot value, so everything is compared to that value: arrayToSort[highIndex]
int makePartitions(int *arrayToSort, int lowIndex, int highIndex)
{
    int pivotPosition = lowIndex;                                           // Set the first item as pivot position. If there are no less items, place the pivot to the first item by default

    for (int curIndex = lowIndex; curIndex < highIndex; curIndex++){        // Checks from the first till the one before the last, since the last is the pivot value
        if (arrayToSort[curIndex] < arrayToSort[highIndex]){                // If the current is less than the pivot (<= can be used, then equal items are getting close from the right)
            if (curIndex != pivotPosition)                                  // To prevent copy at the same position, but can be made unconditional
                swap(arrayToSort[curIndex], arrayToSort[pivotPosition]);    // Place a smaller item at the place of the current preliminary pivot position
            pivotPosition++;                                                // Move forward the pivot position
        }
    }
    swap(arrayToSort[pivotPosition], arrayToSort[highIndex]);                // Place the pivot value at the position right after all smaller items

    return pivotPosition;                                                    // Return the pivot position. Note: current's pivot position is unchanged till the end of the sorting including quickSort() sub-calls
}

void quickSort(int *arrayToSort, int lowIndex, int highIndex)
{
    if (lowIndex < highIndex){                                                     // Stop recursion: high index can be -1 if the pivot given before is 0, then the processing only for the right range. Or they are equal (one item after/before pivot), or low is more (no items after/before pivot)
        int pivotPosition = makePartitions(arrayToSort, lowIndex, highIndex);      // Find the pivot position
        quickSort(arrayToSort, lowIndex, pivotPosition - 1);                       // Call for the part before the pivot
        quickSort(arrayToSort, pivotPosition + 1, highIndex);                      // Call for the part after the pivot
    }
}

int main(int argc, char const *argv[])
{
    // int intArray[]{5, 3, -6, 6, 3, -10, -1, 3, 7, -3, 7};
    // int intArray[]{5, 4, 3, 2, 1};
    // int intArray[]{1, 2, 3, 4, 5};
    // int intArray[]{3, 1, 5, 3, 7, 3};
    int intArray[]{3, 7, 5, 4, 4, 1, 10, 5};

    cout << "Print the initial array state:\n";
    int arraySize = sizeof(intArray) / sizeof(*intArray);
    printArray(intArray, arraySize);

    quickSort(intArray, 0, arraySize - 1);                                  // Call covering all the items from the first till the last

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