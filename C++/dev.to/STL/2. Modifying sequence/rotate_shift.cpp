#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <algorithm>

/*** rotate(ForwIt first, ForwIt middle, ForwIt last) examples:
 * It actually moves everything to the left until middle becomes the first, that is [first, middle) are placed after the elements in [middle, last) keeping an elements order
 *
 * shift_left(), shift_right() are added with C++20 Standard
 *
**/

void printVector(auto &vectToOut);
using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Create a vector and a list of the same content
    vector<int> myVector{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> myVectorToCopy(myVector.size());
    printVector(myVector);

    // 1. rotate() example: the new position of prevously first element is returned
    auto firstItNewPlace = rotate(myVector.begin(), myVector.begin() + 3, myVector.end());         // The 3-rd element becomes first
    printVector(myVector);

    cout << "Print out [previousFirst; Last): " << endl;
    auto printNum = [](int &numToPrint){cout << numToPrint << ' ';};
    for_each(firstItNewPlace, myVector.end(), printNum);

    // 2. rotate_copy(): the same, but copy the result to another vector
    rotate_copy(myVector.begin(), myVector.begin() + 1, myVector.end(), myVectorToCopy.begin());  // Rotate for one element
    printVector(myVectorToCopy);

    // 3. shift_left(), shift_right() examples: the difference is that shifted element which becomes out of the range, are not added to another side
    shift_left(myVectorToCopy.begin(), myVectorToCopy.end(), 1);            // If move-semantics is implemented, it is used
    printVector(myVectorToCopy);                                            // Last element is doubled, first is missed
    shift_right(myVectorToCopy.begin(), myVectorToCopy.end(), 1);
    printVector(myVectorToCopy);                                            // First element is doubled

    // Check with internal interval and print out all the vector
    shift_left(myVectorToCopy.begin() + 2, myVectorToCopy.begin() + 4, 1);    // Move [2; 4) left
    printVector(myVectorToCopy);                                              // The [1] element is not changed, the 2-nd just disappeard with 3-rd occupuying its place

    return 0;
}

void printVector(auto &vectToOut)
{
    cout << "Vector's size and capacity: " << vectToOut.size() << " " << vectToOut.capacity() << endl;
    for (auto &curItem : vectToOut)
        cout << curItem << ", ";
    cout << endl;
}