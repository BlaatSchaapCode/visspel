// SPDX-License-Identifier: MIT
#pragma once

#include "../types/point.hpp"
#include <optional>
#include <tuple>

namespace window {

enum class CameraType { Isometric, Grid };

struct CameraConfig {
    CameraType m_type;
    int32_t m_tile_width, m_tile_height;
};

class Camera {
  public:
    Camera(CameraConfig config, int32_t screen_w, int32_t screen_h);

    void resize(int32_t screen_w, int32_t screen_h);
    void center_on(types::Point p);
    std::pair<int32_t, int32_t> translate(types::Point p) const;
    types::Point translate_inv(int32_t x, int32_t y) const;

    const CameraConfig m_config;
    int32_t m_screen_x, m_screen_y;
    int32_t m_screen_w, m_screen_h;
};
} // namespace window::renderer