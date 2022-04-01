// SPDX-License-Identifier: MIT
#pragma once
#include <algorithm>
#include <cassert>
#include <concepts>
#include <memory>
#include <span>

#include "point.hpp"
#include "types.hpp"

namespace types {
template <std::regular T> class Grid {
  public:
    explicit Grid(GridSize w, GridSize h, T value = {}) : m_width(w), m_height(h) {
        assert(w > 0 && h > 0);
        m_elems = std::make_unique<T[]>(w * h);
        for (auto &elem : span())
            elem = value;
    }

    GridSize width() const { return m_width; }
    GridSize height() const { return m_height; }

    T operator[](Point p) const { return m_elems[index(p)]; }
    T &operator[](Point p) { return m_elems[index(p)]; }

    size_t index(Point p) const {
        assert(p.x >= 0 && p.y >= 0 && p.x < m_width && p.y < m_height);
        return static_cast<size_t>(p.x) + static_cast<size_t>(p.y) * static_cast<size_t>(m_width);
    }
    Point index_inverse(size_t s) const {
        assert(s < m_width * m_height);
        return {static_cast<GridSize>(s % m_width), static_cast<GridSize>(s / m_width)};
    }

    // TODO: Unittests

    size_t count(T value) const {
        return std::ranges::count_if(span(), [value](T obj) { return obj == value; });
    }
    size_t size() const { return static_cast<size_t>(m_width) * static_cast<size_t>(m_height); }
    std::span<const T> span() const { return std::span(&m_elems[0], size()); }
    std::span<T> span() { return std::span(&m_elems[0], size()); }

    // TODO: Add iter() and iter_mut() functions when c++ supports coroutines well.
    // Currently (C++20), there is cppcoro::generator but that should have been part of the stl.

  private:
    GridSize m_width, m_height;
    std::unique_ptr<T[]> m_elems;
};
} // namespace types