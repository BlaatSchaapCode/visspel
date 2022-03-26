// SPDX-License-Identifier: MIT
#pragma once

#include "types.hpp"
#include "grid.hpp"

namespace types {
struct Map {
    explicit Map(GridSize w, GridSize h);
    Map(Map&&) = default;
    Map &operator=(Map&&) = default;

    Grid<FishCount> m_fish;
    Grid<OilCount> m_oil;
    Grid<TileType> m_tiles;
};
} // namespace types