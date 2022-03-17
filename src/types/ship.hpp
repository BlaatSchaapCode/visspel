// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>

#include "point.hpp"
#include "types.hpp"

namespace types {
class Ship {
    PlayerID m_player = 0;
    Point m_pos;
    uint32_t m_fish_count = 0;
    uint32_t m_fish_capacity = 0;
    uint8_t m_speed = 0;
    uint8_t m_steps_this_turn = 0;

  public:
    void catch_fish(uint32_t *count);
    void start_turn();
    bool move(Point new_pos);
};
} // namespace types
