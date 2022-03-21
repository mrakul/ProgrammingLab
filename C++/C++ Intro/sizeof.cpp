#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int x[10];
    int *p = x;
    cout << "Array size: " << sizeof(x) << endl;
    cout << "Size of one element: " << sizeof(*x) << endl;
    cout << "Number of elements: " << sizeof(x) / sizeof(*x) << endl;

    cout << "Size of pointer :" << sizeof(p) << endl;
    cout << "Pointer size: " << sizeof(p) << " Int size: " << sizeof(*p) << endl;
    //How much does the size of the pointer exceed the size of the number
    cout << "Ptr Size / Int size ratio :" << sizeof(p) / sizeof(*p) << endl;
    return 0;
}
