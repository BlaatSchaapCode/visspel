// SPDX-License-Identifier: MIT

#include "game_scene.hpp"

#include "../types/game.hpp"
#include "../types/map.hpp"
#include "../types/player.hpp"
#include "../types/ship.hpp"

namespace window {
GameScene::GameScene(types::Game game)
    : m_camera(CameraConfig{.m_type = CameraType::Grid, .m_tile_width = 32, .m_tile_height = 32}, 800, 600),
      m_game(std::move(game)) {

    const char *image_name = "tileset.png";
    mp_tileset = SDL_LoadBMP(image_name); // TODO: Use SDL_Image to load a png
    if (mp_tileset == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", image_name, SDL_GetError());
    }
}
GameScene::~GameScene() {
    // Deallocate surface
    SDL_FreeSurface(mp_tileset);
    mp_tileset = nullptr;
}
void GameScene::draw(SDL_Surface *p_screen_surface) const {
    SDL_BlitSurface(mp_tileset, NULL, p_screen_surface, NULL);

    draw_map(p_screen_surface, m_game.map());
    for (auto &[shipID, ship] : m_game.ships())
        draw_ship(p_screen_surface, ship, m_game.players()[ship.player_id()]);
}

void GameScene::resize(int32_t screen_w, int32_t screen_h) { m_camera.resize(screen_w, screen_h); }

void GameScene::draw_map(SDL_Surface *p_screen_surface, const types::Map &map) const {
    // TODO: Only render the part that is needed
    for (types::GridSize map_y = 0; map_y < map.m_tiles.height(); ++map_y) {
        for (types::GridSize map_x = 0; map_x < map.m_tiles.width(); ++map_x) {
            auto [screen_x, screen_y] = m_camera.translate(types::Point{map_x, map_y});

            auto tile = map.m_tiles[{map_x, map_y}];
            //SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);


            // TODO: Render
        }
    }
}

void GameScene::draw_ship(SDL_Surface *p_screen_surface, const types::Ship &ship, const types::Player &player) const {
    auto [screen_x, screen_y] = m_camera.translate(ship.pos());

    // TODO: Render ship
    // TODO: Render sail
}
} // namespace window
