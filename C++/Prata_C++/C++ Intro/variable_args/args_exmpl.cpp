#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;

template <typename Type>                                    // Template for single argument to stop the recursion
void oneArgOut(const Type& funcVariable)                    // (+) Need to either call this funcOut() to have one argument call, or another like oneArgOut(), but then need to implement zero-arguments function for funcOut()
{
    cout << __PRETTY_FUNCTION__ << "Current value is: " << funcVariable << endl;
}

void funcOut(){cout << "\t### Terminating LAST funcOut() ###" << endl;}          //Or the solution is to have termination function for zero arguments

//Variadic template to accept variadic number of arguments
template<typename Type, typename... Args>                // (!) Note that typename... is also specifies that types are different
void funcOut(const Type& firstArg, const Args&... args)  // recursive variadic function for several arguments. Note: the first argument is needed to identify as multiple arguments
{                                                        // "Args is a template parameter pack, and args is a function parameter pack"
    // cout << __PRETTY_FUNCTION__ << endl << "Current value is: " << firstArg << endl;
    oneArgOut(firstArg);
    funcOut(args...);                                    //  Calls the function for the rest of arguments. Finally, the one-argument function funcOut is called (or zero argument, if this implementation chosen)
    cout << "Exit from funcOut(...)" << endl;
}


//Initializer list function (the same type arguments). Note: initializer_list always uses copy semantics, that is no references uses
template <class Type>
void initListFunc(initializer_list<Type> argsList)
{
    for (auto curArg : argsList){
        cout << __PRETTY_FUNCTION__ << endl << "Current value is: "<< curArg << endl;
    }
}

int main(int argc, char const *argv[])
{
    cout << endl << "\tFunction calls:" << endl;
    string str1("Hello"), str2("world");

    funcOut(1, 2.5, 'a', str1);

    initListFunc({10, 20, 30, 40});
    initListFunc({str1, str2});

    return EXIT_SUCCESS;
}