#include <matplot/matplot.h>

void demo_plot() {
    using namespace matplot;
    auto x = linspace(0, 2 * pi, 100);
    auto y = transform(x, [](double v) { return std::sin(v); });
    plot(x, y);
    title("Sin(x) - POC");
    show();
}

void scatter_with_line(std::vector<double> X, std::vector<double> Y, double slope, double intercept) {
    matplot::scatter(X, Y);
    // plot the regression line
    // y_pred = slope scalar mul (x feature matrix) + intercept
    const double min_val_x = *std::ranges::min_element(X);
    const double max_val_x = *std::ranges::max_element(X);
    const double y_at_x_min = slope * min_val_x + intercept;
    const double y_at_x_max = slope * max_val_x + intercept;
    matplot::line(min_val_x, y_at_x_min, max_val_x, y_at_x_max);
    matplot::show();
}