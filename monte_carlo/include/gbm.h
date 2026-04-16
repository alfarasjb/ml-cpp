//
// Created by Jay on 4/17/2026.
//

#ifndef ML_CPP_GBM_H
#define ML_CPP_GBM_H
#include <cmath>

// not path dependent
double terminal_price(
    const double S_0,
    const double r,
    const double sigma,
    const int T,
    const double Z) {
    // S_0 initial stock price
    // r drift
    // sigma volatility
    // T period
    // Z drawn from a standard normal dist
    return S_0 * exp((r - 0.5 * pow(sigma, 2)) * T + sigma * sqrt(T) * Z);
}
#endif //ML_CPP_GBM_H
