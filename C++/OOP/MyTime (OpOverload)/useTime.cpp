#include <iostream>
#include "MyTime.h"

int main()
{
    using std::cout;
    using std::endl;
    //Create two objects
    MyTime initTime;
    MyTime addedTime(3, 50);

    //Set initial value
    initTime.Reset(1, 30);
    initTime.Show();

    //Add hours and minutes
    initTime.AddHr(1);
    initTime.AddMin(10);
    initTime.Show();

    //Add another object by overloaded operator+
    initTime = initTime + addedTime;
    initTime.Show();

    //Multiplication test: 1. By overloaded * operator, 2. By Friend function
    initTime = initTime * 2.0;
    initTime = 2.0 * initTime; //invalid by operator overloading (friend function is called)

    cout << initTime;

    //Conversion check
    MyTime convertTime = MyTime(24.5);
    return 0;
}