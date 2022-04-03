// SPDX-License-Identifier: MIT
#pragma once
#include <sdl2/SDL.h>
//#include <sdl2/SDL_image.h>
#include "camera.hpp"

#include "scene.hpp"

namespace window {
// TODO: Should this implement some kind of interface?
class MainWindow {
  public:
    MainWindow();
    ~MainWindow();

    inline void set_scene(std::unique_ptr<BaseScene> scene) { m_scene.set(std::move(scene)); };

    void draw();

  private:
    SceneStack m_scene;
    SDL_Window *mp_window = nullptr;
    SDL_Surface *mp_screen_surface = nullptr;
};
} // namespace window