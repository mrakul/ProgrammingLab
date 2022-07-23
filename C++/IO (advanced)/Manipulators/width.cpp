// width.cpp -- using the width method
#include <iostream>
int main(int argc, char const *argv[])
{
    using std::cout;
    using std::endl;

    int w = cout.width(30);     //returns the previous default value (0) and set the new (30)
    cout << "Default field width = " << w << endl;

    cout.width(5);
    cout << "N";
    cout.width(8);
    cout << "N * N" << endl;

    for (long i = 1; i <= 100; i *= 10)
    {
        cout.width(5);
        cout << i;
        cout.width(8);
        cout << i * i << endl;
    }

    return 0;
}