#pragma once
#include "Defines.h"
#include <directxcollision.h>
#include <vector>

using namespace DirectX;
using std::vector;

struct Wall : BoundingBox
{
	Wall(float x, float y, int index);

	bool m_flags[1];
};

class Walls
{
public:
	Walls();
	~Walls();

private:

	vector<vector<Wall*>> m_walls;
};

