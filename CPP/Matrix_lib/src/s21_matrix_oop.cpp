#include "s21_matrix_oop.h"



bool S21Matrix::EqMatrix(const S21Matrix& other){
    bool res = true; // 1 - good, 0 - bad
    if(!matrix_|| !other.matrix_){
        throw std::invalid_argument("Matrix array is empty");
    } 
    if(rows_ == other.rows_ && cols_ == other.cols_){
        for(auto i = 0; i < rows_ && res == 1; i++){
            for(auto j = 0; j < cols_ && res == 1; j++){
                double del = matrix_[i*cols_+j] - other.matrix_[i*cols_+j];
                del = del < 0 ? del*(-1.0) : del;
                res = DELTA > del;
            }
        }
    }else
        res = false;
    return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other){
    if(!matrix_|| !other.matrix_){
        throw std::invalid_argument("Matrix array is empty");
    } 
    if(cols_ < 1 || rows_ < 1 || other.cols_ < 1 || other.rows_ < 0){
        throw std::invalid_argument("Matrix should at least 1x1 | wrong matrix size");
    } 
    if(rows_ != other.rows_ || cols_ != other.cols_){
        throw std::invalid_argument("Number of columns and rows should same in both matrices");
    } 
    for(auto i = 0; i < rows_*cols_; i++){
        matrix_[i] += other.matrix_[i];
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other){
    if(!matrix_|| !other.matrix_){
        throw std::invalid_argument("Matrix array is empty");
    } 
    if(cols_ < 1 || rows_ < 1 || other.cols_ < 1 || other.rows_ < 0){
        throw std::invalid_argument("Matrix should at least 1x1 | wrong matrix size");
    } 
    if(rows_ != other.rows_ || cols_ != other.cols_){
        throw std::invalid_argument("Number of columns and rows should same in both matrices");
    } 
    for(auto i = 0; i < rows_*cols_; i++){
        matrix_[i] -= other.matrix_[i];
    }    
}

void S21Matrix::MulNumber(double number){
    if(!matrix_){
        throw std::invalid_argument("Matrix array is empty");
    } 
    if(cols_ < 1 || rows_ < 1){
        throw std::invalid_argument("Matrix should at least 1x1 | wrong matrix size");
    } 
    for(auto i = 0; i < rows_*cols_; i++){
        matrix_[i] *= number;
    }    
}

void S21Matrix::MulMatrix(const S21Matrix& other){
    if(!matrix_|| !other.matrix_){
        throw std::invalid_argument("Matrix array is empty");
    } 
    if(cols_ < 1 || rows_ < 1 || other.cols_ < 1 || other.rows_ < 0){
        throw std::invalid_argument("Matrix should at least 1x1 | wrong matrix size");
    } 
    if(cols_ != other.rows_){
        throw std::invalid_argument("Base matrix column number doesnt equal other matrix row number");
    }  
    double *tempMatrix_ = new double[rows_ * other.cols_]();
    for(int i = 0; i < rows_; i++){
        for(int j = 0; j < other.cols_; j++){
            tempMatrix_[i*other.cols_+j] = 0;
            for(int m = 0; m < cols_; m++){
                tempMatrix_[i*other.cols_+j] += matrix_[i*cols_+m] * other.matrix_[m*other.cols_+j];
            }
        }
    }
    cols_ = other.cols_;
    delete[] matrix_;
    matrix_ = new double[rows_ * cols_]();
    for(int i = 0; i < rows_*cols_; i++){
        matrix_[i] = tempMatrix_[i];
    }
}

S21Matrix S21Matrix::Transpose(){  
    if(matrix_ == NULL){
        throw std::invalid_argument("Matrix array is empty");
    }  
    if(cols_ <= 0 || rows_ <= 0){
        throw std::invalid_argument("Matrix should at least 1x1 | wrong matrix size");
    } 
    // if(!matrix_ || cols_ <= 0 || rows_ <= 0) return *this;
    S21Matrix temp(cols_, rows_);
    for(int i = 0; i < cols_; i++){
        for(int j = 0; j < rows_; j++){
            temp.matrix_[i*rows_ + j] = matrix_[j*cols_ + i]; 
        }
    }
    return temp;
}

double S21Matrix::Determinant(){
    if(matrix_ == NULL){
        throw std::invalid_argument("Matrix array is empty");
    }
    if(rows_ != cols_){
        throw std::invalid_argument("Matrix should be square");
    }   
    if(rows_ < 1){
        throw std::invalid_argument("Matrix should at least 1x1 | wrong matrix size");
    }     
    if (rows_ == 1) {
        return matrix_[0];
    } else if (rows_ == 2) {
        return matrix_[0] * matrix_[3] - matrix_[1] * matrix_[2];
    } else {
        double det = 0.0;
        
        for (int i = 0; i < cols_; i++) {
            S21Matrix subMatrix;
            subMatrix.rows_ = rows_ - 1;
            subMatrix.cols_ = cols_ - 1;
            subMatrix.matrix_ = new double[subMatrix.rows_ * subMatrix.cols_];            
            int subMatrixIndex = 0;
            for (int j = 1; j < rows_; j++) {
                for (int k = 0; k < cols_; k++) {
                    if (k == i) continue;
                    subMatrix.matrix_[subMatrixIndex++] = matrix_[j * cols_ + k];
                }
            }
            det += (i % 2 == 0 ? 1 : -1) * matrix_[i] * subMatrix.Determinant();
            
        }
        return det;
    }
}



S21Matrix S21Matrix::createSubMatrix(int excludeRow, int excludeCol) {
    S21Matrix subMatrix(rows_ - 1, cols_ - 1);
    int subI = 0;
    for (int i = 0; i < rows_; i++) {
        if (i == excludeRow) {
            continue;
        }

        int subJ = 0;
        for (int j = 0; j < cols_; j++) {
            if (j == excludeCol) {
                continue;
            }
            subMatrix(subI, subJ) = matrix_[i*cols_ + j];
            subJ++;
        }
        subI++;
    }
    return subMatrix;
}

S21Matrix S21Matrix::CalcComplements() {
    if(matrix_ == NULL){
        throw std::invalid_argument("Matrix array is empty");
    }
    if(rows_ != cols_){
        throw std::invalid_argument("Matrix must be square");
    }
    if(rows_ < 2){
        throw std::invalid_argument("Matrix size must be at least 2x2");
    }
    S21Matrix complementMatrix(rows_,cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            S21Matrix subMatrix = createSubMatrix(i, j);
            int determinant = subMatrix.Determinant();
            int sign = (i + j) % 2 == 0 ? 1 : -1;
            complementMatrix(i,j) = determinant * sign;
        }
    }
    return complementMatrix;
}


/*
A-1 = 1/ det(A) * A(Т,compl)
A-1 - inverse matrix
det(A) - determinant of A matrix
A(T,compl) - transposed matrix of complements matrix (first find complements matrix -> transpose it)
*/
S21Matrix S21Matrix::InverseMatrix() {
    double det = this->Determinant();
    if(matrix_ == NULL){
        throw std::invalid_argument("Matrix array is empty");
    }
    if(det == 0 ){
        throw std::invalid_argument("Determinant should be different than 0");
    }
    if(rows_ != cols_){
        throw std::invalid_argument("Matrix must be square for inversion");
    }    
    
    S21Matrix complementMatrix = *this;
    // complementMatrix.matrix_ = matrix_;        
    
    complementMatrix = complementMatrix.CalcComplements();
    S21Matrix transpose;
    transpose = complementMatrix.Transpose();
    S21Matrix inverse;
    inverse = transpose * (1.0/det);
    return inverse;
}


void S21Matrix::MatElemToNull(){
    if(matrix_){
        for(int i = 0; i < rows_*cols_; i++)
            matrix_[i] = 0;
    }
}

int S21Matrix::getterCols_(){
    return cols_;
}

int S21Matrix::getterRows_(){
    return rows_;
}


/*
add functionality when changing cols or rows number:
when increasing matrix make new  elements equal ti 0
when reducing matrix remove excess elements 

1 2 3   -> add rows - > 1 2 3
4 5 6                   4 5 6
                        0 0 0

1 2 3                   1 2 
4 5 6 -> remove cols -> 4 5
7 8 9                   7 8
*/
S21Matrix& S21Matrix::setterCols_(int newCols){
    if(rows_ < 1 || newCols < 1 || cols_ < 1 || !matrix_){
        throw std::invalid_argument(
            "Incorrect matrix");
    }

    if(cols_ == newCols) return *this;
    
    S21Matrix temp(rows_, newCols);
    if(newCols > cols_){
        for(int i = 0; i < rows_; i++){
            for(int j = 0; j < cols_; j++){
                temp(i,j) = matrix_[i*cols_+j];
            }
            for(int j = cols_+1; j < newCols; j++){
                temp(i,j) = 0.0;
            }
        }
    }else{
        for(int i = 0; i < rows_; i++){
            for(int j = 0; j < newCols; j++){
                temp(i,j) = matrix_[i*cols_+j];
            } 
        }
    }
    *this = temp;
    return *this;
}

S21Matrix& S21Matrix::setterRows_(int newRows){
    if(rows_ < 1 || newRows < 1 || cols_ < 1 || !matrix_){
        throw std::invalid_argument(
            "Incorrect matrix");
    }
    if(rows_ == newRows) return *this;
    S21Matrix temp(newRows, cols_);
    if(newRows > rows_){
        for(int i = 0; i < newRows; i++){
            for(int j = 0; j < cols_ && i < rows_; j++){
                temp(i,j) = matrix_[i*cols_+j];
            }
            for(int j = 0; j < cols_ && i >= rows_; j++){
                temp(i,j) = 0.0;
            }
        }
    }else{
        for(int i = 0; i < newRows; i++){
            for(int j = 0; j < cols_; j++){
                temp(i,j) = matrix_[i*cols_+j];
            } 
        }
    }
    *this = temp;
    return *this;
}

void S21Matrix::print(){
    std::cout.precision(11);
    for(int i = 0; i < rows_; i++){
        for(auto j = 0; j <cols_; j++){
            std::cout << std::setw(3) << matrix_[i*cols_+j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


