// Placement new demostration
#include <iostream>
#include <string>
#include <new>

using namespace std;

const int BUF_SIZE = 512;

class TestingClass
{
private:
    string mWords;
    int mNumber;
public:
    TestingClass(const string &strToConstruct = "Testing Class default object", int numToConstruct = 0)
    {
        mWords = strToConstruct; mNumber = numToConstruct; cout << mWords << " constructed\n";
    }

    ~TestingClass() { cout << mWords << " destroyed\n"; }

    void Show() const { cout << mWords << ", " << mNumber << endl; }
};

/*** Mainline code ***/

int main(int argc, char const *argv[])
{
    char *bufPtr = new char[BUF_SIZE];                              // Allocate a block of memory
    TestingClass *ptrObj1, *ptrObj2;

    ptrObj1 = new (bufPtr) TestingClass;                            // (!!!) Placement new: place a new object at the butPtr location, but it doesn't allocate a new memory
    ptrObj2 = new TestingClass("Heap object1", 20);                 // Place object on heap
    cout << "Memory block addresses:\n" <<
        "bufPtr: " << (void *)bufPtr <<
        " Object1 on heap address: " << ptrObj2 << endl;

    cout << "Memory contents:\n";
    cout << ptrObj1 << ": ";
    ptrObj1->Show();
    cout << ptrObj2 << ": ";
    ptrObj2->Show();

    //Create two more classes
    TestingClass *ptrObj3, *ptrObj4;
    // Place the 3-rd object right after the first object
    ptrObj3 = new (bufPtr + sizeof(TestingClass)) TestingClass("Buffer object2", 6);
    ptrObj4 = new TestingClass("Heap2", 10);

    cout << "Memory contents:\n";
    cout << ptrObj3 << ": ";
    ptrObj3->Show();
    cout << ptrObj4 << ": ";
    ptrObj4->Show();

    delete ptrObj2;                                                 //Free heap as usual
    delete ptrObj4;                                                 //Free heap as usual

    //(!) Need to explicitly call the destructor for the placed objects
    //delete ptrObj1;                                               //Must not use these deletes, since it releases the memory without
    //delete ptrObj2;

    ptrObj3->~TestingClass();                                       // (!) Call the destructor explicitly: buffer still exists, but the related objects destructors are called
    ptrObj1->~TestingClass();                                       // My note: destructor itself only calls the destructors for the contained objects, not being releasing the memory
    //And after that release the buffer's memory
    delete[] bufPtr;                                                // Release buffer after calling the destructors explicitly

    cout << "Done" << endl;

    return 0;
}