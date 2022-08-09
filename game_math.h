#pragma once
#include <cstdint>
#include "modern/modern_def.h"

#define TILE_MAP_SIZE 256
#define RENDER_CELLS_RANGE 1
#define MAP_DIVISION 64
#define NUM_OF_DIVIDES_X MAP_DIVISION
#define NUM_OF_DIVIDES_Y MAP_DIVISION
#define HALF_NUM_OF_DIVIDES_X (NUM_OF_DIVIDES_X / 2)
#define HALF_NUM_OF_DIVIDES_Y (NUM_OF_DIVIDES_Y / 2)
#define HALF_MAP_SIZE (TILE_MAP_SIZE / 2.0f)
#define MAP_Y_CHUNK (TILE_MAP_SIZE) / NUM_OF_DIVIDES_Y
#define MAP_X_CHUNK (TILE_MAP_SIZE) / NUM_OF_DIVIDES_X

#define TEXT_DEFAULT_FONT 20.f

int32_t GetXCell(const float x) modern_except_state;
int32_t GetYCell(const float y) modern_except_state;