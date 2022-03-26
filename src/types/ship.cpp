// SPDX-License-Identifier: MIT

#include "ship.hpp"
#include <algorithm>
#include <cassert>

#include "map.hpp"

namespace types {

void Ship::start_turn() { m_steps_this_turn = m_speed; }

bool Ship::move(Map *map, Point delta) {
    Point new_pos = m_pos + delta;
    if (!move_check(map, new_pos))
        return false;

    move_enter_tile(map, new_pos);
    return true;
}

bool Ship::move_check(Map *map, Point new_pos) const {
    auto &tile = map->m_tiles[new_pos];
    if (tile == TileType::Grass)
        return false;

    uint8_t cost = 1;
    return m_steps_this_turn < cost;
}

void Ship::move_enter_tile(Map *map, Point new_pos) {
    m_steps_this_turn--;
    m_pos = new_pos;

    auto &detail = map->m_details[new_pos];

    if (detail == TileObjectType::Fish && m_fish_count < m_fish_capacity) {
        detail = TileObjectType::None;
        m_fish_count++;
        // TODO: Play catch fish sound
    }
}
} // namespace types
