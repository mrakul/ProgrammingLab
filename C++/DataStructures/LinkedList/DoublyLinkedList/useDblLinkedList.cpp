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

        /* 1. Inserting methods testing */
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

        myList.insertToTail(Person{"Tail", "Person"});

        // Print the list nodes data in both directions
        myList.printInForwardDirection();
        //myList.printInReverseDirection();

        auto nodePtr = myList.getNodeByIndex(0);
        myList.removeFromHead();
        nodePtr = myList.getNodeByIndex(7);
        myList.removeFromTail();
        nodePtr = myList.getNodeByIndex(1);
        myList.removeByIndex(1);
        myList.removeByIndex(1);
        myList.removeFromTail();
        myList.removeFromTail();
        // myList.removeFromHead();
        myList.removeFromTail();

        cout << "\t ### Inner block: exit ###" << endl;
    }

    return 0;
}
