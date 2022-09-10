#include <tuple>
#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    tuple<size_t, size_t, size_t> threeD;                       // All three members set to 0
    tuple<string, vector<double>, int, list<int>>
        someVal("constants", {3.14, 2.718}, 42, {0,1,2,3,4,5});

    //tuple<size_t, size_t, size_t> threeD = {1,2,3};           // Error
    tuple<size_t, size_t, size_t> threeD2{1,2,3};               // OK

    // make_tuple example: ISBN, count, price per book
    auto item = make_tuple("0-999-78345-X", 3, 20.00);         // The type is: tuple<const char*, int, double>.

    // auto book = get<0>(item);                                  // returns the first member of item
    // auto cnt = get<1>(item);                                   // returns the second member of item
    // auto price = get<2>(item) / cnt;                           // returns the last member of item
    get<2>(item) *= 0.8;                                          // apply 20% discount
    get<0>(item) = "Cringe";                                      // Point to another const char *
    cout << get<0>(item)[3];                                      // May be print out, but can't be changed

    // Get the number of elements in a tuple:
    typedef decltype(item) trans;                                 // trans is the type of item
    size_t numOfElem = tuple_size<trans>::value;                  // returns the number of members in object’s of type trans, returns 3
    tuple_element<1, trans>::type cntCopy = get<1>(item);         // cnt has the same type as the second member in item, cnt is an int
    numOfElem++, cntCopy++;                                       // Make compiler happy


    /*** 2. Relational operators ***/
    tuple<string, string> duo("1", "2");
    tuple<size_t, size_t> twoD(1, 2);
    //bool b = (duo == twoD);                                      // error: can’t compare a size_t and a string

    tuple<size_t, size_t, size_t> threeD3(1, 2, 3);
    //bool b = (twoD < threeD);                                    // error: differing number of members
    tuple<size_t, size_t> twoD2(0, 0);
    bool b = (twoD2 < twoD);                                       // ok: b is true
    cout << b;                                                     // Make compiler happy

    return 0;
}
