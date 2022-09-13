#include "useless.h"

//Factory function to check the behavior with move semantics
Useless objFactory();

int main(int argc, char const* argv[])
{
    cout << "\t### Starting inner block ###" << endl;
    {
        Useless obj1(10, 'x');           // int, char constructor is called
        Useless obj2 = obj1;             // copy constructor is called
        Useless obj3(20, 'o');           // int, char constructor is called

        /*** Move constructor using ***/
        // Notes:
        // 1. operator+(&) is called first and returns rvalue
        // 2. Move constructor is called explicitly if specify move(objX + objX)
        // After the Move Constructor, the temporary object is deleted as usual
        // 3. (!!!) If not specify move() explicitly, that is Useless objX(objX + objX), the compiler, g++ in our case, makes optimization and just transfers the name of obj4 to the object created in operator+().
        // In this case, only 4 objects are created, but the result is the same, without calling move constructor, but making the same
        Useless obj4(move(obj1 + obj3));       // (!!!) calls operator+(), move constructor is called if specify move() explicitly since operator+() returns RVALUE
        // Additional note:
        // For the old compilers without Move Semantics (where there is no && definition and move()), the sequence will be as following:
        // 1. Calls the operator+()
        // 2. operator+() creates the temporary temp object
        // 3. When return temp, the Copy Constructor is called (&) to create a new temp2 object (having reference) from temp object
        // 4. Temp object is destructed (operator+())
        // 5. Copy Constructor is created to copy from temp2 object to obj4
        // 6. Destruct temp2 object

        //Print out the objects
        cout << "object one: ";
        obj1.ShowData();
        cout << "object two: ";
        obj2.ShowData();
        cout << "object three: ";
        obj3.ShowData();
        cout << "object four: ";
        obj4.ShowData();

        /*** Copy Assignment operator using ***/
        Useless obj5;       //Use default constructor
        obj5 = obj4;        //Make the copy of obj4

        cout << "### Copy assignment use ###" << endl;
        cout << "object five: ";
        obj5.ShowData();
        cout << "object four: ";
        obj4.ShowData();

        /*** Move Assignment operator using ***/
        obj5 = move(obj1);
        obj5 = static_cast<Useless &&>(obj2);           //Or to static_cast to rvalue. Those syntaxes are equal

        //Print out the objects
        cout << "### Move assignment use ###" << endl;
        cout << "object one: ";
        obj1.ShowData();
        cout << "object two: ";
        obj1.ShowData();
        cout << "object five: ";
        obj5.ShowData();

        /*** Factory class checking ***/
        Useless obj6;                                   // Use default constructor
        obj6 = objFactory();                            // Assign rvalue of the objFactory: move constructor is called and the temporary object is deleted

        Useless *obj7Ptr = new Useless{obj6};
        cout << obj7Ptr;
    }

    // May be observed that obj5 has 10 elements when released, and obj1 has 30, so they swapped (if case of swap)
    // Or if the moved object is reset, then it is empty ("object is empty" output)

    cout << "\t### After inner block ###" << endl;
}

Useless objFactory(){
    return Useless(5, 'X');                            // Constructor (int, char) is called
}