#include <iostream>

class Action
{
    int a;
public:
    Action(int i = 0) : a(i) {}
    int val() const { return a; };
    virtual void funcOut(char ch) const final { std::cout << val() << ch << std::endl; }       // 'final' specifier -> "virtual function 'virtual void Bingo::f(char) const' overriding final function"
};

class Bingo : public Action
{
public:
    using Action::funcOut;                        //To use the hidden function of the base class if hidden and this is desirable
    Bingo(int i = 0) : Action(i) {}
    virtual void funcOut(char *ch) const //override       // With override secifier, the compiler notifies "member function declared with 'override' does not override a base class member"
        { std::cout << val() << ch << std::endl; }         // 'override' specifier checks the signature existence
};

// Because class Bingo uses funcOut(char* ch) instead of funcOut(char ch), funcOut(char ch) of the Base class is hidden
// to a Bingo object.This prevents a program from using code like the following :
int main(){                              //main() in the header just for example
    Bingo b(10);
    b.funcOut('@');                            // works for Action object, fails for Bingo object if not specify override
}
