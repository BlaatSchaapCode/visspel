// SPDX-License-Identifier: MIT
#pragma once
#include <sdl2/include/SDL.h>
//#include <sdl2/include/SDL_image.h>
#include "camera.hpp"

namespace types {
class Game;
struct Map;
class Ship;
struct Player;
} // namespace types

namespace window::renderer {
// TODO: Should this implement some kind of interface?
class SDLRenderer {
  public:
    SDLRenderer(Camera camera);
    ~SDLRenderer();

    void draw(const types::Game &game);
    void draw_map(const types::Map &map);
    void draw_ship(const types::Ship &ship, const types::Player &player);

  private:
    Camera m_camera;
    SDL_Window *m_window = nullptr;
    SDL_Surface *m_screen_surface = nullptr;
    SDL_Surface *m_tileset = nullptr;
};
} // namespace window::renderer