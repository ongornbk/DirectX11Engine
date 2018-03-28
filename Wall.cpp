#include "Walls.h"

#define Z_ZEROF 0.0f

Wall::Wall(float x, float y, int index)
{
	Center.x = x;
	Center.y = y;
	Center.z = Z_ZEROF;

	m_flags[0] = true;
}