//
// Created by Jay on 4/8/2026.
//

#include <filesystem>
#include <iostream>
#include <ostream>

#include "core/Matrix.h"
#include <utility>

#include "plots.h"
#include "core/data_gen.h"
#include <fstream>
#include <iomanip>

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
    double scale_factor = 0.5 / X.rows();
    double loss = scale_factor * dot(residuals.transpose(), residuals);
    Matrix gradient = X.transpose() * residuals * (1.0 / X.rows());
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
        15,
        0,
        100
    );
    Matrix X_scaled = standard_scale(X);
    Matrix X_prep = prepend_ones(X_scaled);
    Matrix theta(X_prep.cols(), 1, 0.0);

    theta.print();
    const double learning_rate = 0.05;
    const int max_iters = 100;
    std::vector<double> losses;
    std::cout << "Writing to: " << std::filesystem::absolute("artifacts") << "\n";
    std::filesystem::create_directories("artifacts");
    std::ofstream data_out("artifacts/dataset.csv");
    data_out << std::setprecision(16);
    data_out << "x,y\n";
    for (int i = 0; i < X_scaled.rows(); ++i) {
        data_out << X_scaled(i, 0) << "," << Y(i, 0) << "\n";
    }
    data_out.close();


    std::ofstream out("artifacts/gd_trace.csv");
    out << std::setprecision(16);
    out << "iter,w,b,loss\n";



    for (int i = 0; i < max_iters; ++i) {
        auto [loss, grad] = compute_loss_and_gradient(X_prep, Y, theta);
        losses.push_back(loss);
        double intercept = theta(0, 0);
        double slope = theta(1, 0);

        out << i << "," << slope << "," << intercept << "," << loss << "\n";
        theta = theta - grad * learning_rate;
        // needs an assertion somewhere. but for the sake of generating the artifact, this is ok.

        std::cout << "iter " << i << " Loss " << loss << std::endl;
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