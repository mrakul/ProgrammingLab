#include <memory>
#include <string>
#include "../../OOP/MyTime (OpOverload)/MyTime.h"

std::shared_ptr<MyTime> timeFactory(int hours, int minutes);

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
    shared_ptr<MyTime> myTimeObj2 = myTimeObj;                                  // Create another pointer, which points to the same object
    // shared_ptr<MyTime> myTimeObj2 = std::make_shared<MyTime>(*myTimeObj);    // This form creates another one object basing on the myTimeObj, so there are two different objects

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

    /*** 4. timeFactory() call: ***/
    auto newSharedPtr = timeFactory(10, 30);         // Pointer is copied from the timeFactory()
    cout << "newSharedPtr.useCount() = " << newSharedPtr.use_count() << endl;       // Here it has exclusive ownership

    }                                                // Destroy existing objects here

    return 0;

}

// factory returns a shared_ptr pointing to a dynamically allocated object
std::shared_ptr<MyTime> timeFactory(int hours, int minutes)
{
    // shared_ptr will take care of deleting this memory
    return std::make_shared<MyTime>(hours, minutes);            //Constructor of MyTime is called here
}