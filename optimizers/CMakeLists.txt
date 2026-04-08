project(optimizers)

add_library(optimizers
    src/optimizers/gradient_descent.cpp
)

target_include_directories(optimizers PUBLIC include/)
target_link_libraries(optimizers PUBLIC linalg)
target_link_libraries(optimizers PUBLIC ols)
add_executable(optimizers_linear_regression_demo examples/linear_regression_demo.cpp)
target_link_libraries(optimizers_linear_regression_demo PRIVATE optimizers)

add_executable(optimizers_loss_surface_demo examples/loss_surface_demo.cpp)
target_link_libraries(optimizers_loss_surface_demo PRIVATE optimizers)

add_executable(optimizers_tests tests/test_gradient_descent.cpp)
target_link_libraries(optimizers_tests PRIVATE optimizers)

add_executable(optimizers_gd_demo examples/gd_demo.cpp)
target_link_libraries(optimizers_gd_demo PRIVATE optimizers)