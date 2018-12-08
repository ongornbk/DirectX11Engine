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

	std::map<int8_t, RenderContainerVector*> m_zVectors;

	bool m_zStance[256];

	void Update(float dt);
	void Sort();
	void _vectorcall Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) noexcept;
	void Clear();
	void Push(Unit* unit, int8_t z);
	void Push(Doodads* doodads, int8_t z);
	void Push(AnimatedDoodads* animated, int8_t z);
	void Push(Tree* tree, int8_t z);
	uint32_t GetSize();
	__m128 GetSizeX4();
	std::vector<uint32_t> GetSizeVector();
	std::stack<Unit*> _vectorcall GetUnitsInRange(Unit* object, float range);

};
