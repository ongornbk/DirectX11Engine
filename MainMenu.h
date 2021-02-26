
#pragma once
#include "GameComponent.h"
#include "SettingsC.h"
#include "LuaScript.h"



class MainMenu : public GameComponent
{
	class IScript* m_update;
public:
	MainMenu(void);
	~MainMenu(void);
	bool Initialize() override;
	void Update() override;
	void Render(ID3D11DeviceContext* const deviceContext, DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix) override;
	//static Unit* GetHero();

private:
	DirectX::XMFLOAT4X4    m_worldMatrix;
};

