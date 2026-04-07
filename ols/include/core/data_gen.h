//
// Created by Jay on 4/7/2026.
//

#ifndef ML_CPP_DATA_GEN_H
#define ML_CPP_DATA_GEN_H
#include "core/Matrix.h"
std::pair<Matrix, Matrix> generate_random_data(
    int n,
    double slope,
    double intercept,
    double noise_std,
    double x_min,
    double x_max
);
#endif //ML_CPP_DATA_GEN_H
