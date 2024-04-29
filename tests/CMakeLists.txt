cmake_minimum_required(VERSION 3.12)
project(compile_time_regexp_test CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories("..")

find_package(Catch2 CONFIG REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-fconstexpr-steps=1000000000)
endif()

# Targets
add_executable(tests simple_test.cc utility_test.cc)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_custom_target(
  runtests
  COMMAND tests
  DEPENDS tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
include(Catch)
catch_discover_tests(tests)
