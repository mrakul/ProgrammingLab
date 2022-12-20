#include "doublyLinkedList.h"
#include "person.h"
#include <iostream>
#include <string>

using namespace std;

LinkedList<Person> returnListToAppend();                // To check the move semantics of appendList method

int main(int argc, char const *argv[])
{
    cout << "\t ### Inner block: enter ###" << endl;
    {
        /*** 0. Creating persons to add then to the Linked LIst ***/
        Person personOne;                                // Default constructor: ID = 0
        Person personTwo = Person{"Cringe", "Famous"};   // (string, string): ID = 1, no Copy Constructor
        Person personThree = personTwo;                  // Copy constructor of Person class: ID = 2

        LinkedList<Person> myList;

        /* 1. Inserting methods testing */
        myList.insertToHead(personOne);
        myList.insertToHead(personTwo);
        myList.insertToHead(personThree);

        // Print the list nodes data in both directions
        myList.printInForwardDirection();
        myList.printInReverseDirection();

        /* 1. Inserting functions tests */
        //while (myList.insertToTail(Person({"Cycle", "Person"})));
        int indexToInsert = 0;
        myList.insertByIndex(indexToInsert, Person{"Added to:", std::to_string(indexToInsert) + " index"});             // Temporary object is created, copied by Copy Constructor to the dynamically allocated memory, and temporary is destroyed
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

        /* 2. Searching function test */
        cout << "Finding " << myList.searchItem(Person{"Tail", "Person"}) << " <- found at index " << endl;        // Trying to find the last person's index

        /* 3. Removing functions test */
        auto nodePtr = myList.getNodeByIndex(0);
        cout << "Node to delete: " << myList.getNodeByIndex(0)->nodeData;
        myList.removeFromHead();
        (nodePtr = myList.getNodeByIndex(7)) ? (cout << "Node to delete: " << nodePtr->nodeData) : (cout << "No node for that index\n");
        myList.removeFromTail();
        cout << "Node to delete: " << myList.getNodeByIndex(1)->nodeData;
        myList.removeByIndex(1);
        myList.removeByIndex(1);
        // Remain 3 elements to check the destructor
        myList.printInForwardDirection();
        // myList.removeFromTail();
        // myList.removeFromHead();
        // myList.removeFromTail();

        /* 4. Copy Constructor and Copy Assignment operator checking */
        {
            LinkedList<Person> myList2 = myList;
            myList2.printInForwardDirection();
            myList.removeFromHead();
            myList2 = myList;
        }

        /* 5. Move Constructor and Move Assignment operator checking */
        {
            LinkedList<Person> myList3 = LinkedList<Person>{myList};                           // Just calls the copy constructor
            //LinkedList<Person> myList4 = std::move(LinkedList<Person>(myList3));             // Move Constructor on the temporary created list based on myList3
            LinkedList<Person> myList4 = std::move(myList3);                                   // Move Constructor on myList3

            // Move Assignment
            LinkedList<Person> myList5;                                                        // Creates an empty List
            myList5.insertToHead(Person("myList5 ", "Person"));
            myList5 = std::move(myList4);                                                      // Move Assignment
        }

        /* 6. Append functions checking */
        {
            LinkedList<Person> myList6 = LinkedList<Person>{myList};                           // Just calls the copy constructor
            LinkedList<Person> listToAppend = LinkedList<Person>{myList};                      // The same list
            myList6.printInForwardDirection();                                                 // Print the initial value

            // Append the local list
            myList6.appendList(move(listToAppend));                                            // Append the list
            myList6.printInForwardDirection();                                                 // Print after appending

            // Append the local list
            myList6.appendList(returnListToAppend());                                          // Append the list from the function: move-semantics is used for the temporary object
            myList6.printInForwardDirection();                                                 // Print after appending

            // Append to an empty list
            LinkedList<Person> emptyList;
            emptyList.appendList(returnListToAppend());
            emptyList.printInForwardDirection();

        }

        cout << "\t ### Inner block: exit ###" << endl;
    }                                                                                          // Destroy the rest of the objects

    return 0;
}

LinkedList<Person> returnListToAppend()
{
    LinkedList<Person> listToReturn;
    listToReturn.insertToTail({"Person1", "Inserted"});
    listToReturn.insertToTail({"Person2", "Inserted"});

    return listToReturn;
}