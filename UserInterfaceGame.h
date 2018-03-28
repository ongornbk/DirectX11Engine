#pragma once
#include "Sprite.h"
#include "Types.h"
#include "Engine.h"
#include "Camera.h"

class Engine;

class UserInterfaceGame
{
public:
	UserInterfaceGame(Engine* engine, Shader* shader);
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update(XMVECTOR cameraPosition);
    static void GetMousePosition(int &X,int &Y);
	~UserInterfaceGame();
private:
	Sprite * m_cursor;
	Sprite*  m_ui;


	XMFLOAT4X4 m_cursorMatrix;
	XMFLOAT4X4 m_uiMatrix;
};

