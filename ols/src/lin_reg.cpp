//
// Created by Jay on 4/6/2026.
//

#include "lin_reg.h"
#include <vector>
#include <cmath>

#include "plots.h"

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
    // validation
    if (X.rows() != Y.rows()) throw std::invalid_argument("X and Y must have the same number of rows");
    if (X.rows() == 0 || X.cols() == 0) throw std::invalid_argument("X must not be empty");
    if (!Y.is_vector()) throw std::invalid_argument("Y must be a column vector");
    // reset metrics
    ssr_ = 0;
    sst_ = 0;
    fitted_ = false;
    // goal: calculate beta.
    Matrix X_aug = prepend_ones(X);
    const Matrix X_transposed = X_aug.transpose();
    // this is 2x1
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
    y_pred_ = predict(X_aug);
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
    // nice to have: abstract this into some wrapper.
    Matrix y_hat = X * beta_;
    return y_hat;
}

double LinReg::r_squared() const {
    if (!fitted_) {
        throw std::runtime_error("Model has not been fitted.");
    }
    return 1 - ssr_ / sst_;
}

void LinReg::plot() const {
    if (!fitted_) {
        throw std::runtime_error("Model has not been fitted.");
    }
    if (!X_.is_vector()) {
        // only for single linear regression.
        throw std::runtime_error("Only Nx1 Matrix is allowed.");
    }
    // scatter x vs y true
    // convert to row vector?
    const std::vector<double> X_row = X_.as_vector();
    const std::vector<double> Y_row = Y_.as_vector();
    const std::string title = "Linear Regression with R2 " + std::to_string(r_squared());
    scatter_with_line(X_row, Y_row, slope(), intercept(), title);
}