#include <iostream>
// Example program to reverse an array

using namespace std;

// Function definitions
void printArray(int *const arrayPtr, const int arraySize);
void reverseArray(int *const arrayPtr, const int arraySize);

// Constants
const int ARRAY_SIZE = 11;

int main(int argc, char const *argv[])
{
    // Initialize and print the array
    int intsArray[ARRAY_SIZE]{1, 3, 5, 7, 9, 300, 4, 6, 8, 10, 500};
    printArray(intsArray, ARRAY_SIZE);

    // Reverse and print the array
    reverseArray(intsArray, ARRAY_SIZE);
    printArray(intsArray, ARRAY_SIZE);

    return 0;
}

void printArray(int const *const arrayPtr, const int arraySize){
    for (int i = 0; i < arraySize; i++)
        cout << arrayPtr[i] << " ";
    cout << endl;
}

void reverseArray(int *const arrayPtr, const int arraySize){
    for (int i = 0; i < arraySize / 2; i++){
        std::swap(arrayPtr[i], arrayPtr[arraySize - i - 1]);
    }
}