//
// Created by Jay on 4/11/2026.
//

#include <matrix.h>
#include <optimizers_helpers.h>

Matrix standard_scale(const Matrix& X) {
    Matrix X_scaled(X.rows(), X.cols());
    for (int j = 0; j < X.cols(); ++j) {
        const double mu = column_mean(X, j);
        const double sigma = column_std(X, j, mu);
        for (int i = 0; i < X.rows(); ++i) {
            X_scaled(i, j) = (X(i, j) - mu) / sigma;
        }
    }
    return X_scaled;
}