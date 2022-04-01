// SPDX-License-Identifier: MIT

// C++ Library Includes
#include <cstdint>
#include <iostream>
#include <string>

// Library Includes
#include <cxxopts.hpp>

// Game includes
#include "network/network.hpp"
#include "procgen/gamegen.hpp"
#include "types/game.hpp"
#include "utils/logger.hpp"
#include "utils/version.hpp"

int parse_options(int argc, char *argv[]) {
    try {
        cxxopts::Options options(*argv, "A fishing game");

        options.add_options()("h,help", "Display help");

        options.add_options()("s,server", "Start as server");
        options.add_options()("c,client", "Start as client");

        //		options.add_options() ("4,ipv4", "IPv4 only");
        //		options.add_options() ("6,ipv6", "IPv6 only");

        options.add_options()("H,host", "Host to connect to", cxxopts::value<std::string>()->default_value("127.0.0.1"));
        options.add_options()("p,port", "Port to connect to/listen on", cxxopts::value<uint16_t>()->default_value("1234"));

        auto result = options.parse(argc, argv);

        if (result["help"].as<bool>()) {
            std::cout << options.help();
            return 0;
        }

        if (result["server"].as<bool>()) {
            std::cout << "Server requested" << std::endl;
            network::listen(result["port"].as<uint16_t>());
        }

        if (result["client"].as<bool>()) {
            std::cout << "Client requested" << std::endl;
            network::connect(result["host"].as<std::string>(), result["port"].as<uint16_t>());
        }
        return 0;
    } catch (const cxxopts::OptionException &e) {
        // Error parsing the command line
        std::cout << "Failed to parse command line options" << std::endl;
        std::cout << e.what() << std::endl;
        return -1;
    }
}

int main(int argc, char *argv[]) {
    int result;
    utils::Version version;

    network::init();

    result = parse_options(argc, argv);
    if (result)
        return result;

    types::Game game = procgen::make_game(3);

    LOG_INFO(" Game map size:    %2dx%2d", game.map().m_tiles.width(), game.map().m_tiles.height());
    LOG_INFO(" Number of players %d", game.players().size());
    LOG_INFO(" Number of fish    %d", game.map().m_details.count(types::TileObjectType::Fish));
    LOG_INFO(" Number of oil:    %d", game.map().m_details.count(types::TileObjectType::Oil));

    LOG_INFO("Compiled using %s", version.m_compiler_full_name.c_str());
    LOG_INFO("Git branch %s commit %s", version.m_git_branch.c_str(), version.m_git_commit.c_str());

    LOG_INFO(" "press a key to quit");
    std::cin.get();

    network::deinit();

    return 0;
}
