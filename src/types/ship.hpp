// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>

#include "point.hpp"
#include "types.hpp"

namespace types {
struct Map;

class Ship {
  public:
    void start_turn();
    bool move(Map* map, Point delta);
    inline PlayerID player_id() const { return m_player; }
    inline Point pos() const { return m_pos; }
    inline PlayerID player_id() { return m_player; }

  private:
    bool move_check(Map *map, Point new_pos) const;
    void move_enter_tile(Map *map, Point new_pos);

  private:
    PlayerID m_player = 0;
    Point m_pos;
    uint32_t m_fish_count = 0;
    uint32_t m_fish_capacity = 0;
    uint8_t m_speed = 0;
    uint8_t m_steps_this_turn = 0;
};
} // namespace types
