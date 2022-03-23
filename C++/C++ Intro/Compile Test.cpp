#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

struct pims
{
    int a{0};
    string Str1{" "};
    // int b(4); - prohitibetd initializizing form
};

int main(int argc, char const *argv[])
{
    // int c(5);
    string a{"Test lalala"};
    string b("Another initializator mode");

    auto stringsSum = a + b;
    decltype(stringsSum) stringTest = "Decltype + init test: " + stringsSum;

    cout << a << endl
         << "a length is:" << a.length() << endl
         << "size:" << a.size() << endl;
    cout << b << endl
         << "b length is:" << b.length() << endl
         << "size:" << b.size() << endl;
    a = a + ' ' + b;

    cout << a << endl
         << "a new length is:" << a.length() << endl
         << "size:" << a.size() << endl;

    cout << "stringTest: " << stringTest << endl;

    string line;
    // char lineChar[20];

    // reads the line until \n, but discarding \n
    while (getline(cin, line) && !line.empty())
    {
        cout << line.size() << endl;

        cout << line << endl;
        decltype(line.size()) punct_cnt = 0;
        // count the number of punctuation characters in s
        // for (c = line[0], i = 0; i < line.size(); i++)     // for every char in s
        for (auto &c : line) // !! c is a reference, since we want to change the initial string
            if (ispunct(c))  // if the character is punctuation
                ++punct_cnt; // increment the punctuation counter
            else
                c = toupper(c); //Make upper all the symbols

        cout << punct_cnt
             << " punctuation characters in " << line << endl;
    }

    // cin >> c;

    cout << "Current date: " << __DATE__ << endl;
    cout << "Current file: " << __FILE__ << endl;
    cout << "Line in the file: " << __LINE__ << endl;
    cout << "Standard: " << __STDC__;
    cout << "Standard hosted: " << __STDC_HOSTED__ << endl;
    cout << "Standard version: " << __cplusplus << endl;
    cout << "Current date: " << __TIME__ << endl;

    // {
    //     int i, *const cp;
    //     int *p1, *const p2;
    //     const int ic = 5, &r = ic;
    //     const int *const p3;
    //     const int *p;
    // int null = 0, *p = &null;
    // }

    /*
        do {
            character = getchar(); // считать введённый со стандартного потока  ввода  символ
            putchar (character);   // вывести этот символ
        } while (character != '.'); // пока введенный символне точка
    */

    return 0;
}
