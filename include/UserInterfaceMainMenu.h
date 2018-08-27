#pragma once
#include "Engine.h"

class Engine;

class UserInterfaceMainMenu
{
public:
	UserInterfaceMainMenu(Engine* engine, Shader* shader);
	~UserInterfaceMainMenu();

	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update(XMVECTOR cameraPosItion);
	static void GetMousePosition(int &X, int &Y);
};

