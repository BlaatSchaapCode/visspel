// SPDX-License-Identifier: MIT
#include "sdl_renderer.hpp"

#include "../../types/game.hpp"
#include "../../types/map.hpp"
#include "../../types/player.hpp"
#include "../../types/ship.hpp"

// #include "../../utils/logger.cpp"

namespace window::renderer {

SDLRenderer::SDLRenderer(Camera camera) : m_camera(camera) {
    // TODO: Use exceptions instead of only logging errors

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // TODO: Log correctly
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    m_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_camera.m_screen_w,
                                m_camera.m_screen_h, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    m_screen_surface = SDL_GetWindowSurface(m_window);

    const char *image_name = "tileset.png";
    m_tileset = SDL_LoadBMP(image_name); // TODO: Use SDL_Image to load a png
    if (m_tileset == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", image_name, SDL_GetError());
    }
}

SDLRenderer::~SDLRenderer() {
    // Deallocate surface
    SDL_FreeSurface(m_tileset);
    m_tileset = nullptr;

    // Destroy window
    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void SDLRenderer::draw(const types::Game &game) {
    SDL_FillRect(m_screen_surface, NULL, SDL_MapRGB(m_screen_surface->format, 0xFF, 0xFF, 0xFF));

    SDL_BlitSurface(m_tileset, NULL, m_screen_surface, NULL);

    draw_map(game.map());
    for (auto &[shipID, ship] : game.ships())
        draw_ship(ship, game.players()[ship.player_id()]);

    SDL_UpdateWindowSurface(m_window);
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

    // TODO: Render
}
} // namespace window::renderer