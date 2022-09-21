#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printVector(auto &vectToOut);

int main(int argc, char const *argv[])
{
    /* Erase-remove idioms explanation: remove() function allows to remove unmatching elements for one pass through the vector.
       Unmatched elements moved forward, but the tail conatins old values */

    // (!): since C++20, there is std::erase() algorithm to correctly remove required items
    vector<int> intsVect{1, 2, 3, 2, 5, 2, 6, 2, 4, 8};
    printVector(intsVect);

    // Remove unwanted elements: unmatched elements moved forward, but the tail contains old values, capacity and size remains the same.
    auto vectNewEnd = remove(intsVect.begin(), intsVect.end(), 2);
    [[maybe_unused]] auto difference = intsVect.end() - vectNewEnd;                      // 4 of '2' were removed
    printVector(intsVect);

    // Erase the vector's tail: size becomes 6, but capacity remains 10
    intsVect.erase(vectNewEnd, end(intsVect));
    printVector(intsVect);

    // Now removes all odd numbers
    auto isOdd = [](int i) { return i % 2 != 0; };   // Or i & 1;
    intsVect.erase(remove_if(begin(intsVect), end(intsVect), isOdd), end(intsVect));
    printVector(intsVect);

    // Changes the actual allocated size (reallocating the memory)
    intsVect.shrink_to_fit();
    // Note: resize() only moves the end iterator if decreasing the size. Otherwise, it allocates more memory
    // intsVect.resize(intsVect.size() + 7);
    printVector(intsVect);

    return 0;
}

// Interesting that specifying auto for formal parameter, this becomes a template and works well (since C++20):
void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto i : vectToOut){
        cout << i << ", ";
    }
    cout << endl;
}