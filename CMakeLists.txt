cmake_minimum_required(VERSION 3.20)
project(ml-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
        GIT_TAG        v1.2.1
        GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(matplotplusplus)

add_subdirectory(linalg)
add_subdirectory(ols)
add_subdirectory(plots)