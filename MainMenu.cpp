#include "MainMenu.h"
#include "TextureShader.h"

#include "ResourceManager.h"
#include "Engine.h"
#include "Defines.h"
#include "LUAManager.h"

MainMenu::MainMenu(void) : m_update(nullptr)
{
}

MainMenu::~MainMenu(void)
{
	if (m_update)
	{
		delete m_update;
		m_update = nullptr;
	}
}

bool MainMenu::Initialize()
{
#pragma region
#define INITIALIZATION_FAILED { return false; }
	TextureShader* shader = (TextureShader*)(ResourceManager::GetInstance()->GetShaderByName("texture.fx"));
	ID3D11Device* _device = GRAPHICS GetDevice();
	ID3D11DeviceContext* _context = GRAPHICS GetDeviceContext();
	RendererManager* _renderer = RendererManager::GetInstance();
	//_renderer->EnableCollision(false);
	if ((!shader) || (!_device) || (!_context) || (!_renderer)) INITIALIZATION_FAILED
#pragma endregion

		lua::Execute(lua::LUA_LOCATION_MAINMENU_INITIALIZATION);

	//m_update = new LuaScript();

	//m_update->Load(lua::LUA_LOCATION_GAMESCENE_UPDATE);


	if (shader == NULL)
	{
		return false;
	}



	return true;
}

void MainMenu::Update()
{
	class Input* const input = ENGINE GetInput();

	if (input == NULL) return;

	lua::Execute(lua::LUA_LOCATION_MAINMENU_UPDATE);
}

void MainMenu::Render(ID3D11DeviceContext* const deviceContext, DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix)
{
}
