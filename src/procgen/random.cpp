// SPDX-License-Identifier: MIT
#include "random.hpp"
#include <random>

namespace procgen::random {
static std::mt19937 make_rng() {
    std::random_device os_rng;
    return std::mt19937(os_rng());
}

thread_local std::mt19937 g_rng = make_rng();

bool bernoulli(double p) {
    std::bernoulli_distribution distribution(p);
    return distribution(g_rng);
}

double uniform_real(double max) {
    std::uniform_real_distribution<double> distribution(0.0, max);
    return distribution(g_rng);
}

double uniform_real(double min, double max) {
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(g_rng);
}
} // namespace procgen::random