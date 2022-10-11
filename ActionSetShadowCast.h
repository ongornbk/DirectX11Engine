#pragma once
#include "IAction.h"
#include "GameObject.h"

class ActionSetShadowCast :
	public IAction
{
	class modern_handle m_object;
	bool           m_shadowCast;

	ActionSetShadowCast() = delete;

public:

	//ActionApplyColorFilter(class Unit* const object,struct DirectX::XMFLOAT4& color);
	ActionSetShadowCast(class GameObject* const object, bool shadow);
	~ActionSetShadowCast();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};


