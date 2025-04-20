#include "matrix.h"
#include <iostream>

using namespace std;

class Tester{};

int main(){
    int* matrix1[2];
    int matrix11[2] = {6, 4};
    int matrix12[2] = {8, 3};
    matrix1[0] = matrix11;
    matrix1[1] = matrix12;
    const Matrix A(2, 2, matrix1);

    int* matrix2[2];
    int matrix21[3] = {1, 2, 3};
    int matrix22[3] = {4, 5, 6};
    matrix2[0] = matrix21;
    matrix2[1] = matrix22;
    const Matrix B(2, 3, matrix2);

    int* matrix3[2];
    int matrix31[3] = {2, 4, 6};
    int matrix32[3] = {1, 3, 5};
    matrix3[0] = matrix31;
    matrix3[1] = matrix32;
    const Matrix C(2, 3, matrix3);

    cout << A + ((B*3) * C.transpose()) << endl;

    return 0;
}
