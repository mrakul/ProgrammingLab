#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{   
    string a("Test lalala");
    char character;
    cout << a << "<- length is:" << a.length() << endl
         << "size:" << a.size();
    // cin >> c;

    do {
        character = getchar(); // считать введённый со стандартногопотока  ввода  символ
        putchar (character);   // вывести этот символ
    } while (character != '.'); // пока введенный символне точка
    
    return 0;
}
