#pragma once
#include "GameComponent.h"
#include "Model.h"
#include "Player.h"
#include "SettingsC.h"



class GameScene : public GameComponent
{

public:
	GameScene(void);
    ~GameScene(void);
	bool Initialize() override;
	void Update() override;
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) override;
	static Unit* GetHero();

private:
	XMFLOAT4X4    m_worldMatrix;
};

