#include <string>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    //C-strings input
    // char info[100];
    // cin >> info;            // read a word
    // cin.getline(info, 100); // read a line, discard \n
    // cin.get(info, 100);     // read a line, leave \n in queue

    //For string objects, recall, you have two options :
    string stuff;
    //Just an example to print out pointer to the actual data: they are both equal after the default constructor, but non-null
    char const * ptr1 = stuff.data();
    cout << hex << reinterpret_cast<const void*>(ptr1) << endl;
    char const * ptr2 = stuff.c_str();
    cout << hex << reinterpret_cast<const void*>(ptr2) << endl;

    cin >> stuff;        // read a word (stays /n in the buffer)
    cout << "stuff's length: " << stuff.length() << endl;
    char ch = cin.get();    //discard newline
    while(getline(cin, stuff) && !stuff.empty())
    {
        std::cout << stuff.length();
    } // read a line, discard \n

    // Both versions of getline() allow for an optional argument that specifies which character
    // to use to delimit input:
    //cin.getline(info, 100, ':'); // read up to ':', discard :
    //getline(cin, stuff, ':');         // read up to ':', discard :
/*
    // The main operational difference is that the string versions automatically size the target
    //     string object to hold the input characters :
    char fname[10];
    string lname;
    cin >> fname;           // could be a problem if input size > 9 characters
    cin >> lname;           // can read a very, very long word
    cin.getline(fname, 10); // may truncate input
    //?getline(cin, fname);    // no truncation
*/
    return 0;
}
