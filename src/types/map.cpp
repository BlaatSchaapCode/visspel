// SPDX-License-Identifier: MIT
#include "map.hpp"

namespace types {
types::Map::Map(GridSize w, GridSize h) : m_details(w,h), m_tiles(w,h) {
}
} // namespace types
