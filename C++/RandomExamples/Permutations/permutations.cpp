#include <iostream>
#include <cstring>

using namespace std;

const int NUM_OF_LETTERS = 10;

void printPermutations(char *stringToPermute, int startIndex, int endIndex);

int main(int argc, char const *argv[])
{
    char charArray[NUM_OF_LETTERS]{'A', 'B', 'C', 'D'};                    // char charArray[NUM_OF_LETTERS]{"ABCD"} is allowed
    printPermutations(charArray, 0, strlen(charArray) - 1);                // Pass the ending index in array

    // By using std::next_permutation()                                    // To use this function a string should be in ascending order, that is the last state is descending order
    // std::string stringToPermute("ABCD");
    // do{
    //     std::cout << stringToPermute << "\n";
    // } while (std::next_permutation(stringToPermute.begin(), stringToPermute.end()));

    return 0;
}

void printPermutations(char *stringToPermute, int startIndex, int endIndex)
{
    if (startIndex == endIndex)                                                            // End recursion condition: when only the subset is one letter (no permutations need more)
        std::cout << stringToPermute << endl;
    else
        for (int i = startIndex; i <= endIndex; i++){
            swap(stringToPermute[startIndex], stringToPermute[i]);                          // Place the current letter at the first position, and the first letter to the current position (at first iteration the first letter stays at its own position)
            printPermutations(stringToPermute, startIndex + 1, endIndex);                   // Make the same with subset without the first letter
            swap(stringToPermute[startIndex], stringToPermute[i]);                          // Return everything back
        }
}
