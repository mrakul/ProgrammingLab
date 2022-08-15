#include <iostream>
#include "String.h"

//Additional functions to test
void callme1(String &); // pass by reference
void callme2(String);   // pass by value

using std::endl;
using std::cout;

int main()
{
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

        //Since the object is passed by value, the destructor is called for the temporary object also.
        //If no copy constructor implemented then object number is not incremented (default copy constructor is called)
        //Second, it releases the memory of the strPtr by calling the destructor
        //Note: destructor is called for the temporary objectX_COPY object (with the name of Object2) just right after the call callme2(), (?) that is exists in callme2 only
        callme2(obj2);
        cout << "obj2: " << obj2 << endl;

        cout << "Initialize one object to another:" << endl;
        //Again, COPY CONSTRUCTOR is called
        String objBasedOnAnother = obj3;       //This is another syntax for String sailor = String(obj3);  Or this:  String sailor(obj3)?
        //String objBasedOnAnother(obj3);

        cout << "objBasedOnAnother: " << objBasedOnAnother << endl;

        //Assignment operator check
        cout << "Assign one object to another:" << endl;
        String obj4;
        obj4 = obj1;
        cout << "obj4: " << obj4 << endl;

        //[] operator overloading test
        String object1{"Right"};        //Simple String(const char * ) constructor is called
        object1[0] = 'F';
        cout << object1;
        cout << "Exiting the block." << endl;
    }

    cout << "End of main()" << endl;

    return 0;
}

void callme1(String &rsb) {
    cout << "String passed by reference:" << endl;
    cout << " \"" << rsb << "\"\n";
}

void callme2(String sb) {
    cout << "String passed by value:" << endl;
    cout << " \"" << sb << "\"\n";
}