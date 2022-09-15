#include "doublyLinkedList.h"
#include "person.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "\t ### Inner block: enter ###" << endl;
    {
        /*** 0. Creating persons to push then to the Stack ***/
        Person personOne;                                // Default constructor: ID = 0
        Person personTwo = Person{"Cringe", "Famous"};   // (string, string): ID = 1
        Person personThree = personTwo;                  // Copy constructor of Person class: ID = 2

        LinkedList<Person> myList;

        /* 1. AddToHead() method */
        myList.insertToHead(personOne);
        myList.insertToHead(personTwo);
        myList.insertToHead(personThree);

        // Print the list nodes data in both directions
        myList.printInForwardDirection();
        myList.printInReverseDirection();

        //while (myList.insertToTail(Person({"Cycle", "Person"})));
        int indexToInsert = 0;
        myList.insertByIndex(indexToInsert, Person{"Added to:", std::to_string(indexToInsert) + " index"});
        indexToInsert = 3;
        myList.insertByIndex(indexToInsert, Person{"Added to:", std::to_string(indexToInsert) + " index"});
        indexToInsert = 2;
        myList.insertByIndex(indexToInsert, Person{"Added to:", std::to_string(indexToInsert) + " index"});
        indexToInsert = 10;
        myList.insertByIndex(indexToInsert, Person{"Added to:", std::to_string(indexToInsert) + " index"});

        // Print the list nodes data in both directions
        myList.printInForwardDirection();
        myList.printInReverseDirection();

    cout << "\t ### Inner block: exit ###" << endl;
    }

    return 0;
}
