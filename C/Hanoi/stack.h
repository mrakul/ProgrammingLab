#ifndef STACK_H
#define STACK_
#include <stdbool.h>

/*** Declarations ***/
typedef struct Disk_S{
    int diameter;
    struct Disk_S *prevDisk;
} Disk_T;

typedef struct Stack_S{
    Disk_T *stackHead;
    int numOfElem;
} Stack_T;


/*** Function prototypes ***/
/***
* initializeStack:
* INPUT: pointer to stack
* OUTPUT: void
***/
void initializeStack(Stack_T *stackToInit);

/***
* populate: add maxDiskDiam disks to the stack from masDiskDiam to 1
* INPUT: maxDiskDiam
* RETURN: success = 1, fail = 0
***/

/* Push/Pop from the stack */
void pushToStack(Stack_T *stackPtr, Disk_T *addedDisk);
Disk_T *popFromStack(Stack_T *stackPtr);

Disk_T * getNewDisk(int diameter);

int populateStack(Stack_T * stackPtr, int maxDiskDiam);

/***/
void printStack(Stack_T *stackPtr);

//TODO:
//popFromStack
//free()

#endif