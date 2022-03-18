// SPDX-License-Identifier: MIT

#include "ship.hpp"
#include <algorithm>

namespace types {
void Ship::catch_fish(uint32_t *count) {
    uint32_t catch_count = std::min(*count, m_fish_capacity - m_fish_count);
    m_fish_count += catch_count;
    *count -= catch_count;
}

void Ship::start_turn() { m_steps_this_turn = m_speed; }

bool Ship::move(Point new_pos) {
    uint8_t cost = 1;

    if (m_steps_this_turn < cost)
        return false;

    m_steps_this_turn--;
    m_pos = new_pos;
    return true;
}
} // namespace types
