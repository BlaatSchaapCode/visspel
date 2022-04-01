// SPDX-License-Identifier: MIT
#pragma once

#include <string>
#include <vector>

#include "types.hpp"

namespace types {
struct Player {
    std::string m_name;
    Money m_money = 0;
    std::vector<ShipID> m_ships;
};
} // namespace types
