#include <iostream>

int main()
{
    using namespace std;

    const int ArSize = 20;
    char name[ArSize];
    char dessert[ArSize];
    char testGetline[ArSize];


    cout << "Enter your name: " << endl;
    cin.get(name, ArSize).get(); // read string, newline

    cout << "Enter your favorite dessert: " << endl;
    cin.get(dessert, ArSize).get();

    cout << "I have some delicious " << dessert;
    cout << " for you, " << name << '.' << endl;

    cin >> testGetline; //reads until the whitespace encountered
    cout << testGetline << endl;
    cin.getline(testGetline, ArSize);
    cout << "The rest of the string is: " << testGetline << endl;

    return 0;
}