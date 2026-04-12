// this file should basically just generate some linear dataset

#include <random>

#include "matrix.h"
std::pair<Matrix, Matrix> generate_random_data(
    const int n,
    const double slope,
    const double intercept,
    const double noise_std,
    const double x_min,
    const double x_max,
    const int n_dims = 1
) {
    // seed so numgen is deterministic
    constexpr int seed = 42;
    std::mt19937 rng(seed);
    // create distributions for x to sample, and random noise drawn from normal dist
    std::uniform_real_distribution x_dist(x_min, x_max);
    std::normal_distribution noise(0.0, noise_std);
    Matrix X(n, n_dims);
    Matrix Y(n, n_dims);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n_dims; ++j) {
            X(i, j) = x_dist(rng);
            Y(i, j) = slope * X(i, j) + intercept + noise(rng);
        }
    }
    return { X, Y };
}
