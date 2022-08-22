// somedefs.h
#include <iostream>
template <typename Type, typename F>

//f() - is a function of v?
Type useFunction(Type v, F f)
{
    static int count = 0;
    count++;
    std::cout << " useFunction objects count = " << count
        << ", &count = " << &count << std::endl;
    return f(v);
}

//Functor object
class FunctorMultiply
{
private:
    double z_;
public:
    FunctorMultiply(double z = 1.0) : z_(z) {}
    double operator()(double p) { return z_ * p; }
};

//Another one functor (another function)
class FunctorAdd
{
private:
    double z_;
public:
    FunctorAdd(double z = 1.0) : z_(z) {}
    double operator()(double q) { return z_ + q; }
};