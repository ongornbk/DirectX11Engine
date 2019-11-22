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

class RendererManager;

struct TileInfo
{
	DirectX::XMFLOAT4X4    m_world;
	int32                  m_index[2];
	DirectX::XMFLOAT2      m_position;
};

class Tile
{
public:


	static void SetGlobals(struct ID3D11Device* const device, class Shader* const shader, class RendererManager* const renderer);
	static void SetVolatileGlobals(const struct DirectX::XMFLOAT4X4 viewMatrix, const struct DirectX::XMFLOAT4X4 projectionMatrix);
	static void SetDeviceContext(struct ID3D11DeviceContext* const context);

	virtual void Update(const float dt) = 0;
	virtual void Render() = 0;

	bool m_collision;

	TileInfo m_info;

protected:
	virtual void LoadTexture() = 0;
public:
};


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
	Tile* map[TILE_MAP_SIZE][TILE_MAP_SIZE];

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


class SimpleTile : public Tile
{
public:
	SimpleTile(const float x,const float y,const int32 ix,const int32 iy);
	SimpleTile(const struct DirectX::XMFLOAT2 position, int32* const index);
    explicit SimpleTile(struct TileInfo& info);
	~SimpleTile();

	void SetTexture(class Texture* const texture);
	void Update(const float dt) override;
	void Render() override;


	friend class AnimatedTile;



private:
	void LoadTexture() override;



	//Texture* m_texture;




};

class AnimatedTile : public Tile
{
public:
	AnimatedTile(const float x,const float y,const int32 ix,const int32 iy,class Texture* texture);
	explicit AnimatedTile(struct TileInfo& info,class Texture* texture);
	~AnimatedTile();

	void SetTexture(class Texture* texture);
	void Update(const float dt) override;
	void Render() override;

	

	friend class SimpleTile;

private:
	void LoadTexture();

	//Texture* m_texture;

};

class EmptyTile : public Tile
{
public:
	EmptyTile(const float x, const float y, const int32 ix, const int32 iy);
	//	explicit SimpleTile(class Tile* tile, class Texture* texture);
	~EmptyTile();

	//void SetTexture(class Texture* const texture);
	void Update(const float dt) override;
	void Render() override;

	bool m_collision;
};

