#pragma once
#include "Engine.h"
#include "Tile.h"
#include "Unit.h"
#include "UserInterfaceGame.h"
#include "UserInterface.h"
#include "CollisionBox.h"

#pragma region
class Engine;
class Model;
class Unit;
class UserInterfaceGame;
class UserInterface;
struct TileMap;
#pragma endregion

extern "C"

{

enum RenderType
{
	UNIT   = 0,
	MODEL  = 1,
	BOX    = 2
};



	struct RenderObject
	{
#define OFFSETMULTIPLIER 1.40f
#define MINIMALOFFSET 5.0f

		union
		{
			Model* m_model;
			Unit*  m_unit;
			CollisionBox* m_box;

		};

		void SetRenderType(RenderType type) noexcept
		{
			this->m_type = type;
		}

		bool IsPushable() noexcept
		{
			switch (m_type)
			{
			case UNIT:
			{
				return m_unit->m_model->m_flags[2];
				break;
			}
			case MODEL:
			{
				return m_model->m_flags[2];
				break;
			}
			case BOX:
			{
				return m_box->m_pushable;
				break;
			}
			default: return false;
			}
		}

		void Block(bool block = true)
		{
			switch (m_type)
			{
			case UNIT:
			{
				m_unit->m_model->Block(block);
				break;
			}
			case MODEL:
			{
				m_model->Block(block);
				break;
			}
			case BOX:
			{
				break;
			}
			default: return;
			}
		}

		void TranslateXMinus(float offset) noexcept
		{
			float value = (offset*OFFSETMULTIPLIER);
			if ((value) > MINIMALOFFSET)
			{
				value = 0;
				return;
			}
			switch (m_type)
			{
			case UNIT:
			{
				m_unit->m_model->Center.x -= value;
				break;
			}
			case MODEL:
			{
				m_model->Center.x -= value;
				break;
			}
			case BOX:
			{
				m_box->Center.x -= value;
				break;
			}
			}

		}

		void TranslateYMinus(float offset) noexcept
		{
			float value;
			if ((value = (offset*OFFSETMULTIPLIER)) > MINIMALOFFSET)
			{
				value = 0;
				return;
			}
			switch (m_type)
			{
			case UNIT:
			{
				m_unit->m_model->Center.y -= value;
				break;
			}
			case MODEL:
			{
				m_model->Center.y -= value;
				break;
			}
			case BOX:
			{
				m_box->Center.y -= value;
				break;
			}
			}

		}

		void TranslateXPlus(float offset) noexcept
		{
			float value;
			if ((value = (offset*OFFSETMULTIPLIER)) > MINIMALOFFSET)
			{
				value = 0;
				return;
			}
			switch (m_type)
			{
			case UNIT:
			{
				m_unit->m_model->Center.x += value;
				break;
			}
			case MODEL:
			{
				m_model->Center.x += value;
				break;
			}
			case BOX:
			{
				m_box->Center.x += value;
				break;
			}
			}

		}

		void TranslateYPlus(float offset) noexcept
		{
			float value;
			if ((value = (offset*OFFSETMULTIPLIER)) > MINIMALOFFSET)
			{
				value = 0;
				return;
			}
			switch (m_type)
			{
			case UNIT:
			{
				m_unit->m_model->Center.y += value;
				break;
			}
			case MODEL:
			{
				m_model->Center.y += value;
				break;
			}
			case BOX:
			{
				m_box->Center.y += value;
				break;
			}
			}

		}

		void Update() noexcept
		{
			switch (m_type)
			{
			case UNIT:
			{
				m_unit->m_model->UpdatePosition();
				break;
			}
			case MODEL:
			{
				m_model->UpdatePosition();
				break;
			}
			}
		}

		void GoBack() noexcept
		{
			switch (m_type)
			{
			case UNIT:
			{
				m_unit->m_model->GoBack();
				break;
			}
			case MODEL:
			{
				m_model->GoBack();
				break;
			}
			}
		}


		RenderType m_type;

	};

}

class RendererManager
{
public:




	RendererManager(Engine* engine,Shader* shader);
	~RendererManager();

	void PushModel(Model* model);
	void PushBox(CollisionBox* box);
	void PushUnit(Unit* unit);
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update();
	void RemoveAllObjects();

	static RendererManager* GetInstance();
private:
	vector<RenderObject> m_objects;

	Engine* m_engine;
	Shader* m_shader;




	TileMap m_map;
	UserInterface* m_ui;
};

