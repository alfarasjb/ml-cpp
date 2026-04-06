//
// Created by Jay on 4/6/2026.
//

#include "../../include/core/LinReg.h"
#include <vector>
#include <cmath>

Matrix prepend_ones(Matrix& X) {
    Matrix x_aug(X.rows, X.cols + 1, 1);
    for (int i = 0; i < x_aug.rows; ++i) {
        for (int j = 1; j < x_aug.cols; ++j) {
            // start iterating from column index 1 (second column)
            // since we already have a 1s matrix from instantiation.
            x_aug.data[i][j] = X.data[i][j - 1];
        }
    }
    return x_aug;
}

void LinReg::fit(
    Matrix& X, // raw feature matrix
    Matrix& Y //note: this is a column vector
) {
    // goal: calculate beta.
    Matrix X_aug = prepend_ones(X);
    Matrix X_transposed = X_aug.transpose();
    // this is 2x1 or 1x2 idk
    _beta = (X_transposed * X_aug).inverse() * X_transposed * Y;

    // calculate metrics
    Matrix y_row = Y.IsColumnVector() ? Y.transpose() : Y;

    // calculate y_bar
    double total = 0.0;
    for (int i = 0; i < y_row.cols; ++i) {
        total += y_row.data[0][i];
    }
    double y_bar = total / y_row.cols;

    // predict
    _y_pred = predict(X_aug); // idk the shape
    for (int i = 0; i < Y.rows; ++i) {
        const double y_i = Y.data[i][0];
        const double f_i = _y_pred.data[i][0];
        _ssr += std::pow(y_i - f_i, 2);
        _sst += std::pow(y_i - y_bar, 2);
    }
    fitted = true; // set fitted flag to true
}

Matrix LinReg::predict(Matrix& X) {
    Matrix y_hat = X * _beta;
    return y_hat;
}

double LinReg::r_squared() const {
    return 1 - _ssr / _sst;
}

