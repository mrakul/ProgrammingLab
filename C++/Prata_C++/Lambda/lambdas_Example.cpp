#include <vector>
#include <iostream>
#include <functional>

using namespace std;

//Make two predicates (takes one argument and returns bool):
bool divBy3(int x) { return !(x % 3); }           //The same as x % 3 == 0;
bool divBy13(int x) { return x % 13 == 0; }

template <typename Type>
class Divisible
{
private:
    Type divider;
public:
    Divisible() : divider(1) {}
    Divisible(const Type &divSet) : divider(divSet) {}

    Divisible(const Divisible<Type> &copiedObj)
    {
        this->divider = copiedObj.divider;           //Actually, as default is doing
    }

    //Try move semantics constructor
    Divisible(Divisible<Type> &&movedObj)
    {
        swap(this->divider, movedObj.divider);
        //this->divider = movedObj.divider;
        //movedObj.divider = 0;                   //reset the source oject's value (not critical)
    }

    //Copy assignment operator
    Divisible<Type> &operator=(const Divisible<Type> &movedObj)
    {
        this->divider = movedObj.divider;
        return *this;
    }

    //Move assignment operator
    Divisible<Type> &operator=(Divisible<Type> &&movedObj)
    {
        swap(this->divider, movedObj.divider);
        return *this;
    }

    bool operator()(const Type &curValue)
    {
        return !(curValue % divider);
    }

    ~Divisible()
    {
        //cout << "Destructor is called" << endl;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> numVect(1000, 0);
    srand(time(0));                                     // To have different sequence of random numbers
    generate(numVect.begin(), numVect.end(), rand);     // rand is a generator - the function with no arguments. (!) rand should be used without (). No difference to use & or not before the name
    cout << endl;

    /*** 1.  Count divisible numbers using functions ***/
    cout << "Divisible by three count, function: " << count_if(numVect.begin(), numVect.end(), divBy3) << endl;
    cout << "Divisible by thirteen count, function: " << count_if(numVect.begin(), numVect.end(), divBy13) << endl;

    /*** 2.  Count divisible numbers using functor ***/
    Divisible<int> divFunctor(3);
    cout << "Divisible by three count, functor: " << count_if(numVect.begin(), numVect.end(), divFunctor) << endl;
    Divisible<int> divFunctor2(move(Divisible<int>(10)));       //Call the move constructor! (without move the copy constructor is not called, I suppose that the compiler optimization works as for Useless example)
    divFunctor2 = divFunctor;                                   //This calls the copy assignment operator
    divFunctor2 = Divisible<int>(13);                           //This calls the move assignment operator

    cout << "Divisible by three count, functor: " << count_if(numVect.begin(), numVect.end(), divFunctor) << endl;
    //Note: may be used temporary object:
    cout << "Divisible by thirteen count, functor (temp object): " << count_if(numVect.begin(), numVect.end(), Divisible<int>(13)) << endl;

    /*** 3. Count divisible using lambdas ***/
    cout << "Divisible by three count, lambda: " << count_if(numVect.begin(), numVect.end(), [](int curNum) {return !(curNum % 3);}) << endl;
    auto mod13 = [](int curNum) {return !(curNum % 13);};              // mod13 is a name for the lambda. No return type explicitly needed when there is only return statement.

    // Otherwise, need to specify explicitly trailing return type:
    cout << "Divisible by thirteen count, lambda: " << count_if(numVect.begin(), numVect.end(), mod13) << endl;

    // lambda can use any automatic variable in scope, for example: [](double x)->double{int y = x; return x – y;}
    // [&] - access to all automatic variables in scope by reference, [=] - access by value
    int count13 = 0;    //may create two variables and use by lambda
    std::for_each(numVect.begin(), numVect.end(), [&count13](int x) {count13 += x % 13 == 0;});     // works as -> count13 += ((x % 13) == 0). If true, count13 incremented by 1 (true converted to 1)
    cout << "Divisible by thirteen count, lambda and 'external' variable: " << count13 << endl;


    /* cout << "Zero ", divBy3(0) ? (cout << "True ") : (cout << "False ");
    cout << "One ", divBy3(1) ? (cout << "True ") : (cout << "False ");
    cout << "Two ", divBy3(2) ? (cout << "True ") : (cout << "False ");
    cout << "Three ", divBy3(3) ? (cout << "True ") : (cout << "False ");
    divBy3(4) ? (cout << "True ") : (cout << "False ");
    divBy3(5) ? (cout << "True ") : (cout << "False ");
    cout << (divBy3(6) ? "True " : "False ") << endl; */

    return 0;
}