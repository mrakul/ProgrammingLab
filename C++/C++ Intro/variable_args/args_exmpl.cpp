#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;

template <typename Type>                                  // Template for single argument to stop the recursionю
void oneArgOut(const Type& funcVariable)
{
    cout << __PRETTY_FUNCTION__ << "Current value is: " << funcVariable << endl;
}

void funcOut(){cout << "\t### Terminating funcOut() ###";}                                       //Or the solution is to have termination function for zero arguments


template<typename Type, typename... Args>                // (!) Note that typename... is also specifies that types are different
void funcOut(const Type& firstArg, const Args&... args)  // recursive variadic function for several arguments. Note: the first argument is needed to identify as multiple arguments
{                                                        // "Args is a template parameter pack, and args is a function parameter pack"
    // cout << __PRETTY_FUNCTION__ << endl << "Current value is: " << firstArg << endl;
    oneArgOut(firstArg);
    funcOut(args...);                                    //  Calls the function for the rest of arguments. Finally, the one-argument function funcOut is called (or zero argument, if this implementation chosen)
}

template <class Type>
void initListFunc(initializer_list<Type> argsList)              //Initializer list function (the same type arguments). Note: initializer_list always uses copy semantics, that is no references uses
{
    for (auto curArg : argsList){
        cout << __PRETTY_FUNCTION__ << endl << "Current value is: "<<curArg << endl;
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