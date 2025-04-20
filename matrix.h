#include <iostream>

#define DEFVALUE 0 //Default value for an entry into a matrix.

#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
    public:
    //Public member functions
    //
    //Constructor for Matricies.
    //Takes the number of rows and columns of the matrix,
    //and an array of values which are inserted into the matrix from 
    //left to right and top to bottom.
    Matrix(const int rows, const int columns, int* values[]){
        //Define dimensions
        m_rows = rows;
        m_columns = columns;

        //Build matrix
        m_matrix = new int*[rows];
        for (int i = 0; i < rows; i++){
            m_matrix[i] = new int[columns];
            for (int x = 0; x < columns; x++){
                if (values[i][x]){
                    m_matrix[i][x] = values[i][x];
                } else {
                    m_matrix[i][x] = DEFVALUE;
                }
            }
        }
    }

    //Copy constructor for matrices
    //Creates a deep copy of the passed matrix
    Matrix(const Matrix& rhs){
        //Define dimensions
        m_rows = rhs.m_rows;
        m_columns = rhs.m_columns;

        //Build matrix
        m_matrix = new int*[m_rows];
        for (int i = 0; i < m_rows; i++){
            m_matrix[i] = new int[m_columns];
            for (int x = 0; x < m_columns; x++){
                if (rhs.m_matrix[i][x]){
                    m_matrix[i][x] = rhs.m_matrix[i][x];
                } else {
                    m_matrix[i][x] = DEFVALUE;
                }
            }
        }
    }



    //Destructor for matricies
    ~Matrix(){
        clear(m_matrix, m_rows);
    }

    //Overloaded multiplication operator for the Matrix class
    //This version of the multiplication operator allows scalors to
    //be applied to matricies
    Matrix operator*(const int scalor) const{
            Matrix nMatrix(*this);
            for (int i = 0; i < m_rows; i++){
                for (int x = 0; x < m_columns; x++){
                    nMatrix.m_matrix[i][x] *= scalor;
                }
            }

            return nMatrix;
    }

    //Creates a transpose of the passed matrix
    //i.e. turns rows to columns and vice versa
    Matrix transpose() const{
        //Define new dimensions
        const int nRows = m_columns;
        const int nColumns = m_rows;

        //Build new matrix
        int** nValues = new int*[nRows];
        for (int i = 0; i < nRows; i++){
            nValues[i] = new int[nColumns];
            for (int x = 0; x < nColumns; x++){
                nValues[i][x] = m_matrix[x][i];
            }
        }

        //Build new object
        Matrix nMatrix(nRows, nColumns, nValues);
        for (int i = 0; i < nRows; i++){
            delete[] nValues[i];
        }
        delete[] nValues;

        return nMatrix;
    }

    //Overloaded addition operator for the Matrix class
    //Allows matricies to be added together
    Matrix operator+(const Matrix& rhs) const{
        if ((m_rows == rhs.m_rows) and (m_columns == rhs.m_columns)){
            Matrix nMatrix(*this);
            for (int i = 0; i < m_rows; i++){
                for (int x = 0; x < m_columns; x++){
                    nMatrix.m_matrix[i][x] += rhs.m_matrix[i][x];
                }
            }

            return nMatrix;
        }

        return *this;
    }

    //This overload of the multiplication operator
    //allows two matricies of compatible sizes to
    //be multiplied together
    Matrix operator*(const Matrix& rhs) const{
        if (m_columns == rhs.m_rows){
            //Define new dimensions
            const int nRows = m_rows;
            const int nColumns = rhs.m_columns;

            //Create new matrix
            int** nValues = new int*[m_rows];
            Matrix nrhs = rhs.transpose();
            for (int i = 0; i < nRows; i++){
                nValues[i] = new int[rhs.m_columns];
                for (int x = 0; x < nColumns; x++){
                    nValues[i][x] = 
                    dot(m_matrix[i], nrhs.m_matrix[x], m_columns);
                }
            }

            //Create new object
            Matrix nMatrix(nRows, nColumns, nValues);
            for (int i = 0; i < nRows; i++){
                delete[] nValues[i];
            }
            delete[] nValues;


            return nMatrix;
        }

        return *this;
    }

    //Overloaded assignment operator for the Matrix object
    //Creates a deep copy of the right hand side Matrix
    Matrix operator=(const Matrix& rhs){
        //Check if lhs and rhs are same
        if (this != &rhs){
            //Clear current matrix
            clear(m_matrix, m_rows);

            //Define new dimensions
            m_rows = rhs.m_rows;
            m_columns = rhs.m_columns;

            //Build new matrix
            m_matrix = new int*[m_rows];
            for (int i = 0; i < m_rows; i++){
                m_matrix[i] = new int[m_columns];
                for (int x = 0; x < m_columns; x++){
                    m_matrix[i][x] = rhs.m_matrix[i][x];
                }    
            }
        }

        return *this;
    }

    friend std::ostream& operator<<
    (std::ostream& os, const Matrix& rhs) {
        for (int i = 0; i < rhs.m_rows; i++){
            os << "|";
            for (int x = 0; x < rhs.m_columns; x++){
                os << " " << rhs.m_matrix[i][x] << " ";
            }
            os << "|\n";
        }

        return os;
    }

    //Overloaded equivalence operator for matrices
    //Returns true if both matrices have the same dimensions and values
    bool operator==(const Matrix& rhs) const{
        if (this == &rhs){
            return true;
        } else if ((m_rows == rhs.m_rows) and (m_columns == rhs.m_columns)) {
            for (int i = 0; i < m_rows; i++){
                for (int x = 0; x < m_columns; x++){
                    if (m_matrix[i][x] != rhs.m_matrix[i][x]){
                        return false;
                    }
                }
            }
        }

        return false;
    }

    //Overloaded non-equivilance operator for matrices
    //Returns true if either matrix differs at all from the other
    bool operator!=(const Matrix& rhs) const{
        if (*this == rhs){
            return false;
        }

        return true;
    }

    //Public member variables
    int** m_matrix;

    private:
    //Private member variables
    int m_rows;
    int m_columns;
    friend class Tester;


    //Private helper functions
    //
    //Finds the dot product of two vectors 
    int dot(int* lhs, int* rhs, const int size) const{
        int sum = 0;
        for (int i = 0; i < size; i++){
            sum += lhs[i] * rhs[i];
        }

        return sum;
    }

    //Deallocates all values in a matrix
    void clear(int* matrix[], int rows){
        for (int i = 0; i < rows; i++){
            delete[] matrix[i];
        }
        delete[] m_matrix;
    }
};

#endif
