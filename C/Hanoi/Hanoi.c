#include <stdio.h>
#include "stack.h"
#define DISKS_TO_ADD 10

/*** Main ***/
int main(int argc, char const *argv[]){
    // Initialize local variables
    bool populateError = false;
    Disk_T *poppedDisk = NULL;

    //Initialize stack
    Stack_T myStack;
    initializeStack(&myStack);

    /* Populate stack */
    populateError = populateStack(&myStack, DISKS_TO_ADD);

    if (populateError)
        printf("Something went wrong! \n");
    else
        printStack(&myStack);

    if((poppedDisk = (popFromStack(&myStack), popFromStack(&myStack), popFromStack(&myStack)))){    //(!!!) pop 3 disks, assign the value of the last to the poppedDisk variable (with no braces, the first value will be assigned)
        printf("Popped disk diameter is: %d \n\n", poppedDisk->diameter);
        printStack(&myStack);
    }

    return 0;
}


