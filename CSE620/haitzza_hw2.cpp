#include "haitzza_hw2.h"
#include <algorithm>
#include <iomanip>
#include <functional>
#include <numeric>

Matrix::Matrix() {
    this->mat = twoDimVec(1.0, std::vector<double>(1.0,0));
}

Matrix::Matrix(double rows, double cols) {
    this->mat = twoDimVec(rows, std::vector<double>(cols));
    this->width = 0;
    this->precision = 0;
}

Matrix::Matrix(const Matrix& other) {
    this->mat = other.mat;
    this->width = other.width;
    this->precision = other.precision;
}

double& Matrix::operator()(int row, int col) {
    return mat[row][col];
}

Matrix Matrix::operator+(const Matrix& right) const {
    return addSubHelp(right, std::plus<double>());
}

Matrix Matrix::operator-(const Matrix& right) const {
    return addSubHelp(right, std::minus<double>());
}

Matrix Matrix::operator*(const Matrix& right) const {
    Matrix a(this->mat.size(), right.mat[0].size());
    std::cout << this->mat[0].size() << " " << right.mat.size() << std::endl;
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

Matrix Matrix::operator*(const double scalar) const {
    return scalarHelp(scalar, std::multiplies<double>());
}

Matrix Matrix::operator/(const double scalar) const {
    return scalarHelp(scalar, std::divides<double>());
}

Matrix& Matrix::operator*=(const double scalar) {
    for (uint i = 0; i < this->mat.size(); i++) {
        for (uint j = 0; j < this->mat[0].size(); j++) {
            this->mat[i][j] = this->mat[i][j] * scalar;
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(const double scalar) {
    for (uint i = 0; i < this->mat.size(); i++) {
        for (uint j = 0; j < this->mat[0].size(); j++) {
            this->mat[i][j] = this->mat[i][j] / scalar;
        }
    }
    return *this;
}

Matrix Matrix::operator~() const {
    Matrix a(this->mat[0].size(), this->mat.size());
    for (uint i = 0; i < this->mat.size(); i++) {
        for (uint j = 0; j < this->mat[0].size(); j++) {
            a.mat[j][i] = this->mat[i][j];
        }
    }
    return a;
}

Matrix Matrix::operator>>(const int shiftVal) const {
    Matrix a(*this);
    for (uint j = 0; j < a.mat.size(); j++) {
        for (int i = 0; i < shiftVal; i++) {
            a.mat[j].insert(a.mat[j].begin(), 0.0);
        }
    }
    return a;
}

Matrix Matrix::operator<<(const int shiftVal) const {
    Matrix a(*this);
    for (uint j = 0; j < a.mat.size(); j++) {
        for (int i = 0; i < shiftVal; i++) {
            a.mat[j].erase(a.mat[j].begin(), a.mat[j].begin()+1);
        }
    }
    return a;
}

std::string Matrix::setFormat(int width, int precision) {
    this->width = width;
    this->precision = precision;
    return "";
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (uint i = 0; i < mat.mat.size(); i++) {
        for (uint j = 0; j < mat.mat[0].size(); j++) {
            os << mat.mat[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

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

Matrix Matrix::scalarHelp(const double& right, std::function<double(double x, double y)> op) const {
    Matrix a(*this);
    for (uint i = 0; i < this->mat.size(); i++) {
        for (uint j = 0; j < this->mat[0].size(); j++) {
            a.mat[i][j] = op(a.mat[i][j], right);
        }
    }
    return a;
}

Matrix Matrix::addSubHelp(const Matrix& right, std::function<double(double x, double y)> op) const {
    if (this->mat.size() != right.mat.size() ||
        this->mat[0].size() != right.mat[0].size()) {
        return Matrix(0,0);
    }
    Matrix a(this->mat.size(), this->mat[0].size());
    for (uint i = 0; i < a.mat.size(); i++) {
        for (uint j = 0; j < a.mat[0].size(); j++) {
            a.mat[i][j] = op(this->mat[i][j], right.mat[i][j]);
        }
    }
    return a;
}
