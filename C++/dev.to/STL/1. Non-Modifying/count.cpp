#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

/*** count(), count_of examples ***/

using namespace std;

int main(int argc, char const *argv[])
{
    set<int> mySet{1, 2, 3, 4, 5, 7, 8, 9};
    set<int> subSet{5, 7, 8};

    // 1. Count number of 3 in the set
    auto num = count(mySet.begin(), mySet.end(), 3);
    cout << "Count 3 in the set: " << num << endl;

    // 2. Count number of odd numbers in the set
    num = count_if(mySet.begin(), mySet.end(), [](const int &curItem){return (curItem & 1);});
    cout << "Count odd numbers: " << num << endl;

    return 0;
}
