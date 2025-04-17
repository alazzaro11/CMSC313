#include<stdio.h>
#include <stdlib.h>

#define DEFVALUE 0 //Default value for an entry into a matrix.

int** allocMat(const int rows, const int columns){
    int** result =  (int**)malloc(sizeof(int) * rows);
    for (int i = 0; i < rows; i++){
        result[i] = (int*)malloc(sizeof(int) * columns);
    }

    return result;
}

void deallocMat(int** matrix){
    for (int i = 0; i < sizeof(matrix); i++){
        free(matrix[i]);
    }
    free(matrix);
}

int** mAddition(int** mat1, int** mat2){
    if (sizeof(mat1) == sizeof(mat2)){
        int rows = sizeof(mat1) / sizeof(int);
        int columns = sizeof(mat1[0]) / sizeof(int);
        int** result = allocMat(rows, columns);
        for (int i = 0; i < sizeof(mat1) / sizeof(int); i++){
            if (sizeof(mat1[i]) == sizeof(mat2[i])){
                for (int x = 0; 
                    x < sizeof(mat1[i]) / sizeof(int); x++){
                    result[i][x] = mat1[i][x] + mat2[i][x];
                }
            } else {
                deallocMat(result);
                return mat1;
            }
        }

        return result;
    }

    return mat1;
}

int** mScale(int** matrix, const int scalor){
    int rows = sizeof(matrix) / sizeof(int);
    int columns = sizeof(matrix[0]) / sizeof(int);
    int** result = allocMat(rows, columns);
    for (int i = 0; i < sizeof(matrix) / sizeof(int); i++){
        for (int x = 0; 
            x < sizeof(matrix[i]) / sizeof(int); x++){
            result[i][x] = matrix[i][x] * scalor;
        }
    }

    return result;
}

int** transpose(int** matrix){
    int rows = sizeof(matrix[0]) / sizeof(int);
    int columns = sizeof(matrix) / sizeof(int);
    int** result = allocMat(rows, columns);
    for (int i = 0; i < sizeof(matrix) / sizeof(int); i++){
        for (int x = 0; 
            x < sizeof(matrix[i]) / sizeof(int); x++){
            result[x][i] = matrix[i][x];
        }
    }

    return result;
}

int** mMult(int** mat1, int** mat2){
    if (sizeof(mat1) == sizeof(mat2[0])){
        int rows = sizeof(mat1) / sizeof(int);
        int columns = sizeof(mat2) / sizeof(int);
        int** result = allocMat(rows, columns);

        int nRows = sizeof(mat2[0]) / sizeof(int);
        int nColumns = sizeof(mat2) / sizeof(int);
        int** trans = transpose(mat2);
        for (int i = 0; i < nRows; i++){
            for (int x = 0; nColumns; x++){
                result[i][x] = dot(mat1[i], trans[i], nRows);
            }
        }
        deallocMat(trans);

        return result;
    }

    return mat1;
}

int dot(int* lhs, int* rhs, const int size){
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += lhs[i] * rhs[i];
    }

    return sum;
}

int main(){
    int** A = allocMat(2, 2);
    int** B = allocMat(2, 3);
    int** C = allocMat(2, 3);

    A[0][0] = 6; A[0][1] = 4;
    A[1][0] = 8; A[1][1] = 3;

    B[0][0] = 1; B[0][1] = 2; B[0][2] = 3;
    B[1][0] = 4; B[1][1] = 5; B[1][2] = 6;

    C[0][0] = 2; C[0][1] = 4; C[0][2] = 6;
    C[1][0] = 1; C[1][1] = 3; C[1][2] = 5;

    int** D = mAddition(A, (mMult(mScale(B, 3), transpose(C))));

    for (int i = 0; i < 2; i++){
        for (int x = 0; x < 3; x++){
            printf("%d", D[i][x]);
            printf(" ");
        }
        printf("\n");
    }

    deallocMat(A);
    deallocMat(B);
    deallocMat(C);
    deallocMat(D);

    return 0;
}