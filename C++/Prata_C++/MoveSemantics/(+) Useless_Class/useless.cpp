#include "useless.h"
#include <cstring>

//Initialize static variable

int Useless::countObjects = 0;

Useless::Useless()
{
    ++countObjects;
    numElements = 0;
    ptrData = nullptr;
    cout << "! Default Constructor called, number of objects: " << countObjects << endl;
    ShowObject();
}

Useless::Useless(int numToCreate) : numElements(numToCreate)
{
    ++countObjects;
    cout << "! int Constructor called, number of objects: " << countObjects << endl;
    ptrData = new char[numElements];
    ShowObject();
}

Useless::Useless(int numToCreate, char charToFill) : numElements(numToCreate)
{
    ++countObjects;
    cout << "! (int, char) Constructor called, number of objects: " << countObjects << endl;
    ptrData = new char[numElements];
    for (int i = 0; i < numElements; i++)
        ptrData[i] = charToFill;
    ShowObject();
}

//Copy constructor
Useless::Useless(const Useless &sourceObj) : numElements(sourceObj.numElements)
{
    ++countObjects;
    cout << "! Copy Constructor called, number of objects: " << countObjects << endl;
    ptrData = new char[numElements];
    for (int i = 0; i < numElements; i++)
        ptrData[i] = sourceObj.ptrData[i];
    ShowObject();
}

// Move Constructor: creates an object actually and swaps bookkeeping info with the rvalue object
Useless::Useless(Useless &&sourceObj) : numElements(sourceObj.numElements)
{
    ++countObjects;
    cout << "! Move constructor called, number of objects: " << countObjects << endl;
    ptrData = sourceObj.ptrData;        // steal address
    sourceObj.ptrData = nullptr;        // give old object nothing in return (need to swap actually?).
    sourceObj.numElements = 0;          // (?) Need to swap? Note: since we are creating the new object, nothing is allocated for it, so we can set to 0 and nullptr sourceObj (as was for targed)
    ShowObject();
}

//Note: operator+() doesn't create object automatically as constructors, needs to create it explicitly
Useless Useless::operator+(const Useless &addedObj) const                                                //Returning rvalue (temp object, not the reference to itself)
{
    cout << "Entering operator+()" << endl;
    //Create another one temp object concatenating both objects (length of sum of both)
    Useless temp = Useless(numElements + addedObj.numElements);

    //Populate with the data of source and then the added object
    for (int i = 0; i < numElements; i++)
        temp.ptrData[i] = ptrData[i];
    for (int i = numElements; i < temp.numElements; i++)
        temp.ptrData[i] = addedObj.ptrData[i - numElements];

    cout << "Leaving operator+()" << endl;

    //Return temp object as rvalue(?)
    return temp;
}

//Assignment operator of lvalue (copy assignment operator)
Useless &Useless::operator=(const Useless &assignedObj)
{
    if (this == &assignedObj)                               //If assign an object to itself, then just return itself
        return *this;

    delete[] this->ptrData;                                 //Release the obtained memory before allocating the new memory

    this->numElements = assignedObj.numElements;            //Copy number of elements
    this->ptrData = new char[numElements];                  //Allocate enough memory
    //Or use a cycle explicitly
    memcpy(this->ptrData, assignedObj.ptrData, this->numElements);      //Copy all the data from the assigned to the source

    return *this;
}

//Assignment operator of rvalue (move assignment operator)
Useless &Useless::operator=(Useless &&movedObj)
{
    if (this == &movedObj)                               //If move an object to itself, then just return itself
        return *this;

    //One opportunity is to swap pointers and number of elements
    //swap(this->numElements, movedObj.numElements);
    //swap(this->ptrData, movedObj.ptrData);

    //Or correctly to release the target explicitly and set the pointer/number of the moved object, resetting the moved object members?
    delete[] this->ptrData;
    this->numElements = movedObj.numElements;
    this->ptrData = movedObj.ptrData;
    movedObj.numElements = 0;
    movedObj.ptrData = nullptr;

    return *this;
}

Useless::~Useless()
{
    cout << "! Destructor called, objects left: " << --countObjects << endl;
    cout << "deleted object:" << endl;
    ShowObject();
    delete[] ptrData;
}


void Useless::ShowObject() const
{
    cout << "Number of elements: " << numElements;
    cout << " Data address: " << (void *)ptrData << endl;
}

void Useless::ShowData() const
{
    if (numElements == 0)
        cout << "(object empty)";
    else
        for (int i = 0; i < numElements; i++)
            cout << ptrData[i];
    cout << endl;
}