// Copyright 2014 Zach Haitz
#include <iostream>
#include <vector>
#include <functional>

// alias a 2d vector of doubles to mat
using twoDimVec = std::vector<std::vector<double>>;

class Matrix {
 public:
    Matrix();
    Matrix(double rows, double cols);
    Matrix(const Matrix& other);
    double& operator()(int row, int col);
    Matrix operator+(const Matrix& right) const;
    Matrix operator-(const Matrix& right) const;
    Matrix operator*(const Matrix& right) const;
    Matrix operator*(const double scalar) const;
    Matrix operator/(const double scalar) const;
    Matrix& operator*=(const double scalar);
    Matrix& operator/=(const double scalar);
    Matrix operator~() const;
    Matrix operator>>(const int shiftVal) const;
    Matrix operator<<(const int shiftVal) const;
    Matrix& setFormat(int width, int precision);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);

 private:
    Matrix addSubHelp(const Matrix& right,
                      std::function<double(double x, double y)> op) const;
    Matrix scalarHelp(const double& right,
                      std::function<double(double x, double y)> op) const;
    twoDimVec mat;
    int width;
    int precision;
};
