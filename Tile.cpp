#include "Tile.h"
#include "ResourceManager.h"
#include "GlobalUtilities.h"
#include "Camera.h"
#include "RendererManager.h"
#include "IPP.h"
#include <array>
#include <fstream>
#include <string>
#include <streambuf>
#include <sstream>

#define TILE_MAP_HALF_SIZE_FLOAT TILE_MAP_SIZE / 2.0f
#define TILE_MAP_HALF_SIZE_INT32 TILE_MAP_SIZE / 2

#define CELL_ZERO_Z             0.0f
#define TILE_NUMBER_OF_TEXTURES 13

#define ANIMATEDTILE_FRAME_COUNT 4.0f


struct TileType
{
	union
	{
	struct
	{
	int32 tile_type;
	int32 tile_sub;
	};
	int64 tile_val;
	};

	bool operator !=(const struct TileType type)
	{
		return (tile_val != type.tile_val);
	}
};


	namespace
	{
		static float        m_cellMultiplier = 1.00;
	}

	namespace tile
	{

static float CELL_WIDTH           = 320.0f;
static float CELL_HALF_WIDTH      = 160.0f;
static float CELL_HEIGHT          = 160.0f;
static float CELL_HALF_HEIGHT     = 80.0f;
static int   CAMERA_TILE_VIEW     = 14;
static int   CAMERA_RENDER_CUT    = 1;
static int   CAMERA_TILE_CUT      = CAMERA_TILE_VIEW - CAMERA_RENDER_CUT;
static int   CAMERA_TILE_DEEP_CUT = CAMERA_TILE_CUT + 2;
static uint8_t tilesub[32] ={
	3u,//GRASS
	2u,//DIRT
	0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u
};

	}

	void SetCellMultiplier(const float multiplier) noexcept
	{
		m_cellMultiplier = multiplier/100.0f;
	}

	void LoadTilesResourceFromFile(std::string filename)
	{

	}




	class array< int32,2> _vectorcall TransformXMFLOAT2ToTileMapINDEX2(
		const struct XMFLOAT2 floats
	) noexcept
	{
		class array< int32, 2> _indexes = { TILE_MAP_HALF_SIZE_INT32,TILE_MAP_HALF_SIZE_INT32 };
		_indexes[0] -= (int32)(floats.x / tile::CELL_WIDTH);
		_indexes[0] -= (int32)(floats.y / tile::CELL_HEIGHT);
		_indexes[1] += (int32)(floats.x / tile::CELL_WIDTH);
		_indexes[1] -= (int32)(floats.y / tile::CELL_HEIGHT);
		ipp::math::SquashInt32Array(_indexes.data(), 2, 0, TILE_MAP_RANGE);
		return _indexes;
	}

	class array< int32, 2> _vectorcall TransformXMFLOAT3ToTileMapINDEX2(
		const struct XMFLOAT3 floats
	) noexcept
	{
		class array< int32, 2> _indexes = { TILE_MAP_HALF_SIZE_INT32,TILE_MAP_HALF_SIZE_INT32 };
		_indexes[0] -= (int32)(floats.x / tile::CELL_WIDTH);
		_indexes[0] -= (int32)(floats.y / tile::CELL_HEIGHT);
		_indexes[1] += (int32)(floats.x / tile::CELL_WIDTH);
		_indexes[1] -= (int32)(floats.y / tile::CELL_HEIGHT);
		ipp::math::SquashInt32Array(_indexes.data(), 2, 0, TILE_MAP_RANGE);
		return _indexes;
	}

	int32 _vectorcall TransformXMFLOAT3ToTileMapINDEX2WithCheck(
		const struct XMFLOAT3 floats,
		class array< int32, 2>& index
	) noexcept
	{
		index = { TILE_MAP_HALF_SIZE_INT32,TILE_MAP_HALF_SIZE_INT32 };
		index[0] -= (int32)(floats.x / tile::CELL_WIDTH);
		index[0] -= (int32)(floats.y / tile::CELL_HEIGHT);
		index[1] += (int32)(floats.x / tile::CELL_WIDTH);
		index[1] -= (int32)(floats.y / tile::CELL_HEIGHT);
		return ipp::math::SquashInt32ArrayWithCheck(index.data(), 2, 0, TILE_MAP_RANGE);
	}


namespace
{
	static struct ID3D11Device*        m_device;
	static class Shader*               m_tileShader;
	static class VertexBuffer*         m_vertexBuffer;
	static class VertexBuffer*         m_animatedVertexBuffer;
	static class Texture*              m_texture[32][8];
	static float                       m_size[2];
	static struct ID3D11DeviceContext* m_deviceContext;
	static struct XMFLOAT4X4           m_viewMatrix;
	static struct XMFLOAT4X4           m_projectionMatrix;
	static struct TileType             m_tile[TILE_MAP_SIZE][TILE_MAP_SIZE];
	static struct TileType             current = {0u,0u};
	static class RendererManager*      m_renderer;
	static struct TileMap*             m_currentTileMap;
}

Tile::Tile(
	const float x,
	const float y,
	const int32 ix,
	const int32 iy
) : 
	m_position(x, y),
	m_index{ ix,iy },
	m_collision(false)
{
	DirectX::XMStoreFloat4x4(&m_world, DirectX::XMMatrixTranslation(x,y, CELL_ZERO_Z));
}

Tile::Tile(
	const struct XMFLOAT2 position,
	class array< int32, 2> index
) : 
	m_index(index),
	m_collision(false)
{
	DirectX::XMStoreFloat4x4(&m_world, DirectX::XMMatrixTranslation(position.x, position.y, CELL_ZERO_Z));
}

Tile::Tile(
	class AnimatedTile* tile
): 
	m_position(tile->m_position),
	m_index(tile->m_index),
	m_collision(false)
{
	DirectX::XMStoreFloat4x4(&m_world, DirectX::XMMatrixTranslation(m_position.x, m_position.y, CELL_ZERO_Z));
}

Tile::Tile(
	class Tile * tile
) : 
	m_position(tile->m_position),
	m_index(tile->m_index),
	m_collision(false)
{
	DirectX::XMStoreFloat4x4(&m_world, DirectX::XMMatrixTranslation(m_position.x, m_position.y, CELL_ZERO_Z));
}


Tile::~Tile()
{
	
}

void Tile::SetGlobals(ID3D11Device* device,Shader * shader, RendererManager* renderer)
{

	m_renderer = renderer;



#pragma warning(disable : 4996)
#pragma region
	using std::ifstream;
	using std::getline;
	using std::istreambuf_iterator;
	using std::istringstream;
#pragma endregion
	ifstream stream("../settings/tile.file");
	if (!stream.good())
	{

	}
	string BUFFER((istreambuf_iterator<char>(stream)), istreambuf_iterator<char>());
	istringstream ss(BUFFER);
	vector<int> sizes;
	string token;
	while (getline(ss, token, '\n'))
	{
		sizes.push_back(atoi(token.c_str()));
	}
	tile::CELL_WIDTH = (float)sizes.at(0);
	tile::CELL_HEIGHT = (float)sizes.at(1);
	tile::CELL_HALF_HEIGHT = tile::CELL_HEIGHT / 2.0f;
	tile::CELL_HALF_WIDTH = tile::CELL_WIDTH / 2.0f;

	m_size[0] = tile::CELL_WIDTH * m_cellMultiplier;
	m_size[1] = tile::CELL_HEIGHT * m_cellMultiplier;

	tile::CAMERA_TILE_VIEW     = sizes.at(2);
	tile::CAMERA_RENDER_CUT    = sizes.at(3);
	tile::CAMERA_TILE_CUT      = tile::CAMERA_TILE_VIEW - tile::CAMERA_RENDER_CUT;
	tile::CAMERA_TILE_DEEP_CUT = tile::CAMERA_TILE_CUT + sizes.at(4);

	for (int i = 0; i < TILE_MAP_SIZE; ++i)
		for (int j = 0; j < TILE_MAP_SIZE; ++j)
		{
			m_tile[i][j].tile_type = 0u;
		}
	m_tileShader = shader;
	m_device = device;
	m_vertexBuffer = new VertexBuffer();
	(void)m_vertexBuffer->Initialize(device, shader, m_size, true);
	m_animatedVertexBuffer = new VertexBuffer();
	(void)m_animatedVertexBuffer->Initialize(device, shader, m_size, true);
	m_texture[0][0] = ResourceManager::GetInstance()->GetTextureByName("grass0");
	m_texture[0][1] = ResourceManager::GetInstance()->GetTextureByName("grass1");
	m_texture[0][2] = ResourceManager::GetInstance()->GetTextureByName("grass2");
	m_texture[0][3] = ResourceManager::GetInstance()->GetTextureByName("grass3");
	m_texture[1][0] = ResourceManager::GetInstance()->GetTextureByName("dirt0");
	m_texture[1][1] = ResourceManager::GetInstance()->GetTextureByName("dirt1");
	m_texture[1][2] = ResourceManager::GetInstance()->GetTextureByName("dirt2");
	m_texture[2][0] = ResourceManager::GetInstance()->GetTextureByName("rock");
	m_texture[3][0] = ResourceManager::GetInstance()->GetTextureByName("leaves");
	m_texture[4][0] = ResourceManager::GetInstance()->GetTextureByName("paving");
	m_texture[5][0] = ResourceManager::GetInstance()->GetTextureByName("paving2");
	m_texture[6][0] = ResourceManager::GetInstance()->GetTextureByName("dust");
	m_texture[7][0] = ResourceManager::GetInstance()->GetTextureByName("water");
	m_texture[8][0] = ResourceManager::GetInstance()->GetTextureByName("sand0");

}

void Tile::SetDeviceContext(ID3D11DeviceContext * context)
{
	m_deviceContext = context;
}

void Tile::SetVolatileGlobals(XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_viewMatrix = viewMatrix;
	m_projectionMatrix = projectionMatrix;
	current.tile_type = 0u;
	m_tileShader->SetShaderParameters(m_deviceContext, m_texture[current.tile_type][current.tile_sub]->GetTexture());
}



void Tile::LoadTexture()
{
	current = m_tile[m_index[0]][m_index[1]];
	m_tileShader->SetShaderParameters(m_deviceContext, m_texture[current.tile_type][current.tile_sub]->GetTexture());

}

void Tile::Update()
{
}

void Tile::Render()
{
	const TileType type = m_tile[m_index[0]][m_index[1]];
	if (current != type)
	{
		LoadTexture();
	}
	m_tileShader->SetShaderParameters(m_deviceContext,m_world, m_viewMatrix, m_projectionMatrix);
	m_vertexBuffer->Render(m_deviceContext);
}
TileMap::~TileMap()
{
	for (int32 i = 0; i < TILE_MAP_SIZE; ++i)
	{
		for (int32 j = 0; j < TILE_MAP_SIZE; ++j)
		{
			delete map[i][j];
		}
	}
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = NULL;
	}
	if (m_animatedVertexBuffer)
	{
		delete m_animatedVertexBuffer;
		m_animatedVertexBuffer = NULL;
	}
}

void TileMap::Initialize()
{
	float offsety = (TILE_MAP_RANGE) *tile::CELL_HALF_HEIGHT;
	float offsetx = 0.0f;
	for (int32 i = 0; i < TILE_MAP_SIZE; ++i)
	{
		for (int32 j = 0; j < TILE_MAP_SIZE; ++j)
		{
			map[i][j] = new Tile(offsetx + (tile::CELL_HALF_WIDTH*j), offsety - (tile::CELL_HALF_HEIGHT*j), i, j);
			map[i][j]->m_type = Tile::Type::TILE;

			//if (m_tile[i][j])
			//{
			//	//CollisionBox* box = new CollisionBox(XMFLOAT3(offsetx + (CELL_HALF_WIDTH*j)+40.0f, offsety - (CELL_HALF_HEIGHT*j)+20.0f, 0.0f), 80.0f);
			////	m_renderer->PushBox(box);
			//}
		}
		offsetx -= tile::CELL_HALF_WIDTH;
		offsety -= tile::CELL_HALF_HEIGHT;
	}
}

TileMap::TileMap(float size, float framesPerSecond, float animationSpeed, bool isLooping)
{
	renderInts[0] = 0;
	renderInts[1] = 0;
	renderInts[2] = 0;
	renderInts[3] = 0;

	m_framesPerSecond = (1000.0f / framesPerSecond) / 1000.0f;
	m_animationSpeed = animationSpeed;
	m_isLooping = isLooping;
	m_currentSpeed = 0;

	m_currentFrame = 0;
	m_previousFrame = -1.0f;
	m_maxFrames = ANIMATEDTILE_FRAME_COUNT;
}

void _vectorcall TileMap::Render(
	struct ID3D11DeviceContext * deviceContext,
	const struct XMFLOAT4X4 viewMatrix,
	const struct XMFLOAT4X4 projectionMatrix,
	const XMVECTOR cameraPosition
)
{
	m_tileShader->Begin(deviceContext);
	GRAPHICS EnableAlphaBlending(true);
	 float _f[2] = { TILE_MAP_HALF_SIZE_FLOAT,TILE_MAP_HALF_SIZE_FLOAT };
	 
	_f[0] += cameraPosition.m128_f32[0] / tile::CELL_WIDTH;
	_f[0] -= cameraPosition.m128_f32[1] / tile::CELL_HEIGHT;
	_f[1] -= cameraPosition.m128_f32[0] / tile::CELL_WIDTH;
	_f[1] -= cameraPosition.m128_f32[1] / tile::CELL_HEIGHT;
	renderInts[2] = ( int32)_f[1] - tile::CAMERA_TILE_VIEW;
	renderInts[3] = ( int32)_f[1] + tile::CAMERA_TILE_VIEW;
	renderInts[0] = ( int32)_f[0] - tile::CAMERA_TILE_VIEW;
	renderInts[1] = ( int32)_f[0] + tile::CAMERA_TILE_VIEW;
	int tempA = renderInts[3] + renderInts[1] - tile::CAMERA_TILE_DEEP_CUT;
	int tempC = renderInts[0] + renderInts[2] + tile::CAMERA_TILE_CUT;
	ipp::math::SquashInt32Array(renderInts,4,0,TILE_MAP_RANGE);
	renderInts[4] = renderInts[3] + renderInts[1] - tile::CAMERA_TILE_DEEP_CUT;
	renderInts[5] = renderInts[0] + renderInts[2] + tile::CAMERA_TILE_DEEP_CUT;
	Tile::SetVolatileGlobals(viewMatrix, projectionMatrix);
	for ( int32 j = renderInts[2]; j <renderInts[3]; ++j)
	{
		for ( int32 i = renderInts[0]; i < renderInts[1]; ++i)
		{
			const  int32 tempB = i + j;
			if (((tempB) > (tempA)) || ((tempB) < (tempC)))
				continue;
			switch (map[j][i]->m_type)
			{
			case Tile::Type::TILE:
				map[j][i]->Render();
				break;
			case Tile::Type::ANIMATEDTILE:
				map[j][i]->Render();
				break;
			}
			
		}
	}
	GRAPHICS EnableAlphaBlending(false);
	m_tileShader->End(deviceContext);
	
}

void TileMap::SetTile(
	const struct XMFLOAT2 position,
	const int32 tile
)
{
	SetTile(TransformXMFLOAT2ToTileMapINDEX2(position),tile);
}

void _vectorcall TileMap::SetTile(
	const struct XMFLOAT2 position,
	const int32 tile,
	const int32 brush
)
{
	array< int32,2> pos = TransformXMFLOAT2ToTileMapINDEX2(position);
	for (int32 x = 0; x < brush; ++x)
	{
		for (int32 y = 0; y < brush; ++y)
		{
			if (x + y < brush)
			{
				pos[0] += x;
				pos[1] += y;
				SetTile(pos, tile);
			}

		}
	}
}

void TileMap::SetTile(
	array< int32, 2> index,
	int32 tile)
{
	ipp::math::clamp(tile, 0, 8);
	m_tile[index[0]][index[1]].tile_type = (uint8_t)tile;
	m_tile[index[0]][index[1]].tile_sub = ipp::math::RandomUint8(0, tile::tilesub[(uint8_t)tile]);
	if (tile == 7)
	{

		if (map[index[0]][index[1]]->m_type == Tile::Type::TILE)
		{

			AnimatedTile* tilep = new AnimatedTile(map[index[0]][index[1]], m_texture[tile][ipp::math::RandomUint8(0u, tile::tilesub[tile])]);
			delete map[index[0]][index[1]];
			map[index[0]][index[1]] = (Tile*)tilep;
			map[index[0]][index[1]]->m_type = Tile::Type::ANIMATEDTILE;
			map[index[0]][index[1]]->m_collision = true;

		}
		else
		{
			((AnimatedTile*)map[index[0]][index[1]])->SetTexture(m_texture[tile][ipp::math::RandomUint8(0u,tile::tilesub[tile])]);
		}
	}
	else
	{
		if (map[index[0]][index[1]]->m_type == Tile::Type::ANIMATEDTILE)
		{
			
			Tile* tilep = new Tile((AnimatedTile*)map[index[0]][index[1]]);
			delete dynamic_cast<AnimatedTile*>(map[index[0]][index[1]]);
			map[index[0]][index[1]] = tilep;
			map[index[0]][index[1]]->m_type = Tile::Type::TILE;
			map[index[0]][index[1]]->m_collision = false;
		}
	}
}

void TileMap::SaveToFile(std::string filename)
{
	remove(filename.c_str());
	std::ofstream myfile;
	myfile.open(filename);
	
	for (uint16_t i = 0u; i < TILE_MAP_SIZE; ++i)
	{
		for (uint16_t j = 0u; j < TILE_MAP_SIZE; ++j)
		{
			myfile << m_tile[i][j].tile_type;
		}
		myfile << '\n';
	}
	


	myfile.close();
}

void TileMap::LoadFromFile(std::string filename)
{
	std::ifstream myfile;
	myfile.open(filename);
	char ch;
	for ( int32 i = 0; i < TILE_MAP_SIZE; ++i)
	{
		for ( int32 j = 0; j < TILE_MAP_SIZE; ++j)
		{

			myfile.get(ch);
			array< int32, 2> pos = { i,j };
			SetTile(pos, (int32)ch);
		}
		myfile.get(ch);
	}



	myfile.close();
}

int32 TileMap::CollisionAt(
	const struct XMFLOAT3& position
)
{
	class array< int32, 2> index;
	const int32 collision = TransformXMFLOAT3ToTileMapINDEX2WithCheck(position,index);
	if (collision)return 1;
	const class Tile* tilep = m_currentTileMap->map[index[0]][index[1]];
	if (tilep)
	{
		return (int32)tilep->m_collision;
	}
	else
	{
		return 0;
	}
}
void TileMap::SetCurrentTileMap(
	struct TileMap* const tilemap
)
{
	m_currentTileMap = tilemap;
}

void TileMap::Update(const float dt)
{
	for (int32 j = renderInts[2]; j <renderInts[3]; ++j)
	{
		for (int32 i = renderInts[0]; i < renderInts[1]; ++i)
		{
			int32 sum = i + j;
			if ((sum >(renderInts[4])) || (sum < (renderInts[5])))
				continue;
			map[j][i]->Update();
		}
	}
	if (m_maxFrames == 1.0f) return;
	if (m_currentFrame < m_maxFrames)
	{
		m_currentSpeed += m_animationSpeed + dt;

		if (m_currentSpeed > m_framesPerSecond)
		{
			m_currentFrame++;
			m_currentSpeed = 0.0f;
			if (m_currentFrame >= m_maxFrames)
			{
				if (m_isLooping)
				{
					m_currentFrame = 0.0f;
				}
				else
				{
					m_currentFrame = m_maxFrames;
				}
			}

		}
	}
	if (m_currentFrame == m_previousFrame) return;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	SpriteVertexType* vertices = m_animatedVertexBuffer->GetVertices();

	vertices[0].uv.x = m_currentFrame / m_maxFrames;
	vertices[0].uv.y = 1.0f;

	vertices[1].uv.x = m_currentFrame / m_maxFrames;
	vertices[1].uv.y = 0.0f;

	vertices[2].uv.x = (m_currentFrame + 1.0f) / m_maxFrames;
	vertices[2].uv.y = 0.0f;

	vertices[3].uv.x = (m_currentFrame + 1.0f) / m_maxFrames;
	vertices[3].uv.y = 1.0f;

	HRESULT result = m_deviceContext->Map(m_animatedVertexBuffer->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return;
	}

	SpriteVertexType* verticesPtr = (SpriteVertexType*)mappedResource.pData;
	memcpy(verticesPtr, (void*)vertices, sizeof(SpriteVertexType) * m_animatedVertexBuffer->GetVertexCount());

	m_deviceContext->Unmap(m_animatedVertexBuffer->GetVertexBuffer(), 0);

	m_previousFrame = m_currentFrame;
}

AnimatedTile::AnimatedTile(
	const float x,
	const float y,
	const int32 ix,
	const int32 iy,
	class Texture* const texture
) : 
	Tile(x, y, ix, iy), m_texture(texture)
{

}

AnimatedTile::AnimatedTile(
	class Tile * const tile,
	class Texture * const texture
) : 
	Tile(tile->m_position,tile->m_index),
	m_texture(texture)
{

}

AnimatedTile::~AnimatedTile()
{
}

void AnimatedTile::SetTexture(
	class Texture * const texture
)
{
	m_texture = texture;
}

void AnimatedTile::Update(
	const float dt
)
{
	Tile::Update();
}

void AnimatedTile::Render()
{
	if (current.tile_type != m_tile[m_index[0]][m_index[1]].tile_type)
	{
		LoadTexture();
	}
	m_tileShader->SetShaderParameters(m_deviceContext, m_world, m_viewMatrix, m_projectionMatrix);
	m_animatedVertexBuffer->Render(m_deviceContext);
}

void AnimatedTile::LoadTexture()
{
	current = m_tile[m_index[0]][m_index[1]];
	m_tileShader->SetShaderParameters(m_deviceContext, m_texture->GetTexture());
}
