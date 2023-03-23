#include <memory>
#include <string>
#include "../../OOP/MyTime (OpOverload)/MyTime.h"

std::shared_ptr<MyTime> timeFactoryShared(int hours, int minutes);
std::unique_ptr<MyTime> timeFactoryUnique(int hours, int minutes);

int main(int argc, char const *argv[])
{
    using std::auto_ptr;
    using std::unique_ptr;
    using std::shared_ptr;
    using std::string;
    using std::cout, std::endl;
    using std::boolalpha;

    // 1. New string auto_ptr() (auto is deprecated now)
    //auto_ptr<string> ptrString {new string};    //or auto_ptr<string>(new string);

    //  2. unique_ptr() examples: observe how unique_ptr() is destroyed after quitting the block
    {
        unique_ptr<MyTime> myTimeUnique = unique_ptr<MyTime>(new MyTime(5, 30));
        // unique_ptr<MyTime> MyTimeUnique2 = MyTimeUnique;                 // Compiler restricts this: "use of deleted function 'std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&)"
        myTimeUnique.reset(new MyTime(6, 45));                              // Ownership to another object, the old one is destructed, MyTime destructor is called (and the deleter is called implicitly?)

        MyTime *myTimePtr = myTimeUnique.release();                         // Release the ownership, so the object should be deleted by the caller for the target pointer.
                                                                            // In this case, using *myTimePtr leads to Segmentation Fault (as for auto_ptr which lost the ownership of the object)

        delete myTimePtr;                                                   // Destruct the object explicitly

        // 2.1. Example with transfering ownership by using Move Semantics
        unique_ptr<MyTime> myTimeSource = unique_ptr<MyTime>(new MyTime(1, 50));
        unique_ptr<MyTime> myTimeTarget;

        // myTimeTarget = myTimeSource;                                     // This is restricted: explicit copying not to make fake copy assignment
        myTimeTarget = move(myTimeSource);                                  // (!) But this is ALLOWED, since myTimeSource is considered as a temporary (rvalue), so it will lose the ownership in this case as if it will be not used

    }                                                                       // Note: here, myTimeUnique doesn't own the MyTime object and points to nullptr.

    // 3. shared_ptr() example pointing to MyTime object
    {
        unique_ptr<MyTime>(new MyTime(10, 10));                                        // Interesting that this creates a temporary pointer and destroys it suddenly with the related object
        shared_ptr<MyTime> myTimeShared = unique_ptr<MyTime>(new MyTime(2, 3));        // This is possible since unique_ptr is temporary (?)
        shared_ptr<MyTime> myTimeShared2 = myTimeShared;                                  // Create another pointer, which points to the same object
        // shared_ptr<MyTime> myTimeShared2 = std::make_shared<MyTime>(*myTimeShared);    // This form creates another one object basing on the (*myTimeShared), so there are two different objects

        cout << "myTimeShared.useCount() = " << myTimeShared.use_count()
            << " myTimeShared2.useCount() = " << myTimeShared2.use_count() << endl;       // For both it is observed that use_count() call gives 2 -- both have ownership

        myTimeShared.reset();                                                             // Reset the pointer, not destroying object, since myTimeShared2 still manages it

        cout << "myTimeShared.useCount() = " << myTimeShared.use_count()                  // myTimeShared points to nullptr here, since was reset (shows 0 on count)
            << " myTimeShared2.useCount() = " << myTimeShared2.use_count() << endl;       // myTimeShared2 shows 1, since still pointing to the shared object

        cout << boolalpha << "myTimeShared unique : " << myTimeShared.unique() << endl;   // Returns False, since doesn't point to any object
        cout << boolalpha << "myTimeShared2 unique : " << myTimeShared2.unique() << endl; // Returns True, since still points to the created object

        myTimeShared2.reset(new MyTime(7, 45));                                           // Reset the pointer to manage another object, destroys the object: previous MyTime destructor is called (implicitly called the deletor of the old one memory?)

        cout << "myTimeShared.useCount() = " << myTimeShared.use_count()
            << " myTimeShared2.useCount() = " << myTimeShared2.use_count() << endl;

        //myTimeShared2.reset();                                                         // Reset the pointer, destroys the object: MyTime destructor is called
    }                                                                                    // Or destory the object after of myTimeShared2 when quitting the block

    /*** 4. timeFactoryShared() call: ***/
    {
        auto newSharedPtr = timeFactoryShared(10, 30);                                  // Pointer is copied from the timeFactoryShared(), the local pointer is destroyed after, so newSharedPtr points uniquely to the object actually
        cout << "newSharedPtr.useCount() = " << newSharedPtr.use_count() << endl;       // Here it has exclusive ownership

        auto newUniquePtr = timeFactoryUnique(20, 30);                                  // This creates unique object, compiler allows to return temporary unique_ptr here and assign by Move Semantics
        timeFactoryUnique(20, 30);                                                      // Here, since the pointer is not moved to another, an object is deleted immediately (just an example for understanding)
    }

    return 0;
}

// Factory returns a shared_ptr pointing to a dynamically allocated object
std::shared_ptr<MyTime> timeFactoryShared(int hours, int minutes)
{
    // shared_ptr will take care of deleting this memory
    return std::make_shared<MyTime>(hours, minutes);
    // Note: above is the same as below (?)
    // return std::shared_ptr<MyTime>(new MyTime(hours, minutes));
}

// Factory returns a unique_ptr pointing to a dynamically allocated object
std::unique_ptr<MyTime> timeFactoryUnique(int hours, int minutes)
{
    // unique_ptr will take care of deleting this memory
    return std::make_unique<MyTime>(hours, minutes);
    // return std::unique_ptr<MyTime>(new MyTime(hours, minutes));
}