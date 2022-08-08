// check_it.cpp -- checking for valid input
#include <iostream>

int main(int argc, char const* argv[])
{
    using namespace std;
    cout << "Enter numbers: ";
    int sum = 0;
    int input;

    while (cin >> input)
    {
        sum += input;
    }

    cout << "Last value entered = " << input << endl;
    cout << "Sum = " << sum << endl;
    if (cin.fail() && !cin.eof()) // failed because of mismatched input
    {
        cin.clear(); // reset stream state
        while (!isspace(cin.get()))
            continue; // get rid of bad input
        // Or this way:
        // while (cin.get() != '\n')
        //    continue; // get rid rest of line
    }
    else // else bail out
    {
        cout << "I cannot go on!\n";
        exit(1);
    }

    cin >> input;                   // If not reset stream state, will not work

    cout << "Last value entered = " << input << endl;
    cout << "Sum = " << sum << endl;

    return 0;
}