#include "haitzza_hw2.h"
#include <algorithm>

Matrix::Matrix() {
    this->mat(1, std::vector<double>(1,0));
}

Matrix::Matrix(int rows, int cols) {
    this->mat(rows, std::vector<double>(1));
    this->width = 0;
    this->precision = 0;
}

Matrix::Matrix(const Matrix& other) {
    this->mat = other->mat;
    this->width = other->width;
    this->precision = other->precision;
}

double& Matrix::operator()(int row, int col) const {
    return *mat[row][col];
}

Matrix Matrix::operator+(const Matrix& right) const {
    return addSubHelp(right, std::plus<double>());
}

Matrix Matrix::operator-(const Matrix& right) const {
    return addSubHelp(right, std::minus<double>());
}

Matrix Matrix::operator*(const Matrix& right) const {
    Matrix a(this->mat.size(), right.mat[0].size());
    for (int i = 0; i < this->mat.size(); i++) {
        for (int j = 0; j < right.mat[0].size(); j++) {
            
        }
    }
}

Matrix Matrix::addSubHelp(const Matrix& right, std::function<double(double x, double y)> op) const {
    if (this->mat.size() != right.mat.size() ||
        this->mat[0].size() != right.mat[0].size()) {
        return Matrix(0,0);
    }
    Matirx a(this->mat.size(), this->mat[0].size());
    for (int i = 0; i < a.mat.size(); i++) {
        for (int j = 0; j < a.mat[0].size(); j++) {
            a.mat[i][j] = op(&this(i,j),&right(i,j));
        }
    }
}
