// SPDX-License-Identifier: MIT

#include "gamegen.hpp"
#include "random.hpp"

#include <algorithm>
#include <cmath>

namespace t = types;

namespace procgen {
static void add_player(t::Game *game) {
    // TODO: Add players
    // TODO: Add player harbours
    // TODO: Add player ships
}

t::Game make_game(types::PlayerID player_count) {
    const double water_tiles_per_player = 200;
    const double perc_water = 0.9;
    const double border_size = 1.5;

    const double num_tiles = water_tiles_per_player / perc_water * player_count;
    const t::GridSize width = (t::GridSize)std::round(std::sqrt(num_tiles) + 2 * border_size);
    const t::GridSize height = width;

    t::Map map{width, height};

    for (size_t i = 0; i < map.m_tiles.size(); ++i) {
        t::Point pos = map.m_tiles.index_inverse(i);
        auto &tile = map.m_tiles[pos];
        auto &detail = map.m_details[pos];
        t::GridSize border_distance = static_cast<t::GridSize>(std::min({pos.x + 1, pos.y + 1, width - pos.x, height - pos.y}));

        if (border_distance < border_size + random::uniform_real()) {
            tile = t::TileType::Grass;
        } else if (border_distance < border_size + 1 + random::uniform_real()) {
            tile = t::TileType::ShallowWater; // TODO: Water should be placed around the landmass as a post-processing.
                                              // This works better when adding islands later, I guess.
        } else {
            tile = t::TileType::DeepWater;
            if (random::bernoulli(0.1))
                detail = t::TileObjectType::Fish;
        }
    }

    t::Game game{std::move(map)};
    for (int i = 0; i < player_count; ++i)
        add_player(&game); // TODO: Should this be called here or should this be a separate function?

    return game;
}
} // namespace procgen