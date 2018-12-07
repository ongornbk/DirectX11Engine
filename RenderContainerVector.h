#pragma once
#include "RenderContainer.h"
#include "Doodads.h"
#include "AnimatedDoodads.h"
#include "Tree.h"
#include "Unit.h"
#include "Vector.h"
#include <stack>
//#include <forward_list>

//using std::forward_list;

struct RenderContainerVector
{

	RenderContainerVector();

	Vector<RenderContainer*> m_objectsXY[2][32];
	//forward_list<RenderContainer*>   m_objectsXY[2][16];

	void Update(float dt);
	void Sort();
	void _vectorcall Render(ID3D11DeviceContext * deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ShaderPackage &shader) noexcept;
	void Clear();
	void Push(Unit* unit);
	void Push(Doodads* doodads);
	void Push(AnimatedDoodads* animated);
	void Push(Tree* tree);
	std::stack<Unit*> _vectorcall GetUnitsInRange(Unit* object, float range) noexcept;

};