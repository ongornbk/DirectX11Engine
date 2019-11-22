#pragma once
#include "UserInterfaceGame.h"
#include "UserInterfaceMainMenu.h"
#include "UserInterfaceGameMenu.h"

#pragma region
class UserInterfaceGame;
class UserInterfaceMainMenu;
class UserInterfaceGameMenu;
#pragma endregion

class UserInterface
{
public:

#define UI_CURSOR_SIZE 48.0f
#define UI_MUI_OFFSET 490.0f
#define UI_GAMEMENU_OFFSET 800.0f
#define UI_MUI_HEIGHT 175.0f
#define UI_CURSOR_ZERO_Z 0.0f

	enum Type
	{
		MAINMENU = 0,
		GAME = 1,
		GAMEMENU = 2
	};
private:
	union Interface
	{
	public:	
	UserInterfaceMainMenu* m_mainMenu;
	UserInterfaceGame*     m_game;
	UserInterfaceGameMenu*  m_gameMenu;
	};
public:
	UserInterface(void);
	UserInterface(const enum Type type);
	
	~UserInterface();

	 void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	 void Update(XMVECTOR cameraPosition);
	 void SetScene(const enum Type scene,class Shader* shader);
	 void SetScene(const uint32 scene,class Shader* shader);
	 static void GetMousePosition(float&X, float&Y);

	Interface m_interface;
	Type      m_type;
};

