// SPDX-License-Identifier: MIT

#include "point.hpp"

namespace types {
Point &Point::operator+=(const Point &r) {
    x += r.x;
    y += r.y;
    return *this;
}

Point Point::operator+(const Point &r) {
    Point ret(*this);
    ret += r;
    return ret;
}

Point &Point::operator-=(const Point &r) {
    x -= r.x;
    y -= r.y;
    return *this;
}

Point Point::operator-(const Point &r) {
    Point ret(*this);
    ret -= r;
    return ret;
}
} // namespace types