#pragma once
#include "Defines.h"
#include "Sprite.h"
#include "Types.h"



#define TILE_MAP_RANGE TILE_MAP_SIZE -1

extern "C"
{
	extern void _vectorcall InitializeTemplates();
	extern void SetCellMultiplier(float multiplier = 1.0f);
}

#pragma region
class Tile;
class RendererManager;
#pragma endregion

struct TileMap
{
	TileMap();
	~TileMap();
	void Initialize();
	void _vectorcall Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,XMVECTOR cameraPosition);
	Tile* map[TILE_MAP_SIZE][TILE_MAP_SIZE];
};

class Tile
{
public:
	Tile(float x,float y,int ix,int iy);
	~Tile();

	static void SetGlobals(ID3D11Device* device, Shader* shader,RendererManager* renderer);
	static void SetVolatileGlobals(ID3D11DeviceContext * deviceContex, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	
	 void Update();
	 void Render();
private:
	void LoadTexture();
	XMFLOAT4X4 m_world;
	INDEX2     m_index;
};

