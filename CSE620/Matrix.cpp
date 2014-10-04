// Copyright 2014 Zach Haitz
#include "./Matrix.h"
#include <algorithm>
#include <iomanip>
#include <functional>
#include <numeric>
#include <vector>

// default constructor. creates a 1x1 matrix with
// 8 width and 0 precision for formatting
Matrix::Matrix() {
    this->mat = twoDimVec(1.0, std::vector<double>(1.0, 0));
    this->width = 8;
    this->precision = 0;
}

// given a number of rows, and cols, creates a rows by cols matrix
// inits width and precision to 8 and 0, respectively
Matrix::Matrix(double rows, double cols) {
    this->mat = twoDimVec(rows, std::vector<double>(cols));
    this->width = 8;
    this->precision = 0;
}

// copy constructor
Matrix::Matrix(const Matrix& other) {
    this->mat = other.mat;
    this->width = other.width;
    this->precision = other.precision;
}

// return the value at row col. can't be const because
// we can change the value in the matrix
double& Matrix::operator()(int row, int col) {
    return mat[row][col];
}

// adds two matrices
Matrix Matrix::operator+(const Matrix& right) const {
    return addSubHelp(right, std::plus<double>());
}

// subtracts two matrices
Matrix Matrix::operator-(const Matrix& right) const {
    return addSubHelp(right, std::minus<double>());
}

// multiplies two matrices... not a strassen algorithm :(
Matrix Matrix::operator*(const Matrix& right) const {
    // size is rows of left and cols of right
    Matrix a(this->mat.size(), right.mat[0].size());
    for (uint i = 0; i < this->mat.size(); i++) {
        for (uint j = 0; j < right.mat[0].size(); j++) {
            a.mat[i][j] = 0;
            for (uint k = 0; k < this->mat[0].size(); k++) {
                a.mat[i][j] += this->mat[i][k] * right.mat[k][j];
            }
        }
    }
    return a;
}

// multiplies all values by some scalar
Matrix Matrix::operator*(const double scalar) const {
    return scalarHelp(scalar, std::multiplies<double>());
}

// divides all values by some scalar
Matrix Matrix::operator/(const double scalar) const {
    return scalarHelp(scalar, std::divides<double>());
}

// modifies this by multiplying this by some scalar
// wasn't able to reuse the scalarHelper because const vs non-const
Matrix& Matrix::operator*=(const double scalar) {
    return thisScalarHelper(std::multiplies<double>(), scalar);
}

// modifies this matrix by dividing by some scalar
Matrix& Matrix::operator/=(const double scalar) {
    // should check for divide by zero here...
    return thisScalarHelper(std::divides<double>(), scalar);
}

// helper method that multiplies or divides this by some scalar value
Matrix& Matrix::thisScalarHelper(std::function<double(double x, double y)> op,
                                 const double scalar) {
    for (uint i = 0; i < this->mat.size(); i++) {
        for (uint j = 0; j < this->mat[0].size(); j++) {
            this->mat[i][j] = op(this->mat[i][j], scalar);
        }
    }
    return *this;
}

// returns and creates the transpose of this matrix
Matrix Matrix::operator~() const {
    Matrix a(this->mat[0].size(), this->mat.size());
    for (uint i = 0; i < this->mat.size(); i++) {
        for (uint j = 0; j < this->mat[0].size(); j++) {
            a.mat[j][i] = this->mat[i][j];
        }
    }
    return a;
}

// inserts shiftVal cols at beginning of matrix fills them with 0's
Matrix Matrix::operator>>(const int shiftVal) const {
    Matrix a(*this);
    for (uint j = 0; j < a.mat.size(); j++) {
        for (int i = 0; i < shiftVal; i++) {
            a.mat[j].insert(a.mat[j].begin(), 0.0);
        }
    }
    return a;
}

// removes shiftVals cols from beginning
Matrix Matrix::operator<<(const int shiftVal) const {
    Matrix a(*this);
    for (uint j = 0; j < a.mat.size(); j++) {
        for (int i = 0; i < shiftVal; i++) {
            a.mat[j].erase(a.mat[j].begin(), a.mat[j].begin()+1);
        }
    }
    return a;
}

// change format vars and return a reference to this to print
Matrix& Matrix::setFormat(int width, int precision) {
    this->width = width;
    this->precision = precision;
    return *this;
}

// Print the given mat
// use std::setw and std::setprecision to format the matrix as defined
// by the user
std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    os << std::setw(mat.width) << std::setprecision(mat.precision);
    for (uint i = 0; i < mat.mat.size(); i++) {
        for (uint j = 0; j < mat.mat[0].size(); j++) {
            os <<mat.mat[i][j]
               << std::setw(mat.width)
               << std::setprecision(mat.precision);
        }
        os << std::endl;
    }
    return os;
}

// read in a matrix using the aggred upon protocol
// first to values are the number of rows and cols, then the rest
// are the values
std::istream& operator>>(std::istream& is, Matrix& matrix) {
    int rows, cols;
    is >> rows >> cols;
    matrix = Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            is >> matrix.mat[i][j];
        }
    }
    return is;
}

// helper method to apply scalar multiplication to const matrix
Matrix Matrix::scalarHelp(const double& right,
                          std::function<double(double x, double y)> op) const {
    Matrix a(*this);
    for (uint i = 0; i < this->mat.size(); i++) {
        for (uint j = 0; j < this->mat[0].size(); j++) {
            a.mat[i][j] = op(a.mat[i][j], right);
        }
    }
    return a;
}

// helper method to apply addition or subtraction to given matrix...
// I really wish I was smart enough to combine this and the multiplication...
Matrix Matrix::addSubHelp(const Matrix& right,
                          std::function<double(double x, double y)> op) const {
    // verify first that you can actually add/sub the matrices.
    // need to have same number of rows and cols in both
    if (this->mat.size() != right.mat.size() ||
        this->mat[0].size() != right.mat[0].size()) {
        return Matrix(0, 0);
    }
    Matrix a(this->mat.size(), this->mat[0].size());
    for (uint i = 0; i < a.mat.size(); i++) {
        for (uint j = 0; j < a.mat[0].size(); j++) {
            a.mat[i][j] = op(this->mat[i][j], right.mat[i][j]);
        }
    }
    return a;
}
