// SPDX-License-Identifier: MIT

#include "scene.hpp"
#include <cassert>

namespace window {
void SceneStack::set(std::unique_ptr<BaseScene> scene) {
    assert(scene->m_scene_stack == nullptr);

    m_scene = std::move(scene);
    m_scene->m_scene_stack = this;
}

void SceneStack::clear() { m_scene.reset(); }
} // namespace window