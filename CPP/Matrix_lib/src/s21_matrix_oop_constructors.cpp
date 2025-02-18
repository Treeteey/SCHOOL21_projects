#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
    rows_ = 0;
    cols_ = 0;
    matrix_ = new double[rows_ * cols_]();
    // std::cout <<"empty matrix created\n";
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols){
    if(rows > 0 && cols > 0){
        matrix_ = new double[rows_ * cols_]();
        MatElemToNull();
    }
    // std::cout <<"empty matrix  with " << rows_ << " " << cols_ << " created\n";
}

//copy constructor
S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_){
    if(other.rows_ > 0 && other.cols_ > 0 && other.matrix_){
        matrix_ = new double[rows_ * cols_]();
        std::memcpy(matrix_, other.matrix_, other.rows_*other.cols_* sizeof(double));       
        // std::cout <<"matrix copied\n";
    }
}

/*
Move constructor вызывается вместо copy constructor в случае, 
когда объект, из которого создается копия, вот-вот будет уничтожен. 
В таком конструкторе обычно данные из временного объекта переносятся
в новый объект, а полям временного объекта присваиваются nullptr
или что-то такое. Важно понимать, что при выходе из move constructor
оба объекта должны оставаться валидными и для обоих должен корректно
отрабатывать деструктор. Ссылка T&& называется rvalue reference
и означает ссылку на объект, который вот-вот будет уничтожен.
*/
S21Matrix::S21Matrix(S21Matrix&& other){
    if(rows_*cols_ == other.rows_*other.cols_){
        std::memcpy(matrix_, other.matrix_, other.rows_*other.cols_* sizeof(double));
    }else{
        // delete[] matrix_;
        matrix_ = new double[other.rows_ * other.cols_]();
        std::memcpy(matrix_, other.matrix_, other.rows_*other.cols_* sizeof(double));
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    delete[] other.matrix_;
    other.matrix_ = nullptr;
    other.cols_ = 0;
    other.rows_ = 0;
    // std::cout <<"matrix moved\n";
}

//destrutor
S21Matrix::~S21Matrix(){
    if(matrix_){
        delete[] matrix_;
        matrix_ = nullptr;
    }
    // std::cout <<"matrix destroyed:" << cols_ << " " << rows_ << "\n";
    cols_ = 0;
    rows_ = 0;    
}