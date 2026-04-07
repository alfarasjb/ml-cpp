add_library(plots
        src/plots.cpp
)

target_include_directories(plots PUBLIC include)
target_link_libraries(plots PUBLIC Matplot++::matplot)

add_executable(plots_example examples/main.cpp)
target_link_libraries(plots_example PRIVATE plots)
