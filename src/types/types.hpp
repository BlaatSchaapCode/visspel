// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>

namespace types {
typedef uint8_t PlayerID;
typedef uint16_t ShipID;
typedef int32_t Money;
typedef uint16_t GridSize;

enum class TileType : uint8_t {
	Grass,
	ShallowWater,
	DeepWater,
};

enum class TileObjectType : uint8_t {
	None,
	Fish,
	Oil,
};
} // namespace types
