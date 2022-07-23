#include <iostream>
#include <cstring>

int main(int argc, char const *argv[])
{
    using std::cout;
    using std::endl;
    using std::flush;

    // const char *state1 = "Florida";
    const char *state2 = "Kansas";
    const char *state3 = "Euphoria";
    int str2Len = std::strlen(state2);

    cout << 'W' << endl;
    // Print out C-string with length of state2 string
    cout.write(state3, str2Len);

    // cout as chars test
    long val = 560031841;
    cout.write((char *)&val, sizeof(long));

    cout << "Enter a number: ";
    float num;
    std::cin >> num; // When input is pending, "Enter a number: " buffer content is flushed to output(?)

    // Explicitly flush the buffer
    cout << "Hello, good-looking! " << flush;
    cout << "Wait just a moment, please." << endl;
    flush(cout);
    cout << flush;

    return 0;
}