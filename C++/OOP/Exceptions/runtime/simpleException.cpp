// simpleException.cpp
#include <iostream>
#include <cstdlib>
#include <stdexcept>
double hmean(double a, double b);

int main()
{
    double x, y, z;
    std::cout << "Enter two numbers: ";
    while (std::cin >> x >> y)
    {
        try
        { // start of try block
            z = hmean(x, y);
        }                     // end of try block
        catch (std::runtime_error &error)                   //(!) actually, always made a copy of error, but for catch derived class exceptions this construction is used
            //(const char *s) // start of exception handler
        {
            std::cout << error.what() << std::endl;
            std::cout << "Enter a new pair of numbers: ";
            continue;       //If not have continue here, then the statements after the catch{} will be processed
        }
        std::cout << "Harmonic mean of " << x << " and " << y
                  << " is " << z << std::endl;
        std::cout << "Enter next set of numbers <q to quit>: ";
    }
    std::cout << "Bye!\n";
    return 0;
}
double hmean(double a, double b)
{
    if (a == -b)
        throw std::runtime_error("bad hmean() arguments: a = -b not allowed");
    // {
    //     std::cout << "untenable arguments to hmean()\n";
    //     std::abort();
    // }
    return 2.0 * a * b / (a + b);
}