//
// Created by Jay on 4/8/2026.
//

#ifndef ML_CPP_GRADIENT_DESCENT_H
#define ML_CPP_GRADIENT_DESCENT_H
#include "matrix.h"
#include <utility>


struct GDTrace {
    double loss;
    std::vector<double> coefficients;
    double bias;
};

class GradientDescent {
    Matrix X;
    Matrix Y;

    double learning_rate;
    int max_iters;
    std::vector<GDTrace> trace;
public:
    GradientDescent(const Matrix& X, const Matrix& Y, const double learning_rate, const int max_iters)
    : X { X }
    , Y { Y }
    , theta { Matrix(X.cols(), 1, 0.0) }
    , learning_rate { learning_rate }
    , max_iters { max_iters } {
        if (X.rows() != Y.rows()) {
            throw std::runtime_error("Feature space and label space shape do not match.");
        }
        if (!Y.is_column_vector()) {
            throw std::runtime_error("Label space needs to be a column vector.");
        }
        if (learning_rate <= 0 || max_iters <= 0) {
            throw std::runtime_error("Learning rate and Num iters must be greater than zero.");
        }
    }

    Matrix theta;

    std::pair<double, Matrix> compute_loss_and_gradient() const;
    void start();
    void plot() const;
    void export_trace_to_csv() const;
};
#endif //ML_CPP_GRADIENT_DESCENT_H
