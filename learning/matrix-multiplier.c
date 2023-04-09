#include <stdio.h>
#include <stdlib.h>

#define INPUT_STR_SIZE 10

struct Matrix {
    unsigned int num_rows;
    unsigned int num_cols;
    int **array;
};

void initMatrixStruct(struct Matrix* matrix, unsigned int rowCount, unsigned int colCount);
void freeMatrixStruct(struct Matrix* matrix);
int checkMultiplicationPossible(struct Matrix* matrixA, struct Matrix* matrixB);
void getRowColInput(char arr[], unsigned int* rowVal, unsigned int* colVal);
void getMatrixFillInput(struct Matrix* matrix);
void printMatrix(struct Matrix* matrix);

int main(void)
{
    struct Matrix matrixA, matrixB, outputMatrix;
    char input[INPUT_STR_SIZE];
    unsigned int rowInput = 0, colInput = 0;

    printf(" Please enter the number of rows and columns of the first matrix you'd like to multiply.\n "
        "Please input like so: 3 4 (rows followed by columns, with a space between)\n "
        "Note that your input must be greater than 0.\n "
        );

    getRowColInput(input, &rowInput, &colInput);
    
    initMatrixStruct(&matrixA, rowInput, colInput);
    rowInput = 0, colInput = 0;

    printf("Please enter the number of rows and columns of the second matrix you'd like to multiply.\n");

    getRowColInput(input, &rowInput, &colInput);

    initMatrixStruct(&matrixB, rowInput, colInput);
    rowInput = 0, colInput = 0;

    if (!checkMultiplicationPossible(&matrixA, &matrixB)) {
        freeMatrixStruct(&matrixA);
        freeMatrixStruct(&matrixB);
        return 0;
    }

    initMatrixStruct(&outputMatrix, matrixA.num_rows, matrixB.num_cols);

    printf("Please input the values in your first matrix.\n");
    getMatrixFillInput(&matrixA);

    printf("Please input the values in your second matrix.\n");
    getMatrixFillInput(&matrixB);

    freeMatrixStruct(&matrixA);
    freeMatrixStruct(&matrixB);
    freeMatrixStruct(&outputMatrix);

    return 0;
}

void getRowColInput(char arr[], unsigned int* rowVal, unsigned int* colVal) {
    while (*rowVal <= 0 && *colVal <= 0) {
        fgets(arr, INPUT_STR_SIZE, stdin);
        sscanf(arr, "%u %u", rowVal, colVal);
    }
}

void initMatrixStruct(struct Matrix* matrix, unsigned int rowCount, unsigned int colCount) {
    matrix->num_rows = rowCount;
    matrix->num_cols = colCount;
    matrix->array = calloc(rowCount, sizeof(int *));

    for (int i=0; i < (int)colCount; i++) {
        matrix->array[i] = calloc(colCount, sizeof(int));
    }
}

void freeMatrixStruct(struct Matrix* matrix) {
    for (int i = 0; i < (int)matrix->num_cols; i++) {
        free(matrix->array[i]);
    }

    matrix->num_cols = 0;
    matrix->num_rows = 0;

    free(matrix->array);
    matrix->array = NULL;
}

int checkMultiplicationPossible(struct Matrix* matrixA, struct Matrix* matrixB) {
    if (!matrixA || !matrixB) {
        printf("Please provide 2 matrices to check!\n");
        return 0;
    }

    if (matrixA->num_cols != matrixB->num_rows) {
        printf("Matrix multiplication is not possible.\n "
            "The number of columns in the first matrix must equal the number of rows in the second.\n"
        );
        return 0;
    }

    return 1;
}

void getMatrixFillInput(struct Matrix* matrix) {
    const int maxInputLen = 5;
    char input[maxInputLen];
    int currInput = 0;

    for (int i=0; i < (int)matrix->num_rows; i++) {
        for (int j=0; j < (int)matrix->num_cols; j++) {
            printf("Matrix[%d][%d]: ", i, j);
            fgets(input, maxInputLen, stdin);
            sscanf(input, "%d", &currInput);
            matrix->array[i][j] = currInput;
        }
    }
}

void printMatrix(struct Matrix* matrix) {
    if (matrix->num_cols == 0 || matrix->num_rows == 0) {
        printf("No matrix to print.\n");
    }

    printf("\n");
    for (int i=0; i < (int)matrix->num_rows; i++) {
        for (int j=0; j < (int)matrix->num_cols; j++) {
            printf("%d ", matrix->array[i][j]);
        }
        printf("\n");
    }
}