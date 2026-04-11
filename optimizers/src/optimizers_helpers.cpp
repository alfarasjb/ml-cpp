//
// Created by Jay on 4/11/2026.
//
#include <matrix.h>
Matrix prepend_ones(const Matrix& X) {
    Matrix x_aug(X.rows(), X.cols() + 1, 1);
    for (int i = 0; i < x_aug.rows(); ++i) {
        for (int j = 1; j < x_aug.cols(); ++j) {
            // start iterating from column index 1 (second column)
            // since we already have a 1s matrix from instantiation.
            x_aug(i, j) = X(i, j - 1);
        }
    }
    return x_aug;
}


double column_mean(const Matrix& X, const int col) {
    double sum = 0.0;
    for (int i = 0; i < X.rows(); ++i) sum += X(i, col);
    return sum / X.rows();
}

double column_std(const Matrix& X, const int col, const double mean) {
    double sq_sum = 0.0;
    for (int i = 0; i < X.rows(); ++i) {
        double diff = X(i, col) - mean;
        sq_sum += diff * diff;
    }
    return std::sqrt(sq_sum / X.rows());  // population std, not sample
}
