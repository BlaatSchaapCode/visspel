// SPDX-License-Identifier: MIT
#pragma once

#include <cstdint>

namespace types {
typedef uint8_t PlayerID;
typedef uint16_t ShipID;
typedef int32_t Money;
typedef int16_t GridSize;

typedef uint8_t FishCount;
typedef uint8_t OilCount;
enum class TileType : uint8_t {
	Grass,
	ShallowWater,
	DeepWater,
};
} // namespace types
