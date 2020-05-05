#pragma once
#include "IAction.h"
#include "Unit.h"

class ActionApplyColorFilter :
	public IAction
{
	class Unit* m_object;
	struct DirectX::XMFLOAT4 m_color;

	ActionApplyColorFilter() = delete;

public:

	ActionApplyColorFilter(class Unit* const object,struct DirectX::XMFLOAT4& color);
	~ActionApplyColorFilter();

	void execute() override;
};

