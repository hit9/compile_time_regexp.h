cmake_minimum_required(VERSION 3.10)
project(compile_time_regexp_example CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("..")

# Targets
add_executable(example example.cc)
target_link_libraries(example)
