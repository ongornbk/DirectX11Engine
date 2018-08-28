#pragma once
#include "GameComponent.h"

class MainMenuScene : GameComponent
{
public:
	MainMenuScene(void);
	~MainMenuScene(void);

	bool Initialize() override;
	void Update() override;
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) override;

private:

	XMFLOAT4X4  m_worldMatrix;
};

