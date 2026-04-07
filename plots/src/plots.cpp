#include <matplot/matplot.h>


void scatter_with_line(
    const std::vector<double>& X,
    const std::vector<double>& Y,
    const double& slope,
    const double& intercept,
    const std::string& title = ""
    ) {
    auto s = matplot::scatter(X, Y);
    s->marker_size(6);
    s->marker_face_color({0.0, 0.45, 0.74});

    const double min_val_x = *std::ranges::min_element(X);
    const double max_val_x = *std::ranges::max_element(X);
    const double y_at_x_min = slope * min_val_x + intercept;
    const double y_at_x_max = slope * max_val_x + intercept;
    auto l = matplot::line(min_val_x, y_at_x_min, max_val_x, y_at_x_max);
    l->color({0.85, 0.2, 0.2});
    l->line_width(2);

    matplot::title(title);
    matplot::xlabel("X");
    matplot::ylabel("Y");
    matplot::grid(true);
    matplot::show();
}