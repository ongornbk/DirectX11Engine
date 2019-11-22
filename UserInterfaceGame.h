#pragma once
#include "gdef.h"
#include "Sprite.h"
#include "Engine.h"
#include "Camera.h"
#include "GameChat.h"
#include "gdef.h"

class Engine;

class UserInterfaceGame
{
public:
	UserInterfaceGame(class Engine* engine,class Shader* shader);
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update(XMVECTOR cameraPosition);
    void GetMousePosition(float&x, float&y);
	static GameChat* GetGameChat();
	~UserInterfaceGame();

	static void SetFPS(const int32 fps) noexcept;

private:
	Sprite * m_cursor;
	Sprite*  m_ui;


	XMFLOAT4X4 m_cursorMatrix;
	XMFLOAT4X4 m_uiMatrix;

	array< float, 2> m_mousePosition;
	Text          m_fpsText;
	//std::vector<Text*> m_objectsText;


	Text     m_cpuText;
	Text     m_mainText;
	Engine*  m_engine;
	Input*   m_input;
	int32 xm, ym;
};

