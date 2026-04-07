//
// Created by Jay on 4/6/2026.
//

#include "../../include/core/LinReg.h"
#include <vector>
#include <cmath>

Matrix prepend_ones(const Matrix& X) {
    Matrix x_aug(X.rows(), X.cols() + 1, 1);
    for (int i = 0; i < x_aug.rows(); ++i) {
        for (int j = 1; j < x_aug.cols(); ++j) {
            // start iterating from column index 1 (second column)
            // since we already have a 1s matrix from instantiation.
            x_aug.data[i][j] = X.data[i][j - 1];
        }
    }
    return x_aug;
}

void LinReg::fit(
    const Matrix& X, // raw feature matrix
    const Matrix& Y //note: this is a column vector
) {
    // reset metrics
    ssr_ = 0;
    sst_ = 0;
    fitted_ = false;
    // goal: calculate beta.
    Matrix X_aug = prepend_ones(X);
    const Matrix X_transposed = X_aug.transpose();
    // this is 2x1 or 1x2 idk
    beta_ = (X_transposed * X_aug).inverse() * X_transposed * Y;

    // calculate metrics
    const Matrix y_row = Y.is_column_vector() ? Y.transpose() : Y;

    // calculate y_bar
    double total = 0.0;
    for (int i = 0; i < y_row.cols(); ++i) {
        total += y_row.data[0][i];
    }
    const double y_bar = total / y_row.cols();

    // predict
    y_pred_ = predict(X_aug); // idk the shape
    for (int i = 0; i < Y.rows(); ++i) {
        const double y_i = Y.data[i][0];
        const double f_i = y_pred_.data[i][0];
        ssr_ += std::pow(y_i - f_i, 2);
        sst_ += std::pow(y_i - y_bar, 2);
    }
    fitted_ = true; // set fitted flag to true
}

Matrix LinReg::predict(const Matrix& X) const {
    Matrix y_hat = X * beta_;
    return y_hat;
}

double LinReg::r_squared() const {
    return 1 - ssr_ / sst_;
}

