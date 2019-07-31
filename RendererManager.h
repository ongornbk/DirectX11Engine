#pragma once
#include "Engine.h"
#include "Tile.h"
#include "Unit.h"
#include "UserInterfaceGame.h"
#include "UserInterface.h"
#include "Doodads.h"
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


	int32 _vectorcall validateRendering(
		const struct XMFLOAT3& object
	) noexcept;

	void _cdecl CleanupFrame();


class RendererManager
{
public:

	



	RendererManager(Engine* engine,Shader* units,Shader* ui,Shader* shadow,Shader* select);
	~RendererManager();


	void PushUnit(class Unit* unit,const int32 z = 0);
	void PushDoodads(class Doodads* doodads,const int32 z = 0);
	void PushAnimatedDoodads(class AnimatedDoodads* doodads,const int32 z = 0);
	void PushTree(class Tree* doodads,const int32 z = 0);
	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix
	);
	void Update();
	void SetInterface(const uint32 type,class Shader* shader);
	void SetTile(XMFLOAT2 position, const int32 tile);
	void SetTile(XMFLOAT2 position, const int32 tile,const int32 brush);
	void SaveInstanceToFile(std::string filename);
	void LoadInstanceToFile(std::string filename);

	std::stack<Unit*> _vectorcall GetUnitsInRange(class Unit* object,const float range) noexcept;

	static RendererManager* GetInstance();
	static size_t GetNumberOfObjects();
	static __m128 GetNumberOfObjectsX4();
	static std::vector<int64> GetNumberOfObjectsVector();

private:

	

	Engine* m_engine;
	Shader* m_shader;
	Shader* m_unitsShader;
	Shader* m_shadowShader;
	Shader* m_selectShader;

	TileMap* m_map;
	UserInterface* m_ui;
};

