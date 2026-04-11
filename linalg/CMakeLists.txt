project(linalg)

add_library(linalg
        src/matrix.cpp
        src/matrix_helpers.cpp)


add_executable(linalg_tests tests/test_matrix.cpp)
target_link_libraries(linalg_tests PRIVATE linalg)
target_include_directories(linalg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)