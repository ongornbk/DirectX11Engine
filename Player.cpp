#include "Player.h"

using GlobalUtilities::random;
using GlobalUtilities::Translate;

#define SCALE 70.0f

namespace
{
	Shader* kkk;
	WCHAR* str[7] = { L"w",L"b",L"h",L"d",L"n",L"y",L"z"};
	float hhhh = -900.0f;
	float kjh = 28.0f;
}

Player::Player(void)
{
	//memset(&m_entity, NULL, sizeof(m_entity));
	kkk = (TextureShader*)(ResourceManager::GetInstance()->GetShaderByName("texture.fx"));
}


Player::~Player(void)
{
	delete[] str;
}

void Player::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, Shader * shader)
{
	


	
}

void Player::Update()
{
	UpdateInput();
}



void Player::UpdateInput()
{
	
		
	
		Input* input = Engine::GetEngine()->GetInput();

		if (input == NULL) return;
		
		
//if (input->IsKeyDown(DIK_SPACE))
{

	//Entity* entity = EntityManager::GetInstance()->AddEntity();
	//entity->InitializeAnimatedSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), Engine::GetEngine()->GetGraphics()->GetDeviceContext(),shader,(WCHAR*)str[random(0,2)].c_str(),70.0f,1.0f,1.0f,true);
	//entity->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(), kkk, str[random(0, 6)],28);
	//entity->SetPosition(hhhh, -600.0f);
	//	entity->SetVelocity(random(-100, 100), random(200.0f, 1000.0f));
	//	hhhh += kjh;
	//	if (hhhh > 900.0f)
	//	{
	//		kjh = -28.0f;
	//		hhhh = 900.0f;
	//	}
	//	else if (hhhh < -900.0f)
	//	{
	//		kjh = 28.0f;
	//		hhhh = -900.0f;
	//	}

	
}

		if (input->IsKeyHit(DIK_Q))
		{
			Engine::GetEngine()->Release();
		}
	
	
}

