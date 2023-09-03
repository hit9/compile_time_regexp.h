compile_time_regexp.hpp
=======================

Simple compile time DFA based regular expression for C++20.

Source
-----

Single header file - [compile_time_regexp.hpp](compile_time_regexp.hpp), without dependencies.

Tested compilers, with flag `-std=c++20`:

- clang 16+
- gcc 13+

Example
-------

```cpp
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
```

Supported Syntax
----------------

- `ab` matches `ab`.
- `a|b` matches `a` or `b`.
- `a*` matches 0 or more `a`.
- `a+` matches 1 or more `a`.
- `a?` matches 0 or 1 `a`.
- `[0-9a-z]` matches characters in some ranges.
- `(a|b)*` parentheses to force priority

For instance, `(a|b)*ab` matches `ababab`.

Run tests
---------

```bash
cmake -S . -B build
make -C build
./build/tests/tests
```


Internal Brief
--------------

Three main steps:

- `NfaParser` - Parse a given pattern string to NFA via dijkstra two stack algorithm.
- `DfaBuilder` - Build a DFA from given NFA via [subset-construction](https://en.wikipedia.org/wiki/Powerset_construction).
- `DfaMinifier` - Minify a DFA to an equivalent DFA that has a minimum number of states via [hopcroft alogrithm](https://en.wikipedia.org/wiki/DFA_minimization#Hopcroft's_algorithm).

Chinese blog, 中文博客 - [实现一个简单的正则表达式引擎](https://writings.sh/post/regexp)

License
-------

BSD.
