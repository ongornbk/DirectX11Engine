#pragma once
#include "ColorFilter.h"
#include "GameObject.h"
#include "IAction.h"

class ActionAddAlpha :
	public IAction
{
	class modern_handle m_object;
	float m_alpha;

	ActionAddAlpha() = delete;

public:

	//ActionApplyColorFilter(class Unit* const object,struct DirectX::XMFLOAT4& color);
	ActionAddAlpha(class GameObject* const object,const float alpha);
	~ActionAddAlpha();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

