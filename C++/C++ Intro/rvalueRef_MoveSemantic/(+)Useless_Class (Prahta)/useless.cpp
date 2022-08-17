#include "useless.h"

//Initialize static variable

int Useless::countObjects = 0;

Useless::Useless(){
    ++countObjects;
    numElements = 0;
    ptrData = nullptr;
    cout << "! Default Constructor called, number of objects: " << countObjects << endl;
    ShowObject();
}

Useless::Useless(int numToCreate) : numElements(numToCreate){
    ++countObjects;
    cout << "! int Constructor called, number of objects: " << countObjects << endl;
    ptrData = new char[numElements];
    ShowObject();
}
Useless::Useless(int numToCreate, char charToFill) : numElements(numToCreate){
    ++countObjects;
    cout << "! (int, char) Constructor called, number of objects: " << countObjects << endl;
    ptrData = new char[numElements];
    for (int i = 0; i < numElements; i++)
        ptrData[i] = charToFill;
    ShowObject();
}

//Copy constructor
Useless::Useless(const Useless& sourceObj) : numElements(sourceObj.numElements){
    ++countObjects;
    cout << "! Copy Constructor called, number of objects: " << countObjects << endl;
    ptrData = new char[numElements];
    for (int i = 0; i < numElements; i++)
        ptrData[i] = sourceObj.ptrData[i];
    ShowObject();
}

//Creates an object actually and swaps bookkeeping info with the rvalue object
Useless::Useless(Useless&& sourceObj) : numElements(sourceObj.numElements)
{
    ++countObjects;
    cout << "! Move constructor called, number of objects: " << countObjects << endl;
    ptrData = sourceObj.ptrData;        // steal address
    sourceObj.ptrData = nullptr;        // give old object nothing in return (need to swap?)
    sourceObj.numElements = 0;          // (?) Need to swap?
    ShowObject();
}

Useless::~Useless()
{
    cout << "! Destructor called, objects left: " << --countObjects << endl;
    cout << "deleted object:" << endl;
    ShowObject();
    delete[] ptrData;
}

//Note: operator+() doesn't create object automatically as constructors, needs to create it explicitly
Useless Useless::operator+(const Useless& addedObj) const        //Returning rvalue (temp object, not the reference to itself)
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

void Useless::ShowObject() const
{
    cout << "Number of elements: " << numElements;
    cout << " Data address: " << (void*)ptrData << endl;
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