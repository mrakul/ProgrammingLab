#include <iostream>
using namespace std;
// #pragma pack(push, 1)

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
    // 1. Set refObject.reference be pointint to main's ten
    TestRef refObject(ten);                                                 // refObject.reference is reference to ten
    cout << refObject.reference << " " << ten << " " << eleven << endl;     // Output: 10 10 11

    // 2. Change starting address of the structure to the address of eleven
    int64_t *p = (int64_t *) &refObject;                                    // int32_t in 32 bit OS;
    *p = (int64_t) &eleven;
    // Note:
    // p is the address of TestRef and also the address of the reference refObject.reference
    // *p is the address of ten variable
    //
    // Difficult to understand? refObject.reference indeed a pointer to ten variable
    // *p will return the address inside the memory of refObject.reference
    // that is the address of ten variable
    // this statement is true: *p == &ten
    // ------>
    // now we change the value of *p to the address of eleven
    // then refObject.reference will be the reference of eleven instead the reference of ten

    printf("%zu", sizeof(int));

    cout << refObject.reference << " " << ten << " " << eleven << endl;     // Output: 11 10 11
    printf("Reference %d ", *(*(int**)p));

    return 0;
}
