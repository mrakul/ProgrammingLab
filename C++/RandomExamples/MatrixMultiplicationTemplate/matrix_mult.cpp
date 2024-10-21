#include <iostream>
using namespace std;

template <uint N, uint M>
struct Matrix
{
    double matrix[N][M];

};

template <uint N, uint M>
void printMatrix(const Matrix<N, M> &matrixToPrint)
{
    for (uint i = 0; i < N; i++)
    {
        for (uint j = 0; j < M; j++)
            cout << matrixToPrint.matrix[i][j] << " ";
        cout << endl;
    }
}

template <uint A_ROWS, uint A_COLUMNS, uint B_COLUMNS>
void multiplyMatrixes(const Matrix<A_ROWS, A_COLUMNS> &A, const Matrix<A_COLUMNS, B_COLUMNS> &B, Matrix<A_ROWS, B_COLUMNS> &C)
{
    for (uint i = 0; i < A_ROWS; i++)
        for (uint j = 0; j < B_COLUMNS; j++)
            for (uint k = 0; k < A_COLUMNS; k++)
                C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
}

// TODO:
// template <uint A_ROWS, uint A_COLUMNS, uint B_ROWS, uint B_COLUMNS>
// void multiplyMatrixesShift {

// }

int main(int argc, char const *argv[])
{
    // 1. Usual matrix multiplication: num of A columns is equal to num of B rows
    constexpr Matrix<2, 4> A = {1, 1, 2, 2,         // Make it constexpr (!)
                                1, 1, 2, 2};


    // (!) Possible due to Move-assignment operator "constexpr Matrix<2U, 4U> &Matrix<2U, 4U>::operator=(Matrix<2U, 4U> &&)"
    // A = {1, 1, 2, 2,
    //      1, 1, 2, 2};
    printMatrix(A);

    // A = {3, 4, 5, 6,
    //      7, 8, 9, 10};
    // printMatrix(A);

    Matrix<4, 4> B = {0, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 1, 1, 0,
                      0, 0, 1, 1};

    Matrix<2, 4> C;
    printMatrix(C);

    multiplyMatrixes(A, B, C);
    printMatrix(C);

    // 2. Multiplication with shift: num of A columns is not equal to num of B rows
    Matrix<1, 14> A2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    Matrix<3, 32> B2 = {
                            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                        };

    printMatrix(A2);
    printMatrix(B2);

    cout << "\n";

    return EXIT_SUCCESS;
}