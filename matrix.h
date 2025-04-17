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

    //Destructor for matricies
    ~Matrix(){
        clear(m_matrix, m_rows);
    }

    void clear(int* matrix[], int rows){
        for (int i = 0; i < rows; i++){
            delete[] matrix[i];
        }
        delete[] m_matrix;
    }

    //Overloaded multiplication operator for the Matrix class
    //This version of the multiplication operator allows scalors to
    //be applied to matricies
    Matrix operator*(const int scalor) const{
        //Build new matrix
        int** nValues = new int*[m_rows];
        for (int i = 0; i < m_rows; i++){
            nValues[i] = new int[m_columns];
            for (int x = 0; x < m_columns; x++){
                nValues[i][x] = m_matrix[i][x] * scalor;
            }
        }

        //Build ne object
        Matrix nMatrix(m_rows, m_columns, nValues);
        for (int i = 0; i < m_rows; i++){
            delete[] nValues[i];
        }
        delete[] nValues;

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
            //Build new matrix
            int** nValues = new int*[m_rows];
            for (int i = 0; i < m_rows; i++){
                nValues[i] = new int[m_columns];
                for (int x = 0; x < m_columns; x++){
                    nValues[i][x] = 
                    m_matrix[i][x] + rhs.m_matrix[i][x];
                }
            }

            //Build ne object
            Matrix nMatrix(m_rows, m_columns, nValues);
            for (int i = 0; i < m_rows; i++){
                delete[] nValues[i];
            }
            delete[] nValues;

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
            int** nValues= new int*[nRows];
            Matrix nrhs = rhs.transpose();
            for (int i = 0; i < nRows; i++){
                nValues[i] = new int[nColumns];
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
};

#endif