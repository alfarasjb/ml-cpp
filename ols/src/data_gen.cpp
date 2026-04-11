// this file should basically just generate some linear dataset

#include <random>

#include "matrix.h"
std::pair<Matrix, Matrix> generate_random_data(
    const int n,
    const double slope,
    const double intercept,
    const double noise_std,
    const double x_min,
    const double x_max
) {
    // seed so numgen is deterministic
    constexpr int seed = 42;
    std::mt19937 rng(seed);
    // create distributions for x to sample, and random noise drawn from normal dist
    std::uniform_real_distribution x_dist(x_min, x_max);
    std::normal_distribution noise(0.0, noise_std);
    Matrix X(n, 1);
    Matrix Y(n, 1);
    for (int i = 0; i < n; ++i) {
        X(i, 0) = x_dist(rng);
        Y(i, 0) = slope * X(i, 0) + intercept + noise(rng);
    }
    return { X, Y };
}
