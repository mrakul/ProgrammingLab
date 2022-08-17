// useless.cpp -- an otherwise useless class with move semantics
#include <iostream>

using namespace std;

class Useless
{
private:
    int numElements;             // number of elements
    char* ptrData;               // pointer to data
    static int countObjects;     // number of objects (static)
    void ShowObject() const;

public:
    //Constructors
    Useless();
    explicit Useless(int numToFill);
    Useless(int numToFill, char charToFill);
    //Copy and move
    Useless(const Useless& sourceObj);       // regular copy constructor
    Useless(Useless&& sourceObj);            // move constructor

    ~Useless();
    Useless operator+(const Useless& addedObj)const;
    // need operator=() in copy and move versions, ommitted just for demonstration

    void ShowData() const;
};
