#pragma once
#include "RenderLayer.h"
#include "modern/modern_array.h"

class RenderLayerItem :
	public RenderLayer
{
	class modern_array<class GameObject*> m_objects[2][MAP_DIVISION];
public:
	RenderLayerItem();
	~RenderLayerItem();

	const enum class RenderLayerType GetType() const modern_except_state override;
	void Update(const float dt = 0.f) override;
	void CleanUp() override;
	void _stdcall Sort() override;
	void _stdcall QSort() override;
	void _stdcall StaticSort() override;
	void _stdcall StaticQSort() override;
	void _vectorcall Render(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage& shader
	) modern_except_state override;
	void _vectorcall PreRender(
		struct ID3D11DeviceContext* const deviceContext,
		const struct XMFLOAT4X4& viewMatrix,
		const struct XMFLOAT4X4& projectionMatrix,
		const struct ShaderPackage& shader
	) modern_except_state override;
	void Clear() override;
	void Push(class Unit* const unit) override;
	void Push(class Doodads* const doodads) override;
	void Push(class AnimatedDoodads* const animated) override;
	void Push(class Tree* const tree) override;
	void Push(class RegionPointObject* const tree) override;
	void Push(class GameObject* const object) override;
	void Push(class Interface* const inter) override;
	std::stack<class Unit*> _vectorcall GetUnitsInRange(Unit* object, float range) modern_except_state override;
	std::stack<class Unit*> _vectorcall GetUnitsInRange(Agent* agent, float range) modern_except_state override;
	std::stack<class Tree*> _vectorcall GetTreesBelow(class GameObject* const object, float range)modern_except_state override;
};

