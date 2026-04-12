// this file should basically just generate some linear dataset

#include <random>

#include "matrix.h"

// Note: when generating random data, we automatically match number of dimensions based on weights.
std::pair<Matrix, Matrix> generate_random_data(
    const int n,
    const Matrix& weights, // slope
    const double intercept,
    const double noise_std,
    const double x_min,
    const double x_max
) {
    if (!weights.is_one_dimensional()) {
        throw std::runtime_error("Weights must be a one-dimensional");
    }
    Matrix weights_calc(weights);
    // transpose weights to a row vector?
    if (weights_calc.is_column_vector()) {
        weights_calc = weights_calc.transpose();
    }
    const int n_dims = weights_calc.cols();
    // seed so numgen is deterministic
    constexpr int seed = 42;
    std::mt19937 rng(seed);
    // create distributions for x to sample, and random noise drawn from normal dist
    std::uniform_real_distribution x_dist(x_min, x_max);
    std::normal_distribution noise(0.0, noise_std);
    Matrix X(n, n_dims);
    Matrix Y(n, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n_dims; ++j) {
            X(i, j) = x_dist(rng);
        }
    }
    // Y = X * weights^T + intercept + noise
    Y = X * weights_calc.transpose();
    for (int i = 0; i < n; ++i) {
        Y(i, 0) = Y(i, 0) + intercept + noise(rng);
    }
    return { X, Y };
}
