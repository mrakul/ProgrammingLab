#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


void initializeStack(Stack_T * stackPtr){
    stackPtr->stackHead = NULL;      //points to nowhere
    stackPtr->numOfElem = 0;          //no elements at all
}

/* Gets a new disk memory and initialize it     */
/* INPUT: int diameter - diameter of the new disk */
Disk_T * getNewDisk(int diameter){
    Disk_T *newDisk = malloc(sizeof(Disk_T));
    if (newDisk){
        newDisk->diameter = diameter;
        newDisk->prevDisk = NULL;
    }
    return newDisk;
}

void pushToStack(Stack_T * stackPtr, Disk_T *addedDisk){
    if (stackPtr->stackHead)                          //may be made unconditional: if stackHead == NULL, addedDisk->prevDisk will be set to NULL;
        addedDisk->prevDisk = stackPtr->stackHead;
    stackPtr->stackHead = addedDisk;
}

Disk_T *popFromStack(Stack_T *stackPtr){
    Disk_T *poppedDisk = NULL;
    if(stackPtr->stackHead != NULL){
        poppedDisk = stackPtr->stackHead;   //return address of the current head
        stackPtr->stackHead = poppedDisk->prevDisk;     //point stack to the disk below
        poppedDisk->prevDisk = NULL;        //Disconnect disk from the disk below (optionallyB)
    }

    return poppedDisk;   //return value of the pointer (by value)
}

void printStack(Stack_T *stackPtr){
    Disk_T *currentDisk = NULL;

    for(currentDisk = stackPtr->stackHead; currentDisk != NULL; currentDisk = currentDisk->prevDisk){
        printf("Diameter of the disk is: %d\n", currentDisk->diameter);
    }
    putchar('\n');
}

int populateStack(Stack_T *stackPtr, int maxDiskDiam){
    Disk_T *addedDisk;      //is a pointer to the added disk
    bool notGot = false;
    while (maxDiskDiam > 0 && !notGot){
        addedDisk = getNewDisk(maxDiskDiam);
        if (addedDisk){
            pushToStack(stackPtr, addedDisk);  //pass the stack address and the new disk address (pass the pointer by value)
            maxDiskDiam--;
        }
        else
            notGot = true;
    }
    return (notGot ? true : false);     //if some disk not added, return 1 (error), otherwise - return 0
}