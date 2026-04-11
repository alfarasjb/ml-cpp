project(optimizers)

add_library(optimizers
    src/gradient_descent.cpp src/optimizers_helpers.cpp src/scalers.cpp
        include/optimizers_helpers.h include/scalers.h
)

target_include_directories(optimizers PUBLIC include/)
target_link_libraries(optimizers PUBLIC linalg)
target_link_libraries(optimizers PUBLIC ols)
