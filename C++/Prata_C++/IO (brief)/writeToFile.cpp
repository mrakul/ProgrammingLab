#include <iostream>
#include <fstream> // for file I/O

int main()
{
    using namespace std;
    char automobile[50];
    int year;
    double a_price;
    double d_price;
    ofstream outFile;            // create object for output
    outFile.open("carinfo.txt"); // Open a file (get file descriptor and so on). Note: opened in the text mode (by default?)
    cout << "Enter the make and model of automobile: ";
    cin.getline(automobile, 50);
    cout << "Enter the model year: ";
    cin >> year;
    cout << "Enter the original asking price: ";
    cin >> a_price;
    d_price = 0.913 * a_price;

    // Output to stdout
    cout << fixed;          //write floating-point values in fixed-point notation!
    cout.precision(2);
    cout.setf(ios_base::showpoint);
    cout << "Make and model: " << automobile << endl;
    cout << "Year: " << year << endl;
    cout << "Was asking $" << a_price << endl;
    cout << "Now asking $" << d_price << endl;

    // Output to the text file
    outFile << fixed;
    outFile.precision(2);
    outFile.setf(ios_base::showpoint);
    outFile << "Make and model: " << automobile << endl;
    outFile << "Year: " << year << endl;
    outFile << "Was asking $" << a_price << endl;
    outFile << "Now asking $" << d_price << endl;
    outFile.close(); // done with file

    cin.get();      // cin.get() is a special case to read any symbol (including NEWLINE) not to stay it in the buffer
    cin.get();

    return 0;
}