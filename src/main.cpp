// SPDX-License-Identifier: MIT

#include "procgen/gamegen.hpp"
#include "utils/version.hpp"
#include "utils/logger.hpp"

#include <iostream>

#include "types/game.hpp"

//#include <cxxopts.hpp>

int main(int argc, char *argv[]) {
    utils::Version version;

    std::cout << "Compiled using " << version.m_compiler_full_name << std::endl;

    std::cout << "Git branch " << version.m_git_branch << " commit " << version.m_git_commit << std::endl;

    types::Game game = procgen::make_game(3);

    std::cout << "Game map size: " << game.map().m_tiles.width() << " x " << game.map().m_tiles.height() << std::endl;
    std::cout << "Number of players: " << game.players().size() << std::endl;
    std::cout << "Number of fish: " << game.map().m_details.count(types::TileObjectType::Fish) << std::endl;
    std::cout << "Number of oil: " << game.map().m_details.count(types::TileObjectType::Oil) << std::endl;

    LOG_INFO("Compiled using %s", version.m_compiler_full_name.c_str());
    LOG_INFO("Git branch %s commit %s", version.m_git_branch.c_str(), version.m_git_commit.c_str());


    std::cout << "press a key to quit";
    std::cin.get();

    return 0;
}
