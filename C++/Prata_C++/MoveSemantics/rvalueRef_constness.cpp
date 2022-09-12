// rvref.cpp -- simple uses of rvalue references
#include <iostream>
inline double someFunc(double localVal) { return 5.0 * (localVal - 32.0) / 9.0; };

using namespace std;

double up(double x) { return 2.0 * x; }

void constLvalRef(const double& rx) { cout << rx << endl; }
void nconstLvalRef(double& rx) { cout << rx << endl; }
void nconstRvalRef(double&& rx) { cout << rx << endl; }

int main(int argc, const char* argv[])
{
    //(!!!) Check different cases for the lvalue and rvalue reference
    double w = 10.0;
    constLvalRef(w);              // is valid, and the argument rx refers to w.
    constLvalRef(w + 1);	      // is valid, and the argument rx refers to a temporary initialized to the value of w + 1
    constLvalRef(up(w));          // is valid, and the argument rx refers to a temporary initialized to the return value of up(w).
    //In general, if an lvalue is passed to a const lvalue reference parameter, the parameter
    // is initialized to the lvalue. If an rvalue is passed to the function, a const lvalue
    // reference parameter refers to a temporary copy of the value.

    nconstLvalRef(w);                   // is valid, and the argument rx refers to w.
    // nconstLvalRef(w + 1);	        // is an error because w + 1 is an rvalue.
    // nconstLvalRef(up(w));	        // is an error because the return value of up(w) is an rvalue.
    // In general, if an lvalue is passed to a non-const lvalue reference parameter, the
    // parameter is initialized to the lvalue. But a non-const lvalue reference parameter
    // can’t accept an rvalue function argument.

    // nconstRvalRef(w);               // is an error because an rvalue reference cannot refer to an lvalue, such as w.
    nconstRvalRef(w+1);             // is valid, and rx refers to the temporary value of the expression w+1.
    nconstRvalRef(up(w));           // is valid, and rx refers to the temporary return value of up(w)

    cin.get();

    /* Example from the book
    double value = 21.5;
    double&& rd1 = 7.07;        //rvalue
    double&& rd2 = 1.8 * value + 32.0;
    double&& rd3 = someFunc(rd2);

    cout << " tc value and address: " << value << ", " << &value << endl;
    cout << "rd1 value and address: " << rd1 << ", " << &rd1 << endl;
    cout << "rd2 value and address: " << rd2 << ", " << &rd2 << endl;
    cout << "rd3 value and address: " << rd3 << ", " << &rd3 << endl;
    */

    return 0;
}