#include <string>
#include <iostream>

using namespace std;

void quoteInput (const int &numOut);
void quoteInput (const double &dblOut);
void quoteInput (const string &strOut);

int main(int argc, char const *argv[])
{
    int number;
    double dbl;
    string str;
    char ch;

    cout << "Input the integer please: ";
    cin >> number;
    quoteInput(number);
    cout << (ch = cin.get());      //remove NewLine from istream (\n) (Note: cout << cin.get() output 10 value - is the value of NewLine in ASCII)

    cout << "Input the double please: ";
    cin >> dbl;
    quoteInput(dbl);
    cout << (ch = cin.get());      //remove NewLine from istream (\n)

    // Reads the line until \n, but discarding \n (getline call)
    // ENTER stops asking
    cout << "Input the string please: ";
    while (getline(cin, str) && !str.empty())
    {
        cout << "String size is: " << str.size() << endl;
        quoteInput(str);
   }

   return 0;
}

void quoteInput (const int &numOut){
    cout << "Your number is: \"" << numOut << "\"";
}

void quoteInput (const double &dblOut){
        cout << "Your number is: \"" << to_string(dblOut) << "\"";
}

void quoteInput (const string &strOut){
    cout << "Your string is: \"" << strOut << "\"";
}

