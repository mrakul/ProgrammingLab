#include <memory>
#include <string>
#include "..\OOP\MyTime (OpOverload)\MyTime.h"

int main(int argc, char const *argv[])
{
    using std::auto_ptr;
    using std::unique_ptr;
    using std::shared_ptr;
    using std::string;

    //1. New string auto_ptr (auto is deprecated now)
    //auto_ptr<string> ptrString {new string};    //or auto_ptr<string>(new string);
    //2. New double unique_ptr
    unique_ptr<double> ptrDbl = unique_ptr<double>(new double);
    //3. New MyTime obj shared_ptr (NOT THE BEST SOLUTION TO INITIALIZE :) )
    shared_ptr<MyTime> myTimeObj;
    myTimeObj = *(new shared_ptr<MyTime>);

    return 0;
}
