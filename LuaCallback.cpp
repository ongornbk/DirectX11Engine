#include "ResourceManager.h"
#include "LUAManager.h"
#include "Camera.h"
#include "SettingsC.h"
#include "Engine.h"
#include "Global.h"
#include "GameScene.h"
#include "IPP.h"
#include "Network.h"
#include "LuaPointer.h"
#include "Sorting.h"
#include "UnitGroup.h"
#include "Math.h"

#include <atlbase.h>

#ifdef __cplusplus
extern "C"
#endif // __cplusplus
{


namespace lua_callback
{
#pragma region
	using std::string;
	using std::wstring;
#pragma endregion

#define LUA_STRING lua_tostring
#define LUA_FLOAT (float)lua_tointeger
#define LUA_BOOLEAN lua_toboolean

	static void SetResourceManager(class ResourceManager* const manager);
	static void SetCamera(class Camera* const camera);
	static void Initialize(class Engine* const engine);
	static void SetInput(class Input* const input);
	static void SetRendererManager(class RendererManager* const renderer);

	namespace
	{

		static class ResourceManager*     m_resources;
		static class Camera*              m_camera;
		static class Engine*              m_engine;
		static class Input*               m_input;
		static class Global*              m_global;
		static struct ID3D11Device*        m_device;
		static struct ID3D11DeviceContext* m_deviceContext;
		static class TextureShader*       m_unitsShader;
		static class RendererManager*     m_renderer;

	}

	static void SetRendererManager(
		class RendererManager* const manager
	)
	{
		m_renderer = manager;
	}

	static void SetResourceManager(
		class ResourceManager* const manager
	)
	{
		m_resources = manager;
	}

	static void SetCamera(
		class Camera* const camera
	)
	{
		m_camera = camera;
	}

	static void InitializeGraphics()
	{
		m_device = m_engine->GetGraphics()->GetDevice();
		m_deviceContext = m_engine->GetGraphics()->GetDeviceContext();
		m_unitsShader = (class TextureShader*)m_resources->GetShaderByName("units.fx");
	}

	static void Initialize(
		class Engine* const engine
	)
	{
		m_engine = engine;
		m_global = Global::GetInstance();
	}

	static void SetInput(
		class Input* const input
	)
	{
		m_input = input;
	}

	namespace Resources
	{
		static  int32 LoadTexture(
			struct lua_State* const state
		)
		{
#pragma warning(disable : 4996)
			std::string str = LUA_STRING(state, 1);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			std::wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());
			m_resources->LoadTextureResource(wide_string);
			delete wide_string;
			return 0;
		}

		static  int32 LoadSound(
			struct lua_State* const state
		)
		{
#pragma warning(disable : 4996)
			std::string str = LUA_STRING(state, 1);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			std::wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());
			m_resources->LoadSoundResource(wide_string);
			delete wide_string;
			return 0;
		}

		static  int32 AddModelPaths(
			struct lua_State* const state
		)
		{
			std::string str = LUA_STRING(state, 1);
			m_engine->AddModelPaths(str);
			return 0;
		}

		//static  int32 AddSoundsPaths(
		//	struct lua_State* const state
	//	)
		//{
			//class Unit* const unit = (class Unit* const)(lua_tointeger(state, 1));
			//std::string str = LUA_STRING(state, 2);
			//if (unit)
			//	//unit->LoadSounds(str);
			//return 0;
		//}
	}

	namespace Cameras
	{
		static  int32 InitializeProjectionMatrix(
			struct lua_State* const state
		)
		{
			m_camera->InitializeProjectionMatrix(
				XM_PI / LUA_FLOAT(state, 1),
				Settings::GetAspectRatio(),
				1.0f / LUA_FLOAT(state, 2),
				LUA_FLOAT(state, 3));
			return 0;
		}

		static  int32 InitializeOrthoMatrix(lua_State* state)
		{
			m_camera->InitializeOrthoMatrix(
				Settings::GetResolutionX(),
				Settings::GetResolutionY(),
				1.0f / LUA_FLOAT(state, 1),
				LUA_FLOAT(state, 2)
			);
			return 0;
		}

		static  int32 SetCameraLookAt(
			struct lua_State* const state
		)
		{
			m_global->camera_lookat = XMVectorSet(
				(float)lua_tointeger(state, 1),
				(float)lua_tointeger(state, 2),
				(float)lua_tointeger(state, 3),
				(float)lua_tointeger(state, 4)
			);
			return 0;
		}

		static  int32 SetCameraUp(
			struct lua_State* const state
		)
		{
			m_global->camera_up = XMVectorSet(
				(float)lua_tointeger(state, 1),
				(float)lua_tointeger(state, 2),
				(float)lua_tointeger(state, 3),
				(float)lua_tointeger(state, 4)
			);
			return 0;
		}

		static  int32 SetCameraPosition(
			struct lua_State* const state
		)
		{
			DirectX::XMVECTOR position;
			position.m128_f32[0] = LUA_FLOAT(state, 1);
			position.m128_f32[1] = LUA_FLOAT(state, 2);
			position.m128_f32[2] = LUA_FLOAT(state, 3);
			m_camera->SetPosition(position);
			return 0;
		}

		static  int32 LockCameraOnUnit(
			struct lua_State* const state
		) noexcept
		{
			class Unit* const unit = m_global->m_lastPickedUnit;
			if (unit)
			{
				m_engine->GetCameraControl()->LockCameraPositionOnUnit(unit);
			}
			return 0;
		}

		
	}

	namespace Music
	{
		static  int32 AddMusic(
			struct lua_State* const state
		)
		{
			std::string str = LUA_STRING(state, 1);
			m_engine->AddMusicSound(str, LUA_FLOAT(state, 2), LUA_BOOLEAN(state, 3));
			return 0;
		}

		static  int32 PlayMusic(lua_State* state) noexcept
		{
#pragma warning(disable : 4996)
			std::string str = LUA_STRING(state, 1);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			std::wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());
			m_engine->PlayMusic(wide_string);
			delete wide_string;
			return 0;
		}

		static  int32 AddInterfaceSound(lua_State* state)
		{
			std::string str = LUA_STRING(state, 1);
			m_engine->AddInterfaceSound(str, LUA_FLOAT(state, 2));
			return 0;
		}

		static  int32 PlaySound(lua_State* state) noexcept
		{
#pragma warning(disable : 4996)
			std::string str = LUA_STRING(state, 1);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			std::wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());
			m_engine->PlaySound(wide_string);
			delete wide_string;
			return 0;
		}
	}

	namespace _Network
	{
		static  int32 _StartServer(lua_State* state) noexcept
		{
			//Network::StartServer((uint16)lua_tointeger(state, 1));
			return 0;
		}
	}

	namespace _Game
	{
		static  int32 __PostQuitMessage(
			struct lua_State* const state
		) noexcept
		{
			PostQuitMessage(( int32)lua_tointeger(state, 1));
			return 0;
		}

		static  int32 PauseGame(
			struct lua_State* const state
		)
		{
			m_engine->PauseGame();
			return 0;
		}

		static  int32 ResumeGame(
			struct lua_State* const state
		)
		{
			m_engine->ResumeGame();
			return 0;
		}
	}

	

	static int32_t __IsKeyHit(
		struct lua_State* const state
	) noexcept
	{
		if (m_input->IsKeyHit((unsigned int)lua_tointeger(state,1)))
		{
			lua_pushboolean(state, true);
		}
		else
		{
			lua_pushboolean(state, false);
		}
		return 1;
	}
	static int32 __IsKeyPressed(
		struct lua_State* const state
	) noexcept
	{
		if (m_input->IsKeyDown((uint32)lua_tointeger(state, 1)))
		{
			lua_pushboolean(state, true);
		}
		else
		{
			lua_pushboolean(state, false);
		}
		return 1;
	}

	static int32 __GetMouseState(
		struct lua_State* const state
	) noexcept
	{
		if (m_input->GetMouseState((int32)lua_tointeger(state, 1)))
		{
			lua_pushboolean(state,true);
		}
		else
		{
			lua_pushboolean(state, false);
		}
		return 1;
	}

	static int32 __GetMousePressed(
		struct lua_State* const state
	) noexcept
	{
		lua_pushboolean(state,m_input->GetMousePressed((int32)lua_tointeger(state,1)));
		return 1;
	}

	static int32 CreateUnit(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = new class Unit();
		//m_global->m_lastCreatedRenderContainer = unit;
		lua_pushinteger(state,(lua_Integer)unit);
		return 1;
	}

	static int32 ApplyColorFilter(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		if (unit)
		{
			unit->SetColorFilter(LUA_FLOAT(state, 2), LUA_FLOAT(state, 3), LUA_FLOAT(state, 4), LUA_FLOAT(state, 5));
		}
		return 0;
	}

	static int32 DeleteObject(
		struct lua_State* const state
	) noexcept
	{
		class EObject* const object = (class EObject* const)lua_tointeger(state, 1);
		if (object)
		{
			object->Release();
			CleanupFrame();
			if (object == m_global->m_lastSelectedUnit)
				m_global->m_lastSelectedUnit = nullptr;
		}
		return 0;
	}

	static int32_t PickUnit(
		struct lua_State* const state
	) noexcept
	{
		m_global->m_pickedObject = m_global->m_lastPickedUnit = (class Unit* const)(lua_tointeger(state, 1));//dynamic cast?
			//(class Unit* const )LuaPointer((int32_t)lua_tointeger(state, 1), (int32_t)lua_tointeger(state, 2)).ptr;
		return 0;
	}

	static int32_t PickObject(
		struct lua_State* const state
	) noexcept
	{
		m_global->m_pickedObject = (class EObject* const)lua_tointeger(state, 1);
		return 0;
	}

	static int32 IsSelected(
		struct lua_State* const state
	) noexcept
	{
		class EObject* const object = (class EObject* const)lua_tointeger(state, 1);

		if (object) lua_pushboolean(state, object->m_flags.m_selected);
		else lua_pushboolean(state, false);

		return 1;
	}

	static int32_t CreateDoodads(
		struct lua_State* const state
	) noexcept
	{
		class Doodads* const doodads = new class Doodads();
		m_global->m_lastCreatedRenderContainer = doodads;
		lua_pushinteger(state, (lua_Integer)(doodads));
		//const union LuaPointer lptr(doodads);
		//lua_pushinteger(state, lptr.lua.first);
		//lua_pushinteger(state, lptr.lua.second);
		return 1;
	}

	static int32_t CreateAnimatedDoodads(
		struct lua_State* const state
	) noexcept
	{
		class AnimatedDoodads* const doodads = new class AnimatedDoodads();
		m_global->m_lastCreatedRenderContainer = doodads;
		lua_pushinteger(state, (lua_Integer)(doodads));
		return 1;
	}

	static int32 CreateTree(
		struct lua_State* const state
	) noexcept
	{
		class Tree* const tree = new class Tree();
		m_global->m_lastCreatedRenderContainer = tree;
		lua_pushinteger(state, (lua_Integer)(tree));
		//const union LuaPointer lptr(tree);
		//lua_pushinteger(state, lptr.lua.first);
		//lua_pushinteger(state, lptr.lua.second);
		return 1;
	}

	//static int32_t SetZ(lua_State* state) noexcept
	//{
	//	
	//	RenderContainer* rc = m_global->m_lastCreatedRenderContainer;
	//	if (rc)
	//	{
	//		rc->SetZ(LUA_FLOAT(state, 1));
	//	}
	//	return 0;
	//}

	static int32_t GetMousePosition(
		struct lua_State* const state
	) noexcept
	{
		float xm, ym;
		UserInterface::GetMousePosition(xm, ym);
		m_global->m_lastPoint = DirectX::XMFLOAT3(xm,ym, 0.0f);
		lua_pushnumber(state,(double)xm);
		lua_pushnumber(state,(double)ym);
		return 2;
	}

	static int32_t GetLastSelectedUnit(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = m_global->m_lastSelectedUnit;
		lua_pushinteger(state, (lua_Integer)unit);
		return 1;
	}

	static int32_t PickLastCreatedUnit(
		struct lua_State* const
	) noexcept
	{
		class Unit* const unit = (class Unit*)m_global->m_lastCreatedRenderContainer;
		if (unit)
		{
			m_global->m_lastPickedUnit = unit;
		}
		return 0;
	}

	static int32 GiveTaskGotoPoint(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		if (unit)
		{
			class TaskGotoPoint* const task = new TaskGotoPoint();
			task->destination.x = LUA_FLOAT(state, 2);
			task->destination.y = LUA_FLOAT(state, 3);
			task->object = unit;
			unit->GiveTask(task);
		}
			return 0;
	}

	static int32 SetTaskGotoPoint(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		if (unit)
		{
			class TaskGotoPoint* const task = new TaskGotoPoint();
			task->destination.x = LUA_FLOAT(state, 2);
			task->destination.y = LUA_FLOAT(state, 3);
			task->object = unit;
			unit->SetTask(task);
		}
		return 0;
	}

	static int32 SetTaskAttack(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const object = (class Unit* const)lua_tointeger(state, 1);
		class EObject* const target = (class EObject* const)lua_tointeger(state, 2);
		if (object&&target&&target->m_type==EObject::EObjectType::UNIT)
		{
			if (object->IsAttacking())
			{
				lua_pushboolean(state, true);
			}
			else
			{
				if (object->GetTaskType() == Task::Type::TASKATTACK)
				{
					const TaskAttack* const task = (class TaskAttack* const)object->GetTask();
					if (task)
					{
						if (task->inrange)
							lua_pushboolean(state, false);
						else
							lua_pushboolean(state, true);
					}
					else
					{
						lua_pushboolean(state, true);
					}
					
				}
				else
				{
					class TaskAttack* const task = new TaskAttack();
					task->object = object;
					task->target = target;
					task->Initialize();
					object->SetTask(task);
					lua_pushboolean(state, false);
				}
			}
				
		}
		else
		{
			return true;
		}
		return 1;
	}

	static int32_t SetFootstepsSound(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			std::string  str = lua_tostring(state, 1);
			class Sound* const sound = Canals::GetInstance()->__GetSound(str);
			unit->SetFootstepsSound(sound);
		}
		return 0;
	}

	static int32_t BeginRunning(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->BeginRunning();
		}
		return 0;
	}

	static int32_t EndRunning(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->EndRunning();
		}
		return 0;
	}

	static int32 CleanTasks(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		if (unit)
		unit->DiscardTasks();
		return 0;
	}

	

	static int32 InitializeUnit(
		struct lua_State* const state
	) noexcept
	{
		///class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		class Unit* const unit = dynamic_cast<class Unit* const>((class EObject* const)lua_tointeger(state, 1));
		if (unit)
		{
		std::string str = lua_tostring(state, 2);
		const float p_z = (const float)lua_tointeger(state, 7);

		wchar_t* wide_string = new wchar_t[str.length() + 1];
		std::wstring ws = std::wstring(str.begin(), str.end()).c_str();
		wcscpy(wide_string, ws.c_str());

			unit->Initialize(
				m_device,
				m_deviceContext,
				m_unitsShader,
				wide_string,
				(float)lua_tointeger(state, 3),
				(float)lua_tointeger(state, 4),
				struct DirectX::XMFLOAT3((float)lua_tointeger(state, 5),(float)lua_tointeger(state, 6),p_z),
				lua_toboolean(state, 8)
			);
			m_renderer->PushUnit(unit,(int32)p_z);

			delete wide_string;
		}
		return 0;
		
	}

	static int32 InitializeDoodads(
		struct lua_State* const state
	) noexcept
	{
		class Doodads* const doodads = (class Doodads* const)lua_tointeger(state, 1);
		if (doodads)
		{
			std::string str = lua_tostring(state, 2);
			const float p_x = (const float)lua_tointeger(state, 5);
			const float p_y = (const float)lua_tointeger(state, 6);
			const float p_z = (const float)lua_tointeger(state, 7);

			
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			std::wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());


			doodads->Initialize(
				m_device,
				m_deviceContext,
				m_unitsShader,
				wide_string,
				(const float)lua_tointeger(state, 3),
				(const float)lua_tointeger(state, 4),
				struct DirectX::XMFLOAT3(p_x, p_y, p_z)
			);
			m_renderer->PushDoodads(doodads, (int32)p_z);

			delete wide_string;
		}
		return 0;

	}

	static int32 InitializeAnimatedDoodads(
		struct lua_State* const state
	) noexcept
	{
		class AnimatedDoodads* const doodads = (class AnimatedDoodads* const)lua_tointeger(state, 1);
		if (doodads)
		{
			std::string str = lua_tostring(state, 2);
			const float p_x = (const float)lua_tointeger(state, 5);
			const float p_y = (const float)lua_tointeger(state, 6);
			const int32 z   = (const int32)lua_tointeger(state, 7);
			const float p_z = (const float)z;

			wchar_t* wide_string = new wchar_t[str.length() + 1];
			std::wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());


			doodads->Initialize(
				m_device,
				m_deviceContext,
				m_unitsShader,
				wide_string,
				(float)lua_tointeger(state, 3),
				(float)lua_tointeger(state, 4),
				struct DirectX::XMFLOAT3(p_x, p_y, p_z)
			);
			m_renderer->PushAnimatedDoodads(doodads,z);

			delete wide_string;
		}
		return 0;

	}

	static int32 InitializeTree(
		struct lua_State* const state
	) noexcept
	{
		class Tree* const tree = (class Tree* const)lua_tointeger(state, 1);
		if (tree)
		{
			string str = lua_tostring(state, 2);
			const float p_x = (const float)lua_tointeger(state, 5);
			const float p_y = (const float)lua_tointeger(state, 6);
			const float p_z = (const float)lua_tointeger(state, 7);

			
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());

			tree->Initialize(
				m_device,
				m_deviceContext,
				m_unitsShader,
				wide_string,
				(float)lua_tointeger(state, 3),
				(float)lua_tointeger(state, 4),
				struct DirectX::XMFLOAT3(p_x, p_y, p_z)
			);
			m_renderer->PushTree(tree, (int32)p_z);

			delete wide_string;
				
		}
		return 0;

	}

	static int32 SetRenderingFlag(
		struct lua_State* const state
	) noexcept
	{
		class EObject* const object = (class EObject* const)lua_tointeger(state, 1);
		if (object)
		{
			object->m_flags.m_rendering =  (bool)lua_toboolean(state, 2);
		}
		return 0;
	}

	static int32 SetShadowFlag(
		struct lua_State* const state
	) noexcept
	{
		class EObject* const object = (class EObject* const)lua_tointeger(state, 1);
		if (object)
		{
			object->m_flags.m_cast_shadow = (bool)lua_toboolean(state, 2);
		}
		return 0;
	}

	static int32 SetPushableFlag(
		struct lua_State* const state
	) noexcept
	{
		class EObject* const object = (class EObject* const)lua_tointeger(state, 1);
		if (object)
		{
			object->m_flags.m_pushable = (bool)lua_toboolean(state, 2);
		}
		return 0;
	}

	static int32 SetSelectableFlag(
		struct lua_State* const state
	) noexcept
	{
		class EObject* const object = (class EObject* const)lua_tointeger(state, 1);
		if (object)
		{
			object->m_flags.m_selectable = (bool)lua_toboolean(state, 2);
		}
		return 0;
	}

	static int32 SetCollisionPriority(
		struct lua_State* const state
	) noexcept
	{
		class EObject* const object = (class EObject* const)lua_tointeger(state, 1);
		if (object)
		{
			object->collisionPriority = (int32)lua_tointeger(state, 2);
		}
		return 0;
	}

	static int32_t GetRenderContainerFlag(lua_State* state) noexcept
	{
		//RenderContainer* rc = m_global->m_lastCreatedRenderContainer;
	//	if (rc)
		{
			//lua_pushboolean(state, rc->m_flag[lua_tointeger(state,1)]);
		}
		return 1;
	}

	static int32_t SetNumberOfFrames(
		struct lua_State* const state
	) noexcept
	{
		class AnimatedDoodads* const animatedDoodad = (AnimatedDoodads*)lua_tointeger(state, 1);
		if (animatedDoodad)
		{
			animatedDoodad->SetNumberOfFrames(LUA_FLOAT(state, 2));
		}
		return 0;
	}

	static int32 SetWalkingStance(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
			enum Unit::WalkingStance ws;
			switch (lua_tointeger(state, 2))
			{
			case 0:
				ws = Unit::WalkingStance::WS_WALK;
				break;
			case 1:
				ws = Unit::WalkingStance::WS_RUN;
				break;
			}
			unit->SetWalkingStance(ws);
		return 0;
	}

	namespace _Units
	{
		static int32 ChangeWalkingStance(
			struct lua_State* const state
		) noexcept
		{
			class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
			if(unit)
			unit->ChangeWalkingStance();
			return 0;
		}
	}
	

	static int32 SetUnitSpeed(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		if (unit)
		{
			unit->SetSpeed((float)lua_tointeger(state,2));
		}
		return 0;
	}

	static int32 SetUnitPosition(
		struct lua_State* const state
	)
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		if (unit)
		{
			unit->SetPosition(struct DirectX::XMFLOAT3((float)lua_tointeger(state, 2), (float)lua_tointeger(state, 3), (float)lua_tointeger(state, 4)));
		}
		return 0;
	}
	
	static int32 GetUnitPosition(
		struct lua_State* const state
	)
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		if (unit)
		{
			const struct DirectX::XMFLOAT3& position = unit->m_boundingSphere.Center;
			lua_pushinteger(state,(int32)position.x);
			lua_pushinteger(state,(int32)position.y);
		}
		else
		{
			lua_pushinteger(state, 0);
			lua_pushinteger(state, 0);
		}
		return 2;
	}

	static int32 GetUnitsInRange(
		struct lua_State* const state
	)
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		const float range = LUA_FLOAT(state, 2);
		if (unit)
		{
			m_global->m_stack = m_renderer->GetUnitsInRange(unit, range);
			m_global->m_size = (uint32)m_global->m_stack.size();
		}
		return 0;
	}

	static int32 PopGroup(
		struct lua_State* const state
	)
	{
		
		if (m_global->m_stack.empty())
		{
			lua_pushinteger(state, 0);
		}
		else
		{
			lua_pushinteger(state, (lua_Integer)m_global->m_stack.top());
			m_global->m_stack.pop();
		}
		return 1;
	}

	static  int32 GetSize(
		struct lua_State* const state
	)
	{
		lua_pushinteger(state, (lua_Integer)m_global->m_size);
		return 1;
	}

	static  int32 SetUnitRotations(
		struct lua_State* const state
	)
	{
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 1);
		if (unit)
		{
			unit->SetRotations((int32)lua_tointeger(state, 2));
		}
		return 0;
	}

	static  int32 SetInterface(lua_State* state)
	{
		m_renderer->SetInterface((unsigned int)lua_tointeger(state,1), m_resources->GetShaderByName("texture.fx"));
		return 0;
	}

	

	static int LoadFont(
		struct lua_State* const state
	) //EXPORTED
	{
		m_engine->AddFont(lua_tostring(state, 1), LUA_FLOAT(state, 2), LUA_FLOAT(state, 3));
		return 0;
	}

	static int32_t SetTilesMultiplier(
		struct lua_State* const state
	) noexcept
	{
		SetCellMultiplier(LUA_FLOAT(state, 1));
		return 0;
	}

	static int32_t __LoadTilesResourceFromFile(
		struct lua_State* const state
	)
	{
		LoadTilesResourceFromFile(lua_tostring(state, 1));
		return 0;
	}

	static int32 SetTile(
		struct lua_State* const state
	) //EXPORTED
	{
		struct DirectX::XMFLOAT2 position(m_global->m_lastPoint.x, m_global->m_lastPoint.y);
		m_renderer->SetTile(position,(int32)lua_tointeger(state, 1), (int32)lua_tointeger(state, 2));
		return 0;
	}

	static int32 SaveInstance(
		struct lua_State* const state
	)
	{
		m_renderer->SaveInstanceToFile(lua_tostring(state, 1));
		return 0;
	}

	static int32 SetLastSelectedUnit(
		struct lua_State* const state
	)
	{
		m_global->m_lastSelectedUnit = (class Unit* const)lua_tointeger(state, 1);
		return 0;
	}

	static int32 LoadInstance(
		struct lua_State* const state
	)
	{
		m_renderer->LoadInstanceToFile(lua_tostring(state, 1));
		return 0;
	}

	static int32 GetInput(
		struct lua_State* const state
	)
	{
		lua_pushstring(state, (ipp::Console::GetInput().c_str()));
		return 1;
	}

	static int32 Println(
		struct lua_State* const state
	)
	{
		ipp::Console::Println(lua_tostring(state, 1));
		return 0;
	}

	static int32 GameChatMessageFront(
		struct lua_State* const state
	)
	{
		class GameChat* const game_chat = UserInterfaceGame::GetGameChat();
		if (game_chat)
		{
			std::string str = lua_tostring(state, 1);
			game_chat->PushTextFront(str);
		}
		else
		{
			ipp::Console::SetTextColor(ipp::TextColors::RED);///
			ipp::Console::Println("Game chat has not been initialized!");///
		}
		return 0;
	}

	static int32 GameChatMessageBack(
		struct lua_State* const state
	)
	{
		class GameChat* const game_chat = UserInterfaceGame::GetGameChat();
		if (game_chat)
		{
			std::string str = lua_tostring(state, 1);
			game_chat->PushText(str);
		}
		else
		{
			ipp::Console::SetTextColor(ipp::TextColors::RED);///
			ipp::Console::Println("Game chat has not been initialized!");///
		}
		return 0;
	}

	static int32 ClearGameChat(
		struct lua_State* const state
	)
	{
		class GameChat* const game_chat = UserInterfaceGame::GetGameChat();
		if (game_chat)
		{
			game_chat->ClearQueue();
		}
		return 0;
	}

	static int32 CreateUnitGroup(
		struct lua_State* const state
	)
	{
		class UnitGroup* const unit_group = new UnitGroup();
		lua_pushinteger(state, (lua_Integer)unit_group);
		return 1;
	}

	static int32 DeleteUnitGroup(
		struct lua_State* const state
	)
	{
		class UnitGroup* const unit_group = (class UnitGroup* const)lua_tointeger(state, 1);
		if (unit_group)
		{
			unit_group->clear();
			delete unit_group;
		}
		return 0;
	}

	static int32 GetUnitsInGroup(
		struct lua_State* const state
	)
	{
		class UnitGroup* const unit_group = (class UnitGroup* const)lua_tointeger(state, 1);
		if (unit_group)
		{
			m_global->m_stack = unit_group->GetStack();
			m_global->m_size = (uint32)m_global->m_stack.size();
		}
		return 0;
	}

	static int32 AddUnitToGroup(
		struct lua_State* const state
	)
	{
		class UnitGroup* const unit_group = (class UnitGroup* const)lua_tointeger(state, 1);
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 2);
		
		if (unit_group&& unit)
		{
			unit_group->Insert(unit);
		}
		return 0;
	}

	static int32 RemoveUnitFromGroup(
		struct lua_State* const state
	)
	{
		class UnitGroup* const unit_group = (class UnitGroup* const)lua_tointeger(state, 1);
		class Unit* const unit = (class Unit* const)lua_tointeger(state, 2);

		if (unit_group && unit)
		{
			unit_group->Remove(unit);
		}
		return 0;
	}

	static int32 GetDistanceBetweenUnits(
		struct lua_State* const state
	)
	{
		class Unit* const unit0 = (class Unit* const)lua_tointeger(state, 1);
		class Unit* const unit1 = (class Unit* const)lua_tointeger(state, 2);

		if (unit0 && unit1)
		{
			const float distance = XMFloat3Distance2D(unit0->GetPosition(), unit1->GetPosition());
			lua_pushnumber(state, (lua_Number)distance);
		}
		else
			lua_pushnumber(state, 0.);
		return 1;
	}

	static int32 StartCasting(
		struct lua_State* const state
	)
	{
		class Unit* const unit0 = (class Unit* const)lua_tointeger(state, 1);
		const DirectX::XMFLOAT2 point = DirectX::XMFLOAT2((float)lua_tonumber(state, 2), (float)lua_tonumber(state, 3));

		if (unit0)
		{
			unit0->StartCasting(point);
		}

		return 0;
	}



	static void RegisterFunctions()
	{
		struct lua_State* const m_lua = lua::GetInstance();

		//Resources
		lua_register(m_lua, "LoadTexture", lua_callback::Resources::LoadTexture);
		lua_register(m_lua, "LoadSound", lua_callback::Resources::LoadSound);
		lua_register(m_lua, "AddModelPaths", lua_callback::Resources::AddModelPaths);
		//Cameras
		lua_register(m_lua, "InitializeProjectionMatrix", lua_callback::Cameras::InitializeProjectionMatrix);
		lua_register(m_lua, "InitializeOrthoMatrix", lua_callback::Cameras::InitializeOrthoMatrix);
		lua_register(m_lua, "SetCameraPosition", lua_callback::Cameras::SetCameraPosition);
		lua_register(m_lua, "LockCameraOnUnit", lua_callback::Cameras::LockCameraOnUnit);
		lua_register(m_lua, "SetCameraLookAt", lua_callback::Cameras::SetCameraLookAt);
		lua_register(m_lua, "SetCameraUp", lua_callback::Cameras::SetCameraUp);
		//Music
		lua_register(m_lua, "AddMusic", lua_callback::Music::AddMusic);
		lua_register(m_lua, "PlayMusic", lua_callback::Music::PlayMusic);
		lua_register(m_lua, "AddInterfaceSound", lua_callback::Music::AddInterfaceSound);
		lua_register(m_lua, "PlaySound", lua_callback::Music::PlaySound);
		//System
		lua_register(m_lua, "PostQuitMessage", lua_callback::_Game::__PostQuitMessage);
		lua_register(m_lua, "SaveInstance", lua_callback::SaveInstance);
		lua_register(m_lua, "LoadInstance", lua_callback::LoadInstance);
		//Input
		lua_register(m_lua, "IsKeyHit", lua_callback::__IsKeyHit);
		lua_register(m_lua, "IsKeyPressed", lua_callback::__IsKeyPressed);
		lua_register(m_lua, "GetMouseState", lua_callback::__GetMouseState);
		lua_register(m_lua, "GetMousePressed", lua_callback::__GetMousePressed);
		lua_register(m_lua, "GetMousePosition", lua_callback::GetMousePosition);
		
		//EObject
		lua_register(m_lua, "SetPushableFlag", lua_callback::SetPushableFlag);//@@
		lua_register(m_lua, "SetRenderingFlag", lua_callback::SetRenderingFlag);//@@
		lua_register(m_lua, "SetShadowFlag", lua_callback::SetShadowFlag);//@@
		lua_register(m_lua, "SetSelectableFlag", lua_callback::SetSelectableFlag);//@@
		lua_register(m_lua, "SetCollisionPriority", lua_callback::SetCollisionPriority);//@@
		lua_register(m_lua, "PickObject", lua_callback::PickObject);
		//lua_register(m_lua, "SetZ", lua_callback::SetZ);
		//Units
		lua_register(m_lua,"CreateUnit", lua_callback::CreateUnit);//@@
		lua_register(m_lua,"InitializeUnit", lua_callback::InitializeUnit);//@@
		lua_register(m_lua,"SetWalkingStance", lua_callback::SetWalkingStance);//@@
		lua_register(m_lua,"ChangeWalkingStance", lua_callback::_Units::ChangeWalkingStance);//@@
		lua_register(m_lua,"SetUnitSpeed", lua_callback::SetUnitSpeed);//@@
		lua_register(m_lua,"SetUnitRotations", lua_callback::SetUnitRotations);//@@
		lua_register(m_lua, "PickUnit", lua_callback::PickUnit);//@@
		lua_register(m_lua, "DeleteObject", lua_callback::DeleteObject);//@@
		lua_register(m_lua, "IsSelected", lua_callback::IsSelected);//@@
		lua_register(m_lua, "SetFootstepsSound", lua_callback::SetFootstepsSound);
		lua_register(m_lua, "ApplyColorFilter", lua_callback::ApplyColorFilter);
		lua_register(m_lua, "BeginRunning", lua_callback::BeginRunning);
		lua_register(m_lua, "EndRunning", lua_callback::EndRunning);
		lua_register(m_lua, "SetLastSelectedUnit", lua_callback::SetLastSelectedUnit);
		lua_register(m_lua, "GetDistanceBetweenUnits", lua_callback::GetDistanceBetweenUnits);
		lua_register(m_lua, "StartCasting", lua_callback::StartCasting);
		//Doodads
		lua_register(m_lua, "CreateDoodads", lua_callback::CreateDoodads);
		lua_register(m_lua, "InitializeDoodads", lua_callback::InitializeDoodads);
		//Animated Doodads
		lua_register(m_lua, "CreateAnimatedDoodads", lua_callback::CreateAnimatedDoodads);
		lua_register(m_lua, "InitializeAnimatedDoodads", lua_callback::InitializeAnimatedDoodads);
		lua_register(m_lua, "SetNumberOfFrames", lua_callback::SetNumberOfFrames);
		//Trees
		lua_register(m_lua, "CreateTree", lua_callback::CreateTree);
		lua_register(m_lua, "InitializeTree", lua_callback::InitializeTree);
		//lua_register(m_lua,"PickHero", lua_callback::PickHero);
		lua_register(m_lua, "PickLastCreatedUnit", lua_callback::PickLastCreatedUnit);
		lua_register(m_lua, "GetLastSelectedUnit", lua_callback::GetLastSelectedUnit);
		lua_register(m_lua,"GiveTaskGotoPoint", lua_callback::GiveTaskGotoPoint);//@@
		lua_register(m_lua,"SetTaskGotoPoint", lua_callback::SetTaskGotoPoint);//@@
		lua_register(m_lua, "SetTaskAttack", lua_callback::SetTaskAttack);//@@
		lua_register(m_lua,"CleanTasks", lua_callback::CleanTasks);//@@

		lua_register(m_lua, "SetUnitPosition", lua_callback::SetUnitPosition);//@@
		lua_register(m_lua, "GetUnitsInRange", lua_callback::GetUnitsInRange);//@@
		lua_register(m_lua, "GetSize", lua_callback::GetSize);//@@
		lua_register(m_lua, "PopGroup", lua_callback::PopGroup);//@@
		lua_register(m_lua, "GetUnitPosition", lua_callback::GetUnitPosition);//@@
		//RendererManager
		lua_register(m_lua,"SetInterface", lua_callback::SetInterface);
		//Engine
		lua_register(m_lua,"ResumeGame", lua_callback::_Game::ResumeGame);
		lua_register(m_lua,"PauseGame", lua_callback::_Game::PauseGame);
		//Fonts
		lua_register(m_lua, "LoadFont", lua_callback::LoadFont);
		//Tiles
		lua_register(m_lua, "SetTilesMultiplier", lua_callback::SetTilesMultiplier);
		lua_register(m_lua, "SetTile", lua_callback::SetTile);
		lua_register(m_lua, "LoadTilesResourceFromFile", lua_callback::__LoadTilesResourceFromFile);
		//Console
		lua_register(m_lua, "GetInput", lua_callback::GetInput);
		lua_register(m_lua, "Println", lua_callback::Println);
		//Network
		lua_register(m_lua, "StartServer", lua_callback::_Network::_StartServer);
		//GameChat
		lua_register(m_lua, "ClearGameChat", lua_callback::ClearGameChat);
		lua_register(m_lua, "GameChatMessageBack", lua_callback::GameChatMessageBack);
		lua_register(m_lua, "GameChatMessageFront", lua_callback::GameChatMessageFront);
		//UnitGroup
		lua_register(m_lua, "CreateUnitGroup", lua_callback::CreateUnitGroup);
		lua_register(m_lua, "DeleteUnitGroup", lua_callback::DeleteUnitGroup);
		lua_register(m_lua, "GetUnitsInGroup", lua_callback::GetUnitsInGroup);
		lua_register(m_lua, "AddUnitToGroup", lua_callback::AddUnitToGroup);
		lua_register(m_lua, "RemoveUnitFromGroup", lua_callback::RemoveUnitFromGroup);
	}

}

}
