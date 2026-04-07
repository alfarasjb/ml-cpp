project(ols)
add_library(ols
    src/core/LinReg.cpp src/core/data_gen.cpp
)
target_include_directories(ols PUBLIC include/)
add_executable(ols_example examples/main.cpp)
target_link_libraries(ols_example PRIVATE ols)
target_link_libraries(ols PUBLIC linalg)
target_link_libraries(ols PUBLIC plots)