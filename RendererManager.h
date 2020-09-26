#pragma once
#include "Engine.h"
#include "Tile.h"
#include "Unit.h"
#include "UserInterfaceGame.h"
#include "UserInterface.h"
#include "Doodads.h"
#include "Tree.h"
#include "RegionPointObject.h"
#include "RenderContainerVector.h"
#include "modern/modern_array.h"
#include "RenderLayer.h"
#include <stack>
#include <map>

#pragma region
class Engine;
class Model;
class Unit;
class Doodads;
class AnimatedDoodads;
class Tree;
class RegionPointObject;
class UserInterfaceGame;
class UserInterfaceGameMenu;
class UserInterfaceMainMenu;
class UserInterface;
struct TileMap;
struct RenderContainerVector;
#pragma endregion

_Use_decl_annotations_
	const _Out_ int32 _stdcall validateRendering(
		const struct XMFLOAT3& _In_ object
	) noexcept;

	void _cdecl CleanupFrame();
	void _cdecl EditFrame();

class RendererManager
{
public:

	



	RendererManager(Engine* engine,Shader* units,Shader* ui,Shader* shadow,Shader* select);
	~RendererManager();


	void PushUnit(class Unit* unit);
	void PushDoodads(class Doodads* doodads);
	void PushAnimatedDoodads(class AnimatedDoodads* doodads);
	void PushTree(class Tree* doodads);
	void Push(class EObject* const object, const enum class RenderLayerType layer);
	void PushRegionPointObject(class RegionPointObject* object);
	void Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix
	);
	void Update();
	void SetInterface(const uint32 type,class Shader* shader);
	void SetTile(struct DirectX::XMFLOAT2 &position, const int32 tile);
	void SetTile(struct DirectX::XMFLOAT2 &position, const int32 tile,const int32 brush);
	void SaveInstanceToFile(std::string filename);
	void LoadInstanceToFile(std::string filename);
	void SetTileMapRendering(const int64 rendering = 1);
	void SetFps(const int32 fps);

	std::stack<class Unit*> _vectorcall GetUnitsInRange(class Unit* const object,const float range) noexcept;

	static class RendererManager* GetInstance();
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

	class RenderLayer* m_layers[enum_cast<int32_t>(RenderLayerType::COUNT)];

	//EObjectVector m_objects;
};

