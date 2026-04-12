//
// Created by Jay on 4/11/2026.
//

#include <matrix.h>
#include <optimizers_helpers.h>

Matrix standard_scale(const Matrix& X) {
    // note: matrix is never empty. check is done in instantiation.
    Matrix X_scaled(X.rows(), X.cols());
    for (int j = 0; j < X.cols(); ++j) {
        const double mu = column_mean(X, j);
        const double sigma = column_std(X, j, mu);
        if (sigma == 0) {
            throw std::runtime_error("Error. Column Standard Deviation is 0.");
        }
        for (int i = 0; i < X.rows(); ++i) {
            X_scaled(i, j) = (X(i, j) - mu) / sigma;
        }
    }
    return X_scaled;
}