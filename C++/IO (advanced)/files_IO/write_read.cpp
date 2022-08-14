// fileio.cpp -- saving to a file
#include <iostream>     //not needed for many systems (needed for cout/cin in my case?)
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

int main(int argc, char const* argv[])
{
    using namespace std;
    string fileName;

    // 1. Write to a file
    //Create a new file
    cout << "Enter name for new file: ";
    cin >> fileName;
    //Create a new file stream and associate it with the file (opening)
    ofstream foutStream;
    // foutStream.open(fileName.c_str());    //ofstream fStream(fileName.c_str()); Note: fileName may be just used since string will be converted to char *
    foutStream.open(argv[1], ios_base::out | ios_base::app);    // Open the file of the first argument, options are optionally, out is set by default, app (append) not to truncate the file

    //Check if the file is opened
    if (foutStream.is_open())
        cout << "File is opened ...";
    else
        exit(EXIT_FAILURE);

    foutStream << "<<< SECRET DATA BELOW >>>" << endl;           // Write the header
    cout << "Enter the number you want to save to a file: ";     // write to screen
    float numToSave;
    cin >> numToSave;

    // The simplest way to write is:
    foutStream << "The saved number is: " << numToSave << endl;

    // By using write()
    char floatToChars[10];
    snprintf(floatToChars, sizeof(floatToChars), "%f", numToSave);      //Convert to string to output and use write (or jts use << operator)
    foutStream.write("The saved number, sprintf conversion: ", strlen("The saved number, sprintf conversion: ")).write((char*)&numToSave, sizeof(numToSave)).write(floatToChars, strlen(floatToChars)).put('\n');   //writing string

    // (!!!) Convert by sstream
    char strToConvert[10];
    stringstream strStream;
    strStream << numToSave;     // Write the number to the string stream
    strStream >> strToConvert;  // Write the stream's content to the string (chars)
    foutStream.write("The saved number, stringstream: ", strlen("The saved number, stringstream: ")).write(floatToChars, strlen(floatToChars)).put('\n');

    foutStream.close();     // Close the file

    // 2. Read the saved data
    // Create input stream object for the created file and associate with it
    //ifstream finStream(fileName.c_str());
    ifstream finStream(argv[1]);

    cout << "Here are the contents of " << fileName << ":" << endl;
    char bufToRead[10];
    /*while (finStream.get(ch)) // read character from file and
        cout << ch; // write it to screen
    cout << "Done" << endl; */

    while(finStream.read(bufToRead,  sizeof(bufToRead)))  //getline() sets the fail bit after reading the first portion; get() sets also fail after getting to NEWLINE
        cout.write(bufToRead, sizeof(bufToRead));         // And read doesn't set NULL at the end, so need to use cout.write() to specify size of the buffer
    cout.put('\n');

    cout << finStream.eofbit << " " << finStream.badbit << " " << finStream.failbit << endl;    //read() sets EOF and fail bits
    cout << finStream.eof() << " " << finStream.bad() << " " << finStream.fail();

    finStream.close();

    return 0;
}