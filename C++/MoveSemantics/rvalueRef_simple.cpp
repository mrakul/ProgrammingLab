// rvref.cpp -- simple uses of rvalue references
#include <iostream>
inline double someFunc(double localVal) { return 5.0 * (localVal - 32.0) / 9.0; };

using namespace std;

double up(double x) { return 2.0 * x; }

void r1(const double& rx) { cout << rx << endl; }
void r2(double& rx) { cout << rx << endl; }
void r3(double&& rx) { cout << rx << endl; }

int main(int argc, const char* argv[])
{

    double value = 21.5;
    double&& rd1 = 7.07;        //rvalue
    double&& rd2 = 1.8 * value + 32.0;
    double&& rd3 = someFunc(rd2);

    cout << " tc value and address: " << value << ", " << &value << endl;
    cout << "rd1 value and address: " << rd1 << ", " << &rd1 << endl;
    cout << "rd2 value and address: " << rd2 << ", " << &rd2 << endl;
    cout << "rd3 value and address: " << rd3 << ", " << &rd3 << endl;

    //(!!!) Check different cases for the lvalue and rvalue reference
    double w = 10.0;
    r1(w);              // is valid, and the argument rx refers to w.
    r1(w + 1);	        // is valid, and the argument rx refers to a temporary initialized to the value of w+1
    r1(up(w));          // is valid, and the argument rx refers to a temporary initialized to the return value of up(w).
    //In general, if an lvalue is passed to a const lvalue reference parameter, the parameter
    // is initialized to the lvalue. If an rvalue is passed to the function, a const lvalue
    // reference parameter refers to a temporary copy of the value.

    r2(w);              // is valid, and the argument rx refers to w.
    // r2(w + 1);	        // is an error because w + 1 is an rvalue.
    // r2(up(w));	        // is an error because the return value of up(w) is an rvalue.
    // In general, if an lvalue is passed to a non-const lvalue reference parameter, the
    // parameter is initialized to the lvalue. But a non-const lvalue reference parameter
    // can’t accept an rvalue function argument.


    //r3(w);		        // is an error because an rvalue reference cannot refer to an lvalue, such as w.
    r3(w+1);             // is valid, and rx refers to the temporary value of the expression w+1.
    r3(up(w));           // is valid, and rx refers to the temporary return value of up(w)

    cin.get();
    return 0;
}