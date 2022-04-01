// SPDX-License-Identifier: MIT
#pragma once

namespace procgen::random {
bool bernoulli(double p);
double uniform_real(double max = 1.0);
double uniform_real(double min, double max);
}