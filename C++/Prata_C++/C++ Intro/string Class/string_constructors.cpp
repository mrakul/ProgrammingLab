// str1.cpp -- introducing the string class
#include <iostream>
#include <string>

// using string constructors
int main()
{
    using namespace std;
    string one("Lottery Winner!"); // Constructor #1
    cout << one << endl;           // overloaded <<

    //String2
    string two(20, '$');           // Constructor #2
    cout << two << endl;

    //String3
    string three(one);              // Constructor #3
    cout << three << endl;
    one += " Oops!";                // overloaded +=
    cout << one << endl;
    two = "Sorry! That was ";
    three[0] = 'P';

    //String4
    string four;                    // Constructor #4
    four = two + three;             // overloaded +, =
    cout << four << endl;
    char alls[] = "All's well that ends well";

    //String5
    string five(alls, 20);          // Constructor #5 (take first 20 symbols or more)
    cout << five << "!\n";

    //String6
    string six(alls + 6, alls + 10); // Constructor #6 (uses Iterators conception)
    cout << six << ", ";

    //String7
    string seven(&five[6], &five[10]); // Constructor #6 again
    cout << seven << "...\n";

    //String8
    string eight(four, 7, 16);          // Constructor #7: start position and number of characters to copy
    cout << eight << " in motion!" << endl;

    string piano_man = {'L', 'i', 's','z','t'}; //Constructor #9 from the Stephen Prata's C++ Primer Plus book - use Initializer list

    //Actions on the strings
    if (one > two)
        cout << "One is more than two" << endl;
    else
        cout << "Two is more than one" << endl;

    int where = one.find("Win");
    where = one.find_first_of("Wane");

    cout << "C-style string of 'one' string: " << one.c_str() << endl;
    cout << "Size of 'one' string is: " << one.size() << endl;      //Initial size is 15 + 6 symbols, so the capacity is 30 initially, and not changed
    cout << "Capacity of 'one' string is: " << one.capacity() << endl;
    one = one + one + one;
    cout << "Size of 3-x 'one' string is: " << one.size() << endl;
    cout << "Capacity of 3-x 'one' string is: " << one.capacity() << endl;

    return 0;
}