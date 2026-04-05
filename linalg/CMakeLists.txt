project(linalg)

add_library(linalg src/core/Matrix.cpp)
target_include_directories(linalg PUBLIC include/)

add_executable(linalg_example examples/main.cpp)
target_link_libraries(linalg_example PRIVATE linalg)