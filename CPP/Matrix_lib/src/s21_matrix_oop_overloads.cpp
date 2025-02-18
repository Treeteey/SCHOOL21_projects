#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other){
    S21Matrix res = *this;
    res.SumMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other){
    S21Matrix res = *this;
    res.SubMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other){
    S21Matrix res = *this;
    res.MulMatrix(other);
    return *this;
}


// friend function - added to S21MAtrix class
S21Matrix operator*(double number, S21Matrix& matrix){
    S21Matrix res = matrix;
    res.MulNumber(number);
    return res;
}
// friend function - added to S21MAtrix class
S21Matrix operator*(S21Matrix& matrix, double number){
    S21Matrix res = matrix;
    res.MulNumber(number);
    return res;
}

bool S21Matrix::operator==(const S21Matrix& other){
    return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other){
    if(this == &other){
        return *this;
    }
    if(matrix_){
        delete[] matrix_;
    }
    matrix_ = new double[other.rows_*other.cols_]();
    rows_ = other.rows_;
    cols_ = other.cols_;
    for(int i = 0; i < rows_*cols_; i++){
        matrix_[i] = other.matrix_[i];
    }
    return *this;
}        

S21Matrix& S21Matrix::operator+=(const S21Matrix& other){
    SumMatrix(other);
    return *this;
}    

S21Matrix& S21Matrix::operator-=(const S21Matrix& other){
    SubMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other){
    MulMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(double number){
    MulNumber(number);
    return *this;
}



// index operator overload
double& S21Matrix::operator()(int row, int col){
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return matrix_[row * cols_ + col];
}
// read only purposes : const double& element = matrix(0, 0);
const double& S21Matrix::operator()(int row, int col) const {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return matrix_[row * cols_ + col];
}