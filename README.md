AUTHORING: Antonio Lazzaro/UMBC/CMSC 313/10:00/(4/16/25)

PURPOSE: These files are meant to create libraries for matrix operations that can be used on any matrices of arbitrary 2D size.

FILES:
matrix.h - Header file for matrix.cpp, which includes the Matrix class and its member functions, allows the creation of matrices and multiple operations on them.
matrix.cpp - Tests the functionality of the implemented Matrix functions.
matrix.c - Another implementation of matrix operations and testing, but done in C rather than C++.

BUILD INSTRUCTIONS: Matricies in both versions are created through 2D arrays. In the C++ file, the functions are meant to be implemented so that other than taking the transpose of a matrix, all operations can be written as if writing operations for integers. (Note that the scalor must be to the right of the multiplication operator.) Matrices in the C version must be iniitialized through "allocMat()" if created from scratch. All matrices in the C version must be deinitialized using "deallocMat" before the end of the program to prevent leaks.

TESTING METHODOLOGY: In the main functions for both of the testing programs, 3 matricies were intialized from scratch, as defined in the assignment instructions, and D was initialized through the operations done on the other 3 matrices.

ADDITIONAL INFORMATION: My machine repeatedly put out that the size of the arrays were equal to the size of a single integer, thus I was not able to complete sufficient testing.
