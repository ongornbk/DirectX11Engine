#pragma once
#include "IAction.h"
#include "ColorFilter.h"
#include "modern/modern_handle.h"
#include "modern/modern_guard.h"
#include "RenderContainer.h"

class ActionApplyColorFilter :
	public IAction
{
	class modern_handle m_object;
	struct DirectX::XMFLOAT4 m_color;

	ActionApplyColorFilter() = delete;

public:

	//ActionApplyColorFilter(class Unit* const object,struct DirectX::XMFLOAT4& color);
	ActionApplyColorFilter(class EObject* const object, struct DirectX::XMFLOAT4 color);
	~ActionApplyColorFilter();

	void execute() override;
	const enum class ActionBehavior execute_in_array() override;
};

