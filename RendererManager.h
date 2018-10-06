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


struct RenderZMap
{

	RenderZMap();

	~RenderZMap();

	std::map<int8_t, RenderContainerVector*> m_zVectors;
	
	bool m_zStance[256];

	void Update(float dt);
	void Sort();
	void _vectorcall Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader* shader) noexcept;
	void Clear();
	void Push(Unit* unit,int8_t z);
	void Push(Doodads* doodads, int8_t z);
	void Push(AnimatedDoodads* animated, int8_t z);
	void Push(Tree* tree, int8_t z);
	uint32_t GetSize();
	__m128 GetSizeX4();
	std::stack<Unit*> _vectorcall GetUnitsInRange(Unit* object, float range);

};

struct RenderContainerVector
{

	RenderContainerVector();

	vector<RenderContainer*> m_objectsX[4];
	vector<RenderContainer*> m_objectsY;

	void Update(float dt);
	void Sort();
	void _vectorcall Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader* shader) noexcept;
	void Clear();
	void Push(Unit* unit);
	void Push(Doodads* doodads);
	void Push(AnimatedDoodads* animated);
	void Push(Tree* tree);
	std::stack<Unit*> _vectorcall GetUnitsInRange(Unit* object, float range) noexcept;

};


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

