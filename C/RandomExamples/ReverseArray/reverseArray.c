#include <stdio.h>

void reverseArray(int array[], int num){
;
}

void printArr(int array[], int num){
    for(int i = 0; i < num; i++){
        printf("%d: %d\n", i, array[i]);
    }
}

void reverseArr(int array[], int num){
    int temp = 0;
    for(int i = 0; i < num/2; i++){
        temp = array[i];
        array[i] =  array[num - i - 1];
        array[num - i - 1] = temp;
    }
}

int main(int argc, const char *argv[]){
    int array[] = {1, 2, 3, 4, 5, 6};
    printArr(array, sizeof(array)/sizeof(*array));
    reverseArr(array, sizeof(array)/sizeof(*array));
    printArr(array, sizeof(array)/sizeof(*array));

    return 0;
}