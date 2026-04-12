//
// Created by Jay on 4/12/2026.
//

#include "matrix.h"
#include "lin_reg.h"
#include "data_gen.h"
#include "gradient_descent.h"
#include "optimizers_helpers.h"
#include "scalers.h"

int main() {
    try {
        auto [X, Y] = generate_random_data(
        100,
        // lmao linreg basically tries to guess this.
        Matrix({{1.9, 5.3, 2.3}}),
        0.5,
        5,
        0,
        100
    );
        LinReg model;
        model.fit(X, Y);
        model.print_stats();
        // model.plot();

        // GD
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
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
