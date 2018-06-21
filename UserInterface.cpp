#include "UserInterface.h"

namespace
{
	static UserInterface* m_instance;
	static Engine*        m_engine;
}

UserInterface::UserInterface()
{
	m_instance = this;
	m_engine = Engine::GetEngine();
}

UserInterface::UserInterface(Type type)
{
	m_type = type;
	m_instance = this;
	m_engine = Engine::GetEngine();
}


UserInterface::~UserInterface()
{
	switch (m_type)
	{
	case GAME:
		delete m_interface.m_game;
		break;
	case MAINMENU:
		delete m_interface.m_mainMenu;
		break;
	case GAMEMENU:
		delete m_interface.m_gameMenu;
		break;
	}
}
void UserInterface::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	switch (m_type)
	{
	case GAME:
		m_interface.m_game->Render(deviceContext, viewMatrix, projectionMatrix);
		break;
	case MAINMENU:
		m_interface.m_mainMenu->Render(deviceContext, viewMatrix, projectionMatrix);
		break;
	case GAMEMENU:
		m_interface.m_gameMenu->Render(deviceContext, viewMatrix, projectionMatrix);
		break;
	}
}

void UserInterface::Update(XMVECTOR cameraPosition)
{
	switch (m_type)
	{
	case GAME:
		m_interface.m_game->Update(cameraPosition);
		break;
	case MAINMENU:
		m_interface.m_mainMenu->Update(cameraPosition);
		break;
	case GAMEMENU:
		m_interface.m_gameMenu->Update(cameraPosition);
		break;
	}
}

void UserInterface::SetScene(Type scene,Shader* shader)
{
	switch (m_type)
	{
	case GAME:
		if (m_interface.m_game)
		{
			delete m_interface.m_game;
			m_interface.m_game = NULL;
		}
		break;
	case MAINMENU:
		if (m_interface.m_mainMenu)
		{
			delete m_interface.m_mainMenu;
			m_interface.m_mainMenu = NULL;
		}
		break;
	case GAMEMENU:
		if (m_interface.m_gameMenu)
		{
			delete m_interface.m_gameMenu;
			m_interface.m_gameMenu = NULL;
		}
		break;
	}
	
	m_type = scene;
	
	switch (m_instance->m_type)
	{
	case GAME:
		m_interface.m_game = new UserInterfaceGame(m_engine, shader);
		break;
	case MAINMENU:
		m_interface.m_mainMenu = new UserInterfaceMainMenu(m_engine, shader);
		break;
	case GAMEMENU:
		m_interface.m_gameMenu = new UserInterfaceGameMenu(m_engine, shader);
		break;
	}
}

void UserInterface::GetMousePosition(int & X, int & Y)
{
	switch (m_instance->m_type)
	{
	case GAME:
		m_instance->m_interface.m_game->GetMousePosition(X,Y);
		break;
	case MAINMENU:
		m_instance->m_interface.m_mainMenu->GetMousePosition(X, Y);
		break;
	case GAMEMENU:
		m_instance->m_interface.m_gameMenu->GetMousePosition(X, Y);
		break;
	}
}
