#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int x[10];
    int *p = x;
    cout << "Number of elements: " <<sizeof(x) / sizeof(*x) << endl;
    cout << sizeof(p) / sizeof(*p) << endl;
    cout << "Pointer size: " << sizeof(p) << " Int size: " << sizeof(*p) << endl;
    return 0;
}
