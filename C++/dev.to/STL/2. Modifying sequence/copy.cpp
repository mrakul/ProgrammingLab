#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

/*** copy() examples ***/

void printVector(auto &vectToOut);
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> sourceVector{1, 2, 3, 4, 5, 7, 8, 9};
    vector<int> targetVector;                                                               // Size = 0, Capacity = 0
    auto printNum = [](const int &numToPrint){cout << numToPrint << ' ';};

    // 1. copy() example
    // copy(sourceVector.begin(), sourceVector.end(), targetVector.begin());                // This gives segmentation fault since copy just incrementing iterators, and targetVector doesn't contain elements at all
    copy(sourceVector.begin(), sourceVector.end(), insert_iterator<vector<int>>(targetVector, targetVector.begin()));           // Need to use insert_iterator() to insert and change the size of the vector
    // for_each(targetVector.begin(), targetVector.end(), printNum);
    printVector(targetVector);

    // 2. copy_n(): copies n elements from the source to the target, use back_insert_iterator to place the elements at the end now
    copy_n(sourceVector.begin(), 5, back_inserter(targetVector));                             // back_insert_iterator calls container.push_back() with the value passed
    printVector(targetVector);
    // copy_n(sourceVector.begin(), 5, back_insert_iterator<vector<int>>(targetVector));      // or explicitly specify the type of the container

    // 3. copy_if(): copy only the items matching the condition
    // Clear the elements by resizing, shrink-to-fit and then reserve enough space for copying from the source
    targetVector.resize(0);
    printVector(targetVector);
    targetVector.shrink_to_fit();
    printVector(targetVector);
    targetVector.reserve(sourceVector.size());
    printVector(targetVector);

    // Copy odd numbers and print the vector again
    copy_if(sourceVector.begin(), sourceVector.end(), back_inserter(targetVector), [](const int &curItem){return (curItem & 1);});
    printVector(targetVector);

    // 4. copy_backward(): copies in the backward direction using bidirectional iterators (starting from the last going to the first preserving relative order of the items)
    // Note from https://en.cppreference.com: the behavior is undefined if d_last is within (first, last]. std::copy must be used instead of std::copy_backward in that case.
    std::vector<int> inputNumbers{1, 2, 3, 4, 5, 6, 7};
    std::vector<int> outputNumbers(inputNumbers.size());

    printVector(outputNumbers);
    copy_backward(begin(inputNumbers), begin(inputNumbers) + 3, begin(outputNumbers) + 5);
    printVector(outputNumbers);
    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem << ", ";
    cout << endl;
}