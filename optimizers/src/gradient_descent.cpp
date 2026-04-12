//
// Created by Jay on 4/8/2026.
//


#include "gradient_descent.h"
#include <utility>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "plots.h"

std::pair<double, Matrix> GradientDescent::compute_loss_and_gradient() const {
    if (X.cols() != theta.rows()) {
        throw std::runtime_error("Invalid dimensions");
    }
    const Matrix residuals = X * theta - Y;
    // loss
    const double scale_factor = 0.5 / X.rows();
    const double loss = scale_factor * dot(residuals.transpose(), residuals);
    Matrix gradient = X.transpose() * residuals * (1.0 / X.rows());
    return std::make_pair(loss, gradient);
}

void GradientDescent::start() {
    // clear the trace
    trace.clear();
    for (int i = 0; i < max_iters; ++i) {
        auto[loss, grad] = compute_loss_and_gradient();

        // theta is a column vector
        const double bias = theta(0, 0);
        std::vector<double> coefficients;
        for (int j = 1; j < theta.rows(); ++j) {
            coefficients.push_back(theta(j, 0));
        }

        trace.push_back({
            loss,
            coefficients,
            bias
        });

        theta = theta - grad * learning_rate; // update
    }
}

void GradientDescent::plot() const {
    if (trace.empty()) {
        std::cout << "Trace is empty" << std::endl;
        return;
    }
    std::vector<double> losses;
    for (const auto& [loss, coefficients, bias]: trace) {
        losses.push_back(loss);
    }
    plot_loss_curve(losses);
}

void GradientDescent::export_trace_to_csv() const {
    if (X.cols() != 2) {
        std::cout << "export_trace_to_csv only supports single-feature models." << std::endl;
        return;
    }
    if (trace.empty()) {
        std::cout << "Trace is empty" << std::endl;
        return;
    }
    std::cout << "Writing to: " << std::filesystem::absolute("artifacts") << "\n";
    std::filesystem::create_directories("artifacts");
    std::ofstream data_out("artifacts/dataset.csv");
    data_out << std::setprecision(16);
    data_out << "x,y\n";
    // Note: X has prepended ones.
    for (int i = 0; i < X.rows(); ++i) {
        data_out << X(i, 1) << "," << Y(i, 0) << "\n";
    }
    data_out.close();
    std::ofstream out("artifacts/gd_trace.csv");
    out << std::setprecision(16);
    out << "iter,w,b,loss\n";

    int i = 0;
    for (const auto& [loss, coefficient, bias]: trace) {
        // this line will break. ignore for now.
        // there is no point exporting multi feature coefficients.
        out << i++ << "," << coefficient[0] << "," << bias << "," << loss << "\n";
    }
}