#include "utils/version.hpp"

#include <iostream>

#include <cxxopts.hpp>

int main(int argc, char *argv[]) {
    utils::Version version;
    std::cout << "Compiled using " << version.m_compiler_full_name << std::endl;

    std::cout << "Git branch " << version.m_git_branch << 
			" commit " << version.m_git_commit  << std::endl;; 

    return 0;
}
