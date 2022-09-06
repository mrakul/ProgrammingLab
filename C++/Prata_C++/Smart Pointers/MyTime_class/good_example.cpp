#include <memory>
#include <string>
#include "../../OOP/MyTime (OpOverload)/MyTime.h"

int main(int argc, char const *argv[])
{
    using std::auto_ptr;
    using std::unique_ptr;
    using std::shared_ptr;
    using std::string;
    using std::cout, std::endl;

    //1. New string auto_ptr (auto is deprecated now)
    //auto_ptr<string> ptrString {new string};    //or auto_ptr<string>(new string);

    //2. New MyTime unique_ptr
    unique_ptr<MyTime> myTimeUnique = unique_ptr<MyTime>(new MyTime(5, 30));
    // unique_ptr<MyTime> MyTimeUnique2 = MyTimeUnique;                 // Compiler restricts this
    myTimeUnique.reset(new MyTime(6, 45));                              // Ownership to another object, the old one is destructed, MyTime destructor is called (and the deleter is called implicitly?)

    MyTime * myTimePtr = myTimeUnique.release();                        // Release the ownership, so the object should be deleted by the caller for the target pointer

    delete myTimePtr;                                                   // Destruct the object

    //3. New MyTime obj shared_ptr
    // Create a block to observe when the destructor will be called
    {
    shared_ptr<MyTime> myTimeObj = unique_ptr<MyTime>(new MyTime(2, 3));
    shared_ptr<MyTime> myTimeObj2 = myTimeObj;

    cout << "myTimeObj.useCount() = " << myTimeObj.use_count()
        << " myTimeObj2.useCount() = " << myTimeObj2.use_count() << endl;       // For both it is observed that use_count() call gives 2 -- both have ownership

    myTimeObj.reset();           //Reset the pointer, not destroying object, since myTimeObj2 still manages it

    cout << "myTimeObj.useCount() = " << myTimeObj.use_count()
        << " myTimeObj2.useCount() = " << myTimeObj2.use_count() << endl;

    myTimeObj.unique() ? cout << "Yes " : cout << "No ";
    cout << (myTimeObj2.unique() ? "Yes " : "No ") << endl;     //braces makes conditional operator more prioritized (meaning operator precedence)

    myTimeObj2.reset(new MyTime(7, 45));           //Reset the pointer to manage another object, destroys the object: MyTime destructor is called (implicitly called the deletor of the old one memory?)

    cout << "myTimeObj.useCount() = " << myTimeObj.use_count()
        << " myTimeObj2.useCount() = " << myTimeObj2.use_count() << endl;

    //myTimeObj2.reset();                            // Reset the pointer, destroys the object: MyTime destructor is called
    }                                                // Destroy existing objects here

    return 0;
}
