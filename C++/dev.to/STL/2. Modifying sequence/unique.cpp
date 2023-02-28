#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void printVector(auto &vectToOut);

int main(int argc, char const *argv[])
{
    // 0. Create a vector containing equal items sequentially
    vector<int> myVector{1, 2, 2, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9, 9};
    printVector(myVector);

    // 1. unique(): removes non-unique sequential items and returns the new end. The same approach as for remove()
    auto newEnd = unique(myVector.begin(), myVector.end());
    printVector(myVector);
    myVector.erase(newEnd, myVector.end());                             // Cut off unwanted part as for remove() approach
    printVector(myVector);

    // 2. unique() using predicate
    newEnd = unique(myVector.begin(), myVector.end(), [](int &leftNum, int &rightNum){return (leftNum + 1 == rightNum);});         // Removes if next is more then the current by one
    printVector(myVector);
    myVector.erase(newEnd, myVector.end());                             // Cut off unwanted part as for remove() approach
    printVector(myVector);

    // 3. unique_copy(): copies the unique consecutive items to another container and returns the new end within the new container
    vector<int> sourceVector{1, 1, 1, 7, 7, 4, 4, 3, 3};
    vector<int> targetVector(sourceVector.size());
    printVector(sourceVector);

    newEnd = unique_copy(sourceVector.begin(), sourceVector.end(), targetVector.begin());               // Predicate can be used also as the last parameter
    printVector(targetVector);                                                                          // Print all the target vector
    for_each(targetVector.begin(), newEnd, [](int &curItem){cout << curItem << " ";});                  // Print till the new end

    targetVector.erase(newEnd, targetVector.end());                                                     // Cut off unwanted part
    printVector(targetVector);                                                                          // Print all the target vector

}

void printVector(auto &vectToOut){
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem << ", ";
    cout << endl;
}