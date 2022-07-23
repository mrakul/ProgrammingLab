// setf2.cpp -- using setf() with 2 arguments to control formatting
#include <iostream>
#include <cmath>
using namespace std;

void printTestNumbers(void);

int main(int argc, char const *argv[])
{
    // use left justification, show the plus sign, show trailing zeros, with a precision of 3
    cout.setf(ios_base::left, ios_base::adjustfield);
    cout.setf(ios_base::showpos);
    cout.setf(ios_base::showpoint);
    cout.precision(3);

    // use e-notation and save old format setting
    ios_base::fmtflags old = cout.setf(ios_base::scientific, ios_base::floatfield);

    // Print out the numbers
    cout << "Left Justification:" << endl;
    printTestNumbers();

    // Change to internal justification and print out
    cout.setf(ios_base::internal, ios_base::adjustfield);
    // Restore default floating-point display style (not the scientist, so the total number of digits precision used)
    cout.setf(old, ios_base::floatfield);
    cout << "Internal Justification:" << endl;
    printTestNumbers();

    // Use right justification, fixed notation and print out
    cout.setf(ios_base::right, ios_base::adjustfield);
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout << "Right Justification:" << endl;
    printTestNumbers();

    return 0;
}

void printTestNumbers(void)
{
    for (long number = 1; number <= 41; number += 10)
    {
        cout.width(4);
        cout << number << "|";
        cout.width(12);
        cout << sqrt(double(number)) << "|" << endl;
    }
}