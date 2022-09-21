//This example is to demonstrate Template Argument Deduction
#include <iostream>

using namespace std;

template <typename F, typename T1, typename T2>
void funcToDemonstrate(F func, T1 t1, T2 t2)
{
    func(t1, t2);               //t2 is a type int, and fOut() in turn works with reference to t2 (t2 is a copy if num)
}

//      A function parameter that is an rvalue reference to a template type parameter
// (i.e., T&&) preserves the constness and lvalue/rvalue property of its corresponding argument.
template <typename F, typename T1, typename T2>
void funcToDemonstrate2(F func, T1 &&t1, T2 &&t2)
{
    func(t1, t2);              //(!!!) t1 has type T1&&, since 42 is passed as int&& and formal parameter is T1&&
}                           //      t2 has type T2&, since num is passed
//      The first exception affects how type deduction is done for rvalue reference parameters.
// When we pass an lvalue(e.g., i) to a function parameter that is an rvalue
// reference to a template type parameter(e.g, T &&), the compiler deduces the template
// type parameter as the argument’s lvalue reference type. So, when we call
// (!!!) f3(i), the compiler deduces the type of T as int &, not int.
//      Deducing T as int &would seem to mean that f3’s function parameter would
// be an rvalue reference to the type int &.Ordinarily, we cannot(directly) define a
// reference to a reference(§ 2.3.1, p. 51).However, it is possible to do so indirectly
// through a type alias(§ 2.5.1, p. 67) or through a template type parameter.
// In such contexts, we see the second exception to the normal binding rules : If
// we indirectly create a reference to a reference, then those references “collapse.” In
// all but one case, the references collapse to form an ordinary lvalue reference type.
//      The new standard, expanded the collapsing rules to include rvalue references.References
// collapse to form an rvalue reference only in the specific case of an rvalue
// reference to an rvalue reference.That is, for a given type X :
// • X & &, X & &&, and X & && all collapse to type X &
// • The type X && &&collapses to X &&

template <typename F, typename T1, typename T2>
void funcToDemonstrate3(F func, T1 &&t1, T2 &&t2)
{
    func(std::forward<T1>(t1), std::forward<T2>(t2));              //(!!!) t1 has type T1&&, since 42 is passed as int&& and formal parameter is T1&&. Note: t2 works without forward<> since it is passed as lvalue reference, and val2 of the fOu2() is the lvalue reference
}
//(!!!)If we call funcToDemonstrate3(fOut2, 42, num), num will be passed to fOut2 as an int& and 42 will be passed as an int&&.

// This template works fine until we want to use it to call a function that has a reference parameter:
void fOut(int val1, int &val2)             // note val2 is a reference
{
    cout << val1 << " " << ++val2 << endl;
}
// Here fOut changes the value of the argument bound to val2. However, if we call fOut
// through funcToDemonstrate, the changes made by fOut do not affect the original argument

void fOut2(int &&val1, int &val2)           //Use rvalue reference and lvalue reference types
{
    cout << val1 << " " << val2 << endl;
}


int main(int argc, char const *argv[])
{
    // const int NUM = 42;                  // May be used instead of 42 (but will be treated as lvalue link?)
    int num{500};
    fOut(42, num);                          // fOut copies 42 to print and changes num by 1

    // 1. No change num, but wanted
    funcToDemonstrate(fOut, 42, num);       // fOut called through funcToDemonstrate and leaves num unchanged (but print out 502 of t2)

    // 2. Solve one half of a problem: num is changed. But cannot be used to call a function that has an rvalue reference parameter.
    funcToDemonstrate2(fOut, 42, num);       // fOut called through funcToDemonstrate2 and changes the num, since t2 type is T2&, and fOut works with num

    // 2.1 Call to fOut2
    //what is passed to fOut2() will be the parameter named t1 inside funcToDemonstrate2.
    // A function parameter, like any other variable, is an lvalue expression (§ 13.6.1, p. 533).
    // As a result, the call to fOut2() in funcToDemonstrate2() passes an lvalue to fOut2’s rvalue reference parameter.
    //(!) So, with the call of fOut2 we can't bind rvalue reference to lvalue int
    // funcToDemonstrate2(fOut2, 42, num);           // error, fOut2 call: "cannot bind rvalue reference of type 'int&&' to lvalue of type 'int'"
                                                     // The reason in the first parameter of fOut2(int &&val1, int &val2):
                                                     // in funcToDemonstrate(int &&t1, ...) t1 is passed as rval ref, but after in fOut() rval reference expression goes to lvalue, but rvalue is expected.
                                                     // forward<T1>(t1) in funcToDemonstrate3() solves this preserving reference type
    funcToDemonstrate3(fOut2, 42, num);

    // Explanation:
    // Above call doesn't work since we cannot bind an rvalue reference to a variable defined as an rvalue reference type:
    // Like any other expression, a variable expression has the lvalue/rvalue property. Variable expressions are lvalues (!!!)
    int &&rvalRef = 42;         // ok: literals are rvalues
    //int &&rvalRefToRef = rvalRef;             // (!!!) error: the expression rvalRef is an lvalue, we can't bind rvalue reference to variable expression, which is lvalue
    int &&rvalRefToRef = move(rvalRef);         // WORKS!
    cout << rvalRefToRef << endl;               // Make compiler happy

    // Example with lvalue how it works: we may specify lvalue reference to lvalue reference (but actually, finally they both serve to referent object)
    const int &lvalRef = num;
    cout << &lvalRef << endl;
    const int &lvalRefToRef = lvalRef;          // Works OK, since lvalRefToRef is a refernce to lvalue, and lvalRef is a variable expression
    cout << &lvalRefToRef << endl;

    return 0;
}