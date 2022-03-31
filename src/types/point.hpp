// SPDX-License-Identifier: MIT
#pragma once

#include "types.hpp"
#include <compare>

namespace types {
struct Point {
    GridSize x = -1;
    GridSize y = -1;

    auto operator<=>(const Point &) const = default;

    Point &operator+=(const Point &r);
    Point &operator-=(const Point &r);
    Point operator+(const Point &r);
    Point operator-(const Point &r);
};

const static inline Point NULLPOINT = {-0x7f, -0x7f};
} // namespace types
