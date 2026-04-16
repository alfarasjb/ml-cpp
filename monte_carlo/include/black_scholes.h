//
// Created by Jay on 4/17/2026.
//

#ifndef ML_CPP_BLACK_SCHOLES_H
#define ML_CPP_BLACK_SCHOLES_H
#include <cmath>
double european_bs_call_price(
    const double S_0,
    const double K,
    const double r,
    const double sigma,
    const int T
    ) {
    auto N = [](const double x) { return 0.5 * erfc(-x / sqrt(2)); };
    const double d1 = log(S_0 / K) + (r + 0.5 * pow(sigma, 2) * T) / (sigma * sqrt(T));
    const double d2 = d1 - sigma * sqrt(T);
    const double call = S_0 * N(d1) - K * exp(-r * T) * N(d2);
    return call;
}

#endif //ML_CPP_BLACK_SCHOLES_H
