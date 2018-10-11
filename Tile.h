#pragma once
#include "Defines.h"
#include "Sprite.h"
#include "Types.h"



#define TILE_MAP_RANGE TILE_MAP_SIZE -1

extern "C"
{
	//extern void _vectorcall InitializeTemplates();
	extern void SetCellMultiplier(float multiplier = 1.0f);
	extern void LoadTilesResourceFromFile(std::string filename);
}

extern "C++"
{
	extern INDEX2 _vectorcall TransformXMFLOAT2ToTileMapINDEX2(XMFLOAT2 floats) noexcept;
	extern INDEX2 _vectorcall TransformXMFLOAT3ToTileMapINDEX2(XMFLOAT3 floats) noexcept;
}

#pragma region
class Tile;
class RendererManager;
#pragma endregion

struct TileMap
{
	TileMap(float size, float framesPerSecond, float animationSpeed, bool isLooping);
	~TileMap();
	void Initialize();
	void _vectorcall Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,XMVECTOR cameraPosition);
	void _vectorcall SetTile(XMFLOAT2 position, int32_t tile);
	void _vectorcall SetTile(XMFLOAT2 position, int32_t tile,int32_t brush);
	void _vectorcall SetTile(INDEX2 index, int32_t tile);
	void SaveToFile(std::string filename);
	void LoadFromFile(std::string filename);

	static bool CollisionAt(XMFLOAT3 position);
	static void SetCurrentTileMap(TileMap* tilemap);
	Tile* map[TILE_MAP_SIZE][TILE_MAP_SIZE];

	void Update(float dt);

private:

	int32_t   renderInts[6];

	float m_currentFrame;
	float m_previousFrame;
	float m_maxFrames;
	float m_animationSpeed;
	float m_currentSpeed;
	float m_framesPerSecond;
	bool m_isLooping;
};

class AnimatedTile;

class Tile
{
public:
	Tile(float x,float y,int ix,int iy);
	Tile(XMFLOAT2 position,INDEX2 index);
	explicit Tile(AnimatedTile* tile);
	explicit Tile(Tile* tile);
	virtual ~Tile();

	static void SetGlobals(ID3D11Device* device, Shader* shader,RendererManager* renderer);
	static void SetVolatileGlobals(XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	static void SetDeviceContext(ID3D11DeviceContext* context);
	
	virtual void Update();
	virtual void Render();

	enum Type
	{
		TILE,
		ANIMATEDTILE
	}m_type;

protected:

	friend class AnimatedTile;

	void LoadTexture();
	XMFLOAT4X4 m_world;
	INDEX2     m_index;
	XMFLOAT2   m_position;

public:

	bool m_collision;

};

class AnimatedTile : Tile
{
public:
	AnimatedTile(float x, float y, int ix, int iy,Texture* texture);
	explicit AnimatedTile(Tile* tile, Texture* texture);
	~AnimatedTile();

	void SetTexture(Texture* texture);
	void Update(float dt);
	void Render();
private:
	void LoadTexture();

	Texture* m_texture;

protected:

	friend class Tile;

};

