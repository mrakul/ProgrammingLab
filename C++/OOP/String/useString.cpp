#include <iostream>
using std::cout;
#include "String.h"

//Additional functions to test
void callme1(String &); // pass by reference
void callme2(String);   // pass by value

int main()
{
    using std::endl;
    {
        cout << "Starting an inner block.\n";
        String obj1("Object1");
        String obj2("Object2");
        String obj3("Object3");
        cout << "obj1: " << obj1 << endl;
        cout << "obj2: " << obj2 << endl;
        cout << "obj3: " << obj3 << endl;

        //Check pass by reference
        callme1(obj1);
        cout << "obj1: " << obj1 << endl;

        //Since the object is passed by value, the destructor is called for the temporary local object also.
        //If no copy constructor to call then object number is not incremented (default copy constructor is called)
        //Second, it releases the memory of the strPtr by calling the destructor
        //Note: destructor is called for the temporary object just right after the call
        callme2(obj2);
        cout << "obj2: " << obj2 << endl;

        cout << "Initialize one object to another:\n";
        //Again, copy constructor is called
        String sailor = obj3;
        cout << "sailor: " << sailor << endl;

        //Assignment operator check
        cout << "Assign one object to another:\n";
        String obj4;
        obj4 = obj1;
        cout << "obj4: " << obj4 << endl;

        //[] operator overloading test
        String object1{"Right"};
        object1[0] = 'F';
        cout << object1;
        cout << "Exiting the block.\n";
    }

    cout << "End of main()\n";
    return 0;
}

void callme1(String &rsb) {
    cout << "String passed by reference:\n";
    cout << " \"" << rsb << "\"\n";
}
void callme2(String sb) {
    cout << "String passed by value:\n";
    cout << " \"" << sb << "\"\n";
}