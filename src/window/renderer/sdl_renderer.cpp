// SPDX-License-Identifier: MIT
#include "sdl_renderer.hpp"
#include <sdl2/include/SDL.h>

#include "../../types/game.hpp"
#include "../../types/ship.hpp"
#include "../../types/map.hpp"
#include "../../types/player.hpp"

namespace window::renderer {

void SDLRenderer::draw(const types::Game &game) {
    draw_map(game.map());
    for (auto& [shipID, ship] : game.ships())
        draw_ship(ship, game.players()[ship.player_id()]);
}

void SDLRenderer::draw_map(const types::Map &map) {
    // TODO: Only render the part that is needed
    for (types::GridSize map_y = 0; map_y < map.m_tiles.height(); ++map_y) {
        for (types::GridSize map_x = 0; map_x < map.m_tiles.width(); ++map_x) {
            auto [screen_x, screen_y] = m_camera.translate(types::Point{map_x, map_y});
            // TODO: Render
        }
    }
}

void SDLRenderer::draw_ship(const types::Ship &ship, const types::Player &player) {

    auto [screen_x, screen_y] = m_camera.translate(ship.pos());
    // TODO: Implement
}
} // namespace window::renderer