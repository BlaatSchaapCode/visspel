#include "game.hpp"

namespace types {
ShipID Game::add_ship(Ship ship) {
    ShipID ship_id = m_shipid_autoincrement++;
    add_ship(ship_id, std::move(ship));
    return ship_id;
}

void Game::add_ship(ShipID ship_id, Ship ship) {
    PlayerID player_id = ship.player_id();
    m_ships[ship_id] = std::move(ship);
    // TODO: Check player_id's
    m_players[player_id].m_ships.push_back(ship_id);
}

void Game::start_turn() {
    for (auto& [id,ship] : m_ships) {
        ship.start_turn();
    }
}
}; // namespace types
