#pragma once
#include "IAction.h"
#include "Unit.h"
#include "RendererManager.h"
#include "Global.h"
class ActionRemoveUnit :
	public IAction
{
	class Unit* m_unit;

public:

	ActionRemoveUnit(class Unit* const unit);
	~ActionRemoveUnit();
	
	void execute() override;



};

