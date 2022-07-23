#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace std;
    cout << "Enter an integer: ";
    int n;
    cin >> n;
    cout << "n n*n" << endl;
    cout << n << " " << n * n << " (decimal)" << endl;

    // set to hex mode
    cout << hex;
    cout << n << " ";
    cout << n * n << " (hexadecimal)" << endl;

    // set to octal mode
    cout << oct << n << " " << n * n << " (octal)" << endl;

    // alternative way to call a manipulator
    dec(cout);
    cout << n << " " << n * n << " (decimal)" << endl;
    return 0;

}
