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

    LinReg model;
    model.fit(X, Y);
    model.print_stats();
    return 0;
}
