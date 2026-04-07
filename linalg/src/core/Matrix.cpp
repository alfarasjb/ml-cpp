//
// Created by Jay on 4/5/2026.
//

#include "../../include/core/Matrix.h"
#include "../../include/core/MatrixHelpers.h"
#include <iostream>
#include <stdexcept>

Matrix::Matrix(const int rows, const int cols)
    : rows_ { rows }
    , cols_ { cols }
    , data_(rows, std::vector(cols, 0.0)) {
}

Matrix::Matrix(const int rows, const int cols, const double val)
    : rows_ { rows }
    , cols_ { cols }
    , data_(rows, std::vector(cols, val)) {}

Matrix::Matrix(const Matrix2D& data)
    : rows_ { static_cast<int>(data.size()) }
    , cols_ { static_cast<int>(data[0].size()) }
    , data_(data) {}


Matrix Matrix::elementwise(
    const Matrix &other,
    const std::function<double(double, double)>& op) const
{
    // dimension check
    if (rows_ != other.rows() || cols_ != other.cols()) {
        throw std::runtime_error("Matrix Size does not match.");
    }
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result(i, j) = op((*this)(i, j), other(i, j));
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
    Matrix new_matrix(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            new_matrix(i, j) = (*this)(i, j) * scalar;
        }
    }
    return new_matrix;
}

// matmul
Matrix Matrix::operator*(const Matrix& other) const {
    // check dimensions first. inner dimensions must be equal
    if (cols_ != other.rows()) {
        throw std::runtime_error("Matrix inner dimensions do not match");
    }
    // create a result matrix of size i and j (rows, and other.cols)
    Matrix result(rows_, other.cols());
    const int inner = cols_; // or other.rows. since they should be equal
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            double sum = 0.0;
            for (int k = 0; k < inner; ++k) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix new_matrix(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            new_matrix(j, i) = (*this)(i, j);
        }
    }
    return new_matrix;
}

void Matrix::print() const {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std:: cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::identity(const Matrix& a) {
    // returns nxn matrix with 1 as the diagonal, and 0 everywhere else
    // n should be non-zero
    if (!a.is_square_matrix()) {
        throw std::runtime_error("Not a square matrix.");
    }
    Matrix identity_matrix(a.rows(), a.cols(), 0);
    for (int i = 0; i < a.rows(); ++i) {
        for (int j = 0; j < a.cols(); ++j) {
            if (i == j) {
                // diagonal
                identity_matrix(i, j) = 1.0;
            }
        }
    }
    return identity_matrix;
}

Matrix Matrix::identity(const int n) {
    const Matrix a(n, n, 0);
    return identity(a);
}
static Matrix convert_column_vector_to_row_vector(const Matrix &vector) {
    if (vector.cols() > 1 && vector.rows() == 1) {
        // already a row vector
        return vector;
    }
    // if not, then transpose
    return vector.transpose();
}
double dot (const Matrix& a, const Matrix& b) {
    // nx1 matrix only.
    // num cols a = num rows b
    // transpose conditions: if len a == len b, then transpose
    if (!a.is_one_dimensional() || !b.is_one_dimensional()) {
        throw std::runtime_error("Only Nx1 Matrix is allowed.");
    }
    const Matrix a_transposed = convert_column_vector_to_row_vector(a);
    const Matrix b_transposed = convert_column_vector_to_row_vector(b);
    if (a_transposed.cols() != b_transposed.cols()) {
        throw std::runtime_error("Matrix does not have the same dimensionality.");
    }
    return (a_transposed * b_transposed.transpose())(0, 0);
}

Matrix Matrix::inverse() const {
    Matrix a(*this);  // work on a copy
    Matrix identity_matrix = identity(a);
    for (int k = 0; k < cols_; ++k) {
        // k is the pivot column.
        // for the pivot column, find the max row index.
        if (const int max_row = find_max_row_for_matrix(a, k); max_row != k) {
            std::swap(a.data_[k], a.data_[max_row]);
            std::swap(identity_matrix.data_[k], identity_matrix.data_[max_row]);
        }
        scale_pivot_column(a, k, identity_matrix);
        zero_out(a, k, identity_matrix);
    }
    return identity_matrix;
}