//
// Created by Jay on 4/12/2026.
//

#include "matrix.h"
#include "lin_reg.h"
#include "data_gen.h"

int main() {
    try {
        auto [X, Y] = generate_random_data(
        100,
        Matrix({{1.9, 5.3, 2.3}}),
        0.5,
        5,
        0,
        100
    );
        LinReg model;
        model.fit(X, Y);
        model.print_stats();
        // model.plot();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
