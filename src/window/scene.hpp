// SPDX-License-Identifier: MIT
#pragma once

#include <memory>
#include <sdl2/SDL.h>

namespace window {
class SceneStack;

class BaseScene {
  public:
    virtual ~BaseScene(){};

    // TODO: Key input
    // TODO: Mouse input
    // TODO: Gamepad input

    virtual void draw(SDL_Surface *p_screen_surface) const = 0;
    virtual void resize(int32_t screen_w, int32_t screen_h) = 0;

  private:
    friend SceneStack;
    SceneStack *m_scene_stack = nullptr;

  protected:
    inline SceneStack *get_scene_stack() { return m_scene_stack; };
};

class SceneStack {
  public:
    void set(std::unique_ptr<BaseScene> scene);
    void clear();

    inline BaseScene *operator->() { return m_scene.get(); }

  private:
    // TODO: This should become a stack with push and pop
    std::unique_ptr<BaseScene> m_scene;
};
} // namespace window