//
// Created by Jay on 4/8/2026.
//

#include <filesystem>
#include <iostream>
#include <ostream>
#include <utility>
#include <fstream>

#include "matrix.h"
#include "data_gen.h"
#include "gradient_descent.h"
#include "optimizers_helpers.h"
#include "scalers.h"

int main() {
    try {
        auto [X, Y] = generate_random_data(
            100,
            Matrix({{ 1.9 }}),
            0.5,
            15,
            0,
            100
        );
        const Matrix X_scaled = standard_scale(X);
        const Matrix X_prep = prepend_ones(X_scaled);

        constexpr double learning_rate = 0.05;
        constexpr int max_iters = 100;

        GradientDescent optimizer(X_prep, Y, learning_rate, max_iters);

        optimizer.start();
        const Matrix theta_ols = (X_prep.transpose() * X_prep).inverse() * X_prep.transpose() * Y;

        std::cout << "\n=== Results ===\n";
        std::cout << "GD theta:\n";
        optimizer.theta.print();
        std::cout << "OLS theta:\n";
        theta_ols.print();
        optimizer.plot();
        optimizer.export_trace_to_csv();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}