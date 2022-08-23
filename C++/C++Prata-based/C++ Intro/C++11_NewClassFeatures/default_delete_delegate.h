#include <string>

class Someclass
{
public:
    Someclass() = default;              // use compiler-generated default constructor
    // disable copy constructor and copy assignment operator:
    Someclass(const Someclass&) = delete;
    Someclass& operator=(const Someclass&) = delete;
    // Prevents copy, for example:
    // Someclass one;
    // Someclass two;
    // Someclass three(one); // not allowed, one an lvalue
    // Someclass four(one + two); // allowed, expression is an rvalue

    // use compiler-generated move constructor and move assignment operator:
    Someclass(Someclass&&) = default;
    Someclass& operator=(Someclass&&) = default;
    Someclass& operator+(const Someclass&) const;


    void redo(double);
    void redo(int) = delete;
    // For example:
    // Someclass sclass;
    // sclass.redo(5);        //without void redo(int) = delete, int will be promoted to double. Otherwise, will be prohibited.
};

//Delegating constructors
class Notes
{
    int k;
    double x;
    std::string st;
public:
    Notes();
    Notes(int);
    Notes(int, double);
    Notes(int, double, std::string);
};
Notes::Notes(int kk, double xx, std::string stt) : k(kk), x(xx), st(stt) {/*do stuff*/}
Notes::Notes() : Notes(0, 0.01, "Oh") {/* do other stuff*/ }                                //Default constructor uses the first constructor's code
Notes::Notes(int kk) : Notes(kk, 0.01, "Ah") {/* do yet other stuff*/ }
Notes::Notes(int kk, double xx) : Notes(kk, xx, "Uh") {/* ditto*/ }