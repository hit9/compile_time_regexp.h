#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <numeric>
#include <tuple>

#include "compile_time_regexp.hpp"

template <>
struct ctre::_::hash<int> {
  constexpr uint32_t operator()(int v) const {
    return ctre::_::hash<uint32_t>{}(static_cast<uint32_t>(v));
  };
};

TEST_CASE("map", "[map runtime test]") {
  ctre::_::map<int, int> m;
  REQUIRE(m.set(1, 1));
  REQUIRE(m.set(2, 2));
  REQUIRE(m.set(3, 3));
  REQUIRE(m.set(2, 4));  // update
  REQUIRE(m.get(1) == 1);
  REQUIRE(m.get(2) == 4);
  REQUIRE(m.get(3) == 3);
  REQUIRE(m.size() == 3);
}

TEST_CASE("map", "[map compiltime test #1]") {
  auto f = []() constexpr {
    ctre::_::map<int, int> m;
    m.set(1, 1);
    m.set(2, 2);
    m.set(3, 3);
    m.set(2, 4);  // update
    return m.get(2);
  };
  REQUIRE(f() == 4);
}

TEST_CASE("map", "[map compiltime test #2]") {
  auto f = []() constexpr {
    ctre::_::map<int, int> m;
    m.set(1, 1);
    m.set(2, 2);
    m.set(3, 3);
    m.set(2, 4);
    m.pop(2);
    return m.has(2);
  };
  REQUIRE(f() == false);
}

TEST_CASE("map", "[map compiltime test #3]") {
  auto f = []() constexpr {
    ctre::_::map<int, int> m;
    for (auto i = 0; i < 100; i++) m[i] = 100 - i;
    for (auto p : m) {
      auto &[k, v] = p;
      if (k + v != 100) return false;
    }
    return true;
  };
  REQUIRE(f() == true);
}

TEST_CASE("map", "[map compiltime test #4]") {
  auto f = []() constexpr {
    ctre::_::map<int, ctre::_::set<int>> m;
    m[1].add(1);
    m[1].add(2);
    m[1].add(3);

    m[2].add(4);
    m[2].add(5);

    m[3].add(6);
    m[3].add(7);
    m[3].add(8);

    for (auto x : m[1])
      if (x == 0) return false;
    for (auto x : m[3])
      if (x == 0) return false;

    if (!m[1].has(1)) return false;
    if (!m[1].has(2)) return false;
    if (!m[1].has(3)) return false;

    return true;
  };
  REQUIRE(f() == true);
}

TEST_CASE("set", "[test compiltime test #1]") {
  auto f = []() constexpr {
    ctre::_::set<int> a;
    ctre::_::set<int> b{1};

    a.merge(b);

    for (auto i = 10; i < 20; i++) a.add(i);
    if (std::accumulate(a.begin(), a.end(), 0) != 145 + 1) return false;
    return true;
  };
  REQUIRE(f() == true);
}
