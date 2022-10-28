#include <iostream>
#include <vector>
// Example program to reverse an vector

using namespace std;

void printArray(vector<int> &vectorToPrint);
void reverseArray(vector<int> &vectorToRevert);

int main(int argc, char const *argv[])
{
    // Initialize and print the vector
    vector<int> intsArray{1, 3, 5, 7, 9, 300, 4, 6, 8, 10, 500};
    printArray(intsArray);

    // Reverse and print the vector
    reverseArray(intsArray);
    printArray(intsArray);

    return 0;
}

void printArray(vector<int> &vectorToPrint){
    for(const &curInt : vectorToPrint)
        cout << curInt << " ";
    cout << endl;
}

void reverseArray(vector<int> &vectorToRevert){
    for(size_t i = 0; i < vectorToRevert.size() / 2; i++)
        std::swap(vectorToRevert.at(i), vectorToRevert.at(vectorToRevert.size() - i - 1));
}