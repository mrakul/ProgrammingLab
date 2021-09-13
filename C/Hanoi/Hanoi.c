#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct Disk_S{
    int diameter;
    struct Disk_S *prevDisk;
} Disk_T;

Disk_T *stackHead = NULL;


/* Gets the new disk memory and initialize it     */
/* INPUT: int diameter - diameter of the new disk */
Disk_T * getNewDisk(int diameter){
    Disk_T *newDisk = NULL;
    newDisk = malloc(sizeof(Disk_T));
    if (newDisk){
        newDisk->diameter = diameter;
        newDisk->prevDisk = NULL;
    }
    return newDisk;
}

void pushToStack(Disk_T *addedDisk){
    if (stackHead)
        addedDisk->prevDisk = stackHead;
    stackHead = addedDisk;
}

void printStack(void){
    Disk_T *currentDisk = NULL;

    for(currentDisk = stackHead; currentDisk != NULL; currentDisk = currentDisk->prevDisk){
        printf("Diameter of the disk is: %d\n", currentDisk->diameter);
    }
}

int populate(int maxDiskDiam){
    Disk_T *addedDisk;
    bool notGot = false;
    while (maxDiskDiam > 0 && !notGot){
        addedDisk = getNewDisk(maxDiskDiam);
        if (addedDisk){
            pushToStack(addedDisk);
            maxDiskDiam--;
        }
        else
            notGot = true;
    }
    return !notGot;
}

int main(int argc, char const *argv[]){

    bool populated = false;
    /* Populate stack */
    populated = populate(10);

    if (!populated)
        printf("Something went wrong! \n");

    printStack();
    return 0;
}