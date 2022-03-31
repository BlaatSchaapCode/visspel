// SPDX-License-Identifier: MIT
#pragma once

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
    void draw(const types::Game &game);
    void draw_map(const types::Map &map);
    void draw_ship(const types::Ship &ship, const types::Player &player);

  private:
    Camera m_camera;
};
} // namespace window::renderer