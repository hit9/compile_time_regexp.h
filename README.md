compile_time_regexp.hpp
=======================

Compile time regular expression.

```cpp
// Runtime DFA build and matching.
ctre::Match("(a|b)*ab", "ababab");

// Compile-time DFA build and matching.
constexpr auto b1 = ctre::Match("(a|b)*ab", "ababab");

// Compile-time DFA build and matching.
auto b2 = ctre::Match<"(a|b)*ab", "ababab">();

// Compile-time DFA build and runtime matching.
auto dfa = ctre::Compile<"(a|b)*ab">();
auto b3 = dfa.Match("ababab");

// Compile-time DFA build and matching.
constexpr auto dfa1 = ctre::Compile<"(a|b)*ab">();
constexpr auto b4 = dfa1.Match("ababab");
```

License
-------

BSD.
