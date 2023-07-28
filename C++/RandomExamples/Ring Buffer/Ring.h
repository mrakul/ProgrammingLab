#include <new>

using namespace std;

/*** Ring Buffer implementation: behave as FIFO with addItem() and getItem() functions.
 *   The buffer's memory is obtained once during creation.
 *   My implementation.
***/

class Ring
{
private:
    size_t itemsMaxNum;                                                        // Value to set max size of the buffer
    size_t numberOfItems;                                                      // Current number of items in the buffer
    int *queueBuffer;                                                          // Buffer area pointer
    // Use indexes to access items in the buffer
    size_t headPos;                                                               // Head position: position of the first to deque item
    size_t tailPos;                                                               // Tail position: (!) tail is one past the end position. If the buffer is full, head is equal to tail

public:
    // Default Constructor
    Ring(): itemsMaxNum(20), numberOfItems(0), queueBuffer(nullptr), headPos(0), tailPos(0)
    {
        queueBuffer = new (nothrow) int[20];                                   // Obtain default area of 20 items. Need to throw exception or check the pointer, surely
    }

    // Constructor using specified value of the buffer size
    Ring(size_t bufferSize): itemsMaxNum(bufferSize), numberOfItems(0), queueBuffer(nullptr), headPos(0), tailPos(0)
    {
        queueBuffer = new (nothrow) int[itemsMaxNum];                          // Obtain enough memory. Need to throw exception or check the pointer, surely
    }

    // Adding an item function
    bool addItem(size_t numToAdd)                                                 // Use a number to set to a new buffer
    {
        // Note: there can be a solution to compare headPos and tailPos to understand if there is free space to add items or there is no items in the buffer (for example, headPos + 1 == tailPos)
        if (numberOfItems == itemsMaxNum)                                      // If number of items reached max buffer size
            return false;                                                      // Return False
        else {                                                                  // There is a space in the buffer to add an item
             queueBuffer[tailPos] = numToAdd;                                   // Set the value at the current tail position
             tailPos++;                                                         // Move the tail forward

            if (tailPos == itemsMaxNum)                                        // If tail position is out of range (after the buffer area)
                tailPos = 0;                                                   // Set the tail pointing to the beginning of the buffer area

            numberOfItems++;                                                   // Increment the number of items after making all the action of adding

            return true;                                                       // Added successfully
        }
    }

    // Getting an item function
    bool getItem(int &gotNum)                                                  // Pass an item by reference to return the number
    {
        if (numberOfItems == 0)                                                // If there are no items in the buffer
            return false;                                                      // Return False
        else{                                                                  // There are items in the buffer
            gotNum = queueBuffer[headPos];                                     // Got the item and move the head position
            headPos++;                                                         // Move head forward

            if (headPos == itemsMaxNum)                                        // If head position is out of range (after the buffer area)
                headPos = 0;                                                   // Set the head pointing to the beginning of the buffer area

            numberOfItems--;                                                   // Decrement the number of items after making all the action of removing

            return true;                                                       // Item got successfully
        }
    }

    // printQueue() is a debug function to print out the items from [headPos; tailPos) range
    void printQueue()
    {
        // Print info header
        cout << "\nHead Position: " << headPos << endl
             << "Tail Position: " << tailPos << endl
             << "Number of elements in the buffer: " << numberOfItems << endl;

        cout << "Buffer's content: " << endl;
        // Print content itself: use the Until loop since head can be equal to tail if max number is reached
        size_t curPos = headPos;                                                  // Start from the head
        if (numberOfItems > 0){                                                // To prevent moving through the cycle
            do {                                                                // Until current reaches the tail
                cout << queueBuffer[curPos] << " <- ";                         // Print the item
                ++curPos;                                                      // Move current forward

                if (curPos == itemsMaxNum)                                     // The same approach: if beyond the buffer
                    curPos = 0;                                                // Move position at the beginning
            } while (curPos != tailPos);                                       // Until the current reaches the tail

            cout.put('\n');
        }
    }

    //Destructor
    ~Ring()
    {
        delete[] queueBuffer;                                                  // Release the area and destroy elements
    }
};