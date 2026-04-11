//
// Created by Jay on 4/5/2026.
//

#ifndef ML_CPP_MATRIXHELPERS_H
#define ML_CPP_MATRIXHELPERS_H
#include "matrix.h"


int find_max_row_for_matrix(const Matrix& a, int k);
void scale_pivot_column(Matrix& a, int k, Matrix& identity_matrix);
void zero_out(Matrix& a, int k, Matrix& identity_matrix);

#endif //ML_CPP_MATRIXHELPERS_H
