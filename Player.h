#pragma once
#include "Engine.h"
class Entity;

#define __E 100

class Player
{
public:
	Player(void);
	~Player(void);

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Shader* shader);
	void Update();
	void UpdateInput();

private:

};

