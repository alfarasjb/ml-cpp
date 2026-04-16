//
// Created by Jay on 4/17/2026.
//

#ifndef ML_CPP_PAYOFF_H
#define ML_CPP_PAYOFF_H
#include <algorithm>
double payoff(const double S_t, const double K) {
    return std::max(S_t, K);
}
#endif //ML_CPP_PAYOFF_H
