#include <iostream>
using namespace std;

struct TestRef
{
    int &reference;
    int ten;
    TestRef(int &ref) : reference(ref) {}
};

int main(int argc, const char *argv[])
{
    int ten = 10;
    int eleven = 11;
    TestRef refObject(ten); // refObject.reference is reference to ten

    cout << refObject.reference << " " << ten << " " << eleven << endl; // Output: 10 10 11

    int64_t *p = (int64_t *)&refObject; // int32_t in 32 bit OS;
    // Note:
    // p is the address of TestRef reference and also the address of the reference refObject.reference
    // *p is the address of ten variable
    //
    // Difficult to understand? refObject.reference indeed a pointer to ten variable
    // *p will return the address inside the memory of refObject.reference
    // that is the address of ten variable
    // this statement is true: *p == &ten
    // ------>
    // now we change the value of *p to the address of eleven
    // then reference.reference will be the reference of eleven instead the reference of ten

    *p = (int64_t)&eleven;          // int32_t in 32 bit OS;

    cout << refObject.reference << " " << ten << " " << eleven << endl; // Output: 11 10 11
    return 0;

}