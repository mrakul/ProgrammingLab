#include <iostream>
#include "stock.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Stock object1 = Stock("Fujitsu", 10, 2.5);
    const Stock object2;
    Stock object3;
    object1.show();
    object2.show();

    object1 = object1.compare(object2);     //object1 gets the greater value of object1/object2

    {
        Stock object3;  //Constructor is called for object3
        Stock object4{"Lane", 5, 12};
        Stock object5 = Stock{"Test", 5, 7};
        Stock object00{5};  //Use constructor with one parameter and initialization list

    }   // Destructor is called for object6, 5, 4, 3, 00

    return 0;
}
