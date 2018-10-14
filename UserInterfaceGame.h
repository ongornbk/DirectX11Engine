#pragma once
#include "Sprite.h"
#include "Types.h"
#include "Engine.h"
#include "Camera.h"
#include "GameChat.h"

class Engine;

class UserInterfaceGame
{
public:
	UserInterfaceGame(Engine* engine, Shader* shader);
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update(XMVECTOR cameraPosition);
    void GetMousePosition(int16_t &x,int16_t &y);
	static GameChat* GetGameChat();
	~UserInterfaceGame();

	static void SetFPS(int fps);

private:
	Sprite * m_cursor;
	Sprite*  m_ui;


	XMFLOAT4X4 m_cursorMatrix;
	XMFLOAT4X4 m_uiMatrix;

	ASINDEX2 m_mousePosition;
	Text     m_fpsText;
	//std::vector<Text*> m_objectsText;


	
	Text     m_mainText;
	Engine*  m_engine;
	Input*   m_input;
	int xm, ym;
};

