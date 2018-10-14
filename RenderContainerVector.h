#pragma once
#include "RenderContainer.h"
#include "Doodads.h"
#include "AnimatedDoodads.h"
#include "Tree.h"
#include "Unit.h"
#include <stack>

struct RenderContainerVector
{

	RenderContainerVector();

	vector<RenderContainer*> m_objectsX[16];
	vector<RenderContainer*> m_objectsY[16];

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