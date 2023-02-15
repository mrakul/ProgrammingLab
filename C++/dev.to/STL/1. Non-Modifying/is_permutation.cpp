#include <iostream>
#include <set>
#include <algorithm>

/*** is_permutation() examples ***/

using namespace std;

int main(int argc, char const *argv[])
{
    // 0. Define containers
    vector<int> myVector1{1, 2, 3, 4, 5};
    vector<int> myVector2{myVector1};

    // 1. is_permutation() example
    random_shuffle(myVector2.begin(), myVector2.end());
    auto isPermutation = is_permutation(myVector1.begin(), myVector1.end(), myVector2.begin());
    isPermutation ? (cout << "The two vectors are permutations of each other\n") : (cout << "The two vectors are NOT permutations of each other\n");

    // 2. Remove one element from the vector1
    myVector1.pop_back();
    isPermutation = is_permutation(myVector1.begin(), myVector1.end(), myVector2.begin());
    isPermutation ? (cout << "The two vectors are permutations of each other\n") : (cout << "The two vectors are NOT permutations of each other\n");

    return 0;
}
