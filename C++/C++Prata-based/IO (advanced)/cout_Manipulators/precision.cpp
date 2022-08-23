// precise.cpp -- setting the precision
#include <iostream>
int main(int argc, char const *argv[])
{
    using std::cout;
    using std::ios_base;
    float price1 = 20.40;
    float price2 = 1.9 + 8.0 / 9.0;

    cout.setf(ios_base::showpoint);     //to print out trailing zeroes
    cout << "\"Furry Friends\" is $" << price1 << "!\n";
    cout << "\"Fiery Fiends\" is $" << price2 << "!\n";

    cout.precision(2);                  //in default mode, sets total number of digits
    cout << "\"Furry Friends\" is $" << price1 << "!\n";
    cout << "\"Fiery Fiends\" is $" << price2 << "!\n";
    return 0;
}