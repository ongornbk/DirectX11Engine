#include "GameScene.h"
#include "TextureShader.h"
#include "GlobalUtilities.h"
#include <thr\threads.h>
#include "Defines.h"

using GlobalUtilities::random;

namespace
{
	float j = 0;
}

GameScene::GameScene()
{
	//m_player = NULL;
	//m_background = NULL;
	//memset(&m_entity, NULL, sizeof(m_entity));
	//XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
	m_enemy = new Model*[(*(Settings::get()->NUMBER_OF_UNITS))];
	m_hero = NULL;
	//m_enemy = NULL;
}


GameScene::~GameScene()
{
	//if (m_player)
	//{
	//	delete m_player;
	//	m_player = NULL;
	//}
	//if (m_background)
	//{
	//	delete m_background;
		//m_background = NULL;
	//}

	if (m_hero)
	{
		delete m_hero;
		m_hero = NULL;
	}
	if (m_enemy)
	{
		delete[] m_enemy;
		//m_enemy = NULL;
	}

}

bool GameScene::Initialize()
{
	TextureShader* shader = (TextureShader*)(ResourceManager::GetInstance()->GetShaderByName("texture.fx"));
	//shader->
	ModelPaths paths;
#pragma region
	paths.ATTACK_1 = L"barbarian_attack1";
	paths.ATTACK_2 = NULL;
	paths.GETHIT   = L"enemy_gethit";
	paths.KICK     = NULL;
	paths.NEUTRAL = NULL;
	paths.RUN = L"barbarian_run";
	paths.SPECIALCAST = NULL;
	paths.SPECIAL_1 = NULL;
	paths.SPECIAL_3 = NULL;
	paths.SPECIAL_4 = NULL;
	paths.TOWNNEUTRAL = L"barbarian_townneutral";
	paths.TOWNWALK = NULL;
	paths.WALK = L"barbarian_run";
#pragma endregion

	float cora = *Settings::get()->COLLISSION_RADIUS;

		m_hero = new Model();
		m_hero->InitializeSpriteModel(Engine::GetEngine()->GetGraphics()->GetDevice(), Engine::GetEngine()->GetGraphics()->GetDeviceContext(), shader, paths, 100.0f);
		m_hero->SetCollisionRadius(cora);
		//m_hero->m_flags[2] = false;
		RendererManager::GetInstance()->PushModel(m_hero);

		paths.RUN = L"enemy_walk";
		paths.TOWNNEUTRAL = L"enemy_townneutral";
		paths.WALK = L"enemy_walk";

		for (int i = 0; i < (*(Settings::get()->NUMBER_OF_UNITS)); i++)
		{
			float range = (float)(*Settings::get()->NUMBER_OF_UNITS);
			m_enemy[i] = new Model();
			m_enemy[i]->InitializeSpriteModel(Engine::GetEngine()->GetGraphics()->GetDevice(), Engine::GetEngine()->GetGraphics()->GetDeviceContext(), shader, paths, 100.0f);
			m_enemy[i]->SetPosition(random(-range, range), random(-range, range));
			m_enemy[i]->SetRotation(random(0, 15));
			m_enemy[i]->SetCollisionRadius(cora);
			RendererManager::GetInstance()->PushModel(m_enemy[i]);
		}
	if (shader == NULL)
	{
		return false;
	}

	//m_player = new Player();
	//m_player->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), Engine::GetEngine()->GetGraphics()->GetDeviceContext(), shader);
	//m_background = new Sprite(1000);
	//XMStoreFloat4x4(&m_worldMatrix, XMMatrixIdentity());
	//m_background->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), shader, L"ambient", true);


	return true;
}

extern "C"
{

	double prd_vect(float x1, float x2, float y1, float y2) noexcept
	{
		return x1 * y2 - y1 * x2;
	}

	double angle_rad(float x1, float x2, float y1, float y2) noexcept
	{
		return (prd_vect(x1, x2, y1, y2) < 0 ? -1 : 1) * acos((x1*x2 + y1 * y2) / (sqrt(x1*x1 + y1 * y1)*sqrt(x2*x2 + y2 * y2)));
	}

	double angle_deg(float x1, float x2, float y1, float y2) noexcept
	{
		return angle_rad(x1, x2, y1, y2) / 3.14f * 180;
	}

	inline  float _vectorcall DistanceBetweenXMFLOAT3(XMFLOAT3 a, XMFLOAT3 b) noexcept
	{
		float xd = abs(a.x - b.x);
		float yd = abs(a.y - b.y);
		float d = sqrt((xd*xd) + (yd*yd));
		return d;
	}

}

void GameScene::Update()
{
	Input* input = ENGINE GetInput();

	if (input == NULL) return;

	if (input->IsKeyHit(DIK_SPACE))
	{
		Model* tempA = Global::GetInstance()->m_lastSelectedModel;
		if (tempA)
		{
			if (tempA != m_hero)
			{
				Model* tempB = m_hero;
				m_hero = tempA;
				Global::GetInstance()->m_lastSelectedModel = tempB;
			}
		}
	}

	XMFLOAT3 xvm = m_hero->GetPosition();

	XMFLOAT3 mfv;



	float aspectratio = Settings::GetAspectRatio();
	float speed, speed1;
#define angle 3.14f / 8
	float rotation = 0.0f, rotation1;

	int xm, ym;
	UserInterfaceGame::GetMousePosition(xm, ym);

	//m_enemy->SetAnimation(SpriteModel::ModelStance::WALK);
//	speed1 = 100.0f;
	XMFLOAT3 mep;

	for (int i = 0; i < (*(Settings::get()->NUMBER_OF_UNITS)); i++)
	{
		mep = m_enemy[i]->GetPosition();
		//mfv.x *= mfv.x;
		//mfv.y *= mfv.y;
		if (input->GetMouseState(1) == 128)
		{
			m_enemy[i]->SetAnimation(SpriteModel::ModelStance::WALK);
			speed1 = 120.0f;

			rotation1 = atan2(mep.y - ym, mep.x - xm)*180.0f / 3.141f;
			rotation1 += 180.0f;
			rotation1 /= 22.5f;
			rotation1 = 28 - rotation1;
			m_enemy[i]->SetRotation((int)rotation1);
			m_enemy[i]->SetVelocity(sin(3.14F + angle * rotation1)*aspectratio*speed1, cos(angle*rotation1)*speed1*-1.0F);
		}
		else
		{
			m_enemy[i]->SetAnimation(SpriteModel::ModelStance::TOWNNEUTRAL);
			m_enemy[i]->SetVelocity();
		}
	

	}

	//m_hero->SetVelocity(sin(3.14F + angle * rotation)*aspectratio*speed, cos(angle*rotation)*speed*-1.0F);
	
	//}
	//else
	//{
		//m_enemy->SetAnimation(SpriteModel::ModelStance::TOWNNEUTRAL);
		//speed1 = 0.0f;
	
		

	if (input->GetMouseState(0) == 128)
	{
		//bool tempBool = true;
		Model* tempA = Global::GetInstance()->m_lastSelectedModel;
		//if (tempA)
		//{
		//	//if (tempA != m_hero)
			//{
				//if (DistanceBetweenXMFLOAT3(m_hero->GetPosition(), tempA->GetPosition())<100.0f)
				//{
			//		Sound* attack = Engine::GetEngine()->CreateSound(L"Attack",100,false);
			//		attack->Play();
			//		speed = 0.0f;
			//		rotation = atan2(ym - xvm.y, xm - xvm.x)*180.0f / 3.141f;
			//		rotation += 180.0f;
			//		rotation /= 22.5f;
			//		rotation = 20 - rotation;
			//		m_hero->SetRotation((int)rotation);
			//		m_hero->PlayAnimation(SpriteModel::ModelStance::ATTACK_1);
			//		tempBool = false;
					//goto ENDFUNCTION;
			//	}
				
			//}
		//}
		//if (tempBool)
		//{
			m_hero->SetAnimation(SpriteModel::ModelStance::RUN);
			speed = 280.0f;
			rotation = atan2(ym - xvm.y, xm - xvm.x)*180.0f / 3.141f;
			rotation += 180.0f;
			rotation /= 22.5f;
			rotation = 20 - rotation;
			m_hero->SetRotation((int)rotation);
	//	}
		//ENDFUNCTION:
	}
	else
	{
		m_hero->SetAnimation(SpriteModel::ModelStance::TOWNNEUTRAL);
		speed = 0.0f;
	}



	m_hero->SetVelocity(sin(3.14F + angle * rotation)*aspectratio*speed, cos(angle*rotation)*speed*-1.0F);
	//m_enemy->SetVelocity(sin(3.14F + angle * rotation1)*aspectratio*speed1, cos(angle*rotation1)*speed1*-1.0F);



	if (input->IsKeyHit(DIK_ESCAPE))
	{
		PostQuitMessage(1);
	}
	
	Camera::GetCurrentCamera()->SetPosition(xvm.x,xvm.y);

}

void GameScene::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
}

