cmake_minimum_required(VERSION 3.20)
project(ml-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Matplot++ CONFIG REQUIRED)

add_subdirectory(linalg)
add_subdirectory(ols)
add_subdirectory(plots)