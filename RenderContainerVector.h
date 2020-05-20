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
	void _stdcall Sort();
	void _stdcall QSort();
	void _vectorcall Render(
		struct ID3D11DeviceContext * const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) noexcept;
	void _vectorcall PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage& shader
	) noexcept;
	void Clear();
	void Push(class Unit* const unit);
	void Push(class Doodads* const doodads);
	void Push(class AnimatedDoodads* const animated);
	void Push(class Tree* const tree);
	std::stack<class Unit*> _vectorcall GetUnitsInRange(Unit* object, float range) noexcept;

};