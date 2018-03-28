#pragma once
#include "RendererManager.h"

#ifndef TILE_MAP_SIZE 
#define TILE_MAP_SIZE 128
#endif // ! TILE_MAP_SIZE 


class CollisionMap
{
private:
	struct TileCollision
	{
		TileCollision()
		{
			for(int i=0;i<4;i++)
				for (int g = 0; g<4; g++)
					tile[i][g] = false;
		}
		bool tile[4][4];
	};
public:
	CollisionMap();
	~CollisionMap();

	void Flush(XMFLOAT3 flush);
	bool Alloc(XMFLOAT3 alloc);

private:
	TileCollision m_tiles[TILE_MAP_SIZE][TILE_MAP_SIZE];
};

