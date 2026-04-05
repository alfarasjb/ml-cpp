project(linalg)

add_library(linalg INTERFACE)
target_include_directories(linalg INTERFACE include/)

add_executable(linalg_example examples/main.cpp)
target_link_libraries(linalg_example PRIVATE linalg)