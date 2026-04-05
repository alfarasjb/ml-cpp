//
// Created by Jay on 4/5/2026.
//
// C++ follows a function prototyping pattern by default when creating new classes
// Declarations live in a .h file, while implementations live in .cpp
#pragma once // tells the compiler to only include this file once.
#include <vector>
#include <functional>
#include <tuple>
#ifndef ML_CPP_MATRIX_H
#define ML_CPP_MATRIX_H

using Matrix2D = std::vector<std::vector<double>>;

class Matrix {
protected:
private:
    // elementwise operation to abstract nested for loop
    Matrix elementwise(
        const Matrix& other,
        // `op` is a function callable that takes arguments of type `double`, `double`
        // and returns a type `double`
        const std::function<double(double, double)>& op
    ) const;
public:
    int rows;
    int cols;
    Matrix2D data;
    // zero matrix with specific dimensions
    Matrix(int rows, int cols);
    // matrix with specified values
    Matrix(int rows, int cols, double val);
    // declare a matrix
    explicit Matrix(const Matrix2D& data);
    void print() const ;
    // matrix addition
    Matrix operator+(const Matrix& other) const;
    // matrix subtraction
    Matrix operator-(const Matrix& other) const;
    //scalar multiplication
    Matrix operator*(double scalar) const;
    // matmul
    Matrix operator*(const Matrix& other) const;
    [[nodiscard]] Matrix transpose() const;
    [[nodiscard]] static Matrix identity(int n);
    std::tuple<int, int> shape = std::make_tuple(rows, cols);
    bool IsOneDimensional() const {
        return rows == 1 || cols == 1;
    }
    bool IsSquareMatrix() const {
        return rows == cols;
    }
    Matrix inverse();
};


double dot(const Matrix& a, const Matrix& b);


#endif //ML_CPP_MATRIX_H
