//
// Created by Jay on 4/6/2026.
//

#include "matrix.h"
#include "lin_reg.h"
#include "data_gen.h"

// TODO: Put this in unit tests
// Matrix X({
//     {1},
//     {2},
//     {3},
//     {4}
// });
// Matrix Y({
//     {3.2},
//     {4.8},
//     {7.3},
//     {8.7}
// });
// // verified with python
// // beta_0 (intercept) = 1.25
// // beta_1 (slope) = 1.9
// // R_2 = 0.988499
// // SSR = 0.21
// // SST = 18.26
// // verified with numpy/sklearn:
// // beta_0 (intercept) ≈ 0.5048
// // beta_1 (slope)     ≈ 1.8407
// // R²                 ≈ 0.9979
// // SSR                ≈ 1.7548
// // SST                ≈ 838.336

int main() {

    auto [X, Y] = generate_random_data(
        100,
        Matrix({{1.9}}),
        0.5,
        5,
        0,
        100
    );
    LinReg model;
    model.fit(X, Y);
    model.print_stats();
    model.plot();
    return 0;
}
