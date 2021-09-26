#pragma once
#include "IAction.h"
#include "Unit.h"
#include "RendererManager.h"
#include "Global.h"
class ActionRemoveObject :
	public IAction
{
	class modern_handle m_object;

	ActionRemoveObject() = delete;

public:

	ActionRemoveObject(class EObject* const object);
	~ActionRemoveObject();
	
	void execute() override;
	const enum class ActionBehavior execute_in_array() override;


};

