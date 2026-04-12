project(ols)
add_library(ols
    src/lin_reg.cpp src/data_gen.cpp
)
target_include_directories(ols PUBLIC include/)
target_link_libraries(ols PUBLIC linalg)
target_link_libraries(ols PUBLIC plots)
target_link_libraries(ols PUBLIC optimizers)