// SPDX-License-Identifier: MIT

#include "camera.hpp"

namespace t = types;

namespace window {

Camera::Camera(CameraConfig config, int32_t screen_w, int32_t screen_h) : m_config(config) { resize(screen_w, screen_h); }

void Camera::resize(int32_t screen_w, int32_t screen_h) {
    m_screen_x += (screen_w - m_screen_w) / 2;
    m_screen_y += (screen_h - m_screen_h) / 2;

    m_screen_w = screen_w;
    m_screen_h = screen_h;
}

void Camera::center_on(types::Point p) {
    auto [x, y] = translate(p);

    m_screen_x = x - m_screen_w / 2;
    m_screen_y = y - m_screen_h / 2;
}

std::pair<int32_t, int32_t> Camera::translate(t::Point p) const {
    int32_t x, y;
    if (m_config.m_type == CameraType::Grid) {
        x = p.x * m_config.m_tile_width;
        y = p.y * m_config.m_tile_height;
    } else {
        x = (p.x + p.y) * m_config.m_tile_width / 2;
        y = (p.x - p.y) * m_config.m_tile_height / 2;
        // TODO: Implement
    }

    return {x - m_screen_x, y - m_screen_y};
}
t::Point Camera::translate_inv(int32_t mouse_x, int32_t mouse_y) const {
    mouse_x += m_screen_x;
    mouse_y += m_screen_y;

    if (m_config.m_type == CameraType::Grid) {
        if (mouse_x < 0 || mouse_y < 0)
            return t::NULLPOINT;

        int32_t x = mouse_x / m_config.m_tile_width;
        int32_t y = mouse_y / m_config.m_tile_height;

        return {(t::GridSize)x, (t::GridSize)y};
    } else {
        return t::NULLPOINT; // TODO: Fix
    }
}
} // namespace window::renderer