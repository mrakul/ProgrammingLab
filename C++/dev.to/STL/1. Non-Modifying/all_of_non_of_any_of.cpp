#include <iostream>
#include <algorithm>
#include <set>

/*** all_of(), none_of(), any_of() non-modifying sequence STL algorithms examples ***/

class NumIsEven
{
public:
    bool operator()(int itemToCheck)
    {
        return !(itemToCheck & 1);
    }
};

using namespace std;

int main(int argc, char const *argv[])
{
    set<int> mySet{2, 4, 6, 8};
    auto numIsOdd = [](const int &itemToCheck) {return (itemToCheck & 1);};
    auto numIsEven = [](const int &itemToCheck){return !(itemToCheck & 1);};

    // 1. Check if all numbers are even
    bool allNnumbersAreEven = all_of(mySet.begin(), mySet.end(), numIsEven);

    if (allNnumbersAreEven)
        cout << "Set contains only even numbers. \n";
    else
        cout << "Set contains odd numbers. \n";

    // Insert 5 to the set and check once again using Class definition (just for example and remembering)
    mySet.insert(5);
    allNnumbersAreEven = all_of(mySet.begin(), mySet.end(), NumIsEven{});
    if (allNnumbersAreEven)
        cout << "Set contains only even numbers. \n";
    else
        cout << "Set contains odd numbers. \n";

    // 2. Check if no numbers are odd
    bool noOddNumbers = none_of(mySet.begin(), mySet.end(), numIsOdd);                  // False: there is 5 in the set
    mySet.erase(5);                                                                     // Remove 5 from the set
    noOddNumbers = none_of(mySet.begin(), mySet.end(), numIsOdd);                       // True: no odd numbers are in the set

    // 3. any_of() example
    bool isAnyOddNum = any_of(mySet.begin(), mySet.end(), numIsOdd);                    // True: there is no any odd number
    mySet.insert(5);                                                                    // Add 5 back
    isAnyOddNum = any_of(mySet.begin(), mySet.end(), numIsOdd);                         // True: there is at least one odd number

    return 0;
}
