//
// Created by Jay on 4/8/2026.
//

#include <iostream>
#include <ostream>

#include "core/Matrix.h"
#include <utility>

#include "plots.h"
#include "core/data_gen.h"

// todo: clean this up later. prepend_ones already exists in linear regression library
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
std::pair<double, Matrix> compute_loss_and_gradient(
    const Matrix& X, const Matrix& y, const Matrix& theta
) {

    const Matrix residuals = X * theta - y;
    // loss
    double loss = 0.5 * dot(residuals.transpose(), residuals);
    Matrix gradient = X.transpose() * residuals;
    return std::make_pair(loss, gradient);
}
double column_mean(const Matrix& X, int col) {
    double sum = 0.0;
    for (int i = 0; i < X.rows(); ++i) sum += X(i, col);
    return sum / X.rows();
}

double column_std(const Matrix& X, int col, double mean) {
    double sq_sum = 0.0;
    for (int i = 0; i < X.rows(); ++i) {
        double diff = X(i, col) - mean;
        sq_sum += diff * diff;
    }
    return std::sqrt(sq_sum / X.rows());  // population std, not sample
}

Matrix standard_scale(const Matrix& X) {
    Matrix X_scaled(X.rows(), X.cols());
    for (int j = 0; j < X.cols(); ++j) {
        double mu = column_mean(X, j);
        double sigma = column_std(X, j, mu);
        for (int i = 0; i < X.rows(); ++i) {
            X_scaled(i, j) = (X(i, j) - mu) / sigma;
        }
    }
    return X_scaled;
}

int main() {
    auto [X, Y] = generate_random_data(
        100,
        1.9,
        0.5,
        1,
        0,
        100
    );
    Matrix X_scaled = standard_scale(X);
    Matrix X_prep = prepend_ones(X_scaled);
    Matrix theta(X_prep.cols(), 1, 0.0);
    const double learning_rate = 0.001;
    const int max_iters = 100;
    std::vector<double> losses;
    for (int i = 0; i < max_iters; ++i) {
        auto [loss, grad] = compute_loss_and_gradient(X_prep, Y, theta);
        losses.push_back(loss);
        theta = theta - grad * learning_rate;
        std::cout << "Loss " << loss << std::endl;
    }
    Matrix theta_ols = (X_prep.transpose() * X_prep).inverse() * X_prep.transpose() * Y;

    std::cout << "\n=== Results ===\n";
    std::cout << "GD theta:\n";
    theta.print();
    std::cout << "OLS theta:\n";
    theta_ols.print();
    plot_loss_curve(losses);

    return 0;
}