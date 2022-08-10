// cinexcp.cpp -- having cin throw an exception
#include <iostream>
#include <exception>
int main(int argc, char const* argv[])
{
    using namespace std;
    // Set failbit to cause an exception to be thrown
    cin.exceptions(ios_base::failbit);
    cout << "Enter numbers: ";
    int sum = 0;
    int input;
    try
    {
        while (cin >> input)
        {
            sum += input;
        }
    }
    catch (ios_base::failure& bf)
    {
        cout << bf.what() << endl;
        cout << "O! the horror!\n";
    }

    cout << "Last value entered = " << input << endl;
    cout << "Sum = " << sum << endl;
    return 0;
}