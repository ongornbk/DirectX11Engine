#pragma once
#include "AnimatedDoodads.h"
#include "RenderContainer.h"
#include "Doodads.h"
#include "Tree.h"
#include "Unit.h"
#include "Vector.h"
#include <stack>
//#include <forward_list>

//using std::forward_list;

struct EObjectVector
{

	EObjectVector();

	Vector<EObject*> m_objectsXY[2][32];
	//forward_list<RenderContainer*>   m_objectsXY[2][16];

	void Update(float dt);
	void CleanUp();
	void Sort();
	void _vectorcall Render(
		struct ID3D11DeviceContext * const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) noexcept;
	void Clear();
	void Push(Unit* unit);
	void Push(Doodads* doodads);
	void Push(AnimatedDoodads* animated);
	void Push(Tree* tree);
	std::stack<Unit*> _vectorcall GetUnitsInRange(Unit* object, float range) noexcept;

};