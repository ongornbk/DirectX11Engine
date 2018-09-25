#include "CollisionMap.h"
#include "IPP.h"

#define TILE_MAP_RANGE (TILE_MAP_SIZE -1)





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
	if (!ipp::math::range(ipi,0,TILE_MAP_RANGE)) return;
	jp -= flush.x / 40.0f;
	jp -= flush.y / 20.0f;
	sji = (int)jp * 4;
	if (!ipp::math::range(sji, 0, TILE_MAP_RANGE)) return;
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
	if (!ipp::math::range(ipi, 0, TILE_MAP_RANGE)) return true;
	jp -= alloc.x / 40.0f;
	jp -= alloc.y / 20.0f;
	sji = (int)jp*4;
	if (!ipp::math::range(sji, 0, TILE_MAP_RANGE)) return true;
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
