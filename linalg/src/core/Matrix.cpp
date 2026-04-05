//
// Created by Jay on 4/5/2026.
//

#include "../../include/core/Matrix.h"

#include <iostream>
#include <stdexcept>

Matrix::Matrix(const int rows, const int cols)
    : rows { rows }
    , cols { cols }
    , data(rows, std::vector(cols, 0.0)) {
}

Matrix::Matrix(const int rows, const int cols, const double val)
    : rows { rows }
    , cols { cols }
    , data(rows, std::vector(cols, val)) {}

Matrix::Matrix(const Matrix2D& data)
    : rows { static_cast<int>(data.size()) }
    , cols { static_cast<int>(data[0].size()) }
    , data(data) {}


Matrix Matrix::elementwise(
    const Matrix &other,
    const std::function<double(double, double)>& op) const
{
    // dimension check
    if (rows != other.rows || cols != other.cols) {
        throw std::runtime_error("Matrix Size does not match.");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = op(data[i][j], other.data[i][j]);
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    return elementwise(
        other,
        [](double const a, double const b) { return a + b; }
    );
}

Matrix Matrix::operator-(const Matrix& other) const {
    return elementwise(
        other,
        [](double const a, double const b) { return a - b; }
    );
}

Matrix Matrix::operator*(const double scalar) const {
    Matrix new_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            new_matrix.data[i][j] = data[i][j] * scalar;
        }
    }
    return new_matrix;
}

Matrix Matrix::transpose() const {
    Matrix new_matrix(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            new_matrix.data[j][i] = data[i][j];
        }
    }
    return new_matrix;
}

void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std:: cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
