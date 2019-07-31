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

	static void SetResourceManager(ResourceManager* manager);
	static void SetCamera(Camera* camera);
	static void Initialize(Engine* engine);
	static void SetInput(Input* input);
	static void SetRendererManager(RendererManager* renderer);

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
			string str = LUA_STRING(state, 1);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());
			m_engine->PlayMusic(wide_string);
			delete wide_string;
			return 0;
		}

		static  int32 AddInterfaceSound(lua_State* state)
		{
			string str = LUA_STRING(state, 1);
			m_engine->AddInterfaceSound(str, LUA_FLOAT(state, 2));
			return 0;
		}

		static  int32 PlaySound(lua_State* state) noexcept
		{
#pragma warning(disable : 4996)
			string str = LUA_STRING(state, 1);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			wstring ws = std::wstring(str.begin(), str.end()).c_str();
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
		static  int32 __PostQuitMessage(lua_State* state) noexcept
		{
			PostQuitMessage(( int32)lua_tointeger(state, 1));
			return 0;
		}

		static  int32 PauseGame(lua_State* state)
		{
			m_engine->PauseGame();
			return 0;
		}

		static  int32 ResumeGame(lua_State* state)
		{
			m_engine->ResumeGame();
			return 0;
		}
	}

	

	static int32_t __IsKeyHit(lua_State* state) noexcept
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
	static int32_t __IsKeyPressed(lua_State* state) noexcept
	{
		if (m_input->IsKeyDown((uint32_t)lua_tointeger(state, 1)))
		{
			lua_pushboolean(state, true);
		}
		else
		{
			lua_pushboolean(state, false);
		}
		return 1;
	}

	static int32_t __GetMouseState(lua_State* state) noexcept
	{
		if (m_input->GetMouseState((uint32_t)lua_tointeger(state, 1)))
		{
			lua_pushboolean(state,true);
		}
		else
		{
			lua_pushboolean(state, false);
		}
		return 1;
	}

	static int32_t __GetMousePressed(lua_State* state) noexcept
	{
		lua_pushboolean(state,m_input->GetMousePressed((int32_t)lua_tointeger(state,1)));
		return 1;
	}

	static int32_t CreateUnit(lua_State* state) noexcept
	{
		class Unit* const unit = new class Unit();
		m_global->m_lastCreatedRenderContainer = unit;
		const union LuaPointer lptr(unit);
		lua_pushinteger(state, lptr.lua.first);
		lua_pushinteger(state, lptr.lua.second);
		return 2;
	}

	static int32_t DeleteUnit(
		struct lua_State* const state
	) noexcept
	{
		class Unit* const unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->Release();
			CleanupFrame();
		}
		return 0;
	}

	static int32_t PickUnit(lua_State* state) noexcept
	{
		m_global->m_lastPickedUnit = (Unit*)LuaPointer((int32_t)lua_tointeger(state, 1), (int32_t)lua_tointeger(state, 2)).ptr;
		return 0;
	}

	static int32_t SetFlags(lua_State* state) noexcept
	{
//		m_global->m_lastFlags.SetFlags(lua_tostring(state, 1));
		return 0;
	}

	static int32_t CreateDoodads(lua_State* state) noexcept
	{
		Doodads* doodads = new Doodads();
		m_global->m_lastCreatedRenderContainer = doodads;
		LuaPointer lptr(doodads);
		lua_pushinteger(state, lptr.lua.first);
		lua_pushinteger(state, lptr.lua.second);
		return 2;
	}

	static int32_t CreateAnimatedDoodads(lua_State* state) noexcept
	{
		AnimatedDoodads* doodads = new AnimatedDoodads();
		m_global->m_lastCreatedRenderContainer = doodads;
		return 0;
	}

	static int32_t CreateTree(lua_State* state) noexcept
	{
		Tree* tree = new Tree();
		m_global->m_lastCreatedRenderContainer = tree;
		return 0;
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

	static int32_t GetMousePosition(lua_State* state) noexcept
	{
		int32 xm, ym;
		UserInterface::GetMousePosition(xm, ym);
		m_global->m_lastPoint = XMFLOAT3((float)xm,(float)ym, 0.0f);
		lua_pushinteger(state, (int32_t)xm);
		lua_pushinteger(state, (int32_t)ym);
		return 2;
	}

	static int32_t GetLastSelectedUnit(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastSelectedUnit;
		if (unit)
		{
			LuaPointer lptr(unit);
			lua_pushinteger(state, lptr.lua.first);
			lua_pushinteger(state, lptr.lua.second);
		}
		else
		{
			LuaPointer lptr(unit);
			lua_pushinteger(state, 0);
			lua_pushinteger(state, 0);
		}
		return 2;
	}

	static int32_t PickLastCreatedUnit(struct lua_State* const) noexcept
	{
		class Unit* const unit = (class Unit*)m_global->m_lastCreatedRenderContainer;
		if (unit)
		{
			m_global->m_lastPickedUnit = unit;
		}
		return 0;
	}

	static int32_t GiveTaskGotoPoint(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			TaskGotoPoint* task = new TaskGotoPoint();
			task->destination.x = LUA_FLOAT(state, 1);
			task->destination.y = LUA_FLOAT(state, 2);
			task->object = unit;
			unit->GiveTask(task);
		}
			return 0;
	}

	static int32_t SetTaskGotoPoint(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			TaskGotoPoint* task = new TaskGotoPoint();
			task->destination.x = LUA_FLOAT(state, 1);
			task->destination.y = LUA_FLOAT(state, 2);
			task->object = unit;
			unit->SetTask(task);
		}
		return 0;
	}

	static int32_t SetFootstepsSound(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			string  str = lua_tostring(state, 1);
			class Sound* sound = Canals::GetInstance()->__GetSound(str);
			unit->SetFootstepsSound(sound);
		}
		return 0;
	}

	static int32_t BeginRunning(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->BeginRunning();
		}
		return 0;
	}

	static int32_t EndRunning(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->EndRunning();
		}
		return 0;
	}

	static int32_t CleanTasks(lua_State* state) noexcept
	{

		m_global->m_lastPickedUnit->DiscardTasks();
		return 0;
	}

	

	static int32_t InitializeUnit(lua_State* state) noexcept
	{
		class Unit* const unit = m_global->m_lastPickedUnit;
		if (unit)
		{
		std::string str = lua_tostring(state, 1);
		const float p_z = (float)lua_tointeger(state, 6);

		wchar_t* wide_string = new wchar_t[str.length() + 1];
		std::wstring ws = std::wstring(str.begin(), str.end()).c_str();
		wcscpy(wide_string, ws.c_str());

			unit->Initialize(
				m_device,
				m_deviceContext,
				m_unitsShader,
				wide_string,
				(float)lua_tointeger(state, 2),
				(float)lua_tointeger(state, 3),
				struct DirectX::XMFLOAT3((float)lua_tointeger(state, 4),(float)lua_tointeger(state, 5),p_z),
				lua_toboolean(state, 7)
			);
			m_renderer->PushUnit(unit,(int32)p_z);

			delete wide_string;
		}
		return 0;
		
	}

	static int32_t InitializeDoodads(lua_State* state) noexcept
	{
		Doodads* doodads = (Doodads*)m_global->m_lastCreatedRenderContainer;
		if (doodads)
		{
			string str = lua_tostring(state, 1);
			float size = (float)lua_tointeger(state, 2);
			float collision = (float)lua_tointeger(state, 3);
			float p_x = (float)lua_tointeger(state, 4);
			float p_y = (float)lua_tointeger(state, 5);
			float p_z = (float)lua_tointeger(state, 6);

			XMFLOAT3 pos(p_x, p_y, p_z);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());


			doodads->Initialize(m_device, m_deviceContext, m_unitsShader, wide_string, size, collision, pos);
			m_renderer->PushDoodads(doodads, (int32)p_z);

			delete wide_string;
		}
		return 0;

	}

	static int32_t InitializeAnimatedDoodads(lua_State* state) noexcept
	{
		AnimatedDoodads* doodads = (AnimatedDoodads*)m_global->m_lastCreatedRenderContainer;
		if (doodads)
		{
			string str = lua_tostring(state, 1);
			float size = (float)lua_tointeger(state, 2);
			float collision = (float)lua_tointeger(state, 3);
			float p_x = (float)lua_tointeger(state, 4);
			float p_y = (float)lua_tointeger(state, 5);
			int8_t z = (int8_t)lua_tointeger(state, 6);
			float p_z = (float)z;
			

			XMFLOAT3 pos(p_x, p_y, p_z);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());


			doodads->Initialize(m_device, m_deviceContext, m_unitsShader, wide_string, size, collision, pos);
			m_renderer->PushAnimatedDoodads(doodads,z);

			delete wide_string;
		}
		return 0;

	}

	static int32_t InitializeTree(lua_State* state) noexcept
	{
		Tree* tree = (Tree*)m_global->m_lastCreatedRenderContainer;
		if (tree)
		{
			string str = lua_tostring(state, 1);
			float size = (float)lua_tointeger(state, 2);
			float collision = (float)lua_tointeger(state, 3);
			float p_x = (float)lua_tointeger(state, 4);
			float p_y = (float)lua_tointeger(state, 5);
			float p_z = (float)lua_tointeger(state, 6);

			XMFLOAT3 pos(p_x, p_y, p_z);
			wchar_t* wide_string = new wchar_t[str.length() + 1];
			wstring ws = std::wstring(str.begin(), str.end()).c_str();
			wcscpy(wide_string, ws.c_str());

			tree->Initialize(m_device, m_deviceContext, m_unitsShader, wide_string, size, collision, pos);
			m_renderer->PushTree(tree, (int32)p_z);

			delete wide_string;
				
		}
		return 0;

	}

	static int32_t SetRenderingFlag(lua_State* state) noexcept
	{
		class EObject* object = m_global->m_lastPickedUnit;
		if (object)
		{
			object->m_flags.m_rendering =  (bool)lua_toboolean(state, 1);
		}
		return 0;
	}

	static int32_t SetShadowFlag(lua_State* state) noexcept
	{
		class EObject* object = m_global->m_lastPickedUnit;
		if (object)
		{
			object->m_flags.m_cast_shadow = (bool)lua_toboolean(state, 1);
		}
		return 0;
	}

	static int32_t SetPushableFlag(lua_State* state) noexcept
	{
		class EObject* object = m_global->m_lastPickedUnit;
		if (object)
		{
			object->m_flags.m_pushable = (bool)lua_toboolean(state, 1);
		}
		return 0;
	}

	static int32_t SetSelectableFlag(lua_State* state) noexcept
	{
		class EObject* object = m_global->m_lastPickedUnit;
		if (object)
		{
			object->m_flags.m_selectable = (bool)lua_toboolean(state, 1);
		}
		return 0;
	}

	static int32_t SetCollisionPriority(lua_State* state) noexcept
	{
		class EObject* object = m_global->m_lastPickedUnit;
		if (object)
		{
			object->collisionPriority = (int32)lua_tointeger(state, 1);
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

	static int32_t SetNumberOfFrames(lua_State* state) noexcept
	{
		AnimatedDoodads* ad = (AnimatedDoodads*)m_global->m_lastCreatedRenderContainer;
		if (ad)
		{
			ad->SetNumberOfFrames(LUA_FLOAT(state, 1));
		}
		return 0;
	}

	static int32_t SetWalkingStance(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
			Unit::WalkingStance ws;
			switch (lua_tointeger(state, 1))
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
		static  int32 ChangeWalkingStance(lua_State* state) noexcept
		{
			m_global->m_lastPickedUnit->ChangeWalkingStance();
			return 0;
		}
	}
	

	static int32_t SetUnitSpeed(lua_State* state) noexcept
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->SetSpeed((float)lua_tointeger(state,1));
		}
		return 0;
	}

	static int32_t PushUnitVariable(lua_State* state) noexcept
	{
		std::string name = LUA_STRING(state, 1);
		bool result = m_global->m_variables.PushUnit(name, m_global->m_lastPickedUnit);
		lua_pushboolean(state, result);
		return 1;
	}

	static int EraseUnitVariable(lua_State* state)
	{
		std::string name = LUA_STRING(state, 1);
		bool result = m_global->m_variables.EraseUnit(name);
		lua_pushboolean(state, result);
		return 1;
	}

	static int GetUnitVariable(lua_State* state)
	{
		std::string name = LUA_STRING(state, 1);
		Unit* unit = m_global->m_variables.GetUnit(name);
		if (unit)
		{
			m_global->m_lastPickedUnit = unit;
			lua_pushboolean(state, true);
		}
		else
		lua_pushboolean(state, false);
		return 1;
	}

	static int SetUnitPosition(lua_State* state)
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->SetPosition(XMFLOAT3((float)lua_tointeger(state, 1), (float)lua_tointeger(state, 2), (float)lua_tointeger(state, 3)));
		}
		return 0;
	}
	
	static int GetUnitPosition(lua_State* state)
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			XMFLOAT3 position;
			position = unit->m_boundingSphere.Center;
			lua_pushinteger(state,(int32)position.x);
			lua_pushinteger(state,(int32)position.y);
			return 2;
		}
		return 0;
	}

	static int GetUnitsInRange(lua_State* state)
	{
		Unit* unit = m_global->m_lastPickedUnit;
		float range = LUA_FLOAT(state, 1);
		if (unit)
		{
			m_global->m_stack = m_renderer->GetUnitsInRange(unit, range);
			m_global->m_size = (uint32)m_global->m_stack.size();
		}
		return 0;
	}

	static int PopGroup(lua_State* state)
	{
		
		if (m_global->m_stack.empty())
		{
			lua_pushboolean(state, false);
		}
		else
		{
			m_global->m_lastPickedUnit = m_global->m_stack.top();
			m_global->m_stack.pop();
			lua_pushboolean(state, true);
		}
		return 1;
	}

	static  int32 GetSize(lua_State* state)
	{
		lua_pushinteger(state, (int)m_global->m_size);
		return 1;
	}

	static  int32 SetUnitRotations(lua_State* state)
	{
		Unit* unit = m_global->m_lastPickedUnit;
		if (unit)
		{
			unit->SetRotations((int32)lua_tointeger(state, 1));
		}
		return 0;
	}

	static  int32 SetInterface(lua_State* state)
	{
		m_renderer->SetInterface((unsigned int)lua_tointeger(state,1), m_resources->GetShaderByName("texture.fx"));
		return 0;
	}

	

	static int LoadFont(lua_State* state) //EXPORTED
	{
		m_engine->AddFont(lua_tostring(state, 1), LUA_FLOAT(state, 2), LUA_FLOAT(state, 3));
		return 0;
	}

	static int32_t SetTilesMultiplier(lua_State* state) noexcept
	{
		SetCellMultiplier(LUA_FLOAT(state, 1));
		return 0;
	}

	static int32_t __LoadTilesResourceFromFile(lua_State* state)
	{
		LoadTilesResourceFromFile(lua_tostring(state, 1));
		return 0;
	}

	static int SetTile(lua_State* state) //EXPORTED
	{
		XMFLOAT2 position;
		position.x= m_global->m_lastPoint.x;
		position.y = m_global->m_lastPoint.y;
		m_renderer->SetTile(position,(int32_t)lua_tointeger(state, 1), (int32_t)lua_tointeger(state, 2));
		return 0;
	}

	static int SaveInstance(lua_State* state)
	{
		m_renderer->SaveInstanceToFile(lua_tostring(state, 1));
		return 0;
	}

	static int LoadInstance(lua_State* state)
	{
		m_renderer->LoadInstanceToFile(lua_tostring(state, 1));
		return 0;
	}

	static int GetInput(lua_State* state)
	{
		lua_pushstring(state, (ipp::Console::GetInput().c_str()));
		return 1;
	}

	static int Println(lua_State* state)
	{
		ipp::Console::Println(lua_tostring(state, 1));
		return 0;
	}

	static int GameChatMessageFront(lua_State* state)
	{
		class GameChat* gc = UserInterfaceGame::GetGameChat();
		if (gc)
		{
			std::string str = lua_tostring(state, 1);
			gc->PushTextFront(str);
		}
		else
		{
			ipp::Console::SetTextColor(ipp::TextColors::RED);
			ipp::Console::Println("Game chat has not been initialized!");
		}
		return 0;
	}

	static int GameChatMessageBack(lua_State* state)
	{
		class GameChat* gc = UserInterfaceGame::GetGameChat();
		if (gc)
		{
			std::string str = lua_tostring(state, 1);
			gc->PushText(str);
		}
		else
		{
			ipp::Console::SetTextColor(ipp::TextColors::RED);
			ipp::Console::Println("Game chat has not been initialized!");
		}
		return 0;
	}

	static int ClearGameChat(lua_State* state)
	{
		class GameChat* gc = UserInterfaceGame::GetGameChat();
		if (gc)
		{
			gc->ClearQueue();
		}
		return 0;
	}

	static void RegisterFunctions()
	{
		lua_State* m_lua = lua::GetInstance();

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
		lua_register(m_lua, "SetPushableFlag", lua_callback::SetPushableFlag);
		lua_register(m_lua, "SetRenderingFlag", lua_callback::SetRenderingFlag);
		lua_register(m_lua, "SetShadowFlag", lua_callback::SetShadowFlag);
		lua_register(m_lua, "SetSelectableFlag", lua_callback::SetSelectableFlag);
		lua_register(m_lua, "SetCollisionPriority", lua_callback::SetPushableFlag);
		lua_register(m_lua, "GetRenderContainerFlag", lua_callback::GetRenderContainerFlag);
		lua_register(m_lua, "SetFlags", lua_callback::SetFlags);
		lua_register(m_lua, "SetFootstepsSound", lua_callback::SetFootstepsSound);
		lua_register(m_lua, "BeginRunning", lua_callback::BeginRunning);
		lua_register(m_lua, "EndRunning", lua_callback::EndRunning);
		//lua_register(m_lua, "SetZ", lua_callback::SetZ);
		//Units
		lua_register(m_lua,"CreateUnit", lua_callback::CreateUnit);
		lua_register(m_lua,"InitializeUnit", lua_callback::InitializeUnit);
		lua_register(m_lua,"SetWalkingStance", lua_callback::SetWalkingStance);
		lua_register(m_lua,"ChangeWalkingStance", lua_callback::_Units::ChangeWalkingStance);
		lua_register(m_lua,"SetUnitSpeed", lua_callback::SetUnitSpeed);
		lua_register(m_lua,"SetUnitRotations", lua_callback::SetUnitRotations);
		lua_register(m_lua, "PickUnit", lua_callback::PickUnit);
		lua_register(m_lua, "DeleteUnit", lua_callback::DeleteUnit);
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
		lua_register(m_lua,"GiveTaskGotoPoint", lua_callback::GiveTaskGotoPoint);
		lua_register(m_lua,"SetTaskGotoPoint", lua_callback::SetTaskGotoPoint);
		lua_register(m_lua,"CleanTasks", lua_callback::CleanTasks);
		lua_register(m_lua,"GetUnitPosition", lua_callback::GetUnitPosition);

		lua_register(m_lua, "SetUnitPosition", lua_callback::SetUnitPosition);
		lua_register(m_lua, "GetUnitsInRange", lua_callback::GetUnitsInRange);
		lua_register(m_lua, "GetSize", lua_callback::GetSize);
		lua_register(m_lua, "PopGroup", lua_callback::PopGroup);
		lua_register(m_lua, "GetUnitPosition", lua_callback::GetUnitPosition);
		lua_register(m_lua, "PushUnitVariable", lua_callback::PushUnitVariable);
		lua_register(m_lua, "GetUnitVariable", lua_callback::GetUnitVariable);
		lua_register(m_lua, "EraseUnitVariable", lua_callback::EraseUnitVariable);
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
	}

}

}
