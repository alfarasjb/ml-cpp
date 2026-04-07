#include <matplot/matplot.h>

void demo_plot() {
    using namespace matplot;
    auto x = linspace(0, 2 * pi, 100);
    auto y = transform(x, [](double v) { return std::sin(v); });
    plot(x, y);
    title("Sin(x) - POC");
    show();
}
