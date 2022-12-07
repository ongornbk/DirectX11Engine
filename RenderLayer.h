#pragma once
#include "RenderLayerType.h"
#include "Sorting.h"
#include "Engine.h"
#include "Agent.h"
#include <stack>

#include <modern__.h>

class RenderLayer
{

public:
	virtual ~RenderLayer();


	virtual const enum class RenderLayerType GetType() const modern_except_state = 0;
	virtual void Update(const float dt = 0.f) = 0;
	virtual void CleanUp() = 0;
	virtual void _stdcall Sort() = 0;
	virtual void _stdcall QSort() = 0;
	virtual void _stdcall StaticSort() = 0;
	virtual void _stdcall StaticQSort() = 0;
	virtual void _vectorcall Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage& shader
	) modern_except_state = 0;
	virtual void _vectorcall PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct DirectX::XMFLOAT4X4& viewMatrix,
		const struct DirectX::XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage& shader
	) modern_except_state = 0;
	virtual void Clear() = 0;
	virtual void Push(class Unit* const unit) = 0;
	virtual void Push(class Doodads* const doodads) = 0;
	virtual void Push(class AnimatedDoodads* const animated) = 0;
	virtual void Push(class Tree* const tree) = 0;
	virtual void Push(class RegionPointObject* const tree) = 0;
	virtual void Push(class GameObject* const object) = 0;
	virtual void Push(class Interface* const inter) = 0;
	virtual std::stack<class Unit*> _vectorcall GetUnitsInRange(Unit* object, float range) modern_except_state = 0;
	virtual std::stack<class Unit*> _vectorcall GetUnitsInRange(Agent* agent, float range) modern_except_state = 0;
	virtual std::stack<class Tree*> _vectorcall GetTreesBelow(class GameObject* const object, float range) = 0;
	virtual size_t GetNumberOfObjects() const modern_except_state;

protected:
	size_t m_size = 0ull;
};

