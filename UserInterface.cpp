#include "UserInterface.h"

namespace
{
	static UserInterface* m_instance;
}

UserInterface::UserInterface(Type type)
{
	m_type = type;
	m_instance = this;
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
	}
}
