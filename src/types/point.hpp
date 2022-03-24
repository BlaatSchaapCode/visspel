// SPDX-License-Identifier: MIT
#pragma once

#include "types.hpp"
#include <compare>

namespace types {
struct Point {
    GridSize x = -1;
    GridSize y = -1;

    auto operator<=>(const Point &) const = default;
};
} // namespace types
