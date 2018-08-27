#include "Tile.h"
#include "ResourceManager.h"
#include "GlobalUtilities.h"
#include "Camera.h"
#include "RendererManager.h"
#include "Onion.h"
#include "PerlinNoise.hpp"
#include <array>
#include <fstream>
#include <string>
#include <streambuf>
#include <sstream>


using Onion::Math::SquashInt32;
using Onion::Math::SquashInt32Array;
using GlobalUtilities::random;

#define TILE_MAP_HALF_SIZE_FLOAT TILE_MAP_SIZE / 2.0f

#define CELL_ZERO_Z             0.0f
#define TILE_NUMBER_OF_TEXTURES 13
#define DEFINED_TEMPLATES       3

#pragma region
#define COPYLOOP8 for(int x = 0;x<8;x++) for (int y = 0; y < 8; y++)
#pragma endregion

extern "C"
{

	struct TileTemplate
	{
		unsigned char m_tile[8][8];
	};

	namespace
	{
		static TileTemplate m_template[DEFINED_TEMPLATES + 1];
		static float        m_cellMultiplier = 1.00;
	}

	namespace tile
	{

static float CELL_WIDTH           = 160.0f;
static float CELL_HALF_WIDTH      = 80.0f;
static float CELL_HEIGHT          = 80.0f;
static float CELL_HALF_HEIGHT     = 40.0f;
static int   CAMERA_TILE_VIEW     = 14;
static int   CAMERA_RENDER_CUT    = 1;
static int   CAMERA_TILE_CUT      = CAMERA_TILE_VIEW - CAMERA_RENDER_CUT;
static int   CAMERA_TILE_DEEP_CUT = CAMERA_TILE_CUT + 2;

	}

	

	void _vectorcall InitializeTemplates() noexcept
	{
		{
			unsigned char tempA[8][8] =
			{
			{4u, 4u, 4u, 4u, 4u, 4u, 4u, 4u },
			{4u, 4u, 4u, 4u, 4u, 4u, 4u, 4u},
			{6u, 6u, 6u, 6u, 6u, 6u, 6u, 6u},
			{7u, 7u, 7u, 7u, 7u, 7u, 7u, 7u},
			{7u, 7u, 7u, 7u, 7u, 7u, 7u, 7u},
			{7u, 7u, 7u, 7u, 7u, 7u, 7u, 7u},
			{0u, 0u, 1u, 3u, 3u, 0u, 0u, 0u},
			{0u, 0u, 0u, 3u, 3u, 0u, 0u, 0u}
			};
			COPYLOOP8
				m_template[0].m_tile[x][y] = tempA[x][y];
		}
		{
			unsigned char tempA[8][8] =
			{
			{ 4u, 3u, 3u, 3u, 3u, 0u, 0u, 2u },
			{ 4u, 3u, 3u, 3u, 3u, 0u, 4u, 3u },
			{ 4u, 4u, 4u, 4u, 3u, 4u, 3u, 3u },
			{ 4u, 4u, 4u, 3u, 3u, 4u, 4u, 4u },
			{ 4u, 4u, 4u, 3u, 3u, 4u, 4u, 4u },
			{ 0u, 0u, 4u, 4u, 4u, 4u, 0u, 0u },
			{ 0u, 5u, 1u, 3u, 3u, 0u, 1u, 0u },
			{ 0u, 0u, 0u, 3u, 3u, 0u, 0u, 0u }
			};
			COPYLOOP8
				m_template[1].m_tile[x][y] = tempA[x][y];
		}
		{
			unsigned char tempA[8][8] =
			{
			{ 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u },
			{ 1u, 2u, 5u, 5u, 4u, 5u, 5u, 1u },
			{ 1u, 5u, 5u, 5u, 4u, 5u, 5u, 1u },
			{ 1u, 5u, 5u, 2u, 4u, 5u, 5u, 1u },
			{ 1u, 4u, 4u, 4u, 4u, 4u, 4u, 4u },
			{ 1u, 3u, 3u, 3u, 4u, 5u, 5u, 1u },
			{ 1u, 3u, 3u, 3u, 3u, 5u, 5u, 1u },
			{ 1u, 1u, 1u, 1u, 1u, 1u, 1u, 1u }
			};
			COPYLOOP8
				m_template[2].m_tile[x][y] = tempA[x][y];
		}
		{
			unsigned char tempA[8][8] =
			{
			{ 7u, 7u, 7u, 7u, 7u, 7u, 7u, 7u },
			{ 7u, 7u, 7u, 7u, 8u, 7u, 7u, 7u },
			{ 7u, 5u, 7u, 7u, 7u, 7u, 7u, 5u },
			{ 7u, 7u, 7u, 7u, 7u, 7u, 7u, 7u },
			{ 7u, 7u, 7u, 7u, 8u, 7u, 7u, 7u },
			{ 7u, 7u, 7u, 7u, 5u, 7u, 7u, 7u },
			{ 7u, 5u, 7u, 7u, 7u, 7u, 8u, 7u },
			{ 7u, 7u, 7u, 7u, 7u, 7u, 7u, 7u }
			};
			COPYLOOP8
				m_template[2].m_tile[x][y] = tempA[x][y];
		}

	}

	void SetCellMultiplier(float multiplier)
	{
		m_cellMultiplier = multiplier/100.0f;
	}


}

namespace
{
	static ID3D11Device*        m_device;
	static Shader*              m_tileShader;
	static VertexBuffer* m_vertexBuffer;
	static Texture*             m_texture[TILE_NUMBER_OF_TEXTURES];
	static float   m_size[2];
	static ID3D11DeviceContext* m_deviceContext;
	static XMFLOAT4X4 m_viewMatrix;
	static XMFLOAT4X4 m_projectionMatrix;
	static unsigned char m_tile[TILE_MAP_SIZE][TILE_MAP_SIZE];
	static unsigned char current = 0u;
	static RendererManager*     m_renderer;
}

Tile::Tile(float x,float y,int ix,int iy)
{
	XMStoreFloat4x4(&m_world, XMMatrixTranslation(x,y, CELL_ZERO_Z));
	m_index.i = ix;
	m_index.j = iy;
	
}


Tile::~Tile()
{
	if (m_vertexBuffer)
	{
		delete m_vertexBuffer;
		m_vertexBuffer = NULL;
	}
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
			m_tile[i][j] = (i * j) % 7;
		}
	m_tileShader = shader;
	m_device = device;
	m_vertexBuffer = new VertexBuffer();
	(void)m_vertexBuffer->Initialize(device, shader, m_size, true);
	m_texture[0] = ResourceManager::GetInstance()->GetTextureByName("grass");
	m_texture[1] = ResourceManager::GetInstance()->GetTextureByName("dirt");
	m_texture[2] = ResourceManager::GetInstance()->GetTextureByName("rock");
	m_texture[3] = ResourceManager::GetInstance()->GetTextureByName("leaves");
	m_texture[4] = ResourceManager::GetInstance()->GetTextureByName("paving");
	m_texture[5] = ResourceManager::GetInstance()->GetTextureByName("paving2");
	m_texture[6] = ResourceManager::GetInstance()->GetTextureByName("dust");
	//m_texture[7] = ResourceManager::GetInstance()->GetTextureByName("grass");
	//m_texture[8] = ResourceManager::GetInstance()->GetTextureByName("fallen_tile");

}

void Tile::SetVolatileGlobals(ID3D11DeviceContext * deviceContext,XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_deviceContext = deviceContext;
	m_viewMatrix = viewMatrix;
	m_projectionMatrix = projectionMatrix;
	current = 0u;
	m_tileShader->SetShaderParameters(m_deviceContext, m_texture[current]->GetTexture());
}



void Tile::LoadTexture()
{
	current = m_tile[m_index.i][m_index.j];
	m_tileShader->SetShaderParameters(m_deviceContext, m_texture[current]->GetTexture());

}

void Tile::Update()
{
}

void Tile::Render()
{
	if (current != m_tile[m_index.i][m_index.j])
	{
		LoadTexture();
	}
	m_tileShader->SetShaderParameters(m_deviceContext,m_world, m_viewMatrix, m_projectionMatrix);
	m_vertexBuffer->Render(m_deviceContext);
}
TileMap::~TileMap()
{
	for (int i = 0; i < TILE_MAP_SIZE; i++)
	{
		for (int j = 0; j < TILE_MAP_SIZE; j++)
		{
			delete map[i][j];
		}
	}
}

void TileMap::Initialize()
{
	float offsety = (TILE_MAP_RANGE) *tile::CELL_HALF_HEIGHT;
	float offsetx = 0.0f;
	for (int i = 0; i < TILE_MAP_SIZE; i++)
	{
		for (int j = 0; j < TILE_MAP_SIZE; j++)
		{
			map[i][j] = new Tile(offsetx + (tile::CELL_HALF_WIDTH*j), offsety - (tile::CELL_HALF_HEIGHT*j), i, j);
			if (m_tile[i][j])
			{
				//CollisionBox* box = new CollisionBox(XMFLOAT3(offsetx + (CELL_HALF_WIDTH*j)+40.0f, offsety - (CELL_HALF_HEIGHT*j)+20.0f, 0.0f), 80.0f);
			//	m_renderer->PushBox(box);
			}
		}
		offsetx -= tile::CELL_HALF_WIDTH;
		offsety -= tile::CELL_HALF_HEIGHT;
	}
}

TileMap::TileMap()
{

}

void _vectorcall TileMap::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,XMVECTOR cameraPosition)
{
	 float _f[2] = { TILE_MAP_HALF_SIZE_FLOAT,TILE_MAP_HALF_SIZE_FLOAT };
	 int   _i[4];
	_f[0] += cameraPosition.m128_f32[0] / tile::CELL_WIDTH;
	_f[0] -= cameraPosition.m128_f32[1] / tile::CELL_HEIGHT;
	_f[1] -= cameraPosition.m128_f32[0] / tile::CELL_WIDTH;
	_f[1] -= cameraPosition.m128_f32[1] / tile::CELL_HEIGHT;
	_i[2] = (int)_f[1] - tile::CAMERA_TILE_VIEW;
	_i[3] = (int)_f[1] + tile::CAMERA_TILE_VIEW;
	_i[0] = (int)_f[0] - tile::CAMERA_TILE_VIEW;
	_i[1] = (int)_f[0] + tile::CAMERA_TILE_VIEW;
	SquashInt32Array(_i,4,0,TILE_MAP_RANGE);
	Tile::SetVolatileGlobals(deviceContext, viewMatrix, projectionMatrix);
	for (int j = _i[2]; j <_i[3]; j++)
	{
		for (int i = _i[0]; i < _i[1]; i++)
		{
			if (((i + j) > (_i[3] + _i[1] - tile::CAMERA_TILE_DEEP_CUT)) || ((i + j) < (_i[0] + _i[2] + tile::CAMERA_TILE_CUT)))
				continue;
			map[j][i]->Render();
		}
	}
}