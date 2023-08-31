#include <catch2/catch_test_macros.hpp>

#include "compile_time_regexp.hpp"

TEST_CASE("Match", "[Compile time match #1]") {
  constexpr auto b1 = ctre::Match<"(a|b)*ab", "abababab">();
  REQUIRE(b1);

  constexpr auto b2 = ctre::Match<"(a|b)*ab", "aaaaaaaaaab">();
  REQUIRE(b2);

  constexpr auto b3 = ctre::Match<"(a|b)*ab", "aaaaaaaaaabc">();
  REQUIRE(!b3);

  constexpr auto b4 = ctre::Match<"(a|b)*ab", "aaaaaaaaaa">();
  REQUIRE(!b4);
}

TEST_CASE("Match", "[Compile time match #2]") {
  constexpr auto b1 = ctre::Match<"a(a|b)*c(d|e)(x|y|z)*", "aabbace">();
  REQUIRE(b1);

  constexpr auto b2 = ctre::Match<"a(a|b)*c(d|e)(x|y|z)*", "aabbbbbbace">();
  REQUIRE(b2);

  constexpr auto b3 = ctre::Match<"a(a|b)*c(d|e)(x|y|z)*", "aabbbbbbad">();
  REQUIRE(!b3);

  constexpr auto b4 = ctre::Match<"a(a|b)*c(d|e)(x|y|z)*", "aabbbbbbaf">();
  REQUIRE(!b4);
}

TEST_CASE("Compile", "[Compile time build and runtime match #1]") {
  constexpr auto d = ctre::Compile<"abab(ab)*cd(e|f)*abc">();
  REQUIRE(d.Size() > 0);
  REQUIRE(d.Match("abababcdeabc"));
  REQUIRE(d.Match("abababcdfabc"));
  REQUIRE(d.Match("ababababababcdfabc"));
  REQUIRE(!d.Match("abababababacdfabc"));
  REQUIRE(!d.Match("abababababacdeabc"));
}

TEST_CASE("Compile", "[Compile time build and runtime match #2]") {
  constexpr auto d = ctre::Compile<"a+b*(c|d)?x+">();
  REQUIRE(d.Size() > 0);
  REQUIRE(d.Match("abcx"));
  REQUIRE(d.Match("abx"));
  REQUIRE(!d.Match("ab"));
  REQUIRE(d.Match("aaabbdxxx"));
}

TEST_CASE("Compile", "[Compile time build and runtime match #3]") {
  constexpr auto d = ctre::Compile<"[a-zA-Z][0-9a-zA-Z]*">();
  REQUIRE(d.Size() > 0);
  REQUIRE(d.Match("abcd12345"));
  REQUIRE(d.Match("name123"));
  REQUIRE(d.Match("name1abac23"));
  REQUIRE(!d.Match("0"));
  REQUIRE(!d.Match("0abcd123"));
  REQUIRE(!d.Match("9123"));
  REQUIRE(!d.Match("abd912!"));
}

TEST_CASE("Compile", "[Compile time build and runtime match #4]") {
  constexpr auto d =
      ctre::Compile<"((\\+|\\-)[0-9])?[0-9]*(([0-9].)|(.[0-9]))?[0-9]*">();
  REQUIRE(d.Size() > 0);
  REQUIRE(d.Match("+31.25"));
  REQUIRE(d.Match("-31.25"));
  REQUIRE(!d.Match("-.25"));
  REQUIRE(!d.Match("-"));
  REQUIRE(d.Match(".123"));
  REQUIRE(d.Match("122."));
  REQUIRE(!d.Match("1.1.1"));
}
