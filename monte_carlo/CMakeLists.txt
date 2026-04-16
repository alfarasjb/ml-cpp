project(monte_carlo)

add_library(monte_carlo
        src/black_scholes.cpp
        src/gbm.cpp
        src/mc_serial.cpp
        src/mc_async.cpp
        src/thread_pool.cpp
        src/mc_pool.cpp)

target_include_directories(monte_carlo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
