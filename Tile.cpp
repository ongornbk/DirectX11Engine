#include "Tile.h"
#include "ResourceManager.h"
#include "GlobalUtilities.h"
#include "Camera.h"
#include "RendererManager.h"
#include "Onion.h"
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

//#pragma region
//#define COPYLOOP8 for(int x = 0;x<8;x++) for (int y = 0; y < 8; y++)
//#pragma endregion

extern "C"
{

//	struct TileTemplate
//	{
//		unsigned char m_tile[8][8];
//	};

	namespace
	{
		//static TileTemplate m_template[DEFINED_TEMPLATES + 1];
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

	
	/*
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
	*/

	void SetCellMultiplier(float multiplier)
	{
		m_cellMultiplier = multiplier/100.0f;
	}




}

extern "C++"
{
	INDEX2 _vectorcall TransformXMFLOAT2ToTileMapINDEX2(XMFLOAT2 floats) noexcept
	{
		float _f[2] = { TILE_MAP_HALF_SIZE_FLOAT,TILE_MAP_HALF_SIZE_FLOAT };
		int   _i[2] = { 0 };
		_f[0] -= floats.x / tile::CELL_WIDTH;
		_f[0] -= floats.y / tile::CELL_HEIGHT;
		_f[1] += floats.x / tile::CELL_WIDTH;
		_f[1] -= floats.y / tile::CELL_HEIGHT;
		_i[0] = (int)_f[0];
		_i[1] = (int)_f[1];
		SquashInt32Array(_i, 2, 0, TILE_MAP_RANGE);
		INDEX2 index(_i[0], _i[1]);
		return index;
	}

	INDEX2 _vectorcall TransformXMFLOAT3ToTileMapINDEX2(XMFLOAT3 floats) noexcept
	{
		float _f[2] = { TILE_MAP_HALF_SIZE_FLOAT,TILE_MAP_HALF_SIZE_FLOAT };
		int   _i[2] = { 0 };
		_f[0] -= floats.x / tile::CELL_WIDTH;
		_f[0] -= floats.y / tile::CELL_HEIGHT;
		_f[1] += floats.x / tile::CELL_WIDTH;
		_f[1] -= floats.y / tile::CELL_HEIGHT;
		_i[0] = (int)_f[0];
		_i[1] = (int)_f[1];
		SquashInt32Array(_i, 2, 0, TILE_MAP_RANGE);
		INDEX2 index(_i[0], _i[1]);
		return index;
	}
}

namespace
{
	static ID3D11Device*        m_device;
	static Shader*              m_tileShader;
	static VertexBuffer*        m_vertexBuffer;
	static VertexBuffer*        m_animatedVertexBuffer;
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
			m_tile[i][j] = 0;
		}
	m_tileShader = shader;
	m_device = device;
	m_vertexBuffer = new VertexBuffer();
	(void)m_vertexBuffer->Initialize(device, shader, m_size, true);
	m_animatedVertexBuffer = new VertexBuffer();
	(void)m_animatedVertexBuffer->Initialize(device, shader, m_size, true);
	m_texture[0] = ResourceManager::GetInstance()->GetTextureByName("grass");
	m_texture[1] = ResourceManager::GetInstance()->GetTextureByName("dirt");
	m_texture[2] = ResourceManager::GetInstance()->GetTextureByName("rock");
	m_texture[3] = ResourceManager::GetInstance()->GetTextureByName("leaves");
	m_texture[4] = ResourceManager::GetInstance()->GetTextureByName("paving");
	m_texture[5] = ResourceManager::GetInstance()->GetTextureByName("paving2");
	m_texture[6] = ResourceManager::GetInstance()->GetTextureByName("dust");
	m_texture[7] = ResourceManager::GetInstance()->GetTextureByName("water");
	//m_texture[8] = ResourceManager::GetInstance()->GetTextureByName("fallen_tile");

}

void Tile::SetDeviceContext(ID3D11DeviceContext * context)
{
	m_deviceContext = context;
}

void Tile::SetVolatileGlobals(XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
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
	for (int i = 0; i < TILE_MAP_SIZE; i++)
	{
		for (int j = 0; j < TILE_MAP_SIZE; j++)
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
	m_maxFrames = 2.0f;
}

void _vectorcall TileMap::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix,XMVECTOR cameraPosition)
{
	 float _f[2] = { TILE_MAP_HALF_SIZE_FLOAT,TILE_MAP_HALF_SIZE_FLOAT };
	 
	_f[0] += cameraPosition.m128_f32[0] / tile::CELL_WIDTH;
	_f[0] -= cameraPosition.m128_f32[1] / tile::CELL_HEIGHT;
	_f[1] -= cameraPosition.m128_f32[0] / tile::CELL_WIDTH;
	_f[1] -= cameraPosition.m128_f32[1] / tile::CELL_HEIGHT;
	renderInts[2] = (int)_f[1] - tile::CAMERA_TILE_VIEW;
	renderInts[3] = (int)_f[1] + tile::CAMERA_TILE_VIEW;
	renderInts[0] = (int)_f[0] - tile::CAMERA_TILE_VIEW;
	renderInts[1] = (int)_f[0] + tile::CAMERA_TILE_VIEW;

	int tempA = renderInts[3] + renderInts[1] - tile::CAMERA_TILE_DEEP_CUT;
	int tempC = renderInts[0] + renderInts[2] + tile::CAMERA_TILE_CUT;
	SquashInt32Array(renderInts,4,0,TILE_MAP_RANGE);
	Tile::SetVolatileGlobals(viewMatrix, projectionMatrix);
	for (int j = renderInts[2]; j <renderInts[3]; j++)
	{
		for (int i = renderInts[0]; i < renderInts[1]; i++)
		{
			int tempB = i + j;
			if (((tempB) > (tempA)) || ((tempB) < (tempC)))
				continue;
			switch (map[j][i]->m_type)
			{
			case Tile::Type::TILE:
				map[j][i]->Render();
				break;
			case Tile::Type::ANIMATEDTILE:
				((AnimatedTile*)map[j][i])->Render();
				break;
			}
			
		}
	}
}

void TileMap::SetTile(XMFLOAT2 position, int32_t tile)
{
	INDEX2 pos = TransformXMFLOAT2ToTileMapINDEX2(position);
	SquashInt32(tile, 0, 7);
	m_tile[pos.i][pos.j] = (unsigned char)tile;
	if (tile == 7)
	{
		
		if (map[pos.i][pos.j]->m_type == Tile::Type::TILE)
		{
			float offsety = (TILE_MAP_RANGE)*tile::CELL_HALF_HEIGHT;
			float offsetx = 0.0f;
			offsetx -= tile::CELL_HALF_WIDTH*pos.i;
			offsety -= tile::CELL_HALF_HEIGHT*pos.j;
			delete map[pos.i][pos.j];
			map[pos.i][pos.j] = (Tile*)(new AnimatedTile(offsetx + (tile::CELL_HALF_WIDTH*pos.j), offsety - (tile::CELL_HALF_HEIGHT*pos.j), pos.i, pos.j, m_texture[tile]));
			map[pos.i][pos.j]->m_type = Tile::Type::ANIMATEDTILE;
			
		}
		else
		{
			((AnimatedTile*)map[pos.i][pos.j])->SetTexture(m_texture[tile]);
		}
	}
	else
	{
		if (map[pos.i][pos.j]->m_type == Tile::Type::ANIMATEDTILE)
		{
			float offsety = (TILE_MAP_RANGE)*tile::CELL_HALF_HEIGHT;
			float offsetx = 0.0f;
			offsetx -= tile::CELL_HALF_WIDTH*pos.i;
			offsety -= tile::CELL_HALF_HEIGHT*pos.j;
			delete map[pos.i][pos.j];
			map[pos.i][pos.j] = new Tile(offsetx + (tile::CELL_HALF_WIDTH*pos.j), offsety - (tile::CELL_HALF_HEIGHT*pos.j), pos.i, pos.j);
			map[pos.i][pos.j]->m_type = Tile::Type::TILE;
		}
	}
	
	 

}

void TileMap::Update(float dt)
{
	for (int j = renderInts[2]; j <renderInts[3]; j++)
	{
		for (int i = renderInts[0]; i < renderInts[1]; i++)
		{
			if (((i + j) >(renderInts[3] + renderInts[1] - tile::CAMERA_TILE_DEEP_CUT)) || ((i + j) < (renderInts[0] + renderInts[2] + tile::CAMERA_TILE_CUT)))
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
	VertexBuffer::VertexType* vertices = m_animatedVertexBuffer->GetVertices();

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

	VertexBuffer::VertexType* verticesPtr = (VertexBuffer::VertexType*)mappedResource.pData;
	memcpy(verticesPtr, (void*)vertices, sizeof(VertexBuffer::VertexType) * m_animatedVertexBuffer->GetVertexCount());

	m_deviceContext->Unmap(m_animatedVertexBuffer->GetVertexBuffer(), 0);

	m_previousFrame = m_currentFrame;
}

AnimatedTile::AnimatedTile(float x, float y, int ix, int iy,Texture* texture) : Tile(x, y, ix, iy)
{
	m_texture = texture;
}

AnimatedTile::~AnimatedTile()
{
}

void AnimatedTile::SetTexture(Texture * texture)
{
	m_texture = texture;
}

void AnimatedTile::Update(float dt)
{
	Tile::Update();
	
}

void AnimatedTile::Render()
{
	if (current != m_tile[m_index.i][m_index.j])
	{
		LoadTexture();
	}
	m_tileShader->SetShaderParameters(m_deviceContext, m_world, m_viewMatrix, m_projectionMatrix);
	m_animatedVertexBuffer->Render(m_deviceContext);
}

void AnimatedTile::LoadTexture()
{
	current = m_tile[m_index.i][m_index.j];
	m_tileShader->SetShaderParameters(m_deviceContext, m_texture->GetTexture());
}
