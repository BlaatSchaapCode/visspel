#include "utils/version.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
    utils::Version version;
    std::cout << "Compiled using " << version.m_compiler_full_name << std::endl;
    return 0;
}
