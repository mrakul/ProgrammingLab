// useless.cpp -- an otherwise useless class with move semantics
#include <iostream>

using namespace std;

class Useless
{
private:
    int numElements;             // number of elements
    char *ptrData;               // pointer to data
    static int countObjects;     // number of objects (static)
    void ShowObject() const;

public:
    //Constructors
    Useless();
    explicit Useless(int numToFill);            // To prevent implicit conversion like obj = 3;
    Useless(int numToFill, char charToFill);
    //Copy and move
    Useless(const Useless &sourceObj);          // Regular Copy Constructor
    Useless(Useless &&sourceObj);               // Move Constructor

    ~Useless();
    Useless operator+(const Useless &addedObj) const;

    //Copy assignment operator
    Useless &operator=(const Useless &assignedObj);
    //Move assignment operator
    Useless &operator=(Useless &&movedObj);

    void ShowData() const;
};
