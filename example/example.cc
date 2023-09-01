#include <iostream>

#include "compile_time_regexp.hpp"

int main(void) {
  //  // Runtime DFA build and matching.
  //  std::cout << ctre::Match("(a|b)*ab", "ababab") << std::endl;
  //
  //  // Compile-time DFA build and matching.
  //  constexpr auto b1 = ctre::Match("(a|b)*ab", "ababab");
  //  std::cout << b1 << std::endl;
  //
  //  // Compile-time DFA build and matching.
  //  auto b2 = ctre::Match<"(a|b)*ab", "ababab">();
  //  std::cout << b2 << std::endl;
  //
  // Compile-time DFA build and runtime matching.
  auto dfa = ctre::Compile<"(a|b)*ab">();
  auto b3 = dfa.Match("ababab");
  std::cout << b3 << std::endl;

  //  // Compile-time DFA build and matching.
  //  constexpr auto dfa1 = ctre::Compile<"(a|b)*ab">();
  //  constexpr auto b4 = dfa1.Match("ababab");
  //  std::cout << b4 << std::endl;
  return 0;
}
