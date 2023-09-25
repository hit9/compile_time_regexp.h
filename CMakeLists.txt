cmake_minimum_required(VERSION 3.10)

project(compile_time_regexp)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(tests)
add_subdirectory(example)

install(FILES compile_time_regexp.h DESTINATION include)
