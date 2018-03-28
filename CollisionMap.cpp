#include "CollisionMap.h"

#define TILE_MAP_RANGE (TILE_MAP_SIZE -1)

inline void squash(int &value) noexcept
{

	if (value > TILE_MAP_RANGE)
	{
		value = TILE_MAP_RANGE;
		return;
	}
	if (value < 0)
	{
		value = 0;
		return;
	}
}

inline bool check(int &value) noexcept
{
	if (value > TILE_MAP_RANGE)
	{
		return false;
	}
	if (value < 0)
	{
		return false;
	}
	return true;
}

CollisionMap::CollisionMap()
{
}


CollisionMap::~CollisionMap()
{
}

void CollisionMap::Flush(XMFLOAT3 flush)
{
	float ip = 16.0f, jp = 16.0f;
	int ipi, sji, tilex, tiley;
	ip += flush.x / 40.0f;
	ip -= flush.y / 20.0f;
	ipi = (int)ip * 4;
	if (!check(ipi)) return;
	jp -= flush.x / 40.0f;
	jp -= flush.y / 20.0f;
	sji = (int)jp * 4;
	if (!check(sji)) return;
	tilex = (int)ip % 4;
	tiley = (int)jp % 4;
	m_tiles[sji][ipi].tile[tiley][tilex] = false;
}

bool CollisionMap::Alloc(XMFLOAT3 alloc)
{
	
	float ip = 16.0f, jp = 16.0f;
	int ipi ,sji,tilex,tiley;
	ip += alloc.x / 40.0f;
	ip -= alloc.y / 20.0f;
	ipi = (int)ip*4;
	if (!check(ipi)) return true;
	jp -= alloc.x / 40.0f;
	jp -= alloc.y / 20.0f;
	sji = (int)jp*4;
	if (!check(sji)) return true;
	tilex = (int)ip % 4;
	tiley = (int)jp % 4;
	if (!m_tiles[sji][ipi].tile[tiley][tilex])
	{
		return false;
	}
	else
	{
		m_tiles[sji][ipi].tile[tiley][tilex] = true;
		return true;
	}
	




}
