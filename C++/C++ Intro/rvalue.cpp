// rvref.cpp -- simple uses of rvalue references
#include <iostream>
inline double someFunc(double localVal) { return 5.0 * (localVal - 32.0) / 9.0; };

int main(int argc, const char *argv[])
{
    using namespace std;

    double value = 21.5;
    double&& rd1 = 7.07;        //rvalue
    double&& rd2 = 1.8 * value + 32.0;
    double&& rd3 = someFunc(rd2);

    cout << " tc value and address: " << value << ", " << &value << endl;
    cout << "rd1 value and address: " << rd1 << ", " << &rd1 << endl;
    cout << "rd2 value and address: " << rd2 << ", " << &rd2 << endl;
    cout << "rd3 value and address: " << rd3 << ", " << &rd3 << endl;

    cin.get();
    return 0;
}