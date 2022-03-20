// SPDX-License-Identifier: MIT

#include <cstdint>
#include <iostream>
#include <string>

#include <cxxopts.hpp>

#include "network/network.hpp"
#include "utils/version.hpp"

int parse_options(int argc, char *argv[]) {
    try {
        cxxopts::Options options("Visspel", "A fishing game");

        options.add_options()("s,server", "Start as server");
        options.add_options()("c,client", "Start as client");

        //		options.add_options() ("4,ipv4", "IPv4 only");
        //		options.add_options() ("6,ipv6", "IPv6 only");

        options.add_options()("h,host", "Host to connect to", cxxopts::value<std::string>());
        options.add_options()("p,port", "Port to connect to", cxxopts::value<uint16_t>());

        auto result = options.parse(argc, argv);

        if (result["server"].as<bool>()) {
            std::cout << "Server requested" << std::endl;

            network::listen(result["port"].as<uint16_t>());
        }

        if (result["client"].as<bool>()) {
            std::cout << "Client requested" << std::endl;
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
    std::cout << "Compiled using " << version.m_compiler_full_name << std::endl;
    std::cout << "Git branch " << version.m_git_branch << " commit " << version.m_git_commit << std::endl;

    network::init();

    result = parse_options(argc, argv);
    if (result)
        return result;

    std::cout << "press enter to quit" << std::endl;
    std::cin.get();


    network::deinit();

    return 0;
}
