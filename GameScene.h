#pragma once
#include "GameComponent.h"
#include "SettingsC.h"



class GameScene : public GameComponent
{

public:
	GameScene(void);
    ~GameScene(void);
	bool Initialize() override;
	void Update() override;
	void Render(ID3D11DeviceContext* const deviceContext, DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix) override;
	//static Unit* GetHero();

private:
	DirectX::XMFLOAT4X4    m_worldMatrix;
};

