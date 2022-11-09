#include <stdio.h>

#define SIZE1 10
#define SIZE2 10

int main(int argc, char const *argv[])
{
    int myMatrix[SIZE1][SIZE2];

    for (int i = 0; i < SIZE1; i++)
        for (int j = 0; j < SIZE2; j++)
            myMatrix[i][j] = (i - j) * 4;

    for (int i = 0; i < SIZE1; i++){
        for (int j = 0; j < SIZE2; j++)
            printf("%d ", myMatrix[i][j]);
        printf("\n");
    }

    return 0;

}