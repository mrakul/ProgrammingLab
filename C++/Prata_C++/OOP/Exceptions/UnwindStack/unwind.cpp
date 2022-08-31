//error5.cpp -- unwinding the stack
#include <iostream>
#include <cmath> // or math.h, unix users may need -lm flag
#include <string>
#include "myExceptions.h"

//class demo;     //forward declaration, definition in the bottom
class demo
{
private:
    std::string word;
public:
    demo(const std::string& str)
    {
        word = str;
        std::cout << "demo object " << word << " created" << std::endl;
    }
    ~demo()
    {
        std::cout << "demo object " << word << " destroyed" << std::endl;
    }
    void show() const
    {
        std::cout << "demo object " << word << " lives!" << std::endl;
    }
};

// function prototypes
double hmean(double a, double b);
double gmean(double a, double b);
double means(double a, double b);

int main(int argc, char const* argv[])
{
    using std::cout;
    using std::cin;
    using std::endl;
    double x, y, z;
    {
        demo d1{"found in block in main()"};
        cout << "Enter two numbers: ";
        while (cin >> x >> y)
        {
            try
            { // start of try block
                z = means(x, y);
                cout << "The mean mean of " << x << " and " << y
                    << " is " << z << endl;
                cout << "Enter next pair: ";
            } // end of try block
            catch (bad_hmean& bg)
            {
                bg.mesg();
                cout << "Try again." << std::endl;
                continue;
            }
            catch (bad_gmean& hg)
            {
                cout << hg.mesg();
                cout << "Values used: " << hg.v1 << ", "
                    << hg.v2 << endl;
                cout << "Sorry, you don't get to play any more." << std::endl;
                break;      //Quit from the loop if bad_gmean exception is caught
            } // end of catch block
            std::cout << "Without continue";        //This line of code is executed if remove 'continue' from the bad_hmean() catcher, so flow is just proceeding
        }
        d1.show();
    }
    cout << "Bye!" << std::endl;
    cin.get();
    cin.get();
    return 0;
}

double means(double a, double b)
{
    double am, hm, gm;
    demo d2("found in means()");
    am = (a + b) / 2.0; // arithmetic mean
    try
    {
        hm = hmean(a, b);
        gm = gmean(a, b);
    }
    catch (bad_hmean& bg) // start of catch block. (!!!) means() doesn't catch the bad_gmean exception
    {
        bg.mesg();
        std::cout << "Caught in means()" << std::endl;
        throw; // rethrows the exception
    }
    d2.show();  //This only called when neither bad_hmean nor bad_gmean is thrown
    return (am + hm + gm) / 3.0;
}

double hmean(double a, double b)
{
    if (a == -b)
        throw bad_hmean(a, b);
    return 2.0 * a * b / (a + b);
}

double gmean(double a, double b)
{
    if (a < 0 || b < 0)
        throw bad_gmean(a, b);
    return std::sqrt(a * b);
}
