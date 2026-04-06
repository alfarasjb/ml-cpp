project(linalg)

add_library(linalg
        src/core/Matrix.cpp
        src/core/MatrixHelpers.cpp)

add_executable(linalg_example examples/main.cpp)
target_link_libraries(linalg_example PRIVATE linalg)

add_executable(linalg_tests tests/test_matrix.cpp)
target_link_libraries(linalg_tests PRIVATE linalg)
target_include_directories(linalg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)