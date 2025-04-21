#include<stdio.h>
#include <stdlib.h>

#define DEFVALUE 0 //Default value for an entry into a matrix.

//This struct is able to carry a 2D array which holds the values for a 2D matrix
//It also stores the integer values for the number of rows and columns in the array
struct Matrix {
    int ** m_matrix;
    int m_rows;
    int m_columns;
};

//This function creates and returns a dynamically alloacted Matrix struct
//in the form of a pointer
//To avoid memory leakage deallocate this Matrix using the deallocMat method
struct Matrix* allocMat(const int rows, const int columns){
    struct Matrix* result = (struct Matrix*)malloc(sizeof(struct Matrix));
    result->m_rows = rows;
    result->m_columns = columns;
    result->m_matrix =  (int**)malloc(sizeof(int) * rows);
    for (int i = 0; i < rows; i++){
        result->m_matrix[i] = (int*)malloc(sizeof(int) * columns);
    }

    return result;
}

//This function frees all dynamically alloacted memory in a Matrix struct
void deallocMat(struct Matrix* matrix){
    for (int i = 0; i < matrix->m_rows; i++){
        free(matrix->m_matrix[i]);
    }
    free(matrix->m_matrix);
    free(matrix);
}

//This function takes two vectors in the form of 1D arrays,
//and returns their dot product 
int dot(int* lhs, int* rhs, const int size){
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += lhs[i] * rhs[i];
    }

    return sum;
}

//This function creates and returns a matrix struct in the form of a pointer
//The matrix is a deep copy of the passed matrix
//To avoid memory leakage, this matrix must be deallocated using the deallocMat method
struct Matrix* copyMat(struct Matrix* rhs){
    struct Matrix* result = allocMat(rhs->m_rows, rhs->m_columns);

    for (int i = 0; i < result->m_rows; i++){
        for (int x = 0; x < result->m_columns; x++){
            result->m_matrix[i][x] = rhs->m_matrix[i][x];
        }
    }

    return result;
}

//This function performs matrix addition on 2 matrices and returns their result
//To avoid memory leakage, this matrix must be deallocated using the deallocMat method
struct Matrix* mAddition(struct Matrix* mat1, struct Matrix* mat2){
    if ((mat1->m_rows == mat2->m_rows) 
    && (mat1->m_columns == mat2->m_columns)){ 
        struct Matrix* result = copyMat(mat1);

        for (int i = 0; i < result->m_rows; i++){
            for (int x = 0; x < result->m_columns; x++){
                result->m_matrix[i][x] += mat2->m_matrix[i][x];
            }
        }

        return result;
    }

    return mat1;
}

//This function scales a matrix based on the passed scalor and returns the result
//To avoid memory leakage, this matrix must be deallocated using the deallocMat method
struct Matrix* mScale(struct Matrix* matrix, const int scalor){
    struct Matrix* result = copyMat(matrix);
    for (int i = 0; i < result->m_rows; i++){
        for (int x = 0; x < result->m_columns; x++){
            result->m_matrix[i][x] *= scalor;
        }
    }

    return result;
}

//This function transposes a matrix and returns the result
//To avoid memory leakage, this matrix must be deallocated using the deallocMat method
struct Matrix* transpose(struct Matrix* matrix){
    struct Matrix* result = allocMat(matrix->m_columns, matrix->m_rows);

    for (int i = 0; i < result->m_rows; i++){
        for (int x = 0; x < result->m_columns; x++){
            result->m_matrix[i][x] = matrix->m_matrix[x][i];
        }
    }

    return result;
}

//This function multiplies two matrices and returns their result
//To avoid memory leakage, this matrix must be deallocated using the deallocMat method
struct Matrix* mMult(struct Matrix* mat1, struct Matrix* mat2){
    if (mat1->m_columns == mat2->m_rows){
        struct Matrix* result = allocMat(mat1->m_rows, mat2->m_columns);
        struct Matrix* trans = transpose(mat2);
        
        for (int i = 0; i < result->m_rows; i++){
            for (int x = 0; x < result->m_columns; x++){
                result->m_matrix[i][x] = 
                dot(mat1->m_matrix[i], trans->m_matrix[x], mat1->m_columns);
            }
        }
        deallocMat(trans);

        return result;
    }

    return mat1;
}

//This function prints a matrix struct to the console
void print(struct Matrix* matrix){
    for (int i = 0; i < matrix->m_rows; i++){
        printf("|");
        printf(" ");
        for (int x = 0; x < matrix->m_columns; x++){
            printf("%d", matrix->m_matrix[i][x]);
            printf(" ");
        }
        printf("|");
        printf("\n");
    }
}

//This main function tests the library functions,
//by using the operations to print a new Matrix
int main(){
    struct Matrix* A = allocMat(2, 2);

    struct Matrix* B = allocMat(2, 3);

    struct Matrix* C = allocMat(2, 3);

    A->m_matrix[0][0] = 6; A->m_matrix[0][1] = 4;
    A->m_matrix[1][0] = 8; A->m_matrix[1][1] = 3;

    B->m_matrix[0][0] = 1; B->m_matrix[0][1] = 2; B->m_matrix[0][2] = 3;
    B->m_matrix[1][0] = 4; B->m_matrix[1][1] = 5; B->m_matrix[1][2] = 6;

    C->m_matrix[0][0] = 2; C->m_matrix[0][1] = 4; C->m_matrix[0][2] = 6;
    C->m_matrix[1][0] = 1; C->m_matrix[1][1] = 3; C->m_matrix[1][2] = 5;

    struct Matrix* op1 = mScale(B, 3);
    struct Matrix* op2 = transpose(C);
    struct Matrix* op3 = mMult(op1, op2);

    struct Matrix* D = mAddition(A, op3);

    print(D);

    deallocMat(A);
    deallocMat(B);
    deallocMat(C);
    deallocMat(D);
    deallocMat(op1);
    deallocMat(op2);
    deallocMat(op3);

    return 0;
}
