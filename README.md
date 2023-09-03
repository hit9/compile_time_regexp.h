compile_time_regexp.hpp
=======================

Compile time regular expression for C++20.

```cpp
// Compile-time DFA build and runtime matching.
constexpr auto dfa = ctre::Compile<"(a|b)*ab">();
auto b = dfa.Match("ababab");

// Runtime DFA build and matching.
auto b1 = ctre::Match("(a|b)*ab", "ababab");

// Compile-time DFA build and matching.
// Compile faster than: ctre::Compile<pattern>().Match(s);
constexpr auto b2 = ctre::Match("(a|b)*ab", "ababab");

// Compile-time DFA build and matching.
auto b3 = ctre::Match<"(a|b)*ab", "ababab">();
```

License
-------

BSD.
