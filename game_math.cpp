#include "game_math.h"

int32_t GetXCell(const float x) noexcept

{
	int32_t i = (int32_t)x / MAP_X_CHUNK;
	i += HALF_NUM_OF_DIVIDES_X;
	if (i >= NUM_OF_DIVIDES_X)
	{
		return NUM_OF_DIVIDES_X - 1;
	}
	else
		if (i < 0)
		{
			return 0;
		}
	return i;
}

int32_t GetYCell(const float y) noexcept
{
	int32_t i = (int32_t)y / MAP_Y_CHUNK;
	i += HALF_NUM_OF_DIVIDES_Y;
	if (i >= NUM_OF_DIVIDES_Y)
	{
		return NUM_OF_DIVIDES_Y - 1;
	}
	else
		if (i < 0)
		{
			return 0;
		}
	return i;
}