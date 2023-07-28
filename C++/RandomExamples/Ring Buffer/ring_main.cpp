#include <iostream>
#include "Ring.h"

const int BUFFER_SIZE = 7;

int main(int argc, char const *argv[])
{
    // 0. Create a Ring buffer of 7 elements
     Ring myRing(BUFFER_SIZE);

    // 1. Fill the buffer fully and print the content. Loop while addItem() returns True
    for (int i = 0; myRing.addItem(i + 1); ++i);
    myRing.printQueue();

    // 2. Take two elements from the buffer and print the content
    int curHead;
    myRing.getItem(curHead);
    myRing.getItem(curHead);
    myRing.printQueue();

    // 3. Try addding more items to the buffer and print the content
    myRing.addItem(10);
    myRing.addItem(11);
    myRing.addItem(12);                                     // No place to save the number
    myRing.printQueue();

    // 4. Remove all the items from the buffer: both head and tail positions are index of 2
    while (myRing.getItem(curHead))
        cout << "Removed item: " << curHead << endl;
    myRing.printQueue();

    // 5. Fill the buffer again and print: observe that both head and tail are still 2
    for (int i = 0; myRing.addItem(i * 10); ++i);
    myRing.printQueue();

    return EXIT_SUCCESS;
}