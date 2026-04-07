//
// Created by Jay on 4/6/2026.
//

#include "../../linalg/include/core/Matrix.h"
#include "../../ols/include/core/LinReg.h"

int main() {
    Matrix X({
        {1},
        {2},
        {3},
        {4}
    });
    Matrix Y({
        {3.2},
        {4.8},
        {7.3},
        {8.7}
    });
    // verified with python
    // beta_0 (intercept) = 1.25
    // beta_1 (slope) = 1.9
    // R_2 = 0.988499
    // SSR = 0.21
    // SST = 18.26
//
//     Matrix X({
//     {1.0}, {2.0}, {3.0}, {4.0}, {5.0},
//     {6.0}, {7.0}, {8.0}, {9.0}, {10.0},
//     {11.0}, {12.0}, {13.0}, {14.0}, {15.0}
// });
//     Matrix Y({
//         {2.8}, {4.1}, {6.5}, {7.2}, {10.1},
//         {11.8}, {12.9}, {15.4}, {16.7}, {19.2},
//         {20.1}, {22.8}, {24.3}, {25.9}, {28.4}
//     });

    // verified with numpy/sklearn:
    // beta_0 (intercept) ≈ 0.5048
    // beta_1 (slope)     ≈ 1.8407
    // R²                 ≈ 0.9979
    // SSR                ≈ 1.7548
    // SST                ≈ 838.336

    LinReg model;
    model.fit(X, Y);
    model.print_stats();
    model.plot();
    return 0;
}
