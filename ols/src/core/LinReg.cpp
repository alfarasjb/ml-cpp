//
// Created by Jay on 4/6/2026.
//

#include "../../include/core/LinReg.h"
#include <vector>
#include <cmath>
#include <matplot/matplot.h>
#include <iostream>
#include <ranges>
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
        total += y_row(0, i);
    }
    const double y_bar = total / y_row.cols();

    // predict
    y_pred_ = predict(X_aug); // idk the shape
    for (int i = 0; i < Y.rows(); ++i) {
        const double y_i = Y(i, 0);
        const double f_i = y_pred_(i, 0);
        ssr_ += std::pow(y_i - f_i, 2);
        sst_ += std::pow(y_i - y_bar, 2);
    }
    X_ = X;
    Y_ = Y;
    fitted_ = true; // set fitted flag to true
}

Matrix LinReg::predict(const Matrix& X) const {
    Matrix y_hat = X * beta_;
    return y_hat;
}

double LinReg::r_squared() const {
    return 1 - ssr_ / sst_;
}

void LinReg::plot() {
    // todo: clean this up
    // scatter x vs y true
    // convert to row vector?
    Matrix X_row(X_);
    Matrix Y_row(Y_);
    // we might need a separate VECTOR type/class
    if (X_.is_column_vector()) {
        X_row = X_.transpose();
    }
    if (Y_.is_column_vector()) {
        Y_row = Y_.transpose();
    }
    std::cout << "XRow \n";
    X_row.print();
    matplot::scatter(X_row.data()[0], Y_row.data()[0]);

    // plot the regression line
    // y_pred = slope scalar mul (x feature matrix) + intercept
    const double min_val_x = *std::ranges::min_element(X_row.data()[0]);
    const double max_val_x = *std::ranges::max_element(X_row.data()[0]);
    const double y_at_x_min = slope() * min_val_x + intercept();
    const double y_at_x_max = slope() * max_val_x + intercept();
    matplot::line(min_val_x, y_at_x_min, max_val_x, y_at_x_max);
    matplot::show();
}