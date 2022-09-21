#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <set>
#include <algorithm>
#include <iterator> // for ostream_iterator
#include <cassert>

using namespace std;

template <typename ContType>
void printVector(const ContType &vectRef)
{
    cout << "Words: {";
    copy(begin(vectRef), end(vectRef), ostream_iterator<typename ContType::value_type>(cout, " "));
    cout << "}\n";
}

template <typename ContType, typename Type>
void insertSorted(ContType &vectRef, const Type &word)
{
    auto it = lower_bound(begin(vectRef), end(vectRef), word);             // This returns the first position where word may be placed (not less than the word value)
    vectRef.insert(it, word);
}

int main(int argc, char const *argv[])
{
    vector<string> myVector{"some", "random", "words", "without", "order", "aaa", "yyy"};
    printVector(myVector);

    // Sort the vector
    assert(false == is_sorted(begin(myVector), end(myVector)));
    sort(myVector.begin(), myVector.end());
    assert( true == is_sorted(begin(myVector), end(myVector)));
    printVector(myVector);

    // Insert the words remaining the vector sorted
    insertSorted(myVector, "apple");
    insertSorted(myVector, "village");
    printVector(myVector);

    return 0;
}