#include "GameScene.h"
#include "TextureShader.h"

#include "ResourceManager.h"
#include "Engine.h"
#include "Defines.h"
#include "LUAManager.h"



GameScene::GameScene() : m_update(nullptr)
{

}


GameScene::~GameScene()
{
	if (m_update)
	{
		delete m_update;
		m_update = nullptr;
	}
}

bool GameScene::Initialize()
{
#pragma region
#define INITIALIZATION_FAILED { return false; }
	TextureShader*        shader   = (TextureShader*)(ResourceManager::GetInstance()->GetShaderByName("texture.fx"));
	ID3D11Device*        _device   = GRAPHICS GetDevice();
	ID3D11DeviceContext* _context  = GRAPHICS GetDeviceContext();
	RendererManager*     _renderer = RendererManager::GetInstance();
	_renderer->EnableCollision(true);
	if ((!shader) || (!_device) || (!_context) || (!_renderer)) INITIALIZATION_FAILED
#pragma endregion

		lua::Execute(lua::LUA_LOCATION_GAMESCENE_INITIALIZATION);

	//m_update = new LuaScript();

	//m_update->Load(lua::LUA_LOCATION_GAMESCENE_UPDATE);


	if (shader == NULL)
	{
		return false;
	}



	return true;
}

extern "C"
{

//	double prd_vect(float x1, float x2, float y1, float y2) modern_except_state
//	{
//		return x1 * y2 - y1 * x2;
//	}
//
//	double angle_rad(float x1, float x2, float y1, float y2) modern_except_state
//	{
//		return (prd_vect(x1, x2, y1, y2) < 0 ? -1 : 1) * acos((x1*x2 + y1 * y2) / (sqrt(x1*x1 + y1 * y1)*sqrt(x2*x2 + y2 * y2)));
//	}
//
//	double angle_deg(float x1, float x2, float y1, float y2) modern_except_state
//	{
//		return angle_rad(x1, x2, y1, y2) / 3.14f * 180;
//	}
//
//	inline  float _vectorcall DistanceBetweenXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) modern_except_state
//	{
//		float xd = abs(a.x - b.x);
//		float yd = abs(a.y - b.y);
//		float d = sqrt((xd*xd) + (yd*yd));
//		return d;
//	}

}

void GameScene::Update()
{

	

	class Input* const input = ENGINE GetInput();

	if (input == NULL) return;

	lua::Execute(lua::LUA_LOCATION_GAMESCENE_UPDATE);

	//m_update->Execute();

	//Unit* selectedunit = Global::GetInstance()->m_lastSelectedUnit;

	

	
	

}

void GameScene::Render(ID3D11DeviceContext * const deviceContext, DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix)
{
}

