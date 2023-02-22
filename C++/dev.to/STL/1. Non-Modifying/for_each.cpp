#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Note: the link below explains why for_each() is in the non-modifying sequence operations category, but can modify items actually
/*       https://stackoverflow.com/questions/662845/why-is-stdfor-each-a-non-modifying-sequence-operation
*/

int main(int argc, char const *argv[])
{
    vector<int> myVector{1, 2, 3, 4, 5};

    // 1. Print the vector, increment every number and print it once again
    auto printNum = [](int &numToPrint){cout << numToPrint << ' ';};
    auto incrementNum = [](int &numToChange){++numToChange;};

    for_each(myVector.begin(), myVector.end(), printNum);
    for_each(myVector.begin(), myVector.end(), incrementNum);           // Note: we cannot modify the number of elements, cannot add or delete elements, but can modify the value by using reference
    for_each(myVector.begin(), myVector.end(), printNum);

    // 2. Just as an exercise: make the same using range-based loop
    for (auto &curNum : myVector){                                     // We can cover only the entire containter
        incrementNum(curNum);
        printNum(curNum);
    }
    // Or manually iterating using iterators
    for (auto it = myVector.begin(); it != myVector.end(); ++it){
        incrementNum(*it);
        printNum(*it);
    }

    return 0;
}
