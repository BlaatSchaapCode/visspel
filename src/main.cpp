// SPDX-License-Identifier: MIT

#include "utils/version.hpp"
#include "utils/logger.hpp"

#include <iostream>

//#include <cxxopts.hpp>

int main(int argc, char *argv[]) {
    utils::Version version;
    LOG_INFO("Compiled using %s", version.m_compiler_full_name.c_str());
    LOG_INFO("Git branch %s commit %s", version.m_git_branch.c_str(), version.m_git_commit.c_str());

    std::cout << "press a key to quit";
    std::cin.get();

    return 0;
}
