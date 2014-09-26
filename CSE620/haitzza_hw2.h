#include <iostream>
#include <vector>

// alias a 2d vector of doubles to mat
using twoDimVec = std::vector<std::vector<double>>;

class Matrix {
 public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    double& operator()(int row, int col) const;
    Matrix operator+(const Matrix& right) const;
    Matrix operator-(const Matrix& right) const;
    Matrix operator*(const Matrix& right) const;                 
    Matrix operator*(const double scalar) const;
    Matrix operator/(const double scalar) const;
    Matrix& operator*=(const double scalar);
    Matrix& operator/=(const double scalar);
    Matrix operator~();
    Matrix operator>>(const int shiftVal) const;
    Matrix operator<<(const int shiftVal) const;
    void setFormat(int width, int precision);
 private:
    Matrix addSubHelp(const Matrix& right, std::function<double(double x, double y)> op) const;
    twoDimVec mat;
    int width;
    int precision;
};
