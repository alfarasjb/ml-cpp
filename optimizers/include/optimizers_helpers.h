//
// Created by Jay on 4/11/2026.
//

#ifndef ML_CPP_OPTIMIZERS_HELPERS_H
#define ML_CPP_OPTIMIZERS_HELPERS_H

#include <matrix.h>

Matrix prepend_ones(const Matrix& X);

// TODO: Move these into matrix class
double column_mean(const Matrix& X, int col);
double column_std(const Matrix& X, int col, double mean);
#endif //ML_CPP_OPTIMIZERS_HELPERS_H
