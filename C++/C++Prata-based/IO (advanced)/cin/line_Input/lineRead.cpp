#include <string>
#include <iostream>

using std::string;
using std::cin, std::cout, std::endl;

int main(int argc, char const* argv[])
{
    string strInput;
    char charInput[10];

    while (cin.get(charInput, sizeof(charInput))){          //If reached EOF, need to reset the state
        cout << "Current input is: " << charInput << endl;
    }

    cin.get(charInput, sizeof(charInput));                  //not working without resetting the state(?)
    while (cin.good())                                      //not working without resetting the state(?)
    {
        cout << "Current input is: " << charInput << endl;
        cin.get(charInput, sizeof(charInput));
    }

    cout << cin.eofbit << " " << cin.badbit << " " << cin.failbit << endl;
    cout << cin.eof() << " " << cin.bad() << " " << cin.fail();     //fail bit is set (for some reason?)

    cin.clear();

    //Example from the book
    //Input the string with getline()
    const int Limit = 255;
    char input[Limit];
    cout << "Enter a string for getline() processing: " << endl;
    cin.getline(input, Limit, '#');     //Note: when # is encountered, EOF is not set

    // Check the stream state after reading
    cout << cin.eofbit << " " << cin.badbit << " " << cin.failbit << endl;
    cout << cin.eof() << " " << cin.bad() << " " << cin.fail();

    //Output the first
    cout << "Here is your input: ";
    cout << input << endl << "Done with phase 1" << endl;
    char ch;

    //Read the next character after the delimiter, since getline() got and discarded the delimiter
    cin.get(ch);
    cout << "The next input character is " << ch << endl;
    if (ch != '\n')
        cin.ignore(Limit, '\n'); // discard the part after the delimiter ("#" in this case) till the NewLine


    //Use cin.get() for input: it leaves the delimiter in the buffer
    cout << "Enter a string for get() processing:" << endl;
    cin.get(input, Limit, '#');
    cout << "Here is your input:\n";
    cout << input << endl << "Done with phase 2" << endl;
    cin.get(ch);
    cout << "The next input character is " << ch << endl;

    return 0;
}
