#pragma once
#include "Engine.h"
#include "Tile.h"
#include "Unit.h"
#include "UserInterfaceGame.h"
#include "UserInterface.h"
#include "Doodads.h"
#include "Tree.h"
#include "Interface.h"
#include "RegionPointObject.h"
#include "RenderContainerVector.h"
#include "modern/modern_array.h"
#include "RenderLayer.h"
#include "ObjectFocusType.h"
#include "Agent.h"
#include "Projectile.h"
#include "LineOfCollision.h"
#include "RectOfCollision.h"
#include "Region.h"
#include "UserInterfaceState.h"
#include "FuzzyTimer.h"
#include <stack>
#include <map>
#include <list>

#pragma region
class Engine;
class Model;
class Unit;
class Doodads;
class AnimatedDoodads;
class Tree;
class Agent;
class LineOfCollisionAgent;
class Projectile;
class RegionPointObject;
class UserInterfaceGame;
class UserInterfaceGameMenu;
class UserInterfaceMainMenu;
class UserInterface;
class Region;
struct TileMap;
struct RenderContainerVector;
#pragma endregion

_Use_decl_annotations_
	const _Out_ int32 _stdcall validateRendering(
		const struct XMFLOAT3& _In_ object
	) modern_except_state;

	void _cdecl CleanupFrame();
	void _cdecl EditFrame();

class RendererManager
{
public:

	



	RendererManager(Engine* engine,Shader* units,Shader* ui,Shader* shadow,Shader* select,Shader* inter);
	~RendererManager();




	void PushUnit(class Unit* unit);
	void PushAgent(class Agent* const agent);
	void PushProjectile(class Projectile* const proj);
	void PushDoodads(class Doodads* doodads);
	void PushAnimatedDoodads(class AnimatedDoodads* doodads);
	void PushTree(class Tree* doodads);
	void PushLineOfCollisionAgent(class LineOfCollisionAgent* const agent);
	void PushRectOfCollisionAgent(class RectOfCollisionAgentFirst* const agent);
	void PushRectOfCollisionAgent(class RectOfCollisionAgentSecond* const agent);
	void PushRegionAgent(class RegionAgent* const agent);
	void PushRegionAgentMaster(class RegionAgentMaster* const agent);
	void PushRenderAgent(class RenderAgent* const agent);
	void Push(class EObject* const object, const enum class RenderLayerType layer);
	void PushRegionPointObject(class RegionPointObject* object);
	void PushInterface(class Interface * const object);
	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix
	);
	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct XMFLOAT4X4& interfaceMatrix
	);
	void Update(const float dt,const bool renderframe = false);
	void Sort();
	void PostSortUpdate(const float dt, const bool renderframe = false);
	void Focus(class EObject* const object,const enum class ObjectFocusType type);
	void SetInterface(const uint32 type,class Shader* shader);
	void SetTile(struct DirectX::XMFLOAT2 &position, const int32 tile);
	void SetTile(struct DirectX::XMFLOAT2 &position, const int32 tile,const int32 brush);
	void SaveInstanceToFile(std::string filename);
	void LoadInstanceToFile(std::string filename);
	void SetTileMapRendering(const int64 rendering = 1);
	void SetFps(const int32 fps);
	void SetFocus(class Unit* const unit);
	void EnableCollision(const bool collision = true);
	void SetState(const int64_t state) modern_except_state;
	void Clear();
	class TextFont* const GetFont();

	class Interface* const GetHealthBarMini();
	class Interface* const GetHealthBarMiniBorder();
	class modern_handle& GetCursorAgentHandle();
	class modern_handle& GetFocusAgentHandle();

	std::stack<class Unit*> _vectorcall GetUnitsInRange(class Unit* const object,const float range) modern_except_state;
	std::stack<class Unit*> _vectorcall GetUnitsInRange(class Agent* const agent, const float range) modern_except_state;

	static class RendererManager* GetInstance();
	size_t GetNumberOfObjects();
	static __m128 GetNumberOfObjectsX4();
	static std::vector<int64> GetNumberOfObjectsVector();

private:

	bool m_collision;
	int64_t m_state{};

	Engine* m_engine;
	Shader* m_shader;
	Shader* m_unitsShader;
	Shader* m_shadowShader;
	Shader* m_selectShader;
	Shader* m_interfaceShader;

	TileMap* m_map;
	UserInterface* m_ui;
	class modern_handle m_focus;
	class RenderLayer* m_layers[enum_cast<int32_t>(RenderLayerType::COUNT)];
	class TextFont* m_font;
	class modern_handle m_fpsText;
	class modern_handle m_objectsText;
	class modern_handle m_timersText;
	class modern_handle m_bmapText;
	class modern_handle m_selectStatus;
	class modern_handle m_selectStatusBorder; //TEMP THERE SHOULD BE AN ARRAY IN INTERFACE TO DRAW 
	class modern_handle m_cursorAgent;
	//class modern_handle m_cursor;
	class modern_handle m_gameUI;
	class modern_handle m_healthGlobe;
	class modern_handle m_manaGlobe;
	class modern_handle m_exp;
	class modern_handle m_healthBar;
	class modern_handle m_healthBarBorder;
	class modern_handle m_damage;

	std::list<modern_handle> m_selectGroup;

	//modern_handle test_line0;
	//modern_handle test_line1;
	//modern_handle test_line2;
	//modern_handle test_line3;
	//modern_handle test_region;

	enum class UserInterfaceState m_type = UserInterfaceState::ENUM_USERINTERFACE_TEMPNONE;

	int32 m_fps;
	//EObjectVector m_objects;
};

