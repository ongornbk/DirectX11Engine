#pragma once
#include "Defines.h"
#include "gdef.h"
#include "Sprite.h"
#include <array>


#define TILE_MAP_RANGE TILE_MAP_SIZE -1

	extern void SetCellMultiplier(const float multiplier = 1.0f) noexcept;
	extern void LoadTilesResourceFromFile(std::string filename);
	extern array< int32,2> _vectorcall TransformXMFLOAT2ToTileMapINDEX2(const struct XMFLOAT2 floats) noexcept;
	extern array< int32,2> _vectorcall TransformXMFLOAT3ToTileMapINDEX2(const struct XMFLOAT3 floats) noexcept;

class Tile;
class RendererManager;

struct TileMap
{
	TileMap(const float size,const float framesPerSecond,const float animationSpeed,const bool isLooping);
	~TileMap();
	void Initialize();
	void _vectorcall Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,XMVECTOR cameraPosition);
	void _vectorcall SetTile(const struct XMFLOAT2 position,const int32 tile);
	void _vectorcall SetTile(const struct XMFLOAT2 position,const int32 tile,const int32 brush);
	void _vectorcall SetTile(array< int32, 2> index, int32 tile);
	void SaveToFile(std::string filename);
	void LoadFromFile(std::string filename);

	static int32 CollisionAt(const struct XMFLOAT3& position);
	static void SetCurrentTileMap(struct TileMap* tilemap);
	class Tile* map[TILE_MAP_SIZE][TILE_MAP_SIZE];

	void Update(float dt);

private:

	int32  renderInts[6];

	float m_currentFrame;
	float m_previousFrame;
	float m_maxFrames;
	float m_animationSpeed;
	float m_currentSpeed;
	float m_framesPerSecond;
	bool m_isLooping;
};

class AnimatedTile;

class _Tile //To do
{
	virtual void Update() = 0;
	virtual void Render() = 0;

	XMFLOAT4X4    m_world;
	array< int32, 2> m_index;
	XMFLOAT2      m_position;
};

class Tile
{
public:
	Tile(const float x,const float y,const int32 ix,const int32 iy);
	Tile(const struct XMFLOAT2 position, array< int32, 2> index);
	explicit Tile(class AnimatedTile* tile);
	explicit Tile(class Tile* tile);
	virtual ~Tile();

	static void SetGlobals(struct ID3D11Device* device,class Shader* shader,class RendererManager* renderer);
	static void SetVolatileGlobals(const struct XMFLOAT4X4 viewMatrix,const struct XMFLOAT4X4 projectionMatrix);
	static void SetDeviceContext(struct ID3D11DeviceContext* context);
	
	virtual void Update();
	virtual void Render();

	enum Type
	{
		TILE,
		ANIMATEDTILE,
		EMPTY
	}m_type;

protected:

	friend class AnimatedTile;

	void LoadTexture();
	XMFLOAT4X4    m_world;
	array< int32, 2> m_index;
	XMFLOAT2      m_position;

public:

	bool m_collision;

};

class AnimatedTile : Tile
{
public:
	AnimatedTile(const float x,const float y,const int32 ix,const int32 iy,class Texture* texture);
	explicit AnimatedTile(class Tile* tile,class Texture* texture);
	~AnimatedTile();

	void SetTexture(class Texture* texture);
	void Update(const float dt);
	void Render();
private:
	void LoadTexture();

	Texture* m_texture;

protected:

	friend class Tile;

};

