//
// Created by Jay on 4/5/2026.
//

#include "../../include/core/MatrixHelpers.h"
#include <stdexcept>
#include "../../include/core/Matrix.h"

Matrix identity_matrix(const Matrix& a) {
    // check if nxn. if not, throw error.
    if (!a.IsSquareMatrix()) {
        throw std::runtime_error("Not a square matrix.");
    }
    Matrix identity_matrix_a(a.rows, a.cols, 0);
    // size is already equal here.
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            if (i == j) {
                identity_matrix_a.data[i][j] = 1.0;
            }
        }
    }
    return identity_matrix_a;
}

int find_max_row_for_matrix(const Matrix& a, const int k) {
    int max_row = k;
    for (int i = k + 1; i < a.rows; ++i) {
        if (std::abs(a.data[i][k]) > std::abs(a.data[max_row][k])) {
            max_row = i;
        }
    }
    return max_row;
}

void scale_pivot_column(Matrix& a, const int k, Matrix& identity_matrix) {
    // scale the pivot column and row(k)
    // get the value at that coordinate
    // divide the whole row to get to 1
    const double scale_factor = a.data[k][k];

    for (int i = 0; i < a.cols; ++i) {
        a.data[k][i] /= scale_factor;
        identity_matrix.data[k][i] /= scale_factor;
    }
}

void zero_out(Matrix& a, const int k, Matrix& identity_matrix) {
    // for the pivot column, iterate through the remaining rows.
    // get the value for that row for the pivot column
    // multiply it by the scaled value then subtract to that row.
    for (int i = 0; i < a.rows; ++i) {
        if (i == k) {
            // do not zero out the diagonal lol
            continue;
        }
        const double factor = a.data[i][k];
        for (int j = 0; j < a.cols; ++j) {
            a.data[i][j] -= factor * a.data[k][j];
            identity_matrix.data[i][j] -= factor * identity_matrix.data[k][j];
        }
    }
}