#include "doublyLinkedList.h"
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

        LinkedList<Person> myList;

        myList.addToHead(personOne);
        myList.addToHead(personTwo);
        myList.addToHead(personThree);

        // Print the list nodes data in both directions
        myList.printInForwardDirection();
        myList.printInReverseDirection();

    cout << "\t ### Inner block: exit ###" << endl;
    }

    return 0;
}
