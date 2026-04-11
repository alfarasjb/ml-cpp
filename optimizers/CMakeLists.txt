project(optimizers)

add_library(optimizers
    src/gradient_descent.cpp
)

target_include_directories(optimizers PUBLIC include/)
target_link_libraries(optimizers PUBLIC linalg)
target_link_libraries(optimizers PUBLIC ols)
