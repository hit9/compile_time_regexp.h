cmake_minimum_required(VERSION 3.10)
project(compile_time_regexp_test CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("..")

# Find or Download package Catch 2
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # or a later release
  GIT_PROGRESS TRUE
  FIND_PACKAGE_ARGS NAMES Catch2)

FetchContent_MakeAvailable(Catch2)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-fconstexpr-steps=1000000000)
endif()

# Targets
add_executable(tests simple_test.cc utility_test.cc)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
