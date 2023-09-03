#include <iostream>

#include "compile_time_regexp.hpp"

int main(void) {
  // Compile-time DFA build.
  constexpr auto dfa = ctre::Compile<"(a|b)*ab">();
  // Runtime matching.
  auto b = dfa.Match("ababab");

  // Runtime DFA build and matching.
  auto b1 = ctre::Match("(a|b)*ab", "ababab");

  // Compile-time DFA build and matching.
  // Compile faster than: ctre::Compile<pattern>().Match(s);
  constexpr auto b2 = ctre::Match("(a|b)*ab", "ababab");

  // Compile-time DFA build and matching.
  auto b3 = ctre::Match<"(a|b)*ab", "ababab">();

  // All true.
  std::cout << std::boolalpha << b << b1 << b2 << b3 << std::endl;
  return 0;
}
