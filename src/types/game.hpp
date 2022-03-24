// SPDX-License-Identifier: MIT
#pragma once

#include <unordered_map>

#include "types.hpp"
#include "map.hpp"
#include "player.hpp"
#include "ship.hpp"

namespace types {
class Game {
    Map m_map;
    std::vector<Player> m_players;
    std::unordered_map<ShipID, Ship> m_ships;

    ShipID m_shipid_autoincrement = 0;

public:
    Game(GridSize w, GridSize h, PlayerID player_count);

    ShipID add_ship(Ship);
    void add_ship(ShipID, Ship);
    void start_turn();
};
} // namespace types