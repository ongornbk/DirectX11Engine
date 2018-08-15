#pragma once
#include "Sprite.h"
#include "Types.h"
#include "Engine.h"
#include "Camera.h"
#include "Text.h"

class Engine;

class UserInterfaceGame
{
public:
	UserInterfaceGame(Engine* engine, Shader* shader);
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update(XMVECTOR cameraPosition);
    void GetMousePosition(int &x,int &y);
	~UserInterfaceGame();

	static void SetFPS(int fps);

private:
	Sprite * m_cursor;
	Sprite*  m_ui;


	XMFLOAT4X4 m_cursorMatrix;
	XMFLOAT4X4 m_uiMatrix;

	ASINDEX2 m_mousePosition;
	Text     m_fpsText;
	Engine*  m_engine;
	Input*   m_input;
	int xm, ym;
};

