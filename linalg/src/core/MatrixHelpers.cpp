//
// Created by Jay on 4/5/2026.
//

#include "../../include/core/MatrixHelpers.h"
#include <stdexcept>
#include "../../include/core/Matrix.h"

int find_max_row_for_matrix(const Matrix& a, const int k) {
    int max_row = k;
    for (int i = k + 1; i < a.rows(); ++i) {
        if (std::abs(a(i, k)) > std::abs(a(max_row, k))) {
            max_row = i;
        }
    }
    return max_row;
}

void scale_pivot_column(Matrix& a, const int k, Matrix& identity_matrix) {
    // scale the pivot column and row(k)
    // get the value at that coordinate
    // divide the whole row to get to 1
    const double scale_factor = a(k, k);
    if (std::abs(scale_factor) < 1e-10) {
        throw std::runtime_error("Matrix is singular or near singular.");
    }
    for (int i = 0; i < a.cols(); ++i) {
        a(k, i) /= scale_factor;
        identity_matrix(k, i) /= scale_factor;
    }
}

void zero_out(Matrix& a, const int k, Matrix& identity_matrix) {
    // for the pivot column, iterate through the remaining rows.
    // get the value for that row for the pivot column
    // multiply it by the scaled value then subtract to that row.
    for (int i = 0; i < a.rows(); ++i) {
        if (i == k) {
            // do not zero out the diagonal lol
            continue;
        }
        const double factor = a(i, k);
        for (int j = 0; j < a.cols(); ++j) {
            a(i, j) -= factor * a(k, j);
            identity_matrix(i, j) -= factor * identity_matrix(k, j);
        }
    }
}