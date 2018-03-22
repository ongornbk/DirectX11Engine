#pragma once
#include "GameComponent.h"
#include "Model.h"
#include "Player.h"
#include "SettingsC.h"

class GameScene : public GameComponent
{
public:
	GameScene(void);
	virtual ~GameScene(void);
#define ival 16
	bool Initialize() override;
	void Update() override;
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) override;

private:
	//Player* m_player;
	//Sprite* m_background;
	Model*      m_hero;
	Model**     m_enemy;
	XMFLOAT4X4  m_worldMatrix;
};

