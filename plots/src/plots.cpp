#include <matplot/matplot.h>


void scatter_with_line(
    const std::vector<double>& X,
    const std::vector<double>& Y,
    const double& slope,
    const double& intercept,
    const std::string& title = ""
    ) {
    matplot::scatter(X, Y);
    // plot the regression line
    // y_pred = slope scalar mul (x feature matrix) + intercept
    const double min_val_x = *std::ranges::min_element(X);
    const double max_val_x = *std::ranges::max_element(X);
    const double y_at_x_min = slope * min_val_x + intercept;
    const double y_at_x_max = slope * max_val_x + intercept;
    matplot::line(min_val_x, y_at_x_min, max_val_x, y_at_x_max);
    matplot::title(title);
    matplot::show();
}