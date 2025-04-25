#pragma once

namespace type_holes {
struct Hole {
  template <typename T> operator T() { throw "unreachable"; }
};
constexpr auto _ = Hole{};
constexpr auto hole = Hole{};
} // namespace type_holes