#include <memory>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

const int CNT_SIZE = 10;

int main(int argc, char const *argv[])
{
    allocator<int> allocatorInt;                // Allocator for ints
    vector<int> vectInts(CNT_SIZE);             // Create a source vector of ints

    // Fill the vector with values
    int i = 0;                                  // Counter
    for (auto it = vectInts.begin(); it != vectInts.end(); it++)
        *it = i++;

    // Allocate the new memory area, unconstructed
    int *memToUsePtr = allocatorInt.allocate(vectInts.size() * 2);        // Allocate double of memory elements as vector holds, or 'auto memToUsePtr'

    // Construct elements at the first half of the memory as the copy of vectInts and returns one past the constructed objects
    auto curPosPtr = uninitialized_copy(vectInts.begin(), vectInts.end(), memToUsePtr);     // Construct elements starting at memToUsePtr as copies of elements in vectInts

    // Construct the remaining elements as 42. Note: assign returned value to curPosPtr and pass it as forward iterator, works well
    curPosPtr = uninitialized_fill_n(curPosPtr, vectInts.size(), 42);

    // Print out the current value from the end and destroy the element
    cout << "New mem with constructed elements: " << endl;
    while (curPosPtr != memToUsePtr)
    {
        cout << *(curPosPtr - 1) << ' ';
        allocator_traits<allocator<int>>::destroy(allocatorInt, --curPosPtr);
    }
    cout << endl;

    //Release the memory
    allocatorInt.deallocate(memToUsePtr, CNT_SIZE);

    /*** 2. Try make_move_iterator() adapter ***/
        // Allocate twice an initial vector required
    auto newVectMem = allocatorInt.allocate(CNT_SIZE * 2);

    // Move the elements from the initial vector: in this case it will be just copied, since primitive ints are used
    curPosPtr = uninitialized_copy(make_move_iterator(vectInts.begin()),
                                    make_move_iterator(vectInts.end()),
                                    newVectMem);
    // Fill the second part with reverted iterators
    curPosPtr = uninitialized_copy(make_move_iterator(vectInts.rbegin()),
                                    make_move_iterator(vectInts.rend()),
                                    curPosPtr);

    cout << "New mem with constructed elements: " << endl;
    while (curPosPtr != newVectMem)
    {
        cout << *(curPosPtr - 1) << ' ';
        allocator_traits<allocator<int>>::destroy(allocatorInt, --curPosPtr);
    }
    cout << endl;

    allocatorInt.deallocate(newVectMem, CNT_SIZE * 2);

    /*** 3. Copy from the list to uninitialized memory ***/

    // Create a list for experiment: list content may be copied/moved (?) to the uninitialized memory using iterators
    list<int> listInts(CNT_SIZE);
    cout << "List content: " << endl;
    i = 0;
    for (auto &num : listInts)
    {
        num = 100 - i;
        cout << num << " ";
        i++;
    }
    cout << endl;

    // Allocate memory required to copy
    auto newVectMem2 = allocatorInt.allocate(CNT_SIZE * 2);

    // Move the elements from the initial list: in this case it will be just copied, since primitive ints are used
    curPosPtr = uninitialized_copy(make_move_iterator(listInts.begin()),
                                   make_move_iterator(listInts.end()),
                                   newVectMem2);

    // Fill the second part with reverted iterators
    curPosPtr = uninitialized_copy(make_move_iterator(listInts.rbegin()),
                                   make_move_iterator(listInts.rend()),
                                   curPosPtr);

    cout << "New mem with constructed elements: " << endl;
    while (curPosPtr != newVectMem2)
    {
        cout << *(curPosPtr - 1) << ' ';
        allocator_traits<allocator<int>>::destroy(allocatorInt, --curPosPtr);
    }
    cout << endl;

    allocatorInt.deallocate(newVectMem2, CNT_SIZE * 2);

    return 0;
}