// SPDX-License-Identifier: MIT

#include "procgen/gamegen.hpp"
#include "utils/version.hpp"

#include <iostream>

#include "types/game.hpp"

#include "window/renderer/camera.hpp"
#include "window/renderer/sdl_renderer.hpp"

//#include <cxxopts.hpp>

namespace r = window::renderer;

int main(int argc, char *argv[]) {
    utils::Version version;
    std::cout << "Compiled using " << version.m_compiler_full_name << std::endl;

    std::cout << "Git branch " << version.m_git_branch << " commit " << version.m_git_commit << std::endl;

    types::Game game = procgen::make_game(3);

    std::cout << "Game map size: " << game.map().m_tiles.width() << " x " << game.map().m_tiles.height() << std::endl;
    std::cout << "Number of players: " << game.players().size() << std::endl;
    std::cout << "Number of fish: " << game.map().m_details.count(types::TileObjectType::Fish) << std::endl;
    std::cout << "Number of oil: " << game.map().m_details.count(types::TileObjectType::Oil) << std::endl;

    r::SDLRenderer renderer(
        r::Camera(r::CameraConfig{.m_type = r::CameraType::Grid, .m_tile_width = 32, .m_tile_height = 32}, 800, 600));

    renderer.draw(game);

    std::cout << "press a key to quit";
    std::cin.get();

    return 0;
}
