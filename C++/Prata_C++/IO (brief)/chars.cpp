#include <iostream>
using namespace std;
int main()
{

    // char ch;
    // while ((ch = cin.get()) && !cin.eof())     //read char by char (or ch = cin.get()) != EOF))  // OR cin.get(ch)
    // {
    //     cout << ch;
    // }
    // return 0;

    int line = 0;
    char ch;
    while (cin.get(ch) && ch != 'Q')
    {
        if (ch == '\n')
            line++;
    }

    cout << "Number of lines: " << line;

    return 0;
}