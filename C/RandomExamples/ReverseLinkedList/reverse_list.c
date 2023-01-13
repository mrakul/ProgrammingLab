#include <stdlib.h>
#include <stdio.h>

typedef struct Item_S {
    int data;
    struct Item_S *nextItem;
} Item;

void reverseList(Item **listHead);
void printList(Item *listHead);
void addItem(int dataToAdd, Item **listHead);

int main(int argc, char const *argv[])
{
    // 0. Create the list head and initialize to NULL
    Item *listHead = NULL;

    // 1. Add items passing address of listHead and print the initial state of the list
    addItem(1, &listHead);
    addItem(2, &listHead);
    addItem(3, &listHead);
    addItem(4, &listHead);
    addItem(5, &listHead);
    addItem(7, &listHead);
    printList(listHead);

    // 2. Reverse the list and print the new state
    reverseList(&listHead);
    printList(listHead);

    return 0;
}

void reverseList(Item **listHead){
    Item *curItem = *listHead;                                           // Start from the head
    Item *prevItem = NULL;                                               // Previous item is alway NULL (what is before the head)
    Item *nextItemToReverse;                                             // To save the next Item following the reversed

    while (curItem){                                                     // While have items to process
        nextItemToReverse = curItem->nextItem;                           // Save the next item to process before reversing the current
        curItem->nextItem = prevItem;                                    // Reverse the current
        prevItem = curItem;                                              // Set the current as the previous
        curItem = nextItemToReverse;                                     // Set the saved next item as the current
    }

    *listHead = prevItem;                                                // Return the last reversed item
}

void addItem(int dataToAdd, Item **listHead){                           // Pass pointer-to-pointer if the listHead is NULL to change it
    Item *curItem = *listHead;

    // If no items yet
    if (!(*listHead)){
        *listHead = malloc(sizeof(Item));
        (*listHead)->data = dataToAdd;
        (*listHead)->nextItem = NULL;
        return;
    }

    // If items exists in the list, find the last one
    while (curItem->nextItem != NULL){
        curItem = curItem->nextItem;
    }

    curItem->nextItem = malloc(sizeof(Item));
    curItem->nextItem->data = dataToAdd;
    curItem->nextItem->nextItem = NULL;
    return;
}

void printList(Item *listHead){
    Item *curItem = listHead;
    printf("Current list values: ");

    while(curItem){
        printf("%d->", curItem->data);
        curItem = curItem->nextItem;
    }
    printf("NULL\n");
}

// I've written this during interview :)

/*

1->2->3->4->5->N

5->4->3->2->1->N

*/

// int *revertList(int *listHead){
//     int *curFirst = listHead;
//     int *curLast = listHead;
//     int *oneBeforeLast;
//     int *tempHead, int *tempTail;


//     int numOfItems;

//     while (curLast != NULL){
//         oneBeforeLast = curLst;
//         curLast = curLast->nextItem;
//         ++numOfItems;
//     }

//     curLast = oneBeforeLast;
//     for (int i = 0; i < (numOfItems / 2); i++){
//         while (curLast != oneBeforeLast){


//             oneBeforeLast = curLast;
//             curLast = curLast->nextItem;
//         }

//     tempHead = curFirst;
//     tempTail = curLast;

//     curLast->nextItem = curFirst;
//     oneBeforeLast->nextItem = NULL;



//     }

//     return XXX;
// }