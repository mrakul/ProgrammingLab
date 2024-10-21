#include <stdio.h>

#define NUM_OF_ROWS 10
#define NUM_OF_COLUMNS 10

/// @brief The procedure prints the matrix.
/// @param matrixToPrint    matrix to print (pointer to the array of NUM_OF_COLUMNS ints)
/// @param numOfRows        number of rows
/// @param numOfColumns     number of columns
void printMatrix(int (* matrixToPrint)[NUM_OF_COLUMNS], int numOfRows, int numOfColumns);
// Note: alternatives for the function declaration, just to remember
// void printMatrix(int matrixToPrint[][NUM_OF_COLUMNS], int numOfColumns, int numOfRows);       // the first dimension is ignored anyway
// void printMatrix(int rows, int cols, int ar[rows][cols]);                                      // This is possible because of C's VLAs addition

/// @brief Transpose the same matrix
void transposeMatrix(int matrixToPrint[][NUM_OF_COLUMNS], int numOfRows, int numOfColumns);

int main(int argc, char const *argv[])
{
    int myMatrix[NUM_OF_ROWS][NUM_OF_COLUMNS];

    // Filling the matrix
    for (int i = 0; i < NUM_OF_ROWS; i++)
        for (int j = 0; j < NUM_OF_COLUMNS; j++)
            myMatrix[i][j] = (i - j) * 4;

    // Print out the matrix
    printMatrix(myMatrix, NUM_OF_ROWS, NUM_OF_COLUMNS);

    // Matrix transpositioning
    transposeMatrix(myMatrix, NUM_OF_ROWS, NUM_OF_COLUMNS);

    // Check the result
    printMatrix(myMatrix, NUM_OF_ROWS, NUM_OF_COLUMNS);

    return 0;

}

void printMatrix(int matrixToPrint[][NUM_OF_COLUMNS], int numOfRows, int numOfColumns)
{
    printf("Printed matrix:\n");
    for (int i = 0; i < numOfRows; i++){
        for (int j = 0; j < numOfColumns; j++)
            printf("%d ", matrixToPrint[i][j]);
        printf("\n");
    }
    putchar('\n');
}

void transposeMatrix(int (* matrixToTrans)[NUM_OF_COLUMNS], int numOfRows, int numOfColumns){
    printf("Matrix transpositioning ...\n");
    for (int i = 0; i < numOfRows; i++)
        for (int j = 0; j < numOfColumns; j++)
            if (j > i) {
                int temp = matrixToTrans[i][j];
                matrixToTrans[i][j] = matrixToTrans[j][i];
                matrixToTrans[j][i] = temp;
            }
}