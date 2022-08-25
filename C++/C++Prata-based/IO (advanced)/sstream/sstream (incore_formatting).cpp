#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;

const int BUFF_SIZE = 12;

int main(int argc, char const* argv[])
{

    // 1. Use of stringstream, that is for input and output
    stringstream strStream;                                             // Bidirectional stringstream (two streams?)
    char strToConvert[BUFF_SIZE];
    // strToConvert[4] = 'g';   // (?)

    strStream << "Number: " << 43.59 << " Cringe sentence#" << endl;     // Write OUT to the string stream
    cout << strStream.str();                                            // Print out the stream's content
    // strStream.read(strToConvert, 15);  // Write the stream's content to the string (chars)
    // cout.write(strToConvert, 5);    // The alternative to output to cout

    while (strStream.get(strToConvert, BUFF_SIZE))// ,'#')) //- check another delimiter             //Read IN to the strToConver: get() continues reading if the buffer is small, getline() stops immediately
        cout.write(strToConvert, strStream.gcount());           // Print out the number of read characters!
    // Read word-by-word and print out
    // while (strStream >> strToConvert)
    //     cout << " " << strToConvert;

    //strStream.clear();
    cout << strStream.eofbit << " " << strStream.badbit << " " << strStream.failbit << endl;    //read() sets EOF and fail bits
    cout << strStream.eof() << " " << strStream.bad() << " " << strStream.fail();

    strStream.clear();

    char ch = strStream.get();
    ch = ch;

    // 2. Use of ostringstream to only output there
    ostringstream outStream;
    string name;
    cout << "What is your name? ";
    getline(cin, name);

    int age;
    cout << "How old are you? ";
    cin >> age;

    // Write formatted information to the stream
    outStream << "Your name is " << name << ", and your age is " << age << endl;
    // Using the str() method “freezes” the object, and you can no longer write to it
    string result = outStream.str();

    cout << result;         // Show formatted string

    // 3. Use of istringstream to only input
    char sentence[] = "This is the best sentence in the world";
    istringstream inStream(sentence);           //Constructor to initialize by the sentence above
    char word[10];
    while (inStream >> word)
        cout << word << endl;


    return EXIT_SUCCESS;
}