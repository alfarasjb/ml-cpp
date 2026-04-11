#ifndef ML_CPP_PLOTS_H
#define ML_CPP_PLOTS_H

#include <string>
#include <vector>
void scatter_with_line(
    const std::vector<double>& X,
    const std::vector<double>& Y,
    const double& slope,
    const double& intercept,
    const std::string& title = ""
);

void plot_loss_curve(
    const std::vector<double>& losses,
    const std::string& title = "Loss Curve"
);

#endif //ML_CPP_PLOTS_H
