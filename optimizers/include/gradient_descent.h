//
// Created by Jay on 4/8/2026.
//

#ifndef ML_CPP_GRADIENT_DESCENT_H
#define ML_CPP_GRADIENT_DESCENT_H
#include "matrix.h"
#include <utility>


struct GDTrace {
    double loss;
    double slope;
    double intercept;
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
    , max_iters { max_iters } {}

    Matrix theta;

    std::pair<double, Matrix> compute_loss_and_gradient() const;
    void start();
    void plot() const;
    void export_trace_to_csv() const;
};
#endif //ML_CPP_GRADIENT_DESCENT_H
