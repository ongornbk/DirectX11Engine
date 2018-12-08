#pragma once
#include "Engine.h"
#include "Sprite.h"

class UserInterfaceGameMenu
{
public:
	UserInterfaceGameMenu(Engine* engine, Shader* shader);
	~UserInterfaceGameMenu();

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update(XMVECTOR cameraPosItion);
	void GetMousePosition(int16_t &X, int16_t &Y);

private:

	Sprite* m_cursor;
	Sprite* m_gameMenu;

	XMFLOAT4X4 m_cursorMatrix;
	XMFLOAT4X4 m_gameMenuMatrix;

	array<i16,2> m_mousePosition;
	Engine*  m_engine;
	Input*   m_input;

	int xm, ym;
};

