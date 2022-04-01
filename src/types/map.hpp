// SPDX-License-Identifier: MIT
#pragma once

#include "grid.hpp"
#include "types.hpp"

namespace types {
struct Map {
    explicit Map(GridSize w, GridSize h);
    Map(Map &&) = default;
    Map &operator=(Map &&) = default;

    Grid<TileType> m_tiles;
    Grid<TileObjectType> m_details;
};
} // namespace types