#include <memory>
#include <iostream>

using namespace std;


// Forward declaration
class B;

// Make two classes having pointers to each other
class A
{
public:
    shared_ptr<B> m_BPtr;
    A() { std::cout << "A object constructed " << std::endl; }
    ~A() { std::cout << "A object destructed " << std::endl; }
};

class B
{
public:
    shared_ptr<A> m_APtr;
    B() { std::cout << "B object constructed " << std::endl; }
    ~B() { std::cout << "B object destructed " << std::endl; }
};

// Modify classes to make one class having ownership on another
class BAux;
class AMain
{
public:
    shared_ptr<BAux> m_BPtr;
    AMain() { std::cout << "AMain object constructed " << std::endl; }
    ~AMain() { std::cout << "AMain object destructed " << std::endl; }
};

class BAux
{
public:
    weak_ptr<AMain> m_APtr;
    BAux() { std::cout << "BAux object constructed " << std::endl; }
    ~BAux() { std::cout << "BAux object destructed " << std::endl; }
};

/*** Mainline code ***/
int main(int argc, char const *argv[])
{
    /*** 1. Use shared pointers in the cyclic dependency to demostrate that objects will not be deleted ***/
    {
        shared_ptr<A> objAPtr = make_shared<A>();     // +1 A: create new A and point separate pointer to it
        objAPtr->m_BPtr = make_shared<B>();           // +1 B: create new B and point from object A to it
        objAPtr->m_BPtr->m_APtr = objAPtr;            // +1 A: point from B to A
        // 2 pointers ==> A
        // 1 pointer  ==> B

        /* As a result: objAPtr is destroyed, counter to A is decremented.
        * A's and B's reference counters both remains 1
        * Objects are not destroyed => memory leak */
    }

    /*** 2. Use weak_ptr in the subsidiary object of BAux ***/
    weak_ptr<AMain> weakAMain_ptr;                               // Create in the outer block to check existence of an object within and out of the block
    {
        shared_ptr<AMain> objAMainPtr = make_shared<AMain>();    // +1 A: create new A and point separate pointer to it
        objAMainPtr->m_BPtr = make_shared<BAux>();               // +1 B: create new B and point from object A to it
        objAMainPtr->m_BPtr->m_APtr = objAMainPtr;               // +0 : B doesn't lead to increment reference counter to A
        // 1 pointer ==> A
        // 1 pointer  ==> B

        /* As a result: objAPtr is destroyed, counter to A is decremented.
        * A reference counter reaches 0, so A object is destroyed.
        * Subsequently, pointer to B is destroyed within A, and B's counter reaches 0.
        * Both objects are destroyed. */

        // Assign sharedPtr to weakPtr (bind weakPtr to the shared Obj) and check existence of an object
        weakAMain_ptr = objAMainPtr;

        cout << "\t ### Inner block check ###" << endl;
        if (shared_ptr<AMain> sharedAMainPtr = weakAMain_ptr.lock()){                           // Within this block, local shared_ptr is created and is counted by use_count(), that is return 2
            cout << "Object AMain still exists\n" <<
                "AMain shared pointers counter: " << weakAMain_ptr.use_count() << endl;
        }
        else
            cout << "Object AMain already destroyed" << endl;
    }

    // Check existence of an object
    cout << "\t ### Outer block check ###" << endl;
    if (auto sharedAMainPtr = weakAMain_ptr.lock()){                                            // May be used auto: compiler can deducts type
        cout << "Object AMain still exists" <<
            "AMain shared pointers counter: " << weakAMain_ptr.use_count() << endl;
    }
    else
        cout << "Object AMain already destroyed" << endl;

    return 0;
}