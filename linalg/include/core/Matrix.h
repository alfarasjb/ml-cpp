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
    int rows_, cols_;
    Matrix2D data_;
public:
    [[nodiscard]] int rows() const { return rows_; }
    [[nodiscard]] int cols() const { return cols_; }
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
    // operator overload for accessing matrix elements
    // call this by
    // Matrix my_new_matrix(2, 2); // creates a 2x2 zero matrix
    // my_new_matrix(1, 1); // gets data_[1][1];
    // references an element.
    // non-const matrices
    double &operator()(const int i, const int j) { return data_[i][j]; }
    const double& operator()(const int i, const int j) const { return data_[i][j]; }
    [[nodiscard]] Matrix transpose() const;
    [[nodiscard]] static Matrix identity(const Matrix& a);
    [[nodiscard]] static Matrix identity(int n);
    [[nodiscard]] std::tuple<int, int> shape() const { return { rows_, cols_ }; }

    [[nodiscard]] bool is_one_dimensional() const {
        return rows_ == 1 || cols_ == 1;
    }
    [[nodiscard]] bool is_square_matrix() const {
        return rows_ == cols_;
    }
    [[nodiscard]] bool is_row_vector() const {
        return rows_ == 1;
    }
    [[nodiscard]] bool is_column_vector() const {
        return cols_ == 1;
    }
    [[nodiscard]] Matrix inverse() const;
};


double dot(const Matrix& a, const Matrix& b);


#endif //ML_CPP_MATRIX_H
