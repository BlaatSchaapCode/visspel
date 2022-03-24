// SPDX-License-Identifier: MIT

#include "utils/version.hpp"

#include <iostream>

#include "types/game.hpp"

//#include <cxxopts.hpp>

int main(int argc, char *argv[]) {
    utils::Version version;
    std::cout << "Compiled using " << version.m_compiler_full_name << std::endl;

    std::cout << "Git branch " << version.m_git_branch << 
			" commit " << version.m_git_commit  << std::endl;; 

    types::Game game{20,20,4};

    std::cout << "press a key to quit";
    std::cin.get();

    return 0;
}
