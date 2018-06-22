#pragma once
#include "Engine.h"

class UserInterfaceGameMenu
{
public:
	UserInterfaceGameMenu(Engine* engine, Shader* shader);
	~UserInterfaceGameMenu();

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update(XMVECTOR cameraPosItion);
	void GetMousePosition(int &X, int &Y);

private:

	Sprite* m_cursor;
	Sprite* m_gameMenu;

	XMFLOAT4X4 m_cursorMatrix;
	XMFLOAT4X4 m_gameMenuMatrix;

	ASINDEX2 m_mousePosition;
	Engine*  m_engine;
	Input*   m_input;

	int xm, ym;
};

