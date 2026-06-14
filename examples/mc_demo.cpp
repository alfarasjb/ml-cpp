//
// Created by Jay on 4/17/2026.
//

// Smoke test / usage example
//
// Test params: S0=100, K=100, r=0.05, sigma=0.20, T=1.0
// Expected BS call price: ~10.4506
//
// 1. Compute BS closed-form price
// 2. Run serial MC at N=10M, print price + SE, compare to BS
// 3. Run async MC, verify matches serial
// 4. Run pool MC, verify matches serial
// 5. Print all three results side-by-side

#include "black_scholes.h"
#include <iostream>
#include <random>

#include "gbm.h"
#include "payoff.h"
#include <cmath>
int main () {
    constexpr double S_0 = 100;
    constexpr double K = 100;
    constexpr double r = 0.05;
    constexpr double sigma = 0.20;
    constexpr int T = 1;

    const double closed_form_call_price = european_bs_call_price(
        S_0, K, r, sigma, T
    );
    std::cout << "Closed Form Call Price " << closed_form_call_price << std::endl;


    constexpr int n_sims = 100000;
    double total = 0;

    std::mt19937 rng(std::random_device{}());
    std::normal_distribution<double> Z(0.0, 1.0);

    for (int i = 0; i < n_sims; ++i) {

        const double terminal = terminal_price(
            S_0, r, sigma, T, Z(rng)
        );
        std::cout << terminal << std::endl;
        total += payoff(terminal, K);
    }
    const double call_option_value = exp(-r * T) * (total / n_sims);
    std::cout << "Call Option Value " << call_option_value << std::endl;
    return 0;
}
