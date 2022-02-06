#include <iostream>
#include <string>

using namespace std;

struct pims {
    int a{0};
    //int b(4); - prohitibetd initializizing form
};

int main(int argc, char const *argv[])
{
    int c(5);
    char name2[10] = "C++owboy";
    string a{"Test lalala"};
    string b("Test lalala");
    char character;
    cout << a << "<- length is:" << a.length() << endl
         << "size:" << a.size();
    // cin >> c;

    cout << "Current date: " << __DATE__ << endl;
    cout << "Current file: " << __FILE__ << endl;
    cout << "Line in the file: " << __LINE__ << endl;
    cout << "Standard: " << __STDC__;
    cout << "Standard hosted: " << __STDC_HOSTED__ << endl;
    cout << "Standard version: " << __cplusplus << endl;
    cout << "Current date: " << __TIME__ << endl;

    int i = 100, sum = 0;
    for (int i = 0; i != 10; ++i)
        sum += i;
    std::cout << i << " " << sum << std::endl;

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
