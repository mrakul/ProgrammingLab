#include <stdio.h>

#define NUM_OF_COLUMNS 10
#define NUM_OF_ROWS 10

/// @brief The procedure prints the matrix.
/// @param matrixToPrint    matrix to print (pointer to the array of NUM_OF_ROWS ints)
/// @param numOfColumns     number of columns
/// @param numOfRows        number of rows
void printTheMatrix(int (* matrixToPrint)[NUM_OF_COLUMNS], int numOfColumns, int numOfRows);
// Note: alternatives for the function declaration, just to remember
// void printTheMatrix(int matrixToPrint[][NUM_OF_COLUMNS], int numOfColumns, int numOfRows);       // the first dimension is ignored anyway
// void printTheMatrix(int rows, int cols, int ar[rows][cols]);                                      // This is possible because of C's VLAs addition

void transpositionTheMatrix(int matrixToPrint[][NUM_OF_COLUMNS], int numOfColumns, int numOfRows);

int main(int argc, char const *argv[])
{
    int myMatrix[NUM_OF_COLUMNS][NUM_OF_ROWS];

    // Filling the matrix
    for (int i = 0; i < NUM_OF_COLUMNS; i++)
        for (int j = 0; j < NUM_OF_ROWS; j++)
            myMatrix[i][j] = (i - j) * 4;

    // Print out the matrix
    printTheMatrix(myMatrix, NUM_OF_COLUMNS, NUM_OF_ROWS);

    // Matrix transpositioning
    transpositionTheMatrix(myMatrix, NUM_OF_COLUMNS, NUM_OF_ROWS);

    // Check the result
    printTheMatrix(myMatrix, NUM_OF_COLUMNS, NUM_OF_ROWS);

    return 0;

}

void printTheMatrix(int matrixToPrint[][NUM_OF_COLUMNS], int numOfColumns, int numOfRows)
{
    printf("Printed matrix:\n");
    for (int i = 0; i < numOfColumns; i++){
        for (int j = 0; j < numOfRows; j++)
            printf("%d ", matrixToPrint[i][j]);
        printf("\n");
    }
    putchar('\n');
}

void transpositionTheMatrix(int (* matrixToTrans)[NUM_OF_COLUMNS], int numOfColumns, int numOfRows){
    printf("Matrix transpositioning ...\n");
    for (int i = 0; i < numOfColumns; i++)
        for (int j = 0; j < numOfRows; j++)
            if (i != j){
                int temp = matrixToTrans[i][j];
                matrixToTrans[i][j] = matrixToTrans[j][i];
                matrixToTrans[j][i] = temp;
            }
}