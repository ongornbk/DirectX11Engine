#pragma once
#include "UserInterfaceGame.h"
#include "UserInterfaceMainMenu.h"

#pragma region
class UserInterfaceGame;
class UserInterfaceMainMenu;
#pragma endregion

class UserInterface
{
public:
	enum Type
	{
		MAINMENU = 0,
		GAME = 1
	};
private:
	union Interface
	{
	public:	
	UserInterfaceMainMenu* m_mainMenu;
	UserInterfaceGame*     m_game;
	};
public:
	UserInterface(Type type);
	
	~UserInterface();

	 void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	 void Update(XMVECTOR cameraPosition);
	 static void GetMousePosition(int &X, int &Y);

	Interface m_interface;
	Type      m_type;
};

