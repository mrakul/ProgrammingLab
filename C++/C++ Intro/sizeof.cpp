#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int x[10];
    int *p = x;
    cout << "Array size: " << sizeof(x) << endl;
    cout << "Size of one element (first): " << sizeof(*x) << endl;
    cout << "Number of elements: " << sizeof(x) / sizeof(*x) << endl;

    cout << "Size of pointer: " << sizeof(p) << endl;
    cout << "Pointer size: " << sizeof(p) << " Int size: " << sizeof(*p) << endl;
    //How much does the size of the pointer exceed the size of the number
    //cout << "Ptr Size / Int size ratio :" << sizeof(p) / sizeof(*p) << endl;

    constexpr int arrSize = 20;
    int *array = new int[arrSize]{0, 1, 2};     //Initialize fields: !!! initializer list may be for dynamic memory allocation
    delete[] array;

    int array2[20]{0, 1, 2};      //Also initializer list
    int sizeArr = sizeof(array2) / sizeof(*array2);
    cout << sizeArr;
    for(int i; i < 20; i++)
        cout << array[i] << endl;

    return 0;
}
