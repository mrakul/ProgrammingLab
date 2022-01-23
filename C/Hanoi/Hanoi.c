#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


/*** Declarations ***/
typedef struct Disk_S{
    int diameter;
    struct Disk_S *prevDisk;
} Disk_T;

Disk_T *stackHead = NULL;

/*** Function prototypes ***/
Disk_T * getNewDisk(int diameter);
void pushToStack(Disk_T *addedDisk);
void printStack(void);
int populate(int maxDiskDiam);
//TODO:
//popFromStack
//free()

/*** Main ***/
int main(int argc, char const *argv[]){
    bool populated = false;
    /* Populate stack */
    populated = populate(10);

    if (!populated)
        printf("Something went wrong! \n");
    else
        printStack();

    return 0;
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

void pushToStack(Disk_T *addedDisk){
    if (stackHead)                          //may be made unconditional: if stackHead == NULL, addedDisk->prevDisk will be set to NULL;
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
