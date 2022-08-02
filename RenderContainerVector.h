#pragma once
#include "AnimatedDoodads.h"
#include "RenderContainer.h"
#include "Doodads.h"
#include "Tree.h"
#include "Unit.h"
#include "modern/modern.h"
#include "game_math.h"
#include <stack>
//#include <forward_list>

//using std::forward_list;

struct EObjectVector
{

	EObjectVector();

	class modern_array<class EObject*> m_objectsXY[2][MAP_DIVISION];
	//forward_list<RenderContainer*>   m_objectsXY[2][16];

	void Update(float dt);
	void CleanUp();
	void _stdcall Sort();
	void _stdcall QSort();
	void _stdcall StaticSort();
	void _stdcall StaticQSort();
	void _vectorcall Render(
		struct ID3D11DeviceContext * const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage &shader
	) modern_except_state;
	void _vectorcall PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage& shader
	) modern_except_state;
	void Clear();
	void Push(class Unit* const unit);
	void Push(class Doodads* const doodads);
	void Push(class AnimatedDoodads* const animated);
	void Push(class Tree* const tree);
	void Push(class RegionPointObject* const tree);
	std::stack<class Unit*> _vectorcall GetUnitsInRange(Unit* object, float range) modern_except_state;

};