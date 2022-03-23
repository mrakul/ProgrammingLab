#include <iostream>

using namespace std;

const int &returnBack (const int &num);

void test (char &);

int main(int argc, char const *argv[])
{
    int value{}, value2 {500};

    value = returnBack(value2);
    cout << "Value1: " << value << " Value2 : " << value2 << endl;

    //returnBack(value2) = 390; //return type should be non-const, therefore passed &int should be non-const (to not convert non-const to returned const)
    cout << "Value1: " << value << " Value2 : " << value2 <<endl;
    //test('Z');    //prohibited: 1. 'Z' is a const; 2. Argument must be modifiable lvalue

    return 0;
}

const int &returnBack (const int &num){
    return num;
}

void test (char & ch){
    ch = 'A';
}