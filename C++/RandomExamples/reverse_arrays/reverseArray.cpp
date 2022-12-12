#include <iostream>
#include <array>
// Example program to reverse an array

const int ARRAY_SIZE = 11;

using namespace std;

void printArray(array<int, ARRAY_SIZE> &arrayToPrint);
void reverseArray(array<int, ARRAY_SIZE> &arrayToRevert);

int main(int argc, char const *argv[])
{
    // Initialize and print the array
    array<int, ARRAY_SIZE> intsArray{1, 3, 5, 7, 9, 300, 4, 6, 8, 10, 500};
    printArray(intsArray);

    // Reverse and print the array
    reverseArray(intsArray);
    printArray(intsArray);

    return 0;
}

void printArray(array<int, ARRAY_SIZE> &arrayToPrint){
    for(const &curInt : arrayToPrint)
        cout << curInt << " ";
    cout << endl;
}

void reverseArray(array<int, ARRAY_SIZE> &arrayToRevert){
    for(size_t i = 0; i < arrayToRevert.size() / 2; i++)
        std::swap(arrayToRevert.at(i), arrayToRevert.at(arrayToRevert.size() - i - 1));
}