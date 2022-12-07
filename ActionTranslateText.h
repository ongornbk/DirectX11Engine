#pragma once
#include "IAction.h"

class ActionTranslateText :
	public IAction
{
	class modern_handle m_object;
	struct DirectX::XMFLOAT3 m_vec;

	ActionTranslateText() = delete;

public:

	//ActionApplyColorFilter(class Unit* const object,struct DirectX::XMFLOAT4& color);
	ActionTranslateText(class modern_handle& object,const struct DirectX::XMFLOAT3 position);
	~ActionTranslateText();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

