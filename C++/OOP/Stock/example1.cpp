#include <iostream>
#include "stock.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Stock object1 = Stock("Fujitsu", 10, 2.5);
    const Stock object2;

    object1.show();
    object2.show();

    {
        Stock object3;  //Constructor is called for object3
        Stock object4{"Lane", 5, 12};
        Stock object5 = Stock{"Test", 5, 7};
    }   // Destructor is called for object3, 4

    return 0;
}
