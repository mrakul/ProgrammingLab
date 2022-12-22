#include <memory>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

const int SIZE = 10;

void outString(string &outStr);

int main(int argc, char const *argv[])
{
    // 1. Without using allocator class
    string *const stringsArr = new string[SIZE];        // Obtains memory for SIZE strings AND construct SIZE empty strings at the same time
    string inputString;
    string *curStrPtr = stringsArr;                     // curStrPtr points to the first string
    // while (cin >> inputString && curStrPtr != stringsArr + SIZE)
    //     *curStrPtr++ = inputString;                     // Assign input value to *curStrPtr

    size_t inputSize = curStrPtr - stringsArr;      // Number of elements have been input

    for_each(stringsArr, stringsArr + inputSize, outString);    //Out only the number of input

    cout << "Number of input words: " << inputSize << endl;

    // We may have created strings that are never used.
    // Moreover, for those objects we do use, we immediately assign new values over the previously initialized strings.
    // The elements that are used are written twice: first when the elements are default initialized, and subsequently
    // when we assign to them.

    // Release the array's memory
    delete[] stringsArr;                                // stringsArr points to an array; must remember to use delete[]

    // 2. With use of allocator class: create an object which will allocate memory for the strings
    allocator<string> strAllocator;
    using traits_t = std::allocator_traits<decltype(strAllocator)>;
    // traits_t::rebind_alloc<std::string> strAlloc_ = strAllocator;        //This is done in https://en.cppreference.com/w/cpp/memory/allocator, not sure if this is obligatory

    string *const stringsArr2 = traits_t::allocate(strAllocator, SIZE);     //Allocate unconstructed memory for SIZE number of strings
    auto curStrPtr2 = stringsArr2;                                          // curStrPtr points to the obtained memory and will point to one past the last constructed element

    //Check the state
    cout << cin.eofbit << " " << cin.badbit << " " << cin.failbit << endl;
    cout << cin.eof() << " " << cin.bad() << " " << cin.fail();     //fail bit is set (for some reason?)

    cin.clear();

    //Call constructors separately within the obtained memory: curStrPtr2 will point to the last past the end element
    stringstream strStream{"Test input sentence"};
    while (strStream >> inputString && curStrPtr2 != stringsArr2 + SIZE)
        traits_t::construct(strAllocator, curStrPtr2++, inputString);       // Construct the string on the (*curStrPtr) place with content of inputString
    //Another constructors calls examples
    // traits_t::construct(strAllocator, curStrPtr2++, 10, 'c');            // *curStrPtr is "cccccccccc"
    // traits_t::construct(strAllocator, curStrPtr2++, "Hi!");              // *curStrPtr is "Hi!"

    inputSize = curStrPtr2 - stringsArr2;                                   // Number of elements have been input
    for_each(stringsArr2, stringsArr2 + inputSize, outString);                //Out only the number of input

    //Call the destructors appropriately starting from the end
    while (curStrPtr2 != stringsArr2)
        traits_t::destroy(strAllocator, --curStrPtr2);                      //curStrPtr2 will point to the memory before the stringsArr2

    //Release the memory
    traits_t::deallocate(strAllocator, stringsArr2, SIZE);                  //Release the memory for all the strings input

    return 0;
}

void outString(string &outStr)
{
    cout << outStr << " ";
}