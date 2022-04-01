// SPDX-License-Identifier: MIT
#pragma once

#include "types.hpp"
#include <compare>

namespace types {
struct Point {
    GridSize x = ~0;
    GridSize y = ~0;

    auto operator<=>(const Point &) const = default;

    Point &operator+=(const Point &r);
    Point &operator-=(const Point &r);
    Point operator+(const Point &r);
    Point operator-(const Point &r);
};

const static inline Point NULLPOINT = {~0, ~0};
} // namespace types
