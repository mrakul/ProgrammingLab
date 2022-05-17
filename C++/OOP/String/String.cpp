// strngbad.cpp -- String class methods
#include <cstring> // string.h for some
#include "String.h"

using std::cout;

// Initialize static class member
int String::objectsNumber = 0;

// construct String from C string
String::String(const char *s)
{
    strLen = std::strlen(s);                                            // set size
    strPtr = new char[strLen + 1];                                      // allot storage
    std::strcpy(strPtr, s);                                             // initialize pointer
    objectsNumber++;                                                    // set object count
    cout << objectsNumber << ": \"" << strPtr << "\" object created\n"; // To observe what happened
}
String::String() // default constructor
{
    strLen = strlen("C++") + 1;
    strPtr = new char[strLen];
    std::strcpy(strPtr, "C++"); // default string
    objectsNumber++;
    cout << objectsNumber << ": \"" << strPtr << "\" default object created\n"; // To observe what happened
}

// Copy constructor to make a deep copy of the object
String::String(const String &st)
{
    // Make deep copy of the object
    strLen = st.strLen;                                                 // set size
    strPtr = new char[strLen + 1];                                      // allot storage
    std::strcpy(strPtr, st.strPtr);                                     // initialize pointer
    objectsNumber++;                                                    // set object count
    cout << objectsNumber << ": \"" << strPtr << "\" object created\n"; // To observe what happened
}

String::~String() // necessary destructor
{
    cout << "\"" << strPtr << "\" object deleted, "; // To observe what happened
    --objectsNumber;                                 // Decrease number of objects
    cout << objectsNumber << " left\n";              // To observe what happened
    delete[] strPtr;                                 // Delete obtained memory
}
std::ostream &operator<<(std::ostream &os, const String &st)
{
    os << st.strPtr;
    return os;
}

String &String::operator=(const String &source)
{
    if (this == &source)
        return *this;
    // release obtained memory by the strPtr of the target
    delete[] strPtr;    //or 'delete this->strPtr'

    strLen = source.strLen;
    strPtr = new char[strLen + 1];
    std::strcpy(strPtr, source.strPtr);
    return *this;
}

char &String::operator[](int i)
{
    return strPtr[i];
}

const char &String::operator[](int i) const
{
    return strPtr[i];
}