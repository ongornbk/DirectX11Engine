#pragma once
#include "Engine.h"
#include "Tile.h"
#include "Unit.h"
#include "UserInterfaceGame.h"
#include "UserInterface.h"
#include "Stack.h"
#include "Doodads.h"
#include "AnimatedDoodads.h"
#include "Tree.h"
#include "RenderZMap.h"
#include <stack>
#include <map>

#pragma region
class Engine;
class Model;
class Unit;
class Doodads;
class AnimatedDoodads;
class Tree;
class UserInterfaceGame;
class UserInterfaceGameMenu;
class UserInterfaceMainMenu;
class UserInterface;
struct TileMap;
struct RenderContainerVector;
#pragma endregion

extern "C"
{
	bool _vectorcall validateRendering(XMFLOAT3 object) noexcept;
}


class RendererManager
{
public:

	

	enum RenderingStyle
	{
		NOREVERSE = 0,
		REVERSE = 1
	};

	RendererManager(Engine* engine,Shader* units,Shader* ui);
	~RendererManager();


	void PushUnit(Unit* unit,int8_t z);
	void PushDoodads(Doodads* doodads, int8_t z);
	void PushAnimatedDoodads(AnimatedDoodads* doodads, int8_t z);
	void PushTree(Tree* doodads, int8_t z);
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update();
	void SetRenderingStyle(RenderingStyle render);
	void SetInterface(uint32_t type, Shader* shader);
	void SetTile(XMFLOAT2 position, int32_t tile);
	void SetTile(XMFLOAT2 position, int32_t tile,int32_t brush);
	void SaveInstanceToFile(std::string filename);
	void LoadInstanceToFile(std::string filename);

	std::stack<Unit*> _vectorcall GetUnitsInRange(Unit* object, float range) noexcept;

	static RendererManager* GetInstance();
	static size_t GetNumberOfObjects();
	static __m128 GetNumberOfObjectsX4();

private:

	

	Engine* m_engine;
	Shader* m_shader;
	Shader* m_unitsShader;



	RenderingStyle m_renderingStyle;
	TileMap* m_map;
	UserInterface* m_ui;
};

