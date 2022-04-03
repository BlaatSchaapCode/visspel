// SPDX-License-Identifier: MIT
#pragma once
#include <type_traits>
#include <memory>

#include "scene.hpp"

#include "camera.hpp"
#include <sdl2/SDL.h>

#include "../types/game.hpp"

namespace types {
class Game;
struct Map;
class Ship;
struct Player;
} // namespace types

namespace window {
class GameScene : public BaseScene {
  public:
    GameScene(types::Game game);
    ~GameScene();

    void draw(SDL_Surface *p_screen_surface) const override;
    void resize(int32_t screen_w, int32_t screen_h) override;

  private:
    void draw_map(SDL_Surface *p_screen_surface, const types::Map &map) const;
    void draw_ship(SDL_Surface *p_screen_surface, const types::Ship &ship, const types::Player &player) const;

  private:
    Camera m_camera;
    types::Game m_game;
    SDL_Surface *mp_tileset = nullptr;
};

static_assert(!std::is_abstract<GameScene>(), "GameScene doen't implement all virtual functions");
} // namespace window