#include <stdio.h>
#include <stdlib.h>

#define SIZE1 10
#define SIZE2 10

typedef struct MyData_S {
    int number;
    char *cringe;
} MyData_T;

struct MyData {
    int number;
    char *cringe;
};

int main(int argc, char const *argv[]){
    int **myMatrix = malloc(SIZE1 * sizeof(int *));

    for (int i = 0; i < SIZE1; i++){                            // Move through the pointers to create underlying vector
        myMatrix[i] = malloc(SIZE2 * sizeof(int));
        for (int j = 0; j < SIZE2; j++){
            myMatrix[i][j] = i + j;
            // *(*(myMatrix + i) + j) = i + j;
        }
    }

    for (int i = 0; i < SIZE1; i++){
        for (int j = 0; j < SIZE2; j++)
            printf("%d ", myMatrix[i][j]);
        printf("\n");
    }

    return 0;
}