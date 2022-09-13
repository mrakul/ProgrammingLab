#include "stack.h"
#include "person.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "\t ### Inner block: enter ###" << endl;
    {
        /*** 1. Creating persons to push then to the Stack ***/
        Person personOne;                                // Default constructor: ID = 0
        Person personTwo = Person{"Cringe", "Famous"};   // (string, string): ID = 1
        Person personThree = personTwo;                  // Copy constructor of Person class: ID = 2

        Stack<Person> myStack;

        myStack.push(personOne);
        myStack.push(personTwo);
        myStack.push(personThree);
        myStack.push(Person{"PersonToAdd", "TempCreated"});     // Push temporary object, use copy constructor in push to initialize dynamic memory obtained and then destroy the temporary object

    cout << "\t ### Inner block: exit ###" << endl;
    }

    return 0;
}
