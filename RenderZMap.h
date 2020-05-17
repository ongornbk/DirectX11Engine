#pragma once
#include "Shader.h"
#include "Doodads.h"
#include "RendererManager.h"
#include "RenderContainerVector.h"
#include "Tree.h"
#include <stack>
#include <map>


struct RenderZMap
{

	RenderZMap();

	~RenderZMap();

	std::map<int64, EObjectVector*> m_zVectors;

	bool m_zStance[256];

	void UpdateFps(const int32 fps);
	void Update(const float dt);
	void CleanUp();
	void Sort();
	void _vectorcall Render(
		struct ID3D11DeviceContext * const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		struct ShaderPackage &shader
	) noexcept;
	void Clear();
	void Push(Unit* unit,const int64 z);
	void Push(Doodads* doodads,const int64 z);
	void Push(AnimatedDoodads* animated,const int64 z);
	void Push(Tree* tree, const int64 z);
	uint32_t GetSize();
	__m128 GetSizeX4();
	std::vector<int64> GetSizeVector();
	std::stack<Unit*> GetUnitsInRange(class Unit* object,const float range);

private:

	int32 m_fps;
	int32 m_sortingDepth;
};
