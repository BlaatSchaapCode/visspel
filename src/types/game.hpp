// SPDX-License-Identifier: MIT
#pragma once

#include <vector>
#include <unordered_map>
#include <span>

#include "types.hpp"
#include "map.hpp"
#include "player.hpp"
#include "ship.hpp"

namespace types {
class Game {
public:
    Game(Map map);

    ShipID add_ship(Ship);
    void add_ship(ShipID, Ship);
    void start_turn();

    const Map &map() const { return m_map; }
    std::span<Player> players() { return m_players; }
    std::span<const Player> players() const { return m_players; }

    // TODO: I would like to change this function syntax to return a range
    const std::unordered_map<ShipID, Ship> ships() const { return m_ships; };

private:
    Map m_map;
    std::vector<Player> m_players;
    std::unordered_map<ShipID, Ship> m_ships;

    ShipID m_shipid_autoincrement = 0;
};
} // namespace types