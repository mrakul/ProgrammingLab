#include "useless.h"

int main(int argc, char const* argv[])
{
    cout << "\t### Starting inner block ###" << endl;
    {
        Useless obj1(10, 'x');           // int, char constructor is called
        Useless obj2 = obj1;             // copy constructor is called
        Useless obj3(20, 'o');           // int, char constructor is called

        // Notes:
        // 1. Move constructor is called explicitly if specify move(objX + objX)
        // After the Move Constructor, the temporary object is deleted as usual
        // 2. (!!!) If not specify move() explicitly, that is Uselecss objX(objX + objX), the compiler, g++ in our case, makes optimization and just transfers the name of obj4 to the object created in operator+().
        // In this case, only 4 objects are created, but the result is the same, without calling move constructor, but making the same
        Useless obj4(move(obj1 + obj3));       // (!!!) calls operator+(), move constructor is called if specify move() explicitly since operator+() returns RVALUE

        //Print out the objects
        cout << "object one: ";
        obj1.ShowData();
        cout << "object two: ";
        obj2.ShowData();
        cout << "object three: ";
        obj3.ShowData();
        cout << "object four: ";
        obj4.ShowData();

    }

    cout << "\t### After inner block ###" << endl;
}