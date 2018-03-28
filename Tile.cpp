#include "Tile.h"
#include "ResourceManager.h"
#include "GlobalUtilities.h"
#include "Camera.h"
#include "RendererManager.h"
#include <array>



using GlobalUtilities::random;

#define TILE_MAP_HALF_SIZE_FLOAT TILE_MAP_SIZE / 2.0f

#define CELL_WIDTH              160.0f
#define CELL_HALF_WIDTH         80.0f
#define CELL_HEIGHT             80.0f
#define CELL_HALF_HEIGHT        40.0f
#define CELL_MULTIPLIER         1.02f
#define CELL_ZERO_Z             0.0f
#define CAMERA_TILE_VIEW        14
#define CAMERA_RENDER_CUT       1
#define CAMERA_TILE_CUT         CAMERA_TILE_VIEW - CAMERA_RENDER_CUT
#define CAMERA_TILE_DEEP_CUT    CAMERA_TILE_CUT + 2
#define TILE_NUMBER_OF_TEXTURES 12
#define DEFINED_TEMPLATES       2

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
	}



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

	inline void _vectorcall squashArray4(int value[4]) noexcept
	{
		for (char i = 0; i < 4; i++)
		{
			if (value[i] > TILE_MAP_RANGE) value[i] = TILE_MAP_RANGE;
			else if (value[i] < 0) value[i] = 0;
		}
		return;
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

	}


}

namespace
{
	static ID3D11Device*        m_device;
	static Shader*              m_tileShader;
	static VertexBuffer* m_vertexBuffer;
	static Texture*             m_texture[TILE_NUMBER_OF_TEXTURES];
	static float   m_size[2] = { CELL_WIDTH * CELL_MULTIPLIER,CELL_HEIGHT * CELL_MULTIPLIER };
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
	for (int i = 0; i < TILE_MAP_SIZE; i+=8)
		for (int j = 0; j < TILE_MAP_SIZE; j+=8)
		{
			int _rand = random(0, DEFINED_TEMPLATES);
			if((i<TILE_MAP_SIZE)&&(j<TILE_MAP_SIZE))
COPYLOOP8
				{

					m_tile[i + x][j + y] = m_template[_rand].m_tile[x][y];
			}
		}
	m_tileShader = shader;
	m_device = device;
	m_vertexBuffer = new VertexBuffer();
	(void)m_vertexBuffer->Initialize(device, shader, m_size,true);
	m_texture[0] = ResourceManager::GetInstance()->GetTextureByName("simplegrass");
	m_texture[1] = ResourceManager::GetInstance()->GetTextureByName("hole");
	m_texture[2] = ResourceManager::GetInstance()->GetTextureByName("simplestone");
	m_texture[3] = ResourceManager::GetInstance()->GetTextureByName("dirt");
	m_texture[4] = ResourceManager::GetInstance()->GetTextureByName("floor");
	m_texture[5] = ResourceManager::GetInstance()->GetTextureByName("stone");
	m_texture[6] = ResourceManager::GetInstance()->GetTextureByName("grasstofloor");
	m_texture[7] = ResourceManager::GetInstance()->GetTextureByName("grass");
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
	float offsety = (TILE_MAP_RANGE) *CELL_HALF_HEIGHT;
	float offsetx = 0.0f;
	for (int i = 0; i < TILE_MAP_SIZE; i++)
	{
		for (int j = 0; j < TILE_MAP_SIZE; j++)
		{
			map[i][j] = new Tile(offsetx + (CELL_HALF_WIDTH*j), offsety - (CELL_HALF_HEIGHT*j), i, j);
			if (m_tile[i][j])
			{
				//CollisionBox* box = new CollisionBox(XMFLOAT3(offsetx + (CELL_HALF_WIDTH*j)+40.0f, offsety - (CELL_HALF_HEIGHT*j)+20.0f, 0.0f), 80.0f);
			//	m_renderer->PushBox(box);
			}
		}
		offsetx -= CELL_HALF_WIDTH;
		offsety -= CELL_HALF_HEIGHT;
	}
}

TileMap::TileMap()
{

}

void _vectorcall TileMap::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,XMVECTOR cameraPosition)
{
	register float _f[2] = { TILE_MAP_HALF_SIZE_FLOAT,TILE_MAP_HALF_SIZE_FLOAT };
	register int   _i[4];
	_f[0] += cameraPosition.m128_f32[0] / CELL_WIDTH;
	_f[0] -= cameraPosition.m128_f32[1] / CELL_HEIGHT;
	_f[1] -= cameraPosition.m128_f32[0] / CELL_WIDTH;
	_f[1] -= cameraPosition.m128_f32[1] / CELL_HEIGHT;
	_i[2] = (int)_f[1] - CAMERA_TILE_VIEW;
	_i[3] = (int)_f[1] + CAMERA_TILE_VIEW;
	_i[0] = (int)_f[0] - CAMERA_TILE_VIEW;
	_i[1] = (int)_f[0] + CAMERA_TILE_VIEW;
	squashArray4(_i);
	Tile::SetVolatileGlobals(deviceContext, viewMatrix, projectionMatrix);
	for (int j = _i[2]; j <_i[3]; j++)
	{
		for (int i = _i[0]; i < _i[1]; i++)
		{
			if (((i + j) > (_i[3] + _i[1] - CAMERA_TILE_DEEP_CUT)) || ((i + j) < (_i[0] + _i[2] + CAMERA_TILE_CUT)))
				continue;
			map[j][i]->Render();
		}
	}
}