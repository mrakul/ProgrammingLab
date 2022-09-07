// callable.cpp -- callable types and templates
#include "somedefs.h"
#include <iostream>
#include <functional>

double dubValue(double x) { return 2.0 * x; }
double square(double x) { return x * x; }

/*** Section below is just for testing to pass rand() function to another functions ***/
const int MIN_NUM = 0;                      // Define limits
const int MAX_NUM = 100;
//Takes any random function as input to pass to generate() function
int randomCustomized(int (*randFuncToUse)()){
    return (MIN_NUM + randFuncToUse() % (MAX_NUM - MIN_NUM + 1));
}

int randomCustomized2(std::function<int(void)> randFuncToUse){
    return (MIN_NUM + randFuncToUse() % (MAX_NUM - MIN_NUM + 1));
}
/*************************************************************************************/

int main(int argc, char const *argv[])
{
    using std::cout;
    using std::endl;
    double y = 4.0;
    // 1. Without using a std::function wrapper
    //Use functions: the two below has one instantiation, so the total number of instantiations is 5 (two for objects and two for lambdas)
    cout << "Function pointer dubValue:" << endl;
    cout << " " << useFunction(y, dubValue) << endl;
    cout << "Function pointer square:" << endl;
    cout << " " << useFunction(y, square) << endl;

    // Use functors
    cout << "Function object FunctorMultiply:" << endl;
    cout << " " << useFunction(y, FunctorMultiply(5.0)) << endl;
    cout << "Function object FunctorAdd:" << endl;
    cout << " " << useFunction(y, FunctorAdd(5.0)) << endl;

    // Use lambdas
    cout << "Lambda expression 1:" << endl;
    cout << " " << useFunction(y, [](double u) {return u * u;}) << endl;
    cout << "Lambda expression 2:" << endl;
    cout << " " << useFunction(y, [](double u) {return u + u / 2.0;}) << endl;

    // 2. Using std::function wrapper to unify calls: as a result, only one instantiation of a function is created
    std::function<double(double)> dblDblFunction[6];
    dblDblFunction[0] = dubValue;
    dblDblFunction[1] = square;
    dblDblFunction[2] = FunctorMultiply(5.0);   //Creating an object?
    dblDblFunction[3] = FunctorAdd(5.0);
    dblDblFunction[4] = [](double u) {return u * u;};
    dblDblFunction[5] = [](double u) {return u + u / 2.0;};

    //Or not create 6 objects, and create a temporary object for the call, preliminary defining a type:
    typedef std::function<double(double)> fnDblDblTypeDef;                   // Specify a type
    using fnDblDblTypeDef2 = std::function<double(double)>;                  // Or in this form

    //Now there is one instantiation used, counter showing 6 calls of one instantiation
    cout << "Function pointer dubValue:" << endl;
    cout << " " << useFunction(y, fnDblDblTypeDef(dubValue)) << endl;        //Use temporary object instead of dblDblFunction[0]
    cout << "Function pointer square:" << endl;
    cout << " " << useFunction(y, fnDblDblTypeDef2(square)) << endl;

    cout << "Function object FunctorMultiply:" << endl;
    cout << " " << useFunction(y, dblDblFunction[2]) << endl;
    cout << "Function object FunctorAdd:" << endl;
    cout << " " << useFunction(y, dblDblFunction[3]) << endl;

    cout << "Lambda expression 1:" << endl;
    cout << " " << useFunction(y, dblDblFunction[4]) << endl;
    cout << "Lambda expression 2:" << endl;
    cout << " " << useFunction(y, dblDblFunction[5]) << endl;

    return 0;
}