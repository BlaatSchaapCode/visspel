// SPDX-License-Identifier: MIT
#pragma once

#include "types.hpp"
#include <compare>

namespace types {
struct Point {
    GridSize x = UINT16_MAX;
    GridSize y = UINT16_MAX;

    auto operator<=>(const Point &) const = default;

    Point &operator+=(const Point &r);
    Point &operator-=(const Point &r);
    Point operator+(const Point &r);
    Point operator-(const Point &r);
};

const static inline Point NULLPOINT = {UINT16_MAX, UINT16_MAX};
} // namespace types
