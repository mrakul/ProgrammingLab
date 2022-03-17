#include <iostream>
#include <fstream> // file I/O support
#include <cstdlib> // to include exit() function
const int SIZE = 60;

int main()
{
    using namespace std;
    char filename[SIZE];
    ifstream inFile; // object for handling file input
    cout << "Enter name of data file: ";
    cin.getline(filename, SIZE);
    inFile.open(filename); // associate inFile with a file
    if (!inFile.is_open()) // failed to open file
    {
        cout << "Could not open the file " << filename << endl;
        cout << "Program terminating.\n";
        exit(EXIT_FAILURE);
    }
    double value;
    double sum = 0.0;
    int count = 0;        // number of items read

    //inFile >> value; // first read to check inFile.good()
    //while (inFile.good()) // while input good and not at EOF
    while (inFile >> value) // read and test for success, since inFileinFile, when placed in a context in which a bool value expected, evaluates to inFile.good()—that is, to true or false
    {
        cout << "Current read value: " << value << endl;
        ++count;         // count read numbers
        sum += value;    // calculate total value
        inFile >> value; // get next value
    }

    //If an error or EOF encountered, or unknown reason
    if (inFile.eof())
        cout << "End of file reached.\n";
    else if (inFile.fail())
        cout << "Input terminated by data mismatch.\n";
    else if (inFile.bad())
        cout << "Input terminated for unknown reason.\n";

    if (count == 0)
        cout << "No data processed.\n";
    else
    {
        cout << "Items read: " << count << endl;
        cout << "Sum: " << sum << endl;
        cout << "Average: " << sum / count << endl;
    }
    inFile.close(); // fClose the file

    return 0;
}