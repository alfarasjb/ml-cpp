//
// Created by Jay on 4/6/2026.
//

#ifndef ML_CPP_LINREG_H
#define ML_CPP_LINREG_H
#include "../../linalg/include/core/Matrix.h"
#include <iostream>

// this should return a model
class LinReg {
protected:
private:
    // these properties will be set AFTER fitting.
    double _ssr = 0; // sum of squared residuals
    double _sst = 0; // total sum of squares
    double _y_bar = 0; // mean of observed data
    bool fitted = false;
    Matrix _beta; // coefficients. should be 2x1 matrix where _beta_0 is slope, _beta_1 is intercept
    Matrix _y_pred; // predicted values (we will use this for calculating metrics)
public:
    double ssr() const { return _ssr; }
    double sst() const { return _sst; }
    double y_bar() const { return _y_bar; }
    Matrix beta() const { return _beta; }
    // fit should call the predict function so we can calculate r_squared.
    // after predicting, we should set ssr and sst. these won't change.
    // everytime the data would change, we would need to call fit, which calls predict
    // which subsequently creates new ssr and sst.
    void fit(Matrix& X, Matrix& Y);
    Matrix predict(Matrix& X); // returns predictions from feature matrix
    // calculated only when called
    double r_squared() const;
    LinReg(): _beta(Matrix(0, 0)), _y_pred(Matrix(0, 0)) {};
    void print_stats() const {
        std::cout << "R_2: " << r_squared() << std::endl;
        std::cout << "Beta_0: " << _beta.data[0][0] << std::endl;
        std::cout << "Beta_1: " << _beta.data[1][0] << std::endl;
        std::cout << "SSR: " << _ssr << std::endl;
        std::cout << "SST: " << _sst << std::endl;
        _beta.print();
    }
};

#endif //ML_CPP_LINREG_H
