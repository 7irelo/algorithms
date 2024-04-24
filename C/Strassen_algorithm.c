#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix of size n x n
int **allocateMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)malloc(n * sizeof(int));
    return matrix;
}

// Function to deallocate memory for a matrix
void deallocateMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

// Function to add two matrices of size n x n
void addMatrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices of size n x n
void subtractMatrices(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Function to perform standard matrix multiplication
void standardMatrixMultiplication(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Function to perform Strassen matrix multiplication recursively
void strassenMatrixMultiplication(int **A, int **B, int **C, int n) {
    // Base case: if the matrix size is 1x1, perform simple multiplication
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Allocate memory for submatrices
    int **A11 = allocateMatrix(n/2);
    int **A12 = allocateMatrix(n/2);
    int **A21 = allocateMatrix(n/2);
    int **A22 = allocateMatrix(n/2);
    int **B11 = allocateMatrix(n/2);
    int **B12 = allocateMatrix(n/2);
    int **B21 = allocateMatrix(n/2);
    int **B22 = allocateMatrix(n/2);
    int **C11 = allocateMatrix(n/2);
    int **C12 = allocateMatrix(n/2);
    int **C21 = allocateMatrix(n/2);
    int **C22 = allocateMatrix(n/2);
    int **M1 = allocateMatrix(n/2);
    int **M2 = allocateMatrix(n/2);
    int **M3 = allocateMatrix(n/2);
    int **M4 = allocateMatrix(n/2);
    int **M5 = allocateMatrix(n/2);
    int **M6 = allocateMatrix(n/2);
    int **M7 = allocateMatrix(n/2);
    int **temp1 = allocateMatrix(n/2);
    int **temp2 = allocateMatrix(n/2);

    // Divide matrices A and B into submatrices
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n/2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n/2];
            A21[i][j] = A[i + n/2][j];
            A22[i][j] = A[i + n/2][j + n/2];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + n/2];
            B21[i][j] = B[i + n/2][j];
            B22[i][j] = B[i + n/2][j + n/2];
        }
    }

    // Calculate M1 = (A11 + A22) * (B11 + B22)
    addMatrices(A11, A22, temp1, n/2);
    addMatrices(B11, B22, temp2, n/2);
    strassenMatrixMultiplication(temp1, temp2, M1, n/2);

    // Calculate M2 = (A21 + A22) * B11
    addMatrices(A21, A22, temp1, n/2);
    strassenMatrixMultiplication(temp1, B11, M2, n/2);

    // Calculate M3 = A11 * (B12 - B22)
    subtractMatrices(B12, B22, temp1, n/2);
    strassenMatrixMultiplication(A11, temp1, M3, n/2);

    // Calculate M4 = A22 * (B21 - B11)
    subtractMatrices(B21, B11, temp1, n/2);
    strassenMatrixMultiplication(A22, temp1, M4, n/2);

    // Calculate M5 = (A11 + A12) * B22
    addMatrices(A11, A12, temp1, n/2);
    strassenMatrixMultiplication(temp1, B22, M5, n/2);

    // Calculate M6 = (A21 - A11) * (B11 + B12)
    subtractMatrices(A21, A11, temp1, n/2);
    addMatrices(B11, B12, temp2, n/2);
    strassenMatrixMultiplication(temp1, temp2, M6, n/2);

    // Calculate M7 = (A12 - A22) * (B21 + B22)
    subtractMatrices(A12, A22, temp1, n/2);
    addMatrices(B21, B22, temp2, n/2);
    strassenMatrixMultiplication(temp1, temp2, M7, n/2);

    // Calculate submatrices of the result matrix
    addMatrices(M1, M4, temp1, n/2);
    subtractMatrices(temp1, M5, temp2, n/2);
    addMatrices(temp2, M7, C11, n/2);

    addMatrices(M3, M5, C12, n/2);

    addMatrices(M2, M4, C21, n/2);

    subtractMatrices(M1, M2, temp1, n/2);
    addMatrices(temp1, M3, temp2, n/2);
    addMatrices(temp2, M6, C22, n/2);

    // Combine submatrices into the result matrix
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n/2; j++) {
            C[i][j] = C11[i][j];
            C[i][j + n/2] = C12[i][j];
            C[i + n/2][j] = C21[i][j];
            C[i + n/2][j + n/2] = C22[i][j];
        }
    }

    // Deallocate memory for submatrices
    deallocateMatrix(A11, n/2);
    deallocateMatrix(A12, n/2);
    deallocateMatrix(A21, n/2);
    deallocateMatrix(A22, n/2);
    deallocateMatrix(B11, n/2);
    deallocateMatrix(B12, n/2);
    deallocateMatrix(B21, n/2);
    deallocateMatrix(B22, n/2);
    deallocateMatrix(C11, n/2);
    deallocateMatrix(C12, n/2);
    deallocateMatrix(C21, n/2);
    deallocateMatrix(C22, n/2);
    deallocateMatrix(M1, n/2);
    deallocateMatrix(M2, n/2);
    deallocateMatrix(M3, n/2);
    deallocateMatrix(M4, n/2);
    deallocateMatrix(M5, n/2);
    deallocateMatrix(M6, n/2);
    deallocateMatrix(M7, n/2);
    deallocateMatrix(temp1, n/2);
    deallocateMatrix(temp2, n/2);
}

// Function to print a matrix of size n x n
void printMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

// Main function to test the Strassen algorithm
int main() {
    int n;
    printf("Enter the size of the matrices (power of 2): ");
    scanf("%d", &n);

    // Allocate memory for matrices A, B, and C
    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    // Perform matrix multiplication using Strassen algorithm
    strassenMatrixMultiplication(A, B, C, n);

    // Print the result matrix
    printf("Resultant matrix C:\n");
    printMatrix(C, n);

    // Deallocate memory for matrices
    deallocateMatrix(A, n);
    deallocateMatrix(B, n);
    deallocateMatrix(C, n);

    return 0;
}