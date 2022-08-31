// strquote.cpp -- different designs
#include <iostream>
#include <string>
using namespace std;

string version1(const string &s1, const string &s2);
// Note: since s2 is a const reference, and the actual argument is (const char *) type,
// then a temporary variable of the string type is created to manupulate data
const string &version2(string &s1, const string &s2); // has side effect of changing s1

const string &version3(string &s1, const string &s2); // bad design

//Mainline
int main(int argc, char const *argv[])
{
    string input, copy, result;

    //Input a new string
    cout << "Enter a string: ";
    getline(cin, input);
    copy = input;
    cout << "Your string as entered: " << input << endl;

    // 1. Return string type rvalue by version1 (?)
    result = version1(input, "***");
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;

    // 2. Return reference to the first parameter (input)
    result = version2(input, "###");
    //version2(input, "###") = "Cringe";        //(!) if specify string &version2(...), then it is allowed since returning non-const reference to s1

    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;
    cout << "Resetting original string.\n";
    input = copy;

    //3. Bad behavior: version3 returns a reference to a local variable temp which doesn't exist after function terminated
    // result = version3(input, "@@@");
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;
    return 0;
}

string version1(const string &s1, const string &s2)
{
    string temp;
    temp = s2 + s1 + s2;
    return temp;
}

const string &version2(string &s1, const string &s2) // has side effect
{
    s1 = s2 + s1 + s2;
    // safe to return reference passed to function
    return s1;
}

// const string &version3(string &s1, const string &s2) // bad design
// {
//     string temp;
//     temp = s2 + s1 + s2;
//     // unsafe to return reference to local variable
//     return temp;
// }