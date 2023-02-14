#include <iostream>
#include <string>

using namespace std;

class ClassToCheck
{
private:
    int id;
    string memberString;

public:
    ClassToCheck(int numToSet, string stringToSet): id(numToSet), memberString(stringToSet)
    {
        cout << "Constructor ClassToCheck(int numToSet, string stringToSet) is called" << endl;
    }
    // This conflicts with the Constructor above
    // ClassToCheck(const int &numToSet, const string &stringToSet): id(numToSet), memberString(stringToSet)
    // {
    //     cout << "Constructor ClassToCheck(int numToSet, strint stringToSet) is called" << endl;
    // }


    ClassToCheck(const ClassToCheck &copiedObject): id(copiedObject.id), memberString(copiedObject.memberString)
    {}
    // ClassToCheck(ClassToCheck &&copiedObject): id(copiedObject.id), memberString(copiedObject.memberString)
    // {}

    friend ostream &operator<<(ostream &outStream, const ClassToCheck &outObject)
    {
        cout << "Object #" << outObject.id << ", String: " << outObject.memberString << endl;
        return outStream;
    }
};

int main(int argc, char const *argv[])
{
    ClassToCheck myObject1(1, "TestString1");
    ClassToCheck myObject2(2, "TestString2");
    // ClassToCheck myObject3;                             // If specify any Constructor, then no default constructor presents
    ClassToCheck myObject4(myObject1);                     // If specify only Move Constructor, then copy Constructor is deleted
    ClassToCheck myObject5(move(myObject2));               // If specify only Copy Constructor (with const reference), this will use Copy Constructor

    cout << myObject1 << endl;
    cout << myObject2 << endl;
    cout << myObject4 << endl;
    cout << myObject5 << endl;

    return 0;
}

