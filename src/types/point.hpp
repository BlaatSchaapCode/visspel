// SPDX-License-Identifier: MIT
#pragma once

#include "types.hpp"
#include <compare>

namespace types {
struct Point {
    GridSize x;
    GridSize y;

    auto operator<=>(const Point &) const = default;
};
} // namespace types
