#pragma once
#include "Engine.h"
#include "Tile.h"
#include "Unit.h"
#include "UserInterfaceGame.h"
#include "UserInterface.h"
#include "Stack.h"
#include <stack>

#pragma region
class Engine;
class Model;
class Unit;
class UserInterfaceGame;
class UserInterfaceGameMenu;
class UserInterfaceMainMenu;
class UserInterface;
struct TileMap;
#pragma endregion

extern "C"
{
	bool _vectorcall validateRendering(XMFLOAT3 object) noexcept;
}

struct UnitsVector
{
	vector<Unit*> m_objects;

	void Update(float dt);
	void Sort();
	void Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, Shader* shader);
	void Clear();
	void Push(Unit* unit);
	static std::stack<Unit*> GetUnitsInRange(Unit* object, float range);

};


class RendererManager
{
public:

	

	enum RenderingStyle
	{
		NOREVERSE = 0,
		REVERSE = 1
	};

	RendererManager(Engine* engine,Shader* shader);
	~RendererManager();


	void PushUnit(Unit* unit);
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix);
	void Update();
	void SetRenderingStyle(RenderingStyle render);
	void SetInterface(unsigned int type, Shader* shader);
	void SetTile(XMFLOAT2 position, int32_t tile);
	void SaveInstanceToFile(std::string filename);
	void LoadInstanceToFile(std::string filename);

	static RendererManager* GetInstance();
private:

	

	Engine* m_engine;
	Shader* m_shader;



	RenderingStyle m_renderingStyle;
	TileMap* m_map;
	UserInterface* m_ui;
};

