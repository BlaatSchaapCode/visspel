#include "map.hpp"

namespace types {
types::Map::Map(GridSize w, GridSize h) : m_fish(w,h), m_oil(w,h), m_tiles(w,h) {
}
} // namespace types
