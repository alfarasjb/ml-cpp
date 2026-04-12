cmake_minimum_required(VERSION 3.20)
project(ml-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Matplot++ CONFIG REQUIRED)

add_subdirectory(linalg)
add_subdirectory(ols)
add_subdirectory(plots)
add_subdirectory(optimizers)

add_executable(linalg_example examples/linalg_example.cpp)
target_link_libraries(linalg_example PRIVATE linalg)

add_executable(ols_example examples/ols_example.cpp)
target_link_libraries(ols_example PRIVATE ols optimizers)

add_executable(plots_example examples/plots_example.cpp)
target_link_libraries(plots_example PRIVATE plots)

add_executable(gd_demo examples/gd_demo.cpp)
target_link_libraries(gd_demo PRIVATE optimizers)

add_executable(multi_linreg_example examples/multi_linreg_example.cpp)
target_link_libraries(multi_linreg_example PRIVATE ols optimizers)