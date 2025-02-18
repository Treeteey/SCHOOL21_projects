#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iomanip>

#define DELTA 10e-10

class S21Matrix {
private:
    // attributes
    int rows_, cols_;         // Rows and columns
    double *matrix_;         // Pointer to the memory where the matrix is allocated

public:
    S21Matrix();                                                // default constructor
    S21Matrix(int rows, int cols);                              // parameterized constructor
    S21Matrix(const S21Matrix& other);                          // copy cnstructor
    S21Matrix(S21Matrix&& other);                               // move cnstructor
    ~S21Matrix();                                               // destructor

    // some operators overloads 
    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    friend S21Matrix operator*(double number, S21Matrix& matrix);
    friend S21Matrix operator*(S21Matrix& matrix, double number);
    bool operator==(const S21Matrix& other);
    S21Matrix& operator=(const S21Matrix& other);                  //w
    S21Matrix& operator+=(const S21Matrix& other);                         
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(double number);
    double& operator()(int row, int col);                          // index operator overload
    const double& operator()(int row, int col) const;

    // some public methods
    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other); 
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix InverseMatrix();
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    

    //side chicks
    void MatElemToNull();
    double getterMatElem(int i);
    int getterRows_();
    int getterCols_();
    // void setterRows_(int newRows);
    // void setterCols_(int newCols);
    S21Matrix& setterRows_(int newRows);
    S21Matrix& setterCols_(int newCols);


    void print();
    S21Matrix createSubMatrix(int excludeRow, int excludeCol);
};

S21Matrix operator*(double number, S21Matrix& matrix);
S21Matrix operator*(S21Matrix& matrix, double number);


#endif