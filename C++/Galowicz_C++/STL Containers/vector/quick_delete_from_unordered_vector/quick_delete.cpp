#include <iostream>
#include <vector>
#include <algorithm>


// The idea is to move the last element to the required position and then drop one last element
// We can do it because the vector is unsorted so we may not save the order of the items
template <typename Type>
void quick_remove_at(std::vector<Type> &vectToRemove, std::size_t index)
{
    if (index < vectToRemove.size()){
        vectToRemove.at(index) = std::move(vectToRemove.back());
        vectToRemove.pop_back();
    }
}

template <typename Type>
void quick_remove_at(std::vector<Type> &intsVect, typename std::vector<Type>::iterator it)
{
    if (it != std::end(intsVect)){                  // Means that the value was found by find()
        *it = std::move(intsVect.back());
        intsVect.pop_back();
    }
}
// The ambiguity the typename keyword resolves for std::vector<Type>::iterator it is that T::iterator
// can refer either to a nested type (case 1) or a static class attribute (case 2).
// The compiler interprets a construction like this as case 2 by default. The typename keyword enforces case 1.


int main(int argc, char const *argv[])
{
    std::vector<int> intsVect{123, 456, 789, 100, 200};
    auto num1 = intsVect.size();
    auto num2 = intsVect.capacity();        // 5/5

    // 1. Try quick_remove_at() which uses an index of an element to remove
    quick_remove_at(intsVect, 2);
    num1 = intsVect.size();
    num2 = intsVect.capacity();             // 4/5
    for (int i : intsVect){ std::cout << i << ", "; }
    std::cout << '\n';

    // 2. Try quick_remove_at() which uses an iterator to remove
    quick_remove_at(intsVect, std::find(std::begin(intsVect), std::end(intsVect), 123));
    num1 = intsVect.size();
    num2 = intsVect.capacity();            // 3/5

    for (int i : intsVect){ std::cout << i << ", "; }
    std::cout << '\n';

    // 3. Try empty vector to check boundaries
    std::vector<int> vect2;
    quick_remove_at(vect2, 0);

    return 0;
}