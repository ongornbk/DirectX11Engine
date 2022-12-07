#pragma once
#include "IAction.h"
#include "ColorFilter.h"
#include "GameObject.h"

class ActionApplyColorFilter :
	public IAction
{
	class modern_handle m_object;
	struct DirectX::XMFLOAT4 m_color;

	ActionApplyColorFilter() = delete;

public:

	//ActionApplyColorFilter(class Unit* const object,struct DirectX::XMFLOAT4& color);
	ActionApplyColorFilter(class GameObject* const object, struct DirectX::XMFLOAT4 color);
	~ActionApplyColorFilter();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

