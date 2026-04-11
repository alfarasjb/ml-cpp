//
// Created by Jay on 4/6/2026.
//

#ifndef ML_CPP_LINREG_H
#define ML_CPP_LINREG_H
#include "matrix.h"
#include <iostream>

// this should return a model
class LinReg {
protected:
private:
    // these properties will be set AFTER fitting.
    double ssr_ = 0; // sum of squared residuals
    double sst_ = 0; // total sum of squares
    double y_bar_ = 0; // mean of observed data
    bool fitted_ = false;
    Matrix beta_; // coefficients. should be 2x1 matrix where _beta_0 is slope, _beta_1 is intercept
    Matrix y_pred_; // predicted values (we will use this for calculating metrics)
    Matrix X_;
    Matrix Y_;
public:
    [[nodiscard]] double ssr() const { return ssr_; }
    [[nodiscard]] double sst() const { return sst_; }
    [[nodiscard]] double y_bar() const { return y_bar_; }
    [[nodiscard]] Matrix beta() const { return beta_; }
    [[nodiscard]] double slope() const { return beta_(1, 0); }
    [[nodiscard]] double intercept() const { return beta_(0, 0); }
    // fit should call the predict function so we can calculate r_squared.
    // after predicting, we should set ssr and sst. these won't change.
    // everytime the data would change, we would need to call fit, which calls predict
    // which subsequently creates new ssr and sst.
    void fit(const Matrix& X, const Matrix& Y);
    [[nodiscard]] Matrix predict(const Matrix& X) const; // returns predictions from feature matrix
    // calculated only when called
    [[nodiscard]] double r_squared() const;
    LinReg(): beta_(Matrix(0, 0)), y_pred_(Matrix(0, 0)), X_(Matrix(0, 0)), Y_(Matrix(0, 0)) {};
    void print_stats() const {
        std::cout << "R_2: " << r_squared() << std::endl;
        std::cout << "Beta_0: " << beta_(0, 0) << std::endl;
        std::cout << "Beta_1: " << beta_(1, 0) << std::endl;
        std::cout << "SSR: " << ssr_ << std::endl;
        std::cout << "SST: " << sst_ << std::endl;
        beta_.print();
    }
    void plot() const;
};

#endif //ML_CPP_LINREG_H
