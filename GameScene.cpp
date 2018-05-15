#include "GameScene.h"
#include "TextureShader.h"
#include "GlobalUtilities.h"
#include <thr\threads.h>
#include "Defines.h"
#include "LUAManager.h"

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
	m_enemy = new Unit*[(*(Settings::get()->NUMBER_OF_UNITS))];
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
#pragma region
#define INITIALIZATION_FAILED { return false; }
	TextureShader*        shader   = (TextureShader*)(ResourceManager::GetInstance()->GetShaderByName("texture.fx"));
	ID3D11Device*        _device   = GRAPHICS GetDevice();
	ID3D11DeviceContext* _context  = GRAPHICS GetDeviceContext();
	RendererManager*     _renderer = RendererManager::GetInstance();
	if ((!shader) || (!_device) || (!_context) || (!_renderer)) INITIALIZATION_FAILED
#pragma endregion

		lua::Execute(lua::LUA_LOCATION_GAMESCENE_INITIALIZATION);


	//shader->
	ModelPaths paths(L"../../content/Textures/models/barbarian.mod");

	float cora = *Settings::get()->COLLISSION_RADIUS;

	m_hero = new Unit();
		m_hero->Initialize(_device, _context, shader, paths, 100.0f,cora,XMFLOAT3(0.0F,0.0F,0.0F),false);
		m_hero->SetWalkingStance(Unit::WalkingStance::RUN);
		m_hero->SetSpeed(255.0f);

		ENGINE GetCameraControl()->LockCameraPositionOnUnit(m_hero);

		_renderer->PushUnit(m_hero);

		paths.RUN = L"enemy_walk";
		paths.TOWNNEUTRAL = L"enemy_townneutral";
		paths.WALK = L"enemy_walk";

		for (int i = 0; i < (*(Settings::get()->NUMBER_OF_UNITS)); i++)
		{
			XMFLOAT3 vlt;
			vlt.x = random(-1000.0f, 1000.0f);
			vlt.y = random(-800.0f, 800.0f);
			vlt.z = 0.0f;
			m_enemy[i] = new Unit();
			m_enemy[i]->Initialize(_device, _context, shader, paths, 100.0f,cora, vlt);
			m_enemy[i]->SetWalkingStance(Unit::WalkingStance::WALK);
			m_enemy[i]->SetSpeed(140.0f);
			_renderer->PushUnit(m_enemy[i]);
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

	lua::Execute(lua::LUA_LOCATION_GAMESCENE_UPDATE);

	Input* input = ENGINE GetInput();

	if (input == NULL) return;

	XMFLOAT3 xvm = m_hero->GetPosition();

	int xm, ym;
	UserInterfaceGame::GetMousePosition(xm, ym);

	Unit* selectedunit = Global::GetInstance()->m_lastSelectedUnit;


	//m_enemy->SetAnimation(SpriteModel::ModelStance::WALK);
//	speed1 = 100.0f;
	XMFLOAT3 mep;
	/*
	for (int i = 0; i < (*(Settings::get()->NUMBER_OF_UNITS)); i++)
	{
		mep = m_enemy[i]->GetPosition();
		//mfv.x *= mfv.x;
		//mfv.y *= mfv.y;
		if (input->GetMouseState(1) == 128)
		{
			Task* task = new Task();
			TaskGotoPoint* tgtp = new TaskGotoPoint();
			tgtp->destination = XMFLOAT3((float)xm, (float)ym, 0.0f);
			tgtp->object = m_enemy[i];
			task->m_content.taskGotoPoint = tgtp;
			task->m_type = Task::Type::TASKGOTOPOINT;
			if (input->IsKeyDown(DIK_LSHIFT))
			{
				m_enemy[i]->GiveTask(task);
			}
			else
			{
				m_enemy[i]->SetTask(task);
			}
		}
		else
		{

		}

		if (input->IsKeyHit(DIK_SPACE))
		{
			Task* task = new Task();
			TaskPatrol* tgtp = new TaskPatrol();
			tgtp->pointB = m_hero->GetPosition();
			tgtp->pointA = m_enemy[i]->GetPosition();
			tgtp->object = m_enemy[i];
			task->m_content.taskPatrol = tgtp;
			task->m_type = Task::Type::TASKPATROL;
			m_enemy[i]->SetTask(task);
		}

		else
		{

		}

		if (input->IsKeyHit(DIK_1))
		{
			Task* task = new Task();
			TaskFollow* tgtp = new TaskFollow();
			tgtp->object = m_enemy[i];
			tgtp->target = m_hero;
			task->m_content.taskFollow = tgtp;
			task->m_type = Task::Type::TASKFOLLOW;
			m_enemy[i]->SetTask(task);
		}

		else
		{

		}
		
	

	}

	*/

	if (input->GetMouseState(0) == 128)
	{
		
		Task* task = new Task();
		TaskGotoPoint* tgtp = new TaskGotoPoint();
		tgtp->destination = XMFLOAT3((float)xm, (float)ym, 0.0f);
		tgtp->object = m_hero;
		task->m_content.taskGotoPoint = tgtp;
		task->m_type = Task::Type::TASKGOTOPOINT;
		m_hero->SetTask(task);
	}
	else
	{

	}

	if (selectedunit)
	{
		mep = selectedunit->GetPosition();
		//mfv.x *= mfv.x;
		//mfv.y *= mfv.y;
		if (input->GetMouseState(1) == 128)
		{
			Task* task = new Task();
			TaskGotoPoint* tgtp = new TaskGotoPoint();
			tgtp->destination = XMFLOAT3((float)xm, (float)ym, 0.0f);
			tgtp->object = selectedunit;
			task->m_content.taskGotoPoint = tgtp;
			task->m_type = Task::Type::TASKGOTOPOINT;
			if (input->IsKeyDown(DIK_LSHIFT))
			{
				selectedunit->GiveTask(task);
			}
			else
			{
				selectedunit->SetTask(task);
			}
		}
		else
		{

		}

		if (input->IsKeyHit(DIK_SPACE))
		{
			Task* task = new Task();
			TaskPatrol* tgtp = new TaskPatrol();
			tgtp->pointB = m_hero->GetPosition();
			tgtp->pointA = selectedunit->GetPosition();
			tgtp->object = selectedunit;
			task->m_content.taskPatrol = tgtp;
			task->m_type = Task::Type::TASKPATROL;
			selectedunit->SetTask(task);
		}

		else
		{

		}

		if (input->IsKeyHit(DIK_1))
		{
			Task* task = new Task();
			TaskFollow* tgtp = new TaskFollow();
			tgtp->object = selectedunit;
			tgtp->target = m_hero;
			task->m_content.taskFollow = tgtp;
			task->m_type = Task::Type::TASKFOLLOW;
			selectedunit->SetTask(task);
		}

		else
		{

		}
	}

	if (input->GetMouseState(0) == 128)
	{
		Task* task = new Task();
		TaskGotoPoint* tgtp = new TaskGotoPoint();
		tgtp->destination = XMFLOAT3((float)xm, (float)ym, 0.0f);
		tgtp->object = m_hero;
		task->m_content.taskGotoPoint = tgtp;
		task->m_type = Task::Type::TASKGOTOPOINT;
		m_hero->SetTask(task);
	}
	else
	{

	}



	if (input->IsKeyHit(DIK_ESCAPE))
	{
		PostQuitMessage(1);
	}
	
	

}

void GameScene::Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
}

