cmake_minimum_required(VERSION 3.10)

project(
  compile_time_regexp
  VERSION 1.0.0
  DESCRIPTION
    "A simple compile time dfa based regular expression library for C++20. ")

option(BUILD_TESTS "Enables testing and builds tests" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(BUILD_TESTS)

  add_subdirectory(tests)
  add_subdirectory(example)
endif()

install(FILES compile_time_regexp.h DESTINATION include)
