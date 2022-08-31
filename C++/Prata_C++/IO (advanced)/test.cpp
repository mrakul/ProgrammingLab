#include <iostream>
#include <cstring>
#include <iomanip>

int main(int argc, char const* argv[])
{
    using std::cout;
    using std::endl;
    using std::flush;

    // const char *state1 = "Florida";
    const char* state2 = "Kansas";
    const char* state3 = "Euphoria";
    int str2Len = std::strlen(state2);

    cout << 'W' << endl;    //the same as cout.put('W');
    // Print out C-string with length of state2 string
    cout.write(state3, str2Len);

    // cout as chars test
    long val = 560031841;
    cout.write((char*)&val, sizeof(long));

    cout << "Enter a number: " << endl;
    float num;
    std::cin >> num; // When input is pending, "Enter a number: " buffer content is flushed to output(?)
    using std::setw;

    cout.setf(std::ios_base::left, std::ios_base::adjustfield);

    cout << setw(15) << "Decimal form"
        << setw(15) << "Hex form"
        << setw(15) << "Octal form" << endl;

    cout.setf(std::ios::showbase); // or cout << showbase;
    cout << setw(15) << num << std::hex
         << setw(15) << num << std::oct
         << setw(15) << num << endl;

    // Explicitly flush the buffer
    cout << "Hello, good-looking! " << flush;
    cout << "Wait just a moment, please." << endl;
    flush(cout);
    cout << flush;

    return 0;
}