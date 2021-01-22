cmake_minimum_required(VERSION 3.11)
project(redis_l)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(util_test/cpp)
add_subdirectory(util_test/thread_info)
add_subdirectory(plugins/jemalloc)
add_subdirectory(redis)
